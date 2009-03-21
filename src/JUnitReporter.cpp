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
#include <iostream>
#include <boost/typeof/typeof.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "FileOutputStream.h"
#include "ConsoleOutputStream.h"

namespace CppSpec {

JUnitReporter::JUnitReporter()
: specificationName(), behaviorName(), behaviorResults(), createLogFiles(false), reportDirectory() {
}

JUnitReporter::JUnitReporter(const std::string& reportDirectory)
: specificationName(), behaviorName(), behaviorResults(), createLogFiles(true), reportDirectory(reportDirectory) {
}

JUnitReporter::~JUnitReporter() {
}

void JUnitReporter::specificationStarted(const Runnable& specification) {
	specificationName = specification.getName();
	behaviorResults.clear();
	timer->startSpecification();
}

void JUnitReporter::behaviorStarted(const std::string& behavior) {
	behaviorName = behavior;
	timer->startBehavior();
}


void JUnitReporter::behaviorSucceeded() {
	behaviorResults.push_back(Result(behaviorName, "", true, timer->durationFromBehaviorStart(), "", 0));
}

void JUnitReporter::behaviorFailed(const std::string& file, int line, const std::string& description) {
	behaviorResults.push_back(Result(behaviorName, description, false, timer->durationFromBehaviorStart(), file, line));
}

void JUnitReporter::specificationEnded(const std::string& /*specName*/) {
	int pass(0);
	int fails(0);
	OutputStream* output = createOutputStream();

	calculateResults(pass, fails);

	std::string time = currentTime();

	(*output) << "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>" << "\n";
	(*output) << "<testsuite failures=\"" << fails << "\" name=\"" << specificationName << "\" tests=\"" << pass + fails << "\" time=\"" << timer->durationFromSpecificationStart() << "\" timestamp=\"" << time << "\">" << "\n";
	printSpecResults(*output);
	(*output) << "</testsuite>" << "\n";

	delete output;
}

OutputStream* JUnitReporter::createOutputStream() {
	if(createLogFiles) {
		return new FileOutputStream(reportDirectory, specificationName);
	}

	return new ConsoleOutputStream;
}

void JUnitReporter::calculateResults(int& pass, int& fails) {
	for(BOOST_AUTO(it, behaviorResults.begin()); it != behaviorResults.end(); ++it) {
		it->pass ? ++pass : ++fails;
	}
}

void JUnitReporter::printSpecResults(OutputStream& output) {
	for(BOOST_AUTO(it, behaviorResults.begin()); it != behaviorResults.end(); ++it) {
		output << "<testcase classname=\"" << specificationName << "\" name=\"" << it->behaviorName << "\" time=\"" << it->duration << "\"";
		if(!it->pass) {
			output << ">" << "\n";
			output << "<error message=\"" << it->reason << " at " << it->file << ":" << it->line << "\" />" << "\n";
			output << "</testcase>" << "\n";
		}
		else {
			output << " />" << "\n";
		}
	}
}

std::string JUnitReporter::currentTime() {
    boost::posix_time::ptime currentTime = boost::posix_time::second_clock::local_time();
    return boost::posix_time::to_simple_string(currentTime);
}

}
