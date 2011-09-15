#
# Copyright 2007 - 2009 Timo Puronen
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

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ../lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)
set(CPPSPEC_SRCS SpecDoxReporter.cpp SpecificationRegistry.cpp SpecRunner.cpp Util.cpp SpecResult.cpp
	Timer.cpp Matcher.cpp JUnitReporter.cpp BoostTimer.cpp FileOutputStream.cpp ConsoleOutputStream.cpp)

set(CPPSPEC_INCLUDES ../include/BeType.h ../include/Invocation.h ../include/SpecDoxReporter.h 
    ../include/Behavior.h ../include/InvocationResult.h ../include/SpecResult.h ../include/BoostTimer.h 
    ../include/InvokingType.h ../include/SpecRunner.h ../include/ConsoleOutputStream.h ../include/JUnitReporter.h 
    ../include/Specification.h ../include/ContextHolder.h ../include/Matcher.h ../include/SpecificationBase.h 
    ../include/CppSpec.h ../include/SpecificationRegistry.h ../include/CppSpecConfig.h
    ../include/OutputStream.h ../include/SpecifyFailedException.h ../include/Expectation.h ../include/Reporter.h 
    ../include/Timer.h ../include/FileOutputStream.h ../include/Runnable.h ../include/TypeHasStreamingOperator.h 
    ../include/Functor.h ../include/ShouldType.h ../include/TypeNameResolver.h)

include_directories("${CMAKE_HOME_DIRECTORY}/include" ${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})
add_library(CppSpec SHARED ${CPPSPEC_SRCS} ${CPPSPEC_INCLUDES})
target_link_libraries(CppSpec ${Boost_LIBRARIES})

if(MSVC_IDE)
    file(GLOB CPPSPEC_HEADERS "${CMAKE_HOME_DIRECTORY}/include/*.h")
    source_group("Header Files" FILES ${CPPSPEC_HEADERS})
    
    list(APPEND CPPSPEC_SRCS ${CPPSPEC_HEADERS})
endif(MSVC_IDE)

if(UNIX)
	set(CMAKE_CXX_FLAGS  ${CMAKE_CXX_FLAGS} " -Wall -Wextra")
endif(UNIX)

if(MSVC)
	set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} " /EHsc")
endif(MSVC)


install(TARGETS CppSpec
		RUNTIME DESTINATION bin
		LIBRARY DESTINATION lib
		ARCHIVE DESTINATION lib)

install(FILES 	../include/CppSpec.h
				../include/SpecificationBase.h
				../include/Specification.h
				../include/Expectation.h
				../include/SpecRunner.h
				../include/SpecificationRegistry.h
				../include/Runnable.h
				../include/Reporter.h
				../include/Matcher.h
				../include/ShouldType.h
				../include/InvokingType.h
				../include/BeType.h
				../include/ContextHolder.h
				../include/Functor.h
				../include/Behavior.h
				../include/TypeHasStreamingOperator.h
				../include/TypeNameResolver.h
				../include/CppSpecConfig.h
				../include/SpecifyFailedException.h
				../include/Invocation.h
				../include/InvocationResult.h
                ../include/SpecResult.h
                ../include/Timer.h
		DESTINATION include/CppSpec)

install(FILES   ../include/Needle/Binder.h
                ../include/Needle/Inject.h
                ../include/Needle/NeedleTypeNameResolver.h
        DESTINATION include/CppSpec/Needle)

set(CPACK_PACKAGE_NAME "cppspec")
set(CPACK_PACKAGE_VERSION_MAJOR 0)
set(CPACK_PACKAGE_VERSION_MINOR 5)
set(CPACK_PACKAGE_VERSION_PATCH 0)
set(CPACK_PACKAGE_CONTACT timo.puronen@reaktor.fi)
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Behavior-driven development framework for C++")
#set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_HOME_DIRECTORY}/README")
#set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_HOME_DIRECTORY}/LICENSE")
set(CPACK_NSIS_MODIFY_PATH ON)

include(CPack)
include(InstallRequiredSystemLibraries)
