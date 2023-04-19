//ALGO2 IS1 210A LAB07
//Jarosław Grzesiak
//gj49263@zut.edu.pl

//heap sorting, counting sort, and bucket sort
#include <iostream>
#include <time.h>
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
	Dynamic_Array(T* a, int n);
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
	/**
	Dynamic_Array &operator=(const Dynamic_Array & tab2) {
		for (int i = 0; i < size; i++) {
			delete tab;
		}
		T tab = new T[size];
		for (int i = 0; i < size; i++) {
			tab[i] = tab2[i];
		}
	}
	/**/
};

template <typename T>
class Heap {
	Dynamic_Array<T>* tab;
	int size;

	void heapUp(int index);		//przekopcowanie w gore							//done
	void heapDown(int index);	//przekopcowanie w dol							//done
public:
	Heap();																		//done
	Heap(T* a, int n, bool fix_top_down);
	T poll();					//pobranie elementu max z kopca i usuniecie go	//done

	void insert(T val);			//dodanie nowego elementu						//done	
	void clear();				//wyczyszczenie kopca							
	void to_string();			//"print"								//done
	void stats() {
		cout << "Aktualny rozmiar kopca: " << size << endl;
	}
	void sort() {
		
			int n = size;
			for (int i = 0; i < n; i++) {
				T maxVal = tab->get(0);
				T pom2 = tab->get(size - 1);

				tab->swap(0, pom2);
				tab->swap(size - 1, maxVal);

				size--;
				heapDown(0);
			}
		
		size = n;
	}
};

//lista dk
template <typename T>
void bubble_sort(T* array, int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = 0; j < size - 1 - i; j++)
		{
			if (array[j] > array[j + 1])
			{
				T temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
		}
	}
	
}

void counting_sort_int(int* a, int n,int max)
{

	int* counts = new int[max];
	
	for (int i = 0; i < n; i++)	
		counts[a[i]]++;

	int k = 0;
	for (int i = 0; i < max; i++)
		for (int j = 0; j < counts[i]; j++)
			a[k++] = i;
	delete [] counts;
}

template <typename T>
void counting_sort(T* a,int n, T max)
{

	T* counts = new T[max];

	for (int i = 0; i < n; i++)
		counts[a[i]]++;

	int k = 0;
	for (int i = 0; i < max; i++)
		for (int j = 0; j < counts[i]; j++)
			a[k++] = i;
	delete[] counts;
}
template <typename T>
void bucket_T(T* a, int n, T m)
{
	double w = m / (double)n;
	int* tab_sizes = new int[n];
	T** tab = new T*[n];
	//List<T>** tab = new List<T>*[n];
	for (int i = 0; i < n; i++)
	{
		//tab[i] = new List[n];
		tab[i] = new T[n];
		tab_sizes[i] = 0;

	}

	for (int i = 0; i < n; i++)
	{
		int index = a[i] / w;
		tab[index][tab_sizes[index]++] = a[i];
		//tab[index].add(a[i]);
	}


	int k = 0;
	for (int i = 0; i < n; i++) {
		if (tab_sizes[i] > 1)
		{
			bubble_sort(tab[i], tab_sizes[i]);
		}
		for (int j = 0; j < tab_sizes[i]; j++)
			a[k++] = tab[i][j];
	}
	delete[] tab_sizes;
	for (int i = 0; i < n; i++)
		delete[] tab[i];
	delete[] tab;


}
/**
void bucket_int(int* a,int n, int m)
{
	//int m = get_max(a,n);
	double w = m / (double) n;
	//int** tab = new int*[n];
	int* tab_sizes = new int[n];
	Dynamic_Array<int>* tab = new Dynamic_Array<int>[n];
	
	for (int i = 0; i < n; i++)
	{
		tab[i]= new int[n];
		tab_sizes[i] = 0;
		
	}

	for (int i = 0; i < n; i++)
	{
		int index = a[i] / w;
		tab[index][tab_sizes[index]++] = a[i];
		
		tab[index].add(a[i] / w);
	}


	int k = 0;
	for (int i = 0; i < n; i++) {
		if (tab_sizes[i] > 1) 
		{
			bubble_sort(tab[i], tab_sizes[i]);
		}
		for (int j = 0; j < tab_sizes[i]; j++)
			a[k++] = tab[i][j];
	}
	delete[] tab_sizes;
	for (int i = 0; i < n; i++)
		delete[] tab[i];
	delete[] tab;

	// return result
}
/**/


