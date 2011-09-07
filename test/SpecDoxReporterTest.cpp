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
#include "OutputStreamStub.h"
#include "SpecDoxReporter.h"
#include "SpecResult.h"

class SpecDoxReporterTest : public ::testing::Test {
protected:    
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
};

TEST_F(SpecDoxReporterTest, specificationRun) {
    CppSpec::SpecResult results("TestSpec");
    reporter->addSpecification(results);
    EXPECT_EQ("TestSpec:\nTestSpec executed, 0 of 0 behaviors passed and 0 failed.\n\n", outputStream->written());
}

TEST_F(SpecDoxReporterTest, specificationWithPassingBehavior) {
    CppSpec::SpecResult results("TestSpec");
    results.addPass("thisShouldPass", "00.010000");
    reporter->addSpecification(results);
    EXPECT_EQ("TestSpec:\n  this should pass\nTestSpec executed, 1 of 1 behaviors passed and 0 failed.\n\n", outputStream->written());
}

TEST_F(SpecDoxReporterTest, specificationWithFailingBehavior) {
    CppSpec::SpecResult results("TestSpec");
    results.addFail("thisShouldPass", "00.010000", "file.cpp", 10, "an exception occured");
    reporter->addSpecification(results);
    EXPECT_EQ("TestSpec:\n  this should pass, an exception occured in file.cpp:10\nTestSpec executed, 0 of 1 behaviors passed and 1 failed.\n\n", outputStream->written());
}
