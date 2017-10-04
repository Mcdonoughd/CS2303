#include "eventQueue.h"
#include<list>
#include "Event.h"

eventQueue::eventQueue(){
	head = NULL;
}
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
bool eventQueue::Exists(int data){
	// Create a temp pointer
	Event *tmp = head;
	// No nodes
	if ( tmp == NULL ){
		return false;}

	// Last node of the list
	if ( tmp->Next() == NULL ) {
		return false;
	}
	else {
		// Parse thru the nodes

		while (tmp != NULL){
			if ( tmp->getactiontime() == data ) {break;}
			if ( tmp->Next() == NULL ) {
				return false;
			}
			tmp = tmp->Next();
		};
		// Delete the current node
		delete tmp;
		return true;
	}
}
/**
 * Print the contents of the list
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
 */
void eventQueue::Delete(int data) {

	// Create a temp pointer
	Event *tmp = head;

	// No nodes
	if ( tmp == NULL )
		return;

	// Last node of the list
	if ( tmp->Next() == NULL ) {
		delete tmp;
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
		delete tmp;
	}
}

Event* eventQueue::getEvent(int i){
	// Create a temp pointer
	Event *tmp = head;
	if(this->Exists(i)){
		do {
			if ( tmp->getactiontime() == i ) break;
				tmp = tmp->Next();
		} while ( tmp != NULL );
		return tmp;
	}
	else {
		// Parse thru the nodes
		return NULL;
	}
}


eventQueue::~eventQueue(){

}
