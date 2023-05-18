#include "PriorityQueue.h"
#include "ShortTest.h"
#include <assert.h>
#include <iostream>

bool rel(TPriority p1, TPriority p2) {
	if (p1 <= p2) {
		return true;
	}
	else {
		return false;
	}
}




void testAll() { //call each function and see if it exists
	PriorityQueue pq(rel);
	
	assert(pq.isEmpty() == true);
	
	//adaugam 5, 3, 10, 2, 12 -> rezultat: 2, 3, 5, 10, 12
	pq.push(5, 5);
	assert(pq.top().first == 5);
	assert(pq.top().second == 5);
	pq.push(3, 3);
	assert(pq.top().first == 3);
	assert(pq.top().second == 3);
	pq.push(10, 10);
	assert(pq.top().first == 3);
	assert(pq.top().second == 3);
	pq.push(2, 2);
	assert(pq.top().first == 2);
	assert(pq.top().second == 2);
	pq.push(12, 12);
	assert(pq.top().first == 2);
	assert(pq.top().second == 2);
	assert(pq.isEmpty() == false);
	assert(pq.pop().second == 2);
	assert(pq.top().second == 3);
	assert(pq.pop().second == 3);
	assert(pq.top().second == 5);
	assert(pq.pop().second == 5);
	assert(pq.top().second == 10);
	assert(pq.pop().second == 10);
	assert(pq.top().second == 12);
	assert(pq.pop().second == 12);
	assert(pq.isEmpty() == true);
}

void testChangePriority() {
    std::cout<<"bravo!"<<endl;
    PriorityQueue pq(rel);
    pq.push(5, 5);
    pq.push(3, 3);
    pq.push(10, 10);
    pq.push(2, 2);
    pq.push(12, 12);

    // change priority of existing element
    pq.changePriority(5, 1);
    assert(pq.top().second == 2);
    pq.changePriority(12, 4);
    assert(pq.top().second == 2);
    assert(pq.pop().second == 2);
    assert(pq.top().second == 3);

    // change priority of non-existing element
    pq.changePriority(7, 8);
    assert(pq.top().second == 3);

    // change priority to the same value
    pq.changePriority(3, 3);
    assert(pq.top().second == 3);

    //change priority of the last element in the queue
    pq.changePriority(12, 6);
    assert(pq.top().second == 3);
    assert(pq.pop().second == 3);
    assert(pq.top().second == 5);
    assert(pq.pop().second == 5);
    assert(pq.top().second == 10);
    assert(pq.pop().second == 10);
    assert(pq.top().second == 12);
    assert(pq.pop().second == 12);
    assert(pq.isEmpty() == true);
    std::cout<<"bravo!"<<endl;
}
