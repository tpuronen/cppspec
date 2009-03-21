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

DummyReporter::DummyReporter() : succes(0), failed(0) {
}

DummyReporter::~DummyReporter() {
}

void DummyReporter::specificationStarted(const CppSpec::Runnable& /*specName*/) {
}

void DummyReporter::behaviorStarted(const std::string& /*behavior*/) {
}

void DummyReporter::behaviorSucceeded() {
	++succes;
}

void DummyReporter::behaviorFailed(const std::string&, int, const std::string& description) {
	++failed;
	lastFailureDescription = description;
}

void DummyReporter::specificationEnded(const std::string& /*specName*/) {
}
