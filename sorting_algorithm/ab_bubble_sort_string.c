#include<stdio.h>
#include<string.h>

struct Course{
    char name[25];
};
const int n = 2;
struct Course data[n+1];

void swap(struct Course *a, struct Course *b){
    struct Course temp = *a;
    *a = *b;
    *b = temp;
}

void sortAlpha(int a, int b){
    int len = strlen(data[a].name) < strlen(data[b].name) ? strlen(data[a].name) : strlen(data[b].name);
    int tempA = 1, tempB = 1;
    for(int i = 1; i < len; i++){
        if(data[a].name[tempA] == ' ') tempA++;
        if(data[b].name[tempB] == ' ') tempB++;
        if(data[a].name[tempA] == data[b].name[tempB]) {
            tempA++;
            tempB++;
        }
        if(data[a].name[tempA] > data[b].name[tempB]){
			swap(&data[a], &data[b]);
            return;
		}
    }
    if(strlen(data[a].name) > strlen(data[b].name)){
        swap(&data[a], &data[b]);
    }
}

void sort(){
    for(int i = 0; i < n - 1; i++){
        for(int j = 0; j < n - i - 1; j++){
            if(data[j].name[0] == data[j+1].name[0]){
                sortAlpha(j, j+1);
            } else if(data[j].name[0] > data[j].name[0]){
                swap(&data[j], &data[j+1]);
            }

        }
    }
}

int main(){
    strcpy(data[0].name, "ABC");
    strcpy(data[1].name, "ABCD");
    sort();
    for(int i = 0; i < n; i++){
        printf("%s\n", data[i].name);
    }
    return 0;
}
