// Online C compiler to run C program online
#include <stdio.h>
#include <stdlib.h>

struct node {
       int data;
       struct node *next;
};
struct node *head = NULL;

struct node * create_node(int data){
      struct node *temp =  (struct node *)malloc(sizeof(struct node));
      temp->data = data;
      temp->next = NULL;
      return temp;
} 

void print_node(struct node *l1) {
    struct node *temp = l1;
    while (temp) {
         printf("%d->",temp->data);
         temp = temp->next;
    }
    printf("NULL\n");
}

void reverse_node(struct node *l1) {
     struct node *curr = l1;
     struct node *prev = NULL;
     struct node *next = NULL;
     
     while(curr) {
         next = curr->next;
         curr->next = prev;
         prev = curr;
         curr = next;
     }
     head = prev;
}

void rec_reverse_node(struct node *q, struct node *p) {
        if (p) {
            rec_reverse_node(p, p->next);
            p->next = q;
        } else {
            head = q;
        }
}

void rec_reverse_node1(struct node *p) {
      if (!p || !p->next)     {
          head = p;
          return;
      }
      rec_reverse_node1(p->next);
      struct node *temp = p;
      temp->next->next = temp;
      temp->next = NULL;
}

void del_node(int pos, struct node *p){
    if (!p) {
        return;
    }
    struct node *t;
    while(pos-1) {
        t = p;
        p = p->next;
        pos--;
    }
    t->next = t->next->next;
}

void del_node_without_head(struct node *p){
    if (!p) {
        return;
    }
    struct node *t;
    while(pos-1) {
        t = p;
        p = p->next;
        pos--;
    }
    t->next = t->next->next;
}

//1->2->3->4->null
int main() {
    head = create_node(1);
    head->next = create_node(2);
    head->next->next = create_node(3);
    head->next->next->next = create_node(4);
    
    print_node(head);
    reverse_node(head);
    print_node(head);
    rec_reverse_node(NULL, head);
    print_node(head);
    rec_reverse_node1(head);
    print_node(head);    
    del_node(2, head);
    print_node(head);
    del_node1(2);
    print_node(head);     
    return 0;
}
