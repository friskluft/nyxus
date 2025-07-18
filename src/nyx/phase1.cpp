#include <string>
#include <vector>
#include <map>
#include <array>
#include <regex>

#ifdef WITH_PYTHON_H
	#include <pybind11/pybind11.h>
	#include <pybind11/stl.h>
	#include <pybind11/numpy.h>
	namespace py = pybind11;
#endif

#include "environment.h"
#include "globals.h"
#include "helpers/timing.h"

namespace Nyxus
{
	//
	// segmented 2D case
	//
	bool gatherRoisMetrics (int sidx, const std::string & intens_fpath, const std::string & label_fpath, ImageLoader & L)
	{
		// Reset per-image counters and extrema
		//	 -- disabling this due to new prescan functionality-->	LR::reset_global_stats();

		int lvl = 0, // Pyramid level
			lyr = 0; //	Layer

		// Read the tiff. The image loader is put in the open state in processDataset()
		size_t nth = L.get_num_tiles_hor(),
			ntv = L.get_num_tiles_vert(),
			fw = L.get_tile_width(),
			th = L.get_tile_height(),
			tw = L.get_tile_width(),
			tileSize = L.get_tile_size(),
			fullwidth = L.get_full_width(),
			fullheight = L.get_full_height();

		int cnt = 1;
		for (unsigned int row = 0; row < nth; row++)
			for (unsigned int col = 0; col < ntv; col++)
			{
				// Fetch the tile 
				bool ok = L.load_tile(row, col);
				if (!ok)
				{
					std::string erm = "Error fetching tile row:" + std::to_string(row) + " col:" + std::to_string(col) + " from I:" + intens_fpath + " M:" + label_fpath;
					#ifdef WITH_PYTHON_H
						throw erm;
					#endif	
					std::cerr << erm << "\n";
					return false;
				}

				// Get ahold of tile's pixel buffer
				const std::vector<uint32_t>& dataI = L.get_int_tile_buffer();
				const std::shared_ptr<std::vector<uint32_t>>& spL = L.get_seg_tile_sptr();
				bool wholeslide = spL == nullptr; // alternatively, theEnvironment.singleROI

				// Iterate pixels
				for (size_t i = 0; i < tileSize; i++)
				{
					// mask label if not in the wholeslide mode
					PixIntens label = 1;
					if (!wholeslide)
						label = (*spL)[i];

					// Skip non-mask pixels
					if (! label)
						continue;

					int y = row * th + i / tw,
						x = col * tw + i % tw;
					
					// Skip tile buffer pixels beyond the image's bounds
					if (x >= fullwidth || y >= fullheight)
						continue;

					// Update pixel's ROI metrics
					feed_pixel_2_metrics (x, y, dataI[i], label, sidx); // Updates 'uniqueLabels' and 'roiData'
				}

#ifdef WITH_PYTHON_H
				if (PyErr_CheckSignals() != 0)
					throw pybind11::error_already_set();
#endif

				// Show progress info
				VERBOSLVL2(
					if (cnt++ % 4 == 0)
						std::cout << "\t" << int((row * nth + col) * 100 / float(nth * ntv) * 100) / 100. << "%\t" << uniqueLabels.size() << " ROIs" << "\n";
				);
			}

		// fix ROIs' AABBs with respect to anisotropy
		if (theEnvironment.anisoOptions.customized() == false)
		{
			for (auto& rd : roiData)
			{
				LR& r = rd.second;
				r.make_nonanisotropic_aabb ();
			}
		}
		else
		{
			double	ax = theEnvironment.anisoOptions.get_aniso_x(),
						ay = theEnvironment.anisoOptions.get_aniso_y();

			for (auto& rd : roiData)
			{
				LR& r = rd.second;
				r.make_anisotropic_aabb (ax, ay);
			}
		}

		return true;
	}

