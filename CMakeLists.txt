cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 11)

project(excel)


add_executable(
	main

	src/main.cpp
	src/Type.cpp
	src/IntegerType.cpp
	src/FloatingType.cpp
	src/doctest.h src/FloatingType.test.cpp src/doctest_main.cpp)