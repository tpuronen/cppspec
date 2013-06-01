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

#ifndef EXPECTATION_H_
#define EXPECTATION_H_

#include <boost/call_traits.hpp>

namespace CppSpec {

template<typename T>
class Expectation {
public:
	explicit Expectation(const T& expected) : expected(expected), reversed(false) {
	}

	Expectation(const Expectation& rhs) : expected(rhs.expected), reversed(rhs.reversed) {
	}

	template<class U>
	bool equals(const U& actual) const {
		bool result = (expected == actual);
		return result ^ reversed;
	}

	Expectation& operator !() {
		reversed = !reversed;
		return *this;
	}

	const T& operator()() const {
		return expected;
	}

private:
	Expectation& operator =(const Expectation&);

private:
	const T& expected;
	bool reversed;
};

template<typename T>
class FloatExpectation {
public:
    explicit FloatExpectation(const T& expected, const T& tolerance) :
        expected(expected),
        tolerance(tolerance),
        reversed(false)
    {
    }

    FloatExpectation(const FloatExpectation& rhs) :
        expected(rhs.expected),
        tolerance(rhs.tolerance),
        reversed(rhs.reversed) {
    }

    template<class U>
    bool almostEquals(const U& actual) const {
        bool result = (upper() > actual) && (lower() < actual);
        return result ^ reversed;
    }

    FloatExpectation& operator !() {
        reversed = !reversed;
        return *this;
    }

    const T& operator()() const {
        return expected;
    }

    const T upper() const {
        return expected + tolerance;
    }
    const T lower() const {
        return expected - tolerance;
    }

private:
    FloatExpectation& operator =(const FloatExpectation&);

private:
    const T& expected;
    const T& tolerance;
    bool reversed;

};


}

#endif /* EXPECTATION_H_ */
