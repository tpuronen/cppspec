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

#ifndef FILEOUTPUTSTREAM_H_
#define FILEOUTPUTSTREAM_H_

#include "OutputStream.h"
#include <string>
#include <boost/filesystem/fstream.hpp>

namespace CppSpec {

class FileOutputStream : public OutputStream {
public:
    explicit FileOutputStream(const std::string& directory, const std::string& specification);
    virtual ~FileOutputStream();

public: // from OutputStream
    OutputStream& operator<<(const std::string& output);
    OutputStream& operator<<(long output);

private:
    FileOutputStream(const FileOutputStream&);
    FileOutputStream& operator=(const FileOutputStream&);

private:
    boost::filesystem::ofstream file;
};

}

#endif /* FILEOUTPUTSTREAM_H_ */
