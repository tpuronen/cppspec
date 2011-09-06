/*
 * Copyright 2007 Timo Puronen
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
#include "CppSpec.h"

using CppSpec::InvocationResult;
using CppSpec::Specification;

class TestClass {
public:
	class MyException : public std::exception {
	public:
	    const char* what() const throw() {return "MyException";}
	};

	class RuntimeException : public std::runtime_error {
	public:
	    explicit RuntimeException(const std::string& message) : std::runtime_error(message) {}
	};

	class NonStreamable {
	public:
		bool operator==(const NonStreamable&) {
			return false;
		}
	};

	void throwStdException() {
		throw std::exception();
	}

	void throwInt() {
		throw 1;
	}

	void throwDerived() {
		throw MyException();
	}

	void throwRuntimeException() {
	    throw RuntimeException("Something terrible happened");
	}

	void throwString() {
		throw std::string("Exception occured");
	}

	void functionWithArgument(int arg) {
		if(arg > 10) {
			throw std::exception();
		}
	}

	void constFunctionThrowingException() const {
		throw std::exception();
	}

	void functionWithTwoArguments(int arg, int arg2) {
		throw std::exception();
	}

	void functionWithThreeArguments(int arg, int arg2, int arg3) {
		throw std::exception();
	}

	void throwNonStreamable() {
		throw NonStreamable();
	}
};

class TestSpec : public Specification<TestClass, TestSpec> {
};

class ExceptionThrowingSpecificationTest : public ::testing::Test {
protected:
	ExceptionThrowingSpecificationTest() {
        spec = new TestSpec();
	}

    ~ExceptionThrowingSpecificationTest() {
		delete spec;
		spec = NULL;
    }

	TestSpec* spec;
};

TEST_F(ExceptionThrowingSpecificationTest, StdException) {
	InvocationResult result = spec->invoking(&TestClass::throwStdException).should.raise.exception<std::exception>();
    EXPECT_TRUE(result.wasSuccess());
}

TEST_F(ExceptionThrowingSpecificationTest, ThrowInt) {
	InvocationResult result = spec->invoking(&TestClass::throwInt).should.raise.exception<int>();
    EXPECT_TRUE(result.wasSuccess());
}

TEST_F(ExceptionThrowingSpecificationTest, ThrowIntValue) {
	InvocationResult result = spec->invoking(&TestClass::throwInt).should.raise.exception<int>(1);
    EXPECT_TRUE(result.wasSuccess());
}

TEST_F(ExceptionThrowingSpecificationTest, ThrowStringValue) {
	InvocationResult result = spec->invoking(&TestClass::throwString).should.raise.exception(std::string("Exception occured"));
    EXPECT_TRUE(result.wasSuccess());
}

TEST_F(ExceptionThrowingSpecificationTest, DifferentStringValueThrown) {
    try {
        spec->specify(spec->invoking(&TestClass::throwString).should.raise.exception(std::string("Another exception occured")));
    } catch (CppSpec::SpecifyFailedException& e) {
        EXPECT_EQ("Expected std::string[Another exception occured] but std::string[Exception occured] was thrown", e.message);
        return;
    }
    FAIL();
}

TEST_F(ExceptionThrowingSpecificationTest, ThrowWrongIntValue) {
    try {
        spec->specify(spec->invoking(&TestClass::throwInt).should.raise.exception(2));
    } catch (CppSpec::SpecifyFailedException& e) {
        EXPECT_EQ("Expected int[2] but int[1] was thrown", e.message);
        return;
    }
    FAIL();
}

TEST_F(ExceptionThrowingSpecificationTest, DerivedException) {
    InvocationResult result = spec->invoking(&TestClass::throwDerived).should.raise.exception<TestClass::MyException>();
    EXPECT_TRUE(result.wasSuccess());
}

TEST_F(ExceptionThrowingSpecificationTest, ThrowWrongException) {
    try {
        spec->specify(spec->invoking(&TestClass::throwDerived).should.raise.exception<std::string>());
    } catch (CppSpec::SpecifyFailedException& e) {
        EXPECT_EQ("Expected std::string but TestClass::MyException[MyException] was thrown", e.message);
        return;
    }
    FAIL();
}

TEST_F(ExceptionThrowingSpecificationTest, ConstFunctionThrowing) {
	InvocationResult result = spec->invoking(&TestClass::constFunctionThrowingException).should.raise.exception<std::exception>();
    EXPECT_TRUE(result.wasSuccess());
}

TEST_F(ExceptionThrowingSpecificationTest, FunctionWithArgument) {
	InvocationResult result = spec->invoking(&TestClass::functionWithArgument, 20).should.raise.exception<std::exception>();
    EXPECT_TRUE(result.wasSuccess());
}

TEST_F(ExceptionThrowingSpecificationTest, FunctionWithTwoArguments) {
	InvocationResult result = spec->invoking(&TestClass::functionWithTwoArguments, 1, 2).should.raise.exception<std::exception>();
	EXPECT_TRUE(result.wasSuccess());
}

TEST_F(ExceptionThrowingSpecificationTest, FunctionWithThreeArguments) {
	InvocationResult result = spec->invoking(&TestClass::functionWithThreeArguments, 1, 2, 3).should.raise.exception<std::exception>();
	EXPECT_TRUE(result.wasSuccess());
}

TEST_F(ExceptionThrowingSpecificationTest, FunctionWithArgumentNoThrow) {
	try {
        spec->specify(spec->invoking(&TestClass::functionWithArgument, 0).should.raise.exception<std::string>());
    } catch (CppSpec::SpecifyFailedException& e) {
        EXPECT_EQ("Expected std::string but no exception was thrown", e.message);
        return;
    }
    FAIL();
}

TEST_F(ExceptionThrowingSpecificationTest, ThrowNonStreamable) {
    try {
        spec->specify(spec->invoking(&TestClass::throwNonStreamable).should.raise.exception<int>());
    } catch (CppSpec::SpecifyFailedException& e) {
        EXPECT_EQ("Expected int but unknown type was thrown", e.message);
        return;
    }
    FAIL();
}

TEST_F(ExceptionThrowingSpecificationTest, AssertStdExceptionTypeAndMessage) {
    InvocationResult result = spec->invoking(&TestClass::throwDerived).should.raise.exception(TestClass::MyException());
    EXPECT_TRUE(result.wasSuccess());
}
