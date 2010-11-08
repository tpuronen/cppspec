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
#include "SpecDoxReporter.h"
#include "StubRunnable.h"
#include "OutputStreamStub.h"
#include <string>

struct SpecDoxReporterTest {
    SpecDoxReporterTest() : outputStream(new OutputStreamStub), reporter(new CppSpec::SpecDoxReporter(*outputStream)) {
    }

    ~SpecDoxReporterTest() {
        delete reporter;
        reporter = NULL;
        delete outputStream;
        outputStream = NULL;
    }

    OutputStreamStub* outputStream;
    CppSpec::SpecDoxReporter* reporter;
	StubRunnable runnable;
};

SUITE(SpecDoxReporter) {
    TEST_FIXTURE(SpecDoxReporterTest, specificationStarted) {
        reporter->specificationStarted(runnable);
        CHECK_EQUAL("TestSpec:\n", outputStream->written());
    }

    TEST_FIXTURE(SpecDoxReporterTest, specificationEnded) {
        std::string name("TestSpec");
        reporter->specificationEnded(name);
        CHECK_EQUAL("TestSpec executed, 0 of 0 behaviors passed and 0 failed.\n\n", outputStream->written());
    }

    TEST_FIXTURE(SpecDoxReporterTest, behaviourEnded) {
        std::string name("emptyStackShouldThrowExceptionOnPop");
        reporter->behaviorStarted(name);
        CHECK_EQUAL("  empty stack should throw exception on pop", outputStream->written());
    }

    TEST_FIXTURE(SpecDoxReporterTest, behaviorSucceeded) {
        reporter->behaviorSucceeded();
        CHECK_EQUAL("\n", outputStream->written());
		CHECK(!reporter->anyBehaviorFailed());
    }

    TEST_FIXTURE(SpecDoxReporterTest, behaviorFailed) {
        reporter->behaviorFailed("Foo.cpp", 10, "expected 1, but was 0");
        CHECK_EQUAL(", expected 1, but was 0 in Foo.cpp:10\n", outputStream->written());
		CHECK(reporter->anyBehaviorFailed());
    }

	TEST_FIXTURE(SpecDoxReporterTest, failureInformationIsRetainedBetweenSpecifications) {
        reporter->behaviorFailed("Foo.cpp", 10, "expected 1, but was 0");
		reporter->specificationStarted(runnable);
		CHECK(reporter->anyBehaviorFailed());
	}
}
