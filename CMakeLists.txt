cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)
project(table-project)

include_directories(${CMAKE_SOURCE_DIR})

set(SOURCES
	table-project/tabletypes/Type.cpp
	table-project/tabletypes/IntegerType.cpp
	table-project/tabletypes/DoubleType.cpp
	table-project/tabletypes/StringType.cpp
	table-project/tabletypes/FormulaType.cpp
	table-project/table/Table.cpp
	table-project/math/Operators.cpp
	)

add_executable(Run ${SOURCES} table-project/main.cpp)
add_executable(Test ${SOURCES} table-project-tests/test-main.cpp)