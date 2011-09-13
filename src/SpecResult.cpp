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
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>

namespace CppSpec {

SpecResult::BehaviorResult::BehaviorResult(const SpecResult::BehaviorResult& that)
    : name(that.name), duration(that.duration), passed(that.passed), file(that.file), message(that.message), line(that.line)
{
}
    
SpecResult::SpecResult(const std::string& name) : specificationName(name) {
}
    
SpecResult::SpecResult(const SpecResult& that) : specificationName(that.specificationName), duration(that.duration) {
    behaviorResults.resize(that.behaviorResults.size());
    std::copy(that.firstBehavior(), that.lastBehavior(), behaviorResults.begin());
}
 
SpecResult& SpecResult::operator=(const SpecResult& that) {
    specificationName = that.specificationName;
    duration = that.duration;
    behaviorResults.resize(that.behaviorResults.size());
    std::copy(that.firstBehavior(), that.lastBehavior(), behaviorResults.begin());
    return *this;
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

size_t SpecResult::passCount() const {
    return std::count_if(behaviorResults.begin(), behaviorResults.end(), 
                         boost::lambda::bind(&BehaviorResult::passed, boost::lambda::_1) == true);
}

size_t SpecResult::failCount() const {
    return std::count_if(behaviorResults.begin(), behaviorResults.end(),
                         boost::lambda::bind(&BehaviorResult::passed, boost::lambda::_1) == false);
}

}