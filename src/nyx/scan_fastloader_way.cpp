//
// This file is a collection of drivers of tiled TIFF file scanning from the FastLoader side
//
#if __has_include(<filesystem>)
  #include <filesystem>
  namespace fs = std::filesystem;
#elif __has_include(<experimental/filesystem>)
  #include <experimental/filesystem> 
  namespace fs = std::experimental::filesystem;
#else
  error "Missing the <filesystem> header."
#endif
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <map>
#include <array>
#ifdef WITH_PYTHON_H
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>
namespace py = pybind11;
#endif
#include "environment.h"
#include "globals.h"
#include "helpers/helpers.h"
#include "helpers/timing.h"

// Sanity
#ifdef _WIN32
#include<windows.h>
#endif


namespace Nyxus
{
	std::string get_arrow_filename(const std::string& output_path, const std::string& default_filename, const SaveOption& arrow_file_type){

	/*
				output_path			condition			verdict
	Case 1: 	/foo/bar		exist in fs				is a directory, append default filename with proper ext
				/foo/bar/		or ends with / or \
				\foo\bar\			

	Case 2:		/foo/bar		does not exist in fs	assume the extension is missing, append proper ext
								but /foo exists

	Case 3: 	/foo/bar		neither /foo nor 		treat as directory, append default filename with proper ext
								/foo/bar exists in fs
	
	Case 4: 	/foo/bar.ext	exists in fs and is a 	append default filename with proper ext
								directory	
			
	Case 5: 	/foo/bar.ext	does not exist in fs  	this is a file, check if ext is correct and modify if needed

	Case 6:		empty									default filename with proper ext
								

	*/
		std::string valid_ext = [&arrow_file_type](){
			if (arrow_file_type == Nyxus::SaveOption::saveArrowIPC) {
				return ".arrow";
			} else if (arrow_file_type == Nyxus::SaveOption::saveParquet) {
				return ".parquet";
			} else {return "";}
		}();
		
		if (output_path != ""){
			auto arrow_path = fs::path(output_path);
			if (fs::is_directory(arrow_path) // case 1, 4
			    || Nyxus::ends_with_substr(output_path, "/") 
				|| Nyxus::ends_with_substr(output_path, "\\")){
				arrow_path = arrow_path/default_filename;
			} else if(!arrow_path.has_extension()) { 
				if(!fs::is_directory(arrow_path.parent_path())){ // case 3
					arrow_path = arrow_path/default_filename;
				}
				// else case 2, do nothing here	
			}
			// case 5 here, but also for 1-4, update extenstion here
			arrow_path.replace_extension(valid_ext);
			return arrow_path.string();
		} else { // case 6
			return default_filename + valid_ext;
		}  
	}
	
