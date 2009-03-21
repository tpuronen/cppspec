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

#ifndef CONSOLEOUTPUTSTREAM_H_
#define CONSOLEOUTPUTSTREAM_H_

#include "OutputStream.h"

namespace CppSpec {

class ConsoleOutputStream : public OutputStream {
public:
    ConsoleOutputStream();
    ~ConsoleOutputStream();

public: // from OutputStream
    OutputStream& operator<<(const std::string& output);
    OutputStream& operator<<(long output);

private:
    ConsoleOutputStream(const ConsoleOutputStream&);
    ConsoleOutputStream& operator=(const ConsoleOutputStream&);
};

}

#endif /* CONSOLEOUTPUTSTREAM_H_ */
