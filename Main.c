#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.c"

int main() {

    int user_input = 0;
    char buffer[100];
    Node* expression_root = NULL;

    while (1) { // Main menu loop
        printf("\nCalculator Menu:\n");
        printf(" 1. Load postfix expression\n 2. Print Prefix\n 3. Print Infix\n 4. Print Postfix\n");
        printf(" 5. Evaluate expression\n 6. Show Height, CountNodes, CountLeaves\n 7. Delete Current Tree\n 8. Quit\n");
        printf("Pick an option: ");

        if (scanf("%d", &user_input) != 1) break;
        getchar(); // clear the newline

        if (user_input == 8) break; //exit command

        switch (user_input) {
            case 1: //input postfix expression
                if (expression_root) free_tree(expression_root);
                printf("Enter expression: ");
                fgets(buffer, 100, stdin);
                buffer[strcspn(buffer, "\n")] = 0; // strip newline
                expression_root = parse_postfix(buffer);
                break;

            case 2: //show prefix
                if (expression_root) { show_prefix(expression_root); printf("\n"); }
                break;

            case 3: //show infix
                if (expression_root) { show_infix(expression_root); printf("\n"); }
                break;

            case 4: //show postfix
                if (expression_root) { show_postfix(expression_root); printf("\n"); }
                break;

            case 5: //solve, use calc function
                if (expression_root) {
                    printf("The result is: %d\n", calc(expression_root));
                }
                break;

            case 6: //tree info (height, total nodes, leaf nodes)
                if (expression_root) {
                    printf("Height: %d\n", tree_height(expression_root));
                    printf("Total Nodes: %d\n", total_nodes(expression_root));
                    printf("Leaf Nodes: %d\n", count_leaf_nodes(expression_root));
                }
                break;

            case 7: //clear memory
                free_tree(expression_root);
                expression_root = NULL;
                printf("Memory cleared.\n");
                break;

            default: //invalid input
                printf("Invalid choice, try again.\n");
                break;
        }
    }

    if (expression_root) free_tree(expression_root); //cleanup before exit
    printf("Exiting now\n");
    return 0;
}