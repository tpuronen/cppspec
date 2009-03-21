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

#ifndef INVOCATIONRESULT_H_
#define INVOCATIONRESULT_H_

#include <string>

namespace CppSpec {

class InvocationResult {
public:
    explicit InvocationResult() : result(false) {}
    InvocationResult(const InvocationResult& that) : result(that.result), description(that.description) {}

    void setSuccess() {result = true;}
    void setFailure(const std::string& description) {this->description = description;}

    bool wasSuccess() const {return result;}
    const std::string& getDescription() const {return description;}

private:
    InvocationResult& operator=(const InvocationResult&);

private:
    bool result;
    std::string description;
};

}

#endif /* INVOCATIONRESULT_H_ */
