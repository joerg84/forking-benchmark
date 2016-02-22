cmake_minimum_required (VERSION 2.6)
project (Templates)

################################
# GTest
################################
include(ExternalProject)
ExternalProject_Add(gtest
  URL https://googletest.googlecode.com/files/gtest-1.7.0.zip
  # Comment above line, and uncomment line below to use subversion.
  # SVN_REPOSITORY http://googletest.googlecode.com/svn/trunk/
  # Uncomment line below to freeze a revision (here the one for 1.7.0)
  # SVN_REVISION -r700

  PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
  INSTALL_COMMAND ""
)
ExternalProject_Get_Property(gtest source_dir binary_dir)


################################
# Unit Tests
################################
# Add test cpp file
add_executable( runUnitTests testfoo.cpp )

######################################
# Configure the test to use GoogleTest
add_dependencies(runUnitTests gtest)
include_directories(${source_dir}/include)
target_link_libraries(runUnitTests ${binary_dir}/libgtest.a)
target_link_libraries(runUnitTests ${binary_dir}/libgtest_main.a)

add_test(NAME    runUnitTests
         COMMAND runUnitTests)
