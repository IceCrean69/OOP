#include <string>
#include <vector> 
#include <iostream>
#include <fstream> 

using namespace std;
class Client {
private:
    int code;
    string name;
public:
    static int clientsCount;
    Client(int c, string n) : code(c), name(n) {
        Client::clientsCount += 1;
        cout << "Client constructor for " << name << " (Code: " << code << ")" << endl;
    }
    ~Client() {
        clientsCount--;
        cout << "Client destructor for " << name << " (Code: " << code << ")" << endl;
    }
    int GetCode() const { 
        return code;
    }
    string GetName() const { 
        return name;
    }
    static int GetClientCount() {
        return clientsCount;
    }
};
int Client::clientsCount = 0;


// Ciste Abstraktni trida

class AbstractAccount {
    public:
        AbstractAccount() {}
        virtual ~AbstractAccount() {}
        virtual bool CanWithdraw(double a) = 0;
    };

    class Account : public AbstractAccount {
    private:
        int number;
        double interestRate;
        Client *owner;
        Client *partner; 

    protected:
        double balance;

    public:
        static int accountsCount;

        Account(int n, Client *c)
            : AbstractAccount(), number(n), balance(0.0), interestRate(0.0), owner(c), partner(nullptr) {
            accountsCount++;
            cout << "Account constructor for Account #" << this->number << " (Owner: " << owner->GetName() << ")" << endl;
        }

        Account(int n, Client *c, double ir)
            : AbstractAccount(), number(n), balance(0.0), interestRate(ir), owner(c), partner(nullptr) {
            accountsCount++;
            cout << "Account constructor for Account #" << this->number << " with IR (Owner: " << owner->GetName() << ")" << endl;
        }

        Account(int n, Client *c, Client *p)
            : AbstractAccount(), number(n), balance(0.0), interestRate(0.0), owner(c), partner(p) {
            accountsCount++;
            cout << "Account constructor for Account #" << this->number << " with Partner (Owner: " << owner->GetName() << ", Partner: " << (p ? p->GetName() : "None") << ")" << endl;
        }

        Account(int n, Client *c, Client *p, double ir)
            : AbstractAccount(), number(n), balance(0.0), interestRate(ir), owner(c), partner(p) {
            accountsCount++;
            cout << "Account constructor for Account #" << this->number << " with Partner and IR (Owner: " << owner->GetName() << ", Partner: " << (p ? p->GetName() : "None") << ")" << endl;
        }

        virtual ~Account() override {
            accountsCount--;
            cout << "Account destructor for Account #" << this->number << endl;
        }

        static int GetAccountsCount() {
            return accountsCount;
        }
        int GetNumber() const { 
            return number;
        }
        virtual double GetBalance() const {
            return balance;
        }
        double GetInterestRate() const { 
            return interestRate;
        }
        Client* GetOwner() const {
            return owner;
        }
        Client* GetPartner() const {
            return partner;
        }

        virtual bool CanWithdraw(double a) override {
            cout << "Account::CanWithdraw called for #" << GetNumber() << ". Amount: " << a << ", Balance: " << GetBalance() << endl;
            return GetBalance() >= a;
        }

        virtual void Deposit(double a) { 
            cout << "Account::Deposit called for #" << GetNumber() << ". Amount: " << a << endl;
            balance += a;
        }

        bool Withdraw(double a) {
            cout << "Account::Withdraw called for #" << GetNumber() << ". Amount: " << a << endl;
            if (CanWithdraw(a)) { 
                balance -= a;
                return true;
            } else {
                return false;
            }
        }

        void AddInterest() {
            balance = balance * (1 + interestRate);
        }
        void ChangeInterest(double newRate) { 
            this->interestRate = newRate;
        }
};
int Account::accountsCount = 0;

class CreditAccount : public Account {
    private:
        double credit;
    public:
        CreditAccount(int n, Client* o, double c)
            : Account(n, o), credit(c) {
            cout << "CreditAccount constructor for CreditAccount #" << GetNumber() << " with credit " << c << endl;
        }
        CreditAccount(int n, Client* o, double ir, double c)
            : Account(n, o, ir), credit(c) {
            cout << "CreditAccount constructor for CreditAccount #" << GetNumber() << " with IR and credit " << c << endl;
        }

        ~CreditAccount() override { 
            cout << "CreditAccount destructor for CreditAccount #" << GetNumber() << endl;
        }

        virtual bool CanWithdraw(double a) override {
            cout << "CreditAccount::CanWithdraw called for #" << GetNumber() << ". Amount: " << a << ", Balance: " << GetBalance() << ", Credit: " << credit << endl;
            return (GetBalance() + this->credit >= a);
        }
    };


class PartnerAccount : public Account {
    public:
        PartnerAccount(int n, Client *o, Client *p) : Account(n, o, p) {
            cout << "PartnerAccount constructor for #" << GetNumber() << " (Owner: " << o->GetName() << ", Partner: " << p->GetName() << ")" << endl;
        }
        PartnerAccount(int n, Client *o, Client *p, double ir) : Account(n, o, p, ir) {
            cout << "PartnerAccount constructor for #" << GetNumber() << " with IR (Owner: " << o->GetName() << ", Partner: " << p->GetName() << ")" << endl;
        }
        ~PartnerAccount() override {
            cout << "PartnerAccount destructor for #" << GetNumber() << endl;
        }
};


