# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\PersonalAssistant_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\PersonalAssistant_autogen.dir\\ParseCache.txt"
  "PersonalAssistant_autogen"
  )
endif()
