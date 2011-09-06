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
#include "DummyReporter.h"
#include "Needle/Binder.h"

using CppSpec::Specification;

class EmptyTestSpec : public Specification<void, EmptyTestSpec> {
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

TEST(EmptySpecificationTest, HasName) {
    EmptyTestSpec spec;
    EXPECT_EQ(std::string("EmptyTestSpec"), spec.getName());
}

TEST(EmptySpecificationTest, HasCountOfZero) {
    EmptyTestSpec spec;
    EXPECT_EQ((size_t)0, spec.getBehaviorCount());
}

class SpecWithBehavioursTest : public ::testing::Test {
protected:
    void SetUp() {
        Needle::Binder::instance().bind<CppSpec::Reporter>(new DummyReporter());
        spec = new SpecWithBehaviours();
    }
    
    void TearDown() {
        delete spec;
        spec = NULL;
        Needle::Binder::instance().deleteBindings();
    }
    
    SpecWithBehaviours* spec;
};

TEST_F(SpecWithBehavioursTest, HasCount) {
    EXPECT_EQ((size_t)7, spec->getBehaviorCount());
}

TEST_F(SpecWithBehavioursTest, CanCallContextForVoid) {
    spec->context();
}

TEST_F(SpecWithBehavioursTest, BehaviorsAreExecuted) {
    (*spec)();
    Needle::Inject<CppSpec::Reporter> reporter;
    const DummyReporter& dreporter = dynamic_cast<const DummyReporter&>(*reporter);
    EXPECT_EQ(3, dreporter.success);
    EXPECT_EQ(4, dreporter.failed);
}
