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

#ifndef DUMMYREPORTER_H_
#define DUMMYREPORTER_H_

#include "Reporter.h"
#include "Runnable.h"

class DummyReporter : public CppSpec::Reporter {
public:
	DummyReporter();
	~DummyReporter();

public: // from Reporter
	void specificationStarted(const CppSpec::Runnable& /*specName*/);
	void behaviorStarted(const std::string& /*behavior*/);
	void behaviorSucceeded();
	void behaviorFailed(const std::string&, int, const std::string& description);
	void specificationEnded(const std::string& /*specName*/);

public:
	int succes;
	int failed;
	std::string lastFailureDescription;
};

#endif /*DUMMYREPORTER_H_*/
