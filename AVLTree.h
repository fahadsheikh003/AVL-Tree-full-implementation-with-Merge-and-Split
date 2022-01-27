#pragma once
//Fahad Waheed

#include<iostream>
using namespace std;

template <typename K, typename V>
class AVL
{
	struct Node
	{
		K key;
		V value;
		int height;
		Node* left;
		Node* right;

		//default constructor
		Node() :key(K()), value(V()), height(-1), left(NULL), right(NULL) {};

		//parameterized constructors
		Node(K key, V value) :key(key), value(value), height(0), left(NULL), right(NULL) {};

		Node(K key, V value, int height, Node* left, Node* right)
			: key(key), value(value), height(height), left(left), right(right) {};
	};

	Node* root;

	//function to return height of node (subtree) used to handle exceptions
	int getheight(Node* node)
	{
		if (node == NULL)
			return -1;
		return node->height;
	}

	//function to return maximum from two integer values
	int max(int i1, int i2)
	{
		return (i1 > i2 ? i1 : i2);
	}

	//function to get balance factor of a node
	int getbalancefactor(Node* node)
	{
		if (node == NULL)
			return 0;
		return getheight(node->left) - getheight(node->right);
	}

	//function to right rotate a node
	Node* singlerotationwithright(Node* previousroot)
	{
		Node* newroot = previousroot->left;//new root
		Node* temp = newroot->right;//preserving the right subtree of previous root's left child

		//new root's left child will remain same

		newroot->right = previousroot;//previous root will be new root's right child 
		previousroot->left = temp;//setting previous root's left which previously points to new root

		//calculating height of both previous root and new root, as height of remaining nodes remains the same
		previousroot->height = max(getheight(previousroot->left),
			getheight(previousroot->right)) + 1;

		newroot->height = max(getheight(newroot->left),
			getheight(newroot->right)) + 1;

		return newroot;
	}

	//function to left rotate a node
	Node* singlerotationwithleft(Node* previousroot)
	{
		Node* newroot = previousroot->right;//new root
		Node* temp = newroot->left;//preserving the left subtree of previous root's right child

		//new root's right child will remain same

		newroot->left = previousroot;//previous root will be new root's left child 
		previousroot->right = temp;//setting previous root's right which previously points to new root

		//calculating height of both previous root and new root, as height of remaining nodes remains the same
		previousroot->height = max(getheight(previousroot->left),
			getheight(previousroot->right)) + 1;

		newroot->height = max(getheight(newroot->left),
			getheight(newroot->right)) + 1;

		return newroot;
	}

	//function that first right rotates right child of a node and then left rotates the node
	Node* doublerotationrightleft(Node* previousroot)
	{

		previousroot->right = singlerotationwithright(previousroot->right);
		Node* newroot = singlerotationwithleft(previousroot);

		return newroot;
	}

	//function that first left rotates left child of a node and then right rotates the node
	Node* doublerotationleftright(Node* previousroot)
	{
		previousroot->left = singlerotationwithleft(previousroot->left);
		Node* newroot = singlerotationwithright(previousroot);

		return newroot;
	}

	//function to insert data in AVL
	Node* AVLinsertion(Node* currnode, K key, V value)
	{
		if (currnode == NULL)//if there is no node with key
		{
			currnode = new Node(key, value);
			return currnode;
		}
		else if (key < currnode->key)//recursive call and Rotation
		{
			currnode->left = AVLinsertion(currnode->left, key, value);
			if (getbalancefactor(currnode) == 2)
			{
				if (key < currnode->left->key)
					currnode = singlerotationwithright(currnode); //RR rotation
				else
					currnode = doublerotationleftright(currnode); //LR rotation 
			}
		}
		else if (key > currnode->key)//recursive call and Rotation
		{
			currnode->right = AVLinsertion(currnode->right, key, value);
			if (getbalancefactor(currnode) == -2)
			{
				if (key > currnode->right->key)
					currnode = singlerotationwithleft(currnode); //LL rotation
				else
					currnode = doublerotationrightleft(currnode); //RL rotation
			}
		}
		
		//updating height of nodes
		currnode->height = max(getheight(currnode->left),
			getheight(currnode->right)) + 1;

		return currnode;
	}

