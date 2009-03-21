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


#ifndef NEEDLE_TYPENAMERESOLVER_H_
#define NEEDLE_TYPENAMERESOLVER_H_

#include <boost/type_traits.hpp>
#include <typeinfo>
#ifdef __GNUC__
#include <cxxabi.h>
#endif

namespace Needle {

class NeedleTypeNameResolver {
public:
    template<class T>
	std::string getTypename() const {
#ifdef __GNUC__
		int status;
		char* demangledName = abi::__cxa_demangle(typeid(T).name(), NULL, NULL, &status);
		std::string demangled(demangledName);
		free(demangledName);
		return demangled;
#else
		return typeid(T).name();
#endif
	}

    template<class T>
    std::string getTypename(T& t) {
#ifdef __GNUC__
        int status;
        char* demangledName = abi::__cxa_demangle(typeid(t).name(), NULL, NULL, &status);
        std::string demangled(demangledName);
        free(demangledName);
        return demangled;
#else
        return typeid(t).name();
#endif
    }
};

}

#endif /* NEEDLE_TYPENAMERESOLVER_H_ */