//dodac tablice przechowujaca list 
//zrobic uniwersalny counting sort
/**/
int main()
{
	const int MAX_ORDER = 2;
	const int m = (int)pow(10, 7);
	for (int o = 1; o <= MAX_ORDER; o++)
	{
		const int n = (int)pow(10, o);
		int* array1 = new int[n];
		for (int i = 0; i < n; i++)
		{
			int rand_val = rand() % 1000 + 1;
			array1[i] = rand_val;
		}
		int* array2 = new int[n];
		int* array3 = new int[n];
		memcpy(array2, array1, n * sizeof(int)); // pierwsza kopia
		memcpy(array3, array1, n * sizeof(int)); // druga kopia
		// sortowanie przez zliczanie ( do wykonania w miejscu )
		clock_t t1 = clock();
		counting_sort_int(array1, n, m);
		clock_t t2 = clock();
		double time= (t2 - t1) / (double)CLOCKS_PER_SEC;
		std::cout << "Counting sort: " << time << " sec\n";

		t1 = clock();
		Heap <int>* bh = new Heap <int>(array2, n, true);
		bh->to_string();
		cout << "st: " << endl;
		
	
		bh->sort();
		t2 = clock();
		time = (t2 - t1) / (double)CLOCKS_PER_SEC;
		std::cout << "Heap sort: " << time << " sec.\n";
		bh->to_string();

		t1 = clock();
	//bucket_int(array3, n, m);
		t2 = clock();
		time = (t2 - t1) / (double)CLOCKS_PER_SEC;
		std::cout << "Bucket sort: " << time << " sec.\n";

		delete[] array1;
		delete[] array2;
		delete[] array3;
	}
}

class some_object
{
	char name;
	int nr;
public:
	some_object()
	{
		name = '\0';
		nr = 0;
	}
	some_object(char name, int nr) : name(name), nr(nr) {}

	friend ostream& operator<< (ostream& wyjscie, const some_object& p1);
	bool operator> (some_object const& p) const
	{
		return name > p.name;
	}
};

ostream& operator<< (ostream& os, const some_object& p1)
{
	return os << "Imie: " << p1.name << '\t' << "Nr: " << p1.nr << endl;
}
/**
int main_some_objects()
{
	const int MAX_ORDER = 7; // maksymalny rzad wielkosci sortowanych danych
	const double m_Double = (double)pow(2, 30); 
		for (int o = 1; o <= MAX_ORDER; o++)
		{
			const int n = (int)pow(10, o); // rozmiar tablicy z danymi
			double* array1 = new double [n];
			//some_object** array1 = new some_object * [n];
			for (int i = 0; i < n; i++)
			{
			
				some_object* so = new some_object();
				so((rand() << 15), rand());
					so ('a' + rand() % 26);
				array1[i] = so;
				array1[i] = (double)rand();

			}
			 // skrotowy wypis tablicy do posortowania ( np . pewna liczba poczatkowych elementow )
				some_object** array2 = new some_object * [n];
			memcpy(array2, array1, n * sizeof(some_object*)); // kopia
			// sortowanie przez kopcowanie
			clock_t t1 = clock();
			//Heap < some_object* >* bh = new Heap < some_object* >(array1, n,true);
			Heap < double >* bh = new Heap < double >(array1, n, true);
			std::cout << "Counting sort: " << time << " sec\n";
			clock_t t2 = clock();
			// wypis pomiaru czasu i skrotowej postaci wynikowej tablicy
			// sortowanie kubelkowe
				t1 = clock();
				//bucket_T(array2, n, 1.0);
				t2 = clock();
			// wypis pomiaru czasu i skrotowej postaci wynikowej tablicy
				 // sprawdzenie zgodnosci tablic array1 , array2 i wypis informacji o zgodnosci na ekran
				delete[] array1;
			delete[] array2;
		}
}
/**/
/**
int main()
{
	srand(time(NULL));
	int const z = 20;
	int a[z], b[z];
	
	for (int i = 0; i < z; i++)
	{
		b[i] = rand() % 100;
	
	}
	cout << "\n\n\n";
	cout << "before sort: \n";
	for (int i = 0; i < z; i++)
	{
		cout << b[i] << endl;
	}
	int m = get_max(b, z) + 1;
	bucket_int(b, z, m);
	cout << "\n\n\n\n\n\n\n\n\nBucket sort: \n";
	for (int i = 0; i < z; i++)
	{
		cout << b[i] << endl;
	}

	int z = 10000;
	float max = 10000;
	float  b[10000];
	//srand(time(NULL));

	for (int i = 0; i < z; i++)
	{
		b[i] = rand() % z;
	}
	
	time_t time1 = clock();
	bucket_int(b, z-1, max);
	time_t time2 = clock();
	double time = (time2 - time1) / (double)CLOCKS_PER_SEC;
	cout << "Czas: " << time << endl;
	
}
/**/


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
Dynamic_Array<T>::Dynamic_Array(T* a, int n)
{
	capacity = n;
	size = n;
	tab = a;
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
//koniec ///////////////////////////
template <typename T>
Heap<T>::Heap()
{
	size = 0;
	tab = new Dynamic_Array<T>;
}

template <typename T>
Heap<T>::Heap(T* a, int n, bool fix_top_down)
{
	size = n;
	tab = new Dynamic_Array<T>(a, n);
	if (fix_top_down)
	{
		for (int i = 0; i < size; i++)
		{
			heapUp(i);
		}
	}
	else {
		for (int i = size - 1; i >= 0; i--)
		{
			heapDown(i);
		}
	}

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

