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
#include <UnitTest++.h>
#include <string>
#include <boost/regex.hpp>

using CppSpec::BoostTimer;

struct BoostTimerTest {
    BoostTimerTest() : regexp("\\d{2}.\\d{6}") {timer = new BoostTimer;}
    ~BoostTimerTest() {delete timer;}

    BoostTimer* timer;
    boost::regex regexp;
};

SUITE(BoostTimer) {
    TEST_FIXTURE(BoostTimerTest, specificationDurationFormatIsExpected) {
        timer->startSpecification();
        std::string duration(timer->durationFromSpecificationStart());
        CHECK(boost::regex_match(duration, regexp));
    }

    TEST_FIXTURE(BoostTimerTest, behaviorDurationFormatIsExpected) {
        timer->startBehavior();
        std::string duration(timer->durationFromBehaviorStart());
        CHECK(boost::regex_match(duration, regexp));
    }
}
