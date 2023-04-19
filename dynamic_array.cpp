//ALGO2 IS1 210A lab02
//Jarosław Grzesiak
//gj49263@zut.edu.pl
//dynamic array that ezxpand it's size by 2 or any other natural number, when it's getting full
#include <iostream>
#include <time.h>

using namespace std;

template <typename T>
class Dynamic_Array
{
	const int expand=2;
	int size;
	int capacity;
	T* tab;
public:
	Dynamic_Array();
	void add(T value);
	T get(int indeks);
	void swap(int index,T val);
	void clear();
	void show();
	void bb_sort();
};

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
		T *tab_new = new T[capacity];
		for (int i = 0; i < size; i++)
		{
			tab_new[i] = tab[i];
		}
		delete tab;
		tab = tab_new;
	}
	tab[size] = value;
	size++;
}

template <typename T>
T Dynamic_Array<T>::get(int indeks)
{
	if (indeks > size)
	{
		return 0;
	}
	else
	{
		return tab[indeks];
	}
}

template <typename T>
void Dynamic_Array<T>::swap(int index,T val)
{
	if (index > size)
	{
		
		cout << "za duzy indeks, opuszczam program\n";
		exit(0);
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
	tab = new T[capacity];
	//Dynamic_Array();
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
void change(T& a, T& b)
{
	T c = a;
	a = b;
	b = c;
}

template <typename T>
void Dynamic_Array<T>::bb_sort()
{
	for (int j = 0; j < size ;j++)
	{
		for (int i = 0; i < size-1; i++)
		{
			if (tab[i + 1] < tab[i])
				change(tab[i], tab[i + 1]);
		}
	}
}

int main()
{
	Dynamic_Array<int>* tmp = new Dynamic_Array<int>;
	const int nr = 5;

	double x = 0.0;
	
	int counter = 0;

	for (int i = nr; i <= nr ; i++)
	{
		counter++;
		const int n = pow(10, i);

		srand(time(NULL));
		double max_time_per_element = 0.0;
		clock_t t1_s = clock();
		for (int j = 0; j < n; j++)
		{
			clock_t t1_e = clock();
			tmp->add(rand() % 1024 );
			clock_t t2_e = clock();
			double time_per_element = t2_e - t1_e;
			if (time_per_element > max_time_per_element)
			{
				max_time_per_element = time_per_element;
				cout << "\nNowy najgorszy czas dla indeksu " << j << " : " << max_time_per_element / (double)CLOCKS_PER_SEC <<" sec" << endl;
			}
		}
		clock_t t2_s = clock();
		cout << "Laczny czas operacji: " << (t2_s - t1_s)/(double)CLOCKS_PER_SEC<<" sec." << endl;
		cout << "Sredni czas operacji: " << ((t2_s - t1_s) / (double)n)/(double)CLOCKS_PER_SEC << " sec." << endl;
		//tmp->swap(n * 2, 345);
	}
}
