cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 11)

project(table)


add_executable(
	Run

	src/main.cpp

	src/celltypes/base/Type.cpp
	src/celltypes/IntegerType.cpp
	src/celltypes/DoubleType.cpp
	src/celltypes/StringType.cpp

)

add_executable(
	Test

	test/main/main.cpp

	src/celltypes/base/Type.cpp
	src/celltypes/IntegerType.cpp
	src/celltypes/DoubleType.cpp
	src/celltypes/StringType.cpp
)