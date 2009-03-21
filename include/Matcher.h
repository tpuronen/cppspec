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

#ifndef MATCHER_H_
#define MATCHER_H_

#include "CppSpecConfig.h"
#include <string>

namespace CppSpec {

class CppSpec_EXPORT Matcher {
public:
	enum Mode {Search, Match};
	explicit Matcher(const std::string& expression, Mode mode);
    Matcher(const Matcher& that);

public:
	bool operator()(const std::string& text) const;
	Matcher& operator !();
	Mode getMode() const;
	const std::string& getExpression() const;

private:
    Matcher& operator=(const Matcher&);

private:
	const std::string expression;
	Mode mode;
	bool reversed;
};

}

#endif /*MATCHER_H_*/
