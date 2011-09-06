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

#ifndef CPPSPEC_H_
#define CPPSPEC_H_

#include "Specification.h"
#include "Behavior.h"
#include "SpecRunner.h"

#define REGISTER_BEHAVIOUR(Specification, BehaviorName) \
	static CppSpec::Behavior<Specification> BehaviorName##Instance(this, &Specification::BehaviorName, #BehaviorName); \
	behaviors.push_back(&BehaviorName##Instance);

#define specify(...) \
	specifyImpl(__FILE__, __LINE__, __VA_ARGS__)

#define CPPSPEC_MAIN \
	int main(int argc, const char* argv[]) { \
        CppSpec::SpecRunner runner(argc, argv); \
		return runner.runSpecifications(); \
	}


#endif /*CPPSPEC_H_*/
