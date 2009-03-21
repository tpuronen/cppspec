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

#include "CppSpec.h"

#include <vector>

template<typename ElementType>
class Stack {
public:
	explicit Stack() : elements() {}

	void push(ElementType element) {elements.push_back(element);}

	void pop() {
		if(elements.empty()) {
			throw std::exception();
		}

		elements.pop_back();
	}

	ElementType& top() {
		if(elements.empty()) {
			throw std::exception();
		}

		return elements.back();
	}

	int count() const {return elements.size();}
	bool empty() const {return elements.empty();}

	bool operator==(const Stack& rhs) const {
		return elements == rhs.elements;
	}

private:
	Stack(const Stack<ElementType>& rhs);
	Stack& operator =(const Stack<ElementType>& rhs);

private:
	std::vector<ElementType> elements;
};

class EmptyStackSpec : public CppSpec::Specification<Stack<int>, EmptyStackSpec> {
public:
	EmptyStackSpec() {
		REGISTER_BEHAVIOUR(EmptyStackSpec, poppingShouldRaiseException);
		REGISTER_BEHAVIOUR(EmptyStackSpec, backShouldRaiseException);
		REGISTER_BEHAVIOUR(EmptyStackSpec, stackIsEmpty);
		REGISTER_BEHAVIOUR(EmptyStackSpec, stackEqualsWithEmpty);
		REGISTER_BEHAVIOUR(EmptyStackSpec, countShouldBeZero);
	}

	void poppingShouldRaiseException() {
		specify(invoking(&Stack<int>::pop).should.raise.exception<std::exception>());
	}

	void backShouldRaiseException() {
		specify(invoking(&Stack<int>::top).should.raise.exception<std::exception>());
	}

	void stackIsEmpty() {
		specify(should.be().empty());
	}

	void stackEqualsWithEmpty() {
		Stack<int> anotherStack;
		specify(context(), should.equal(anotherStack));
	}

	void countShouldBeZero() {
		specify(context().count(), should.equal(0));
	}
} emptyStackSpec;

class StackWithElementsSpec : public CppSpec::Specification<Stack<int>, StackWithElementsSpec > {
public:
	StackWithElementsSpec() {
		REGISTER_BEHAVIOUR(StackWithElementsSpec, stackIsNotEmpty);
		REGISTER_BEHAVIOUR(StackWithElementsSpec, stackShouldReturnPushedObject);
		REGISTER_BEHAVIOUR(StackWithElementsSpec, stackShouldBeEmptyAfterPop);
		REGISTER_BEHAVIOUR(StackWithElementsSpec, stackShouldEqualWithItself);
		REGISTER_BEHAVIOUR(StackWithElementsSpec, countShouldBeOne);
	}

	Stack<int>* createContext() {
		Stack<int>* stack = new Stack<int>();
		stack->push(1);
		return stack;
	}

	void stackIsNotEmpty() {
		specify(not should.be().empty());
	}

	void stackShouldReturnPushedObject() {
		specify(context().top(), should.equal(1));
	}

	void stackShouldBeEmptyAfterPop() {
		context().pop();
		specify(should.be().empty());
	}

	void stackShouldEqualWithItself() {
		specify(context(), should.equal(context()));
	}

	void countShouldBeOne() {
		specify(context().count(), should.equal(1));
	}
} stackWithElementsSpec;
