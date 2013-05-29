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

#ifndef SPECIFICATIONBASE_H_
#define SPECIFICATIONBASE_H_

#include "Runnable.h"
#include "TypeNameResolver.h"
#include "Expectation.h"
#include "SpecifyFailedException.h"
#include "SpecificationRegistry.h"
#include "Functor.h"
#include "TypeHasStreamingOperator.h"
#include "Matcher.h"
#include "InvokingType.h"
#include "SpecResult.h"
#include "Timer.h"
#include <vector>
#include <sstream>

namespace CppSpec {

template<class Derived>
class SpecificationBase : public Runnable {
public:
    SpecificationBase() : behaviors(), name(TypeNameResolver().getTypename<Derived>()) {
        SpecificationRegistry::instance().addSpecification(this);
    }

public:
    /**
     * Specify that condition must be fullfilled.
     */
    void specifyImpl(const std::string& file, int line, bool condition) {
        if(!condition) {
            throw SpecifyFailedException(file, line, "Expected true, but was false");
        }
    }

    /**
     * Specify that actual and expected must equal.
     */
    template<class T, class U>
    void specifyImpl(const std::string& file, int line, const T& actual, const Expectation<U>& expected) {
        if(!expected.equals(actual)) {
            std::stringstream message;
            writeInequalMessageToStream(message, actual, expected, CheckIf<TypeHasStreamingOperator<T>::result && TypeHasStreamingOperator<U>::result>());
            throw SpecifyFailedException(file, line, message.str());
        }
    }

    /**
     * Specify that actual and expected must almost equal (for floating point values).
     */
    template<class T, class U>
    void specifyImpl(const std::string& file, int line, const T& actual, const FloatExpectation<U>& expected) {
        if(!expected.almostEquals(actual)) {
            std::stringstream message;
            writeInequalMessageToStream(message, actual, expected, CheckIf<TypeHasStreamingOperator<T>::result && TypeHasStreamingOperator<U>::result>());
            throw SpecifyFailedException(file, line, message.str());
        }
    }

    void specifyImpl(const std::string& file, int line, const std::string& text, const Matcher& matcher) {
        if(!matcher(text)) {
            std::stringstream message;
            if(matcher.getMode() == Matcher::Search) {
                message << matcher.getExpression() << " was not found in " << text;
            } else {
                message << matcher.getExpression() << " did not match " << text;
            }
            throw SpecifyFailedException(file, line, message.str());
        }
    }

    void specifyImpl(const std::string& file, int line, const InvocationResult& invocation) {
        if(!invocation.wasSuccess()) {
            throw SpecifyFailedException(file, line, invocation.getDescription());
        }
    }

public: // from Runnable
    const std::string& getName() const {
        return name;
    }

    unsigned int getBehaviorCount() const {
        return behaviors.size();
    }

protected:
    void executeBehavior(Functor& behavior, SpecResult& results) {
        boost::shared_ptr<Timer> timer = Timer::create();
        try {
            timer->start();
            behavior();
            results.addPass(behavior.getName(), timer->stop());
        }
        catch (SpecifyFailedException& e) {
            results.addFail(behavior.getName(), timer->stop(), e.file, e.line, e.message);
        }
        catch (std::exception& e) {
            std::stringstream msg;
            msg << TypeNameResolver().getTypename(e) << "[" << e.what() << "] occured in " << behavior.getName();
            results.addFail(behavior.getName(), timer->stop(), msg.str());
        }
        catch (...) {
            std::stringstream msg;
            msg << "An exception occured in " << behavior.getName();
            results.addFail(behavior.getName(), timer->stop(), msg.str());
        }
    }

private:
    template<class T>
    void writeInequalMessageToStream(std::ostream& stream, const T& actual, const Expectation<T>& expected, CheckIf<true>) {
        stream << std::boolalpha << "expected " << expected() << ", but was " << actual;
    }

    template<class T, class U>
    void writeInequalMessageToStream(std::ostream& stream, const T& actual, const Expectation<U>& expected, CheckIf<true>) {
        stream << std::boolalpha << "expected " << expected() << ", but was " << actual;
    }

    template<class T>
    void writeInequalMessageToStream(std::ostream& stream, const T& actual, const Expectation<T>& expected, CheckIf<false>) {
        stream << "actual was not expected";
    }

    template<class T>
    void writeInequalMessageToStream(std::ostream& stream, const T& actual, const FloatExpectation<T>& expected, CheckIf<true>) {
        stream << std::boolalpha << "expected [" << expected.lower() << ", " << expected.upper() << "] but was " << actual;
    }

    template<class T, class U>
    void writeInequalMessageToStream(std::ostream& stream, const T& actual, const FloatExpectation<U>& expected, CheckIf<true>) {
        stream << std::boolalpha << "expected [" << expected.lower() << ", " << expected.upper() << "] but was " << actual;
    }

    template<class T>
    void writeInequalMessageToStream(std::ostream& stream, const T& actual, const FloatExpectation<T>& expected, CheckIf<false>) {
        stream << "actual was not expected";
    }

protected:
    typedef std::vector<Functor*> BehaviorList;
    BehaviorList behaviors;

private:
    SpecificationBase(const SpecificationBase&);
    SpecificationBase& operator=(const SpecificationBase&);

private:
    const std::string name;
};

}

#endif /* SPECIFICATIONBASE_H_ */
