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

#include "SpecDoxReporter.h"
#include "Runnable.h"
#include "ConsoleOutputStream.h"
#include <cctype>

namespace CppSpec {

SpecDoxReporter::SpecDoxReporter(OutputStream& outputStream) : outputStream(outputStream), count(0), failedCount(0), successCount(0), failOccured(false) {
}

SpecDoxReporter::~SpecDoxReporter() {
}

void SpecDoxReporter::specificationStarted(const Runnable& specification) {
	outputStream << specification.getName() << ":" << "\n";
	resetCounters();
	}

void SpecDoxReporter::behaviorStarted(const std::string& behavior) {
	outputStream << "  " << separateCamelCasedWords(behavior);
	++count;
	}

void SpecDoxReporter::behaviorSucceeded() {
	outputStream << "\n";
	++successCount;
}

void SpecDoxReporter::behaviorFailed(const std::string& file, int line, const std::string& description) {
	outputStream << ", " << description << " in " << file << ":" << line << "\n";
	++failedCount;
	failOccured = true;
}

void SpecDoxReporter::specificationEnded(const std::string& specName) {
	outputStream << specName << " executed, " << successCount << " of " << count << " behaviors passed and " << failedCount << " failed." << "\n" << "\n";
}

bool SpecDoxReporter::anyBehaviorFailed() const {
	return failOccured;
}

void SpecDoxReporter::resetCounters() {
	count = 0;
	failedCount = 0;
	successCount = 0;
}

std::string SpecDoxReporter::separateCamelCasedWords(const std::string& text) {
	std::string result;
	std::string::iterator it = (const_cast<std::string&>(text)).begin();
	while(it != text.end()) {
		if(::isupper(*it)) {
			result.append(" ");
		}
		result += ::tolower(*it);
		++it;
	}
	return result;
}

}
