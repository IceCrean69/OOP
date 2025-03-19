#include <string>
#include <vector>
#include <iostream>
using namespace std;


class InvoiceItem
{
    public:
        string name;
        int price;
    public:
        InvoiceItem(string n, int p): name(n), price(p){}
        void invoice()
        {
            cout << "Thing bought: " << name << " price: " << price << endl; 
        }

};
class Person
{
    public:
        string firstName;
        string lastName;
        string adress;
        vector <InvoiceItem*> invoiceItems;
    
    public:
        Person(string f, string l, string a) : firstName(f), lastName(l), adress(a){}
        ~Person()
        {
            for(InvoiceItem* item: invoiceItems)
            {
                delete item;
            }
        }
        void introduction()
        {
            cout << "hello my name is: " << firstName<< " " << lastName << ", I live at: " << adress << endl; 
        }
        void addInvoice(InvoiceItem* invoiceItem)
        {
            invoiceItems.push_back(invoiceItem);
        }

        void allInvoices()
        {
            if(invoiceItems.empty())
            {
                cout << "No invoices" << endl;
            }
            else
            {
                for(auto i: invoiceItems)
                {
                    cout << "Invoice item: " << i->name << " price: " << i->price << endl;
                }
            }
        }

        void calculateInvoice()
        {
            
            if(invoiceItems.empty())
            {
                cout << "invoice sum: 0";
                return;
            }
            else
            {
                int sum = 0;
                for(auto i: invoiceItems)
                {
                    sum += i->price;
                }
                cout << "Invoice sum: " << sum << endl;   
            }
        }
};
class Invoice
{
    public:
        int personCount = 0;
        vector<Person*> invoicePerson;
    ~Invoice()
    {
        for(Person* person: invoicePerson)
        {
            delete person;
        }
    }
    void addPerson(Person* person)
    {
        invoicePerson.push_back(person);
        personCount ++;
        return;
    }
    void printAllPersons()
    {
        if(invoicePerson.empty())
        {
            cout << "no person added" << endl;
            return;
        }
        else
        {
            for (auto i: invoicePerson)
            {
                cout << "" << endl;
                cout << "First Name: " << i->firstName<< endl;
                cout << "Last Name: " << i->lastName << endl;
                cout << "Adress: " << i->adress<< endl;
                if(i->invoiceItems.empty())
                {
                    cout << "" << endl;
                    cout << "No items bought" << endl;
                }
                else
                {
                    for(auto j: i->invoiceItems)
                    {   
                        cout << "" << endl;
                        cout << "Invoice item: " << j->name<< endl;
                        cout << "Invoice price: " << j->price << endl;  
                    }
                }
                cout << "-------------------------------------------" << endl;
            }
            
        }
        cout << "" << endl;
        return;
    }
    void calculateInvoice(string lastName)
    {
        if(!invoicePerson.empty())
        {
            for(auto i: invoicePerson)
            {
                if(i->lastName == lastName)
                {
                    int sum = 0;
                    for (auto j: i->invoiceItems)
                    {
                        sum += j->price;
                    }
                    cout << "Total sum of invoice for "<<i->firstName << " " << i->lastName <<" : " << sum << endl;
                    return;
                }
            }
        }
        cout << "No person found";
        return;
    }
        



};

int main()
{
    Invoice invoice;
    Person* person1 = new Person("Jakub", "Galica", "Moravska");
    Person* person2 = new Person("Michal", "Babusak", "Pica Praha");
    InvoiceItem* invoice1 = new InvoiceItem("Television", 500);
    InvoiceItem* invoice2 = new InvoiceItem("iPhone", 800);


    person1->addInvoice(invoice1);
    person1->addInvoice(invoice2);

    invoice.addPerson(person1);
    invoice.addPerson(person2);
    invoice.printAllPersons();
    invoice.calculateInvoice("Galica");
    return 0;
}