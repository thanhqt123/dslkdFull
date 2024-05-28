#include <iostream>
#include <string>
#include <sstream>
using namespace std;
struct NODE
{
    string id, name;
    int gpa;
    bool gender;
    NODE *next;
};
typedef NODE *node;
node taoNode(string id, string name, int gpa, bool gender)
{
    node newNode = new NODE;
    newNode->id = id;
    newNode->name = name;
    newNode->gpa = gpa;
    newNode->gender = gender;
    newNode->next = NULL;
    return newNode;
}
// Bổ sung một sinh viên có id là x, điểm gpa là y và gender là z vào đầu danh sách (Nếu id đã có trong danh sách thì không thêm)
void insF(node &head, string id, int gpa, bool gender)
{
    node p = head;
    while (p != NULL)
    {
        if (p->id == id)
        {
            return;
        }
        p = p->next;
    }
    node newNode = taoNode(id, "", gpa, gender);
    node current = head;
    if (head == NULL)
    {
        head = newNode;
    }
    else
    {
        newNode->next = head;
        head = newNode;
    }
}
// Bổ sung một sinh viên có id là x, điểm gpa là y và gender là z vào CUỐI danh sách (Nếu id đã có trong danh sách thì không thêm)
void insL(node &head, string id, int gpa, bool gender)
{
    node p = head;
    while (p != NULL)
    {
        if (p->id == id)
        {
            return;
        }
        p = p->next;
    }
    node newNode = taoNode(id, "", gpa, gender);

    if (head == NULL)
    {
        head = newNode;
    }
    else
    {
        node current = head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newNode;
    }
}
// Bổ sung một sinh viên có id là x, điểm gpa là y và gender là z vào trước vị trí k trong danh sách
void insP(node &head, string id, int gpa, bool gender, int k)
{
    node newNode = taoNode(id, "", gpa, gender);
    if (head == NULL || k == 1)
    {
        newNode->next = head;
        head = newNode;
    }
    else
    {
        int cnt = 1;
        node p = head;
        while (cnt < k - 1 && p->next != NULL)
        {
            p = p->next;
            cnt++;
        }
        newNode->next = p->next;
        p->next = newNode;
    }
}

void xoa2dau(string &s)
{
    // Xóa các ký tự khoảng trắng ở đầu chuỗi
    while (!s.empty() && s[0] == ' ')
    {
        s.erase(s.begin());
    }
    // Xóa các ký tự khoảng trắng ở cuối chuỗi
    while (!s.empty() && s[s.length() - 1] == ' ')
    {
        s.erase(s.end() - 1);
    }
}

void xoagiua(string &s)
{
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == ' ' && i + 1 < s.length() && s[i + 1] == ' ')
        {
            s.erase(s.begin() + i);
            i--;
        }
    }
}

void chuanhoa(string &s)
{
    xoa2dau(s);
    xoagiua(s);

    for (int i = 0; i < s.length(); i++)
    {
        s[i] = tolower(s[i]);
    }

    s[0] = toupper(s[0]);

    for (int i = 1; i < s.length(); i++)
    {
        if (s[i] == ' ')
        {
            s[i + 1] = toupper(s[i + 1]);
        }
    }
}
// upd x y: Cập nhật hồ sơ một sinh viên có id là x và name là y
void upd(node &head, string id, string name)
{
    node p = head;
    while (p != NULL)
    {
        if (p->id == id)
        {
            chuanhoa(name);
            p->name = name;
            return;
        }
        p = p->next;
    }
}
// sắp xếp danh sách theo thứ tự tăng dần của điểm gpa nếu gpa = nhau thi sx theo thu tu tăng dan của tên
void sx(node &head)
{
    node p = head;
    for (node i = head; i->next != NULL; i = i->next)
    {
        for (node j = i->next; j != NULL; j = j->next)
        {
            if (i->gpa > j->gpa || (i->gpa == j->gpa && (i->name > j->name)))
            {
                swap(i->id, j->id);
                swap(i->name, j->name);
                swap(i->gpa, j->gpa);
                swap(i->gender, j->gender);
            }
        }
    }
}

// Hiển thị số sinh viên trong danh sách trên 1 hàng theo điều kiện
// x = 0 : Tất cả sinh viên
// x = 1 : Số sinh viên có gpa >=80
// x = 2 : Số sinh viên có gpa < 80
int cnt(node &head, int x)
{
    int c = 0;
    if (x == 0)
    {
        node p = head;
        while (p != NULL)
        {
            c++;
            p = p->next;
        }
        return c;
    }
    else if (x == 1)
    {
        node p = head;
        while (p != NULL)
        {
            if (p->gpa >= 80)
            {
                c++;
            }
            p = p->next;
        }
        return c;
    }
    else
    {
        node p = head;
        while (p != NULL)
        {
            if (p->gpa < 80)
            {
                c++;
            }
            p = p->next;
        }
        return c;
    }
}

//: Kiểm tra danh sách sinh viên đã sắp xếp tăng dần theo điểm gpa va ten hay chưa và hiển thị

