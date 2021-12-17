#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
#include <fstream>
#define OK 1
#define ERROR 0
using namespace std;
typedef int Status;
typedef struct STNode
{
    STNode* parent = NULL;
    STNode* children = NULL;
    STNode* nextsibling = NULL;
    string data = "";
}STNode, * STree;

extern vector<STree> AllLeaf;
extern string* siting;

Status InitSTree(STree& ST, const string& data); // 创建一棵树并设定其根结点的数据值
Status Insertchild(STree& ST, const string& data); // 为根结点ST添加一个孩子
Status DeleteNode(STree& ST); // 删除此结点
int PushSite(const string& site, STree& ST); // 一个域名地址存入库中
int SearchSite(const string& site, STree& ST); // 从库中查找一个域名地址，如果域名地址存在则返回1，否则返回0
int DeleteSite(const string& site, STree& ST); // 从库中删除一个域名地址，如果域名不存在则返回-1，删除成功返回1
int ChangeSite(const string& site, const string& change, STree& ST); // 修改已知在库中的一个域名地址
void FindLeaf(const STree& ST); // 寻找库中叶子结点
Status STreeTraverse(const STree& ST); // 遍历域名库
Status Valid(const string& site); // 域名合法性检测
void Menu(); // 互联网域名信息管理系统菜单
