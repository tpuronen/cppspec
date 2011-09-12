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

#include "DummyReporter.h"
#include "SpecResult.h"
#include <boost/typeof/typeof.hpp>

DummyReporter::DummyReporter() : success(0), failed(0) {
}

DummyReporter::~DummyReporter() {
}

void DummyReporter::addSpecification(const CppSpec::SpecResult& results) {
    for (BOOST_AUTO(it, results.firstBehavior()); it != results.lastBehavior(); ++it) {
        it->passed ? ++success : ++failed;
    }
}

bool DummyReporter::anyBehaviorFailed() const {
	return failed != 0;
}
