#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

typedef struct tree {
    int data;
    tree *left;
    tree *right;
} t1;

t1 *
create(int data) {
    t1 *temp = new tree;
    temp->data = data;
    temp->left = temp->right = NULL;
    return temp;
}

void
printIterativeInorder(t1 *head) {
    stack<t1 *> s1;
    t1 *temp = head;
    cout << "InOrder: " << "\t";
    while (temp || !s1.empty()) {
        if (temp) {
            s1.push(temp);
            temp = temp->left;
        } else {
            temp = s1.top();
            cout << temp->data << "\t";
            s1.pop();
            temp = temp->right;
        }
    }
    cout << endl;
}

void
printIterativePreOrder(t1 *head) {
    stack<t1 *> s1;
    t1 *temp = head;
    cout << "PreOrder: " << "\t";
    while (temp || !s1.empty()) {
        if (temp) {
            cout << temp->data << "\t";
            s1.push(temp);
            temp = temp->left;
        } else {
            temp = s1.top();
            s1.pop();
            temp = temp->right;
        }
    }
    cout << endl;
}

void
printIterativePostOrder(t1 *head) {
    stack<t1 *> s1;
    stack<t1 *> s2;
    t1 *temp = head;
    cout << "PostOrder: " << "\t";
    s1.push(temp);
    while (!s1.empty()) {
        temp = s1.top();
        s1.pop();
        s2.push(temp);
        if (temp->left) {
            s1.push(temp->left);
        }
        if (temp->right) {
            s1.push(temp->right);
        }
    }

    while(!s2.empty()) {
        temp = s2.top();
        s2.pop();
        cout << temp->data << "\t";
    }
    cout << endl;
}


void
printLevelOrder(t1 *head) {
    t1 *temp = head;
    queue<t1 *> q;
    q.push(temp);
    cout << "LevelOrder: " << "\t";
    while(!q.empty()) {
        temp = q.front();
        cout << temp->data << "\t";
        q.pop();
        if (temp->left) {
            q.push(temp->left);
        }
        if (temp->right) {
            q.push(temp->right);
        }
    }
    cout << endl;
}

int
countTotalNodes(t1 *head) {
    if (!head) {
        return 0;
    }

    return countTotalNodes(head->left) + countTotalNodes(head->right) + 1;
}

int
countNodesWithLeftRightNode(t1 *head) {
    int x,y;
    if (head) {
        x = countNodesWithLeftRightNode(head->left);
        y = countNodesWithLeftRightNode(head->right);

        if (head->left && head->right) {
            return x+y+1;
        } else {
            return x+y;
        }
    }

    return 0;
}


int
countHeight(t1 *head) {
    int x,y;
    if (head) {
        x = countHeight(head->left);
        y = countHeight(head->right);

        if (x > y) {
            return x+1;
        } else {
            return y+1;
        }
    }

    return 0;
}

int
countLeafNode(t1 *head) {
    int x,y;
    if (head) {
        x = countLeafNode(head->left);
        y = countLeafNode(head->right);
        if (!head->left && !head->right) {
        //    cout << head->data << "\t";
            return x+y+1;
        } else {
            return x+y;
        }
    }
    return 0;
}


void
printSpiralOrder(t1 *root) {
    cout << "SpiralOrder: " << "\t";
    int h=0;
    queue<t1 *> q;
    q.push(root);
    stack<int> s;
    while(!q.empty()){
        int size = q.size();
        while(size--){
            t1 *t = q.front();
            q.pop();
            if(h%2 != 0 && h!=0){
                cout<< t->data << "\t";
            }
            else{
                s.push(t->data);
            }
            if(t->left) q.push(t->left);
            if(t->right) q.push(t->right);
        }
        while(!s.empty()){
            cout<< s.top() << "\t";
            s.pop();
        }
        h++;
    }
	cout<<endl;
}

int main() {
    t1 *head = create(1);

//       1
//    2      3
// 4    5   6   7
//                 8

    head->left = create(2);
    head->right = create(3);
    head->left->left = create(4);
    head->left->right = create(5);
    head->right->left = create(6);
    head->right->right = create(7);
    head->right->right->right = create(8);
    printIterativeInorder(head);
    printIterativePreOrder(head);
    printIterativePostOrder(head);
    printLevelOrder(head);
    printSpiralOrder(head);
    cout << "Nodes of a tree is : " << countTotalNodes(head) << endl;
    cout << "Nodes with both Left & Right tree is: " << countNodesWithLeftRightNode(head) << endl;
    cout << "Height of a tree is: " << countHeight(head) << endl;
    cout << "Total leaf nodes: " << countLeafNode(head) << endl;
    return 0;
}

// output:
// gnraghav@gnraghav-mbp P1 % cd "/Users/gnraghav/Desktop/P1/" && g++ -std=c++17 bTreeIterative.cpp -o bTreeIterative && "/Users/gnraghav/Desktop/P1/"bTreeIterative
// InOrder:        4       2       5       1       6       3       7       8
// PreOrder:       1       2       4       5       3       6       7       8
// PostOrder:      4       5       2       6       8       7       3       1
// LevelOrder:     1       2       3       4       5       6       7       8
// Nodes of a tree is : 8
// Nodes with both Left & Right tree is: 3
// Height of a tree is: 4
