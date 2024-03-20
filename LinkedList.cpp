#include "LinkedList.h"
#include <iostream>

using namespace std;

LinkedList::LinkedList()
{
	head = nullptr;
	//customerCount = 0; 
}

LinkedList::~LinkedList()
{
	ListNode* nodePtr; // To traverse the list
	ListNode* nextNode; // To point to next node

	// Position nodePtr at the head of the list
	nodePtr = head;

	// While nodePtr is not at the end of the list
	while (nodePtr != nullptr)
	{
		// Save a pointer to the next node
		nextNode = nodePtr->next;

		// Delete the current node
		delete nodePtr;

		// Postition nodePtr at the next node
		nodePtr = nextNode;
	}
}

void LinkedList::insertNode(std::string inputName, std::string inputService)
{
	ListNode* newNode; // A new node
	ListNode* nodePtr; // To traverse the list

	// Gets time in seconds since Jan 1970
	time_t timeVariable = time(0);

	// Time structure pointer
	time_t* timeVarPtr = &timeVariable;

	// Date Time structure pointer
	struct tm dateTime;

	// Gets current local time and returns it to dateTime tm structure
	localtime_s(&dateTime, timeVarPtr);

	// Allocate a new node and initialize member data
	newNode = new ListNode;
	newNode->name = inputName;
	newNode->serviceRequired = inputService;
	newNode->sequenceNumber = getSequenceNumber();
	newNode->next = nullptr;
	newNode->year = dateTime.tm_year + 1900;
	newNode->month = dateTime.tm_mon + 1;
	newNode->day = dateTime.tm_mday;
	newNode->hour = dateTime.tm_hour;
	newNode->minute = dateTime.tm_min;

	// If there are no nodes in the list make newNode the first node
	if (!head)
	{
		head = newNode;
		newNode->next = nullptr;
	}
	else // Otherwise insert newNode at beginning of the list
	{
		// Position nodePtr at the head of the list
		nodePtr = head;

		// If the new node is the 1st in the list, insert it before all other nodes
		head = newNode;
		newNode->next = nodePtr;
	}
}

LinkedList::ListNode* LinkedList::searchList(std::string nameToFind)
{

	ListNode* nodePtr; // to traverse the list

	//if the list is empty is empty, do nothing
	if (!head)
		return nullptr;

	// Determine if the first node is the node being searched for
	if (head->name == nameToFind)
	{
		nodePtr = head;
		return nodePtr;
	}
	else
	{
		// Initialize nodePtr to head of list
		nodePtr = head;

		// Skip all nodes whose name member is not equal to nameToFind
		while (nodePtr != nullptr && nodePtr->name != nameToFind)
		{
			nodePtr = nodePtr->next;
		}
	}

	return nullptr;
}

// Deletes the last node in the list
bool LinkedList::deleteNode()
{

	ListNode* nodePtr; // To traverse the list
	ListNode* previousNode = nullptr; // To point to previous node

	// If there are not items in the list return false
	if (!head)
	{
		return false;
	}

	nodePtr = head;
	
	// If their is only one node in the list, delete that node and return true
	if (nodePtr->next == nullptr)
	{
		delete head;
		head = nullptr;
	}
	// Find and delete the last node and return true
	else
	{
		// Until the second to last item of the list is found
		while (nodePtr->next->next != nullptr)
		{
			nodePtr->next;
		}

		// Delete last node
		delete (nodePtr->next);

		// Make the new last node a nullptr
		nodePtr->next = nullptr;
	}

	return true;
}

// Deletes node with name equal to input
bool LinkedList::deleteNode(std::string nameToDelete)
{
	
	ListNode* nodePtr; // to traverse the list
	ListNode* previousNode = nullptr; // to point to previous node

	//if the list is empty is empty, do nothing
	if (!head)
		return false;

	// Determine if the first node is the nameToDelete
	if (head->name == nameToDelete)
	{
		nodePtr = head->next;
		delete head;
		head = nodePtr;
		
		return true;
	}
	else
	{
		// Initialize nodePtr to head of list
		nodePtr = head;

		// Skip all nodes whose name member is not equal to nameToDelete
		while (nodePtr != nullptr && nodePtr->name != nameToDelete)
		{
			previousNode = nodePtr;
			nodePtr = nodePtr->next;
		}

		// If nodePtr is not at the end of the list, link the previousNode to the 
		// after nodePtr, then delete nodePtr
		if (nodePtr)
		{
			previousNode->next = nodePtr->next;
			delete nodePtr;
			
			return true;
		}
	}

	return false;
}

void LinkedList::listAll()
{
	ListNode* nodePtr; // To traverse through list

	// Position nodePtr at the head of the list
	nodePtr = head;

	// While nodePtr points to a node, traverse the list
	while (nodePtr)
	{


		// Prints sequenceNumber and name
		cout << nodePtr->sequenceNumber << "           " << nodePtr->name << "          ";

		// Sets formating for date and time
		cout << setw(2) << setfill('0');

		// Prints date, time, and serviceRequired
		cout << nodePtr->month << '/' << nodePtr->day << '/' << nodePtr->year << ' ' << nodePtr->hour << ':' << nodePtr->minute << "     " << nodePtr->serviceRequired << endl;

		// Move to next node
		nodePtr = nodePtr->next;
	}

	std::cout << "\n";
}

// Increments the sequence counter everytime a newNode is created
unsigned int LinkedList::getSequenceNumber()
{	
	return ++currentSequence;
}

// Initializes currentSequence to 0
unsigned int LinkedList::currentSequence = 0;