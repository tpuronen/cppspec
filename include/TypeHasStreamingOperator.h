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

#ifndef TYPEHASSTREAMINGOPERATOR_H_
#define TYPEHASSTREAMINGOPERATOR_H_

#include <iostream>
#include <boost/type_traits.hpp>

namespace CppSpec {

typedef char yes;
typedef char (&no)[2];

struct tag{};

struct any {
	template <class T> any(const T&);
};

tag operator << (const any&, const any&);

no test(tag);

template <class T>
yes test(const T&);

template <class T>
struct TypeHasStreamingOperator {
	static typename boost::remove_cv<typename boost::remove_reference<T>::type>::type const& x;
	static const bool result = sizeof(test(std::cout << x)) == sizeof(yes);
};

template<bool v>
struct CheckIf {
	enum { value = v };
};

}

#endif /* TYPEHASSTREAMINGOPERATOR_H_ */
