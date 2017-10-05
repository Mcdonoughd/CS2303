#include "eventQueue.h"
#include<list>
#include "Event.h"

eventQueue::eventQueue(){
	head = NULL;
}
/** Gets the size of the Event Queue
 * @return the size of the event queue as an integer
 *
 */
int eventQueue::getsize(){
	// Create a temp pointer
	Event *tmp = head;
	// No nodes
	if ( tmp == NULL ){
		return 0;}

	// Last node of the list
	if ( tmp->Next() == NULL ) {
		return 1;
	}
	else {
		// Parse thru the nodes
		int i =0;
		while (tmp != NULL){
			if ( tmp->Next() == NULL ) {
				return i+=1;
			}
			tmp = tmp->Next();
			i++;
		};
		// Delete the current node
		delete tmp;
		return i;
	}
}
/** Returns whether something in the event queue exists or not
 * @param data the data
 * @return integer representing whether something exists or not
 */
int eventQueue::Exists(int data){
	// Create a temp pointer
	Event *tmp = this->head;
	int i = 0; //event counter
	// No nodes
	if ( tmp == NULL ){
		return i;}

	// Last node of the list if only two nodes
	if(tmp->getactiontime() == data){
		i++;
	}
	else if( tmp->next == NULL ) {
		//delete tmp;
		return i;
	}
	else {
		// Parse thru the nodes
		while (tmp != NULL){
			if ( tmp->getactiontime() == data ) {i++;}
			if ( tmp->next == NULL ) {
				//delete tmp;
				return i;
			}
			tmp = tmp->next;
		};
		// Delete the current node
		//delete tmp;

	}
	return i;
}
/**
 * Print the contents of the queue.
 */
void eventQueue::Print() {

	// Temp pointer
	Event *tmp = head;

	// No nodes
	if ( tmp == NULL ) {
		printf("EMPTY\n");
		return;
	}

	// One node in the list
	if ( tmp->Next() == NULL ) {
		printf("%d --> NULL\n",tmp->getactiontime());
	}
	else {
		// Parse and print the list
		do {
			printf("%d --> ",tmp->getactiontime() );
			tmp = tmp->Next();
		}
		while ( tmp != NULL );
		printf("NULL\n");
	}
}

/**
 * Append a node to the linked list given data
 */
/*
void eventQueue::Append(int data) {

	// Create a new node
	Event* newNode = new Event();
	newNode->setactiontime(data);
	newNode->SetNext(NULL);

	// Create a temp pointer
	Event *tmp = head;

	if ( tmp != NULL ) {
		// Nodes already present in the list
		// Parse to end of list
		while ( tmp->Next() != NULL ) {
			tmp = tmp->Next();
		}

		// Point the last node to the new node
		tmp->SetNext(newNode);
	}
	else {
		// First node in the list
		head = newNode;
	}
}
/** Adds an event to the eventQueue
 * @param node the Event to be added
 */
void eventQueue::Append(Event* node) {

	//set node's next to 0
	node->SetNext(NULL);

	// Create a temp pointer
	Event *tmp = head;
	//Event *nodePtr = &node;
	if (tmp != NULL) {
		// Nodes already present in the list
		// Parse to end of list
		while (tmp->Next() != NULL ) {
			tmp = tmp->Next();
		}
		// Point the last node to the new node
		tmp->SetNext(node);
	}
	else {
		// First node in the list
		head = node;
		//this->Print();
	}
}

/**
 * Delete a node from the list
 * @param data Is the action time of customers
 * @return nothing as it deletes that node.
 */
void eventQueue::Delete(int data) {

	// Create a temp pointer
	Event *tmp = head;

	// No nodes
	if ( tmp == NULL )
		return;

	// Last node of the list
	if ( tmp->Next() == NULL ) {
		//delete tmp;
		head = NULL;
	}
	else {
		// Parse thru the nodes
		Event *prev;
		do {
			if ( tmp->getactiontime() == data ) break;
			prev = tmp;
			tmp = tmp->Next();
		} while ( tmp != NULL );

		// Adjust the pointers
		prev->SetNext(tmp->Next());

		// Delete the current node
		//delete tmp;
	}
}

/** Gets an event
 * @param actiontime is the time that an event takes to start and finish.
 * @return the event itself
 */
Event* eventQueue::getEvent(int actiontime){
	// Create a temp pointer
	Event *tmp = head;

	while ( tmp != NULL ){
		if ( tmp->getactiontime() == actiontime ) {break;}
		tmp = tmp->next;
	}
	return tmp;

}


eventQueue::~eventQueue(){

}
