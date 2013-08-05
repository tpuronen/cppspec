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

#ifndef CONSOLEREPORTER_H_
#define CONSOLEREPORTER_H_

#include "Reporter.h"
#include <iostream>

namespace CppSpec {

class OutputStream;

class SpecDoxReporter : public Reporter {
public:
	explicit SpecDoxReporter(OutputStream& outputStream);
	~SpecDoxReporter();

    void addSpecification(const SpecResult& results);
    bool anyBehaviorFailed() const;

private:
	std::string formatCamelCasedWordsAndUnderlines(const std::string& text);

private:
    SpecDoxReporter(const SpecDoxReporter&);
    SpecDoxReporter& operator=(const SpecDoxReporter&);

private:
    OutputStream& outputStream;
    bool anyFailed;
};

}

#endif /*CONSOLEREPORTER_H_*/
