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

#ifndef INVOKINGTYPE_H_
#define INVOKINGTYPE_H_

#include <boost/function.hpp>
#include "Invocation.h"

namespace CppSpec {

class InvokingType {
public:
	template<class Invocation>
	explicit InvokingType(Invocation invocation) : should(*this), raise(*this), invocation(invocation) {
	}

	virtual ~InvokingType() {
	}

	InvokingType(const InvokingType& that) : should(*this), raise(*this), invocation(that.invocation) {
	}

	template<class T>
	InvocationResult exception() {
	    return Invocation<T>(invocation).invoke();
	}

	template<class T>
	InvocationResult exception(T expected) {
        return Invocation<T>(invocation).invoke(expected);
	}

public:
	InvokingType& should;
	InvokingType& raise;

private:
	boost::function<void()> invocation;

private:
	InvokingType& operator=(const InvokingType&);
};

}

#endif /* INVOKINGTYPE_H_ */
