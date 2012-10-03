# CppSpec

CppSpec is a behavior driven development (BDD) framework for C++. BDD is a refinement of TDD which turns the focus from writing the tests to the process of defining the behavior of the software using tests. You can read more about BDD from www.behaviour-driven.org.

CppSpec is licensed under Apache License, version 2.0.</p> 
              
## Using CppSpec
 
To define behavior of your class you need to create a specifications for different states of your class. Specification is created by deriving from CppSpec::Specification class. Expectations for the behavior are written using specify method.
 
### Basic validation 
                                                    
    specify(should.be.empty()); 
    specify(not should.be.empty());
    specify(context().count(), should.equal(1));  
                                             
### Exception handling

Exceptions are tested by calling a method which should throw an exception and verifying the result. For example:

    specify(invoking(&Stack<int>::pop).should.raise.exception<std::exception>());

### Containers

If the context implements iterator interface, you can specify that context should contain either unique items or sequences using contain keyword.

    specify(should.contain("key"));
    specify(should.contain(sequence.begin(), sequence.end()));

### Regular expressions 

    specify(context().asString(), should.match(pattern)); 

## Building

Building CppSpec requires CMake and Boost. See CMake documentation for more information about building using CMake.