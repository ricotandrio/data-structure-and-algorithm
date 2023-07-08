#include<stdio.h>
#include<string.h>
#define SZ 10

struct Temp{
	int n;
	char name[25];
} data[SZ+1];

void merge(int l, int m, int r){
	struct Temp temp[r - l + 1];
	int tempIdx = 0;
	int ml = l, mr = m+1;

	while(ml <= m && mr <= r){
		if(strcmp(data[ml].name, data[mr].name) < 0){
			temp[tempIdx++] = data[ml++];
		} else {
			temp[tempIdx++] = data[mr++];
		}
	}

	while(ml <= m){
		temp[tempIdx++] = data[ml++];
	}

	for(int i = 0; i < tempIdx; i++){
		data[i + l] = temp[i];
	}
}

void divide(int l, int r){
	if(l != r){
		int mid = l + (r - l) / 2;
		divide(l, mid);
		divide(mid+1, r);
		merge(l, mid, r);
	}
}

int main(){
	char name[SZ+1][25] = {
		"Hello",
		"Hallo",
		"Halo",
		"Aloha",
		"Hlo",
		"Hai",
		"Hey",
		"Nay",
		"Yay",
		"Yyyay",
	};

	for(int i = 0; i < SZ; i++){
		data[i].n = i;
		strcpy(data[i].name, name[i]);
	}
	divide(0, SZ-1);
	for(int i = 0; i < SZ; i++){
		printf("%d %s\n", data[i].n, data[i].name);
	}
	return 0;
}
