#include <iostream>
using namespace std;

const int n = 26; // rozmiar alfabetu
struct Trie{
	Trie* children[n]; //tablica zawierająca dzieci prefixu
	bool isEnd; //true jesli jest koncem slowa
};

struct Trie *createNode(void) { //tworzenie węzła
   struct Trie *node =  new Trie;
   node->isEnd = false;
   for (int i = 0; i < n; i++) node->children[i] = nullptr;
   return node;
};

void printTrie(struct Trie* root, char str[], int depth = 0)
{

    if (root->isEnd)
    {
        str[depth] = '\0';
        cout << str << endl;
    }


    for (int i = 0; i < n; i++)
    {

        if (root->children[i])
        {
            str[depth] = i + 'a';
            printTrie(root->children[i], str, depth + 1);
        }
    }
}

void insert(struct Trie *root, string word){
	Trie *current = root;
	for(int i=0; i < word.length() ; i++){
			int index = word[i] - 'a'; // a zapisujemy na indexie 0, b na 1 itd...
			Trie *node = current->children[index];
			if(node == nullptr){ //jesli obecny element nie ma dziecka
				node = createNode();
				current->children[index]=node;
			}
			current = node;
	}
	current->isEnd = true;
}
bool search(struct Trie *root, string word){
    Trie *current = root;

    for (int i = 0; i < word.length(); i++)
    {
        int index = word[i] - 'a';
        Trie *node = current->children[index];
        if (node == nullptr) return false;
        current = node;
    }

    return current->isEnd;
}
bool empty(Trie* root)
{
    for (int i = 0; i < n; i++)
        if (root->children[i]) return false;

    return true;
}
struct Trie* deleteTrie(Trie *root, string word, int depth = 0){
	if (!root) return nullptr;
	   if (depth == word.length() ) {
	        if (root->isEnd)
	            root->isEnd = false;
	        if (empty(root)) {
	            delete (root);
	            root = nullptr;
	        }
	        return root;
	    }
	    int index = word[depth] - 'a';
	    root->children[index] = deleteTrie(root->children[index], word, depth+1);
	    if (empty(root) && root->isEnd == false) {
	        delete (root);
	        root = nullptr;
	    }

	    return root;
}




int main(){
	//inicjalizacja naszego drzewa TRIE
		char str[100];//max rozmiar slowa
		string words[] = {"testy", "do", "projektu", "z", "algorytmow", "i", "struktur", "danych" };
	    int n = sizeof(words)/sizeof(words[0]);
	    struct Trie *root = createNode();
	    for (int i = 0; i < n; i++)insert(root, words[i]);
//Wyswietlnenie zawartosci TRIE
	    cout << "Słowa w drzewie: \n";
	    printTrie(root,str);

//Operacja wyszukiwania
	    cout<< "Czy słowo \"trie\" jest w drzewie?: ";
	    search(root, "trie") ? cout << "Tak\n" : cout << "Nie\n";

	    cout<< "Czy słowo \"testy\" jest w drzewie?: ";
	   	search(root, "testy") ? cout << "Tak\n" : cout << "Nie\n";
//Opracja usuwania
	   	cout << "Następuje usunięcie słowa\"testy\"\n";
	    deleteTrie(root, "testy");
	    cout<< "Czy słowo \"testy\" jest w drzewie?: ";
	    search(root, "testy") ? cout << "Tak\n" : cout << "Nie\n";
//Testowanie prefixów
	    cout<< "\nTestowanie działania prefix: \n";
	    delete root;
		string prefixes[] = {"p", "pr", "projekt", "prefix"};
	    root = createNode();
	    int m = sizeof(prefixes)/sizeof(prefixes[0]);
	    for (int i = 0; i < m; i++)insert(root, prefixes[i]);
	    printTrie(root,str);

	    cout<< "Czy słowo \"prefix\" jest w drzewie?: ";
	    search(root, "prefix") ? cout << "Tak\n" : cout << "Nie\n";
	    cout << "Usuwamy słowo które ma wspolny prefix z innym słowem -  \"prefix\" :\n";
	    deleteTrie(root, "prefix");
	    printTrie(root,str);
	    cout<< "Czy słowo \"prefix\" jest w drzewie?: ";
	    search(root, "prefix") ? cout << "Tak\n" : cout << "Nie\n";


	    cout<< "\nCzy słowo \"p\" jest w drzewie?: ";
	   	search(root, "p") ? cout << "Tak\n" : cout << "Nie\n";
	    cout << "Usuwamy słowo które jest prefixem innego słowa -  \"p\" :\n";
   	    deleteTrie(root, "p");
   	    printTrie(root,str);
   	    cout<< "Czy słowo \"p\" jest w drzewie?: ";
	    search(root, "p") ? cout << "Tak\n" : cout << "Nie\n";

	    return 0;
}

