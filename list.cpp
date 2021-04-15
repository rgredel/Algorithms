#include <iostream>
using namespace std;

class Element{
private:
    int v;
    Element* next;
    Element* prev;

public:
    Element(int x, Element* next, Element* prev);    //tworzy element przechowujący x
    int getValue();                                    //zwraca wartość
    void setValue(int v);                            //ustawia warość v
    Element* getNext();                                //zwraca pozycję następnego elementu
    Element* getPrev();                                //zwraca pozycję poprzedniego elementu
    void setNext(Element* p);                        //ustawia p jako następny element
    void setPrev(Element* p);                        //ustawia p jako poprzedni element
};


class OrderedLinkedList{
private:
    Element* head;                    //pozycja pierwszego elementu
    Element* tail;                    //pozycja ostatniego elementu
    int size;

public:
    int getTail(){return tail->getValue();};
    int getHead(){return head->getValue();};
    OrderedLinkedList();                                //tworzy pustą listę
    bool empty();                                //zwraca prawdę jeśli lista pusta, fałsz w przeciwnym przypadku
    int getSize();                                //zwraca wielkość listy (liczbę elementów w liście)
    Element* locate(int x);                         //zwra pozycję wystąpienia elementu x, nullptr jeśli x nie występuje
    void insert(int x);              //wstawia element z wartością x tak, aby zachowany został porządek niemalejący
    void del(int x);                            //usuwa pojedynczy element w wartością x
    void clear();                    //usuwa wszystkie elementy z listy
    void concat(OrderedLinkedList* l);                    //do bieżącej listy dołącza listę l z zachowaniem porządku
    friend ostream& operator<<(ostream& out, OrderedLinkedList* l) //wypisuje elementu listy
    {
            Element* e = l->head;
            if(e == nullptr) out << "Lista pusta \n";
            else {
				for (int i = 0; i < l->getSize(); i++)
				{
					out << e->getValue() << " ";
					if ( i <l->getSize()-1) e = e->getNext();
				}
				out << endl;
				return out;
            }
            return out;

        }
    ~OrderedLinkedList();
};
//Element
Element::Element(int x, Element* next, Element* prev){
	v = x;
	this->next= next;
	this->prev = prev;
}
int Element::getValue(){return v;}
void Element::setValue(int v){this->v = v;}
Element* Element::getNext(){return next;}
Element* Element::getPrev(){return prev;}
void Element::setNext(Element* p){next = p;}
void Element::setPrev(Element* p){prev = p;}

//OrderedLinkedList
OrderedLinkedList::OrderedLinkedList(){
	head=nullptr;
	tail=nullptr;
	size = 0;
	}
bool OrderedLinkedList::empty(){
		if (this->getSize() == 0) return true;
		else return false;
	}
int OrderedLinkedList::getSize(){

	return size;
}
Element* OrderedLinkedList::locate(int x){
	if (empty()) cout << "lista pusta";
	else{
		Element* p = head;
		while(p != nullptr){
			if (p->getValue() == x )return p;
			else p = p->getNext();
		}
		return p ;
		}
	}
void OrderedLinkedList::insert(int x){


	if(OrderedLinkedList::empty()) {
	                Element* nowy = new Element(x, nullptr, nullptr);
	                head = nowy;
	                tail = nowy;
    }
	else if(head->getValue() > x) {
	                Element* nowy = new Element(x, head, nullptr);
	                head->setPrev(nowy);
	                head = nowy;
	}
	else if(tail->getValue() < x) {
	                Element* nowy = new Element(x,  tail, nullptr ); //tail <=> null?
	                tail->setNext(nowy);
	                tail = nowy;
	}
	else {
	              /**/  Element* e = head;
	          while(e->getNext()->getValue() < x ) e = e->getNext();

              Element* nowy = new Element(x,  e->getNext(), e);

	          e->setNext(nowy);

	     }
	size ++;
};

void OrderedLinkedList::del(int x){
	if (empty()) cout << "Lista jest pusta";
	else if(head->getValue() == x) {
	                Element* n = head->getNext();
	                delete head;
	                n->setPrev(nullptr);
	                head = n;
	            }

	else {
	                Element* e = head;
	                while(e->getNext()->getValue() != x) e = e->getNext();

	                        Element* n = e->getNext()->getNext() ;
	                        Element* del = e->getNext();
	                        if(e->getNext()==tail) {
	                        	tail = e;
	                        }
	                        e->setNext(n);
	                        n->setPrev(e);
	                        delete del;

	            }
	            size --;

	       }


int main(){

OrderedLinkedList* a = new OrderedLinkedList();
cout << "Dodajemy wartości 4 , 1, 3, 5, 2  \n";
a->insert(4);a->insert(1);a->insert(3);a->insert(5);a->insert(2);a->insert(7);a->insert(9);a->insert(8);a->insert(6);
cout << "Nasza lista: " <<a<< endl;
cout << "Szukana wartosc jest na adresie : " << a->locate(3) << " wartosc to: "  << a->locate(3)->getValue()<< endl;
cout<< "Usuwamy element z wartością 1(head): " <<endl; a->del(1);
cout <<a<< "Nowy head: "<<a->getHead()<<endl;
cout<< "Usuwamy element z wartością 5(środek): " <<endl; a->del(5);
cout <<a<< endl;

cout<< "Usuwamy element z wartością 9(tail): " <<endl; a->del(9);
cout <<a<< endl;
cout <<"Nowy tail: " <<a->getTail()<<endl;


}
