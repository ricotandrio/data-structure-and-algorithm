#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define SIZE 5

char table[SIZE+1][255];
unsigned long djb2(const char *str) {
	unsigned long key = 5381;
	for(int i = 0; str[i] != '\0'; i++) {
		int ascii = (int)str[i];
	    key = (key << 5) + key + ascii;
    }
	return key % SIZE;
}

void insert(const char *name){
	int idx = djb2(name);
    if(!table[idx][0]){
        strcpy(table[idx], name);
    } else {
        for(int i = (idx + 1)%SIZE; i != idx; i = (i + 1)%SIZE){
            if(!table[i][0]){
                strcpy(table[i], name);
                return;
            }
        }
        puts("FULL");
    }
}

void displayOuter(){
	for(int i = 0; i < SIZE; i++){
		if(!table[i][0]) puts("0");
		else printf("%s\n", table[i]);
	}
}

void popMid(const char *name){
	for(int i = 0; i < SIZE; i++){
		if(!table[i][0]){
			continue;
		} else {
			if(strcmp(table[i], name) == 0){
				memset(table, 0, sizeof(char)*255);
				return;
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
