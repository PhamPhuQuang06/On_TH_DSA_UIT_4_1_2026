#include <iostream>
using namespace std;
int BinarySearch(int a[], int n, int x)
{
    int l = 0;
    int r = n - 1;
    while(l <= r)
    {
        int mid = (l + r)/2;
        if(a[mid] == x) return mid;
        if(a[mid] < x) l = mid + 1;
        else r = mid -1;
    }
    return -1;
}
void SelectionSort(int a[], int n)
{
    for(int i = 0; i < n - 1; i++)
    {
        int minIndx = i;
        for(int j = i + 1; j < n; j++)
        {
            if(a[j] < a[minIndx]) minIndx = j;
        }
        swap(a[i], a[minIndx]);
    }
}
void BubbleSort(int a[], int n)
{
    for(int i = 0; i < n - 1; i++ )
    {
        bool flag = false;
        for(int j = 0; j < n - i - 1; j++)
        {
            if(a[j] > a[j + 1]) 
            {
                swap(a[j], a[j + 1]);
                flag = true;
            }
        }
        if(flag == false) break;
    }
}
void QuickSort(int a[], int l, int r)
{
    int i = l;
    int j = r;
    int pivot = a[(l + r)/ 2];
    while(i <= j)
    {
        while(a[i] < pivot) ++i;
        while(a[j] > pivot) --j;
        if(i <= j)
        {
            swap(a[i], a[j]);
            ++i;
            --j;
        }
    }
    if(l < j) QuickSort(a, l, j);
    if(i < r) QuickSort(a, i, r);
}
void InsertionSort(int a[], int n)
{
    for(int i = 1; i < n; i++)
    {
        int j = i - 1;
        int key = a[i];
        while(j >= 0 && a[j] > key)
        {
            a[j + 1] = a[j];
            --j;
        }
        a[j + 1] = key;
    }
}
int main()
{

}