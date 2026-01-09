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
    if(L.head == nullptr) L.head = L.tail = p;
    else
    {
        L.tail->next = p;
        L.tail = p;
    }
}
void addHead(List &L, int x)
{
    node *p = getNode(x);
    if(L.head == nullptr) L.head = L.tail = p;
    else
    {
        p->next = L.head;
        L.head = p;
    }
}
void DelNode(List &L, int x)
{
    if(L.head == nullptr) return;
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
        p = nullptr;
    }
}
void addBetween(List &L, int key, int x)
{
    if(L.head == nullptr) return;
    node *p = L.head;
    while(p != nullptr)
    {
        if(p->info == key) break;
        p = p->next;
    }
    if(p == nullptr) return;
    else
    {
        node *k = getNode(x);
        k->next =p->next;
        if(k->next == nullptr) L.tail = k;
        p->next = k;
    }
}
void inputList(List &L, int n)
{
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
        cout << p->info << ' ';
        p = p->next;
    }
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    List L;
    Init(L);
    int n; cin >> n;
    inputList(L, n);
    outputList(L);
    return 0;
}