int check(node &head)
{
    //	Cach 1: O(n^2)
    for (node i = head; i->next != NULL; i = i->next)
    {
        for (node j = i->next; j != NULL; j = j->next)
        {
            if (i->gpa > j->gpa || (i->gpa == j->gpa && (i->name > j->name)))
            {
                return 0;
            }
        }
    }
    //	Cach 2: O(n)
    //	node p=head;
    //	while(p!=NULL && p->next!=NULL){
    //		if(p->gpa > p->next->gender || ( p->gpa== p->next->gpa && p->name>p->next->name ) ){
    //			return 0;
    //		}
    //		p=p->next;
    //	}
    //	return 1
    return 1;
}

// del1 x : Xóa node có id là x
void del1(node &head, string x)
{
    node p = head;
    node pre = NULL;
    if (head == NULL)
    {
        return;
    }

    while (p != NULL)
    {
        if (p->id == x)
        {
            if (pre == NULL)
            { // neu xoa node dau tien
                head = p->next;
            }
            else
            { // khong phai la node dau tien
                pre->next = p->next;
            }
            delete p;
            return;
        }
        else
        {
            pre = p;
            p = p->next;
        }
    }
}

// xóa tat ca  sv có gpa <75
void del2(node &head)
{
    if (head == NULL)
    {
        return;
    }
    else
    {
        node p = head;
        node pre = NULL;
        while (p != NULL)
        {
            if (p->gpa < 75)
            {
                // neu node xoa la node dau tien;
                if (pre == NULL)
                {
                    head = p->next;
                    delete p;
                    p = head;
                }
                // neu node xoa k phai la node dau tien
                else
                {
                    pre->next = p->next;
                    delete p;
                    p = pre->next;
                }
            }
            else
            {
                pre = p;
                p = p->next;
            }
        }
    }
}

// tìm kiếm sv có có id =x;
node sv(node &head, string x)
{
    if (head == NULL)
    {
        return NULL;
    }
    node p = head;
    while (p != NULL)
    {
        if (p->id == x)
        {
            return p;
        }
        p = p->next;
    }
    return NULL;
}

// xóa sinh vien cuoi danh sách
void del3(node &head)
{
    if (head == NULL)
    {
        return;
    }
    if (head->next == NULL)
    { // Nếu danh sách chỉ có một node
        delete head;
        head = NULL;
        return;
    }
    node p = head;
    while (p->next->next != NULL)
    { // Duyệt đến node áp chót
        p = p->next;
    }
    delete p->next; // Xóa node cuối
    p->next = NULL; // Cập nhật node áp chót thành node cuối
}

// xóa sinh vien dau danh sách
void del4(node &head)
{
    if (head == nullptr)
    { // Kiểm tra nếu danh sách rỗng
        return;
    }

    node p = head;     // Lưu con trỏ head hiện tại
    head = head->next; // Cập nhật con trỏ head tới node tiếp theo
    delete p;          // Xóa node đầu tiên
}

void in(node head)
{
    node p = head;
    while (p != NULL)
    {
        cout << p->id << "-" << p->name << "-" << p->gender << "-" << p->gpa << "\n";
        p = p->next;
    }
}

int main()
{
    node head = NULL;
    string lc;
    while (cin >> lc)
    {
        if (lc == "end")
        {
            break;
        }
        if (lc == "ins")
        {
            string id;
            int gpa;
            bool gender;
            cin >> id >> gpa >> gender;
            insF(head, id, gpa, gender);
        }
        if (lc == "insl")
        {
            string id;
            int gpa;
            bool gender;
            cin >> id >> gpa >> gender;
            insL(head, id, gpa, gender);
        }
        if (lc == "insp")
        {
            string id;
            int gpa;
            bool gender;
            cin >> id >> gpa >> gender;
            int p;
            cin >> p;
            insP(head, id, gpa, gender, p);
        }
        if (lc == "in")
        {
            in(head);
        }
        if (lc == "upd")
        {
            string id, name;
            cin >> id;
            cin.ignore();
            getline(cin, name);
            upd(head, id, name);
        }
        if (lc == "ord")
        {
            sx(head);
        }
        if (lc == "cnt")
        {
            int x;
            cin >> x;
            cout << cnt(head, x) << "\n";
        }
        if (lc == "check")
        {
            if (check(head))
            {
                cout << "YES" << "\n";
            }
            else
            {
                cout << "NO" << "\n";
            }
        }
        if (lc == "del1")
        {
            string x;
            cin >> x;
            del1(head, x);
        }
        if (lc == "del2")
        {
            del2(head);
        }
        if (lc == "del3")
        {
            del3(head);
        }
        if (lc == "del4")
        {
            del4(head);
        }
        if (lc == "search")
        {
            string id;
            cin >> id;
            node rs = sv(head, id);
            cout << rs->id << " " << rs->name << " " << rs->gpa << " " << rs->gender << "\n";
        }
    }
}
