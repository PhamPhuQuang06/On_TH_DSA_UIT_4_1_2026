#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
struct Node
{
    int info;
    Node *left;
    Node *right;
};
typedef Node* Tree;
Node *getNode(int x)
{
    Node *p = new Node;
    p->info = x;
    p->left = nullptr;
    p->right = nullptr;
    return p;
}
void insertNode(Tree &T, int x)
{
    if(T == nullptr)
    {
        T = getNode(x);
    }
    else
    {
        if(T->info == x) return;
        else if(T->info < x) insertNode(T->right, x);
        else insertNode(T->left, x);
    }
}
void inputTree(Tree &T, int n)
{
    int x;
    for(int i = 0; i < n; i++)
    {
        cin >> x;
        insertNode(T, x);
    }
}
void NLR(Tree T)
{
    if(T == nullptr) return;
    cout << T->info << ' ';
    NLR(T->left);
    NLR(T->right);
}
void LNR(Tree T)
{
    if(T == nullptr) return;
    LNR(T->left);
    cout << T->info << ' ';
    LNR(T->right);
}
void LRN(Tree T)
{
    if(T == nullptr) return;
    LRN(T->left);
    LRN(T->right);
    cout << T->info << ' ';
}
//ham dem so node
int DemNode(Tree T)
{
    if(T == nullptr) return 0;
    return 1 + DemNode(T->left) + DemNode(T->right);
}
// ham dem so la
int DemSoLa(Tree T)
{
    if(T == nullptr) return 0;
    int sum = 0;
    if(T->left == nullptr && T->right == nullptr) ++sum;
    return sum + DemSoLa(T->left) + DemSoLa(T->right);
}
// ham tinh chieu cao cua cay
int Height(Tree T)
{
    if(T == nullptr) return 0;
    int a = Height(T->left);
    int b = Height(T->right);
    return max(a, b) + 1;
}
//-------------chuyển tiền tự + trung tự sang cây--------------
//phần này đoán là sẽ ko ra th nhưng lý thuyết thì có ra=)))
//Ý tưởng thì: Phần tử đầu tiên của duyệt tiền tự luôn là node gốc. Từ đó
//xác định các ptu bên trái của node gốc trong trung tự thì nó bên nhánh trái ngược lại bên nhánh phải
//NGUỒN CHATGPT:
    Node* buildTree(
        vector<int>& preorder, int preL, int preR,
        vector<int>& inorder,  int inL,  int inR)
    {
        if(preL > preR || inL > inR) return nullptr;// nếu index bên trái > index bên phải thì nullptr tức là hết phần từ để thêm r á

        int rootVal = preorder[preL]; // lấy node gốc là phần tử đâu tiên của tiền tự
        Node* root = new Node(rootVal); // thêm mới node gốc vào

        // tìm vị trí root trong inorder
        int k = inL;
        while(inorder[k] != rootVal) k++;

        int leftSize = k - inL;

        root->left = buildTree(
            preorder, preL + 1, preL + leftSize,
            inorder,  inL, k - 1);// tiếp tục đệ quy bên nhanh trái

        root->right = buildTree(
            preorder, preL + leftSize + 1, preR,
            inorder,  k + 1, inR); // tiếp tục đệ quy bên nhánh phải

        return root;
    }

//-------------kiểm tra 2 cây giống nhau-------------
    bool isSameTree(Tree T1, Tree T2)
    {
        if(T1 == nullptr && T2 == nullptr)
            return true;

        if(T1 == nullptr || T2 == nullptr)
            return false;

        if(T1->info != T2->info)
            return false;

        return isSameTree(T1->left, T2->left) &&
               isSameTree(T1->right, T2->right);
    }
// ----------kiểm tra cây complete bt---------------- //cây nhị phân hoàn chỉnh
/*cây nhị phân hoàn chỉnh là cây mà tại mọi mức trừ mức cuối đều điển đầy đủ, còn mức cuối thì điền đầy từ trái qua phải
nếu giải thích không hiểu thì có thể tham khảo nguồn khác xem ảnh cho dễ hiểu
----Ý tưởng là thực hiện duyệt theo thứ tự cấp độ bắt đầu từ nút gốc.
Trong quá trình duyệt, khi tìm thấy một nút không phải là nút đầy đủ ,
tất cả các nút tiếp theo phải là nút lá. Một nút được coi là 'nút đầy đủ'
nếu cả con trái và con phải đều không rỗng (hoặc không phải NULL ). */
bool isCompleteBT(Tree T)
{
    if(T == nullptr) return true; //
    queue<Node *> q;
    q.push(T);
    bool End = false; // kiểm tra xem nút có đầy đủ hay không?
    while(!q.empty())
    {
        Node *curr = q.front();
        q.pop();
        if(curr->left != nullptr)
        {
            if(End == true)
            {
                return false;
            }
            q.push(curr->left);
        }
        else End = true; //tức là cập nhật cây nút này có cây con không có  nhánh trái
        if(curr->right != nullptr)
        {
            if(End == true) return false ;// nếu đã không có nhanh trái mà nhánh phải có thì ko hợp lê
            q.push(curr->right);
        }
        else End = true; // nếu curr->right == nullptr tức là rỗng thì cập nhật là end là nút đó không đầy đủ
    }
    return true;
}

