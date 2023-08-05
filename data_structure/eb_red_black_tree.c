/*
	INSERTION
	----------------------------------------------------------
	1) If the ROOT is NULL, set the new NODE to BLACK.
	2) If the PARENT is BLACK, there is no violation.
	3) If the PARENT is RED:
		1) If the UNCLE is RED:
			- Change the color of PARENT and UNCLE to BLACK.
			- Change the color of GRANDPARENT to RED.
		2) If the UNCLE is BLACK:
			- Perform a SINGLE/DOUBLE ROTATION at the GRANDPARENT.
			- Change the color of PARENT to BLACK and both CHILDREN to RED.
	
	DELETION
	----------------------------------------------------------
	- Follow a similar DELETION process as in a Binary Search Tree (BST).
	- Choose either the RIGHT-MOST node of the LEFT CHILD or the LEFT-MOST node of the RIGHT CHILD.
	
	1) If the NODE-TO-DELETE is RED, there is no violation.
	2) If the NODE-TO-DELETE is BLACK:
		- Delete the NODE.
		- Mark the location as DOUBLEBLACK.
			1) If the SIBLING is RED:
				- Set the Parent's color to RED.
				- Set the SIBLING's color to BLACK.
				- Perform a SPECIAL ROTATION at the Parent of the DOUBLEBLACK.
				- Recheck the DOUBLEBLACK condition.
			2) If the SIBLING is BLACK:
				1) If both CHILDREN of the SIBLING are BLACK:
					- Change the SIBLING's color to RED.
					- Move the DOUBLEBLACK condition to the PARENT.
					- If the parent is BLACK, recheck the DOUBLEBLACK condition.
				2) If one of the CHILDREN of the SIBLING is RED:
					- Perform a SINGLE/DOUBLE ROTATION AT the PARENT.
					- The color positions remain the same as the previous state.

*/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

// declare const value for BLACK and RED variable
const int BLACK = 0;
const int RED = 1;

// struct declaration
struct RBT {
	int value, color;
	struct RBT *left, *right, *parent;
} *root = NULL;

void treeCase(struct RBT *newNode);
struct RBT *leftRotate(struct RBT *curr);
struct RBT *rightRotate(struct RBT *curr);

struct RBT *createNode(int value){
	struct RBT *newNode = (struct RBT *) malloc (sizeof(struct RBT));
	newNode->value = value;
	newNode->color = RED; // red black tree properties, every new node is RED
	newNode->left = newNode->right = newNode->parent = NULL;
	return newNode;
}

void insert(struct RBT *curr, struct RBT *newNode){
	if(!root){
		root = newNode;
	} else if(newNode->value < curr->value){
		if(!curr->left){
			curr->left = newNode;
			curr->left->parent = curr;
			curr = curr->left;
		} else {
			insert(curr->left, newNode);
		}
	} else if(newNode->value > curr->value){
		if(!curr->right){
			curr->right = newNode;
			curr->right->parent = curr;
			curr = curr->right;
		} else {
			insert(curr->right, newNode);
		}
	} else {
		puts("already exists");
		return;
	}
	treeCase(curr); // fix the tree balance of the Red-Black Tree (RBT).
	root->color = BLACK; // RBT properties, root node of the tree is always black
	return;
}

