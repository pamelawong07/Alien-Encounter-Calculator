# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\appencounter_calculator_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\appencounter_calculator_autogen.dir\\ParseCache.txt"
  "appencounter_calculator_autogen"
  )
endif()