// -------------kiểm tra cây perfect tree----------- // cây nhị phân hoàn hảo

/*cây hoàn hảo là cây như nào: cái tên thôi đã biết sơ rồi, là cây mà tất cả các nút không phải nút lá đều có 2 con
và tất cả nút lá có cùng độ cao. Thì để chứng minh xem thì cây đó có phải là Perfect BT không thì có ý tưởng sau:

    --Ý tưởng là thực hiện duyệt cây nhị phân theo thứ tự cấp độ bằng cách sử dụng hàng đợi .
    Bằng cách duyệt cây từng cấp độ một, ta có thể kiểm tra xem cây có thỏa mãn các điều kiện
    của một cây nhị phân hoàn hảo hay không .
    --ý tưởng này giống như duyệt theo BFS vậy đó, cô có gửi nội dung này tham khảo r*/
    bool isPerfect(Tree T)
    {
        if(T == nullptr) return true; // cây rỗng vẫn là cây hoàn hảo
        queue<Node *> q;
        q.push(T);
        int cnt = 1;
        while(!q.empty())// hàng đợi rỗng là dừng
        {
            if(cnt != q.size()) return false; // tại vì cnt tức đếm số phần tử có trong 1 mức và đồng thời q.size() chính là
        //số lượng phần tử đó. nếu không bằng tức là dùng phải cây hoàn hảo. Dựa vào tính chất 2^(h + 1)-1 của cây hoàn hảo
        //ngược lại nếu == thì sẽ: thêm các phần tử ở mức tiếp theo vào hàng đợi
            int siZe = q.size();
            while(siZe--)
            {
                Node *curr = q.front();
                q.pop();
                if(curr->left != nullptr) q.push(curr->left);
                if(curr->right != nullptr) q.push(curr->right);
                //dựa vào tính chất "vào trước ra trước" của queue
                //Note: Stack là "vào sau ra trước"
            }
            cnt *= 2; // vì đến mức tiếp theo thì số lượng nút bằng 2 lần số lượng ptu ở mức trước.
            //ví dụ: mức 0 có 1 ptu là gốc
            //       mức 1 có 2 phần tử
                    //mức 2 có 4 phần tử
                    // mức 3 có 8pt
                    //......

        }
        return true;
    }
// --------kiểm tra cây balance bt--------
        /*
            ý tưởng: cây balance BT là cây mà tại mọi node có chiều cao cây con bên trái và cây con bên phải không
            chênh lệch nhau hơn 1 đơn vị. tức là   |height(left) - height(right)| <= 1
            vậy cần viết hàm tính chiều cao và duyệt đệ quy thôi

        */
        bool BalanceBT(Tree T)
        {
            if(T == nullptr) return true; // cây rỗng vẫn là cây cân bằng. Theo lý thuyết là v, nhưng tùy đề
            int HR = Height(T->right);
            int HL = Height(T->left);
            if(abs(HR - HL) > 1) return false;
            return BalanceBT(T->left)&& BalanceBT(T->right);  // nhưng cách này nó tốn rất nhiều thời gian(vì Height) nên thường
            // chuyển sang vừa tính chiều cao vừa kiểm tra tính cân bằng (Gộp chung 1 hàm)
        }
        int BalanceBTVersion2(Tree T)
        {
            if(T == nullptr) return 0;
            int HL = BalanceBTVersion2(T->left);
            if(HL == -1) return -1;
            int HR = BalanceBTVersion2(T->right);
            if(HR == -1) return -1;
            if(abs(HR - HL) > 1) return -1;
            return (HR > HL? HR : HL) + 1;//toán tử 3 ngồi khi đếu cho dùng max
        }


