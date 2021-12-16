#include <iostream>
#include <string>
#include "STree.h"

int main()
{
	STree ST;
	InitSTree(ST, "ym");
	PushSite("www.baidu.com", ST);
	PushSite("www.wangyiyun.com", ST);
	DeleteSite("www.baidu.com", ST);
	cout << ST->children->children->data << endl;
	ChangeSite("www.wangyiyun.com", "www.kb.com", ST);
	cout << ST->children->children->data << endl;
}
