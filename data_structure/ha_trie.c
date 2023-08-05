#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include<conio.h>
#include<time.h>

struct Trie{
    struct Trie *digit[10];
    char name[50];
    bool isEndofTheNumber;
};

struct Trie *createBase(){
    struct Trie *newBase = (struct Trie *) malloc (sizeof(struct Trie));
    if(newBase){
        newBase->isEndofTheNumber = false;
        for(int i = 0; i < 10; i++) newBase->digit[i] = NULL;
    }
    return newBase;
}

void insert(struct Trie *root, const char *number, const char *name){
    int len = strlen(number);
    struct Trie *temporaryRoot = root;
    for(int i = 0; i < len; i++){
        int idx = number[i] - '0';
        if(!temporaryRoot->digit[idx]) temporaryRoot->digit[idx] = createBase();
        temporaryRoot = temporaryRoot->digit[idx];
    }
    temporaryRoot->isEndofTheNumber = true;
    strcpy(temporaryRoot->name, name);
}

bool searchFor(struct Trie *root, const char *number){
    int len = strlen(number);
    struct Trie *temporaryRoot = root;
    for(int i = 0; i < len; i++){
        int idx = number[i] - '0';
        if(!temporaryRoot->digit[idx]) return false;
        temporaryRoot = temporaryRoot->digit[idx];
    }
    return true;
}

void traverssPossible(struct Trie *temporaryRoot, char *number){
	if(temporaryRoot->isEndofTheNumber == true){
		printf("%s - %s\n", number, temporaryRoot->name);
	}
	char temp[50];
    strcpy(temp, number);
	for(int i = 0; i < 10; i++){
        if(temporaryRoot->digit[i]){
            char suffix = i + '0';
            temp[strlen(number)] = suffix;
            temp[strlen(number) + 1] = '\0';
            traverssPossible(temporaryRoot->digit[i], temp);
		}
	}
}

void possible(struct Trie *root, char *number){
	if(!root) return;

    int len = strlen(number);
    struct Trie *temporaryRoot = root;
    for(int i = 0; i < len; i++){
        int idx = number[i] - '0';
        if(!temporaryRoot->digit[idx]) return;
        temporaryRoot = temporaryRoot->digit[idx];
    }
    traverssPossible(temporaryRoot, number);
}

void generateDatabase(struct Trie *root, char *prefix);
int random(int max){
	int number = rand();
	return number % max;
}

int main(){
	srand(time(NULL));
    struct Trie *root = createBase();
    generateDatabase(root, "08");
	char textToFind[50] = {};
	int index = 0;
	printf("Search : ");
	while(true){
		char text = getch();
		if(text == '\b' && index >= 0) textToFind[--index] = '\0';
        if(index == -1) index = 0;
		system("cls");
		if(text != '\b') textToFind[index++] = text;
		printf("Search : %s\n", textToFind);
		if(index > 0 && (text >= '0' && text <= '9')) possible(root, textToFind);
	}
    return 0;
}

void generateDatabase(struct Trie *root, char *prefix){
	for(int i = 0; i < 10; i++){
		char temp[20] = {};
		char name[20] = {};
		strcat(temp, prefix);
		for(int j = 0; j < 10; j++){
			char suffix = random(10) + '0';
            temp[strlen(temp)] = suffix;
            temp[strlen(temp) + 1] = '\0';
            if(j < 5){
	            name[strlen(name)] = ((int)suffix % 26) + 'a';
	            name[strlen(name) + 1] = '\0';
			}
		}
		insert(root, temp, name);
	}
}
