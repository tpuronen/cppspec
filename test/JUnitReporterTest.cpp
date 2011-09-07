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
#include "JUnitReporter.h"
#include "SpecResult.h"

class JUnitReporterTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        stream = new std::stringstream();
		coutBuf = std::cout.rdbuf();
		std::cout.rdbuf(stream->rdbuf());
        
		reporter = new CppSpec::JUnitReporter();
    }
    
    virtual void TearDown() {
        delete reporter;
        std::cout.rdbuf(coutBuf);
        delete stream;
    }
    
    CppSpec::JUnitReporter* reporter;
	std::stringstream* stream;
	std::streambuf* coutBuf;
};

TEST_F(JUnitReporterTest, oneSuiteWithOnePass) {
    CppSpec::SpecResult result("TestSpec");
    result.addPass("Behavior", "00.010000");
    result.setDuration("00.010000");
    reporter->addSpecification(result);
    const std::string& log(stream->str());

    EXPECT_NE(std::string::npos, log.find("tests=\"1\""));
    EXPECT_NE(std::string::npos, log.find("<testsuite failures=\"0\" name=\"TestSpec\" tests=\"1\" time=\"00.010000\""));
    EXPECT_NE(std::string::npos, log.find("<testcase classname=\"TestSpec\" name=\"Behavior\" time=\"00.010000\""));
    EXPECT_FALSE(reporter->anyBehaviorFailed());
}

TEST_F(JUnitReporterTest, oneFail) {
    CppSpec::SpecResult result("TestSpec");
    result.addFail("Behavior", "00.010000", "Foo.cpp", 10, "An exception occured");
    reporter->addSpecification(result);
    const std::string& log(stream->str());
    
    EXPECT_NE(std::string::npos, log.find("failures=\"1\""));
    EXPECT_TRUE(reporter->anyBehaviorFailed());
}
