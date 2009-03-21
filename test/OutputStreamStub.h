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

#ifndef OUTPUTSTREAMSTUB_H_
#define OUTPUTSTREAMSTUB_H_

#include "OutputStream.h"
#include <sstream>

class OutputStreamStub : public CppSpec::OutputStream {
public:
    OutputStreamStub() : writtenData() {}
    OutputStream& operator<<(const std::string& output) {writtenData << output; return *this;}
    OutputStream& operator<<(long output) {writtenData << output; return *this;}

    const std::string written() {return writtenData.str();}
private:
    std::stringstream writtenData;
};

#endif /* OUTPUTSTREAMSTUB_H_ */
