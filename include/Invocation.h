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

#ifndef INVOCATION_H_
#define INVOCATION_H_

#include <boost/call_traits.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/function.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/bind.hpp>
#include "TypeHasStreamingOperator.h"
#include "TypeNameResolver.h"
#include "InvocationResult.h"

namespace CppSpec {

template<class Expected>
class Invocation {
private:
    class NonOccuringException {
    };

    typedef typename boost::mpl::if_c<boost::is_base_of<std::exception, Expected>::value,
        NonOccuringException,
        std::exception>::type StandardOrNonThrownExceptionType;

public:
    explicit Invocation(boost::function<void()> invocation) : invocation(invocation) {}

    InvocationResult invoke() {
        return internalInvoke(boost::lambda::constant(true), 0);
    }

    InvocationResult invoke(Expected expected) {
        return internalInvoke(boost::lambda::_1 == expected, expected);
    }

private:
    template<class T, class E>
    InvocationResult internalInvoke(T expectedEquals, E expected) {
        InvocationResult result;
        try {
            invocation();
        }
        catch(typename boost::call_traits<Expected>::reference occured) {
            if(expectedEquals(occured)) {
                result.setSuccess();
                return result;
            }
            result.setFailure(exceptionValuesNotMatchedMessage(expected, occured));
            return result;
        } catch(typename boost::add_reference<StandardOrNonThrownExceptionType>::type occured) {
            result.setFailure(standardExceptionThrown(occured));
            return result;
        } catch(...) {
            result.setFailure(wrongExceptionThrownMessage());
            return result;
        }
        result.setFailure(noExceptionThrownMessage());
        return result;
    }

    std::string noExceptionThrownMessage() const {
        std::string description("Expected ");
        description += TypeNameResolver().getTypename<Expected>();
        description += " but no exception was thrown";
        return description;
    }

    std::string wrongExceptionThrownMessage() const {
        std::string description("Expected ");
        description += TypeNameResolver().getTypename<Expected>();
        description += " but unknown type was thrown";
        return description;
    }

    std::string standardExceptionThrown(std::exception& occured) {
        std::string description("Expected ");
        description += TypeNameResolver().getTypename<Expected>();
        description += " but ";
        description += TypeNameResolver().getTypename(occured);
        description += "[";
        description += occured.what();
        description += "] was thrown";
        return description;
    }

    std::string standardExceptionThrown(NonOccuringException&) {
        throw std::logic_error("standardExceptionThrown(NonOccuringException&) called");
    }

    template<class T, class U>
    std::string exceptionValuesNotMatchedMessage(T expected, U occured) const {
        std::string description("Expected ");
        const std::string exceptionTypeName(TypeNameResolver().getTypename<T>());
        description += exceptionTypeName;
        description += "[";
        description += toString(expected);
        description += "] but ";
        description += exceptionTypeName;
        description += "[";
        description += toString(occured);
        description += "] was thrown";
        return description;
    }

    template<class T>
    std::string toString(T t) const {
        return toStringImpl<T>(t, CheckIf<TypeHasStreamingOperator<T>::result>());
    }

    template<class T>
    std::string toStringImpl(T t, CheckIf<true>) const {
        try {
            return boost::lexical_cast<std::string>(t);
        } catch(boost::bad_lexical_cast&) {
            return "** unstreamable class **";
        }
    }

    template<class T>
    std::string toStringImpl(T t, CheckIf<false>) const {
        return "** unstreamable class **";
    }

private:
    Invocation(const Invocation&);
    Invocation& operator=(const Invocation&);

private:
    boost::function<void()> invocation;
};

}

bool operator==(const std::exception& lhs, const std::exception& rhs);
std::ostream& operator<<(std::ostream& out, const std::exception& e);

#endif /* INVOCATION_H_ */
