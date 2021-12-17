#include "STree.h"

vector<STree> AllLeaf;

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
        PushSite(change, ST);
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
