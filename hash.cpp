#include <iostream>
#include <string>
using namespace std;
std::string::size_type sz;
class HashTable{
    private:
        string* t;
        int capacity;
        int size;
    public:
        HashTable(int c);                //konstruktor tworzący pustą tablicę o pojemności c
        bool empty();
        bool full();
        int hashFunction(string s);        //funkcja haszująca dla klucza s
        int insert(string s);            //wstawienie klucza s (zwraca liczbę prób przy wystąpieniu kolizji)
        int del(string s);                //usuwa klucz s (zwraca liczbę prób przy wystąpieniu kolizji)
        int search(string s);        //wyszukuje s i zwraca jego pozycję (-1 jeśli s nie istnieje)
        friend ostream& operator<<(ostream& out, HashTable& ht){ //wypisuje zawartość tablicy (indeks + słowo jeśli pozycja jest zajęta)
         if(!ht.empty()){
        	for (int i=0; i < ht.capacity; i++){
			 if (( (ht.t[i]) != "NULL") && ( ht.t[i] != "FREE" )){
				 out << "t[" <<i<<"] = " << ht.t[i]<<endl;
			 }
			}
         }
         else out << "Tablica jest pusta";
         out <<"\n\n";
         return out;
        }
};

int main(int argc, char** argv) {
string dane[40]{
		"Julia",
		"Zuzanna",
		"Zofia",
		"Lena",
		"Maja",
		"Hanna",
		"Amelia",
		"Alicja",
		"Maria",
		"Aleksandra",
		"Oliwia",
		"Natalia",
		"Wiktoria",
		"Emilia",
		"Antonina",
		"Laura",
		"Pola",
		"Iga",
		"Anna",
		"Liliana",
		"Antoni",
		"Jakub",
		"Jan",
		"Szymon",
		"Franciszek",
		"Filip",
		"Aleksander",
		"Mikolaj",
		"Wojciech",
		"Kacper",
		"Adam",
		"Michal",
		"Marcel",
		"Stanislaw",
		"Wiktor",
		"Piotr",
		"Igor",
		"Leon",
		"Nikodem",
		"Mateusz"
};
// Testy dla zadania 1
{
int n = 7;                //pojemność tablicy z haszowaniem
HashTable h( n );

cout<<"empty(): 1 - "<<h.empty()<<endl;
//cout<<"insert(...)"<<h.insert(...);    //po każdym wstawieniu/usunięciu klucza należy wyświetlić aktualny stan h, po wyszukiwaniu zwrócony indeks
// ...
for (int i = 0; i < n ; i++){
		cout << "Dodano: " << dane[i] << " przy ilości prób: " << h.insert(dane[i]) << endl;
		cout << h;
	}
cout << "Hanna jest na pozycji: t[" << h.search("Hanna")<<"] \n";
cout << "Usuwamy \"Lena\". Do usunięcia potrzeba było: " << h.del("Lena") << " prób\n" << h;
cout << "Lena jest na pozycji: t[" << h.search("Lena")<<"] \n";
}
//testy dla zadania 2
{
	int n = 40;                //pojemność tablicy z haszowaniem
	HashTable h( n );
	int kolizje{},maksimum{};
	double srednia;
	for (int i = 0; i < n ; i++){
		int prob =  h.insert(dane[i]);
		kolizje += prob;
		if(prob>maksimum) maksimum = prob;
	}
	srednia = kolizje/n;
	cout << "************************************************************************\nZADANIE 2\n";
	cout << "Dla h: \n"<< h << "Wystąpiło kolizji: " << kolizje << "\nŚrednia liczba prób wynosiła: "<<srednia<<endl;
	cout << "A maksymalna liczba kolizji to: " << maksimum;
}




    return 0;

}
HashTable::HashTable(int c){
	capacity = c;
	size = 0;
	t = new string[c];
	for( int i = 0; i < capacity; i++)t[i] = "NULL";
}
bool HashTable::empty(){
	if(size == 0 ) return 1;
	else return 0;
}
bool HashTable::full(){
	if (capacity == size) return 1;
	else return 0;
}
int HashTable::hashFunction(string s){
	int sInt=0;
	for (int i = 0; i < s.length() ; i++){
		sInt += s[i];
	}
	return sInt%capacity;
}
int HashTable::insert(string s){
if(!full()){
	int i = 0;
	/**/
	while ( ( (t[(hashFunction(s)+i)%capacity]) != "NULL" ) && ( ( t[(hashFunction(s)+i)%capacity]) != "FREE" )) i++;

	t[(hashFunction(s)+i)%capacity] = s;
	size++;
	return i;

}
else cout << "tablica jest pełna";
}
int HashTable::del(string s){
	int i = 0;
	while( ((t[(hashFunction(s)+i)%capacity]) != "NULL" ) && (i < capacity) ){
		if(t[(hashFunction(s)+i)%capacity] == s){
			t[(hashFunction(s)+i)%capacity] = "FREE";
			size--;
			return i;
		}
		i++;
	}
	return i;
}
int HashTable::search(string s){
int i = 0;
while( ((t[(hashFunction(s)+i)%capacity]) != "NULL" ) && (i < capacity) ){
	if(t[(hashFunction(s)+i)%capacity] == s) return (hashFunction(s)+i)%capacity;
	i++;
}
return -1;
}
