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

#include <UnitTest++.h>
#include <Invocation.h>
#include <Specification.h>

using CppSpec::Invocation;
using CppSpec::InvocationResult;

void methodThrowingInt() {
    throw 5;
}

void methodThrowingStdException() {
    throw std::exception();
}

void nonThrowingMethod() {}

TEST(methodThrowsExpectedException) {
    Invocation<int> invocation(&methodThrowingInt);
    InvocationResult result = invocation.invoke();
    CHECK(result.wasSuccess());
}

TEST(methodThrowsDifferentExceptionType) {
    Invocation<std::string> invocation(&methodThrowingInt);
    InvocationResult result = invocation.invoke();
    CHECK_EQUAL(false, result.wasSuccess());
    CHECK_EQUAL("Expected type but unknown type was thrown", result.getDescription());
}

TEST(methodThrowsExpectedValue) {
    Invocation<int> invocation(&methodThrowingInt);
    InvocationResult result = invocation.invoke(5);
    CHECK(result.wasSuccess());
}

TEST(methodThrowsOtherValue) {
    Invocation<int> invocation(&methodThrowingInt);
    InvocationResult result = invocation.invoke(1);
    CHECK_EQUAL("Expected type[1] but type[5] was thrown", result.getDescription());
    CHECK_EQUAL(false, result.wasSuccess());
}

TEST(methodThrowsStdExceptionWhenIntExpected) {
    Invocation<int> invocation(&methodThrowingStdException);
    InvocationResult result = invocation.invoke(1);
    CHECK_EQUAL("Expected type but type[std::exception] was thrown", result.getDescription());
    CHECK_EQUAL(false, result.wasSuccess());
}

TEST(methodThrowsDifferentTypeWhenValueExpected) {
    Invocation<std::string> invocation(&methodThrowingInt);
    InvocationResult result = invocation.invoke(std::string("Exception"));
    CHECK_EQUAL("Expected type but unknown type was thrown", result.getDescription());
    CHECK_EQUAL(false, result.wasSuccess());
}

TEST(methodDoesNotThrowException) {
    Invocation<std::string> invocation(&nonThrowingMethod);
    InvocationResult result = invocation.invoke(std::string("Exception"));
    CHECK_EQUAL("Expected type but no exception was thrown", result.getDescription());
    CHECK_EQUAL(false, result.wasSuccess());
}
