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

#include <gtest/gtest.h>
#include "BoostTimer.h"
#include <string>
#include <boost/regex.hpp>

using CppSpec::BoostTimer;

class BoostTimerTest : public ::testing::Test {
public:
    BoostTimerTest() : regexp("\\d{1}.\\d{6}") {timer = new BoostTimer;}
    ~BoostTimerTest() {delete timer;}

    BoostTimer* timer;
    boost::regex regexp;
};

TEST_F(BoostTimerTest, specificationDurationFormatIsExpected) {
    timer->start();
    std::string duration(timer->stop());
    ASSERT_TRUE(boost::regex_match(duration, regexp));    
}

TEST_F(BoostTimerTest, behaviorDurationFormatIsExpected) {
    timer->start();
    std::string duration(timer->stop());
    ASSERT_TRUE(boost::regex_match(duration, regexp));
}