	//
	// segmented 2.5D case (aka layoutA, collections of 2D slice images e.g. blah_z1_blah.ome.tif, blah_z2_blah.ome.tif, ..., blah_z500_blah.ome.tif)
	// prerequisite: 'theImLoader' needs to be pre-opened !
	//
	bool gatherRoisMetrics_25D (const std::string& intens_fpath, const std::string& mask_fpath, const std::vector<std::string>& z_indices)
	{
		// Cache the file names in global variables '' to be picked up 
		// by labels in feed_pixel_2_metrics_3D() to link ROIs with their image file origins
		theIntFname = intens_fpath;
		theSegFname = mask_fpath;

		int lvl = 0, // Pyramid level
			lyr = 0; //	Layer

		for (size_t z=0; z<z_indices.size(); z++)
		{ 
			// prepare the physical file 
			// 
			// ifile and mfile contain a placeholder for the z-index. We need to turn them to physical filesystem files
			auto zValue = z_indices[z];	// realistic dataset's z-values may be arbitrary (non-zer-based and non-contiguous), so use the actual value
			std::string ifpath = std::regex_replace (intens_fpath, std::regex("\\*"), zValue),
				mfpath = std::regex_replace (mask_fpath, std::regex("\\*"), zValue);

			// temp SlideProps object
			SlideProps sprp;
			sprp.fname_int = ifpath;
			sprp.fname_seg = mfpath;

			// Extract features from this intensity-mask pair 
			if (theImLoader.open(sprp) == false)
			{
				std::cerr << "Error opening a file pair with ImageLoader. Terminating\n";
				return false;
			}

			// Read the tiff. The image loader is put in the open state in processDataset()
			size_t nth = theImLoader.get_num_tiles_hor(),
				ntv = theImLoader.get_num_tiles_vert(),
				fw = theImLoader.get_tile_width(),
				th = theImLoader.get_tile_height(),
				tw = theImLoader.get_tile_width(),
				tileSize = theImLoader.get_tile_size(),
				fullwidth = theImLoader.get_full_width(),
				fullheight = theImLoader.get_full_height();

			int cnt = 1;
			for (unsigned int row = 0; row < nth; row++)
				for (unsigned int col = 0; col < ntv; col++)
				{
					// Fetch a tile 
					bool ok = theImLoader.load_tile (row, col);
					if (!ok)
					{
						std::string erm = "Error fetching tile row:" + std::to_string(row) + " col:" + std::to_string(col) + " from I:" + ifpath + " M:" + mfpath;
						#ifdef WITH_PYTHON_H
							throw erm;
						#endif	
						std::cerr << erm << "\n";
						return false;
					}

					// Get ahold of tile's pixel buffer
					auto dataI = theImLoader.get_int_tile_buffer(),
						dataL = theImLoader.get_seg_tile_buffer();

					// Iterate pixels
					for (size_t i = 0; i < tileSize; i++)
					{
						// Skip non-mask pixels
						auto label = dataL[i];
						if (!label)
							continue;

						int y = row * th + i / tw,
							x = col * tw + i % tw;

						// Skip tile buffer pixels beyond the image's bounds
						if (x >= fullwidth || y >= fullheight)
							continue;

						// Collapse all the labels to one if single-ROI mde is requested
						if (theEnvironment.singleROI)
							label = 1;

						// Update pixel's ROI metrics
						feed_pixel_2_metrics_3D  (x, y, z, dataI[i], label); // Updates 'uniqueLabels' and 'roiData'
					}

					#ifdef WITH_PYTHON_H
					if (PyErr_CheckSignals() != 0)
						throw pybind11::error_already_set();
					#endif

					// Show stayalive progress info
					VERBOSLVL2(
						if (cnt++ % 4 == 0)
							std::cout << "\t" << int((row * nth + col) * 100 / float(nth * ntv) * 100) / 100. << "%\t" << uniqueLabels.size() << " ROIs" << "\n";
					);
				}

			theImLoader.close();
		}

		// fix ROIs' AABBs with respect to anisotropy
		if (theEnvironment.anisoOptions.customized() == false)
		{
			for (auto& rd : roiData)
			{
				LR& r = rd.second;
				r.make_nonanisotropic_aabb();
			}
		}
		else
		{
			double	ax = theEnvironment.anisoOptions.get_aniso_x(),
				ay = theEnvironment.anisoOptions.get_aniso_y(), 
				az = theEnvironment.anisoOptions.get_aniso_z();

			for (auto& rd : roiData)
			{
				LR& r = rd.second;
				r.make_anisotropic_aabb (ax, ay, az);
			}
		}

		return true;
	}

