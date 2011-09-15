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

#ifndef TIMER_H_
#define TIMER_H_

#include <string>
#include <boost/shared_ptr.hpp>

namespace CppSpec {

class Timer {
public:
    static boost::shared_ptr<Timer> create();
	virtual ~Timer() {}
	virtual void start() = 0;
	virtual std::string stop() = 0;
};

}

#endif /* TIMER_H_ */
