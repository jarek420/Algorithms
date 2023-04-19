//algo2 is1 210A lab03
//Jarosław Grzesiak
//gj49263@zut.edu.pl

//implementation of binary search tree algorithm with time measurement in main
#include <iostream>
#include <time.h>
#define COUNT 10

using namespace std;

template <typename T>
class Node
{
public:
	Node<T>* left;
	Node<T>* right;
	Node<T>* parent;
	T key; 
	int indeks=0;
	Node()
	{
		T key = 0;
		left = nullptr;
		right = nullptr;
		parent=nullptr;
	}

};

template <typename T>
class BST
{
	int size = 0;
	int height = 0;
	Node<T>* root;
	Node<T>* add(Node<T>* node,T key);
	Node<T>* search(Node<T>* node, T key);
	Node <T>* remove(Node<T>* node, T key);
	T succesor(Node<T>* node);
	T succesor(T key);
	int height_(Node<T>* node);
	void clear(Node<T>* &node);
	void print(Node<T>* node, int space);
public:
	BST() {
		root = nullptr;
	}

	void add(T key);
	void check();	
	Node<T>* search(T key);
	void remove(T key);
	T min(Node<T>*node);
	T max(Node<T>* node);
	void clear();
	void print();
	void min();
	void max();
	int height_();
};
//a
template <typename T>
Node<T> * BST<T>::add(Node<T>*node, T key)
{
	if (node == nullptr)
	{
		node = new Node<T>;
		node->key = key;
		node->right = nullptr;
		node->left = nullptr;
		node->parent = nullptr;


	 }
	else if (node->key < key)
	{
		node->right = add(node->right, key);
		node->right->parent = node;

	}
	else
	{
		node->left = add(node->left, key);
		node->left->parent = node;
	}
	return node;
	
}

template <typename T>
void BST<T>::add(T key)
{
	root = add( root, key);
	size++;
}
//b
template <typename T>
Node<T>* BST<T>::search(Node<T>* node, T key)
{

	if (node == nullptr)
		return nullptr;
	else if (node->key == key)
		return node;
	else if (node->key < key)
		return search(node->right, key);
	else
		return search(node->left, key);
	
}

template <typename T>
Node<T>* BST<T>::search(T key)
{
	Node<T>* node = new Node<T>;
		node = search(root, key);
		return node;
}

//c

template <typename T>
Node<T>* BST<T>::remove(Node<T>* node, T key)
{
	if (node == nullptr)
		return nullptr;
	if (node->key == key)
	{
		//wezel jest lisciem
		if (node->left == nullptr && node->right == nullptr)
			node = nullptr;
		//jesli wezel jest półliściem z dzieckiem po prawej
		else if (node->left == nullptr && node->right != nullptr)
		{
			node->right->parent = node->parent;

			node = node->left;
		}
		//jesli wezel jest półlisciem z dzieckiem po lewej
		else if (node->left != nullptr && node->right == nullptr)
		{
			node->left->parent = node->parent;

			node = node->left;
		}
		//wezel jest rodzicem
		else
		{
			T nastepnik = succesor(key);

			node->key = nastepnik;

			node->right = remove(node->right, nastepnik);
		}
	}

	else if (node->key < key)
		node->right = remove(node->right, key);
	else
		node->left = remove(node->left, key);
	return node;
}

template<typename T>
void BST<T>::remove(T key)
{
	root = remove(root, key);
	size--;
}

//metoda ktora szuka nastepcy
template <typename T>
T BST<T>::succesor(Node<T>* node)
{
	if(node->right !=nullptr)
	{
		return min(node->right);
	}
}

template <typename T>
T BST<T>::succesor(T key)
{
	Node<T>* node = search(root, key);

	if(node==nullptr)
	{
		return -1;
	}
	else
		return succesor(node);
}
template <typename T>
T BST<T>::min(Node<T>* node)
{
	while (node->left != nullptr)
	{
		node = node->left;
	}
	return node->key;
}

template <typename T>
void BST<T>::min()
{
	cout << min(root);
}
template <typename T>
void BST<T>::max()
{
	cout << max(root);
}

template <typename T>
T BST<T>::max(Node<T>* node)
{
	while (node->right != nullptr)
	{
		node = node->right;
	}
	return node->key;
}
template<typename T>
void BST<T>::print(Node<T>* node, int space)
{

	if (node == nullptr)
		return;

	space += COUNT;

	print(node->right, space);

	cout << '\n';
	for (int i = COUNT; i < space; i++)
		std::cout << " ";
	cout << node->key << "\n";

	print(node->left, space);
}

template <typename T>
void BST<T>::print()
{
	cout << "ilosc elementow: " << size << endl;
	cout << "wysokosc: " << height_(root) << endl;
	print(root, 0);
}


template <typename T>
int BST<T>::height_(Node<T>* node)
{
	if (node == nullptr)
	{
		return 0;
	}
	else
	{
		int left = height_(node->left);
		int right = height_(node->right);

		return left > right ? left + 1 : right + 1;

	}
}

template <typename T>
int BST<T>::height_()
{
	return height_(root);
}

//f
template<typename T>
void BST<T>::clear(Node<T>*& node)
{
	if (node == nullptr)
		return;
	if (node->left != nullptr)
		clear(node->left);
	if (node->right != nullptr)
		clear(node->right);


	delete node;
	node = nullptr;
}

template<typename T>
void BST<T>::clear()
{
	size = 0;
	clear(root);
}


int main()
{
	const int MAX_ORDER = 2;
	BST<int>* lp = new BST<int>();

	for (int i = 0; i < MAX_ORDER; i++)
	{
		const int n = pow(10, i);

		srand(time(NULL));

		clock_t t1 = clock();
		for (int j = 0; j < n; j++)
		{
			lp->add(((rand()<<15)+rand())%10000);
		}

		clock_t t2 = clock();
		lp->print();
		cout << "Log: " << log2(n) << endl;
		cout << "wysokosc: " << lp->height_() << endl;
		cout << "wysokosc / log: " << lp->height_() / log2(n) << endl;

		double time = (t2 - t1) / (double)CLOCKS_PER_SEC;

		cout << "Czas dodawania: " << n << " elemetow do drzewa: " << time << '\n';
		//cout << "wysokosc/log" << log2(n) / lp->height_()<<endl;

	}
}
