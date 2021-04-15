#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
using namespace std;

void print(int* S, int n){              //wyświetla dane na monitorze
for(int i = 0; i < n; i++){
	cout << *S << " ";
	S++;
}
cout << endl;
}

void initSorted(int* S, int n){		//inicjalizuje tablicę S losowymi liczba posortowanymi niemalejąco
	if (n>0){
	srand(time(NULL));
	*S = rand()%10;
    for( int i = 1; i < n; i++){
	     *(S+i) = (rand()%10) + *((S+i)-1) ;
			}
		}
	else cout << "n<1";
	}

int binarySearch1(int* S, int n, int x, int& cnt){   //wersja iteracyjna
	int left = 0;
	int right = n-1;
	int mid;
	while(left <= right){
		cnt++;
		mid = (left + right) / 2;
		if ( *(S+mid) == x ) return mid;
		else if (*(S+mid) > x ) right = mid-1;
		else left = mid + 1;

	}
	return -1;

}

int interpolationSearch1 (int* S, int n, int x, int& cnt){
		int left = 0;
		int right = n-1;
		int mid;
		while( (*(S+left) <= x) &&  (x <= *(S+right)) ){
			cnt++;
			mid = left +  (x - S[left]) * (right-left) / (S[right] - S[left]) ; // wzór z wykładów nie dział mi poprawnie, liczba kroków była zawyżana więc użyłem wzoru z google
			if (* (S+mid) == x) return mid;

			else if (*(S+mid) > x ) right = mid-1;
			else left = mid + 1;
		}
		return -1;
}
int testuj(int* S, int n, int x, int tries){
	int srednia = 0, sredniaInt = 0;
	for (int i=0; i<tries; i++){
		int cnt{} , cntInt{};

		initSorted(S,n);

		binarySearch1(S,n,x,cnt);
		srednia += cnt;

		interpolationSearch1(S,n,x,cntInt);
		sredniaInt += cntInt;

	}
	srednia = srednia/tries;
	sredniaInt = sredniaInt/tries;
	cout << "srednia liczba krokow dla " << tries << " prob"<< endl << "wyszukiwanie binarne: " << srednia << endl << "wyszukiwanie interpolacyjne " << sredniaInt;
	return 0;
}


int main(){
int n = 20;        //przykładowy rozmiar do testów dla zadania 1
int *S = new int[n];
int x;
int cnt= 0 , cntInt = 0;
//inicjalizacja i wyświetlenie S, wczytanie x, wyszukiwanie i wyświetlenie wyników dla wyszukiwania binarnego i interpolacyjnego
initSorted(S,n);
print(S,n);
cout << "Podaj x: ";
cin >> x;

cout << "wyszukiwanie binarne: "  << binarySearch1(S,n,x,cnt)<<endl;
cout << "wyszukiwanie interpolacyjne: " << interpolationSearch1(S,n,x,cntInt)<<endl;
// wyniki eksperymentu dla zadania 2
testuj(S,n,x,50);
}
