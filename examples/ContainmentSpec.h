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

#include "CppSpec.h"

#include <vector>

class VectorSpec : public CppSpec::Specification<std::vector<int>, VectorSpec> {
public:
	VectorSpec() {
		REGISTER_BEHAVIOUR(VectorSpec, shouldContainOne);
		REGISTER_BEHAVIOUR(VectorSpec, shouldNotContainThree);
		REGISTER_BEHAVIOUR(VectorSpec, shouldContainSequence);
		REGISTER_BEHAVIOUR(VectorSpec, shouldNotContainSeq123);
	}

	std::vector<int>* createContext() {
		std::vector<int>* context = new std::vector<int>();
		context->push_back(6);
		context->push_back(1);
		context->push_back(7);
		context->push_back(8);
		context->push_back(2);
		return context;
	}

	void shouldContainOne() {
		specify(should.have.element(1));
	}

	void shouldNotContainThree() {
		specify(not should.have.element(3));
	}

	void shouldContainSequence() {
		std::vector<int> vector;
		vector.push_back(7);
		vector.push_back(8);
		specify(should.have.elements(vector.begin(), vector.end()));
	}

	void shouldNotContainSeq123() {
		std::vector<int> vector;
		vector.push_back(1);
		vector.push_back(2);
		vector.push_back(3);
		specify(not should.have.elements(vector.begin(), vector.end()));
	}
} vectorSpec;

