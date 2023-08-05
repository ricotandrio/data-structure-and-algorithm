#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct node {
    char id[50];
    struct node *next;
} *head = NULL, *tail = NULL;

struct node *createnode(char *id){
    struct node *newnode = (struct node *) malloc (sizeof(struct node));
    strcpy(newnode->id, id);
    newnode->next = NULL;
    return newnode;
}

void pushhead(struct node *newnode){
    if(!head){
        head = tail = newnode;
    } else {
        newnode->next = head;
        head = newnode;
    }
}

void pushtail(struct node *newnode){
    if(!head){
        head = tail = newnode;
    } else {
        tail->next = newnode;
        tail = newnode;
    }
}

void pushmid(struct node *newnode){
    if(!head){
        head = tail = newnode;
    } else if(strcmp(newnode->id, head->id) < 0){
        pushhead(newnode);
    } else if(strcmp(newnode->id, tail->id) > 0){
        pushtail(newnode);
    } else {
        struct node *curr = head;
        while(curr != tail && strcmp(newnode->id, curr->id) < 0){
            curr = curr->next;
        }
        newnode->next = curr->next;
        curr->next = newnode;
    }
}

void viewall(struct node *curr){
    while(curr){
        printf("%s\n", curr->id);
        curr = curr->next;
    }
}

void pophead(){
    if(head){
        if(head == tail){
            free(head);
            head = tail = NULL;
        } else {
            struct node *temp = head;
            head = head->next;
            free(temp);
            temp->next = NULL;

        }
    }
}

void poptail(){
    if(head){
        if(head == tail){
            free(head);
            head = tail = NULL;
        } else {
            struct node *curr = head;
            while(curr->next != tail){
                curr = curr->next;
            }
            curr->next = NULL;
            free(tail);
            tail = curr;
        }
    }
}

void popmid(char *id){
    struct node *curr = head;
    if(head){
        if(strcmp(head->id, id) == 0){
            pophead();
        } else if(strcmp(tail->id, id) == 0){
            poptail();
        } else {
            while(curr != tail){
                if(strcmp(curr->next->id, id) == 0){
                    struct node *temp = curr->next;
                    curr->next = temp->next;
                    free(temp);
                    temp->next = NULL;
                    temp = NULL;
                    return;
                }
                curr = curr->next;
            }
        }
    }
}

int main(){
    {
        puts(">> SECTION#1");
        pushmid(createnode("ZGDvgizSqa"));
        pushmid(createnode("RMogPTxhlq"));
        pushmid(createnode("tLzAtsOPgv"));
        pushmid(createnode("AqOHSNTuej"));
        pushmid(createnode("GQoEOTscwN"));
        pushmid(createnode("gASvYkANbc"));
        pushmid(createnode("RQHvRPxtcp"));
        pushmid(createnode("qIFpZBMPAU"));
        pushmid(createnode("JXoxSgtwKe"));
        pushmid(createnode("OPbavHNhEU"));

        viewall(head);
    }

    {
        puts("\n>> SECTION#2");
        pophead();
        pophead();
        pophead();
        poptail();
        poptail();
        poptail();
        viewall(head);
    }

    {
        puts("\n>> SECTION#3");
        popmid("RQHvRPxtcp");
        popmid("gASvYkANbc");

        viewall(head);
    }
    return 0;
}


