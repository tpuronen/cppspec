/*
 * Copyright 2008 Timo Puronen
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

#ifndef SPECIFYFAILEDEXCEPTION_H_
#define SPECIFYFAILEDEXCEPTION_H_

namespace CppSpec {

class SpecifyFailedException {
public:
    SpecifyFailedException(const std::string& file, int line, const std::string& message) : file(file), line(line), message(message) {}
    SpecifyFailedException(const SpecifyFailedException& that) : file(that.file), line(that.line), message(that.message) {}

private:
    SpecifyFailedException& operator=(const SpecifyFailedException&);

public:
    std::string file;
    int line;
    std::string message;
};

}

#endif /* SPECIFYFAILEDEXCEPTION_H_ */
