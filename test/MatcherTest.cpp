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

#include "UnitTest++.h"
#include "Matcher.h"

using CppSpec::Matcher;

TEST(findsSubstring) {
    Matcher matcher("violence", Matcher::Search);
    CHECK(matcher("Words like violence break the silence."));
}

TEST(substringNotFound) {
    Matcher matcher("enjoy", Matcher::Search);
    CHECK(!matcher("Words like violence break the silence."));
}

TEST(stringsMatch) {
    Matcher matcher(".*violence.*silence.*", Matcher::Match);
    CHECK(matcher("Words like violence break the silence."));
}

TEST(stringsDoNotMatch) {
    Matcher matcher(".*silence.*violence.*", Matcher::Match);
    !matcher;
    CHECK(matcher("Words like violence break the silence."));
}

TEST(copy) {
    Matcher matcher(".*silence.*violence.*", Matcher::Match);
    Matcher that(matcher);
    CHECK_EQUAL(that.getMode(), Matcher::Match);
    CHECK_EQUAL(that.getExpression(), ".*silence.*violence.*");
}
