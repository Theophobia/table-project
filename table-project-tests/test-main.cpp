#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <table-project-tests/doctest.h>

#include <table-project-tests/tabletypes/Type.test.cpp>
#include <table-project-tests/tabletypes/IntegerType.test.cpp>
#include <table-project-tests/tabletypes/DoubleType.test.cpp>
#include <table-project-tests/tabletypes/StringType.test.cpp>
#include <table-project-tests/tabletypes/FormulaType.test.cpp>

#include <table-project-tests/table/Table.test.cpp>

#include <table-project-tests/math/Operators.test.cpp>
#include <table-project-tests/math/Parser.test.cpp>

#include <table-project-tests/util/StringUtil.test.cpp>
#include <table-project-tests/util/DoubleUtil.test.cpp>
#include <table-project-tests/util/VectorUtil.test.cpp>