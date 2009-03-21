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
#include "JUnitReporter.h"
#include "Timer.h"
#include "StubRunnable.h"
#include <iostream>
#include <sstream>
#include <string>

struct JUnitReporterTest {
    JUnitReporterTest() {
		stream = new std::stringstream();
		coutBuf = std::cout.rdbuf();
		std::cout.rdbuf(stream->rdbuf());

		reporter = new CppSpec::JUnitReporter();
		std::string behaviorName("Behavior");
		reporter->specificationStarted(specification);
		reporter->behaviorStarted(behaviorName);
		name = new std::string("Specification");
    }

    ~JUnitReporterTest() {
		delete name;
		delete reporter;
		std::cout.rdbuf(coutBuf);
		delete stream;
    }

    CppSpec::JUnitReporter* reporter;
	std::stringstream* stream;
	std::streambuf* coutBuf;
	std::string* name;
	StubRunnable specification;
};

SUITE(JUnitReporter) {
    TEST_FIXTURE(JUnitReporterTest, oneSuite) {
        reporter->behaviorSucceeded();
        reporter->specificationEnded(*name);
        const std::string& log(stream->str());

        CHECK(log.find("tests=\"1\"") != std::string::npos);
        CHECK(log.find("<testsuite failures=\"0\" name=\"TestSpec\" tests=\"1\" time=\"00.010000\"") != std::string::npos);
        CHECK(log.find("<testcase classname=\"TestSpec\" name=\"Behavior\" time=\"00.010000\"") != std::string::npos);
    }

    TEST_FIXTURE(JUnitReporterTest, onePass) {
        reporter->behaviorSucceeded();
        reporter->specificationEnded(*name);
        CHECK(stream->str().find("failures=\"0\"") != std::string::npos);
    }

    TEST_FIXTURE(JUnitReporterTest, oneFail) {
        reporter->behaviorFailed("Foo.cpp", 10, "An exception occured");
        reporter->specificationEnded(*name);
        CHECK(stream->str().find("failures=\"1\"") != std::string::npos);
    }
}
