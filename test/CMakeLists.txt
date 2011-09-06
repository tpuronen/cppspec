#
# Copyright 2007 Timo Puronen
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

find_package(GTest REQUIRED)
include_directories(../include ${GTEST_INCLUDE_DIRS} ${BOOST_INCLUDE_DIRS})

set(CPPSPEC_SRCS ../src/SpecDoxReporter.cpp ../src/Matcher.cpp ../src/SpecificationRegistry.cpp ../src/SpecRunner.cpp ../src/BoostTimer.cpp 
    ../src/CuteReporter.cpp ../src/JUnitReporter.cpp ../src/FileOutputStream.cpp ../src/ConsoleOutputStream.cpp ../src/Util.cpp)

set(CPPSPEC_TEST_SRCS main.cpp JUnitReporterTest.cpp SpecDoxReporterTest.cpp BoostTimerTest.cpp SpecificationRegistryTest.cpp
    InvokingTypeTest.cpp TypeHasStreamingOperatorTest.cpp VoidSpecification.cpp MatcherTest.cpp
    ExpectationTest.cpp InvocationTest.cpp ExceptionThrowingSpecificationTest.cpp CuteReporterTest.cpp SpecificationTest.cpp
    DummyReporter.cpp SpecRunnerTest.cpp)

add_executable(CppSpecGTest ${CPPSPEC_SRCS} ${CPPSPEC_TEST_SRCS})
link_directories(${BOOST_LIBRARY_DIRS})
target_link_libraries(CppSpecGTest ${GTEST_BOTH_LIBRARIES} ${Boost_LIBRARIES})

add_test(CppSpecTests CppSpecGTest)
