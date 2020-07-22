#include<stdio.h>
#include<stdlib.h>


typedef struct Node {
   	struct Node *lchild;
   	char info;
   	struct Node *rchild;
} Node_t;   


#define MAX 128U

Node_t *get_node(char x);
void display(Node_t *p, int level);
void preorder(Node_t *p);
void inorder(Node_t *p);
void postorder(Node_t *p);
void levelorder(Node_t *p);
int height(Node_t *p);



Node_t *Queue[MAX];
size_t front, rear;
void Queue_Init(void);
int isEmpty(void);
int isFull(void);
int size(void);
int peek(Node_t *node);
void enqueue(Node_t *node);
Node_t *dequeue(void);


int main(int argc, char *argv[]) 
{
	(void)argc;
	(void)argv;


	Node_t *root = NULL;

	root = get_node('P');

	root->lchild = get_node('Q');
	root->rchild = get_node('R');

	
	root->lchild->lchild = get_node('A');
	root->lchild->rchild = get_node('B');

	
	root->rchild->lchild = get_node('X');

	preorder(root);

	printf("\n");
	
	inorder(root);

	printf("\n");

	postorder(root);

	printf("\n");

	levelorder(root);

	printf("\n");

	printf("Height = %d\n", height(root));


	return 0;


}



Node_t *get_node(char x)
{
	Node_t *node = (Node_t *)malloc(sizeof(Node_t));

	if (node == NULL) {
		printf("Memory Allocation failed...");
		exit(1);
	}

	node->lchild = NULL;
	node->info = x;
	node->rchild = NULL;

	return node;
}



void display(Node_t *p, int level)
{
	if (p == NULL) {
		return;
	}

	display(p->rchild, level + 1);

	printf("\n");

	for (int i = 0; i < level; i++) {
		printf("  ");
	}

	printf("%c", p->info);


	display(p->lchild, level + 1);
}



void preorder(Node_t *p)
{
	if (p == NULL) {
		return;
	}

	printf("%c --> ", p->info);
	preorder(p->lchild);
	preorder(p->rchild);

}



void inorder(Node_t *p)
{
	if (p == NULL) {
		return;
	}

	inorder(p->lchild);
	printf("%c --> ", p->info);
	inorder(p->rchild);

}



void postorder(Node_t *p)
{
	if (p == NULL) {
		return;
	}

	postorder(p->lchild);
	postorder(p->rchild);
	printf("%c --> ", p->info);
}



void levelorder(Node_t *p)
{
	if (p == NULL) {
		printf("Tree is empty\n");
		return;
	}

	enqueue(p);

	Node_t *temp;

	while (!isEmpty()) {
		temp = dequeue();
		printf("%c --> ", temp->info);
		if (temp->lchild != NULL) {
			enqueue(temp->lchild);
		}
		if (temp->rchild != NULL) {
			enqueue(temp->rchild);
		}
	}

}



int height(Node_t *p)
{
	if (p == NULL) {
		return 0;
	}

	int hl = height(p->lchild); 
	int hr = height(p->rchild);

	return 1 + ((hl > hr) ? hl : hr);

}




void Queue_Init(void)
{
	front = rear = 0;
}



int isEmpty(void)
{
	return (front == rear);

}



int isFull(void)
{
	return ((rear + 1) % MAX == front);

}



int size(void)
{
	return ((MAX + (rear - front)) % MAX);
}



int peek(Node_t *node)
{
	(void)node;

	if (isEmpty()) {
		return -1;
	}

	node = Queue[front];
	return 0;
}



void enqueue(Node_t *node)
{
	if (isFull()) {
		return;
	}

	Queue[rear] = node;
	
	rear = (rear + 1) % MAX;
}



Node_t *dequeue(void)
{
	Node_t *node;

	if (isEmpty()) {
		return NULL;
	}

	node = Queue[front];
	
	front = (front + 1) % MAX;

	return node;
}



