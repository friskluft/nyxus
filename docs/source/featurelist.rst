
Nyxus-provided features
=======================

**2D intensity features:**

.. list-table::
   :header-rows: 1

   * - Nyxus feature code
     - Description
   * - INTEGRATED_INTENSITY
     - Integrated intensity of the region of interest (ROI)
   * - MEAN
     - Mean intensity value of the ROI
   * - MEDIAN
     - The median value of pixels in the ROI
   * - MIN
     - Minimum intensity value in the ROI
   * - MAX
     - Maximum intensity value in the ROI
   * - RANGE
     - Range between the maximmu and minimum
   * - COVERED_IMAGE_INTENSITY_RANGE
     - intensity range of the ROI to intensity range of all the ROIs
   * - STANDARD_DEVIATION
     - Standard deviation (unbiased)
   * - STANDARD_DEVIATION_BIASED
     - Biased standard deviation
   * - COV
     - Coefficient of variation
   * - STANDARD_ERROR
     - Standard error
   * - SKEWNESS
     - Skewness - the 3rd standardized moment
   * - KURTOSIS
     - Kurtosis - the 4th standardized moment (Pearson formula)
   * - EXCESS_KURTOSIS
     - Excess kurtosis - the 4th standardized moment (Fisher-corrected formula, IBSI feature IPH6)
   * - HYPERSKEWNESS
     - Hyperskewness - the 5th standardized moment
   * - HYPERFLATNESS
     - Hyperflatness - the 6th standardized moment
   * - MEAN_ABSOLUTE_DEVIATION
     - Mean absolute deviation
   * - MEDIAN_ABSOLUTE_DEVIATION
     - Median absolute deviation
   * - ENERGY
     - ROI energy
   * - ROOT_MEAN_SQUARED
     - Root of mean squared deviation
   * - ENTROPY
     - ROI entropy - a measure of the amount of information (that is, randomness) in the ROI
   * - MODE
     - The mode value of pixels in the ROI - the value that appears most often in a set of ROI intensity values
   * - UNIFORMITY
     - Uniformity - measures how uniform the distribution of ROI intensities is
   * - UNIFORMITY_PIU
     - Percent image uniformity, another measure of intensity distribution uniformity
   * - P01, P10, P25, P75, P90, P99
     - 1%, 10%, 25%, 75%, 90%, and 99% percentiles of intensity distribution
   * - QCOD 
     - quartile coefficient of dispersion
   * - INTERQUARTILE_RANGE
     - Distribution's interquartile range
   * - ROBUST_MEAN_ABSOLUTE_DEVIATION
     - Robust mean absolute deviation
   * - MASS_DISPLACEMENT
     - ROI mass displacement


**2D morphology features:**


