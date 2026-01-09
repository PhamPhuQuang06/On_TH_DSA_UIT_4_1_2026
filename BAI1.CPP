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
void InitList(List &L)
{
    L.head = NULL;
    L.tail = NULL;
}
node *getNode(int x)
{
    node *p = new node;
    p->info = x;
    p->next = NULL;
    return p;
}
void addTail(List &L, int x)
{
    node *p = getNode(x);
    if(L.head == NULL) 
    {
        L.head = L.tail = p;
        return;
    }
    L.tail->next = p;
    L.tail = p;
}
bool findList(List L, int x)
{
    if(L.head == NULL) return false;
    node *p = L.head;
    while(p != NULL)
    {
        if(p->info == x) return true;
        p = p->next;
    }
    return false;
}
void delNode(List &L, int x)
{
    if(L.head == NULL) return;
    node *p = L.head;
    node *k = NULL;
    while(p != NULL)
    {
        if(p->info == x) break;
        k = p;
        p = p->next;
    }
    if(k == NULL)
    {
        L.head = L.head->next;
        p->next = NULL;
        if(L.head == NULL) L.tail = NULL;
    }
    else
    {
        k->next = p->next;
        if(p->next == NULL) 
        {
            L.tail = k;
        }
        else p->next = NULL;
    }
    delete p;
}
void outputList(List L)
{
    if(L.head == NULL) return;
    node *p = L.head;
    while(p != NULL)
    {
        cout << p->info << ' ';
        p = p->next;
    }
}
struct Hash
{
    int m; //số địa chỉ có trong bảng băm
    List *bucket;
    int n; //số lượng ptu có trong bảng băm
};
void InitHash(Hash &H)
{
    H.n = 0;
    H.bucket = new List[H.m];
    for(int i = 0; i < H.m; i++)
    {
        InitList(H.bucket[i]);
    }
    
}
int HashFunc(Hash H, int x)
{
    return x % H.m;
}
void insertHash(Hash &H, int x)
{
    int index = HashFunc(H, x);
    if(H.n == H.m) return;
    addTail(H.bucket[index], x);
    ++H.n;
}
bool findHash(Hash H, int x)
{
    int index = HashFunc(H, x);
    return findList(H.bucket[index], x);
}
void deleteHash(Hash &H, int x)
{
    int index = HashFunc(H, x);
    delNode(H.bucket[index], x);
    --H.n;
}
void inputHash(Hash &H, int n)
{
    int x;
    for(int i = 0; i < n; i++)
    {
        cin >> x;
        insertHash(H, x);
    }
}
void outputHash(Hash H)
{
    for(int i = 0; i < H.m; i++ )
    {
        outputList(H.bucket[i]);
    }
}
int main()
{
    Hash H;
    cout << "Nhap m: ";
    cin >> H.m;
    InitHash(H);
    cout << "Nhap n: ";
    int n; cin >> n;
    inputHash(H, n);
    if(findHash(H, 3)) cout << "YES\n";
    else cout << "NO\n";
    deleteHash(H, 3);
    outputHash(H);
    return 0;
}