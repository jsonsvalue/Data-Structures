//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 1 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode{
	int item;
	struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist{
	int size;
	ListNode *head;
} LinkedList;			// You should not change the definition of LinkedList


///////////////////////// function prototypes ////////////////////////////////////

//You should not change the prototype of this function
int insertSortedLL(LinkedList *ll, int item);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode *findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll;
	int c, i, j;
	c = 1;

	//Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;

	printf("1: Insert an integer to the sorted linked list:\n");
	printf("2: Print the index of the most recent input value:\n");
	printf("3: Print sorted linked list:\n");
	printf("0: Quit:");

	while (c != 0)
	{
		printf("\nPlease input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			j = insertSortedLL(&ll, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			printf("The value %d was added at index %d\n", i, j);
			break;
		case 3:
			printf("The resulting sorted linked list is: ");
			printList(&ll);
			removeAllItems(&ll);
			break;
		case 0:
			removeAllItems(&ll);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}


	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////
// 1. 현재 연결 리스트에 해당 숫자가 존재한다면, 연결 리스트에 추가하지 말 것
// 2. 새로운 노드가 더해진 곳의 인덱스를 저장할 것 
// 3. 연결 리스트가 제대로 작동하지 않으면, -1을 출력할 것

int insertSortedLL(LinkedList *ll, int item)
{	/* add your code here */
	// 새로운 노드의 첫 주소를 동적 할당을 통해서 배정한다.
	// 새로운 노드를 형성할 때, LinkedList의 첫 주소와 내가 정렬하고자하는 데이터를 넣는다.

	ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
	newNode -> item = item;
	newNode -> next = NULL;
	int idx = 0;

	// 헤드 노드 자체가 존재하지 않는다면, 연결 리스트의 헤드 노드에 새로운 노드를 넣는다.
	if(ll->head == NULL){
		ll -> head =  newNode;
	}
	// 헤드 노드가 존재한다면, 헤드 노드를 지정하고 prev & curr을 통한 크기 비교를 해서 새롭게 형성한 노드를 삽입
	else{
		ListNode* curr = ll -> head;
		ListNode* prev = NULL;
		
		// 가장 끝 노드까지 순회 & 아이템의 크기 비교를 해서 인덱스를 기록
		while( curr!= NULL && curr->item < item ){
			prev = curr; 
			curr = curr->next;
			idx++;
		}
		
		// 기존의 노드와 삽입하고자 하는 노드의 데이터가 같을 시, -1을 돌려준다
		if( curr!= NULL && curr-> item == item ){
			free(newNode);
			return -1;
		}
		
		// 기존의 노드와 비교하려는 데이터 조건을 찾았다면, newNode -> next = curr / prev -> next = new Node  
		newNode -> next = curr;
		// 헤드 노드 보다 작은 수 일 경우, headNode 앞에 newNode를 넣는다
		if(prev == NULL){
			ll->head = newNode;
		}// 헤드 노드 보다 큰 수 일 경우, headNode 뒤에 newNode를 넣는다
		 else{
			prev -> next = newNode;
		}

	} 
		

}

///////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll){
	// 연결 리스트가 비어 있을 시, curr = ll -> head 
	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;

	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}


void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}


ListNode *findNode(LinkedList *ll, int index){

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0){
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}