class Bank {
    private:
        Client** clients;
        Account** accounts; 
        int maxClients;
        int maxAccounts;

    public:
        // Simplified constructor, assuming fixed size arrays for example
        Bank(int c, int a) : maxClients(c), maxAccounts(a) {
            clients = new Client*[maxClients](); // Initialize with nullptrs
            accounts = new Account*[maxAccounts](); // Initialize with nullptrs
            cout << "Bank constructor" << endl;
        }
        Bank() : maxClients(100), maxAccounts(100) {
            clients = new Client*[maxClients]();
            accounts = new Account*[maxAccounts]();
            cout << "Bank constructor" << endl;
        }

        ~Bank() {
            cout << "Bank destructor" << endl;
            for (int i = 0; i < Client::GetClientCount(); i++) { 
                if(clients[i]) delete clients[i];
            }
            delete[] clients;

            for (int i = 0; i < Account::GetAccountsCount(); i++) {
                if(accounts[i]) delete accounts[i];
            }
            delete[] accounts;
        }

        Client* GetClient(int c) {
            for (int i = 0; i < Client::GetClientCount(); i++) { 
                if (clients[i] && clients[i]->GetCode() == c) {
                    return clients[i];
                }
            }
            cout << "Client with code " << c << " not found in bank" << endl;
            return nullptr;
        }
        
        Account* GetAccount(int n) {
            for (int i = 0; i < Account::GetAccountsCount(); i++) { 
                if (accounts[i] && accounts[i]->GetNumber() == n) {
                    return accounts[i];
                }
            }
            cout << "Account with number " << n << " not found in bank" << endl;
            return nullptr;
        }

        Client* CreateClient(int c, string n) {
            if (Client::GetClientCount() < maxClients) {
                Client* client = new Client(c, n);
                clients[Client::GetClientCount() -1] = client;
                return client;
            }
            return nullptr;
        }
        Account* CreateAccount(int num, Client *owner) {
            if (Account::GetAccountsCount() < maxAccounts) {
                Account* account = new Account(num, owner);
                accounts[Account::GetAccountsCount() -1] = account;
                return account;
            }
            return nullptr;
        }

        void AddInterest() {
            for (int i = 0; i < Account::GetAccountsCount(); i++) {
                if(accounts[i]) accounts[i]->AddInterest();
            }
        }
};

// 2. Uloha

class IGeometricObject {
    public:
        virtual ~IGeometricObject() {}
        virtual double getArea() const = 0;
        virtual double getPerimeter() const = 0;
        virtual void draw() const = 0;
        virtual string getType() const = 0;
};


class Shape : public IGeometricObject {
    protected:
        string color;
    public:
        Shape(string c) : color(c) {
            cout << "Shape constructor (color: " << color << ")" << endl;
        }
        virtual ~Shape() override {
            cout << "Shape destructor (color: " << color << ")" << endl;
        }

        string getColor() const { return color; }
        void setColor(string c) { color = c; }

        void draw() const override {
            cout << "Drawing a " << color << " " << getType() << "." << endl;
            cout << "  Area: " << getArea() << endl;
            cout << "  Perimeter: " << getPerimeter() << endl;
        }

};

class Circle : public Shape {
    private:
        double radius;
    public:
        Circle(string c, double r) : Shape(c), radius(r) {
            cout << "Circle constructor (color: " << c << ", radius: " << radius << ")" << endl;
        }
        ~Circle() override {
            cout << "Circle destructor (radius: " << radius << ")" << endl;
        }

        double getArea() const override {
            return 3.1415926535 * radius * radius;
        }
        double getPerimeter() const override {
            return 2 * 3.1415926535 * radius;
        }
        string getType() const override {
            return "Circle";
        }
};

class Rectangle : public Shape {
    private:
        double width;
        double height;
    public:
        Rectangle(string c, double w, double h) : Shape(c), width(w), height(h) {
            cout << "Rectangle constructor (color: " << c << ", width: " << width << ", height: " << height << ")" << endl;
        }
        ~Rectangle() override {
            cout << "Rectangle destructor (width: " << width << ", height: " << height << ")" << endl;
        }

        double getArea() const override {
            return width * height;
        }
        double getPerimeter() const override {
            return 2 * (width + height);
        }
        string getType() const override {
            return "Rectangle";
        }
};


int main() {

    // Banka uloha
    Client *client1 = new Client(1, "Alice_Test1");
    Account *acc_ptr = new CreditAccount(101, client1, 50.0); 
    acc_ptr->Deposit(100); 
    delete acc_ptr; 
    delete client1;


    Client *client2 = new Client(2, "Bob_Test2");
    CreditAccount *ca_test2 = new CreditAccount(202, client2, 1.5, 200.0); 
    AbstractAccount *aa_ptr = ca_test2;
    ((Account*)aa_ptr)->Deposit(500); 
    ca_test2->Deposit(100); 
    delete aa_ptr; 
    delete client2;


    //GEO TEST

    IGeometricObject* geoObjects[2];

    geoObjects[0] = new Circle("Red", 5.0);
    geoObjects[1] = new Rectangle("Blue", 4.0, 6.0);

    for (int i = 0; i < 2; ++i) {
        if (geoObjects[i]) {
            cout << "\n--- Object " << i << " Info ---" << endl;
            geoObjects[i]->draw(); 
        }
    }

    for (int i = 0; i < 2; ++i) {
        delete geoObjects[i];
        geoObjects[i] = nullptr;
    }
    return 0;
}