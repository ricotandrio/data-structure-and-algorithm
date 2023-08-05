#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define SIZE 5

struct Node{
	char name[55];
	struct Node *next;
} *table[SIZE+1];

int hash(const char *name){
	int len = strlen(name);
	int sum = 0;
	for(int i = 0; i < len; i++){
		sum = sum + (name[i] % 'a');
	}
	return sum % SIZE;
}

struct Node *createNode(const char *name){
	struct Node *newNode = (struct Node *) malloc(sizeof(struct Node));
	strcpy(newNode->name, name);
	newNode->next = NULL;
	return newNode;
}

void insert(const char *name){
	int idx = hash(name);
	struct Node *newNode = createNode(name);
	if(!table[idx]){
		table[idx] = newNode;
	} else {
		struct Node *curr = table[idx];
		while(curr->next){
			curr = curr->next;
		}
		curr->next = newNode;
	}
}

void traversall(struct Node *curr){
	while(curr){
		printf("%s -> ", curr->name);
		curr = curr->next;
	}
	puts("NULL");
}

void displayOuter(){
	for(int i = 0; i < SIZE; i++){
		if(!table[i]) puts("0");
		else if(table[i]->next){
			traversall(table[i]);
		} else {
			printf("%s -> NULL\n", table[i]->name);
		}
	}
}

void popMid(const char *name){
	int key = hash(name);
	//Apabila ada data
	if (table[key]){
		//Data ada di epan
		if (strcmp(name, table[key]->name) == 0){
			//Pophead
			struct Node *ptr = table[key];
			table[key] = table[key]->next;
			free(ptr);
			ptr->next = NULL;

		} else {
			struct Node *current = table[key];
			while (current->next != NULL && strcmp(current->next->name, name) != 0){
				current = current->next;
			}
			if(current->next && strcmp(current->next->name, name) == 0){
				struct Node *temp = current->next;
				current->next = temp->next;
				temp->next = NULL;
				free(temp);
			}
		}
	}
}


int main(){
	insert("halo");
	insert("budi");
	insert("besok");
	insert("cash");
	popMid("cash");
	displayOuter();
	return 0;
}

