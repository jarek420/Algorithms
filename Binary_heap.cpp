//AlGO2 IS1 210A LAB06
//Jarosław Grzesiak
//gj49263@zut.edu.pl
#include <iostream>
#include <time.h>

// include "dynamic array.h"
using namespace std;
template <typename T>
class Dynamic_Array
{
	const int expand = 2;
	int size;
	int capacity;
	T* tab;
public:
	Dynamic_Array();
	void add(T value);
	T get(int indeks);
	void swap(int index, T val);
	void clear();
	void show();
	void bb_sort();
	int get_size();
	int get_cap();
	void show_element(int index) {
		cout << tab[index];
	}
};
template <typename T>
int Dynamic_Array<T>::get_size() {
	return size;
}
template <typename T>
int Dynamic_Array<T>::get_cap() {
	return capacity;
}

template <typename T>
Dynamic_Array<T>::Dynamic_Array()
{
	capacity = 1;
	size = 0;
	tab = new T[capacity];
}

template <typename T>
void Dynamic_Array<T>::add(T value)
{
	if (size == capacity)
	{
		capacity *= expand;
		T* tab_new = new T[capacity];
		for (int i = 0; i < size; i++)
		{
			tab_new[i] = tab[i];
		}
		tab = new T[capacity];
		for (int i = 0; i < size; i++)
		{
			tab[i] = tab_new[i];
		}
		delete[] tab_new;
	}
	tab[size] = value;
	size++;
}

template <typename T>
T Dynamic_Array<T>::get(int indeks)
{
	if (indeks > size || indeks < 0)
	{
		return 0;
	}
	else
	{
		return tab[indeks];
	}
}

template <typename T>
void Dynamic_Array<T>::swap(int index, T val)
{
	if (index > size || index < 0)
	{
		return;
	}
	else
	{
		tab[index] = val;
	}
}

template <typename T>
void Dynamic_Array<T>::clear()
{
	delete[] tab;
	size = 0;
	capacity = 1;
	Dynamic_Array();
}

template <typename T>
void Dynamic_Array<T>::show()
{
	cout << "Size: " << size << "Pojemnosc: " << capacity << endl;
	if (size < 100)
	{
		for (int i = 0; i < size; i++)
			cout << tab[i] << endl;
	}
	else
		cout << "Jest ponad 100 elementow!";
}

template <typename T>
void Dynamic_Array<T>::bb_sort()
{
	for (int j = 0; j < size; j++)
	{
		for (int i = 0; i < size - 1; i++)
		{
			if (tab[i + 1] < tab[i])
				change(tab[i], tab[i + 1]);
		}
	}
}
//koniec ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
class Heap {
	Dynamic_Array<T>* tab;
	int size;

	void heapUp(int index);		//przekopcowanie w gore							//done
	void heapDown(int index);	//przekopcowanie w dol							//done
public:
	Heap();																		//done
	T poll();					//pobranie elementu max z kopca i usuniecie go	//done
	void insert(T val);			//dodanie nowego elementu						//done	
	void clear();				//wyczyszczenie kopca							
	void to_string();			//"print"								//done
	void stats() {
		cout << "Aktualny rozmiar kopca: " << size << endl;
	}
	


};

template <typename T>
Heap<T>::Heap()
{
	size = 0;
	tab = new Dynamic_Array<T>;
}

template <typename T>
void Heap<T>::insert(T val)
{
	tab->add(val);
	heapUp(size);
	size++;
}

template <typename T>
void Heap<T>::heapUp(int index)
{
	if (index == 0)
		return;
	int parent = (index - 1) / 2;
	if (tab->get(index) >= tab->get(parent))
	{
		T pom1 = tab->get(index);
		tab->swap(index, tab->get(parent));
		tab->swap((parent), pom1);

		heapUp(parent);
	}

}
//index rodzica indeksu 'index' (index-1)/2
//lewy i prawy syn (2*index+1,2*index+2)
//kopcowanie w dol
//jezeli index > index +1

template <typename T>
void Heap<T>::heapDown(int index)
{
	/**/
	int index_pom = index;
	if (index >= size)
		return;
	int l = 2 * index + 1;
		int r = l + 1;
		if (l < size && tab->get(l) > tab->get(index))
			index_pom = l;
		if (r < size && tab->get(r) > tab->get(index_pom))
			index_pom = r;
		if (index_pom != index)
		{
			T pom1 = tab->get(index);
			T pom2 = tab->get(index_pom);

			tab->swap(index, pom2);
			tab->swap(index_pom, pom1);
			heapDown(index_pom);
		}
}

template <typename T>
void Heap<T>::to_string()
{
	for (int i = 0; i < size; i++)
	{
		tab->show_element(i);
		cout << endl;
	}
}
template <typename T>
T Heap<T>::poll()
{
	//pobranie najwiekszego elementu
	T maxVal = tab->get(0);

	//usuniecie
	//T pom1 = tab->get(0);
	T pom2 = tab->get(size - 1);

	tab->swap(0, pom2);
	//tab->swap(size - 1, pom1);
	size--;
	heapDown(0);
	return maxVal;

}
template <typename T>
void Heap<T>::clear()
{
	tab->clear();
	delete tab;
	size = 0;
	tab = new Dynamic_Array<T>;
}

/**/
int main()
{
	const int MAX_ORDER = 10;
	Heap<int>* heap = new Heap<int>;
	for (int o = 1; o <= MAX_ORDER; o++)
	{
		const int n = pow(10, o);

		clock_t t1 = clock();
		for (int i = 0; i < n; i++)
		{
			int p = rand() % 99999;
			heap->insert(p);
		}
		clock_t t2 = clock();
		double time = (t2 - t1) / (double)CLOCKS_PER_SEC;
		cout << "Czas dodania " << n << " elementow: " << time << " sec."<<endl;
		heap->stats();
		clock_t tpoll1 = clock();
		for (int i = 0; i < n; i++)
		{
			heap->poll();
		}
		clock_t tpoll2 = clock();
		double time2 = (tpoll2 - tpoll1) / (double)CLOCKS_PER_SEC;
		cout << "Czas zabrania najwiekszego elementu: " << time2 << " sec." << endl;

		heap->clear();

	}

}
/**/

/**
int main()
{

	Heap<int>* heap = new Heap<int>;
	srand(1);
	int a;
	int n = 4;
	for (int i = 0; i < n; i++)
	{
		a = rand() % 20;
		cout << "Adding: " << a << endl;
		heap->insert(a);
		heap->to_string();
		//cout << endl;
	}


	cout << "FINAL HEAP:" << endl;
	heap->to_string();
	for (int i = 0; i < n; i++)
	{
		
		int b=heap->poll();
		cout << "polled: " << b << endl;
		heap->to_string();
	}
}
/**/
/**
* a=2
* b=6
* c=a
* a=b
* b=c
/**/
