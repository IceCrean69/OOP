#include <string>
#include <iostream>

using namespace std;

struct Node{
    int data;
    Node* next;
};


struct StringNode {
    string data;
    StringNode* left, * right;

    StringNode(string key) {
        data = key;
        left = nullptr;
        right = nullptr;
    }
};

class StringClass {
    public:
        string data;
        StringClass* left, * right;

        StringClass(string key) {
            data = key;
            left = nullptr;
            right = nullptr;
        }


    
};

void DFS(StringNode* stringNode)
    {
        if(stringNode == nullptr) return;

        DFS(stringNode->left);
        cout << stringNode->data << endl;
        DFS(stringNode -> right);

    }


class KeyValues
{
    Node* head;
    public:
        KeyValues() : head(NULL){}

    void insertStart(int value)
    {
        Node* newNode = new Node();
        newNode->data = value;
        newNode->next = head;
        head = newNode;
    }

    void insertEnd(int value)
    {
        Node* newNode = new Node();
        newNode->data = value;
        newNode->next = NULL;

        if(!head)
        {
            head = newNode;
            return;
        }

        Node* temp = head;
        while(temp->next)
        {
            temp = temp->next;
        }

        temp->next = newNode;


    }

    void Display()
    {
        if(!head)
        {
            cout << "list is empty" << endl;
            return;
        }
        Node* temp = head;
        while(temp)
        {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL \n";
    }

};


struct Drivers {
    string question;
    string driver;
    Drivers* yes;
    Drivers* no;

    Drivers(const string& q, const string& d, Drivers* y, Drivers* n)
        : question(q), driver(d), yes(y), no(n) {}
};

void printTree(Drivers* node, int depth = 0) {
    string indent(depth * 4, ' ');
    
    if (node == nullptr) {
        cout << indent << "N/A" << endl;
        return;
    }
    
    if (node->driver.empty()) {
        cout << indent << "[Q] " << node->question << endl;
        cout << indent << "Yes =>" << endl;
        printTree(node->yes, depth + 1);
        cout << indent << "No  =>" << endl;
        printTree(node->no, depth + 1);
    } else {
        cout << indent << "[A] " << node->driver << endl;
    }
}



int main()
{   
    KeyValues keyvalue;

    for(int i = 0; i < 1000; i++)
    {
        keyvalue.insertEnd(i);
    }
    keyvalue.Display();
    
    StringNode* root = new StringNode("nieco");
    root->right = new StringNode("hello");
    root->left = new StringNode("niga");

    DFS(root);

    Drivers* verstappen = new Drivers("", "Max Verstappen", nullptr, nullptr);
    Drivers* perez = new Drivers("", "Sergio Perez", nullptr, nullptr);
    Drivers* hamilton = new Drivers("", "Lewis Hamilton", nullptr, nullptr);
    Drivers* russell = new Drivers("", "George Russell", nullptr, nullptr);
    Drivers* leclerc = new Drivers("", "Charles Leclerc", nullptr, nullptr);
    Drivers* sainz = new Drivers("", "Carlos Sainz", nullptr, nullptr);
    Drivers* norris = new Drivers("", "Lando Norris", nullptr, nullptr);
    Drivers* piastri = new Drivers("", "Oscar Piastri", nullptr, nullptr);
    Drivers* alonso = new Drivers("", "Fernando Alonso", nullptr, nullptr);
    Drivers* stroll = new Drivers("", "Lance Stroll", nullptr, nullptr);

    // Aston Martin větev
    Drivers* q_aston = new Drivers("Je řidič Španěl?", "", alonso, stroll);
    Drivers* aston = new Drivers("Jezdí řidič pro Aston Martin?", "", q_aston, nullptr);

    // McLaren větev
    Drivers* q_mclaren = new Drivers("Je řidič Brit?", "", norris, piastri);
    Drivers* mclaren = new Drivers("Jezdí řidič pro McLaren?", "", q_mclaren, aston);

    // Ferrari větev
    Drivers* q_ferrari = new Drivers("Je řidič z Monaka?", "", leclerc, sainz);
    Drivers* ferrari = new Drivers("Jezdí řidič pro Ferrari?", "", q_ferrari, mclaren);

    // Mercedes větev
    Drivers* q_mercedes = new Drivers("Má řidič 7 mistrovských titulů?", "", hamilton, russell);
    Drivers* mercedes = new Drivers("Jezdí řidič pro Mercedes?", "", q_mercedes, ferrari);

    // Red Bull větev
    Drivers* q_redbull = new Drivers("Je řidič Holanďan?", "", verstappen, perez);
    Drivers* redbull = new Drivers("Jezdí řidič pro Red Bull?", "", q_redbull, mercedes);

    // Kořen stromu
    Drivers* start = redbull;

    // Výpis celého stromu
    printTree(start);



    
    return 0;
}
