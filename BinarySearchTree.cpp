#include <iostream>
using namespace std;

class Node{
    private:
        int value;
        Node* left;
        Node* right;
        Node* parent;
    public:
        Node(int v, Node* l, Node* r, Node* p);
        int getValue();
        Node* getLeft();
        Node* getRight();
        Node* getParent();
        void setValue(int v);
        void setLeft(Node* l);
        void setRight(Node* r);
        void setParent(Node* p);
};

class BSTree{
    private:
        Node* root;
    public:
        BSTree();                        //tworzy puste drzewo
        Node* getRoot();            //zwraca wskażnik do root - metoda pomocnicza w testowaniu
        bool empty(Node* p);        //zwraca prawdę gdy (pod)drzewo p jest puste
        void inorder(Node* p);     //wyświetla węzły w porządku inorder
        void insert(int x);            //wstawia węzeł z wartością x
        Node* search(int x);         //zwraca wskaźnik do węzła z wartością x (lub NULL jeśli nie istnieje)
        Node* minumim(Node* p);            //zwraca wskaźnik do węzła z minimalną wartością w poddrzwie p
        Node* maximum(Node* p);            //zwraca wskaźnik do węzła z maksymalną wartością w poddrzewie p
//        void del(Node* p);            //usuwa węzeł wskazywany przez p
        int size(Node* p);                  //zwraca rozmiar drzewa
        int hight(Node* p);              //zwraca wysokość drzewa
//        void clear(Node* p);           //usuwa wszystkie węzły z drzewa
};

int main(int argc, char** argv) {

BSTree* t = new BSTree();
cout<< "Reprezentacja drzewa: 5 2 8 1 7 4 9 3 6 " << endl;
t->insert(5);
t->insert(2);
t->insert(8);
t->insert(1);
t->insert(7);
t->insert(4);
t->insert(9);
t->insert(3);
t->insert(6);
cout<< "Uporzątkuj wartości w drzewie metodą(inorder): ";t->inorder(t->getRoot());
cout << "Wyszukaj liczbe 1: search(1): "<<t->search(1)->getValue();
cout << endl << "Największa wartosc drzewa: maximum(T): " <<t->maximum(t->getRoot())->getValue();
cout << endl << "Najmniejsza wartosc drzewa: minumim(T): "<< t->minumim(t->getRoot())->getValue();
cout << endl << "Rozmiar drzewa : size(T): " << t->size(t->getRoot());
cout << endl << "Wysokosc drzewa : height(T): " << t->hight(t->getRoot());
return 0;
}	 // Node
		Node::Node(int v, Node* l, Node* r, Node* p){
			value = v;
			left = l;
			right = r;
			parent = p;
		}
		int Node::getValue(){return value;}
        Node* Node::getLeft(){return left;}
        Node* Node::getRight(){return right;}
        Node* Node::getParent(){return parent;}
        void Node::setValue(int v){value = v;}
        void Node::setLeft(Node* l){left = l;}
        void Node::setRight(Node* r){right = r;}
        void Node::setParent(Node* p){parent = p;}

      // BSTree
        BSTree::BSTree(){root = nullptr;} 						//tworzy puste drzewo
               Node* BSTree::getRoot(){return root;}            //zwraca wskażnik do root - metoda pomocnicza w testowaniu
               bool BSTree::empty(Node* p){						//zwraca prawdę gdy (pod)drzewo p jest puste
            	   if(p == nullptr) return true;
            	   else return false;
               }
               void BSTree::inorder(Node* p){					//wyświetla węzły w porządku inorder
            	   if(!empty(p)){


            		   this->inorder(p->getLeft());
            		   cout << p->getValue() << " ";
            		   this->inorder(p->getRight());

            	   }

               }
               void BSTree::insert(int x){						//wstawia węzeł z wartością x
            	  if(empty(this->getRoot())){
            		  Node* e = new Node(x, nullptr, nullptr, nullptr);
            		  root = e;
            	  }
            	  else {

            		  Node* e = new Node(x, nullptr, nullptr, nullptr);
            		  Node* p = root;
            		  bool stop = false;
            		  while(!stop){
            			  if((p->getValue()) > x){

            				  if(empty(p->getLeft())){
            					  p->setLeft(e);
            					  e->setParent(p);
            					  stop = true;
            				  }
            				  else{ p = p->getLeft();

            				  }
            			  }
            			  	 else if (p->getValue() < x){
            			    if(!(empty(p->getRight()))) p = p->getRight();
            				   else{

            				      p->setRight(e);
            				      e->setParent(p);
            				      stop = true;
            				  }
            			  }

            		  }


               }
               }



               Node* BSTree::search(int x){	 					//zwraca wskaźnik do węzła z wartością x (lub NULL jeśli nie istnieje)
            	   Node* p = root;
            	   while(!empty(p) && (p->getValue() != x)){
					   if(p->getValue() > x) p = p->getLeft();
					   else p = p->getRight();
            	   }
            	   return p;
               }
               Node* BSTree::minumim(Node* p){					 //zwraca wskaźnik do węzła z minimalną wartością w poddrzwie p
            	   if(empty(root)) return nullptr;
            	        else {p = root;
            	   		while(!(empty(p->getLeft()))){
            	   		 p = p->getLeft();
            	   		 }
            	   		return p;
            	       }
               }
               Node* BSTree::maximum(Node* p){					//zwraca wskaźnik do węzła z maksymalną wartością w poddrzewie p
            	   if(empty(root)) return nullptr;
            	   else {p = root;
					   while(!(empty(p->getRight()))){
						   p = p->getRight();
					   }
					   return p;
            	   }
               }
               int BSTree::size(Node* p){  						//zwraca rozmiar drzewa
            	   if(empty(p)) return 0;
            	   else return (1 + size(p->getLeft()) + size(p->getRight()));
               }

               int BSTree::hight(Node* p){		 //zwraca wysokość drzewa
            	   if(empty(p)) return -1;
            	   else return (1 + max(hight(p->getLeft()) , hight(p->getRight())));
              }

