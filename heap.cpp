#include <iostream>
using namespace std;

class Heap{
    private:
        int* kopiec;
        int capacity;
        int size;
    public:
        Heap(int c);            //tworzy pusty kopiec o pojemności c
        bool empty();
        bool full();
        void bottomUp(int i);                //przywraca własność kopca metodą wynurzania
        void topDown(int i);                //przywraca własność kopca metodą zatapiania
        friend std::ostream& operator<<(std::ostream& out, Heap& h){

        	if(h.empty()) out << "Kopiec jest pusty";
        	else{

                		for (int i = 0; i < h.size ; i++){
                		out << h.getValue(i) <<" ";
                		}
                }

            return out;
        }
        void insert(int x);                    //wstawia wartość x
        void extractMax();                     //usuwa maksymalną wartość
        int maximum();                        //zwraca maksymalną wartość
        int getLeft(int i);                    //zwraca pozycję lewego syna
        int getRight(int i);                //zwraca pozycję prawego syna
        int getParent(int i);                //zwraca pozycję ojca/
        int getSize();                        //zwraca rozmiar kopca
        void setSize(int s);                //ustawia rozmiar kopca na s
        int getValue(int i);                //zwraca wartość z pozycji i
        void setValue(int i, int x);        //ustawia wartość x na pozycji i
};

int main(int argc, char** argv) {

Heap h(8);
cout << " Mamy kopiec 8 elementowy h(15) \n Wypisujemy zawartosc kopca cout << h : " << h;
cout << "\n Wprowadzamy 8 elementow do kopca h.insert(i) dla i kolejno : 4 1 5 2 6 2 5 6";
h.insert(4);
h.insert(1);
h.insert(5);
h.insert(2);
h.insert(6);
h.insert(2);
h.insert(5);
h.insert(6);
cout << "\n Ponownie sprawdzamy zawartosc kopca: " << h;
cout << "\n Sprwadzamy czy kopiec jest pełny: h.full(): (1-tak , 0-nie)" << h.full();
cout << "\n Rozmiar kopca: getSize(): " << h.getSize();
cout << "\n Maksymalna wartosc maximum(): " << h.maximum();
cout << "Usuwanie najwiekszej wartosci extractMax() i wyświetlenie nowego kopca: ";
h.extractMax();
cout << h;

  return 0;
}

		void Heap::bottomUp(int i)               //przywraca własność kopca metodą wynurzania
		{
			if(i>0) {
			int p = getParent(i);
			if(kopiec[i] > kopiec[p]){
				int temp = kopiec[i];
				kopiec[i] = kopiec[p];
				kopiec[p] = temp;
				bottomUp(p);
			}
			}
		}
        void Heap::topDown(int i)                //przywraca własność kopca metodą zatapiania
        {
        	int l = getLeft(i);
        	int r = getRight(i);
        	int g = i;
        	if( (l < size) && (kopiec[l] > kopiec[i])) {
        		g = l;
        	};

        	if( (r < size) && (kopiec[r] > kopiec[g])) {
        		g = r;
        	};

        	if(g > i){ // g!=i nie działa
        		int temp = kopiec[i];
        		kopiec[i] = kopiec[g];
        		kopiec[g] = temp;
        		topDown(g);

        	};


        }

        void Heap::insert(int x)                   //wstawia wartość x
        {
        	if(full()) cout << "Kopiec pełny!";
        	else{
        		kopiec[size] = x;
        		bottomUp(size);
        		size ++;
        	}
        }
        void Heap::extractMax()                     //usuwa maksymalną wartość
        {
        	if(empty()) cout << "kopiec pusty";
        	else {

        		int temp = kopiec[0];
        		size --;
        		kopiec[0] = kopiec[size];
        		kopiec[size] = temp;
        		topDown(0);

        	}
        	;
        }
        int Heap::maximum()                        //zwraca maksymalną wartość
        {
        	return kopiec[0];
        }
        Heap::Heap(int c){            //tworzy pusty kopiec o pojemności c	
        	size = 0;
        	capacity = c;
		kopiec = new int[capacity];
        }
        bool Heap::empty(){
        	if(size == 0) return true;
        	else return false;
        }
        bool Heap::full(){
        	if (size == capacity) return true;
        	else return false;
        }
        int Heap::getLeft(int i)                    //zwraca pozycję lewego syna
        {
        	if(2*i+1 < size ) return 2*i + 1;
        	else return -1;
        }
        int Heap::getRight(int i)               //zwraca pozycję prawego syna
        {
        	if(2*i+2 < size ) return 2*i + 2;
        	        	else return -1;
        }
        int Heap::getParent(int i)                //zwraca pozycję ojca/
        {
        	if(i==0) return -1;
        	else return (i-1)/2;
        }
        int Heap::getSize()                        //zwraca rozmiar kopca
        {
        	return size;
        }
        void Heap::setSize(int s)                //ustawia rozmiar kopca na s
        {
        	size = s;
        }
        int Heap::getValue(int i)                //zwraca wartość z pozycji i
        {
        	return kopiec[i];
        }
        void Heap::setValue(int i, int x)        //ustawia wartość x na pozycji i
        {
        	kopiec[i]=x;
        }
