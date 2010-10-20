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


#ifndef BINDER_H_
#define BINDER_H_

#include <map>
#include <stdexcept>
#include <boost/type_traits/is_base_and_derived.hpp>
#include <boost/any.hpp>
#include <boost/shared_ptr.hpp>
#include "NeedleTypeNameResolver.h"

namespace Needle {

class InterfaceNotBoundToImplementationException : public std::runtime_error {
public:
    InterfaceNotBoundToImplementationException(const std::string& description) :
        std::runtime_error("Implementation for " + description + " is not bound.") {}
};

class Binder {
public:
    static Binder& instance() {
        static Binder binder;
        return binder;
    }

    template<class Interface, class Implementation>
    void bind(Implementation* implementation) {
        bound[typeid(Interface).name()] = boost::shared_ptr<Interface>(implementation);
    }

    template<class Interface>
    boost::shared_ptr<Interface> get() {
        try {
            boost::shared_ptr<Interface> instance = boost::any_cast<boost::shared_ptr<Interface> >(bound.find(typeid(Interface).name())->second);
            return instance;
        } catch (boost::bad_any_cast&) {
            throw InterfaceNotBoundToImplementationException(NeedleTypeNameResolver().getTypename<Interface>());
        }
    }

    void deleteBindings() {
        bound.clear();
    }

private:
    Binder() {}

private:
    std::map<std::string, boost::any> bound;
};

}

#endif /* BINDER_H_ */