	//function to remove a node of AVL
	Node* AVLdeletion(Node* currnode, K key, V value = V())
	{
		if (currnode == NULL)//if node not found
			return NULL;

		else if (key < currnode->key)//recursive call
		{
			currnode->left = AVLdeletion(currnode->left, key, value);
		}
		else if (key > currnode->key)//recursive call
		{
			currnode->right = AVLdeletion(currnode->right, key, value);
		}
		else if (key == currnode->key)//if node found
		{
			if (currnode->left == NULL && currnode->right == NULL)//if node is a leaf node
			{
				delete currnode;
				currnode = NULL;
			}
			else if (currnode->left == NULL)//if node has only right child
			{
				Node* temp = currnode;
				currnode = currnode->right;

				delete temp;
			}
			else if (currnode->right == NULL)//if node has only left child
			{
				Node* temp = currnode;
				currnode = currnode->left;

				delete temp;
			}
			else//if node has both left and right children
			{
				//traversing to get the minimum node from currnode
				Node* temp = currnode->right;
				while (temp->left)
				{
					temp = temp->left;
				}

				//copying the content of minimum node to currnode
				currnode->key = temp->key;
				currnode->value = temp->value;

				//deleting the minimum node
				currnode->right = AVLdeletion(currnode->right, temp->key, temp->value);
			}
		}

		//if node was leaf node
		if (currnode == NULL)
			return NULL;

		//calculating height after deletion
		currnode->height = max(getheight(currnode->left),
			getheight(currnode->right)) + 1;

		//left subtree is heavy
		if (getbalancefactor(currnode) == 2)
		{
			//checking if left child of left subtree exists or not
			if (getbalancefactor(currnode->left) >= 0)
			{
				currnode = singlerotationwithright(currnode);
			}
			else if (getbalancefactor(currnode->left) < 0)
			{
				currnode = doublerotationleftright(currnode);
			}
		}

		//right subtree is heavy
		else if (getbalancefactor(currnode) == -2)
		{
			//checking if right child of right subtree exists or not
			if (getbalancefactor(currnode->right) <= 0)
			{
				currnode = singlerotationwithleft(currnode);
			}
			else if (getbalancefactor(currnode->right) > 0)
			{
				currnode = doublerotationrightleft(currnode);
			}
		}

		return currnode;
	}

	//function to search a node in AVL
	Node* Search(Node* currnode, K key)
	{
		//Base cases
		if (currnode == NULL)
			return;
		else if (currnode->key == key)
		{
			return currnode;
		}

		//Recursive calls
		else if (key < currnode->key)
			return Search(currnode->left, key);
		else if (key > currnode->key)
			return Search(currnode->right, key);
	}

	//function to insert nodes of a Tree into another Tree which is initially not empty
	void FullTreeInsertion(Node* currnode, AVL<K,V>& Tree)
	{
		if (currnode != NULL)
		{
			Tree.root = Tree.AVLinsertion(Tree.root, currnode->key, currnode->value);
			FullTreeInsertion(currnode->left, Tree);
			FullTreeInsertion(currnode->right, Tree);
		}
	}

	//function to split AVL Tree
	void Split(K key, Node* currnode, AVL<K,V>& Tree1, AVL<K,V>& Tree2)
	{
		if (currnode == NULL)//if node was NULL or becomes NULL while traversing
		{
			return;
		}
		if (currnode->key <= key)//inserting nodes into Tree 1 if they are less than or equal to key
		{
			Tree1.root = Tree1.AVLinsertion(Tree1.root, currnode->key, currnode->value);
		}
		if (currnode->key > key)//inserting nodes into Tree 2 if they are greater than key
		{
			Tree2.root = Tree2.AVLinsertion(Tree2.root, currnode->key, currnode->value);
		}
		//recursive calls
		Split(key, currnode->left, Tree1, Tree2);
		Split(key, currnode->right, Tree1, Tree2);
	}

	//function used to copy nodes from one Tree to another according to their position
	Node* AVLcopynodes(Node* currnode)
	{
		if (currnode == NULL)
			return NULL;
		else
		{
			Node* left = AVLcopynodes(currnode->left);
			Node* right = AVLcopynodes(currnode->right);
			return new Node(currnode->key, currnode->value, currnode->height, left, right);
		}
	}

	//function to delete a Tree
	void clear(Node* node)
	{
		if (node)
		{
			clear(node->left);
			clear(node->right);
			free(node);
		}
	}

	void inorder(Node* node)
	{
		if (node)
		{
			inorder(node->left);
			cout << node->key << "  " << node->value << endl;
			inorder(node->right);
		}
	}

public:
	AVL() : root(NULL) {};

	//copy constructor
	AVL(const AVL<K,V>& obj) :root(NULL)
	{
		this->root = AVLcopynodes(obj.root);
	}

	//copy assignment operator
	AVL<K,V>& operator=(const AVL<K,V>& obj)
	{
		this->clear();

		this->root = AVLcopynodes(obj.root);

		return *this;
	}

	void Insert(K key, V value)
	{
		root = AVLinsertion(root, key, value);
	}

	void Remove(K key, V value = V())
	{
		root = AVLdeletion(root, key, value);
	}

	void Display()
	{
		inorder(root);
	}

	//function to merge two AVL Tree into one
	AVL<K, V> Merge(AVL<K, V> Tree2)
	{
		AVL<K, V> MainTree;

		MainTree = *this;

		MainTree.FullTreeInsertion(Tree2.root, MainTree);

		return MainTree;
	}

	//+ operator overloaded to merge two AVL Tree into one
	AVL<K, V> operator+(AVL<K, V> Tree2)
	{
		AVL<K, V> MainTree;

		MainTree = *this;

		MainTree.FullTreeInsertion(Tree2.root, MainTree);

		return MainTree;
	}

	//function to split an AVL Tree into two
	pair<AVL<K, V>, AVL<K, V>> Split(K key)
	{
		AVL<K, V> Tree1, Tree2;

		pair<AVL<K, V>, AVL<K, V>> P;
		P.first = Tree1;
		P.second = Tree2;

		Split(key, root, P.first, P.second);

		return P;
	}

	//function to delete all nodes of AVL Tree
	void clear()
	{
		clear(root);
		root = NULL;
	}

	~AVL()
	{
		clear();
	}
};