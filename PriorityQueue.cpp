
#include "PriorityQueue.h"
#include <exception>
using namespace std;

///constructor
/// \param r
///complexity: Θ(1) worst, average and best
PriorityQueue::PriorityQueue(Relation r)
{
    this->head = nullptr;
    this->tail = nullptr;
    this-> r = r;
}

/// pushes an element with priority to the queue
/// \param e
/// \param p
///complexity: O(n), worst case: Θ(n), average case:Θ(n), best case: Θ(1)
void PriorityQueue::push(TElem e, TPriority p)
{
	Node* newNode = new Node;
    //newNode->elem = make_pair(e, p);
    newNode->elem.first = e;
    newNode->elem.second = p;
    newNode->next = nullptr;    // it will be the last node in the queue


    if (this->head == nullptr)
    {   // if the queue is empty, the new node becomes the head and tail
        this->head = newNode;
        this->tail = newNode;
        newNode->prev = nullptr;    // because it is the first node in the queue
    }
    else
    {   //insert a new node based on the priority
        Node* current = this->head;
        while (current != nullptr && !this->r(p, current->elem.second))
        {
            // we start at the head of the queue and move forward through the nodes until we find a node with a lower priority or until we reach the end of the queue
            current = current->next;
        }

        if (current == this->head)
        {   //insert at the front of the queue
            newNode->prev = nullptr;
            newNode->next = this->head;
            this->head->prev = newNode;
            this->head = newNode;
        }
        else if (current == nullptr)
        {   //insert at the end of the queue
            newNode->next = nullptr;
            newNode->prev = this->tail;
            this->tail->next = newNode;
            this->tail = newNode;
        }
        else
        {   //insert in the middle of the queue
            newNode->prev = current->prev;
            newNode->next = current;
            current->prev->next = newNode;
            current->prev = newNode;
        }
    }
}


/// returns the element with the highest priority with respect to the order relation
/// throws exception if the queue is empty
/// \return
///complexity: Θ(1) worst, average and best
Element PriorityQueue::top() const
{
	if (isEmpty())
    {
        throw exception();
    }
    else
        return head->elem;
}


/// removes and returns the element with the highest priority
/// throws exception if the queue is empty
/// \return
///complexity: Θ(1) worst, average and best
Element PriorityQueue::pop()
{

    if (isEmpty())
    {
        throw exception();
    }
    else
    {   Node* current = head;
        Element elem = current->elem;
        head = head->next;
        if (head == nullptr)
        {
            tail = nullptr;
        }
        else
        {
            head->prev = nullptr;
        }
        delete current;
        return elem;
    }

}

///verifies if the PriorityQueue is empty
/// \return
///complexity: Θ(1) worst, average and best
bool PriorityQueue::isEmpty() const
{
	if (this->head == nullptr && this->tail == nullptr)
        return true;
	return false;
}

///destructor
///complexity: Θ(n) worst, average and best
PriorityQueue::~PriorityQueue()
{
	Node* current = this->head;
    while (current != nullptr)
    {
        Node* next = current->next;
        delete current;
        current = next;
    }
    this->head = nullptr;
    this->tail = nullptr;
}



/// changes the priority of an element
/// \param e
/// \param p
///complexity: O(n), worst case: Θ(n), average case:Θ(n), best case: Θ(1)
void PriorityQueue::changePriority(TElem e, TPriority p)
{
    Node* current = this->head;
    while (current != nullptr && current->elem.first != e)
    {
        // we start at the head of the queue and move forward through the nodes until we find the node with the specified element
        current = current->next;
    }

    if (current == nullptr)
    {
        // if the element is not in the priority queue, we cannot change its priority, because it does not exist
        throw exception();
    }
    else
    {
        TPriority oldPriority = current->elem.second;
        current->elem.second = p;

        // check if we need to move the element to a new position in the queue
        if (this->r(p, oldPriority))
        {
            // the new priority is higher, so we need to move the element towards the front of the queue
            while (current->prev != nullptr && this->r(current->elem.second, current->prev->elem.second))
            {
                // move the node towards the front of the queue until it has a lower priority than its predecessor or reaches the front of the queue
                Node* prev = current->prev;
                Node* next = current->next;
                prev->next = next;
                if (next != nullptr)
                {
                    next->prev = prev;
                }
                current->prev = prev->prev;
                if (prev->prev == nullptr)
                {
                    // current is now the head of the queue
                    this->head = current;
                }
                else
                {
                    prev->prev->next = current;
                }
                current->next = prev;
                prev->prev = current;
            }
        }
        else if (this->r(oldPriority, p))
        {
            // the new priority is lower, so we need to move the element towards the back of the queue
            while (current->next != nullptr && this->r(current->next->elem.second, current->elem.second))
            {
                // move the node towards the back of the queue until it has a higher priority than its successor or reaches the end of the queue
                Node* prev = current->prev;
                Node* next = current->next;
                current->next = next->next;
                if (next->next == nullptr)
                {
                    // current is now the tail of the queue
                    this->tail = current;
                }
                else
                {
                    next->next->prev = current;
                }
                current->prev = next;
                next->next = current;
                next->prev = prev;
                if (prev != nullptr)
                {
                    prev->next = next;
                }
                else
                {
                    // current is now the head of the queue
                    this->head = next;
                }
            }
        }
    }
}




//preconditions: an existing queue
//postconditions: returns a new queue with a certain element with the new priority
//complexity: total: O(n), worst case Θ(n), average case Θ(n) best case: Θ(1)


//subalgorithm changePriority(e, p) is:
// Node^ current = head
// while current != NIL and current^elem.first != e
//	current = current.next
// end-while
//
// if current = NIL
// 	throw exceptiom
// end-if
// else
// TPriotiy oldPriority = current.elem.second
//  current.elem.second = p
// if r(p, oldPriority) then
//      while current.prev != NIL and r(current.elem.second, current.prev.elem.second
//      	Node^ prev = current.prev
//		Node^ next = current.next
//      	prev.next = next
// 			if next != NIL
//				next.prev=prev
//			end-if
//			current.prev = prev.prev;
//			if prev.prev = NIL
//			head = current
//			else prev.prev.next = current
//			current.next=prev
//			prev.prev = current
// end-if
// else if r(oldPriority, p) then
//	 while current.next != NIL and r(current.next.elem.second, current.elem.second)
// 	 Node^ prev = current.prev
//	 Node^ next = current.next
//      current.next = next.next
//		if next.next = NIL
//		tail = current
//	else
//		next.next.prev = current
//	current.prev = next
//	next.next = current
//	next.prev = prev
//	if prev != NIL
//		prev.next = next
// 	end-if
// 	else
//		head = next
// end-subalgorithm