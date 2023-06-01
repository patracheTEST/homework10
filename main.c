/*
 * Binary Search Tree #2
 *
 * Data Structures
 *
 * School of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

/* for stack */
#define MAX_STACK_SIZE		20
Node* stack[MAX_STACK_SIZE];
int top = -1;


/* for queue */
#define MAX_QUEUE_SIZE		20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;



int initializeBST(Node** h);
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* functions that you have to implement */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int deleteNode(Node* head, int key);  /* delete the node for the key */
Node* pop();
void push(Node* aNode);
Node* deQueue();
void enQueue(Node* aNode);

/* you may add your own defined functions if necessary */


void printStack();



int main()
{
    printf("[----- [김상수] [2018038078] -----]");

	char command;
	int key;
	Node* head = NULL;

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;

		case 'l': case 'L':
			levelOrder(head->left);
			break;

		case 'p': case 'P':
			printStack();
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1;

	front = rear = -1;

	return 1;
}


/**
 * @brief 중위 순회
 * 
 * 왼쪽 자식부터 출력하는 함수(저번 주 과제에 나왔으니 짧게 적겠습니다.)
 * 
 * @param ptr 
 */
void recursiveInorder(Node* ptr)
{
	if(ptr) {
		recursiveInorder(ptr->left);
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right);
	}
}

/**
 * @brief 중위 순회(재귀 없이)
 * 
 * 왼쪽 자식 -> 부모 -> 오른쪽 자식 순으로 출력하는 함수이다.
 * 
 * @param node 
 */
void iterativeInorder(Node* node)
{
    for(;;)
	{
        // 먼저 들어온게 나중에 출력되는 스택을 이용해서 왼쪽 자식을 전부 스택에 넣는다.
		for(; node; node = node->left)
			push(node);
        // 가장 마지막에 넣은 노드, 가장 작은 리프노드가 될 것이다.
		node = pop();

        // 스택에 남아있는 값이 없어서 null 을 반환하면 종료한다.
		if(!node) break;
		printf(" [%d] ", node->key);

        // 오른쪽 자식노드로 변경
		node = node->right;
	}
}

/**
 * @brief 트리의 레벨 순서 순회 함수
 * 
 * 같은 레벨 순으로 출력을 레벨이 낮은 순으로, 왼쪽 부터 출력을 해준다.
 * 
 * @param ptr 
 */
void levelOrder(Node* ptr)
{
    // int front = rear = -1;

	if(!ptr) return; /* empty tree */

	enQueue(ptr);

	for(;;)
	{
		ptr = deQueue(); // 같은 레벨의 노드를 순서대로 deQueue해준다.
		if(ptr) {
			printf(" [%d] ", ptr->key);

			if(ptr->left) // 노드의 왼쪽 값이 있으면 큐에 넣어준다.
				enQueue(ptr->left);
			if(ptr->right) // 노드의 오른쪽 값이 있으면 큐에 넣어준다.
				enQueue(ptr->right);
		}
		else
			break;

	}
}


int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;

	Node* parentNode = NULL;
	while(ptr != NULL) {

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	/* linking the new node to the parent */
	if(parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}

/**
 * @brief 키 값을 검색해서 노드를 삭제하는 함수.
 * 
 * @param head 
 * @param key 
 * @return int 
 */
int deleteNode(Node* head, int key)
{
    // 트리가 비어있을 경우의 처리
    if (head == NULL) {
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	if (head->left == NULL) {
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	Node* root = head->left;

	Node* parent = NULL;
	Node* ptr = root;

    // 지울 노드를 찾아준다.
	while((ptr != NULL)&&(ptr->key != key)) {
		if(ptr->key != key) {

			parent = ptr;

			if(ptr->key > key)
				ptr = ptr->left;
			else
				ptr = ptr->right;
		}
	}

	// 지울 노드가 없을 경우(맞는 키가 없을 경우)
	if(ptr == NULL)
	{
		printf("No node for key [%d]\n ", key);
		return -1;
	}

	/*
	 * case 1: 자식 노드가 없는 노드일 경우의 처리
	 */
	if(ptr->left == NULL && ptr->right == NULL)
	{
        // 루트 노드인가 아닌가
        // 루트 노드가 아닌경우 왼쪽 오른쪽을 구분해서 지워주고
		if(parent != NULL) { 
			if(parent->left == ptr)
				parent->left = NULL;
			else
				parent->right = NULL;
		} else {
            // 루트 노드인 경우
			head->left = NULL;
		}

        // 지워준 노드를 할당 해제해준다.
		free(ptr);
		return 1;
	}

	/**
	 * case 2: 부모 노드일 경우, 자식 노드가 하나밖에 없을 경우
	 */
	if ((ptr->left == NULL || ptr->right == NULL))
	{
        // 자식 노드를 가져온다.
		Node* child;
		if (ptr->left != NULL)
			child = ptr->left;
		else
			child = ptr->right;

        // 루트 노드일 경우의 처리 분리
        // 루트 노드가 아닐 경우 현재 노드의 자리를 자식 노드에게 넘겨준다.
		if(parent != NULL)
		{
			if(parent->left == ptr)
				parent->left = child;
			else
				parent->right = child;
		} else {
			root = child;
		}

		free(ptr);
		return 1;
	}

	/**
	 * case 3: 부모 노드일 경우, 자식 노드가 둘 다 있을 경우
	 */

	Node* candidate;
	parent = ptr;

    // 지울 노드보다 큰 값의 트리인 오른쪽 트리를 가져와서
	candidate = ptr->right;
    // 그 중에서 가장 작은 노드를 가져온다.
	while(candidate->left != NULL)
	{
		parent = candidate;
		candidate = candidate->left;
	}
    // 위의 반복문을 실행 했는지 안했는지
    // 지울 노드의 오른쪽이 서브트리인지 단일 노드인지 에 따라.. 라고 생각했는데 이건 아님.
    // 지울 노드의 오론쪽 노드에 왼쪽 노드가 있는지 없는지에 따라(지울 노드의 오른쪽 노드가 지울 노드의 오른쪽 서브트리에서 가장 작은 값인 경우)
    // 노드의 연결을 바꿔준다.
	if (parent->right == candidate)
		parent->right = candidate->right;
	else
        // left가 아니라 candidate->right의 위치를 가져와 주는 이유는
        // candidate의 왼쪽 노드가 있을 경우는 없지만 오른쪽 노드는 있을 경우가 있기 때문이다.
		parent->left = candidate->right;

	ptr->key = candidate->key;

	free(candidate);
	return 1;
}


void freeNode(Node* ptr)
{
	if(ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)
{

	if(head->left == head)
	{
		free(head);
		return 1;
	}

	Node* p = head->left;

	freeNode(p);

	free(head);
	return 1;
}



Node* pop()
{
    if (top < 0) return NULL;
	return stack[top--];
}

void push(Node* aNode)
{
    stack[++top] = aNode;
}



Node* deQueue()
{
    if (front == rear) {
		// printf("\n....Now Queue is empty!!\n" );
		return NULL;
	}

	front = (front + 1) % MAX_QUEUE_SIZE;
	return queue[front];
}

void enQueue(Node* aNode)
{
    rear = (rear + 1) % MAX_QUEUE_SIZE;
	if (front == rear) {
		// printf("\n....Now Queue is full!!\n");
		return;
	}

	queue[rear] = aNode;
}

void printStack()
{
	int i = 0;
	printf("--- stack ---\n");
	while(i <= top)
	{
		printf("stack[%d] = %d\n", i, stack[i]->key);
	}
}