.. list-table::
   :header-rows: 1

   * - Nyxus feature code
     - Description
   * - AREA_PIXELS_COUNT
     - ROI area in the number of pixels
   * - AREA_UM2
     - ROI area in metric units
   * - CENTROID_X
     - X-coordinate of the enter point of the ROI
   * - CENTROID_Y
     - Y-coordinate of the center point of the ROI
   * - COMPACTNESS
     - Mean squared distance of the object’s pixels from the centroid divided by the area. Compactness of a filled circle is 1, compactness of irregular objects or objects with holes is greater than 1
   * - BBOX_YMIN
     - Y-position and size of the smallest axis-aligned box containing the ROI
   * - BBOX_XMIN
     - X-position and size of the smallest axis-aligned box containing the ROI
   * - BBOX_HEIGHT
     - Height of the smallest axis-aligned box containing the ROI
   * - BBOX_WIDTH
     - Width of the smallest axis-aligned box containing the ROI
   * - MAJOR_AXIS_LENGTH
     - Length (in pixels) of the major axis of the ellipse that has the same normalized second central moments as the region
   * - MINOR_AXIS_LENGTH
     - Length (in pixels) of the minor axis of the ellipse that has the same normalized second central moments as the region
   * - ECCENTRICITY
     - Ratio of ROI's inertia ellipse focal distance over the major axis length
   * - ORIENTATION
     - Angle between the 0th axis and the major axis of the ellipse that has same second moments as the region
   * - ROUNDNESS
     - Represents how similar a ROI's inertia ellipse is to circle. Calculated based on the major and minor exis lengths
   * - EXTENT
     - Proportion of the pixels (2D) or voxels (3D) in the bounding box that are also in the region. Computed as the area/volume of the object divided by the area/volume of the bounding box
   * - ASPECT_RATIO
     - The ratio of the major axis to the minor axis of ROI's inertia ellipse
   * - CONVEX_HULL_AREA
     - Area of ROI's convex hull
   * - SOLIDITY
     - Ratio of pixels in the ROI common with its convex hull image
   * - PERIMETER
     - Number of pixels in ROI's contour
   * - EQUIVALENT_DIAMETER
     - Diameter of a circle with the same area as the ROI
   * - EDGE_MEAN_INTENSITY
     - Mean intensity of ROI's contour pixels
   * - EDGE_STDDEV_INTENSITY
     - Standard deviation of ROI's contour pixels
   * - EDGE_MAX_INTENSITY
     - Maximum intensity of ROI's contour pixels
   * - EDGE_MIN_INTENSITY
     - Minimum intensity of ROI's contour pixels
   * - CIRCULARITY
     - Represents how similar a shape is to circle. Clculated based on ROI's area and its convex perimeter
   * - EROSIONS_2_VANISH
     - Number of erosion operations for a ROI to vanish in its axis aligned bounding box
   * - EROSIONS_2_VANISH_COMPLEMENT
     - Number of erosion operations for a ROI to vanish in its convex hull
   * - FRACT_DIM_BOXCOUNT
     - Fractal dimension determined by the box counting method according to ISO 9276-6. If C is a fractal set, with fractal dimension DF < D, then the number N of boxes of size R needed to cover the set scales as R^(-DF). DF is known as the Hausdorf dimension, or Kolmogorov capacity, or Kolmogorov dimension, or simply box-counting dimension
   * - FRACT_DIM_PERIMETER
     - Fractal dimension determined by the perimeter method according to ISO 9276-6. If we approximate ROI's contour with rulers of length lambda, the perimeter based fractal dimension is the slope of the best fit line of log ROI perimeter versus log lambda, subtracted from 1
   * - WEIGHTED_CENTROID_Y
     - X-coordinate of centroid
   * - WEIGHTED_CENTROID_X
     - Y-coordinate of centroid
   * - MIN_FERET_DIAMETER
     - Feret diameter (or maximum caliber diameter) is the longest distance between any two ROI points along the same (horizontal) direction. This feature is the minimum Feret diameter for angles ranging 0 to 180 degrees
   * - MAX_FERET_DIAMETER
     - Maximum Feret diameter for angles ranging 0 to 180 degrees
   * - MIN_FERET_ANGLE
     - Angle of the minimum Feret diameter
   * - MAX_FERET_ANGLE
     - Angle of the maximum Feret diameter
   * - STAT_FERET_DIAM_MIN
     - Minimum of Feret diameters of the ROI rotated at angles 0-180 degrees
   * - STAT_FERET_DIAM_MAX
     - Maximum of Feret diameters of the ROI rotated at angles 0-180 degrees
   * - STAT_FERET_DIAM_MEAN
     - Mean Feret diameter of the ROI rotated at angles 0-180 degrees
   * - STAT_FERET_DIAM_MEDIAN
     - Median value of Feret diameters of the ROI rotated at angles 0-180 degrees
   * - STAT_FERET_DIAM_STDDEV
     - Standard deviation of Feret diameter of the ROI rotated at angles 0-180 degrees
   * - STAT_FERET_DIAM_MODE
     - Histogram mode of Feret diameters of the ROI rotated at angles 0-180 degrees
   * - STAT_MARTIN_DIAM_MIN
     - Minimum of Martin diameters of the ROI rotated at angles 0-180 degrees
   * - STAT_MARTIN_DIAM_MAX
     - Maximum of Martin diameters of the ROI rotated at angles 0-180 degrees
   * - STAT_MARTIN_DIAM_MEAN
     - Mean of Martin diameter of the ROI rotated at angles 0-180 degrees
   * - STAT_MARTIN_DIAM_MEDIAN
     - Median value of Martin diameters of the ROI rotated at angles 0-180 degrees
   * - STAT_MARTIN_DIAM_STDDEV
     - Standard deviation of Martin diameter of the ROI rotated at angles 0-180 degrees
   * - STAT_MARTIN_DIAM_MODE
     - Histogram mode of Martin diameters of the ROI rotated at angles 0-180 degrees
   * - STAT_NASSENSTEIN_DIAM_MIN
     - Minimum of Nassenstein diameters of the ROI rotated at angles 0-180 degrees
   * - STAT_NASSENSTEIN_DIAM_MAX
     - Maximum of Nassenstein diameters of the ROI rotated at angles 0-180 degrees
   * - STAT_NASSENSTEIN_DIAM_MEAN
     - Mean of Nassenstein diameter of the ROI rotated at angles 0-180 degrees
   * - STAT_NASSENSTEIN_DIAM_MEDIAN
     - Median value of Nassenstein diameters of the ROI rotated at angles 0-180 degrees
   * - STAT_NASSENSTEIN_DIAM_STDDEV
     - Standard deviation of Nassenstein diameter of the ROI rotated at angles 0-180 degrees
   * - STAT_NASSENSTEIN_DIAM_MODE
     - Histogram mode of Nassenstein diameters of the ROI rotated at angles 0-180 degrees
   * - MAXCHORDS_MAX
     - Maximum of ROI's longest chords built at angles 0-180 degrees
   * - MAXCHORDS_MAX_ANG
     - Angle of the chord referenced in MAXCHORDS_MAX
   * - MAXCHORDS_MIN
     - Minimum of ROI's longest chords built at angles 0-180 degrees
   * - MAXCHORDS_MIN_ANG
     - Angle of the chord referenced in MAXCHORDS_MIN
   * - MAXCHORDS_MEDIAN
     - Median value of ROI's longest chords built at angles 0-180 degrees
   * - MAXCHORDS_MEAN
     - Mean value of ROI's longest chords built at angles 0-180 degrees
   * - MAXCHORDS_MODE
     - Histogram mode of ROI's longest chords built at angles 0-180 degrees
   * - MAXCHORDS_STDDEV
     - Sndard deviation of ROI's longest chords built at angles 0-180 degrees
   * - ALLCHORDS_MAX
     - Maximum of all the ROI's chords built at angles 0-180 degrees
   * - ALLCHORDS_MAX_ANG
     - Angle of the chord referenced in ALLCHORDS_MAX
   * - ALLCHORDS_MIN
     - Minimum of all the ROI's chords built at angles 0-180 degrees
   * - ALLCHORDS_MIN_ANG
     - Angle of the chord referenced in ALLCHORDS_MIN
   * - ALLCHORDS_MEDIAN
     - Median value of all the ROI's chords built at angles 0-180 degrees
   * - ALLCHORDS_MEAN
     - Mean value of all the ROI's chords built at angles 0-180 degrees
   * - ALLCHORDS_MODE
     - Histogram mode of all the ROI's chords built at angles 0-180 degrees
   * - ALLCHORDS_STDDEV
     - Sndard deviation of all the ROI's chords built at angles 0-180 degrees
   * - EULER_NUMBER
     - Euler characteristic of the ROI - the number of objects in the ROI minus the number of holes assuming the 8-neighbor connectivity of ROI's pixels
   * - EXTREMA_P1_X
     - X-ccordinate of ROI's axis aligned bounding box extremum point #1
   * - EXTREMA_P1_Y
     - Y-ccordinate of ROI's axis aligned bounding box extremum point #1
   * - EXTREMA_P2_X
     - X-ccordinate of ROI's axis aligned bounding box extremum point #2
   * - EXTREMA_P2_Y
     - 
   * - EXTREMA_P3_X
     - X-ccordinate of ROI's axis aligned bounding box extremum point #3
   * - EXTREMA_P3_Y
     - 
   * - EXTREMA_P4_X
     - X-ccordinate of ROI's axis aligned bounding box extremum point #4
   * - EXTREMA_P4_Y
     - 
   * - EXTREMA_P5_X
     - X-ccordinate of ROI's axis aligned bounding box extremum point #5
   * - EXTREMA_P5_Y
     - 
   * - EXTREMA_P6_X
     - X-ccordinate of ROI's axis aligned bounding box extremum point #6
   * - EXTREMA_P6_Y
     - 
   * - EXTREMA_P7_X
     - X-ccordinate of ROI's axis aligned bounding box extremum point #7
   * - EXTREMA_P7_Y
     - 
   * - EXTREMA_P8_X
     - X-ccordinate of ROI's axis aligned bounding box extremum point #8
   * - EXTREMA_P8_Y
     - 
   * - POLYGONALITY_AVE
     - The score ranges from $ -\infty $ to 10. Score 10 indicates the object shape is polygon and score $ -\infty $ indicates the ROI shape is not polygon
   * - HEXAGONALITY_AVE
     - The score ranges from $ -\infty $ to 10. Score 10 indicates the object shape is hexagon and score $ -\infty $ indicates the ROI shape is not hexagon
   * - HEXAGONALITY_STDDEV
     - Standard deviation of hexagonality_score relative to its mean
   * - DIAMETER_MIN_ENCLOSING_CIRCLE
     - Diameter of the minimum enclosing circle
   * - DIAMETER_CIRCUMSCRIBING_CIRCLE
     - Diameter of the circumscribing circle
   * - DIAMETER_INSCRIBING_CIRCLE
     - Diameter of inscribing circle
   * - GEODETIC_LENGTH
     - Geodetic length approximated by a rectangle with the same area and perimeter: $ area = geodeticlength * thickness$; $perimeter = 2 * (geodetic_length + thickness) $
   * - THICKNESS
     - Thickness approximated by a rectangle with the same area and perimeter: $ area = geodeticlength * thickness$; $perimeter = 2 * (geodetic_length + thickness) $
   * - ROI_RADIUS_MEAN
     - Mean centroid to edge distance
   * - ROI_RADIUS_MAX
     - Maximum of centroid to edge distances
   * - ROI_RADIUS_MEDIAN
     - Median value of centroid to edge distances


