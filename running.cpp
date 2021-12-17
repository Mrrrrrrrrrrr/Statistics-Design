#include <iostream>
#include <string>
#include "STree.h"

int main()
{
	STree ST;
	InitSTree(ST, "ym");
	PushSite("www.baidu.com", ST);
	PushSite("www.baidu", ST);
	PushSite("www.wyy.com", ST);
	FindLeaf(ST);
	cout << AllLeaf.size() << endl;
}
