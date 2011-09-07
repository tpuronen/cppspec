/*
 * Copyright 2011 Timo Puronen
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

#include "SpecResult.h"

namespace CppSpec {

SpecResult::SpecResult(const std::string& name) : specificationName(name) {
}
    
void SpecResult::addPass(const std::string& name, const std::string& duration) {
    BehaviorResult result;
    result.name = name;
    result.duration = duration;
    result.passed = true;
    behaviorResults.push_back(result);
}
    
void SpecResult::addFail(const std::string& name, const std::string& duration, const std::string& message) {
    addFail(name, duration, "", 0, message);
}
    
void SpecResult::addFail(const std::string& name, const std::string& duration, 
                         const std::string& file, int line, const std::string& message) {
    BehaviorResult result;
    result.name = name;
    result.duration = duration;
    result.passed = false;
    result.file = file;
    result.line = line;
    result.message = message;
    behaviorResults.push_back(result);
}

}