cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 11)

project(table)


add_executable(
	Run

	src/main.cpp

	src/tabletypes/base/Type.cpp
	src/tabletypes/IntegerType.cpp
	src/tabletypes/DoubleType.cpp
	src/tabletypes/StringType.cpp
	src/tabletypes/FormulaType.cpp
	src/table/Table.cpp
)

add_executable(
	Test

	test/main/TestEntry.cpp

	src/tabletypes/base/Type.cpp
	src/tabletypes/IntegerType.cpp
	src/tabletypes/DoubleType.cpp
	src/tabletypes/StringType.cpp
	src/tabletypes/FormulaType.cpp
	src/table/Table.cpp
)