	bool processIntSegImagePair (const std::string& intens_fpath, const std::string& label_fpath, int num_FL_threads, size_t filepair_index, size_t tot_num_filepairs)
	{
		std::vector<int> trivRoiLabels, nontrivRoiLabels;

		// Timing block (image scanning)
		{
			{ STOPWATCH("scan1/ImgScan1/S1/lightsteelblue", "\t=");

				// Report the amount of free RAM
				unsigned long long freeRamAmt = getAvailPhysMemory();
				static unsigned long long initial_freeRamAmt = 0;
				if (initial_freeRamAmt == 0)
					initial_freeRamAmt = freeRamAmt;
				double memDiff = double(freeRamAmt) - double(initial_freeRamAmt);
				VERBOSLVL4(std::cout << std::setw(15) << freeRamAmt << " bytes free (" << "consumed=" << memDiff << ") ")

					// Display (1) dataset progress info and (2) file pair info
					int digits = 3, 
					k = std::pow(10.f, digits);
				float perCent = float(filepair_index * 100 * k / tot_num_filepairs) / float(k);
				VERBOSLVL1(std::cout << std::setw(digits + 5) << perCent << " %\t" << " INT: " << intens_fpath << " SEG: " << label_fpath << "\n")
			}

			{ STOPWATCH("scan2A/ImgScan2a/S2a/lightsteelblue", "\t=");

				// Phase 1: gather ROI metrics
				VERBOSLVL4 (std::cout << "Gathering ROI metrics\n");
				bool okGather = gatherRoisMetrics(intens_fpath, label_fpath, num_FL_threads);	// Output - set of ROI labels, label-ROI cache mappings
				if (!okGather)
				{
					std::string msg = "Error in gatherRoisMetrics()\n";
					std::cerr << msg;
					throw (std::runtime_error(msg));
					return false;
				}

				// Check presence of zero-background
				if (zero_background_area == 0)
				{
					std::string msg = "Error: mask image " + theSegFname + " contains no zero-background\n";
					std::cerr << msg;
					throw (std::runtime_error(msg));
					return false;
				}
			}

			{ STOPWATCH("scan2B/ImgScan2b/S2b/lightsteelblue", "\t=");

				// Allocate each ROI's feature value buffer
				for (auto lab : uniqueLabels)
				{
					LR& r = roiData[lab];
					r.initialize_fvals();
				}

				// Dump ROI metrics
				VERBOSLVL4(dump_roi_metrics(label_fpath))	// dumps to file in the output directory
			}

			{ STOPWATCH("scan3/ImgScan3/S3/lightsteelblue", "\t=");

				// Support of ROI blacklist
				fs::path fp(theSegFname);
				std::string shortSegFname = fp.stem().string() + fp.extension().string();

				// Distribute ROIs among phases
				for (auto lab : uniqueLabels)
				{
					LR& r = roiData[lab];					
					
					// Skip blacklisted ROI
					if (theEnvironment.roi_is_blacklisted(shortSegFname, lab))
					{
						r.blacklisted = true;
						VERBOSLVL2(std::cout << "Skipping blacklisted ROI " << lab << " for mask " << shortSegFname << "\n");
						continue;
					}

					// Examine ROI's memory footprint
					if (size_t roiFootprint = r.get_ram_footprint_estimate(), 
						ramLim = theEnvironment.get_ram_limit(); 
						roiFootprint >= ramLim)
					{
						VERBOSLVL2(
							std::cout << "oversized ROI " << lab 
								<< " (S=" << r.aux_area 
								<< " W=" << r.aabb.get_width() 
								<< " H=" << r.aabb.get_height() 
								<< " px footprint=" << roiFootprint << " b"								
								<< ")\n"
						);
						nontrivRoiLabels.push_back(lab);
					}
					else
						trivRoiLabels.push_back(lab);
				}
			}
		}

		// Phase 2: process trivial-sized ROIs
		if (trivRoiLabels.size())
		{
			VERBOSLVL4 (std::cout << "Processing trivial ROIs\n")
			processTrivialRois (trivRoiLabels, intens_fpath, label_fpath, num_FL_threads, theEnvironment.get_ram_limit());
		}

		// Phase 3: process nontrivial (oversized) ROIs, if any
		if (nontrivRoiLabels.size())
		{
			VERBOSLVL4 (std::cout << "Processing oversized ROIs\n")
			processNontrivialRois (nontrivRoiLabels, intens_fpath, label_fpath, num_FL_threads);
		}

		return true;
	}

#ifdef WITH_PYTHON_H
	bool processIntSegImagePairInMemory (const py::array_t<unsigned int, py::array::c_style | py::array::forcecast>& intens, const py::array_t<unsigned int, py::array::c_style | py::array::forcecast>& label, int filepair_index, const std::string& intens_name, const std::string& seg_name, std::vector<int> unprocessed_rois)
	{
		std::vector<int> trivRoiLabels;

		// Phase 1: gather ROI metrics
		bool okGather = gatherRoisMetricsInMemory(intens, label, filepair_index);	// Output - set of ROI labels, label-ROI cache mappings
		if (!okGather)
			return false;

		// Allocate each ROI's feature value buffer
		for (auto lab : uniqueLabels)
		{
			LR& r = roiData[lab];

			r.intFname = intens_name;
			r.segFname = seg_name;

			r.initialize_fvals();
		}

		// Distribute ROIs among phases
		for (auto lab : uniqueLabels)
		{
			LR& r = roiData[lab];
			if (size_t roiFootprint = r.get_ram_footprint_estimate(), 
				ramLim = theEnvironment.get_ram_limit(); 
				roiFootprint >= ramLim)
			{
				unprocessed_rois.push_back(lab);
			}
			else
				trivRoiLabels.push_back(lab);
		}

		// Phase 2: process trivial-sized ROIs
		if (trivRoiLabels.size())
		{
			processTrivialRoisInMemory (trivRoiLabels, intens, label, filepair_index, theEnvironment.get_ram_limit());
		}

		// Phase 3: skip nontrivial ROIs

		return true;
	}
#endif
	int processDataset(
		const std::vector<std::string>& intensFiles,
		const std::vector<std::string>& labelFiles,
		int numFastloaderThreads,
		int numSensemakerThreads,
		int numReduceThreads,
		int min_online_roi_size,
		const SaveOption saveOption,
		const std::string& outputPath)
	{

		#ifdef CHECKTIMING
		if (Stopwatch::inclusive())
			Stopwatch::reset();
		#endif		
		
		// One-time initialization
		init_feature_buffers();

		bool write_apache = (saveOption == SaveOption::saveArrowIPC || saveOption == SaveOption::saveParquet);

		// initialize arrow writer if needed
		if (write_apache) {

			theEnvironment.arrow_stream = ArrowOutputStream(); 
			auto [status, msg] = theEnvironment.arrow_stream.create_arrow_file(saveOption, get_arrow_filename(outputPath, theEnvironment.nyxus_result_fname, saveOption), Nyxus::get_header(theFeatureSet.getEnabledFeatures()));
			
			if (!status) {
				std::cout << "Error creating Arrow file: " << msg.value() << std::endl;
				return 1;
			}
		}


		bool ok = true;

		// Iterate file pattern-filtered images of the dataset
		size_t nf = intensFiles.size();
		for (size_t i = 0; i < nf; i++)
		{
#ifdef CHECKTIMING
			if (Stopwatch::exclusive())
				Stopwatch::reset();
#endif

			// Clear ROI data cached for the previous image
			clear_feature_buffers();

			auto& ifp = intensFiles[i],
				& lfp = labelFiles[i];

			// Cache the file names to be picked up by labels to know their file origin
			fs::path p_int(ifp), p_seg(lfp);
			theSegFname = p_seg.string();
			theIntFname = p_int.string();

			// Scan one label-intensity pair 
			ok = theImLoader.open(theIntFname, theSegFname);
			if (ok == false)
			{
				std::cout << "Terminating\n";
				return 1;
			}

			// Do phased processing: prescan, trivial ROI processing, oversized ROI processing
			ok = processIntSegImagePair(ifp, lfp, numFastloaderThreads, i, nf);
			if (ok == false)
			{
				std::cout << "processIntSegImagePair() returned an error code while processing file pair " << ifp << " and " << lfp << std::endl;
				return 1;
			}

			if (write_apache) {

				auto [status, msg] = theEnvironment.arrow_stream.write_arrow_file(Nyxus::get_feature_values());
				
				if (!status) {
					std::cout << "Error writing Arrow file: " << msg.value() << std::endl;
					return 2;
				}
			} else if (saveOption == SaveOption::saveCSV) {
				ok = save_features_2_csv(ifp, lfp, outputPath);

				if (ok == false)
				{
					std::cout << "save_features_2_csv() returned an error code" << std::endl;
					return 2;
				}
			} else {
				ok = save_features_2_buffer(theResultsCache);

				if (ok == false)
				{
					std::cout << "save_features_2_buffer() returned an error code" << std::endl;
					return 2;
				}
			}

			theImLoader.close();

			// Save nested ROI related info of this image
			if (theEnvironment.nestedOptions.defined())
				save_nested_roi_info(nestedRoiData, uniqueLabels, roiData);

			#ifdef WITH_PYTHON_H
			// Allow heyboard interrupt.
			if (PyErr_CheckSignals() != 0)
			{
				sureprint("\nAborting per user input\n");
				throw pybind11::error_already_set();
			}
			#endif

			#ifdef CHECKTIMING
			if (Stopwatch::exclusive())
			{
				// Detailed timing - on the screen
				VERBOSLVL1(Stopwatch::print_stats());

				// Details - also to a file
				VERBOSLVL3(
					fs::path p(theSegFname);
					Stopwatch::save_stats(theEnvironment.output_dir + "/" + p.stem().string() + "_nyxustiming.csv");
				);
			}
			#endif
		}

		#ifdef CHECKTIMING
		if (Stopwatch::inclusive())
		{
			// Detailed timing - on the screen
			VERBOSLVL1(Stopwatch::print_stats());

			// Details - also to a file
			VERBOSLVL3(
				fs::path p(theSegFname);
				Stopwatch::save_stats(theEnvironment.output_dir + "/inclusive_nyxustiming.csv");
			);
		}
		#endif

		if (write_apache) {
			// close arrow file after use
			auto [status, msg] = theEnvironment.arrow_stream.close_arrow_file();
			if (!status) {
				std::cout << "Error closing Arrow file: " << msg.value() << std::endl;
					return 2;
			}
		}
	
		return 0; // success
	}

#ifdef WITH_PYTHON_H
	
