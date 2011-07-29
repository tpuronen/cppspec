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

find_path(UNITTESTPP_INCLUDE_DIR UnitTest++.h)
find_library(UNITTESTPP_LIBRARY NAMES UnitTest++)
find_package(GTest REQUIRED)
include_directories(../include ${GTEST_INCLUDE_DIRS})

add_executable(CppSpecGTest main.cpp)
target_link_libraries(CppSpecGTest ${GTEST_BOTH_LIBRARIES})

add_test(CppSpecTests CppSpecGTest)

if(UNITTESTPP_INCLUDE_DIR AND UNITTESTPP_LIBRARY) 
	include_directories(../include ${UNITTESTPP_INCLUDE_DIR} ${Boost_INCLUDE_DIRS})
	set(CPPSPEC_SRCS ../src/SpecDoxReporter.cpp ../src/Matcher.cpp ../src/SpecificationRegistry.cpp ../src/SpecRunner.cpp ../src/BoostTimer.cpp ../src/CuteReporter.cpp
	   ../src/JUnitReporter.cpp ../src/FileOutputStream.cpp ../src/ConsoleOutputStream.cpp ../src/Util.cpp)

	if(UNIX)
		set(CMAKE_CXX_FLAGS  ${CMAKE_CXX_FLAGS} " -Wall -fprofile-arcs -ftest-coverage")
	endif(UNIX)
	
	if(MSVC)
		set(EXTRA_LIBS winmm.lib)
		set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} " /EHsc")
	endif(MSVC)
	
	add_definitions(-D__CPPSPEC_TEST__)
	set(EXECUTABLE_OUTPUT_PATH ../bin)	
	link_directories(${Boost_LIBRARY_DIRS})
	add_executable(CppSpecTest ${CPPSPEC_SRCS} main.cpp SpecDoxReporterTest.cpp BoostTimerTest.cpp SpecificationRegistryTest.cpp
	   JUnitReporterTest.cpp InvokingTypeTest.cpp TypeHasStreamingOperatorTest.cpp VoidSpecification.cpp MatcherTest.cpp
	   ExpectationTest.cpp InvocationTest.cpp ExceptionThrowingSpecificationTest.cpp CuteReporterTest.cpp SpecificationTest.cpp
	   DummyReporter.cpp SpecRunnerTest.cpp) 
	target_link_libraries(CppSpecTest ${UNITTESTPP_LIBRARY} ${EXTRA_LIBS} ${Boost_DATE_TIME_LIBRARY} ${Boost_PROGRAM_OPTIONS_LIBRARY}
		${Boost_FILESYSTEM_LIBRARY} ${Boost_REGEX_LIBRARY})
endif(UNITTESTPP_INCLUDE_DIR AND UNITTESTPP_LIBRARY) 
