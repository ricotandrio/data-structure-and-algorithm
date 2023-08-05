#include<stdio.h>
#include<stdlib.h>

struct Node{
    int n;
    struct Node *left, *right;
} *baseRoot = NULL;

struct Node *createNode(int n){
    struct Node *newNode = (struct Node*) malloc(sizeof(struct Node));
    newNode->n = n;
    newNode->left = newNode->right = NULL;
    return newNode;
}

struct Node *insert(struct Node *root, struct Node *newNode){
	if(!root){
		return newNode;
	} else if(newNode->n > root->n){
		root->right = insert(root->right, newNode);
	} else if(newNode->n < root->n){
		root->left = insert(root->left, newNode);
	}
	return root; // if current node is exist or return back the root the previous recursive call

}

// Traverss Binary Tree
void traverssInorder(struct Node *root){
	if(root){
		traverssInorder(root->left);
		printf("%d ", root->n);
		traverssInorder(root->right);
	}
}

void traverssPostorder(struct Node *root){
	if(root){
		traverssPostorder(root->left);
		traverssPostorder(root->right);
		printf("%d ", root->n);
	}
}

void traverssPreorder(struct Node *root){
	if(root){
		printf("%d ", root->n);
		traverssPreorder(root->left);
		traverssPreorder(root->right);
	}
}

int heightTree(struct Node *root){
	return (root ? heightTree(root->left) + heightTree(root->right) + 1 : 0);
}

void printLevel(struct Node *root, int level){
	if(root){
		if(level == 1) printf("%d ", root->n); // if base root
		else if(level > 1){
			printLevel(root->left, level - 1); // the function will search for the depth of the tree by decreasing the level,
			printLevel(root->right, level - 1); //for example level 3 will be reached when root->left->left
		}
	}
}

void traverssLevel(struct Node *root){
	int height = heightTree(root), i; // get height of binary tree
	for(i = 1; i <= height; i++) {
        printLevel(root, i);
		puts("");
    }
}

struct Node *search(struct Node *root, int n){
	if(!root){
		return NULL;
	} else if(root->n == n){
		return root;
	} else if(n < root->n){
		return search(root->left, n);
	} else if(n > root->n){
		return search(root->right, n);
	}
}

// most left and least right
struct Node *successor(struct Node *root){
    struct Node *curr = root->right;
    while(curr && curr->left) curr = curr->left;
    return curr;
}

struct Node *prede(struct Node *root){
    struct Node *curr = curr->left;
    while(curr && curr->right) curr = curr->right;
    return curr;
}

// delete data
struct Node *deleteData(struct Node *root, int n){
    if(!root) return root;
    else if(root->n < n) root->right = deleteData(root->right, n);
    else if(root->n > n) root->left = deleteData(root->left, n);
    else {
        if(!root->left || !root->right){
            struct Node *newRoot = root->right ? root->right : root->left;
            root->left = root->right = NULL;
            free(root);
            return newRoot;
        }
        struct Node *newRoot = successor(root);
        // struct Node *newRoot = prede(root);
        root->n = newRoot->n;
        root->right = deleteData(newRoot, newRoot->n);
    }
    return root;
}

// min, max, count
int minValue(struct Node* node) {
	if(!node) return 0;
	while(node->left){
		node = node->left;
	}
	return node->n;
}

int maxValue(struct Node* node){
	if(!node) return 0;
	while(node->right){
		node = node->right;
	}
	return node->n;
}

int count(struct Node* node){
	if(!node) return 0;
	else {
		int countV = 0;
		countV += count(node->left);
		countV += count(node->right);
		return countV + 1;
	}
}

int nodecount_external(struct Node *curr){
	if(!curr){
		return 0;
	} else if(!curr->left && !curr->right){
		return 1;
	}
	return nodecount_external(curr->left) + nodecount_external(curr->right);
}

int nodecount_internal(struct Node *curr){
	if(!curr){
		return 0;
	} else if(curr->left || curr->right){
		return nodecount_internal(curr->left) + nodecount_internal(curr->right) + 1;
	} else {
		return nodecount_internal(curr->left) + nodecount_internal(curr->right);
	}
}

int nodecount_all(struct Node *curr){
	if(!curr){
		return 0;
	}
	return nodecount_all(curr->left) + nodecount_all(curr->right) + 1;
}

void popall(struct Node *root){
	while(baseRoot){
		baseRoot = deleteData(root, root->n);
	}
}

int main(){
	baseRoot = insert(baseRoot, createNode(2));
	baseRoot = insert(baseRoot, createNode(3));
	baseRoot = insert(baseRoot, createNode(4));
	baseRoot = insert(baseRoot, createNode(2));
	baseRoot = insert(baseRoot, createNode(5));

	printf("Preorder: "); traverssPreorder(baseRoot); puts("");
	printf("Inorder: "); traverssInorder(baseRoot); puts("");
	printf("Postorder: "); traverssPostorder(baseRoot); puts("");

	popall(baseRoot);

	puts(baseRoot ? "NOT EMPTY" : "EMPTY");
    return 0;
}
