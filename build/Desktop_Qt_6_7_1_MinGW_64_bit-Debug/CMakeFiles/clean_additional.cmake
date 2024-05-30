# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Qtify_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Qtify_autogen.dir\\ParseCache.txt"
  "Qtify_autogen"
  )
endif()
