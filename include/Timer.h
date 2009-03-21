/*
 * Timer.h
 *
 *  Created on: Jul 21, 2008
 *      Author: tpuronen
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <string>

namespace CppSpec {

class Timer {
public:
	virtual ~Timer() {}
	virtual void startSpecification() = 0;
	virtual void startBehavior() = 0;
	virtual std::string durationFromSpecificationStart() = 0;
	virtual std::string durationFromBehaviorStart() = 0;
};

}

#endif /* TIMER_H_ */
