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
#include "SpecRunner.h"
#include "OutputStreamStub.h"
#include "SpecificationRegistry.h"
#include "SpecDoxReporter.h"
#include "JUnitReporter.h"
#include "CuteReporter.h"
#include "Runnable.h"

using CppSpec::SpecRunner;
using CppSpec::SpecificationRegistry;
using CppSpec::SpecDoxReporter;
using CppSpec::JUnitReporter;
using CppSpec::CuteReporter;
using CppSpec::Runnable;
using CppSpec::Reporter;

namespace CppSpec {
    class SpecRunnerTestAccessor {
    public:
        template<class ExpectedReporterType>
        void checkThatGivenReporterIsCreated(SpecRunner& specRunner) {
            OutputStreamStub output;
            Reporter* reporter = specRunner.createReporter(output);
            ExpectedReporterType* expectedReporterType = dynamic_cast<ExpectedReporterType*>(reporter);
            EXPECT_TRUE(expectedReporterType != NULL);
            delete reporter;
        }
    };
}
using CppSpec::SpecRunnerTestAccessor;

SpecRunner* createSpecRunner() {
    const char* args[] = {"test"};
	SpecificationRegistry::instance().clear();
    return new SpecRunner(1, args);
}

TEST(SpecRunnerTest, SpecDoxReporterIsReturnedByDefault) {
	SpecRunner* specRunner = createSpecRunner();
    SpecRunnerTestAccessor().checkThatGivenReporterIsCreated<SpecDoxReporter>(*specRunner);
	delete specRunner;
}

TEST(SpecRunnerTest, CreateReporterReturnsJUnitReporterIfGivenInArguments) {
    const char* args[] = {"test", "-o", "junit", "--report-dir", "foo"};
    SpecRunner specRunner(5, args);
    SpecRunnerTestAccessor().checkThatGivenReporterIsCreated<JUnitReporter>(specRunner);
}

TEST(SpecRunnerTest, CreateReporterReturnsJUnitReporterWithoutLogFilesIfGivenInArguments) {
    const char* args[] = {"test", "-o", "junit", "--no-logs"};
    SpecRunner specRunner(4, args);
    SpecRunnerTestAccessor().checkThatGivenReporterIsCreated<JUnitReporter>(specRunner);
}

TEST(SpecRunnerTest, CreateReporterReturnsCuteReporterIfGivenInArguments) {
    const char* args[] = {"test", "-o", "cute"};
    SpecRunner specRunner(3, args);
    SpecRunnerTestAccessor().checkThatGivenReporterIsCreated<CuteReporter>(specRunner);
}

TEST(SpecRunnerTest, ReturnZeroIfNoTestsExecuted) {
    SpecRunner* specRunner = createSpecRunner();
	EXPECT_EQ(0, specRunner->runSpecifications());
	delete specRunner;
}

struct DummyRunnable : public Runnable {
	DummyRunnable() : name("dummy") {}
	void operator()(Reporter* reporter) {
		reporter->specificationStarted(*this);
		reporter->behaviorStarted("failing dummy");
		reporter->behaviorFailed(__FILE__, __LINE__, "dummy fail");
		reporter->specificationEnded(name);
	}
	const std::string& getName() const {return name;}
	unsigned int getBehaviorCount() const {return 0;}
	const std::string name;
};

TEST(SpecRunnerTest, ReturnOneIfATestFails) {
	SpecRunner* specRunner = createSpecRunner();
	DummyRunnable runnable;
	SpecificationRegistry::instance().addSpecification(&runnable);
	EXPECT_EQ(1, specRunner->runSpecifications());
	delete specRunner;
}
