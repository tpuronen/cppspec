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

#include "SpecificationRegistry.h"
#include <iostream>

namespace CppSpec {

SpecificationRegistry::SpecificationRegistry() : specifications() {
}

SpecificationRegistry& SpecificationRegistry::instance() {
	static SpecificationRegistry registry;
	return registry;
}

void SpecificationRegistry::addSpecification(Runnable* specification) {
	specifications.push_back(specification);
}

const SpecificationRegistry::SpecificationList& SpecificationRegistry::getSpecifications() const {
	return specifications;
}

void SpecificationRegistry::clear() {
	specifications.clear();
}

}
