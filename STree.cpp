#include "STree.h"

vector<STree> AllLeaf;
string* siting;

// 创建一个函数，使其能够在结点的孩子们中寻找与给定值相同的孩子，返回其指针，若未找到则返回NULL
STree FindChild(const STree& ST, const string& site)
{
    auto q = ST->children;
    while (q && q->data != site && q->nextsibling)
        q = q->nextsibling;
    if (q && q->data == site)
        return q;
    else
        return NULL;
}

Status InitSTree(STree& ST, const string& data)
{
    ST = new STNode();
    ST->parent = ST;
    ST->data = data;
    ST->nextsibling = NULL;
    ST->children = NULL;
    return OK;
}

Status Insertchild(STree& ST, const string& data)
{
    if (FindChild(ST, data) != NULL)
        return OK;
    if (!ST->children)
    {
        STree p = new STNode();
        p->parent = ST;
        p->data = data;
        p->nextsibling = NULL;
        p->children = NULL;
        ST->children = p;
        return OK;
    }
    else
    {
        STree p = ST->children;
        while (p->nextsibling)
            p = p->nextsibling;
        STree q = new STNode();
        q->parent = ST;
        q->data = data;
        q->children = NULL;
        q->nextsibling = NULL;
        p->nextsibling = q;
        return OK;
    }
}

Status DeleteNode(STree& ST)
{
    if (ST->parent == ST)
    {
        STree p = ST;
        ST = ST->nextsibling;
        delete p;
        p = NULL;
        return OK;
    }
    else if (ST->parent->children == ST)
    {
        ST->parent->children = ST->nextsibling;
        delete ST;
        ST = NULL;
        return OK;
    }
    else
    {
        STree p = ST->parent->children;
        while (p->nextsibling != ST)
            p = p->nextsibling;
        p->nextsibling = ST->nextsibling;
        delete ST;
        ST = NULL;
        return OK;
    }
}

int PushSite(const string& site, STree& ST)
{
    if (!Valid(site))
        return 0;
    stack<string> s;  // 创建一个用于存储string类型的stack用作临时的存储器
    auto iter1 = site.begin();  // 一号迭代器指示每一段域名的首个字母
    auto iter2 = site.begin();  // 二号迭代器在域名压栈时指示其后的"."
    string part[4];
    int i = 0; // i用以计入段数
    while (!(iter1 == iter2 && iter2 == site.end()))
    {
        while (iter2 != site.end() && *iter2 != '.')
            ++iter2;
        for (iter1; iter1 != iter2; ++iter1)
        {
            part[i] += *iter1;
        }
        if (iter2 != site.end())
        {
            ++iter1;
            ++iter2;
        }
        s.push(part[i]);
        ++i;
    }
    auto p = ST;
    while (!s.empty())
    {
        Insertchild(p, s.top());
        p = FindChild(p, s.top());
        s.pop();
    } // 将临时存储栈中的元素逐个添加入域名树中
    if (part[0] != "www")
        Insertchild(p, "www");
    return 1;
}

int SearchSite(const string& site, STree& ST)
{
    stack<string> s;  // 创建一个用于存储string类型的stack用作临时的存储器
    auto iter1 = site.begin();  // 一号迭代器指示每一段域名的首个字母
    auto iter2 = site.begin();  // 二号迭代器在域名压栈时指示其后的"."
    string part[4];
    int i = 0; // i用以计入段数
    while (!(iter1 == iter2 && iter2 == site.end()))
    {
        while (iter2 != site.end() && *iter2 != '.')
            ++iter2;
        for (iter1; iter1 != iter2; ++iter1)
        {
            part[i] += *iter1;
        }
        if (iter2 != site.end())
        {
            ++iter1;
            ++iter2;
        }
        s.push(part[i]);
        ++i;
    }
    auto p = ST;
    while (!s.empty())
    {
        if (!FindChild(p, s.top()))
            return 0;
        p = FindChild(p, s.top());
        s.pop();
    } // 逐段验证临时栈中的域名是否存在
    return 1;
}

