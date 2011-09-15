/*
 * Copyright 2007, 2008 Timo Puronen
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

#ifndef SPECIFICATION_H_
#define SPECIFICATION_H_

#include "SpecificationBase.h"
#include "Reporter.h"
#include "ShouldType.h"
#include "ContextHolder.h"
#include "SpecResult.h"
#include "BoostTimer.h"
#include <boost/bind.hpp>

/**
 * MSVC++ does not support not keyword.
 */
#ifdef _WIN32
#define not !
#endif

namespace CppSpec {

/**
 * Specification base class.
 * @param Context the class under test.
 * @param Derived the concrete specification class as in curiously recurring template pattern.
 */
template <class Context, class Derived>
class Specification : public SpecificationBase<Derived>, public ContextHolder<Context> {
public:
	explicit Specification() : should(*this), contextPtr(NULL) {
	}

	virtual ~Specification() {
		static_cast<Derived*>(this)->destroyContext();
	}

	/**
	 * Create the context object. Can be overridden in derived specification class.
	 */
	Context* createContext() {
		return new Context;
	}

	/**
	 * Destroy the context object. Can be overridden in derived specification class.
	 */
	void destroyContext() {
		delete contextPtr;
		contextPtr = NULL;
	}

public: // Expectations, these are used through specify-macro
	template<class F>
	InvokingType invoking(F f) {
		InvokingType invocation(boost::bind(f, &context()));
		return invocation;
	}

	template<class F, class Arg1>
	InvokingType invoking(F f, Arg1 arg1) {
		InvokingType invocation(boost::bind(f, &context(), arg1));
		return invocation;
	}

	template<class F, class Arg1, class Arg2>
	InvokingType invoking(F f, Arg1 arg1, Arg2 arg2) {
		InvokingType invocation(boost::bind(f, &context(), arg1, arg2));
		return invocation;
	}

	template<class F, class Arg1, class Arg2, class Arg3>
	InvokingType invoking(F f, Arg1 arg1, Arg2 arg2, Arg3 arg3) {
		InvokingType invocation(boost::bind(f, &context(), arg1, arg2, arg3));
		return invocation;
	}

	template<class F, class Arg1, class Arg2, class Arg3, class Arg4>
	InvokingType invoking(F f, Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4) {
		InvokingType invocation(boost::bind(f, &context(), arg1, arg2, arg3, arg4));
		return invocation;
	}

	template<class F, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5>
	InvokingType invoking(F f, Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5) {
		InvokingType invocation(boost::bind(f, &context(), arg1, arg2, arg3, arg4, arg5));
		return invocation;
	}

public: // from Runnable
	SpecResult operator()() {
        SpecResult results(SpecificationBase<Derived>::getName());
		const int count(SpecificationBase<Derived>::behaviors.size());
        boost::shared_ptr<Timer> timer = Timer::create();
        timer->start();
		for(int i = 0; i < count; ++i) {
			contextPtr = static_cast<Derived*>(this)->createContext();
            Functor& behavior = *(SpecificationBase<Derived>::behaviors[i]);
            SpecificationBase<Derived>::executeBehavior(behavior, results);
			static_cast<Derived*>(this)->destroyContext();
		}
        results.setDuration(timer->stop());
        return results;
	}

public: // Vocabulary
	Context& context() {
		return *contextPtr;
	}

	ShouldType<Context> should;

protected:
	Context* contextPtr;

private:
	Specification(const Specification&);
	Specification& operator=(const Specification&);
};

template<class Derived>
class Specification<void, Derived> : public SpecificationBase<Derived>, public ContextHolder<void> {
public:
    Specification() {
    }

    ~Specification() {
    }

public: // from Runnable
    SpecResult operator()() {
        SpecResult results(SpecificationBase<Derived>::getName());
		const int count(SpecificationBase<Derived>::behaviors.size());
        for(int i = 0; i < count; ++i) {
            Functor& behavior = *(SpecificationBase<Derived>::behaviors[i]);
            SpecificationBase<Derived>::executeBehavior(behavior, results);
        }
        return results;
    }

public:
    ShouldType<void> should;

private:
    Specification(const Specification&);
    Specification& operator=(const Specification&);
};

}
#endif /*SPECIFICATION_H_*/
