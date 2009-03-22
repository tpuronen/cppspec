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

#include "UnitTest++.h"
#include "SpecRunner.h"
#include "OutputStreamStub.h"
#include "Reporter.h"
#include "JUnitReporter.h"
#include "SpecDoxReporter.h"
#include <boost/type_traits.hpp>
#include <typeinfo>

#include <iostream>

using CppSpec::SpecRunner;
using CppSpec::Reporter;
using CppSpec::JUnitReporter;
using CppSpec::SpecDoxReporter;

template<class ExpectedReporterType>
void checkThatGivenReporterIsCreated(SpecRunner& specRunner) {
    OutputStreamStub output;
    Reporter* reporter = specRunner.createReporter(output);
    ExpectedReporterType* expectedReporterType = dynamic_cast<ExpectedReporterType*>(reporter);
    CHECK(expectedReporterType != NULL);
    delete reporter;
}

TEST(SpecDoxReporterIsReturnedByDefault) {
    char* args[] = {"test"};
    SpecRunner specRunner(1, args);
    checkThatGivenReporterIsCreated<SpecDoxReporter>(specRunner);
}

TEST(CreateReporterReturnsJUnitReporterIfGivenInArguments) {
    char* args[] = {"test", "-o", "junit"};
    SpecRunner specRunner(3, args);
    checkThatGivenReporterIsCreated<JUnitReporter>(specRunner);
}
