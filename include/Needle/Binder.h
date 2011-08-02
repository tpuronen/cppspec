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
    InterfaceNotBoundToImplementationException(const std::string& description) : std::runtime_error(description) {}
};

class Binder {
public:
    static Binder& instance() {
        static Binder binder;
        return binder;
    }

    template<typename Interface, typename Implementation>
    void bind(Implementation* implementation) {
        bind<Interface>(implementation, "");
    }
    
    template<typename Interface, typename Implementation>
    void bind(Implementation* implementation, const std::string& id) {
        bound[createName<Interface>(id)] = boost::shared_ptr<Interface>(implementation);
    }

    template<typename Interface>
    boost::shared_ptr<Interface> get() {
        return get<Interface>("");
    }
    
    template<typename Interface>
    boost::shared_ptr<Interface> get(const std::string& id) {
        try {
            std::map<std::string, boost::any>::iterator it = bound.find(createName<Interface>(id));
            if (it == bound.end()) {
                throw boost::bad_any_cast();
            }
            return boost::any_cast<boost::shared_ptr<Interface> >(it->second);
        } catch (boost::bad_any_cast& e) {
            std::string description("Implementation for ");
            description += NeedleTypeNameResolver().getTypename<Interface>();
            description += " is not bound.";
            throw InterfaceNotBoundToImplementationException(description);
        }
    }

    void deleteBindings() {
        bound.clear();
    }

private:
    template<typename Interface>
    std::string createName(const std::string& id) {
        std::string name(typeid(Interface).name());
        name += "-" + id;
        return name;
    }
    
private:
    Binder() {}

private:
    std::map<std::string, boost::any> bound;
};

}

#endif /* BINDER_H_ */
