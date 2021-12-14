#pragma once
#include <iostream>
#include <string>
#define OK 1
#define ERROR 0
#define overflow -1
using namespace std;
typedef int Status;
typedef struct STNode
{
    STNode* parent;
    STNode* children;
    STNode* nextsibling;
    string data;
}STNode, * STree;

Status InitSTree(STree& ST, const string& data); // 创建一棵树并设定其根结点的数据值
Status Insertchild(STree& ST, const string& data); // 为根结点ST添加一个孩子
Status DeleteNode(STree& ST); // 删除此结点