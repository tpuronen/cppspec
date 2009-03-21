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

#include "Matcher.h"
#include <boost/regex.hpp>

namespace CppSpec {

Matcher::Matcher(const std::string& expression, Mode mode) : expression(expression), mode(mode), reversed(false) {
}

Matcher::Matcher(const Matcher& that) : expression(that.expression), mode(that.mode), reversed(that.reversed) {
}

Matcher& Matcher::operator !() {
	reversed = !reversed;
	return *this;
}

bool Matcher::operator()(const std::string& text) const {
    boost::regex exp(expression);
    bool result = (mode == Search) ? boost::regex_search(text, exp) : boost::regex_match(text, exp);
    return reversed ? !result : result;
}

Matcher::Mode Matcher::getMode() const {
	return mode;
}

const std::string& Matcher::getExpression() const {
	return expression;
}

}
