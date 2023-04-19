//ALGO 2 IS1 210A LAB06
//jarosław Grzesiak
//gj49263@zut.edu.pl

#include <complex>
#include <iostream>
#include "math.h"
#define _USE_MATH_DEFINES

using namespace std;
double M_PI = 3.14;

complex<double>* FFT(double* tab, int N)
{
    complex<double>* C = new complex<double>[N];
    if (N == 1) {
        C[0] = tab[0];
        return C;
    }

    double* E = new double[N / 2];
    double* O = new double[N / 2];

    for (int i = 0; i < N / 2; i++)
    {
        E[i] = tab[i * 2];
        O[i] = tab[i * 2 + 1];
    }

    complex<double>* Ce = FFT(E, N / 2);
    complex<double>* Co = FFT(O, N / 2);

    for (int k = 0; k < N / 2; k++)
    {
        double t = ( - 2)* M_PI* k / N;
        complex<double> e = complex<double>(cos(t), -sin(t));

        C[k] = Ce[k] + e*Co[k];
        C[k+N/2] = Ce[k] - e*Co[k];

    }
    delete Ce;
    delete Co;

    for (int i = 0; i < N; i++)
        cout << C[i] << endl;

    return C;
}

template <typename T>
complex<double>* DFT(T* tab, int N)
{
    complex<double>* C = new complex<double>[N];
    for (int k = 0; k < N; k++)
    {
        C[k] = complex<double>(0, 0);
        for (int i = 0; i < N; i++)
        {
            double t = 2 * M_PI * i* k / N;
            C[k] += tab[i] * complex<double>(cos(t), -sin(t));
        }
    }

    for (int i = 0; i < N; i++)
        cout << C[i] << endl;
    return C;
}

//zrobic pomiary czasu na lab

int main()
{
    const int MAX_ORDER = 13; // maksymalny rzad wielkosci danych ( w ramach bazy 2)
    const bool PRINT_COEFS = false; // przelacznik do ewentualnego wypisu na ekran rezultatow DFT , FFT
    for (int o = 1; o <= MAX_ORDER; o++)
    {
        const int N = 1 < o; // rozmiar problemu ( potega dwojki - przesuniecie bitowe w lewo )
        printf("N: % i \n", N);
        double* f = new double[N];
        for (int n = 0; n < N; n++)
            f[n] = n / (double)N; // przykladowe dane ( tu akurat : probki funkcji liniowej )
        clock_t t1 = clock();
        complex < double >* cDFT = DFT(f, N);
        clock_t t2 = clock();
        double dft_time = (t2 - t1) / (double)CLOCKS_PER_SEC * 1000.0;
        printf("DFT time[ms] : % f \n", dft_time);
        t1 = clock();
        complex < double >* cFFT = FFT(f, N);
        t2 = clock();
        double fft_time = (t2 - t1) / (double)CLOCKS_PER_SEC * 1000.0;
        printf("FFT time[ms] : % f \n", fft_time);
        // printf("mean e r r o r : % f \n", err(cDFT, cFFT, N));
        if (PRINT_COEFS)
            for (int k = 0; k < N; k++)
                // wypis na ekran wspolczynnikow obu transformat ( czesci rzeczywiste i urojone )
                printf("−−−−−\n", N);
        delete[] f;
        delete[] cDFT;
        delete[] cFFT;
    }
}
/*
int main()
{
	const int N = 5;
	double signal[N];
    for (int i = 0; i < N; i++)
        signal[i] = (rand() % 100);

    cout << "Before" << endl;
    for (int i = 0; i < N; i++)
        cout << signal[i] << endl;

    cout << "DFT" << endl;
    DFT(signal, N);

    cout << "FFT" << endl;
    FFT(signal, N);
}
*/
