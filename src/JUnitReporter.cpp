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

#include "JUnitReporter.h"
#include "Runnable.h"
#include "FileOutputStream.h"
#include "ConsoleOutputStream.h"
#include "SpecResult.h"
#include <iostream>
#include <algorithm>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/typeof/typeof.hpp>

namespace CppSpec {

JUnitReporter::JUnitReporter()
: createLogFiles(false), reportDirectory(), failOccured(false) {
}

JUnitReporter::JUnitReporter(const std::string& reportDirectory)
: createLogFiles(true), reportDirectory(reportDirectory), failOccured(false) {
}

JUnitReporter::~JUnitReporter() {
}
    
void JUnitReporter::addSpecification(const SpecResult& results) {
    const int fails(results.failCount());
    const int pass(results.passCount());
    failOccured = (fails != 0) || failOccured;
    OutputStream* output = createOutputStream(results.getSpecificationName());
    (*output) << "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>" << "\n";    
    (*output) << "<testsuite failures=\"" << fails << "\" name=\"" << results.getSpecificationName() << "\" tests=\"" 
        << pass + fails << "\" time=\"" << results.getDuration() << "\" timestamp=\"" << currentTime() << "\">" << "\n";
	
    for (BOOST_AUTO(it, results.firstBehavior()); it != results.lastBehavior(); ++it) {
        (*output)   << "<testcase classname=\""
                    << results.getSpecificationName()
                    << "\" name=\""
                    << it->name
                    << "\" time=\""
                    << it->duration << "\"";
        if (it->passed) {
            (*output) << " />" << "\n";
        } else {
            (*output) << ">" << "\n";
			(*output) << "<error message=\"" << it->message << " at " << it->file << ":" << it->line << "\" />" << "\n";
			(*output) << "</testcase>" << "\n";
        }
    }
    
    (*output) << "</testsuite>" << "\n";
    delete output;
}

bool JUnitReporter::anyBehaviorFailed() const {
    return failOccured;
}
    
OutputStream* JUnitReporter::createOutputStream(const std::string& specificationName) {
	if(createLogFiles) {
		return new FileOutputStream(reportDirectory, specificationName);
	}

	return new ConsoleOutputStream;
}

std::string JUnitReporter::currentTime() {
    using namespace boost::posix_time;
    return to_simple_string(second_clock::local_time());
}

}