	int processMontage(
		const py::array_t<unsigned int, py::array::c_style | py::array::forcecast>& intensity_images,
		const py::array_t<unsigned int, py::array::c_style | py::array::forcecast>& label_images,
		int numReduceThreads,
		const std::vector<std::string>& intensity_names,
		const std::vector<std::string>& seg_names,
		std::string& error_message,
		const SaveOption saveOption,
		const std::string& outputPath)
	{	
		bool write_apache = (saveOption == SaveOption::saveArrowIPC || saveOption == SaveOption::saveParquet);

		if (write_apache) {

			theEnvironment.arrow_stream = ArrowOutputStream();
			auto [status, msg] = theEnvironment.arrow_stream.create_arrow_file(saveOption, get_arrow_filename(outputPath, theEnvironment.nyxus_result_fname, saveOption), Nyxus::get_header(theFeatureSet.getEnabledFeatures()));
			if (!status) {
				std::cout << "Error creating Arrow file: " << msg.value() << std::endl;
				return 1;
			}
		}

		auto intens_buffer = intensity_images.request();
		auto label_buffer = label_images.request();

		auto width = intens_buffer.shape[1];
		auto height = intens_buffer.shape[2];

		size_t nf = intens_buffer.shape[0];
		
		for (size_t i = 0; i < nf; i++)
		{
			// Clear ROI label list, ROI data, etc.
			clear_feature_buffers();

			auto image_idx = i * width * height;

			std::vector<int> unprocessed_rois;
			auto ok = processIntSegImagePairInMemory (intensity_images, label_images, image_idx, intensity_names[i], seg_names[i], unprocessed_rois);		// Phased processing
			if (ok == false)
			{
				error_message = "processIntSegImagePairInMemory() returned an error code while processing file pair";
				return 1;
			}
			

			if (write_apache) {
			
				auto [status, msg] = theEnvironment.arrow_stream.write_arrow_file(Nyxus::get_feature_values());
				if (!status) {
					std::cout << "Error writing Arrow file: " << msg.value() << std::endl;
					return 2;
				}
			} else {

				ok = save_features_2_buffer(theResultsCache);

				if (ok == false)
				{
					error_message = "save_features_2_buffer() failed";
					return 2;
				}

			}

			if (unprocessed_rois.size() > 0) {
				error_message = "The following ROIS are oversized and cannot be processed: ";
				for (const auto& roi: unprocessed_rois){
					error_message += roi;
					error_message += ", ";
				}
				
				// remove trailing space and comma
				error_message.pop_back();
				error_message.pop_back();
			}

			// Allow heyboard interrupt.
			if (PyErr_CheckSignals() != 0)
                		throw pybind11::error_already_set();
		}


		if (write_apache) {
			// close arrow file after use
			auto [status, msg] = theEnvironment.arrow_stream.close_arrow_file();
			if (!status) {
				std::cout << "Error closing Arrow file: " << msg.value() << std::endl;
				return 2;
			}
		}
		return 0; // success
	}
#endif

