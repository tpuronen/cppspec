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

#ifndef FUNCTOR_H_
#define FUNCTOR_H_

#include <string>

namespace CppSpec {

class Functor {
public:
	virtual void operator()() = 0;
	virtual const std::string& getName() const = 0;
};

}

#endif /* FUNCTOR_H_ */