void treeCase(struct RBT *newNode){
	if(!root || !newNode) return; // if the tree is empty, there is no need to check the balance.

	// while the newNode is not the root, the color of newNode is red, and the color of newNode's parent is also red.
	while(newNode != root && newNode->parent->color == RED && newNode->color == RED){
		struct RBT *tempParentSibling; // struct to store uncle of newnode

		// get uncle node
		if(newNode->parent == newNode->parent->parent->left){
			tempParentSibling = newNode->parent->parent->right;
		}
		else if(newNode->parent == newNode->parent->parent->right){
			tempParentSibling = newNode->parent->parent->left;
		}

		// when uncle is NULL / color of uncle is BLACK then we do rotation
		if((!tempParentSibling || tempParentSibling->color == BLACK)){

			struct RBT *grand = newNode->parent->parent; // used to store grandparents of newnode

			// rotation case for right right case, will be fixed using single left rotation
			if(newNode == newNode->parent->right && newNode->parent == newNode->parent->parent->right){
				newNode->parent->color = BLACK;
				newNode->parent->parent->color = RED;
				grand = leftRotate(newNode->parent->parent);
			}
			// rotation case for left left case, will be fixed using single right rotation
			else if(newNode == newNode->parent->left && newNode->parent == newNode->parent->parent->left){
				newNode->parent->color = BLACK;
				newNode->parent->parent->color = RED;
				grand = rightRotate(newNode->parent->parent);
			}
			// rotation case for right left case, will be fixed using double rotation
			else if(newNode == newNode->parent->left && newNode->parent == newNode->parent->parent->right){
				newNode->color = BLACK;
				newNode->parent->parent->color = RED;
				grand->right = rightRotate(newNode->parent->parent->right);
				grand = leftRotate(grand);
			}
			// rotation case for left right case, will be fixed using double rotation
			else if(newNode == newNode->parent->right && newNode->parent == newNode->parent->parent->left){
				newNode->color = BLACK;
				newNode->parent->parent->color = RED;
				grand->left = leftRotate(newNode->parent->parent->left);
				grand = rightRotate(grand);
			}
		} else {
			/* condition when uncle is exist and uncle color is red
			   at this condition no rotation will needed so we do recolor*/
			tempParentSibling->color = BLACK;
			newNode->parent->color = BLACK;
			newNode->parent->parent->color = RED;
			newNode = newNode->parent->parent; // check grandparent condition
		}
	}
	root->color = BLACK; // set root color by default to black
}

void preorder(struct RBT *curr){
	if(curr){
		printf("%d(%s) ", curr->value, curr->color == 0 ? "B" : "R");
		preorder(curr->left);
		preorder(curr->right);
	}
}

// this function is used to perform left rotation
struct RBT *leftRotate(struct RBT *curr){
	// store current node right sub-tree as pivot
	struct RBT *pivot = curr->right;

	// change current node right sub-tree to pivot left sub-tree
	curr->right = pivot->left;

	// if pivot's left sub-tree is exists, set current node's right parent as curr
	if(curr->right) curr->right->parent = curr;

	// change pivot's parent to current node's parent
	pivot->parent = curr->parent;

	// if pivot's parent doesn't exist then set root as pivot
	if(!pivot->parent) root = pivot;
	else {
		// if pivot's parent exists then check current node is at left sub-tree or right sub-tree
		if(curr->parent->left == curr) curr->parent->left = pivot;
		else curr->parent->right = pivot;
	}

	// move current node to pivot left sub-tree
	pivot->left = curr;

	// set current node's parent to pivot
	curr->parent = pivot;

	// return pivot
	return pivot;
}

// this function is used to perform right rotation
struct RBT *rightRotate(struct RBT *curr){
	// store current node right sub-tree as pivot
	struct RBT *pivot = curr->left;

	// change current node left sub-tree to pivot right sub-tree
	curr->left = pivot->right;

	// if pivot's right sub-tree is exists, set current node's left parent as curr
	if(curr->left) curr->left->parent = curr;

	// change pivot's parent to current node's parent
	pivot->parent = curr->parent;

	// if pivot's parent doesn't exist then set root as pivot
	if(!pivot->parent) root = pivot;
	else {
		// if pivot's parent exists then check current node is at left sub-tree or right sub-tree
		if(curr->parent->left == curr) curr->parent->left = pivot;
		else curr->parent->right = pivot;
	}

	// move current node to pivot left sub-tree
	pivot->right = curr;

	// set current node's parent to pivot
	curr->parent = pivot;

	// return pivot
	return pivot;
}

bool existRedChild(struct RBT *sibling){
	if(!sibling) return false;
	else {
		if(!sibling->left && !sibling->right){
			return false;
		}
		else {
			if(sibling->left && sibling->left->color == RED) return true;
			if(sibling->right && sibling->right->color == RED) return true;
		} 
		return false;
	}
}