**2D texture features:**


.. list-table::
   :header-rows: 1

   * - Nyxus feature code
     - Description
   * - GLCM_ASM
     - GLCM, Angular second moment, IBSI # 8ZQL
   * - GLCM_ACOR
     - GLCM, Autocorrelation, IBSI # QWB0
   * - GLCM_CLUPROM
     - GLCM, Cluster prominence, IBSI # AE86
   * - GLCM_CLUSHADE
     - GLCM, Cluster shade, IBSI # 7NFM
   * - GLCM_CLUTEND
     - GLCM, Cluster tendency, IBSI # DG8W
   * - GLCM_CONTRAST
     - GLCM, Contrast, IBSI # ACUI
   * - GLCM_CORRELATION
     - GLCM, Correlation, IBSI # NI2N
   * - GLCM_DIFAVE
     - GLCM, Difference average, IBSI # TF7R
   * - GLCM_DIFENTRO
     - GLCM, Difference entropy, IBSI # NTRS
   * - GLCM_DIFVAR
     - GLCM, Difference variance, IBSI # D3YU
   * - GLCM_DIS
     - GLCM, Dissimilarity, IBSI # 8S9J
   * - GLCM_ENERGY
     - GLCM, Energy
   * - GLCM_ENTROPY
     - GLCM, Entropy
   * - GLCM_HOM1
     - GLCM, Homogeneity-1
   * - GLCM_HOM2
     - GLCM, Homogeneity-2
   * - GLCM_ID
     - GLCM, Inverse difference, IBSI # IB1Z
   * - GLCM_IDN
     - GLCM, Inverse difference normalized, IBSI # NDRX
   * - GLCM_IDM
     - GLCM, Inverse difference moment, IBSI # WF0Z
   * - GLCM_IDMN
     - GLCM, Inverse difference moment normalized, IBSI # 1QCO
   * - GLCM_INFOMEAS1
     - GLCM, Information measure of correlation 1, IBSI # R8DG
   * - GLCM_INFOMEAS2
     - GLCM, Information measure of correlation 2, IBSI # JN9H
   * - GLCM_IV
     - GLCM, Inverse variance, IBSI # E8JP
   * - GLCM_JAVE
     - GLCM, Joint average, IBSI # 60VM
   * - GLCM_JE
     - GLCM, Joint entropy, IBSI # TU9B
   * - GLCM_JMAX
     - GLCM, Joint maximum (aka max probability), IBSI # GYBY
   * - GLCM_JVAR
     - GLCM, Joint variance (aka sum of squares), IBSI # UR99
   * - GLCM_SUMAVERAGE
     - GLCM, Sum average, IBSI # ZGXS
   * - GLCM_SUMENTROPY
     - GLCM, Sum entropy, IBSI # P6QZ
   * - GLCM_SUMVARIANCE
     - GLCM, Sum variance, IBSI # OEEB
   * - GLCM_VARIANCE
     - GLCM, Variance
   * - GLRLM_SRE
     - Grey level run-length matrix (GLRLM) based feature, Short Run Emphasis 
   * - GLRLM_LRE
     - GLRLM, Long Run Emphasis 
   * - GLRLM_GLN
     - GLRLM, Grey Level Non-Uniformity 
   * - GLRLM_GLNN
     - GLRLM, Grey Level Non-Uniformity Normalized 
   * - GLRLM_RLN
     - GLRLM, Run Length Non-Uniformity
   * - GLRLM_RLNN
     - GLRLM, Run Length Non-Uniformity Normalized 
   * - GLRLM_RP
     - GLRLM, Run Percentage
   * - GLRLM_GLV
     - GLRLM, Grey Level Variance 
   * - GLRLM_RV
     - GLRLM, Run Variance 
   * - GLRLM_RE
     - GLRLM, Run Entropy 
   * - GLRLM_LGLRE
     - GLRLM, Low Grey Level Run Emphasis 
   * - GLRLM_HGLRE
     - GLRLM, High Grey Level Run Emphasis 
   * - GLRLM_SRLGLE
     - GLRLM, Short Run Low Grey Level Emphasis 
   * - GLRLM_SRHGLE
     - GLRLM, Short Run High Grey Level Emphasis 
   * - GLRLM_LRLGLE
     - GLRLM, Long Run Low Grey Level Emphasis 
   * - GLRLM_LRHGLE
     - GLRLM, Long Run High Grey Level Emphasis 
   * - GLDZM_SDE
     - GLDZM, Small Distance Emphasis
   * - GLDZM_LDE
     - GLDZM, Large Distance Emphasis
   * - GLDZM_LGLE
     - GLDZM, Low Grey Level Emphasis
   * - GLDZM_HGLE
     - GLDZM, High GreyLevel Emphasis
   * - GLDZM_SDLGLE
     - GLDZM, Small Distance Low Grey Level Emphasis
   * - GLDZM_SDHGLE
     - GLDZM, Small Distance High GreyLevel Emphasis
   * - GLDZM_LDLGLE
     - GLDZM, Large Distance Low Grey Level Emphasis
   * - GLDZM_LDHGLE
     - GLDZM, Large Distance High Grey Level Emphasis
   * - GLDZM_GLNU
     - GLDZM, Grey Level Non Uniformity
   * - GLDZM_GLNUN
     - GLDZM, Grey Level Non Uniformity Normalized
   * - GLDZM_ZDNU
     - GLDZM, Zone Distance Non Uniformity
   * - GLDZM_ZDNUN
     - GLDZM, Zone Distance Non Uniformity Normalized
   * - GLDZM_ZP
     - GLDZM, Zone Percentage
   * - GLDZM_GLM
     - GLDZM, Grey Level Mean
   * - GLDZM_GLV
     - GLDZM, Grey Level Variance
   * - GLDZM_ZDM
     - GLDZM, Zone Distance Mean
   * - GLDZM_ZDV
     - GLDZM, Zone Distance Variance
   * - GLDZM_ZDE
     - GLDZM, Zone Distance Entropy
   * - GLSZM_SAE
     - GLDZM, Grey level size zone matrix (GLSZM) based feature, Small Area Emphasis
   * - GLSZM_LAE
     - Large Area Emphasis
   * - GLSZM_GLN
     - Grey Level Non - Uniformity
   * - GLSZM_GLNN
     - Grey Level Non - Uniformity Normalized
   * - GLSZM_SZN
     - Size - Zone Non - Uniformity
   * - GLSZM_SZNN
     - Size - Zone Non - Uniformity Normalized
   * - GLSZM_ZP
     - Zone Percentage
   * - GLSZM_GLV
     - Grey Level Variance
   * - GLSZM_ZV
     - Zone Variance
   * - GLSZM_ZE
     - Zone Entropy
   * - GLSZM_LGLZE
     - Low Grey Level Zone Emphasis
   * - GLSZM_HGLZE
     - High Grey Level Zone Emphasis
   * - GLSZM_SALGLE
     - Small Area Low Grey Level Emphasis
   * - GLSZM_SAHGLE
     - Small Area High Grey Level Emphasis
   * - GLSZM_LALGLE
     - Large Area Low Grey Level Emphasis
   * - GLSZM_LAHGLE
     - Large Area High Grey Level Emphasis
   * - GLDM_SDE
     - Grey level dependency matrix (GLDM) based feature, Small Dependence Emphasis(SDE)
   * - GLDM_LDE
     - Large Dependence Emphasis (LDE)
   * - GLDM_GLN
     - Grey Level Non-Uniformity (GLN)
   * - GLDM_DN
     - Dependence Non-Uniformity (DN)
   * - GLDM_DNN
     - Dependence Non-Uniformity Normalized (DNN)
   * - GLDM_GLV
     - Grey Level Variance (GLV)
   * - GLDM_DV
     - Dependence Variance (DV)
   * - GLDM_DE
     - Dependence Entropy (DE)
   * - GLDM_LGLE
     - Low Grey Level Emphasis (LGLE)
   * - GLDM_HGLE
     - High Grey Level Emphasis (HGLE)
   * - GLDM_SDLGLE
     - Small Dependence Low Grey Level Emphasis (SDLGLE)
   * - GLDM_SDHGLE
     - Small Dependence High Grey Level Emphasis (SDHGLE)
   * - GLDM_LDLGLE
     - Large Dependence Low Grey Level Emphasis (LDLGLE)
   * - GLDM_LDHGLE
     - Large Dependence High Grey Level Emphasis (LDHGLE)

   * - NGLDM_LDE
     - Low Dependence Emphasis
   * - NGLDM_HDE
     - High Dependence Emphasis
   * - NGLDM_LGLCE
     - Low Grey Level Count Emphasis
   * - NGLDM_HGLCE
     - High Grey Level Count Emphasis
   * - NGLDM_LDLGLE
     - Low Dependence Low Grey Level Emphasis
   * - NGLDM_LDHGLE
     - Low Dependence High Grey Level Emphasis
   * - NGLDM_HDLGLE
     - High Dependence Low Grey Level Emphasis
   * - NGLDM_HDHGLE
     - High Dependence High Grey Level Emphasis
   * - NGLDM_GLNU
     - Grey Level Non-Uniformity
   * - NGLDM_GLNUN
     - Grey Level Non-Uniformity Normalised
   * - NGLDM_DCNU
     - Dependence Count Non-Uniformity
   * - NGLDM_DCNUN
     - Dependence Count Non-Uniformity Normalised
   * - NGLDM_GLM
     - Grey Level Mean
   * - NGLDM_GLV
     - Grey Level Variance
   * - NGLDM_DCM
     - Dependence Count Mean
   * - NGLDM_DCV
     - Dependence Count Variance
   * - NGLDM_DCE
     - Dependence Count Entropy
   * - NGLDM_DCENE
     - Dependence Count Energy

   * - NGTDM_COARSENESS
     - Neighbouring Grey Tone Difference Matrix (NGTDM) Features, Coarseness
   * - NGTDM_CONTRAST
     - NGTDM, Contrast
   * - NGTDM_BUSYNESS
     - NGTDM, Busyness
   * - NGTDM_COMPLEXITY
     - NGTDM, Complexity
   * - NGTDM_STRENGTH
     - NGTDM, Strength


