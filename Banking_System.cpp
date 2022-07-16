#include<iostream>
#include<vector>
#include<map>
#include<iterator>
#include<fstream>
#include<utility>

using namespace std;


class Account{
    private:
        int acn;
        string fname;
        string lname;
        int acBalance;

    public:

        static int accountN;
        Account(){}
        Account(string fn,string nn,int intialBal=0){
            this->acBalance=intialBal;
            this->acn=accountN++;
            this->fname=fn;
            this->lname=nn;
        }
        string GetFname(){return this->fname;}
        string Getlname(){return this->lname;}
        int GetBal(){ return this->acBalance;}
        int GetAcn(){return this->acn;}
        void WithDraw(int amount);
        void Deposite(int amount);
        void static SetLastAccNum(int accn){accountN=accn;}
        static int GetLastAccNum(){return accountN;}

        friend ifstream & operator>>(ifstream &ifile,Account & ac);
        friend ofstream & operator<<(ofstream &ofile,Account & ac);
        friend ostream & operator<<(ostream &oc, Account &ac);

        ~Account(){}
};
int Account::accountN=1;

class Bank
{
    private:
        map<int,Account> accounts;
       
    public:
        Bank();
        void OpenAccount();
        void CloseAccount();
        void CheckBalance();
        void PrintAllAccounts();
        void Deposite();
        void WithDraw();

        ~Bank();

};

int main()
{
    Bank b;

    int choice;
    do{

        cout<<"$$$WELCOME TO VIRTUAL BANK$$$"<<endl;
        cout<<"Enter 1: for Opening a new account"<<endl;
        cout<<"Enter 2: for Closing an Existing account"<<endl;
        cout<<"Enter 3: for Checking Balance"<<endl;
        cout<<"Enter 4: for Deposite Money"<<endl;
        cout<<"Enter 5: for Withdraw Money"<<endl;
        cout<<"Enter 6: for See all account"<<endl;
        cout<<"Enter any other key to exit"<<endl;
        cin>>choice;
        switch(choice)
        {

            case 1:
                b.OpenAccount();
                break;
            case 2:
                b.CloseAccount();break;
            case 3:
                b.CheckBalance();
                break;
            case 4:
                b.Deposite();break;
            case 5:
                b.WithDraw();
                break;
            case 6:
                b.PrintAllAccounts();
                break;
            
            default:
                exit(0);

        }

    }while(choice!=7);

    return 0;
}


Bank::~Bank()
{
    map<int,Account>::iterator it;

    ofstream opFile;
    opFile.open("Bank_data.txt",ios::trunc);
    for(it=accounts.begin();it!=accounts.end();it++)
    {
        opFile<<it->second;       
    }

    opFile.close();

}

void Bank::WithDraw()
{
    cout<<"Please Enter the Account Number: "<<endl;
    int amt,acn;cin>>acn;
    cout<<"Please Enter the amount You Want to WithDarw: "<<endl;
    
    cin>>amt;

    accounts.find(acn)->second.WithDraw(amt);
    cout<<"You Have successfully Withdraw the amount"<<amt<<" Your Current Balance: "<<accounts.find(acn)->second.GetBal()<<endl;


}

void Bank::Deposite()
{
    cout<<"Please Enter the Account Number: "<<endl;
    int amt,acn;cin>>acn;
    cout<<"Please Enter the amount You Want to Deposite: "<<endl;
    
    cin>>amt;

    accounts.find(acn)->second.Deposite(amt);
    cout<<"You Have successfully Deposited the amount"<<amt<<" Your Current Balance: "<<accounts.find(acn)->second.GetBal()<<endl;


}

void Bank::PrintAllAccounts()
{
    map<int,Account>::iterator it;
    if(accounts.empty()){
        cout<<"No account is there"<<endl;
        return;
    }
    it=accounts.begin();
    for(it;it!=accounts.end();it++)
    {
        cout<<(it->second)<<endl;
    }
}

void Bank::CheckBalance()
{
    cout<<"Please Enter your Account Number: "<<endl;int acn;cin>>acn;
    cout<<"Your Account Balance is "<<accounts.find(acn)->second.GetBal()<<endl;
}


void Bank::CloseAccount()
{
    cout<<"Please Enter your Account Number: "<<endl; int acn;cin>>acn;
    if(accounts.empty()||accounts.find(acn)==accounts.end()){
        cout<<"No Account Exist"<<endl;
        return;
    }
    accounts.erase(accounts.find(acn));
    cout<<"Your Account Successfully Closed"<<endl;
}

 void Bank::OpenAccount()
{
    cout<<"Please Enter your First name: "<<endl;string fname,lname;cin>>fname;
    cout<<"Pleae Enter your Last name: "<<endl;cin>>lname;int b;
    cout<<"Enter the minimum Balace: "<<endl;cin>>b;

    Account A(fname,lname,b);
    accounts.insert({A.GetAcn(),A});
    cout<<"Congratulation! You have successfully Open an account your details below"<<endl;
    cout<<A<<endl;

    ofstream WriteFile;
    WriteFile.open("Bank_data.txt",ios::trunc);
    
    map<int,Account>::iterator it;
    
    for(it=accounts.begin();it!=accounts.end();it++)
    {
        WriteFile<<it->second;
    }
    WriteFile.close();
}

Bank::Bank()
{
    ifstream ipFile;
    ipFile.open("Bank_data.txt");

    if(!ipFile)return;

    Account A;
    while(!ipFile.eof())
    {
        ipFile>>A;
        accounts.insert(pair<int,Account>{A.GetAcn(),A});
    }
    
    Account::SetLastAccNum(A.GetLastAccNum());

    ipFile.close();
}

ofstream & operator<<(ofstream &rfile,Account &acc)
{
    rfile<<acc.fname<<endl;
    rfile<<acc.lname<<endl;
    rfile<<acc.acn<<endl;
    rfile<<acc.acBalance<<endl;
    return rfile;
}

ifstream & operator>>(ifstream &ifile,Account &acc)
{
    ifile>>acc.fname;
    ifile>>acc.lname;
    ifile>>acc.acn;
    ifile>>acc.acBalance;

    return ifile;
}

ostream & operator<<(ostream &Ofile, Account &acc)
{
    Ofile<<"Name: "<<acc.GetFname()<<" "<<acc.Getlname()<<endl;
    Ofile<<"Account Number: "<<acc.GetAcn()<<endl;
    Ofile<<"Current Balance: "<<acc.GetBal()<<endl;
    return Ofile;
    
}

void Account::WithDraw(int amt)
{
    if(amt>this->GetBal()){
        cout<<"Not enough Balance"<<endl;
        return;
    }
    this->acBalance-=amt;
}
void Account::Deposite(int amt)
{
    this->acBalance+=amt;
    cout<<amt<<" being Deposited to your account"<<endl;
    return;
}