void fixDoubleBlack(struct RBT *curr, struct RBT *parent){
	if(curr == root){
		return;
	}	
	
	struct RBT *sibling;
	bool onLeftParent;
	
	// get sibling position and value
	if(parent->left == curr){
		sibling = parent->right;
		onLeftParent = false;
	} else {
		sibling = parent->left;
		onLeftParent = true;
	}
	
	if(!sibling){
		// if sibling is null then check up blackness to parent
		fixDoubleBlack(parent, parent->parent);
	} else if(sibling->color == RED){
		// condition sibling red
		sibling->color = BLACK;
		parent->color = RED;
		if(onLeftParent == true){
//			puts(" CURR BLACK SIBLING RED ON LEFT: RIGHT ROTATE");
			parent = rightRotate(parent);
		} else {
//			puts(" CURR BLACK SIBLING RED ON RIGHT: LEFT ROTATE");
			parent = leftRotate(parent);
		}
		fixDoubleBlack(curr, curr->parent);
	} else {
		// condition sibling black
		if(existRedChild(sibling) == true){
			// condition when curr is black and there's exists at least one red child
			if(sibling->left && sibling->left->color == RED){ 
				//condition if sibling is on left with red color
				if(onLeftParent == true){
					// left left condition
					sibling->left->color = sibling->color;
					sibling->color = parent->color;
					parent = rightRotate(parent);
				} else { 
					// right left condition
					sibling->left->color = parent->color;
					sibling = rightRotate(sibling);
					parent = leftRotate(parent);
				}
			} else {
				// condition if sibling is on right with red color
				if(onLeftParent == true){
					// left right condition
					sibling->right->color = parent->color;
					sibling = leftRotate(sibling);
					parent = rightRotate(parent);
				} else {
					// right right condition 
					sibling->right->color = sibling->color;
					sibling->color = parent->color;
					parent = leftRotate(parent);
				}
			}
			parent->color = BLACK;
		} else {
			// condition when curr is black and there're two black child
			sibling->color = RED;
			
			// if parent color is black then up blackness to parent
			if(parent->color == BLACK){
				fixDoubleBlack(parent, parent->parent);	
			} else {
				parent->color = BLACK;
			}
		}	
	}
	
}

void executeDeleteNode(struct RBT* parent, struct RBT* curr){
	// condition when node is leaf 
	if(!curr->left && !curr->right){
		if(curr != root){
			if(curr->color == BLACK) fixDoubleBlack(curr, parent);

			if(parent->left == curr){
				parent->left = NULL;
			} else {
				parent->right = NULL;
			}
			free(curr);
			curr = NULL;
		} else {
			free(root);
			root = NULL;
		}
	} else if(!curr->left){
		// condition when there's one child in the left sub-tree
		int tempColor = curr->color;
		if(parent != curr){
            if(parent->right == curr){
				parent->right = curr->right;
				parent->right->color = tempColor;
			} else {
				parent->left = curr->right;
				parent->left->color = tempColor;
			}
		} else {
			root = curr->right;
			root->color = BLACK;
		}
		curr->right = NULL;
		free(curr);
		curr = NULL;
	} else if(!curr->right){
		// condition when there's one child in the right sub-tree
		int tempColor = curr->color;
		if(parent != curr){
			if(parent->left == curr){
				parent->left = curr->left;
				parent->left->color = tempColor;
			} else {
				parent->right = curr->left;
				parent->right->color = tempColor;
			}
		} else {
			root = curr->left;
			root->color = BLACK;
		}
		curr->left = NULL;
		free(curr);
		curr = NULL;
	} else {
		// condition when there're two children 
		struct RBT *predesuccessor = curr->left;
		parent = curr;
		while(predesuccessor && predesuccessor->right){
			parent = predesuccessor;
			predesuccessor = predesuccessor->right;
		}
		curr->value = predesuccessor->value;
		executeDeleteNode(parent, predesuccessor);
	}
}

void deletenode(struct RBT* curr, int value) {
	// this function will loop until query is found
	struct RBT *parent = curr;
	while(curr && curr->value != value){
		if(value < curr->value) {
			parent = curr;
			curr = curr->left;
		} else if (value > curr->value){
			parent = curr;
			curr = curr->right;
		}
	}
	if(!curr){
		printf("%d is not found\n", value);
	} else if(curr->value == value){
		printf("Delete %d:\n", value);
        executeDeleteNode(parent, curr);
    }
}

int main(){

	{
		insert(root, createNode(1));
		insert(root, createNode(2));
		insert(root, createNode(3));
		insert(root, createNode(4));
		insert(root, createNode(5));
		insert(root, createNode(6));
		insert(root, createNode(7));
		insert(root, createNode(8));
		insert(root, createNode(9));
		insert(root, createNode(10));
		preorder(root); puts("");
	}
	
	int i; for(i = 0; i < 10; i++){
		deletenode(root, i+1);	
		preorder(root); puts("\n");
		getchar();
	}
	return 0;
}
