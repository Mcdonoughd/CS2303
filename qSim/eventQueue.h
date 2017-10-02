#ifndef EVENTQUEUE_H_
#define EVENTQUEUE_H_
#include "Event.h"
class eventQueue{
private:
	Event *head;       //Node pointers to head and tail
public:
	eventQueue();
	void Print();
	int getsize();
	bool Exists(int time);
	void Append(int data);
	void Append(Event anevent);
	void Delete(int data);
	~eventQueue();
};
#endif
