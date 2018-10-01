#include "avl.hpp"
using namespace std;

int main(void){

	avl<int> t;
	t.insert(20);
	t.insert(12);
	t.insert(5);

	t.show(order::preorder);

	avl<string> t2("Hello world");
	t2.insert("avl");
	t2.insert("com");

	t2.show(order::posorder);

	t2.remove("avl");
	t2.remove("com");

	t2.show(order::inorder);

	return 0;
}