**2D radial intensity distribution features:**


.. list-table::
   :header-rows: 1

   * - Nyxus feature code
     - Description
   * - ZERNIKE2D
     - Zernike features
   * - FRAC_AT_D
     - Fraction of total intensity at a given radius
   * - MEAN_FRAC
     - Mean fractional intensity at a given radius
   * - RADIAL_CV
     - Coefficient of variation of intensity within a ring (band), calculated across $n$ slices


**2D frequency and orientational features:**


.. list-table::
   :header-rows: 1

   * - Nyxus feature code
     - Description
   * - GABOR
     - A set of Gabor filters of varying frequencies and orientations


**2D shape image moments (calculated with constant pixel intensity 1.0 within the ROI segment):**

.. list-table::
   :header-rows: 1

   * - Nyxus feature code
     - Description
   * - SPAT_MOMENT_<order>
     - Spatial (raw) moments of order 00, 01, 02, 03, 10, 11, 12, 20, 21, 30
   * - WEIGHTED_SPAT_MOMENT_<order>
     - Spatial moments weighted by pixel distance to ROI edge of order 00, 01, 02, 03, 10, 11, 20, 21, 30
   * - CENTRAL_MOMENT_<order>
     - Central moments of order 02, 03, 11, 12, 20, 21, 30
   * - WEIGHTED_CENTRAL_MOMENT_<order>
     - Central moments weighted by pixel distance to ROI edge of order 02, 03, 11, 12, 20, 21, 30
   * - NORM_CENTRAL_MOMENT_<order>
     - Normalized central moments of order 02, 03, 11, 12, 20, 21, 30
   * - NORM_SPAT_MOMENT_<order>
     - Normalized (standardized) spatial moments of order 00, 01, 02, 03, 10, 20, 30
   * - HU_M<1-7>
     - Hu's moments of order 1 to 7
   * - WEIGHTED_HU_M<1-7>
     - Weighted Hu's moment of order 1-7

