#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    char data;
    struct node *left, *right;
} Node;

//grabs a char and makes a node out of it
Node* make_node(char c) {
    Node* n = (Node*)malloc(sizeof(Node));
    if (n != NULL) {
        n->data = c;
        n->left = n->right = NULL;
    }
    return n;
}

// parses a postfix expression and builds the tree
Node* parse_postfix(char* exp) {
    Node* stack[100]; // allocate a stack of 100 nodes
    int top = -1;

    for (int i = 0; exp[i] != '\0'; i++) {
        char current = exp[i];

        if (current == ' ' || current == '\t') continue; //skip whitespace

        Node* temp = make_node(current);

        // check if it's an operator
        if (current == '+' || current == '-' || current == '*' || current == '/') { //pop R then L child from stack
            temp->right = stack[top--];
            temp->left = stack[top--];
        }
        stack[++top] = temp;
    }
    return stack[top];
}

void show_prefix(Node* root) { //Root, L, R
    if (!root) return;
    printf("%c ", root->data);

    show_prefix(root->left);
    show_prefix(root->right);
}

void show_infix(Node* root) { //L, Root, R
    if (!root) return;
    if (root->left) printf("( ");

    show_infix(root->left);

    printf("%c ", root->data);

    show_infix(root->right);
    if (root->right) printf(") ");
}

void show_postfix(Node* root) { //L, R, Root
    if (!root) return;

    show_postfix(root->left);
    show_postfix(root->right);
    printf("%c ", root->data);
}

int calc(Node* root) { // evaluates the expression tree
    if (!root) return 0;

    if (!root->left && !root->right) {
        return root->data - '0';
    }

    int a = calc(root->left);
    int b = calc(root->right);

    if (root->data == '+') return a + b; // check operator and perform calculation
    if (root->data == '-') return a - b;
    if (root->data == '*') return a * b;
    if (root->data == '/') return (b != 0) ? (a / b) : 0;

    return 0;
}

int total_nodes(Node* root) { // counts total nodes in the tree
    return root ? 1 + total_nodes(root->left) + total_nodes(root->right) : 0;
}

int count_leaf_nodes(Node* root) { // counts leaf nodes in the tree
    if (!root) return 0;
    if (!root->left && !root->right) return 1;

    return count_leaf_nodes(root->left) + count_leaf_nodes(root->right);
}

int tree_height(Node* root) { //calculates the height of the tree
    if (!root) return -1;

    int lh = tree_height(root->left);
    int rh = tree_height(root->right);

    return (lh > rh ? lh : rh) + 1;
}

void free_tree(Node* root) { //frees memory allocated
    if (root) {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}