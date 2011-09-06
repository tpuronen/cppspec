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
#include "Matcher.h"

using CppSpec::Matcher;

TEST(MatcherTest, findsSubstring) {
    Matcher matcher("violence", Matcher::Search);
    EXPECT_TRUE(matcher("Words like violence break the silence."));
}

TEST(MatcherTest, substringNotFound) {
    Matcher matcher("enjoy", Matcher::Search);
    EXPECT_FALSE(matcher("Words like violence break the silence."));
}

TEST(MatcherTest, stringsMatch) {
    Matcher matcher(".*violence.*silence.*", Matcher::Match);
    EXPECT_TRUE(matcher("Words like violence break the silence."));
}

TEST(MatcherTest, stringsDoNotMatch) {
    Matcher matcher(".*silence.*violence.*", Matcher::Match);
    !matcher;
    EXPECT_TRUE(matcher("Words like violence break the silence."));
}

TEST(MatcherTest, copy) {
    Matcher matcher(".*silence.*violence.*", Matcher::Match);
    Matcher that(matcher);
    EXPECT_EQ(that.getMode(), Matcher::Match);
    EXPECT_EQ(that.getExpression(), ".*silence.*violence.*");
}
