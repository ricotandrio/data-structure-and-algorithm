#include<stdio.h>
#include<stdlib.h>

struct Node{
	int n;
	struct Node *next, *prev;
} *head = NULL, *tail = NULL;

struct Node *createNode(int n){
	struct Node *newNode = (struct Node *) malloc (sizeof(struct Node));
	newNode->n = n;
	newNode->next = newNode->prev = NULL;
	return newNode;
}

void pushHead(struct Node *newNode){
	if(!head) head = tail = newNode;
	else {
		head->prev = newNode;
		newNode->next = head;
		head = newNode;
	}
}

void pushTail(struct Node *newNode){
	if(!head) head = tail = newNode;
	else {
		tail->next = newNode;
		newNode->prev = tail;
		tail = newNode;
	}
}

void pushMid(struct Node *newNode){
	if(!head) head = tail = newNode;
	else if(newNode->n <= head->n) pushHead(newNode);
	else if(newNode->n >= tail->n) pushTail(newNode);
	else {
		struct Node *curr = head->next;
		while(!(newNode->n >= curr->n && newNode->n < curr->next->n)) curr = curr->next;
		struct Node *afterNode = curr->next;
		curr->next = newNode;
		newNode->prev = curr;

		afterNode->prev = newNode;
		newNode->next = afterNode;
	}
}

void search(struct Node *newNode){
	if(!head) puts("EMPTY");
	else if(head->n == newNode->n || tail->n == newNode->n) puts("FOUND");
	else {
		struct Node *curr = head->next;
		while(curr->n != newNode->n && curr != tail) curr = curr->next;
		if(curr == tail) puts("NOT FOUND");
		else puts("FOUND");
	}
}

void popHead(){
	if(!head) puts("EMPTY");
	else if(head == tail){
		free(head);
		head = tail = NULL;
	} else {
		struct Node *oldHead = head;
		head = head->next;
		head->prev = oldHead->next = NULL;
		free(oldHead);
	}
}

void popTail(){
	if(!head) puts("EMPTY");
	else if(head == tail){
		free(head);
		head = tail = NULL;
	} else {
		struct Node *oldTail = tail;
		tail = tail->prev;
		tail->next = oldTail->prev = NULL;
		free(oldTail);
	}
}

void popMid(struct Node *newNode){
	if(!head) puts("EMPTY");
	else if(head->n == newNode->n) popHead();
	else if(tail->n == newNode->n) popTail();
	else {
		struct Node *curr = head->next;
		while(curr != tail && !(curr->n == newNode->n)) curr = curr->next;
		struct Node *prevNode = curr->prev, *nextNode = curr->next;
		prevNode->next = nextNode;
		nextNode->prev = prevNode;
		curr->next = curr->prev = NULL;
		free(curr);
	}
}

void display(){
	struct Node *curr = head;
	while(curr){
		printf("%d -> ", curr->n);
		curr = curr->next;
	} puts("NULL");
}

int main(){
	pushHead(createNode(6));
	pushHead(createNode(5));
	pushTail(createNode(8));
	pushMid(createNode(7));

	search(createNode(0));
	search(createNode(1));

	popHead();
	popTail();

	popMid(createNode(6));

	display();
	return 0;
}
