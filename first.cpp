#include <iostream>
using namespace std;
struct node
{
	int info;
	node *next;
};
struct List 
{
	node *head;
	node *tail;
};
node *getNode(int x)
{
	node *p = new node;
	p->info = x;
	p->next = nullptr;
	return p;
}
void Init(List &L)
{
	L.head = nullptr;
	L.tail = nullptr;
}
void addTail(List &L, int x)
{
	node *p = getNode(x);
	if(L.head == nullptr)
	{
		L.head = L.tail = p;
	}
	else
	{
		L.tail->next = p;
		L.tail = p;
	}
}
void addHead(List &L, int x)
{
	node *p = getNode(x);
	if(L.head == nullptr)
	{
		L.head = L.tail = p;
	}
	else
	{
		p->next = L.head;
		L.head = p;
	}
}
void delNode(List &L, int x)
{
	if(L.head == nullptr)
	{
		return;
	}
	node *p = L.head;
	node *k = nullptr;
	while(p != nullptr)
	{
		if(p->info == x) break;
		k = p;
		p = p->next;
	}
	if(p == nullptr) return;
	if(k == nullptr)
	{
		L.head = L.head->next;
		p->next = nullptr;
		delete p;
		p = nullptr;
	}
	else
	{
		k->next = p->next;
		if(k->next == nullptr) L.tail = k;
		p->next = nullptr;
		delete p;
		p =nullptr;
	}
}
void selectionSort(List &L)
{
	if(L.head == nullptr) return;
	node *p = L.head;
	while(p->next != nullptr)
	{
		node * Min_Node = p;
		node *q = p->next;
		while(q != nullptr)
		{
			if(q->info < Min_Node->info)
			{
				Min_Node = q;

			}
			q = q->next;
		}
		swap(p->info, Min_Node->info);
		p = p->next;
	}
}
void inputList(List &L)
{
	int n;
	cin >> n;
	int x;
	for(int i = 0; i < n; i++)
	{
		cin >> x;
		addTail(L, x);		
	}
}
void outputList(List L)
{
	if(L.head == nullptr) return;
	node *p = L.head;
	while(p != nullptr)
	{
		cout << p->info <<' ';
		p = p->next; 
	}
}
int main()
{
	List L;
	Init(L);
	inputList(L);
	outputList(L);
	
	return 0;
}
