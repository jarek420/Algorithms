//algo2 is1 210a lab04
//JAROSLAW GRZESIAK
//gj49263@zut.edu.pl
#include <iostream>
#include <random>
#include <cmath>

#define RAND_MAX 0x7fff

constexpr auto RED = true;
constexpr auto BLACK = false;

using namespace std;

template <typename T>
class Node {
public:
	Node* parent;
	Node* left;
	Node* right;
	bool color;	
	T key;
	int index=-1;
};

template <typename T>
class RBT {
	Node<T>* root;
	int size;
	int height;
	int next_index = 0;

	Node<T>* guard;

	Node<T>* search(Node<T>* node, T key);					//a	
	void pre_order(Node<T>* node);							//b
	void in_order(Node<T>* node);							//c
	void clear(Node<T>*& node);								//d
	int get_height(Node<T>* node);							//e
	void rotate_left(Node<T>* node);
	void rotate_right(Node<T>* node);
	void show(Node<T>* node);
	Node<T>* get_max(Node<T>* node);
	
public:
	RBT();
	Node<T>* search(T key);
	void add(T key);										//f		
	void clear();
	int get_height();
	void pre_order();
	void in_order();	
	void print();
	void get_max();
	void show();
	void print_static();
};

template<typename T>
RBT<T>::RBT()
{
	guard = new Node<T>;
	guard->color = BLACK;
	guard->parent = guard;
	guard->left = guard;
	guard->right = guard;
	root = guard;
	size = 0;
	height = 0;
}

template<typename T>
Node<T>* RBT<T>::search(Node<T>* node, T key)
{
	if (node != guard)
	{
		if (node->key == key)
		{
			return node;
		}
		else if (node->key < key)
		{
			return search(node->right, key);
		}
		else 
		{
			return search(node->left, key);
		}
	}
	else {
		return nullptr;
	}
}

template<typename T>
Node<T>* RBT<T>::search(T key)
{
	Node<T>* node = new Node<T>;
	node = search(root, key);

	return node;
}

template<typename T>
void RBT<T>::pre_order(Node<T>* node)
{

	if (node != guard)
	{
		cout << node->index << " = " << "color: " << node->color << ", key: " << node->key << ", left: " << node->left->index << ", right: " << node->right->index << endl;

		pre_order(node->left);
		pre_order(node->right);
	}
}

template<typename T>
void RBT<T>::pre_order()
{
	pre_order(root);
}

template<typename T>
void RBT<T>::in_order(Node<T>* node)
{
	if (node != guard)
	{
		in_order(node->left);
		cout << node->key << " ";
		in_order(node->right);
	}
}

template<typename T>
void RBT<T>::in_order()
{
	in_order(root);
}

template<typename T>
void RBT<T>::clear(Node<T>*& node)
{

	if (node != guard)
	{
		clear(node->left);

		clear(node->right);

		delete node;
		node = nullptr;


	}
	else
		return;

}

template<typename T>
void RBT<T>::clear()
{
	size = 0;
	clear(root);

}

template<typename T>
int RBT<T>::get_height(Node<T>* node)
{
	if (node == guard)
		return -1;
	else
	{

		int lDepth = get_height(node->left);
		int rDepth = get_height(node->right);


		if (lDepth > rDepth)
			return(lDepth + 1);
		else return(rDepth + 1);
	}
}

template<typename T>
int RBT<T>::get_height()
{
	return get_height(root);
}

template<typename T>
inline void RBT<T>::rotate_left(Node<T>* node)
{
	Node<T>* node_r = node->right, * p;

	if (node_r != guard)
	{
		p = node->parent;
		node->right = node_r->left;
		if (node->right != guard)
			node->right->parent = node;

		node_r->left = node;
		node_r->parent = p;
		node->parent = node_r;

		if (p != guard)
		{
			if (p->left == node)
				p->left = node_r;
			else
				p->right = node_r;
		}
		else
			root = node_r;
	}
}

//i
template<typename T>
inline void RBT<T>::rotate_right(Node<T>* node)
{
	Node<T>* node_l = node->left, * p;

	if (node_l != guard)
	{
		p = node->parent;

		node->left = node_l->right;
		if (node->left != guard)
			node->left->parent = node;

		node_l->right = node;
		node_l->parent = p;
		node->parent = node_l;

		if (p != guard)
		{
			if (p->left == node)
				p->left = node_l;
			else
				p->right = node_l;
		}
		else
			root = node_l;
	}
}


template <typename T>
void RBT<T>::add(T key)
{
	Node<T>* node = new Node<T>;
	node->index = next_index++;
	node->left = guard;
	node->right = guard;
	node->parent = root;
	node->key = key;

	if (node->parent == guard)
		root = node;
	else
		while (true)
		{
			if (key < node->parent->key)
			{
				if (node->parent->left == guard)
				{
					node->parent->left = node;
					break;
				}
				node->parent = node->parent->left;
			}
			else
			{
				if (node->parent->right == guard)
				{
					node->parent->right = node;
					break;
				}
				node->parent = node->parent->right;
			}

		}
	node->color = RED;

	while ((node != root) && (node->parent->color == RED))
	{
		if (node->parent == node->parent->parent->left)
		{


			if (node->parent->parent->right->color == RED)
			{
				node->parent->color = BLACK;
				node->parent->parent->right->color = BLACK;
				node->parent->parent->color = RED;
				node = node->parent->parent;
				continue;
			}

			if (node == node->parent->right)
			{
				node = node->parent;
				rotate_left(node);
			}

			node->parent->color = BLACK;
			node->parent->parent->color = RED;
			rotate_right(node->parent->parent);
			break;
		}
		else
		{


			if (node->parent->parent->left->color == RED)
			{
				node->parent->color = BLACK;
				node->parent->parent->left->color = BLACK;
				node->parent->parent->color = RED;
				node = node->parent->parent;
				continue;
			}

			if (node == node->parent->left)
			{
				node = node->parent;
				rotate_right(node);
			}

			node->parent->color = BLACK;
			node->parent->parent->color = RED;
			rotate_left(node->parent->parent);
			break;
		}
	}
	root->color = BLACK;
	size++;
}

