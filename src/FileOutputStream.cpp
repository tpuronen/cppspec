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

#include "FileOutputStream.h"

namespace CppSpec {

FileOutputStream::FileOutputStream(const std::string& directory, const std::string& specification) {
    boost::filesystem::path reportPath(directory);
    reportPath /= (specification + ".xml");
    file.open(reportPath);
}

FileOutputStream::~FileOutputStream() {
    file.close();
}

OutputStream& FileOutputStream::operator<<(const std::string& output) {
    file << output;
    return *this;
}

OutputStream& FileOutputStream::operator<<(long output) {
    file << output;
    return *this;
}

}
