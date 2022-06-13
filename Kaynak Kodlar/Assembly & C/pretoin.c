#include<stdio.h>
#include<string.h>
#include<malloc.h>

typedef struct tree_node *tree_ptr;

typedef struct tree_node
{
	tree_ptr left_child;
	char data;
	tree_ptr right_child;
	
} node_struct;

extern void create_tree(tree_ptr *top, char *evaluation, int elength);
extern void inorder(tree_ptr ptr, char *expression);
extern int calculate(tree_ptr node);


tree_ptr get_node(char data)
{
	tree_ptr node = (tree_ptr)malloc(sizeof(node_struct));
	
	node->data = data;
	node->left_child = NULL;
	node->right_child = NULL;
	
	return node;
}

int main()
{
	char input[1024];
	char expression[2048];
	
	tree_ptr root;
	
	for(scanf("%1024s%*[^\n]", input); strcmp(input, "EXIT") != 0; scanf("%1024s%*[^\n]", input))
	{
		create_tree(&root, input, strlen(input));
		inorder(root, expression);
		
		printf("Result:%s=%d\n", expression, calculate(root));
	}
	
	return 0;
}
