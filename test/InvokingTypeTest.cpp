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
#include "InvokingType.h"
#include <boost/bind.hpp>

using namespace CppSpec;

class Context {
public:
	explicit Context() : methodCalled(false) {}

	void voidMethodWithNoArgs() {methodCalled = true;}
	void voidMethodWithOneArg(int a) {methodCalled = true;}
	void voidMethodWithTwoArgs(int a, int b) {methodCalled = true;}
	void voidMethodWithThreeArgs(int a, int b, int c) {methodCalled = true;}
	void voidMethodWithFourArgs(int a, int b, int c, int d) {methodCalled = true;}
	void voidMethodWithFiveArgs(int a, int b, int c, int d, int e) {methodCalled = true;}

public:
	bool methodCalled;
};

class InvokingTypeTest : public ::testing::Test {
protected:
    InvokingTypeTest() {
		context = new Context;
    }

    ~InvokingTypeTest() {
		delete context;
		context = NULL;
    }

    Context* context;
};

TEST_F(InvokingTypeTest, callMethodWithNoArgs) {
    InvokingType functor(boost::bind(&Context::voidMethodWithNoArgs, context));
    functor.exception<int>();
    ASSERT_TRUE(context->methodCalled);
}

TEST_F(InvokingTypeTest, callMethodWithOneArg) {
    InvokingType functor(boost::bind(&Context::voidMethodWithOneArg, context, 1));
    functor.exception<int>();
    ASSERT_TRUE(context->methodCalled);
}

TEST_F(InvokingTypeTest, callMethodWithTwoArgs) {
    InvokingType functor(boost::bind(&Context::voidMethodWithTwoArgs, context, 1, 2));
    functor.exception<int>();
    ASSERT_TRUE(context->methodCalled);
}

TEST_F(InvokingTypeTest, callMethodWithThreeArgs) {
    InvokingType functor(boost::bind(&Context::voidMethodWithThreeArgs, context, 1, 2, 3));
    functor.exception<int>();
    ASSERT_TRUE(context->methodCalled);
}

TEST_F(InvokingTypeTest, callMethodWithFourArgs) {
    InvokingType functor(boost::bind(&Context::voidMethodWithFourArgs, context, 1, 2, 3, 4));
    functor.exception<int>();
    ASSERT_TRUE(context->methodCalled);
}
