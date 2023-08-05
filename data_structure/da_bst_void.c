#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node {
    char id[10];
    struct node *left, *right, *parent;
} *root = NULL;

void insert(const char *id){
    struct node *newnode = (struct node *) malloc (sizeof(struct node));
    strcpy(newnode->id, id);
    newnode->left = newnode->right = NULL;

    if(!root){
        root = newnode;
    } else {
        struct node *curr = root;
        while(curr){
            if(strcmp(id, curr->id) < 0){
                if(!curr->left){
                    curr->left = newnode;
                    newnode->parent = curr;
                    return;
                } else {
                    curr = curr->left;
                }
            } else if(strcmp(id, curr->id) > 0){
                if(!curr->right){
                    curr->right = newnode;
                    newnode->parent = curr;
                    return;
                } else {
                    curr = curr->right;
                }
            } else {
                puts("already exist");
                return;
            }
        }
    }
}

void executeDeleteNode(struct node* parent, struct node* curr){
	if(!curr->left && !curr->right){
		if(curr != root){
			if(parent->left == curr) parent->left = NULL;
			else parent->right = NULL;
			free(curr);
			curr = NULL;
		} else {
			free(root);
			root = NULL;
		}
	} else if(!curr->left){
		if(parent != curr){
            if(parent->right == curr) parent->right = curr->right;
            else parent->left = curr->right;
		} else {
			root = curr->right;
		}
		curr->right = NULL;
		free(curr);
		curr = NULL;
	} else if(!curr->right){
		if(parent != curr){
			if(parent->left == curr) parent->left = curr->left;
			else parent->right = curr->left;
		} else {
			root = curr->left;
		}
		curr->left = NULL;
		free(curr);
		curr = NULL;
	} else {
		struct node *predesuccessor = curr->left;
		parent = curr;
		while(predesuccessor && predesuccessor->right){
			parent = predesuccessor;
			predesuccessor = predesuccessor->right;
		}
        strcpy(curr->id, predesuccessor->id);
		executeDeleteNode(parent, predesuccessor);
	}
}

void delete_and_search(struct node* curr, const char *id, char *function) {
	struct node *parent = curr;
	while(curr && strcmp(curr->id, id) != 0){
		if(strcmp(id, curr->id) < 0) {
			parent = curr;
			curr = curr->left;
		} else if (strcmp(id, curr->id) > 0){
			parent = curr;
			curr = curr->right;
		}
	}
	if(!curr){
		printf("%s is not found\n", id);
        strcpy(function, "not found");
	} else if(strcmp(curr->id, id) == 0){
        if(strcmp(function, "delete") == 0){
            executeDeleteNode(parent, curr);
        } else {
            strcpy(function, "found");
        }
    }
}

struct node *popall(struct node *curr){
	if(curr){
		curr->left = popall(curr->left);
		curr->right = popall(curr->right);
		free(curr);
		curr->parent = NULL;
		if(curr == root) root = NULL;
		else curr = NULL;
	}
	return NULL;
}

int getheight(struct node *curr){
    return (!curr ? 0 : getheight(curr->left) + getheight(curr->right) + 1);
}

void print_level(int i, struct node *curr){
	if(!curr) return;
	else if(i == 1){
		printf("%s ", curr->id);
	} else {
		print_level(i - 1, curr->left);
		print_level(i - 1, curr->right);
	}
}

void level_order(){
	if(!root) puts(">> tree is empty <<");

    int height = getheight(root);
    for(int i = 1; i <= height; i++){
        print_level(i, root);
		puts("");
    }
}

int main(){
	{
		puts(" -- SECTION #1");
	    insert("B");
	    insert("B");
	    insert("C");
	    insert("F");
	    insert("D");
	    insert("A");

		level_order();
		char temp_delete[20] = "delete";

		delete_and_search(root, "B", temp_delete);
		delete_and_search(root, "B", temp_delete); strcpy(temp_delete, "delete");
		delete_and_search(root, "C", temp_delete);
		delete_and_search(root, "F", temp_delete);
		delete_and_search(root, "D", temp_delete);
		delete_and_search(root, "A", temp_delete);
		level_order();
	}

	{
		puts("\n -- SECTION #2");
		insert("A");
	    insert("A");
	    insert("B");
	    insert("C");

		level_order();
		popall(root);
		level_order();
	}

	{
		puts("\n -- SECTION #3");
		insert("A");
	    insert("A");
	    insert("B");
	    insert("C");

		char temp_search[20] = "search";
		delete_and_search(root, "C", temp_search);

		printf(">> %s <<\n", temp_search);
	}

    return 0;
}