**2D intensity image moments (calculated with respect to pixels' actual intensities within the ROI segment):**

.. list-table::
   :header-rows: 1

   * - Nyxus feature code
     - Description
   * - IMOM_RM_<order>
     - Spatial (raw) moments of order 00, 01, 02, 03, 10, 11, 12, 20, 21, 30
   * - IMOM_RM_01
     - of order 00, 01, 02, etc
   * - IMOM_WRM_<order>
     - Spatial moments weighted by pixel distance to ROI edge of order 00, 01, 02, 03, 10, 11, 12, 20, 21, 30
   * - IMOM_СM_<order>
     - Central moments of order 02, 03, 11, 12, 20, 21, 30 
   * - IMOM_WСM_<order>
     - Central moments weighted by pixel distance to ROI edge of order 02, 03, 11, 12, 20, 21, 30
   * - IMOM_NСM_<order>
     - Normalized central moments of order 02, 03, 11, 20, 21, 30
   * - IMOM_NRM_<order>
     - Normalized (standardized) spatial moments of order 00, 01, 02, 03, 10, 20, 30
   * - IMOM_HU<1-7>
     - Hu's moment 1-7
   * - IMOM_WHU<1-7>
     - Weighted Hu's moment 1-7


**2D neighbor features:**

.. list-table::
   :header-rows: 1

   * - Nyxus feature code
     - Description
   * - NUM_NEIGHBORS
     - The number of neighbors bordering the ROI's perimeter within proximity radius specified by command line argument --pixelDistance. (Default value of --pixelDistance is 5.) Algorithmically calculating this feature invilves solving the nearest neighbors search problem that in turn involves the proximity measure and the proximity threshold. Particularly, this plugin uses the :math:`L_2` norm measure over Cartesian space of pixel coordinates and parameter --pixelDistance 
   * - PERCENT_TOUCHING
     - Percent of ROI's contour pixels located at distance 0 from neighboring other ROIs's contour
   * - CLOSEST_NEIGHBOR1_DIST
     - Distance in pixels from ROI's centroid to the nearest neighboring ROI's centroid
   * - CLOSEST_NEIGHBOR1_ANG
     - Angle in degrees between ROI's centroid and its nearest neighboring ROI's centroid
   * - CLOSEST_NEIGHBOR2_DIST
     - Distance in pixels from ROI's centroid to the second nearest neighboring ROI's centroid
   * - CLOSEST_NEIGHBOR2_ANG
     - Angle in degrees between ROI's centroid and its second nearest neighboring ROI's centroid
   * - ANG_BW_NEIGHBORS_MEAN
     - Mean angle in degrees between ROI's centroid and centroids of its neighboring ROIs
   * - ANG_BW_NEIGHBORS_STDDEV
     - Standard deviation in degrees of angles between ROI's centroid and centroids of its neighboring ROIs
   * - ANG_BW_NEIGHBORS_MODE
     - Mode value in degrees of angles between ROI's centroid and centroids of its neighboring ROIs


**3D voxel intensity features:**

.. list-table::
   :header-rows: 1

   * - Nyxus feature code
     - Description
   * - 3COV
     - Coefficient of variation
   * - 3COVERED_IMAGE_INTENSITY_RANGE
     - intensity range of the ROI to intensity range of all the ROIs
   * - 3ENERGY
     - ROI energy
   * - 3ENTROPY
     - ROI entropy - a measure of the amount of information (that is, randomness) in the ROI
   * - 3EXCESS_KURTOSIS
     - measure of how ROI intensity distribution's tails deviate from those of a normal distribution
   * - 3HYPERFLATNESS
     - 6th standardized moment
   * - 3HYPERSKEWNESS
     - 5th standardized moment
   * - 3INTEGRATED_INTENSITY
     - total signal within the ROI
   * - 3INTERQUARTILE_RANGE
     - difference between the 75th and 25th percentiles
   * - 3KURTOSIS
     - 4th standardized moment
   * - 3MAX, 3MEAN, 3MEDIAN, 3MIN
     - minimum, mean, median, and minimum signal value within the ROI
   * - 3MEAN_ABSOLUTE_DEVIATION
     - measure of dispersion around the mean value
   * - 3MEDIAN_ABSOLUTE_DEVIATION
     - measure of dispersion around the median value
   * - 3MODE
     - mode value of voxels signal within the ROI (the most abundant signal value within the ROI)
   * - 3P01, 3P10, 3P25, 3P75, 3P90, 3P99
     - 1%, 10%, 25%, 75%, 90%, and 99% percentiles of intensity distribution
   * - 3QCOD 
     - quartile coefficient of dispersion - measure of statistical dispersion that focuses on the middle 50% of the data, making it robust to outliers
   * - 3RANGE
     - range between the 3MAX and 3MIN
   * - 3ROBUST_MEAN
     - the mean calculated after discarding outliers
   * - 3ROBUST_MEAN_ABSOLUTE_DEVIATION
     - the mean absolute deviation calculated after discarding outliers
   * - 3ROOT_MEAN_SQUARED
     - root of mean squared deviation
   * - 3SKEWNESS
     - 3rd standardized moment
   * - 3STANDARD_DEVIATION
     - standard deviation (unbiased)
   * - 3STANDARD_DEVIATION_BIASED
     - biased standard deviation
   * - 3STANDARD_ERROR
     - standard error
   * - 3UNIFORMITY
     - measure of how uniform the distribution of ROI intensities is
   * - 3UNIFORMITY_PIU
     - the uniformity expressed in the units of percent image uniformity (PIU)
   * - 3VARIANCE
     - variance
   * - 3VARIANCE_BIASED
     - variance calculated with respect to biased sample mean


**3D shape features:**

.. list-table::
   :header-rows: 1

   * - Nyxus feature code
     - Description
   * - 3AREA
     - total of areas of surface faces
   * - 3AREA_2_VOLUME
     - ratio of the surface area to the voxel volume (lower values correspond to more sphere-like ROIs)
   * - 3COMPACTNESS1
     - measure of how compact the shape of the ROI is to a sphere
   * - 3COMPACTNESS2
     - another measure of how compact the shape of the ROI is to a sphere
   * - 3MESH_VOLUME
     - volume of the triangle mesh of the ROI
   * - 3SPHERICAL_DISPROPORTION
     - ratio of ROI's surface area to the surface area of a sphere of the same volume as the ROI (value of 1 corresponds to a perfect square)
   * - 3SPHERICITY
     - measure of the ROI shape's roundness relative to a sphere (value of 1 is a perfect sphere)
   * - 3VOLUME_CONVEXHULL
     - volume of the triangle mesh of ROI's convex hull
   * - 3VOXEL_VOLUME
     - total of volumes of voxels of the ROI


**3D texture features:**

.. list-table::
   :header-rows: 1

   * - Nyxus feature code
     - Description
   * - 3GLCM_<name>
     - 3-dimensional version of the GLCM feature (name = ACOR, ASM, CLUPROM, CLUSHADE, CLUTEND, CONTRAST, CORRELATION, DIFAVE, DIFENTRO, DIFVAR, DIS, ID, IDN, IDM, IDMN, INFOMEAS1, INFOMEAS2, IV, JAVE, JE, JMAX, JVAR, SUMAVERAGE, SUMENTROPY, or SUMVARIANCE)
   * - 3GLDM_<name>
     - 3-dimensional version of the GLDM feature (name = SDE, LDE, LGLE, HGLE, SDLGLE, SDHGLE, LDLGLE, LDHGLE, GLN, DN, DNN, GLV, DV, or DE)
   * - 3GLDZM_<name>
     - 3-dimensional version of the GLDZM feature (name = SDE, LDE, LGLZE, HGLZE, SDLGLE, SDHGLE, LDLGLE, LDHGLE, GLNU, GLNUN, ZDNU, ZDNUN, ZP, GLM, GLV, ZDM, ZDV, or ZDE)
   * - 3GLRLM_<name>
     - 3-dimensional version of the GLRLM feature (name = SRE, LRE, LGLRE, HGLRE, SRLGLE, SRHGLE, LRLGLE, LRHGLE, GLN, GLNN, RLN, RLNN, RP, GLV, RV, or RE)
   * - 3GLSZM_<name>
     - 3-dimensional version of the GLSZM feature (name = SAE, LAE, LGLZE, HGLZE, SALGLE, SAHGLE, LALGLE, LAHGLE, GLN, GLNN, SZN, SZNN, ZP, GLV, ZV, or ZE)
   * - 3NGLDM_<name>
     - 3-dimensional version of the NGLDM feature (name = LDE, HDE, LGLCE, HGLCE, LDLGLE, LDHGLE, HDLGLE, HDHGLE, GLNU, GLNUN, DCNU, DCNUN, DCP, GLM, GLV, DCM, DCV, DCENT, or DCENE)
   * - 3NGTDM_<name>
     - 3-dimensional version of the NGTDM feature (name = COARSENESS, CONTRAST, BUSYNESS, COMPLEXITY, or STRENGTH)

