//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 5 */

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

// You should not change the prototype of this function
void frontBackSplitLinkedList(LinkedList* ll, LinkedList *resultFrontList, LinkedList *resultBackList);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *l);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


///////////////////////////// main() /////////////////////////////////////////////

int main()
{
	int c, i;
	LinkedList ll;
	LinkedList resultFrontList, resultBackList;

	//Initialize the linked list as an empty linked list
	ll.head = NULL;
	ll.size = 0;

	//Initialize the front linked list as an empty linked list
	resultFrontList.head = NULL;
	resultFrontList.size = 0;

	// Initialize the back linked list as an empty linked list
	resultBackList.head = NULL;
	resultBackList.size = 0;

	printf("1: Insert an integer to the linked list:\n");
	printf("2: Split the linked list into two linked lists, frontList and backList:\n");
	printf("0: Quit:\n");

	while (c != 0)
	{
	    printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			insertNode(&ll, ll.size, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			printf("The resulting linked lists after splitting the given linked list are:\n");
			frontBackSplitLinkedList(&ll, &resultFrontList, &resultBackList); // You need to code this function
			printf("Front linked list: ");
			printList(&resultFrontList);
			printf("Back linked list: ");
			printList(&resultBackList);
			printf("\n");
			removeAllItems(&ll);
			removeAllItems(&resultFrontList);
			removeAllItems(&resultBackList);
			break;
		case 0:
			removeAllItems(&ll);
			removeAllItems(&resultFrontList);
			removeAllItems(&resultBackList);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void frontBackSplitLinkedList(LinkedList *ll, LinkedList *resultFrontList, LinkedList *resultBackList)
{
	//나눠야될 부분인 sliceIndex,검색하면서 위치를 찾는 indexCount
	int sliceIndex,indexCount = 0;
	//삽입해야할 노드인 targetNode,각각의 검색 직전 노드인 prevFront,prevBack
	ListNode *targetNode,*previousFrontNode,*previousBackNode;
	
	if(ll == NULL)
		return;

	//targetNode를 포인터헤더로,각각의 prevNode들은 NULL로 초기화
	targetNode = ll->head;
	previousFrontNode = NULL;
	previousBackNode = NULL;

	//sliceIndex가 홀수면 +1,아니면 그냥 반으로 나눈다
	//나중에 보니 sliceIndex = li->size/2 + li->size%2로 해도됨
	if(ll->size %2 ==1)
		sliceIndex = ll->size / 2 + 1;
	else
		sliceIndex = ll->size / 2;

	//targetNode가 끝까지 갔을때 종료
	while(targetNode != NULL){
		//sliceIndex보다 작으면(기준보다 작다면,기준보다 왼쪽이라면)prevFront에 저장
		if(indexCount < sliceIndex){
			if(previousFrontNode == NULL){
				resultFrontList->head = targetNode;
			}
			else{
				previousFrontNode->next = targetNode;
			}
			//직전 노드에 타겟노드를 설정한다
			previousFrontNode = targetNode;
			//frontList의 크기를 늘려야한다
			//안그러면 나중에 검색,삽입,참조할때 size 참조하는데 귀찮아짐
			++(resultFrontList->size);
		}
		else{
			if(previousBackNode == NULL){
				resultBackList->head = targetNode;
			}
			else{
				previousBackNode->next = targetNode;
			}
			previousBackNode = targetNode;
			++(resultBackList->size);
		}
		//타겟노드를 다음 타겟노드로 이동시킨다
		targetNode = targetNode->next;
		++indexCount;
	}

	//타겟노드를 의도하던 위치로 이동시킨 다음에는 기존에 있던 다음노드의 연결상태를 끊어야한다
	//안그러면 2,3,5,6,7일시 연결 그대로 유지되서 2,3,5,6,7과 6,7,로 남음 
	if (previousFrontNode != NULL) {
        previousFrontNode->next = NULL;
    }

	//원본 ll을 분할하면서 각각의 nodeList가 원본을 참조하는데,
	//원본을 해제해두지않으면 나중에 각각 메모리해제할때 이중메모리해제가 발생할수 있음
	ll->head = NULL;
	ll->size = 0;
}

///////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll){

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


ListNode * findNode(LinkedList *ll, int index){

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
