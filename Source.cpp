#include"AVLTree.h"

int main()
{
	AVL<int, string> avl;

	for (int i = 0; i < 7; i++)
		avl.Insert(i + 1, "A");

	avl.Remove(5);

	cout << "AVL #1\n";
	avl.Display();

	AVL<int, string> avl1;

	for (int i = 0; i < 7; i++)
		avl1.Insert(i + 8, "A");

	cout << "\n\nAVL #2\n";
	avl1.Display();

	AVL<int, string> avl2 = avl + avl1;

	cout << "\n\n(Merged AVL (AVL 1 + AVL 2)); AVL #3\n";
	avl2.Display();

	cout << "\n\nSpliting AVL #3 with key = 7";
	pair<AVL<int, string>, AVL<int, string>> P = avl2.Split(7);

	cout << "\n\nAfter Spliting..\n";

	cout << "\n\nAVL #1\n";
	P.first.Display();

	cout << "\n\nAVL #2\n";
	P.second.Display();
}