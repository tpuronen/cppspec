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
#include "SpecResult.h"
#include <cctype>

namespace CppSpec {
    
SpecDoxReporter::SpecDoxReporter(OutputStream& outputStream) : outputStream(outputStream), anyFailed(false) {
}

SpecDoxReporter::~SpecDoxReporter() {
}

void SpecDoxReporter::addSpecification(const SpecResult &results) {
    int pass(0);
    int fail(0);
    outputStream << results.getSpecificationName() << ":" << "\n";
    for (std::vector<SpecResult::BehaviorResult>::const_iterator it = results.firstBehavior(); it != results.lastBehavior(); it++) {
        outputStream << "  " << formatCamelCasedWordsAndUnderlines(it->name);
        if (it->passed) {
            outputStream << "\n";
            ++pass;
        } else {
            outputStream << ", " << it->message << " in " << it->file << ":" << it->line << "\n";
            ++fail;
        }
    }
    anyFailed = anyFailed || (fail != 0);
    outputStream << results.getSpecificationName() << " executed, " << pass << " of " << pass + fail << " behaviors passed and " << fail << " failed." << "\n" << "\n";
}

bool SpecDoxReporter::anyBehaviorFailed() const {
    return anyFailed;
}
    
std::string SpecDoxReporter::formatCamelCasedWordsAndUnderlines(const std::string& text) {
	std::string result;
	std::string::iterator it = (const_cast<std::string&>(text)).begin();
	while(it != text.end()) {
		if(::isupper(*it)) {
			result.append(" ");
		}
		if('_' == *it) {
			result.append(" ");
		} else {
		  result += ::tolower(*it);
    }
		++it;
	}
	return result;
}

}
