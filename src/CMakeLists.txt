add_executable(Forking-Benchmark forking_benchmark.cpp)
IF("${CMAKE_SYSTEM}" MATCHES "Linux")
  add_executable(Clone-Benchmark clone_benchmark.cpp)
ENDIF()
