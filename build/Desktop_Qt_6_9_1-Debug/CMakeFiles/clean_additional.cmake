# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "BarnsleyFern_autogen"
  "CMakeFiles/BarnsleyFern_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/BarnsleyFern_autogen.dir/ParseCache.txt"
  )
endif()
