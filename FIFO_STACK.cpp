#include <iostream>
using namespace std;

class Element{
    private:
        int value;
        Element* next;
    public:
        Element(int x, Element* next);
        int getValue();
        Element* getNext();
        void setNext(Element* p);
};

class LinkedStack{
    private:
        Element* top;
    public:
        LinkedStack();        //tworzy pusty stos
        bool empty();
        void push(int x);
        int getTop();            //zwraca daną ze stosu
        void pop();            //usuwa element ze stosu
        void clear();
        friend std::ostream& operator<<(std::ostream& out, LinkedStack* s) //wyświetla zawartość całego stosu
        {
        	if(s->empty()) {
        		out << " Stos jest pusty ";
        		return out;
        	}
        		Element* e = s->top;
        	    while (e != nullptr)  {

        	            out  << e->getValue() << "  ";
        	        e = e->getNext();
        	    	}
        	    return out;
        }
        ~LinkedStack();
};

class ArrayFifo{
    private:
        int* items;
        int capacity;            //pojemność kolejki
        int size;                //rozmiar kolejki (liczba elementów w kolejce)
        int head;
        int tail;
    public:
        ArrayFifo(int c);        //tworzy pustą kolejkę o pojemności c
        bool empty();
        bool full();
        void enqueue(int x);
        int peek();
        void dequeue();        //usuwa daną z kolejki
        void clear();
        friend std::ostream& operator<<(std::ostream& out, ArrayFifo* f){    //wyświetla zawartość kolejki (od head do tail)
        	for (int i = 0; i <= f->tail; i++) out << f->items[i] << " ";
        	return out;
        }
        ~ArrayFifo();
};

//FIFO
void ArrayFifo::clear(){
	if(empty()) cout << "Nie ma zadnych elementow w kolejce";
	for (int i = 0; i < capacity; i++)
	    items[i] = 0;
	    head = 0;
	    size = 0;
	    tail = 0;
}
ArrayFifo::ArrayFifo(int c){
	items = new int[c];
	capacity = c;
	size = 0;
	head = 0;
	tail =0;
}

void ArrayFifo::dequeue(){
	if(empty()) cout << "Nie ma zadnych elementow w kolejce";
	else {
		items[head] = 0;
		for (int i = 0; i < size; i++)
		items[i] = items[i + 1];
		size--;
		tail--;
	}
}
int ArrayFifo::peek(){return *(items+head);}
void ArrayFifo::enqueue(int x){
	if (empty()) {
	     items[head] = x;
	     size++;
	    }

	else{
	     tail++;
	     size++;
	     items[tail] = x;
	    }
}
bool ArrayFifo::full(){
	if (size == capacity) return true;
	else return false;
}
bool ArrayFifo::empty(){
	if (size == 0) return true;
	else return false;
}






//Element
Element::Element(int x, Element* next){
	value = x;
	Element::next = next;
	}

int Element::getValue(){return value;}

Element* Element::getNext(){return next;}

void Element::setNext(Element* p){next = p;}


//LinkedStack
LinkedStack::LinkedStack(){top = nullptr;}
bool LinkedStack::empty(){
	if( top == nullptr ) return true;
	else return false;
	}

void LinkedStack::push(int x){
	Element* e = top;
	top = new Element(x,e);
}

void LinkedStack::pop(){
	if (empty()) cout << "stos pusty";
	else {Element* e = top ;
	top = top->getNext();
	delete e;
	}
}
int LinkedStack::getTop(){
	if (empty()) cout << "stos pusty";
	else return top->getValue();
}
void LinkedStack::clear(){
	while (top != nullptr){
		pop();
	}
}

void testujStos(LinkedStack* s){
	cout << "\n________________TESTOWANIE STOSU________________\n";
	cout<< "empty(): "<< s->empty()<< endl<<endl;

	cout<< "Dodanie 3 elementow: \n push(2): ";
	s->push(2);
	cout << s  << "\n push(4): ";
	s->push(4);
	cout << s  << "\n push(4): ";
	s->push(3);
	cout << s << endl<< endl;

	cout << "Usuwanie elementu: \n pop(): ";
	s->pop(); cout <<s;

	cout << " \n \n getTop(): " << s->getTop();
	cout << "\n \n empty(): "<< s->empty()<< endl<<endl;
	cout << "clear(): " ;
	s->clear();
	cout << "\nempty(): "<< s->empty();
	cout << "\n_______________________________________________\n";
}

void testujFifo(int c){
	cout <<"*************************\nTESTOWANIE FIFO\n*************************\n";
	ArrayFifo* f = new ArrayFifo(c);
	cout<< "empty(): "<< f->empty() << endl<<endl;

	cout<< "Dodanie 3 elementow: \n enqueue(2): ";
	f->enqueue(2);
	cout << f  << "\n enqueue(4): ";
	f->enqueue(4);
	cout << f  << "\n enqueue(3): ";
	f->enqueue(3);
	cout << f << endl<< endl;

	cout << "Usuwanie elementu: \n dequeue(): ";
	f->dequeue(); cout << f;

	cout << " \n \n peek(): " << f->peek();
	cout << "\n \n empty(): "<< f->empty()<< endl<<endl;
	cout << "clear(): " ;
	f->clear();
	cout << "\nempty(): "<< f->empty();
	cout <<"**********************************************************************";
}
int main(){

LinkedStack* s = new LinkedStack();
testujStos(s);
testujFifo(7);



}
