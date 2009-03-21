/*
 * Copyright 2009 Timo Puronen
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "ConsoleOutputStream.h"
#include <iostream>

namespace CppSpec {

ConsoleOutputStream::ConsoleOutputStream() {
}

ConsoleOutputStream::~ConsoleOutputStream() {
}

OutputStream& ConsoleOutputStream::operator<<(const std::string& output) {
    std::cout << output;
    return *this;
}

OutputStream& ConsoleOutputStream::operator<<(long output) {
    std::cout << output;
    return *this;
}

}
