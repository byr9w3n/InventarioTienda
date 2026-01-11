# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\InventarioTienda_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\InventarioTienda_autogen.dir\\ParseCache.txt"
  "InventarioTienda_autogen"
  )
endif()
