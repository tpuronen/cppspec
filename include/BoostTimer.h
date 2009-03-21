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

#ifndef BOOSTTIMER_H_
#define BOOSTTIMER_H_

#include "Timer.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <sstream>

namespace CppSpec {

class BoostTimer : public Timer {
public:
	explicit BoostTimer();
	virtual ~BoostTimer();

public: // from Timer
	void startSpecification();
	void startBehavior();
	std::string durationFromSpecificationStart();
	std::string durationFromBehaviorStart();

private:
	std::string durationFrom(boost::posix_time::ptime& startTime);

private:
    BoostTimer(const BoostTimer&);
    BoostTimer& operator=(const BoostTimer&);

private:
	boost::posix_time::ptime specificationStartTime;
	boost::posix_time::ptime behaviorStartTime;
	std::stringstream stream;
};

}

#endif /* BOOSTTIMER_H_ */
