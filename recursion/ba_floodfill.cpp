#include<stdio.h>
#include<unistd.h>
#define SZ 15

char map[SZ+2][SZ+2] = {
    "###############",
    "#             #",
    "#         ### #",
    "#             #",
    "#   ####      #",
    "#             #",
    "#             #",
    "#       ##    #",
    "#             #",
    "# ###         #",
    "#             #",
    "###############",
};

int to_mm_second(double num){
	return num * 1000000;
}

void printmap(){
    for(int i = 0; i < SZ; i++){
        printf("%s\n", map[i]);
    }
	usleep(to_mm_second(0.5));
}

void floodfill(int currX, int currY){
    if(currX < 0 || currX > SZ || currY < 0 || currY > SZ
		|| map[currX][currY] == '#' || map[currX][currY] == '0'){

        return;
    }

    map[currX][currY] = '0';
	printmap();

    floodfill(currX + 1, currY);
    floodfill(currX - 1, currY);
    floodfill(currX, currY + 1);
    floodfill(currX, currY - 1);
}

int main(){

    floodfill(1, 1);
	printmap();

    return 0;
}
