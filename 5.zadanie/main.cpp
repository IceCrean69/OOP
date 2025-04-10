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
        static int clientsCount;
        Client(int c, string n)
        {
            this->code = c;
            this->name = n;
            Client::clientsCount += 1;
        }
        ~Client()
        {
            clientsCount--;
        }
        int GetCode()
        {
            return code;
        }
        string GetName()
        {
            return name;
        }
        static int GetClientCount()
        {
            return clientsCount;
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
        static int accountsCount;
        Account(int n, Client *c)
        {
            this->number = n;
            this->owner = c;
            accountsCount++;
        };
        Account(int n, Client *c, double ir)
        {
            this->number = n;
            this->owner = c;
            this->interestRate = ir;
            accountsCount++;
        };
        Account(int n, Client *c, Client *p)
        {
            this->number = n;
            this->owner = c;
            this->partner = p;
            accountsCount++;
        };
        Account(int n, Client *c, Client *p, double ir)
        {
            this->number = n;
            this->owner = c;
            this->partner = p;
            this->interestRate = ir;
            accountsCount++;
        };
        ~Account()
        {
            accountsCount--;
        }
        static int GetAccountsCount()
        {
            return accountsCount;
        }
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
        void ChangeInterest(Account* acc, int num)
        {
            acc->interestRate = num;
            return;
        }
};

class PartnerAccount: public Account
{
    private:
        Client* partner;
    public:
        PartnerAccount(int n, Client *o, Client *p): Account(n, o)
        {
            this->partner = p;
        }
        PartnerAccount(int n, Client *o, Client *p, int ir): Account(n,p,ir)
        {
            this->partner = p;
        }
};

class Bank{
    private:
        Client** clients;
        
        Account** accounts;
    public:
        Bank(int c, int a){};
        Bank() 
        {
            clients = new Client*[100];
            accounts = new Account*[100];
        }
        ~Bank()
        {
            for (int i = 0; i < GetTotalClients(); i++)
            {
                delete clients[i];
            }
            delete[] clients;

            for (int i = 0; i < GetTotalAccounts(); i++)
            {
                delete accounts[i];
            }
            delete[] accounts;

        }

        Client* GetClient(int c)
        {
            for (int i = 0; i < GetTotalClients(); i++)
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
            if(GetTotalClients() != 0){
                for (int i = 0; i < GetTotalClients() - 1; i++)
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
            for (int i = 0; i < GetTotalClients(); i++)
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
            if(GetTotalAccounts() != 0){
                for (int i = 0; i < GetTotalAccounts() - 1; i++)
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
            clients[GetTotalClients()] = client;
            return client;
        }
        Account* CreateAccount(int n, Client *c)
        {
            Account* account = new Account(n, c);
            accounts[GetTotalAccounts()] = account;
            return account;
        }
        Account* CreateAccount(int n, Client *c,double ir)
        {
            Account* account = new Account(n, c, ir);
            accounts[GetTotalAccounts()] = account;
            return account;
        }
        Account* CreateAccount(int n, Client *c, Client *p)
        {
            Account* account = new Account(n, c, p);
            accounts[GetTotalAccounts()] = account;
            return account;
        }
        Account* CreateAccount(int n, Client *c, Client *p, double ir)
        {
            Account* account = new Account(n, c, p, ir);
            accounts[GetTotalAccounts()] = account;
            return account;
        }

        void AddInterest()
        {
            for(int i = 0; i < GetTotalAccounts(); i++)
            {
                Account* acc = accounts[i];
                acc->AddInterest();
            }
        }

        int GetTotalAccounts() const
        {
            return Account:: accountsCount;
        }
        int GetTotalClients() const
        {
            return Client:: clientsCount;
        }
};
int Account::accountsCount = 0;
int Client::clientsCount = 0;
int main(){
    // ifstream file;
    // Bank* bank = new Bank();
    // ifstream fileNames ("name.txt");
    // while(fileAccounts >> number >> nameNum1 >> nameNum2 >> interestRate)
    // {   
    //     if(nameNum2 != 0 && nameNum1 != 0 && interestRate != 0)
    //     {
    //         bank->CreateAccount(number, bank->GetClient(nameNum1), bank->GetClient(nameNum2), interestRate);
    //     }
    //     else if(nameNum1 != 0 && nameNum2 != 0 && interestRate == 0)
    //     {
    //         bank->CreateAccount(number, bank->GetClient(nameNum1), bank->GetClient(nameNum2));
    //     }
    //     else if(nameNum1 != 0 && nameNum2 == 0 && interestRate == 0)
    //     {
    //         bank->CreateAccount(number, bank->GetClient(nameNum1));
    //     }
    //     else if(nameNum1 != 0 && nameNum2 == 0 && interestRate !=0)
    //     {
    //         bank->CreateAccount(number, bank->GetClient(nameNum1), interestRate);
    //     }
    //     else
    //     {
    //         cout << "Invalid input" << endl;
    //     }
    // }
    // file.close();
    // bank->GetAllAccounts();
    // Bank* bank = new Bank();
    // Client* jakub = new Client(58, "jakub");
    // Account* acc  = new Account(1,jakub);
    // cout << acc->GetInterestRate() << endl;
    // acc->ChangeInterest(acc, 15);
    // cout << acc->GetInterestRate() << endl;
    // cout << Client::GetClientCount() << endl;
    // delete bank;
    // delete jakub;
    // cout << "num of accounts : "<< Client::GetClientCount() << endl;

    PartnerAccount* pa;
    Account *c;

    pa = new PartnerAccount (2, new Client(1,"Jakub"), new Client(2,"Jakub"));
    c = pa;
    cout << c->GetOwner()->GetName() << c->GetInterestRate() << endl;

    return 0;
}