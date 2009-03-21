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

#ifndef REPORTER_H_
#define REPORTER_H_

#include <string>

namespace CppSpec {

class Runnable;

class Reporter {
public:
	virtual ~Reporter() {}

public:
	virtual void specificationStarted(const Runnable& specification) = 0;
	virtual void behaviorStarted(const std::string& behavior) = 0;
	virtual void behaviorSucceeded() = 0;
	virtual void behaviorFailed(const std::string& file, int line, const std::string& description) = 0;
	virtual void specificationEnded(const std::string& specName) = 0;
};

}

#endif /*REPORTER_H_*/
