
#include "PriorityQueue.h"
#include <exception>
using namespace std;


PriorityQueue::PriorityQueue(Relation r):head{NULL}, relation{r}
{}


void PriorityQueue::push(TElem e, TPriority p) {
	Element item(e,p);

    Node* newNode = new Node();
    newNode->data = item;
    newNode->next =NULL;

    if(this->head == NULL){
        this->head = newNode;
        this->head->next = NULL;
    }
    else {

        if (relation(newNode->data.second, this->head->data.second)) {
            newNode->next = head;
            this->head = newNode;
        } else {
            Node* iteratorNode;
            iteratorNode = this->head;

            while (iteratorNode->next != NULL &&
                   relation(iteratorNode->next->data.second, newNode->data.second)) {
                iteratorNode = iteratorNode->next;
            }

            // Either at the ends of the list
            // or at required position
            newNode->next = iteratorNode->next;
            iteratorNode->next = newNode;
        }
    }
}

//throws exception if the queue is empty
Element PriorityQueue::top() const {
    if(this->isEmpty())
    {
        throw exception_ptr();
    }

    return this->head->data;
}

Element PriorityQueue::pop() {
    if(this->isEmpty())
    {
        throw exception_ptr();
    }

    Element e;
    Node* p = this->head;
    e.first = this->head->data.first;
    e.second = this->head->data.second;
    this->head = this->head->next;
    free(p);
    return e;
}

bool PriorityQueue::isEmpty() const {
	return head == NULL;
}


PriorityQueue::~PriorityQueue() {
	while(!isEmpty()){
        Node* p = this->head;
        this->head = this->head->next;
        free(p);
    }
};

