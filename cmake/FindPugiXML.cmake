#
# This module detects if pugixml is installed and determines where the
# include files and libraries are.
#
# This code sets the following variables:
# 
# PUGIXML_LIBRARIES   = full path to the pugixml libraries
# PUGIXML_INCLUDE_DIR = include dir to be used when using the pugixml library
# PUGIXML_FOUND       = set to true if pugixml was found successfully
#
# PUGIXML_LOCATION
#   setting this enables search for pugixml libraries / headers in this location


# -----------------------------------------------------
# PUGIXML Libraries
# -----------------------------------------------------
find_library(PUGIXML_LIBRARIES
    NAMES pugixml
    HINTS ${PUGIXML_LOCATION}/lib ${PUGIXML_LOCATION}/lib64 ${PUGIXML_LOCATION}/lib32
    DOC "The main pugixml library"
)
if(PUGIXML_LIBRARIES)
  message(STATUS "pugixml libraries found in ${PUGIXML_LIBRARIES}")
endif()

# -----------------------------------------------------
# PUGIXML Include Directories
# -----------------------------------------------------
find_path(PUGIXML_INCLUDE_DIR 
    NAMES pugixml.hpp
    HINTS ${PUGIXML_LOCATION} ${PUGIXML_LOCATION}/include ${PUGIXML_LOCATION}/include/* /usr/include
    DOC "The pugixml include directory"
)
if(PUGIXML_INCLUDE_DIR)
    message(STATUS "pugixml includes found in ${PUGIXML_INCLUDE_DIR}")
endif()

# -----------------------------------------------------
# handle the QUIETLY and REQUIRED arguments and set PUGIXML_FOUND to TRUE if 
# all listed variables are TRUE
# -----------------------------------------------------
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(pugixml DEFAULT_MSG PUGIXML_LIBRARIES PUGIXML_INCLUDE_DIR)
mark_as_advanced(PUGIXML_INCLUDE_DIR PUGIXML_LIBRARIES)
