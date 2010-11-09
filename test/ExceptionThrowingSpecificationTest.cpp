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

#include "UnitTest++.h"
#include "CppSpec.h"

using CppSpec::InvocationResult;
using CppSpec::Specification;

class Test {
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

class TestSpec : public Specification<Test, TestSpec> {
};

struct ExceptionThrowingSpecification{
	ExceptionThrowingSpecification() {
        spec = new TestSpec();
	}

    ~ExceptionThrowingSpecification() {
		delete spec;
		spec = NULL;
    }

	TestSpec* spec;
};

TEST_FIXTURE(ExceptionThrowingSpecification, StdException) {
	InvocationResult result = spec->invoking(&Test::throwStdException).should.raise.exception<std::exception>();
    CHECK(result.wasSuccess());
}

TEST_FIXTURE(ExceptionThrowingSpecification, ThrowInt) {
	InvocationResult result = spec->invoking(&Test::throwInt).should.raise.exception<int>();
    CHECK(result.wasSuccess());
}

TEST_FIXTURE(ExceptionThrowingSpecification, ThrowIntValue) {
	InvocationResult result = spec->invoking(&Test::throwInt).should.raise.exception<int>(1);
    CHECK(result.wasSuccess());
}

TEST_FIXTURE(ExceptionThrowingSpecification, ThrowStringValue) {
	InvocationResult result = spec->invoking(&Test::throwString).should.raise.exception(std::string("Exception occured"));
    CHECK(result.wasSuccess());
}

TEST_FIXTURE(ExceptionThrowingSpecification, DifferentStringValueThrown) {
    try {
        spec->specify(spec->invoking(&Test::throwString).should.raise.exception(std::string("Another exception occured")));
    } catch (CppSpec::SpecifyFailedException& e) {
        CHECK_EQUAL("Expected type[Another exception occured] but type[Exception occured] was thrown", e.message);
        return;
    }
    CHECK(false);
}

TEST_FIXTURE(ExceptionThrowingSpecification, ThrowWrongIntValue) {
    try {
        spec->specify(spec->invoking(&Test::throwInt).should.raise.exception(2));
    } catch (CppSpec::SpecifyFailedException& e) {
        CHECK_EQUAL("Expected type[2] but type[1] was thrown", e.message);
        return;
    }
    CHECK(false);
}

TEST_FIXTURE(ExceptionThrowingSpecification, DerivedException) {
    InvocationResult result = spec->invoking(&Test::throwDerived).should.raise.exception<Test::MyException>();
    CHECK(result.wasSuccess());
}

TEST_FIXTURE(ExceptionThrowingSpecification, ThrowWrongException) {
    try {
        spec->specify(spec->invoking(&Test::throwDerived).should.raise.exception<std::string>());
    } catch (CppSpec::SpecifyFailedException& e) {
        CHECK_EQUAL("Expected type but type[MyException] was thrown", e.message);
        return;
    }
    CHECK(false);
}

TEST_FIXTURE(ExceptionThrowingSpecification, ConstFunctionThrowing) {
	InvocationResult result = spec->invoking(&Test::constFunctionThrowingException).should.raise.exception<std::exception>();
    CHECK(result.wasSuccess());
}

TEST_FIXTURE(ExceptionThrowingSpecification, FunctionWithArgument) {
	InvocationResult result = spec->invoking(&Test::functionWithArgument, 20).should.raise.exception<std::exception>();
    CHECK(result.wasSuccess());
}

TEST_FIXTURE(ExceptionThrowingSpecification, FunctionWithTwoArguments) {
	InvocationResult result = spec->invoking(&Test::functionWithTwoArguments, 1, 2).should.raise.exception<std::exception>();
	CHECK(result.wasSuccess());
}

TEST_FIXTURE(ExceptionThrowingSpecification, FunctionWithThreeArguments) {
	InvocationResult result = spec->invoking(&Test::functionWithThreeArguments, 1, 2, 3).should.raise.exception<std::exception>();
	CHECK(result.wasSuccess());
}

TEST_FIXTURE(ExceptionThrowingSpecification, FunctionWithArgumentNoThrow) {
	try {
        spec->specify(spec->invoking(&Test::functionWithArgument, 0).should.raise.exception<std::string>());
    } catch (CppSpec::SpecifyFailedException& e) {
        CHECK_EQUAL("Expected type but no exception was thrown", e.message);
        return;
    }
    CHECK(false);
}

TEST_FIXTURE(ExceptionThrowingSpecification, ThrowNonStreamable) {
    try {
        spec->specify(spec->invoking(&Test::throwNonStreamable).should.raise.exception<int>());
    } catch (CppSpec::SpecifyFailedException& e) {
        CHECK_EQUAL("Expected type but unknown type was thrown", e.message);
        return;
    }
    CHECK(false);
}

TEST_FIXTURE(ExceptionThrowingSpecification, AssertStdExceptionTypeAndMessage) {
    InvocationResult result = spec->invoking(&Test::throwDerived).should.raise.exception(Test::MyException());
    CHECK(result.wasSuccess());
}
