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
#include "CuteReporter.h"
#include "StubRunnable.h"
#include <iostream>
#include <sstream>
#include <string>

using CppSpec::CuteReporter;

struct CuteReporterTest {
    CuteReporterTest() {
		stream = new std::stringstream();
		coutBuf = std::cout.rdbuf();
		std::cout.rdbuf(stream->rdbuf());
		reporter = new CppSpec::CuteReporter();
    }

    ~CuteReporterTest() {
		delete reporter;
		std::cout.rdbuf(coutBuf);
		delete stream;
    }

	CuteReporter* reporter;
	std::stringstream* stream;
	std::streambuf* coutBuf;
	StubRunnable specification;
};

TEST_FIXTURE(CuteReporterTest, specificationStarted) {
	reporter->specificationStarted(specification);
	CHECK_EQUAL("\n#beginning TestSpec 1\n", stream->str());
}

TEST_FIXTURE(CuteReporterTest, specificationEnded) {
	std::string name("TestSpec");
	reporter->specificationEnded(name);
	CHECK_EQUAL("\n#ending TestSpec\n", stream->str());
}

TEST_FIXTURE(CuteReporterTest, behaviourStarted) {
	std::string name("emptyStackShouldThrowExceptionOnPop");
	reporter->behaviorStarted(name);
	CHECK_EQUAL("\n#starting emptyStackShouldThrowExceptionOnPop\n", stream->str());
}

TEST_FIXTURE(CuteReporterTest, behaviorSucceeded) {
	std::string name("emptyStackShouldThrowExceptionOnPop");
	reporter->behaviorStarted(name);
	stream->str("");
	reporter->behaviorSucceeded();
	CHECK_EQUAL("\n#success emptyStackShouldThrowExceptionOnPop OK\n", stream->str());
	CHECK(!reporter->anyBehaviorFailed());
}

TEST_FIXTURE(CuteReporterTest, behaviorFailed) {
	std::string name("emptyStackShouldThrowExceptionOnPop");
	reporter->behaviorStarted(name);
	stream->str("");
	reporter->behaviorFailed("File.cpp", 135, "expected 1, but was 2");
	CHECK_EQUAL("\n#failure emptyStackShouldThrowExceptionOnPop File.cpp:135 expected 1, but was 2\n", stream->str());
	CHECK(reporter->anyBehaviorFailed());
}