	//
	// segmented 3D case (true volumetric images e.g. .nii, .nii.gz, .dcm, etc)
	// prerequisite: 'theImLoader' needs to be pre-opened !
	//
	bool gatherRoisMetrics_3D (const std::string& intens_fpath, const std::string& mask_fpath)
	{
		// Cache the file names in global variables '' to be picked up 
		// by labels in feed_pixel_2_metrics_3D() to link ROIs with their image file origins
		theIntFname = intens_fpath;
		theSegFname = mask_fpath;

		int lvl = 0, // Pyramid level
			lyr = 0; //	Layer

		// temp SlideProps object
		SlideProps sprp;
		sprp.fname_int = intens_fpath;
		sprp.fname_seg = mask_fpath;

		// Extract features from this intensity-mask pair 
		if (theImLoader.open(sprp) == false)
		{
			std::cerr << "Error opening a file pair with ImageLoader. Terminating\n";
			return false;
		}

		// Read the tiff. The image loader is put in the open state in processDataset()
		size_t nth = theImLoader.get_num_tiles_hor(),
			ntv = theImLoader.get_num_tiles_vert(),
			fw = theImLoader.get_tile_width(),
			th = theImLoader.get_tile_height(),
			tw = theImLoader.get_tile_width(),
			tileSize = theImLoader.get_tile_size(),
			fullwidth = theImLoader.get_full_width(),
			fullheight = theImLoader.get_full_height(),
			fullD = theImLoader.get_full_depth(),
			sliceSize = fullwidth * fullheight,
			nVox = sliceSize * fullD;

		int cnt = 1;
		for (size_t row = 0; row < nth; row++)
			for (size_t col = 0; col < ntv; col++)
			{
				// Fetch a tile 
				bool ok = theImLoader.load_tile(row, col);
				if (!ok)
				{
					std::string erm = "Error fetching tile row:" + std::to_string(row) + " col:" + std::to_string(col) + " from I:" + intens_fpath + " M:" + mask_fpath;
					#ifdef WITH_PYTHON_H
						throw erm;
					#endif	
					std::cerr << erm << "\n";
					return false;
				}

				// Get ahold of tile's pixel buffer
				auto dataI = theImLoader.get_int_tile_buffer(),
					dataL = theImLoader.get_seg_tile_buffer();

				// Iterate voxels
				for (size_t i = 0; i < nVox; i++)
				{
					// Skip non-mask pixels
					auto label = dataL[i];
					if (!label)
						continue;

					int z = i / sliceSize,
						y = (i - z*sliceSize) / tw,
						x = (i - z * sliceSize) % tw;

					// Skip tile buffer pixels beyond the image's bounds
					if (x >= fullwidth || y >= fullheight || z >= fullD)
						continue;

					// Collapse all the labels to one if single-ROI mde is requested
					if (theEnvironment.singleROI)
						label = 1;

					// Update pixel's ROI metrics
					feed_pixel_2_metrics_3D (x, y, z, dataI[i], label); // Updates 'uniqueLabels' and 'roiData'
				}

#ifdef WITH_PYTHON_H
				if (PyErr_CheckSignals() != 0)
					throw pybind11::error_already_set();
#endif

				// Show stayalive progress info
				VERBOSLVL2(
					if (cnt++ % 4 == 0)
						std::cout << "\t" << int((row * nth + col) * 100 / float(nth * ntv) * 100) / 100. << "%\t" << uniqueLabels.size() << " ROIs" << "\n";
				);
			}

		theImLoader.close();

		// fix ROIs' AABBs with respect to anisotropy
		if (theEnvironment.anisoOptions.customized() == false)
		{
			for (auto& rd : roiData)
			{
				LR& r = rd.second;
				r.make_nonanisotropic_aabb();
			}
		}
		else
		{
			double	ax = theEnvironment.anisoOptions.get_aniso_x(),
				ay = theEnvironment.anisoOptions.get_aniso_y(),
				az = theEnvironment.anisoOptions.get_aniso_z();

			for (auto& rd : roiData)
			{
				LR& r = rd.second;
				r.make_anisotropic_aabb(ax, ay, az);
			}
		}

		return true;
	}

#ifdef WITH_PYTHON_H
	//
	// segmented 2D case
	//
	bool gatherRoisMetricsInMemory (const py::array_t<unsigned int, py::array::c_style | py::array::forcecast>& intens_images, const py::array_t<unsigned int, py::array::c_style | py::array::forcecast>& label_images, int pair_index)
	{
		VERBOSLVL4(std::cout << "gatherRoisMetricsInMemory (pair_index=" << pair_index << ") \n");

		auto rI = intens_images.unchecked<3>();
		auto rL = label_images.unchecked<3>();

		size_t w = rI.shape(2);
		size_t h = rI.shape(1);

		for (size_t col = 0; col < w; col++)
			for (size_t row = 0; row < h; row++)
			{
				// Skip non-mask pixels
				auto label = rL (pair_index, row, col);
				if (!label)
					continue;

				// Collapse all the labels to one if single-ROI mde is requested
				if (theEnvironment.singleROI)
					label = 1;

				// Update pixel's ROI metrics
				auto inten = rI (pair_index, row, col);
				feed_pixel_2_metrics (col, row, inten, label, -1); // Updates 'uniqueLabels' and 'roiData'. Using slide_idx=-1

				if (PyErr_CheckSignals() != 0)
					throw pybind11::error_already_set();
			}

		return true;
	}
#endif
}