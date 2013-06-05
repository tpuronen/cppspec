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

#ifndef SHOULDTYPE_H_
#define SHOULDTYPE_H_

#include "BeType.h"
#include "Expectation.h"
#include "Matcher.h"

#include <algorithm>
#include <string>

namespace CppSpec {

template<typename Context>
class ShouldType {
public:
	explicit ShouldType(ContextHolder<Context>& creator)
		: be(creator), have(*this), contextHolder(creator) {
	}

public: // Interface
	/**
	 * Specify that context must implement the given interface.
	 */
	template<class Base>
	bool implement() {
		Base* base = dynamic_cast<Base*>(&(contextHolder.context()));
		return base != NULL;
	}

	template<typename T>
	bool element(const T& t) {
		return std::find(contextHolder.context().begin(), contextHolder.context().end(), t) != contextHolder.context().end();
	}

	template<class Iterator>
	bool elements(Iterator begin, Iterator end) {
		return std::search(contextHolder.context().begin(), contextHolder.context().end(), begin, end) != contextHolder.context().end();
	}

	template<typename T>
	Expectation<T> equal(const T& t) {
		return Expectation<T>(t);
	}

    template<typename T>
    FloatExpectation<T> almostEqual(const T& t, const T& r) {
        return FloatExpectation<T>(t, r);
    }

	Matcher contain(const std::string& regex) {
		return Matcher(regex, Matcher::Search);
	}

	Matcher match(const std::string& regex) {
		return Matcher(regex, Matcher::Match);
	}

private:
    ShouldType(const ShouldType&);
    ShouldType& operator=(const ShouldType&);

public: // Members
	BeType<Context> be;
	ShouldType<Context>& have;

private:
	ContextHolder<Context>& contextHolder;
};

template<>
class ShouldType<void> {
public:
    ShouldType() : have(*this) {
    }

    template<typename T>
    Expectation<T> equal(const T& t) {
        return Expectation<T>(t);
    }

    template<typename T>
    FloatExpectation<T> almostEqual(const T& t, const T& r) {
        return FloatExpectation<T>(t, r);
    }

    Matcher contain(const std::string& regex) {
        return Matcher(regex, Matcher::Search);
    }

    Matcher match(const std::string& regex) {
        return Matcher(regex, Matcher::Match);
    }

public:
    ShouldType<void>& have;

private:
    ShouldType(const ShouldType&);
    ShouldType& operator=(const ShouldType&);
};

}

#endif /*SHOULDTYPE_H_*/