//g
template<typename T>
inline void RBT<T>::print()
{
	
	cout << "Rozmiar drzewa: " << size << '\n';
	cout << "Wysokosc drzewa: " << get_height(root) << '\n';

	
}

template <typename T>
void RBT<T>::show(Node<T>* node) 
{
	if (node != guard) {
		cout << node->key << ": ";
		if (node->color == BLACK)
		{
			cout << " Czarny ";
		}
		else {
			cout << " Czerwony ";
		}
		if (node->left != guard)
		{
			cout << " l "<<node->right->key;
		}
		else
		{
			cout << " brak ";
		}
		if (node->right != guard)
		{
			cout << " p "<<node->right->key;
		}
		else
		{
			cout << " brak ";
		}

		if (node->parent != guard)
		{
			cout << node->parent->key;
		}
		else
		{
			cout << " N ";
		}
	}
	cout << endl;
}

template <typename T>
void RBT<T>::show()
{
	Node<T>* p = new Node<T>;
	show(p);
}

template <typename T>
void RBT<T>::print_static()		
{
	for (int i = 0;i < size; i++)
		show(search(i));
}
//nie dziala poprawnie wyswietla tylko wartosci jezeli znamy klucze i ilosc elementow
//nie dziala wysiwetlenie najwiekszego elementu w drzewie przez co nie moge ustalic 
//jaka jest najwieksza wartosc w drzewie a to sie wiaze z tym ze nie moge wyprintowac wszystkich elementow
// drzewo na ten moment dziala poprawnie uzupelnic maina dodac pomiary czasow


class Person
{
	char name;
	int nr;
public:
	Person()
	{
		name = '\0';
		nr = 0;
	}
	Person(char name, int nr) : name(name), nr(nr) {}

	friend ostream& operator<< (ostream& wyjscie, const Person& p1);

	bool operator< (Person const& p) const
	{
		return nr < p.nr;
	}
	bool operator== (Person const& p) const
	{
		return nr == p.nr;
	}
};

ostream& operator<< (ostream& os, const Person& p1)
{
	return os << p1.name << ',' << p1.nr;
}
/**
int main() 
{
	const int MAX_ORDER = 7;
	for (int o = 1; o <= MAX_ORDER; o++)
	{
		RBT<Person>* rbt = new RBT<Person>;
		const int n = pow(10, o);

		clock_t t1 = clock();
		for (int i = 0; i < n; i++)
		{
			Person p = Person(rand() % 25000 + 100, rand() % 100);
			rbt->add(p);
		}

		clock_t t2 = clock();

		double time = (t2 - t1) / (double)CLOCKS_PER_SEC;
		rbt->print();
		rbt->print_static();
		cout << "Czas dodawania " << n << " elementow do drzewa: " << time << "kN" << endl;

		cout << "Logarytm: " << log2(n) << endl;
		cout << "Wysokosc/Logarytm: " << rbt->get_height() / log2(n) << endl;


		const int m = pow(10, 4);
		int hits = 0;
		t1 = clock();
		for (int i = 0; i < m; i++)
		{
			Person* p1 = new Person(rand() % 2500 + 100, rand()%100);

			Node<Person>* result = rbt->search(*p1);

			if (result != nullptr)
				hits++;

			delete p1;
		}
		t2 = clock();
		time = ((t2 - t1) / (double)CLOCKS_PER_SEC) / m;
	
		cout << "Czas wyszukiwania: " << m << " elementu drzewa: " << time << " sec." << endl;

		cout << "Liczba trafien: " << hits << endl;


		cout << endl << endl;
		rbt->clear();

		delete rbt;
	}

}
/**/

int main()
{
	RBT<int>* nowy = new RBT<int>;

	nowy->add(1);
	nowy->add(5);
	nowy->add(6);
	nowy->add(7);
	nowy->add(9);
	nowy->add(10);
	nowy->add(4);
	nowy->add(3);
	nowy->add(2);
	nowy->add(0);
	nowy->add(8);
	nowy->pre_order();

	
}

/** napisowa reprezentacja danych
* cout << node->key << ": ";
			if (node->left != nullptr)
			{
				cout << " lewy ";
			}
			else
			{
				cout << " NULL ";
			}
			if (node->right != nullptr)
			{
				cout << " prawy ";
			}
			else
			{
				cout << " NULL ";
			}
			if (node->parent != nullptr)
			{
				cout << node->parent->key;
			}
			else
			{
				cout << " NULL ";
			}
			cout << endl;
 /**/

