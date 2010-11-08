/*
 * Copyright 2008 Timo Puronen
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

#include "CuteReporter.h"
#include "Runnable.h"
#include <iostream>

namespace CppSpec {

CuteReporter::CuteReporter() : currentBehavior(), failOccured(false) {
}

CuteReporter::~CuteReporter() {
}

void CuteReporter::specificationStarted(const Runnable& specification) {
	std::cout << "\n#beginning " << specification.getName() << " " << specification.getBehaviorCount() << std::endl;
}

void CuteReporter::behaviorStarted(const std::string& behavior) {
	std::cout << "\n#starting " << behavior << std::endl;
	currentBehavior = behavior;
}

void CuteReporter::specificationEnded(const std::string& specName) {
	std::cout << "\n#ending " << specName << std::endl;
}

void CuteReporter::behaviorSucceeded() {
	std::cout << "\n#success " << currentBehavior << " OK" << std::endl;
}

void CuteReporter::behaviorFailed(const std::string& file, int line, const std::string& description) {
	std::cout << "\n#failure " << currentBehavior << " " << file << ":" << line << " " << description << std::endl;
	failOccured = true;
}

bool CuteReporter::anyBehaviorFailed() const {
	return failOccured;
}

}