// -----------tìm node---------------
bool FindNode(Tree T, int x)
{
    if(T == nullptr) return false;
    if(T->info == x) return true;
    else if(T->info < x) return FindNode(T->right, x);
    else return FindNode(T->left, x);
}
// ----------tìm min trong cay BST----------
int MinOfBSTree(Tree T)
{

    if(T == nullptr) return -1;
    if(T->left == nullptr) return T->info;
    return MinOfBSTree(T->left);
}
// ---------Tim min trong cay BT----------
int MinOfBTree(Tree T)
{
    if(T == nullptr) return INT_MAX;
    int Min = T->info;
    int MinR = MinOfBTree(T->right);
    int MinL = MinOfBTree(T->left);
    if(Min > MinR ) Min = MinR;
    if(Min > MinL) Min = MinL;
    return Min;
}
// -------tìm max trong cay BST--------
int MaxOfBSTree(Tree T)
{
    if(T == nullptr)
    {
        return -1;
    }
    if(T->right == nullptr) return T->info;
    return MaxOfBSTree(T->right);
}
// --------tìm max trong cay BT--------
int MaxOfBTree(Tree T)
{
    if(T == nullptr) return INT_MIN;
    int Max = T->info;
    int MaxR = MaxOfBTree(T->right);
    int MaxL = MaxOfBTree(T->left);
    if(MaxR > Max) Max = MaxR;
    if(MaxL > Max) Max = MaxL;
    return Max;
}
// ---------xóa node---------
void DelNode(Tree T, int x)
{
    if(T == nullptr) return;
    if(T->info < x) DelNode(T->right, x);
    else if(T->info > x) DelNode(T->left, x);
    else
    {
        if(T->left == nullptr && T->right == nullptr)
        {
            delete T;
            T = nullptr;
            return;
        }
        else if(T->left != nullptr && T->right == nullptr)
        {
            Node *p = T;
            T = T->left;
            delete p;
            p = nullptr;
            return;
        }
        else if(T->right != nullptr && T->left == nullptr)
        {
          Node *p = T;
          T = T->right;
          delete p;
          p = nullptr;
          return;
        }
        else
        {
            // phải tìm node thế mạng: có 2 cách tìm là trái nhất bên nhánh phải và phải nhất bên nhánh trái
            //ở đây là phải nhất bên nhánh trái, tùy đề bài yêu cầu thì lựa giải pháp phù hợp
            Node *p = T->left;
            while(p->right != nullptr)
            {
                p = p->right;
            }
            T->info = p->info; // thay thế giá trị của node thế mạng cho node xóa
            // xóa node đó đi
            DelNode(T, p->info);

        }
    }
}
// ------chuyển BT sang BST-------
/*
    Ý tưởng: Ý tưởng là duyệt cây nhị phân một cách đệ quy và
    lưu trữ các nút vào một mảng . Sắp xếp mảng, sau đó thực
    hiện duyệt cây theo thứ tự trung tố và cập nhật giá trị
    của mỗi nút thành giá trị tương ứng trong cây.
*/
  //vậy đầu tiền cần duyệt cây nhị phân theo đệ quy và lưu vào 1 vector hay gì đó để lưu trữ:
    void DuyetAndLuu(Tree T, vector<int> &nodes)
    {
        // duyệt theeo NLR hay LNR, LRN cũng đc hết
        // ở đây duyệt theo LNR
        if(T == nullptr) return;
        DuyetAndLuu(T->left, nodes);
        nodes.push_back(T->info);
        DuyetAndLuu(T->right, nodes);
    }
    void ConVertBST(Tree &T, vector<int> nodes, int idx)
    {
        if(T == nullptr) return;
        ConVertBST(T->left, nodes, idx);
        T->info = nodes[idx]; ++idx;
        ConVertBST(T->right, nodes, idx);
    }
    //Cần phải sắp xếp vector đó tăng dần vì duyệt cây BST theo LNR thì thứ tự của dãy đó là tăng dần,
    //dựa vào đó để chuyển BT to BST
    void BTtoBST(Tree &T)
    {
        vector<int> nodes;
        DuyetAndLuu(T, nodes);
        sort(nodes.begin(), nodes.end()) ;// begin(), end() là iterator gì đó, có thể kiếm tài liệu đọc nếu có thắc mắc. Tau quên r
        int idx = 0;
        //Cần phải có 1 hàm để gán từng giá trị theo cách duyệt LNR để không thay đổi cấu trúc cây
        //có nghĩa là duyệt lại cây cũ theo LNR và gan lại từng giá trị trong vector để chuyển sang BST:
        ConVertBST(T, nodes, idx);
    }

// --------duyệt cây theo chiều rộng----------
//CÔ CÓ GỬI THAM KHẢO TRONG COURSE TỰ LÊN COI ĐI
int main()
{
    Tree T = nullptr;
    int n;
    cin >> n;
    inputTree(T, n);
    NLR(T);
    return 0;
}
