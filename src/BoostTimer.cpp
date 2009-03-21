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

namespace CppSpec {

BoostTimer::BoostTimer() : specificationStartTime(boost::posix_time::not_a_date_time), behaviorStartTime(boost::posix_time::not_a_date_time) {
    boost::posix_time::time_facet* facet = new boost::posix_time::time_facet();
    stream.imbue(std::locale(std::locale::classic(), facet));
    facet->time_duration_format("%s");
}

BoostTimer::~BoostTimer() {
}

void BoostTimer::startSpecification() {
	specificationStartTime = boost::posix_time::microsec_clock::local_time();
}

void BoostTimer::startBehavior() {
	behaviorStartTime = boost::posix_time::microsec_clock::local_time();
}

std::string BoostTimer::durationFromSpecificationStart() {
    return durationFrom(specificationStartTime);
}

std::string BoostTimer::durationFromBehaviorStart() {
	return durationFrom(behaviorStartTime);
}

std::string BoostTimer::durationFrom(boost::posix_time::ptime& startTime) {
	boost::posix_time::time_duration duration = boost::posix_time::microsec_clock::local_time() - startTime;
    startTime = boost::posix_time::not_a_date_time;
	stream.str("");
    stream << duration;
    return stream.str();
}

}
