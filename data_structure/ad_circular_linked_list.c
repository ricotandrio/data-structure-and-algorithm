#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Node {
    int n;
    struct Node *next, *prev;
} *head = NULL, *tail = NULL;

struct Node *createNode(int n){
    struct Node *newNode = (struct Node *) malloc (sizeof(struct Node));
    newNode->n = n;
    newNode->next = newNode->prev = NULL;
    return newNode;
}

void updateCircular(){
	head->prev = tail;
    tail->next = head;
}

void pushHead(struct Node *newNode){
    if(!head) head = tail = newNode;
    else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
        updateCircular();
	}
}

void pushTail(struct Node *newNode){
    if(!head) head = tail = newNode;
    else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
        updateCircular();
    }
}

void pushMid(struct Node *newNode){
    if(!head) head = tail = newNode;
    else if(head->n >= newNode->n) pushHead(newNode);
    else if(tail->n <= newNode->n) pushTail(newNode);
    else {
        struct Node *curr = head->next;
        while(curr){
            if(curr->n <= newNode->n && curr->next->n > newNode->n) break;
            curr = curr->next;
        }
        struct Node *afterCurr = curr->next;
        curr->next = newNode;
        newNode->prev = curr;
        newNode->next = afterCurr;
        afterCurr->prev = newNode;
    }
}

void popHead(){
	if(!head) return;
	else {
		struct Node *newHead = head->next;
		head = head->next = newHead->prev = NULL;
		free(head);
		head = newHead;
		updateCircular();
	}
}

void popTail(){
	if(!head) return;
	else {
		struct Node *newTail = tail->prev;
		tail = newTail->next = tail->prev = NULL;
		free(tail);
		tail = newTail;
		updateCircular();
	}
}

void popMid(int n){
	if(!head) return;
	else if(head->n == n) popHead();
	else if(tail->n == n) popTail();
	else {
		struct Node *curr = head->next;
		while(curr && curr != tail){
			if(curr->n == n) break;
			curr = curr->next;
		}
		struct Node *afterCurr = curr->next;
		struct Node *beforeCurr = curr->prev;
		beforeCurr->next = afterCurr;
		afterCurr->prev = beforeCurr;
		curr = curr->next = curr->prev = NULL;
		free(curr);
	}
}

void display(){
	struct Node *curr = head;
	printf("NULL -> ");
	while(curr){
		printf("%d -> ", curr->n);
		curr = curr->next;
		if(curr == head) break;
	}
	puts("NULL");
}

int main(){
	pushHead(createNode(5));
	pushHead(createNode(1));
	pushTail(createNode(9));
	pushTail(createNode(12));
	pushTail(createNode(15));
	pushHead(createNode(0));
	pushMid(createNode(6));
	display();
	popHead();
	display();
	popMid(6);
	display();
	printf(">> %d\n", tail->next->n);
	printf(">> %d\n", head->prev->n);
    return 0;
}
