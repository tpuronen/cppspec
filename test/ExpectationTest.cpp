/*
 * Copyright 2009 Timo Puronen
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
#include "Expectation.h"

using CppSpec::Expectation;
using CppSpec::FloatExpectation;

TEST(ExpectationTest, sameTypesEqual) {
  std::string result("expected");
  Expectation<std::string> expected(result);
  EXPECT_TRUE(expected.equals(std::string("expected")));
  EXPECT_TRUE((!expected).equals("something else"));
}

TEST(ExpectationTest, convertibleTypesEqual) {
  std::string result("expected");
  Expectation<std::string> expected(result);
  EXPECT_TRUE(expected.equals("expected"));
}

TEST(ExpectationTest, intTypesEqual) {
  const int result = 24;
  Expectation<int> expected(result);
  EXPECT_TRUE(expected.equals(24));
  EXPECT_TRUE((!expected).equals(25));
}

TEST(FloatExpectationTest, floatTypesEqual) {
  const float result = 2.4f;
  const float tolerance = 0.05f;
  FloatExpectation<float> expected(result, tolerance);
  EXPECT_TRUE(expected.almostEquals(2.41f));
  EXPECT_TRUE((!expected).almostEquals(2.5f));
}
