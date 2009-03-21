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
#include "DummyReporter.h"

using CppSpec::Specification;

class EmptyTestSpec : public Specification<void, EmptyTestSpec> {
};

SUITE(EmptySpecification) {
    TEST(hasName) {
        EmptyTestSpec spec;
        CHECK_EQUAL("type", spec.getName());
    }

    TEST(hasCountOfZero) {
        EmptyTestSpec spec;
        CHECK_EQUAL(0, spec.getBehaviorCount());
    }
};

class SpecWithBehaviours : public Specification<void, SpecWithBehaviours> {
public:
    SpecWithBehaviours() {
        REGISTER_BEHAVIOUR(SpecWithBehaviours, passingBehaviour);
        REGISTER_BEHAVIOUR(SpecWithBehaviours, failingBehaviour);
        REGISTER_BEHAVIOUR(SpecWithBehaviours, intsShouldEqual);
        REGISTER_BEHAVIOUR(SpecWithBehaviours, intsAreInequal);
        REGISTER_BEHAVIOUR(SpecWithBehaviours, findsSubstring);
        REGISTER_BEHAVIOUR(SpecWithBehaviours, substringIsNotFound);
        REGISTER_BEHAVIOUR(SpecWithBehaviours, stringsDoNotMatch);
    }

    void passingBehaviour() {
        specify(true);
    }

    void failingBehaviour() {
        specify(false);
    }

    void intsShouldEqual() {
        specify(2, should.equal(2));
    }

    void intsAreInequal() {
        specify(1, should.equal(2));
    }

    void findsSubstring() {
        specify("silence", should.contain("si"));
    }

    void substringIsNotFound() {
        specify("silence", should.contain("is"));
    }

    void stringsDoNotMatch() {
        specify("silence", should.match("noise"));
    }
};

struct SpecWithBehavioursTest {
    SpecWithBehavioursTest() {
        reporter = new DummyReporter();
        spec = new SpecWithBehaviours();
    }

    ~SpecWithBehavioursTest() {
        delete spec;
        delete reporter;
    }

    DummyReporter* reporter;
    SpecWithBehaviours* spec;
};

SUITE(SpecificationWithBehaviors) {
    TEST_FIXTURE(SpecWithBehavioursTest, hasCount) {
        CHECK_EQUAL(7, spec->getBehaviorCount());
    }

    TEST_FIXTURE(SpecWithBehavioursTest, canCallContextForVoid) {
        spec->context();
    }

    TEST_FIXTURE(SpecWithBehavioursTest, behavioursAreExecuted) {
        (*spec)(reporter);
        CHECK_EQUAL(3, reporter->succes);
        CHECK_EQUAL(4, reporter->failed);
    }
}
