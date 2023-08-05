#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node {
	char name[255];
	int height, bf;
	struct node *left, *right;
};

struct node *rotate(struct node *curr);
struct node *leftrotate(struct node *curr);
struct node *rightrotate(struct node *curr);

int max(int a, int b){
	return a > b ? a : b;
}

int getheight(struct node *curr){
	return curr ? curr->height : 0;
}

int updateheight(struct node *curr){
	return max(getheight(curr->left), getheight(curr->right)) + 1;
}

int updatebalancefactor(struct node *curr){
	return getheight(curr->left) - getheight(curr->right);
}

struct node *updatenode(struct node *curr){
	if(curr){
		curr->height = updateheight(curr);
		curr->bf = updatebalancefactor(curr);
	}
	return curr;
}

struct node *createnode(char *name){
	struct node *newnode = (struct node *) malloc (sizeof(struct node));
	strcpy(newnode->name, name);

	newnode->height = 1;
	newnode->bf = 0;
	newnode->left = newnode->right = NULL;
	return newnode;
}

struct node *insertnode(struct node *curr, struct node *newnode){
	if(!curr){
		return newnode;
	} else if(strcmp(curr->name, newnode->name) > 0){
		curr->left = insertnode(curr->left, newnode);
	} else if(strcmp(curr->name, newnode->name) < 0){
		curr->right = insertnode(curr->right, newnode);
	}
	return rotate(updatenode(curr));
}

void preorder(struct node *curr){
	if(curr){
		printf("%s\n", curr->name);
		preorder(curr->left);
		preorder(curr->right);
	}
}

struct node *rotate(struct node *curr){
	if(curr){
		if(curr->bf > 1){
			if(curr->left->bf >= 0){
				return rightrotate(curr);
			} else {
				curr->left = leftrotate(curr->left);
				return rightrotate(curr);
			}
		} else if(curr->bf < -1){
			if(curr->right->bf <= 0){
				return leftrotate(curr);
			} else {
				curr->right = rightrotate(curr->right);
				return leftrotate(curr);
			}
		}
	}
	return curr;
}

struct node *leftrotate(struct node *curr){
	struct node *pivot = curr->right;
	curr->right = pivot->left;
	pivot->left = curr;

	curr = updatenode(curr);
	return updatenode(pivot);
}

struct node *rightrotate(struct node *curr){
	struct node *pivot = curr->left;
	curr->left = pivot->right;
	pivot->right = curr;

	curr = updatenode(curr);
	return updatenode(pivot);
}

struct node *removenode(struct node *curr, char *key){
	if(!curr){
		return curr;
	} else if(strcmp(curr->name, key) > 0){
		curr->left = removenode(curr->left, key);
	} else if(strcmp(curr->name, key) < 0){
		curr->right = removenode(curr->right, key);
	} else {
		if(!curr->left && !curr->right){
			free(curr);
			curr = NULL;
			return curr;
		} else if(curr->left && !curr->right){
			struct node *temp = curr->left;
			free(curr);
			curr = NULL;
			return rotate(updatenode(temp));
		} else if(!curr->left && curr->right){
			struct node *temp = curr->right;
			free(curr);
			curr = NULL;
			return rotate(updatenode(temp));
		} else {
			struct node *prede = curr->left;
			while(prede->right){
				prede = prede->right;
			}
			strcpy(curr->name, prede->name);
			curr->left = removenode(curr->left, prede->name);
		}
	}
	return rotate(updatenode(curr));
}

void printorder(int level, struct node *curr){
	if(!curr){
		return;
	} else {
		if(level == 1) printf("%s ", curr->name);
		else {
			printorder(level - 1, curr->left);
			printorder(level - 1, curr->right);
		}
	}
}

void travesslevel(struct node *curr){
	int height = curr->height;
	for(int i = 1; i <= height; i++){
		printorder(i, curr); puts("");
	}
}

int nodecount_external(struct node *curr){
	if(!curr){
		return 0;
	} else if(!curr->left && !curr->right){
		return 1;
	}
	return nodecount_external(curr->left) + nodecount_external(curr->right);
}

int nodecount_internal(struct node *curr){
	if(!curr){
		return 0;
	} else if(curr->left || curr->right){
		return nodecount_internal(curr->left) + nodecount_internal(curr->right) + 1;
	} else {
		return nodecount_internal(curr->left) + nodecount_internal(curr->right);
	}
}

int nodecount_all(struct node *curr){
	if(!curr){
		return 0;
	}
	return nodecount_all(curr->left) + nodecount_all(curr->right) + 1;
}

int main(){
	struct node *root = NULL;
	root = insertnode(root, createnode("g"));
	root = insertnode(root, createnode("e"));
	root = insertnode(root, createnode("d"));
	root = insertnode(root, createnode("z"));
	root = insertnode(root, createnode("d"));
	root = insertnode(root, createnode("g"));
	travesslevel(root);
	printf("\ninternal  == %d\n", nodecount_internal(root));
	printf("external  == %d\n", nodecount_external(root));
	printf("all  == %d\n", nodecount_all(root));
	puts("==");
	root = removenode(root, "g");
	root = removenode(root, "e");
	root = removenode(root, "z");
	root = removenode(root, "d");
	preorder(root);
	puts("==");
	root = insertnode(root, createnode("g"));
	root = insertnode(root, createnode("e"));
	root = insertnode(root, createnode("d"));
	root = insertnode(root, createnode("z"));
	root = insertnode(root, createnode("d"));
	root = insertnode(root, createnode("g"));
	preorder(root);
	return 0;
}
