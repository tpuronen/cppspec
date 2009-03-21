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

#ifndef INTERFACESPEC_H_
#define INTERFACESPEC_H_

#include "CppSpec.h"

class Interface {
public:
	virtual ~Interface() {}
	virtual void Foo() = 0;
};

class Implementation : public Interface {
public:
	explicit Implementation() {}
	virtual ~Implementation() {}

	void Foo() {}
};

class ImplementationSpec : public CppSpec::Specification<Implementation, ImplementationSpec> {
public:
	ImplementationSpec() {
		REGISTER_BEHAVIOUR(ImplementationSpec, implementsInterface);
	}

	void implementsInterface() {
		specify(should.implement<Interface>());
	}
} interfaceSpec;

#endif /*INTERFACESPEC_H_*/
