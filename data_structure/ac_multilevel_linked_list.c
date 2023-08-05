#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// struct initialization
struct Node{
	char name[20];
	struct Node *north, *south, *west, *east;
} *baseRoot = NULL;

// return and initializes struct node
struct Node *createNode(const char *name){
	struct Node *newNode = (struct Node*) malloc(sizeof(struct Node));
	strcpy(newNode->name, name);
	newNode->north = newNode->south = newNode->east = newNode->west = NULL;
	return newNode;
}

// connect east node with west node
void joinEastWest(struct Node *east, struct Node *west){
	east->west = west;
	west->east = east;
}

// connect north node with south node
void joinNorthSouth(struct Node *north, struct Node *south){
	north->south = south;
	south->north = north;
}

// deletes the connection between the current city node and its north neighbors
void deleteNorth(struct Node *curr){
	struct Node *temp = curr->north;
	curr->north = NULL;
	if(temp->north){
		temp->north->south = NULL;
		temp->north = NULL;
	}
	if(temp->east){
		temp->east->west = NULL;
		temp->east = NULL;
	}
	if(temp->west){
		temp->west->east = NULL;
		temp->west = NULL;
	}
	temp->south = NULL;
	free(temp);
}

// deletes the connection between the current city node and its south neighbors
void deleteSouth(struct Node *curr){
	struct Node *temp = curr->south;
	curr->south = NULL;
	if(temp->south){
		temp->south->north = NULL;
		temp->south = NULL;
	}
	if(temp->east){
		temp->east->west = NULL;
		temp->east = NULL;
	}
	if(temp->west){
		temp->west->east = NULL;
		temp->west = NULL;
	}
	temp->north = NULL;
	free(temp);
}

// deletes the connection between the current city node and its west neighbors
void deleteWest(struct Node *curr){
	struct Node *temp = curr->west;
	curr->west = NULL;
	if(temp->west){
		temp->west->east = NULL;
		temp->west = NULL;
	}
	if(temp->north){
		temp->north->south = NULL;
		temp->north = NULL;
	}
	if(temp->south){
		temp->south->north = NULL;
		temp->south = NULL;
	}
	temp->east = NULL;
	free(temp);
}

// deletes the connection between the current city node and its east neighbors
void deleteEast(struct Node *curr){
	struct Node *temp = curr->east;
	curr->east = NULL;
	if(temp->east){
		temp->east->west = NULL;
		temp->east = NULL;
	}
	if(temp->north){
		temp->north->south = NULL;
		temp->north = NULL;
	}
	if(temp->south){
		temp->south->north = NULL;
		temp->south = NULL;
	}
	temp->west = NULL;
	free(temp);
}

// validate the option chosen by the user for which connection they want to remove.
void deleteCity(struct Node *currentCity){
	while(1 == 1) {
		puts("Choose Which City to Delete");
		printf("1. East\n2. West\n3. North\n4. South\n5. Back\n>> ");
		int input;
		scanf("%d", &input); getchar();
		switch(input) {
			case 1: {
				deleteEast(currentCity);
				break;
			}
			case 2: {
				deleteWest(currentCity);
				break;
			}
			case 3: {
				deleteNorth(currentCity);
				break;
			}
			case 4: {
				deleteSouth(currentCity);
				break;
			}
			case 5: {
				return;
				break;
			}
		}

	}
}

void mainMenu(){
	if(!baseRoot) puts("No City Yet.");

	struct Node *currentCity = baseRoot;

	while(1 == 1) {
		printf("Current City : %s\n", currentCity->name);
		printf("1. To East\n2. To West\n3. To North\n4. To South\n5. Delete City\n>> ");
		int input;
		scanf("%d", &input); getchar();
		switch(input) {
			case 1:
				if(currentCity->east) currentCity = currentCity->east;
				else puts("No City in the East Side!\n");
				break;
			case 2:
				if(currentCity->west) currentCity = currentCity->west;
				else puts("No City in the West Side!\n");
				break;
			case 3:
				if(currentCity->north) currentCity = currentCity->north;
				else puts("No City in the North Side!\n");
				break;
			case 4:
				if(currentCity->south) currentCity = currentCity->south;
				else puts("No City in the South Side!\n");
				break;
			case 5:
				deleteCity(currentCity);
				break;
		}

	}
}

int main(){
	// initialize the cities.
	struct Node *Seoul = createNode("Seoul");
	struct Node *Busan = createNode("Busan");
	struct Node *Incheon = createNode("Incheon");
	struct Node *Daegu = createNode("Daegu");
	struct Node *Daejeon = createNode("Daejeon");
	struct Node *Gwangju = createNode("Gwangju");

	// set base root
	baseRoot = Seoul;

	// set connection between cities
	joinNorthSouth(Seoul, Incheon);
	joinEastWest(Seoul, Busan);
	joinEastWest(Daejeon, Seoul);
	joinEastWest(Gwangju, Daejeon);

	// call main menu function
	mainMenu();
	return 0;
}
