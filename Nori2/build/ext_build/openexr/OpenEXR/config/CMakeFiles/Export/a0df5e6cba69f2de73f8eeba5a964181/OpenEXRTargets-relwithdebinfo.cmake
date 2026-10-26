#----------------------------------------------------------------
# Generated CMake target import file for configuration "RelWithDebInfo".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "OpenEXR::IlmImf" for configuration "RelWithDebInfo"
set_property(TARGET OpenEXR::IlmImf APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(OpenEXR::IlmImf PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELWITHDEBINFO "CXX"
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/lib/IlmImf-2_5.lib"
  )

list(APPEND _cmake_import_check_targets OpenEXR::IlmImf )
list(APPEND _cmake_import_check_files_for_OpenEXR::IlmImf "${_IMPORT_PREFIX}/lib/IlmImf-2_5.lib" )

# Import target "OpenEXR::zlibstatic" for configuration "RelWithDebInfo"
set_property(TARGET OpenEXR::zlibstatic APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(OpenEXR::zlibstatic PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELWITHDEBINFO "C"
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/lib/zlibstatic.lib"
  )

list(APPEND _cmake_import_check_targets OpenEXR::zlibstatic )
list(APPEND _cmake_import_check_files_for_OpenEXR::zlibstatic "${_IMPORT_PREFIX}/lib/zlibstatic.lib" )

# Import target "OpenEXR::IlmImfUtil" for configuration "RelWithDebInfo"
set_property(TARGET OpenEXR::IlmImfUtil APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(OpenEXR::IlmImfUtil PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELWITHDEBINFO "CXX"
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/lib/IlmImfUtil-2_5.lib"
  )

list(APPEND _cmake_import_check_targets OpenEXR::IlmImfUtil )
list(APPEND _cmake_import_check_files_for_OpenEXR::IlmImfUtil "${_IMPORT_PREFIX}/lib/IlmImfUtil-2_5.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
