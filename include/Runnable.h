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

#ifndef RUNNABLE_H_
#define RUNNABLE_H_

#include "Reporter.h"
#include "SpecResult.h"
#include <string>

namespace CppSpec {

class Reporter;

/**
 * Interface of a runnable specification object
 */
class Runnable {
public:
	virtual ~Runnable() {}

	/**
	 * Execute behaviors of a specification
	 */
	virtual SpecResult operator()() = 0;

	/**
	 * Get the name of the specification.
	 */
	virtual const std::string& getName() const = 0;

	/**
	 * Get count of behaviors
	 */
	virtual unsigned int getBehaviorCount() const = 0;
};

}

#endif /*RUNNABLE_H_*/
