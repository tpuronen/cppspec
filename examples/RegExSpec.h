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

#ifndef REGEXSPEC_H_
#define REGEXSPEC_H_

#include "CppSpec.h"
#include <string>

class RegExSpec : public CppSpec::Specification<std::string, RegExSpec> {
public:
	explicit RegExSpec() {
		REGISTER_BEHAVIOUR(RegExSpec, shouldContainPattern);
		REGISTER_BEHAVIOUR(RegExSpec, shouldNotContainPattern);
		REGISTER_BEHAVIOUR(RegExSpec, shouldMatchPattern);
	}

	std::string* createContext() {
		std::string* context = new std::string("abc.def@ghi.jkl");
		return context;
	}

	void shouldContainPattern() {
		std::string pattern("def@");
		specify(context(), should.contain(pattern));
	}

	void shouldNotContainPattern() {
		std::string pattern("defa");
		specify(context(), not should.contain(pattern));
	}

	void shouldMatchPattern() {
		const std::string regexp("^([0-9a-zA-Z]([-.\\w]*[0-9a-zA-Z])*@([0-9a-zA-Z][-\\w]*[0-9a-zA-Z]\\.)+[a-zA-Z]{2,9})$");
		specify(context(), should.match(regexp));
	}
} regExSpec;

#endif /*REGEXSPEC_H_*/
