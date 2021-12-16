#include <iostream>
#include <string>
#include "STree.h"

int main()
{
	STree ST;
	InitSTree(ST, "ym");
	PushSite("www.baidu.com", ST);
	PushSite("www.wangyiyun.com", ST);
	cout << ST->children->children->nextsibling->data << endl;
}
