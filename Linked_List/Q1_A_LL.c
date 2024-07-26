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

int insertSortedLL(LinkedList *ll, int item)
{
	//목표:index값을 리턴해야한다
	//임시로 반환할 index값,이전값인 비교값 previousNode,임시로 생성해서 넣을 temp
	int index = 0;
	ListNode *previousNode = NULL,*temp;

	//ll의 헤드포인터가 비어있을경우(=처음 숫자를 넣는경우) 헤드에 삽입하고 0값(시작값) 리턴
	if(ll->head == NULL){
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = NULL;
		ll->head->item = item;
		++(ll->size);

		return 0;
	}

	//삽입할 노드 위치 탐색
	ListNode *targetNode = ll->head;

	//삽입할 노드가 끝까지 갈때까지(마지막 노드가 가리키는 노드는 NULL이기때문)
	while(targetNode != NULL){
		//값이 있으면 -1 반환
		if(targetNode->item == item)
			return -1;
		else if(targetNode->item > item){
			//없으면 temp를 생성해서 
			//메모리 할당
			temp = malloc(sizeof(ListNode));

			//연결 재설정
			temp->next = targetNode;
			temp->item = item;

			//뒤의 previousNode=targetNode; 부분을 보면 알겠지만 previousNode은 직전노드
			//직전노드에서도 연결 재설정
			if(previousNode!=NULL)
				previousNode->next = temp;
			else
			//삽입할 노드 위치가 첫번째라면(삽입할 item이 첫번째 값이 된다면) 헤더에 연결
				ll->head = temp;

			return index;
		}

		//못찾으면 이번 노드는 previousNode에,삽입할 노드는 이번노드의 다음 노드로 변경
		previousNode = targetNode;
		targetNode = targetNode->next;

		//연결리스트 사이즈를 1올린다
		//index값을 1 올린다
		++(ll->size);
		++index;
	}

	//삽입할 노드를 끝까지 검색해도 못찾는다면(모든 저장된 수가 item보다 값이 작으면)
	//삽입할 위치는 맨 마지막
	targetNode = malloc(sizeof(ListNode));
	targetNode->next = NULL;
	targetNode->item = item;

	previousNode->next = targetNode;
	++(ll->size);

	return index;
}

///////////////////////////////////////////////////////////////////////////////////

//리스트 전체 요소를 출력하는 함수
void printList(LinkedList *ll){

	//cur은 현재 검색 요소
	ListNode *cur;
	//리스트 자체가 처음부터 없으면 종료
	if (ll == NULL)
		return;
	//검색은 리스트 헤더부터 시작
	cur = ll->head;

	//검색 요소가 없다(=리스트 헤더가 없다)->리스트가 비었다
	if (cur == NULL)
		printf("Empty");
	//마지막노드까지 검색하기 전까지
	while (cur != NULL)
	{
		//검색 요소의 값을 출력하고 다음 검색으로 넘어간다
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}


void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	//마지막 노드까지 검색하기 전까지
	while (cur != NULL){
		//현재 노드가 가리키는 다음 노드를 임시로 저장
		tmp = cur->next;
		//현재 노드 삭제
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}

//노드 검색하는 함수
ListNode *findNode(LinkedList *ll, int index){

	//탐색용 임시 노드 설정	
	ListNode *temp;

	//리스트 자체가 없거나,인덱스 자체를 음수로 주거나,리스트 크기를 넘는 요소를 넣으면 NULL 리턴
	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	//임시노드는 리스트 헤더부터 연결
	temp = ll->head;

	//임시노드가 NULL일때 (헤더가 없다=리스트가 비었다) NULL 리턴
	if (temp == NULL)
		return NULL;

	//index가 음수가 될때까지(검색이 안될때까지) 검색
	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

//노드 삽입하는 함수
int insertNode(LinkedList *ll, int index, int value){

	//이전 노드인 pre 현재 노드인 cur 선언
	ListNode *pre, *cur;

	//리스트가 없거나, 인덱스가 음수거나 사이즈를 넘으면 반환
	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	//리스트 헤더가 없거나(리스트가 비어있거나) 첫번째 값이라면(index = 0) head에 설정
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
	// 이전 노드가 존재한다면(그 와중에 pre값에 이전 노드를 넣음),cur에 이전노드 다음 노드를 저장
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

//특정 노드 삭제 함수
int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	//첫번째 노드를 삭제하는거라면 헤더포인터를 재설정하면서 삭제
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
