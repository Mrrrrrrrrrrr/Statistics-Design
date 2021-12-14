#include "STree.h"

cout<<"mrrrrrrrrrrr"<<endl;

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
    if (ST->parent = ST)
    {
        STree p = ST;
        ST = ST->nextsibling;
        free(p);
        return OK;
    }
    else if (ST->parent->children = ST)
    {
        ST->parent->children = ST->nextsibling;
        free(ST);
        return OK;
    }
    else
    {
        STree p = ST->parent->children;
        while (p->nextsibling != ST)
            p = p->nextsibling;
        p->nextsibling = ST->nextsibling;
        free(ST);
        return OK;
    }
}