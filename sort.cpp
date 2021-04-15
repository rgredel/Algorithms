#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
using namespace std;
void swap(int i, int j, int* S){
	int temp = S[i];
	S[i] = S[j];
	S[j]= temp;
}

int split(int* S, int left, int right)
{
	int temp, mid= S[left];

	while (true)
	{
		while (S[right] > mid)right--;
		while (S[left] < mid) left++;
		if (left < right){
			temp = S[left];
			S[left] = S[right];
			S[right] = temp;
			left++;
			right--;
		}
		else
			return right;
	}
}

void print(int* S, int n){              //wyświetla dane na monitorze
for(int i = 0; i < n; i++){
	cout << *S << " ";
	S++;
}
cout << endl;
}

void init(int* S, int n){		//inicjalizuje tablicę S losowymi liczba posortowanymi niemalejąco
	if (n>0){
	srand(time(NULL));

    for( int i = 0; i < n; i++){
	     *(S+i) = (rand()%10000);
			}
	}
	else cout << "n<1";
}

int* copy(int* S, int n){               //zwraca kopie tablicy S
	int *CpyS = new int[n];
	for (int i=0 ; i<n ; i++){
		*(CpyS+i) = *(S+i);
	}
	return CpyS;
}

void insertionSort(int* S, int n){
	for (int i = 0; i < n; i++) {
		int j=i-1;
		int aux = S[i];
		for (j; j>=0; j--){
			if(S[j] > aux) S[j+1]= S[j];
			else break;
		}
		S[j+1] = aux;
	}



}
void selectionSort(int* S, int n){
	for (int i = 0; i < n-1; ++i) {
		int min = i;
		for (int j = i+1; j < n; ++j) {
			if(S[j] < S[min]) min =j;
		}
		swap(i,min,S);

	}

}
void bubbleSort(int* S, int n){
	for (int i = 0; i < n; ++i) {
		for (int j=n-1; j>i; j--) if(S[j] < S[j-1]) swap(j, j-1, S);
	}

}

void quickSort(int* S, int left, int right){
	int pivot;
	if(left<right){
		pivot = split(S, left, right);
		quickSort(S, left, pivot);
		quickSort(S, pivot+1, right);
	}

}




int main(){
//testy dla zadań 1 i 2

int n = 20;                //przykładowy rozmiar dla testowania pojedynczych algorytmów
// Init, print , copy test
int *S = new int[n];
init(S,n);
cout<< "*S       = " ; print(S,n);
int *CpyS = new int[n];
CpyS = copy(S,n);
cout << "Kopia *S = " ;print(CpyS,n);

//selectionSort
selectionSort(CpyS,n);
cout << "Wynik sortowania przez wybieranie: ";
print(CpyS,n);

//insertSort
CpyS = copy(S,n);
insertionSort(CpyS,n);
cout << "Wynik sortowania przez wstawianie: ";
print(CpyS,n);

//bubbleSort
CpyS = copy(S,n);
bubbleSort(CpyS,n);
cout << "Wynik sortowania bubble:           ";
print(CpyS,n);

//bubbleSort
CpyS = copy(S,n);
quickSort(CpyS,0,n);
cout << "Wynik sortowania quick:            ";
print(CpyS,n);

//testy dla zadania 3
//utworzenie 3 dużych (min. 10000) tablic zawierających te same, losowe dane
int size = 10000;
int* bubble = new int[size];
int* insertion = new int[size];
int* quick = new int[size];
init(bubble, size);
insertion = copy(bubble,size);
quick = 	copy(bubble,size);
//sortowanie z wykorzystaniem poszczególnych algorytmów, zmierzenie czasu dla każdego z nich i wyświetlenie wyników
double clk[3]={};
clock_t start = clock();
bubbleSort(bubble, size);
clock_t end = clock();
clk[0] += (double)(end - start);
cout << "Czas wykonania sortowania przez zamiane: " << clk[0]/100 << endl;

 start = clock();
insertionSort(insertion, size);
end = clock();
clk[1] += (double)(end - start);
cout << "Czas wykonania sortowania przez wstawianie: " << clk[1]/100 << endl;

start = clock();
quickSort(quick,0, size);
end = clock();
clk[2] += (double)(end - start);
cout << "Czas wykonania sortowania przez quickSort: " << clk[2]/100 << endl;


}

