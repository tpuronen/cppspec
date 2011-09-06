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
#include "Invocation.h"
#include "Specification.h"

using CppSpec::Invocation;
using CppSpec::InvocationResult;

void methodThrowingInt() {
    throw 5;
}

void methodThrowingStdException() {
    class stdexception : public std::exception {
    public:
        const char* what() const throw() {return "std::exception";}
    };
    throw stdexception();
}

void nonThrowingMethod() {}


TEST(InvocationTest, methodThrowsExpectedException) {
    Invocation<int> invocation(&methodThrowingInt);
    InvocationResult result = invocation.invoke();
    EXPECT_TRUE(result.wasSuccess());
}

TEST(InvocationTest, methodThrowsDifferentExceptionType) {
    Invocation<std::string> invocation(&methodThrowingInt);
    InvocationResult result = invocation.invoke();
    EXPECT_FALSE(result.wasSuccess());
    EXPECT_EQ("Expected std::string but unknown type was thrown", result.getDescription());
}

TEST(InvocationTest, methodThrowsExpectedValue) {
    Invocation<int> invocation(&methodThrowingInt);
    InvocationResult result = invocation.invoke(5);
    EXPECT_TRUE(result.wasSuccess());
}

TEST(InvocationTest, methodThrowsOtherValue) {
    Invocation<int> invocation(&methodThrowingInt);
    InvocationResult result = invocation.invoke(1);
    EXPECT_EQ("Expected int[1] but int[5] was thrown", result.getDescription());
    EXPECT_FALSE(result.wasSuccess());
}

TEST(InvocationTest, methodThrowsStdExceptionWhenIntExpected) {
    Invocation<int> invocation(&methodThrowingStdException);
    InvocationResult result = invocation.invoke(1);
    EXPECT_EQ("Expected int but methodThrowingStdException()::stdexception[std::exception] was thrown", result.getDescription());
    EXPECT_FALSE(result.wasSuccess());
}

TEST(InvocationTest, methodThrowsDifferentTypeWhenValueExpected) {
    Invocation<std::string> invocation(&methodThrowingInt);
    InvocationResult result = invocation.invoke(std::string("Exception"));
    EXPECT_EQ("Expected std::string but unknown type was thrown", result.getDescription());
    EXPECT_FALSE(result.wasSuccess());
}

TEST(InvocationTest, methodDoesNotThrowException) {
    Invocation<std::string> invocation(&nonThrowingMethod);
    InvocationResult result = invocation.invoke(std::string("Exception"));
    EXPECT_EQ("Expected std::string but no exception was thrown", result.getDescription());
    EXPECT_FALSE(result.wasSuccess());
}
