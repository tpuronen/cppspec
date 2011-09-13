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

#ifndef __SPEC_RESULT__
#define __SPEC_RESULT__

#include "CppSpecConfig.h"
#include <string>
#include <vector>

namespace CppSpec {
    
class SpecResult {
public:
    struct BehaviorResult {
        BehaviorResult() {}
        BehaviorResult(const BehaviorResult& that);
        std::string name;
        std::string duration;
        bool passed;
        std::string file;
        std::string message;
        int line;
    };

public:
    SpecResult(const std::string& name);
    SpecResult(const SpecResult& that);
    SpecResult& operator=(const SpecResult& that);
    
    void addPass(const std::string& name, const std::string& duration);
    void addFail(const std::string& name, const std::string& duration, const std::string& message);
    void addFail(const std::string& name, const std::string& duration, const std::string& file, int line, const std::string& message);
    
    const std::string& getSpecificationName() const {return specificationName;}
    
    void setDuration(const std::string& specDuration) {duration = specDuration;}
    const std::string& getDuration() const {return duration;}

    std::vector<BehaviorResult>::const_iterator firstBehavior() const {return behaviorResults.begin();}
    std::vector<BehaviorResult>::const_iterator lastBehavior() const {return behaviorResults.end();}
    size_t passCount() const;
    size_t failCount() const;
    
private:    
    std::string specificationName;
    std::string duration;
    std::vector<BehaviorResult> behaviorResults;
};

}

#endif // __SPEC_RESULT__