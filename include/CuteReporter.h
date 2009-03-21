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

#ifndef CUTEREPORTER_H_
#define CUTEREPORTER_H_

#include "Reporter.h"
#include <string>

namespace CppSpec {

class CuteReporter : public Reporter {
public:
	CuteReporter();
	virtual ~CuteReporter();

public: // from Reporter
	void specificationStarted(const Runnable& specification);
	void behaviorStarted(const std::string& behavior);
	void behaviorSucceeded();
	void behaviorFailed(const std::string& file, int line, const std::string& description);
	void specificationEnded(const std::string& specName);

private:
    CuteReporter(const CuteReporter&);
    CuteReporter& operator=(const CuteReporter&);

private:
	std::string currentBehavior;
};

}

#endif /* CUTEREPORTER_H_ */
