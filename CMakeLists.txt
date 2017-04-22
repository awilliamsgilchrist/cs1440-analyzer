cmake_minimum_required(VERSION 3.6)
project(ITAK)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES KeyValue.h Dictionary.h Configuration.cpp Configuration.h Utils.cpp Utils.h ResultSet.cpp ResultSet.h Analyzer.h DenialOfServiceAnalyzer.cpp DenialOfServiceAnalyzer.h)
add_executable(ITAK ${SOURCE_FILES} main.cpp)