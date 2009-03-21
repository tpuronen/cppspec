#
# Copyright 2007-2008 Timo Puronen
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

cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(CppSpec)
set(VERSION 0.5.0)

if(WIN32)
  set(Boost_USE_STATIC_LIBS ON)
endif(WIN32)
find_package(Boost COMPONENTS regex program_options filesystem date_time)
add_definitions(${Boost_LIB_DIAGNOSTIC_DEFINITIONS}) 

add_subdirectory(src)
add_subdirectory(examples)
add_subdirectory(test)
