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
	virtual void start() = 0;
	virtual std::string stop() = 0;
};

}

#endif /* TIMER_H_ */
