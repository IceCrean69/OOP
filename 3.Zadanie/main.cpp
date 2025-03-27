#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

class Client
{
    private:
        int code;
        string name;
    public:
        Client(int c, string n): code(c), name(n) {};

        int GetCode()
        {
            return code;
        }
        string GetName()
        {
            return name;
        }

    
};
class Account{
    private:
        int number;
        double balance = 100;
        double interestRate;

        Client *owner;
        Client *partner;
    public:
        Account(int n, Client *c) : number(n), owner(c){};
        Account(int n, Client *c, double ir): number(n), owner(c), interestRate(ir){};
        Account(int n, Client *c, Client *p): number(n), owner(c), partner(p){};
        Account(int n, Client *c, Client *p, double ir): number(n), owner(c), partner(p), interestRate(ir){};

        int GetNumber()
        {
            return number;
        }
        double GetBalance()
        {
            return balance;
        }
        double GetInterestRate()
        {
            return interestRate;
        }
        Client *GetOwner()
        {
            return owner;
        }
        Client *GetPartner()
        {
            return partner;
        }
        bool CanWithdraw(double a)
        {
            return balance >= a ? true : false; 
        }

        void Deposit(double a)
        {
            balance += a;
        }
        bool Withdraw(double a)
        {
            if(balance >= a )
            {
                balance -= a;
                return true;
            }
            else
            {
                return false;
            }
        }
        void AddInterest()
        {
            balance  = balance * (1 + interestRate);
            return;
        }
};

class Bank{
    private:
        Client** clients;
        int clientsCount;
        
        Account** accounts;
        int accountsCount;
    public:
        Bank(int c, int a): clientsCount(0),accountsCount(0){};
        Bank() 
        {
            clients = new Client*[100];
            accounts = new Account*[100];
        }
        ~Bank();

        Client* GetClient(int c)
        {
            for (int i = 0; i < clientsCount; i++)
            {
                Client* j = clients[i];
                if(j->GetCode() == c)
                {
                    cout << j->GetName() << j->GetCode() << endl;
                    return j;
                }
            }
            cout << "Client not found" << endl;
            return NULL;
        };
        void GetAllClients()
        {
            if(clientsCount != 0){
                for (int i = 0; i < clientsCount - 1; i++)
                {
                    Client* j = clients[i];
                    cout << j->GetName() << j->GetCode() << endl;
                }
            }
            else
            {
                cout << "Client not found" << endl;
            }
            
        }
        Account* GetAccount(int n)
        {
            for (int i = 0; i < clientsCount; i++)
            {
                Account* j = accounts[i];
                if(j->GetNumber() == n)
                {
                    return j;
                }
            }
            cout << "account not found" << endl;
            return NULL;
        }
        void GetAllAccounts()
        {
            if(accountsCount != 0){
                for (int i = 0; i < accountsCount - 1; i++)
                {
                    Account* j = accounts[i];
                    cout <<"Owner: "<<j->GetOwner()->GetName() <<" "<<j->GetOwner()->GetCode() << endl;
                    cout <<"Partner: "<<j->GetPartner()->GetName()<<" " << j->GetPartner()->GetCode() << endl;
                    cout <<"Interest rate: " <<j->GetInterestRate() << endl;
                }
            }
            else
            {
                cout << "Client not found" << endl;
            }
        }

        Client* CreateClient(int c, string n)
        {
            Client* client = new Client(c, n);
            clients[clientsCount++] = client;
            return client;
        }
        Account* CreateAccount(int n, Client *c)
        {
            Account* account = new Account(n, c);
            accounts[accountsCount++] = account;
            return account;
        }
        Account* CreateAccount(int n, Client *c,double ir)
        {
            Account* account = new Account(n, c, ir);
            accounts[accountsCount++] = account;
            return account;
        }
        Account* CreateAccount(int n, Client *c, Client *p)
        {
            Account* account = new Account(n, c, p);
            accounts[accountsCount] = account;
            accountsCount += 1;
            return account;
        }
        Account* CreateAccount(int n, Client *c, Client *p, double ir)
        {
            Account* account = new Account(n, c, p, ir);
            accounts[accountsCount++] = account;
            return account;
        }

        void AddInterest()
        {
            for(int i = 0; i < accountsCount; i++)
            {
                Account* acc = accounts[i];
                acc->AddInterest();
            }
        }
};

int main(){
    ifstream file;
    Bank* bank = new Bank();
    ifstream fileNames ("name.txt");
    if(file)
    {
        string name;
        int code;
        while(fileNames >> name >> code)
        {
            cout << name << " " << code << endl;
            bank->CreateClient(code, name);
        }
    }
    ifstream fileAccounts("accounts.txt");
    if(file)
    {
        int number;
        int nameNum1;
        int nameNum2;
        double interestRate;

        while(fileAccounts >> number >> nameNum1 >> nameNum2 >> interestRate)
        {
            bank->CreateAccount(number, bank->GetClient(nameNum1), bank->GetClient(nameNum2), interestRate);
        }
    }
    else if(file)
    {
        int number;
        int nameNum1;

        while(fileAccounts >> number >> nameNum1)
        {
            bank->CreateAccount(number, bank->GetClient(nameNum1));
        }
    }
    else if(file)
    {
        int number;
        int nameNum1;
        int nameNum2;

        while(fileAccounts >> number >> nameNum1 >> nameNum2)
        {
            bank->CreateAccount(number, bank->GetClient(nameNum1), bank->GetClient(nameNum2));
        }
    }
    else if(file)
    {
        int number;
        int nameNum1;
        double interestRate;

        while(fileAccounts >> number >> nameNum1 >> interestRate)
        {
            bank->CreateAccount(number, bank->GetClient(nameNum1), interestRate);
        }
    }
    file.close();
    bank->GetAllAccounts();
    // Client* jakub = new Client(58, "jakub");
    // Account* acc1 = new Account(1, jakub);
    // Account* acc2 = new Account(2,jakub, 0.05);
    // acc2->AddInterest();
    // cout << acc1->GetBalance()<< endl;
    // cout << acc2->GetOwner()->GetName() << endl;
    return 0;
}