int DeleteSite(const string& site, STree& ST)
{
    stack<string> s;  // 创建一个用于存储string类型的stack用作临时的存储器
    auto iter1 = site.begin();  // 一号迭代器指示每一段域名的首个字母
    auto iter2 = site.begin();  // 二号迭代器在域名压栈时指示其后的"."
    string part[4];
    int i = 0; // i用以计入段数
    while (!(iter1 == iter2 && iter2 == site.end()))
    {
        while (iter2 != site.end() && *iter2 != '.')
            ++iter2;
        for (iter1; iter1 != iter2; ++iter1)
        {
            part[i] += *iter1;
        }
        if (iter2 != site.end())
        {
            ++iter1;
            ++iter2;
        }
        s.push(part[i]);
        ++i;
    }
    auto p = ST;
    while (!s.empty())
    {
        if (!FindChild(p, s.top()))
            return 0;
        p = FindChild(p, s.top());
        s.pop();
    } // 逐段验证临时栈中的域名是否存在
    // 以上代码和查找域名的代码相同
    for (int j = 0; j != i; ++j)
    {
        s.push(part[j]);
    } // 再次将键入的域名压栈
    auto q = ST;
    while (!s.empty())
    {
        q = FindChild(q, s.top());
        s.pop();
    } // 令指针变量q指向域名地址的叶子节点
    while (!(q->nextsibling || q->parent->children != q || q == ST))
    {
        q = q->parent;
    } // 寻找应该删除的结点位置
    if (q == ST)
    {
        DeleteNode(q->children);
        return 1;
    }
    else
    {
        DeleteNode(q);
        return 1;
    }
}

int ChangeSite(const string& site, const string& change, STree& ST)
{
    if (!DeleteSite(site, ST))
        return 0;
    else
    {
        if (PushSite(change, ST))
            return 0;
        return 1;
    }
}

void FindLeaf(const STree& ST)
{
    AllLeaf.clear();
    queue<STree> q;
    q.push(ST);
    STree p;
    while (!q.empty())
    {
        p = q.front();
        if (p->children)
            q.push(p->children);
        else
            AllLeaf.push_back(p);
        if (p->nextsibling)
            q.push(p->nextsibling);
        q.pop();
    }
    return;
}

Status STreeTraverse(const STree& ST)
{
    FindLeaf(ST);
    siting = new string[AllLeaf.size()];
    int i = 0;
    for (auto& p : AllLeaf)
    {
        siting[i] = "";
        auto q = p;
        while (q->parent != ST)
        {
            siting[i]+=q->data+".";
            q = q->parent;
        }
        siting[i] += q->data;
        ++i;
    }
    return OK;
}

Status Valid(const string& site)
{
    if (site.size() > 255)
        return ERROR;
    for (auto c : site)
    {
        if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '.' || (c >= '0' && c <= '9' || c == '-')))
            return ERROR;
    }
    stack<string> s;  // 创建一个用于存储string类型的stack用作临时的存储器
    auto iter1 = site.begin();  // 一号迭代器指示每一段域名的首个字母
    auto iter2 = site.begin();  // 二号迭代器在域名压栈时指示其后的"."
    string part[4];
    int i = 0; // i用以计入段数
    while (!(iter1 == iter2 && iter2 == site.end()))
    {
        if (i >= 4)
            return ERROR;
        while (iter2 != site.end() && *iter2 != '.')
            ++iter2;
        for (iter1; iter1 != iter2; ++iter1)
        {
            part[i] += *iter1;
        }
        if (iter2 != site.end())
        {
            ++iter1;
            ++iter2;
        }
        if (part[i].size() > 63 || part[i][0] == '-')
            return ERROR;
        s.push(part[i]);
        ++i;
    }
    if ((i == 4 && part[0] != "www") || i == 1)
        return ERROR;
    ifstream head;
    head.open("head.dat", ios::in);
    string h;
    while (head >> h)
    {
        if (part[i - 1] == h)
            return OK;
    }
    head.close();
    return ERROR;
}

