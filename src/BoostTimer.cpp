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

#include "BoostTimer.h"
#include <iomanip>

namespace CppSpec {

BoostTimer::BoostTimer() {}

BoostTimer::~BoostTimer() {
}

void BoostTimer::startSpecification() {
    specificationStartTime = boost::chrono::system_clock::now();
}

void BoostTimer::startBehavior() {
    behaviorStartTime = boost::chrono::system_clock::now();
}

std::string BoostTimer::durationFromSpecificationStart() {
    return durationFrom(specificationStartTime);
}

std::string BoostTimer::durationFromBehaviorStart() {
	return durationFrom(behaviorStartTime);
}

std::string BoostTimer::durationFrom(boost::chrono::system_clock::time_point& startTime) {
    boost::chrono::duration<double> secs = boost::chrono::system_clock::now() - startTime;
    stream.str("");
    stream << std::fixed << std::setprecision(6) << secs.count();
    return stream.str();
}

}
