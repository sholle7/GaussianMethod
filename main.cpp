#include<iostream>
#include <cmath>
#include <algorithm>//std::swap
#include <iomanip>
using namespace std;

//pomocna funckija za zaokruzivanje brojeva
float zaokruzi(float br,int dec)
{
	float vr = (int)(br * pow(10,dec) + .5);
	return (float)vr /(pow(10, dec));
}
//brisanje matrice A
void brisiA(double** A,int n) {
	for (int i = 0; i < n; i++)delete A[i];
	delete[] A;
}
//brisanje niza B i niza X
void brisiBX(double* B, int n) {
	delete[] B;
}
//brisanje matrice B
void brisiAB(double** AB, int n) {
	for (int i = 0; i < n; i++)delete AB[i];
	delete[] AB;
}
//formiranje matrice A
void napraviA(double** A,int n) {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) A[i][j] =(double)pow(i + j, 2);
}
//formiranje matrice B
void napraviB(double** A, double* B, int n) {
	for (int i = 0; i < n; i++) {
		B[i] = 0;
		for(int j = 0; j < n; j++)B[i] += A[i][j];
	}
}
//formiranje matrice AB
void napraviAB(double** AB,double** A,double* B,int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n+1; j++) {
			if (j != n)AB[i][j] = A[i][j];
			else AB[i][j] = B[i];
		}
	}
}
//ispisivanje matrice A
void ispisiA(double** A, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << A[i][j] << " ";
		}
			cout << endl;
	}
}
//ispisivanje matrice B
void ispisiB(double* B, int n) {
	for (int i = 0; i < n; i++) {
		cout << B[i] << " ";
		cout << endl;
	}
}
//ispisivanje matrice AB
void ispisiAB(double** AB, int n) {
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n + 1; j++) {
			cout<< AB[i][j] << " ";
		}
		cout << endl;
	}
}
//Gausova metoda sa parcijalnim pivotiranjem 
void obrada(double** AB, int n) {
	for (int j = 0; j < n - 1; j++) {
		int maxind = j;//maxind indeks elementa sa najvecom apsolutnom vrednoscu po koloni
		for (int i = j; i < n; i++) if (abs(AB[i][j]) > abs(AB[maxind][j]))maxind = i;//trazenje pivota po koloni
		//zamena vrste ako je maksimalni element nije na tekucoj poziciji vrste
		if (maxind != j) {
			for (int k = j; k < n + 1; k++)swap(AB[maxind][k], AB[j][k]);
		}
		double* m = new double[n - 1 - j];
		int d = 0;
		for (int p = j + 1; p < n; p++) { //p je za vrste, j za kolone
			m[d] = zaokruzi(AB[p][j] / AB[j][j], 5);
			d++;
		}
		for (int p = j + 1, d = 0; p < n; p++) {
			for (int l = j; l < n + 1; l++) {
				AB[p][l] -= m[d] * AB[j][l];
				AB[p][l] = zaokruzi(AB[p][l], 5);//zaokruzivanje 	
			}
			d++;
		}
		delete[]m;
	}
}
//odredjivanje x-ova postupkom unazad
void postupakUnazad(double** AB ,int n,double* X) {
	X = new double[n];
	int m = 0;
	while (m != n)X[m++] = 0;
	for (int i = n - 1; i >= 0; i--) {//za svaku vrstu radimo sledece
		int j;
		for (j = n - 1; j != i; j--) X[i] -= (AB[i][j] * X[j]);	
		
			X[i] += AB[i][n];
			X[i] /= AB[i][i];
			X[i] = zaokruzi(X[i], 5);
	}
	ispisiB(X, n);	
}
int main() {
	int n = 2;
	while (n != 5) {
		double* X = nullptr;

		double** A = new double* [n];
		double* B = new double[n];
		double** AB = new double* [n];
		for (int i = 0; i < n; i++)A[i] = new double[n];
		for (int i = 0; i < n; i++)AB[i] = new double[n + 1];

		napraviA(A, n);
		napraviB(A, B, n);
		napraviAB(AB, A, B, n);
		cout << "Matrica koeficijenata A reda "<< n<<" : " << endl;
		ispisiA(A, n);
		cout << "Kolona matrica B: " << endl;
		ispisiB(B, n);
		cout << "Prosirena matrica AB: " << endl;
		ispisiAB(AB, n);

		cout << endl << endl;
		obrada(AB, n);
		cout << "Ispis napravljene gornje trougaone matrice posle Gausovog algoritma sa parcijalnim pivotiranjem : " << endl;
		ispisiAB(AB, n);
		cout << "Resenja sistema jednacina " << n << " stepena je: " << endl;
		postupakUnazad(AB, n, X);

		brisiA(A, n);
		brisiBX(B, n);
		brisiBX(X, n);
		brisiAB(AB, n);
		n++;
	}
	return 0;
}