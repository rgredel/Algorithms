#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
using namespace std;

string textGenerator(int n);        //funkcja generująca tekst o długości n

int naiveStringMatching(string T, string p);

int BoyerMoore(string T, string p);
int naiveStringMatchingSilance(string T, string p);
int BoyerMooreSilance(string T, string p);
int main(int argc, char** argv) {

//testy dla zadania 1
string text="wzorzec jest szukany w tym tekscie za pomocą algorytmu Boyera-Moorea, wzorzec jest na poczatku, w środku a na koncu tez jest wzorzec";
string pattern="wzorzec";

cout<<"Wyszukiwanie naiwne:\n";
naiveStringMatching(text,pattern);

cout<<"\nWyszukiwanie Boyer-Moore\'a: \n ";
BoyerMoore(text,pattern);

//testy dla zadania 2
//wielokrotne powtórzenie: generaracja tekstu i wzorca, wyszukanie obydwoma algorytmami, wyświetlenie wyników
/**/
cout << "\n\n\n\ZADANIE 2";
for (int i = 10 ; i < 100; i=i+10){
	string text = textGenerator(i);
	string pattern = textGenerator(5);
	cout << "\nLiczba powtórzeń dla naiveStringMatching(): "<<naiveStringMatchingSilance(text, pattern)<<endl;
	cout << "Liczba powtórzeń dla BoyerMoore(): "<< BoyerMooreSilance(text, pattern)<<endl;

}

return 0;
}

string textGenerator(int n){
	srand (time(NULL));
	string tekst="";
	char x;
	for (int i = 0; i<n ; ++i){
		x = (rand() %25) +97;
		tekst += x;
	}
 return tekst;
}

int naiveStringMatching(string T, string p){
	int m = p.length();
	int n = T.length();
	int licznik=0;
	int s = 0;
	for(s; s <= (n-m); s++){
		licznik++;
		int i = 0;
		while (i < m && p[i] == T[s+i]) i++;
		if (i == m) cout << "wzorzec wystąpił z przesunięciem: " <<s<<endl;
	}
	return licznik;
}

int BoyerMoore(string T, string p){
	int m = p.length();
	int n = T.length();
	int licznik=0;
	//wstępne przetwarzanie wzorca
	int bc[T.length()]{-1};
	for (int i = 0 ; i < m; i++){
		bc[p[i]] = i;
	}

	//uproszczony algorytm Boyera-Moorea

	int s = 0;
	while (s < n-m){
		licznik++;
		int i = m-1;
		while(i >= 0 && p[i] == T[s+i]) i--;
		if(i == -1) {
			cout << "wzorzec wystąpił z przesunięciem: " << s << endl;
			s = s +1;
		}
		else{
			if(bc[T[s+i]] == -1) s = s + i + 1 ;
			else if(bc[T[s+i]] < i) s = s + i - bc[T[s+i]];
			else s++ ;

		}
	}
	return licznik;
}



int naiveStringMatchingSilance(string T, string p){
	int m = p.length();
	int n = T.length();
	int licznik=0;
	int s = 0;
	for(s; s <= (n-m); s++){
		licznik++;
		int i = 0;
		while (i < m && p[i] == T[s+i]) i++;
		if (i == m);// cout << "wzorzec wystąpił z przesunięciem: " <<s<<endl;
	}
	return licznik;
}

int BoyerMooreSilance(string T, string p){
	int m = p.length();
	int n = T.length();
	int licznik=0;
	//wstępne przetwarzanie wzorca
	int bc[T.length()]{-1};
	for (int i = 0 ; i < m; i++){
		bc[p[i]] = i;
	}

	//uproszczony algorytm Boyera-Moorea

	int s = 0;
	while (s < n-m){
		licznik++;
		int i = m-1;
		while(i >= 0 && p[i] == T[s+i]) i--;
		if(i == -1) {
			//cout << "wzorzec wystąpił z przesunięciem: " << s << endl;
			s = s +1;
		}
		else{
			if(bc[T[s+i]] == -1) s = s + i + 1 ;
			else if(bc[T[s+i]] < i) s = s + i - bc[T[s+i]];
			else s++ ;

		}
	}
	return licznik;
}