void Menu()
{
    system("color F0");
    cout << "欢迎来到互联网域名信息管理系统，输入密码以登录:" << endl;
    string code;
    cin >> code;
    if (code != "123456")
    {
        cout << "密码错误！" << endl;
        return;
    }
    cout << "欢迎！Administrator" << endl;
    cout << endl;
    cout << "|----------------------------------------------------------------------------------------------------------------------|" << endl;
    cout << "|-----------------------------------------------互联网域名信息管理系统-------------------------------------------------|" << endl;
    cout << "|----------------------------------------------------------------------------------------------------------------------|" << endl;
    cout << "|.......................................................0.退出.........................................................|" << endl;
    cout << "|.....................................................1.创建新库.......................................................|" << endl;
    cout << "|.....................................................2.导入原库.......................................................|" << endl;
    cout << "|.....................................................3.添加域名.......................................................|" << endl;
    cout << "|.....................................................4.删除域名.......................................................|" << endl;
    cout << "|.....................................................5.查找域名.......................................................|" << endl;
    cout << "|....................................................6.导出域名库......................................................|" << endl;
    cout << "|----------------------------------------------------------------------------------------------------------------------|" << endl;
    int button = 1;
    STree ST;
    InitSTree(ST, "ym");
    string dat, change;
    fstream inf;
    while (button)
    {
        cout << "键入序号以执行操作:" << endl;
        cin >> button;
        switch (button)
        {
        case 1:
            if (ST->children)
            {
                cout << "当前暂存库已有一个域名库，是否将当前库导出并清空？" << endl;
                cout << "1.是                                          2.否" << endl;
                cin >> button;
                while (button != 1 && button != 2)
                {
                    cout << "输入有误！请重新输入:" << endl;
                    cin >> button;
                }
                if (button == 1)
                {
                    ;
                }
                else
                {
                    cout << "取消创建新库完成" << endl;
                }
                cout << "|----------------------------------------------------------------------------------------------------------------------|" << endl;
            }
            else
            {
                cout << "创建完毕！当前库中域名数为：0" << endl;
                cout << "|----------------------------------------------------------------------------------------------------------------------|" << endl;
            }
            break;
        case 2:
            inf.open("web.dat", ios::in | ios::out);
            while (inf >> dat)
            {
                transform(dat.begin(), dat.end(), dat.begin(), ::towlower);
                PushSite(dat, ST);
            }
            inf.close();
            FindLeaf(ST);
            cout << "导入成功！当前暂存库中域名数为：" << AllLeaf.size() << endl;
            cout << "|----------------------------------------------------------------------------------------------------------------------|" << endl;
            break;
        case 3:
            cout << "请输入您想添加的域名：" << endl;
            cin >> dat;
            transform(dat.begin(), dat.end(), dat.begin(), ::towlower);
            if (SearchSite(dat, ST))
            {
                cout << "该域名已存在于暂存库中！" << endl;
            }
            else
            {
                if (PushSite(dat, ST))
                {
                    FindLeaf(ST);
                    cout << "添加成功！当前暂存库中域名数为：" << AllLeaf.size() << endl;
                }
                else
                    cout << "添加失败！域名不合法" << endl;
            }
            cout << "|----------------------------------------------------------------------------------------------------------------------|" << endl;
            break;
        case 4:
            cout << "请输入您想删除的域名：" << endl;
            cin >> dat;
            transform(dat.begin(), dat.end(), dat.begin(), ::towlower);
            if (DeleteSite(dat, ST))
            {
                FindLeaf(ST);
                cout << "删除成功！当前暂存库中域名数为：" << AllLeaf.size() << endl;
            }
            else
                cout << "当前暂存库中不存在该域名！" << endl;
            cout << "|----------------------------------------------------------------------------------------------------------------------|" << endl;
            break;
        case 5:
            cout << "请输入您想查找的域名：" << endl;
            cin >> dat;
            transform(dat.begin(), dat.end(), dat.begin(), ::towlower);
            if (SearchSite(dat, ST))
            {
                cout << "该域名在暂存库中，是否对其进行修改：" << endl;
                cout << "1.是                            2.否" << endl;
                cin >> button;
                while (button != 1 && button != 2)
                {
                    cout << "输入有误！请重新输入:" << endl;
                    cin >> button;
                }
                if (button == 2)
                {
                    cout << "查找结束，当前暂存库中域名数为：" << AllLeaf.size() << endl;
                }
                else
                {
                    cout << "请输入修改后的域名：" << endl;
                    cin >> change;
                    if (ChangeSite(dat, change, ST))
                    {
                        FindLeaf(ST);
                        cout << "修改成功！当前暂存库中域名数为：" << AllLeaf.size() << endl;
                    }
                    else
                        cout << "修改失败！修改后的域名不合法" << endl;
                }
            }
            else
                cout << "当前暂存库中不存在该域名！" << endl;
            cout << "|----------------------------------------------------------------------------------------------------------------------|" << endl;
            break;
        case 6:
            inf.open("web.dat", ios::in | ios::out | ios::trunc);
            STreeTraverse(ST);
            for (int i = 0; i < AllLeaf.size(); ++i)
            {
                inf << siting[i] << endl;
            }
            cout << "导出成功！共导出" << AllLeaf.size() << "个域名" << endl;
            cout << "|----------------------------------------------------------------------------------------------------------------------|" << endl;
            break;
        default:
            break;
        }
    }
}
