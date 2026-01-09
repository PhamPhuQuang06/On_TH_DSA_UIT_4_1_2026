#include <iostream>
using namespace std;
struct Hash
{
    int m; //kich thuoc
    int n; //so ptu da co trong bang bam
    int *bucket;
};
void InitHash(Hash &H)
{
    H.n = 0;
    H.bucket = new int [H.m];
    for(int i = 0; i < H.m; i++)
    {
        H.bucket[i] = 0;
    }
}
int HashFunc(Hash H, int x)
{
    return x % H.m;
}
int HashFuncL(Hash H, int x, int &i)
{
    int hk = HashFunc(H, x);
    return (hk + i) % H.m;
   // return 
}
bool ktr(Hash H, int index)
{
    if(H.bucket[index] == 0) return true;
    else return false;
}
void insertHash(Hash &H, int x)
{
    int i = 0;
    int index = HashFunc(H, x);
    if(ktr(H, index)) H.bucket[index] = x;
    else
    {
      
        while(ktr(H, index))
        {
            int bamlai = HashFuncL(H, x, i);
            index = bamlai;
        }
        H.bucket[index] = x;
    }
}
void inputHash(Hash &H, int n)
{
    int x;
    for(int i = 0; i < n; i++)
    {
        cin >> x;
        insertHash(H, x );
        ++H.n;
    }
}
void outputHash(Hash H)
{
    for(int i = 0; i < H.m; i++)
    {
        cout << H.bucket[i] << ' ';
    }
}
int main()
{
    Hash H;
    cin >> H.m;
    int n; cin >> n;
    InitHash(H);
    inputHash(H, n);
    outputHash(H);
    return 0;
}