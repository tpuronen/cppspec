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

#ifndef STUBRUNNABLE_H_
#define STUBRUNNABLE_H_

#include "Runnable.h"

static std::string stubName = "TestSpec";

class StubRunnable : public CppSpec::Runnable {
public:
    CppSpec::SpecResult operator()() {CppSpec::SpecResult result("stub"); return result;}
	const std::string& getName() const {return stubName;}
	unsigned int getBehaviorCount() const {return 1;}
};


#endif /* STUBRUNNABLE_H_ */