	void dump_roi_metrics(const std::string & label_fpath)
	{
		fs::path pseg (label_fpath);
		std::string fpath = theEnvironment.output_dir + "/roi_metrics_" + pseg.stem().string() + ".csv";
		std::cout << "Dumping ROI metrics to " << fpath << " ...\n";

		std::ofstream f (fpath);

		// header
		f << "label, area, minx, miny, maxx, maxy, width, height, min_intens, max_intens, size_bytes, size_class \n";
		// sort labels
		std::vector<int>  sortedLabs { uniqueLabels.begin(), uniqueLabels.end() };
		std::sort(sortedLabs.begin(), sortedLabs.end());
		// body
		for (auto lab : sortedLabs)
		{
			LR& r = roiData[lab];
			auto szb = r.get_ram_footprint_estimate();
			std::string ovsz = szb < theEnvironment.get_ram_limit() ? "TRIVIAL" : "OVERSIZE";
			f << lab << ", "
				<< r.aux_area << ", "
				<< r.aabb.get_xmin() << ", "
				<< r.aabb.get_ymin() << ", "
				<< r.aabb.get_xmax() << ", "
				<< r.aabb.get_ymax() << ", "
				<< r.aabb.get_width() << ", "
				<< r.aabb.get_height() << ", "
				<< r.aux_min << ", "
				<< r.aux_max << ", "
				<< szb << ", "
				<< ovsz << ", ";
			f << "\n";
		}

		f.flush();
		std::cout << "... done\n";
	}

} 