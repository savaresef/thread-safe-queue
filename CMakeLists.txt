cmake_minimum_required(VERSION 3.6)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(THREADS_PREFER_PTHREAD_FLAG ON)
# The project name
project(TSQueue)

#add_subdirectory(include)
add_subdirectory(src)
#add_subdirectory(test)

#enable_testing()
#add_test(testQ test/test.cpp COMMAND test)
