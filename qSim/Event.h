/*
 * Event.h
 *  Created on: Oct 8, 2017
 *  Authors: Daniel McDonough and Surya Vadivazhagu
 */
//
#ifndef EVENT_H_
#define EVENT_H_

class Event {
public:
	int time;
	int duration;

	static int id;
	int ID;

	virtual void action();
	Event();
	void getTime() const;
	virtual ~Event();
};

#endif /* EVENT_H_ */
