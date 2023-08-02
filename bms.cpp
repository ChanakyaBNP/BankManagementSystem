#include<iostream>
#include<stdio.h>
#include<iomanip>
#include<fstream>
#include<cctype>
using namespace std;

class Bank_Account{
    int account_number;
    char name[50];
    char type;
    int money_deposit;

public:
    void report() const;
    int retacno() const{
        return account_number;
    }
    void dep(int x){
        money_deposit+=x;
    }
    void draw(int x)
    {
        money_deposit-=x;
    }
    int retdeposit() const
    {
       return money_deposit;
    }
    void modify();
    void create_account();
    void Display_account();    
    
};

//All the functions

void write_account();  //the function for create account
void display_details(int); //the function for Blance Enquiry
void delete_account(int);  //the function for delete account
void display_all(); //the function for all account holder list
void updation_bank_account(int); //the function for update bank details
void money_deposit_withdraw(int,int); //the function for money deposit and withdraw 

void Bank_Account ::modify(){
    cout<<"Account Number : "<<account_number<<endl;
    cout<<"Modify account holder name : "<<endl;
    cin.ignore();
    cin.getline(name,50);
    cout<<"Modify account type : "<<endl;
    cin>>type;
    type=toupper(type);
    cout<<"modify balance acount :"<<endl;
    cin>>money_deposit;

}
//the function for showing all the element in a report display all account holder list 
void Bank_Account::report() const{
    cout<<account_number<<setw(10)<<"  "<<name<<setw(10)<<"    "<<type<<setw(6)<<"  "<<money_deposit<<endl;
}

//the function for showing during create account section 
void Bank_Account::create_account()
{
    system("cls");
    cout<<"Enter the account number: ";
    cin>>account_number;
    cout<<"Enter the name of account holder: ";
    cin.ignore();
    cin.getline(name,50);
    cout<<"Enter the type of the account (C/S): ";
    cin>>type;
    type=toupper(type);
    cout<<"Enter the initial amount (>=1000 for Saving Account Holder and >=500 for Current Account): ";
    cin>>money_deposit;
    cout<<endl;
    cout<<"Account created....... :)";
    cout<<endl;
}

//the function for showing during balance enquiry section
void Bank_Account::Display_account()
{
    cout<<"Account Number: "<<account_number<<endl;
    cout<<"Account holder name: "<<name<<endl;
    cout<<"Account type: "<<type<<endl;
    cout<<"Balance amount: "<<money_deposit<<endl;
}


int main()
{  
    char ch;
    int num;
    do
    {
    cout<<"------------------------------------------------------"<<endl;
    cout<<"---------|Welcome to Bank Management System|----------"<<endl;
    cout<<"------------------------------------------------------"<<endl;

    cout<<endl;
    cout<<" ----Main Menu----"<<endl; 
    cout<<"1. Create Account"<<endl;
    cout<<"2. Deposit Money"<<endl;
    cout<<"3. Withdraw Money"<<endl;
    cout<<"4. Balance Enquery"<<endl;
    cout<<"5. All Account Holder List"<<endl;
    cout<<"6. Close an Account"<<endl;
    cout<<"7. Modify an Account"<<endl;
    cout<<"8. Exit"<<endl;
    cout<<endl;

    cout<<"Enter your choice (1-8) : ";
    cin>>ch;

    switch(ch)
    {
    //create account    
    case '1':
        write_account();
        break;
    //Deposit money
    case '2':
        system("cls");
        cout<<"Enter the account no : ";
        cin>>num;
        money_deposit_withdraw(num,1);
        break;
    //Withdraw money
    case '3':
        system("cls");
        cout<<"Enter the account no : ";
        cin>>num;
        money_deposit_withdraw(num,2);
        break;
    //Balance enquiry
    case '4':
        system("cls");
        cout<<"Enter the account no : ";
        cin>>num;
        display_details(num);
        break;
    //all account holder list
    case '5':
        display_all();
        break;
    //close an account
    case '6':
        system("cls");
        cout<<"Enter the account no : ";
        cin>>num;
        delete_account(num);
        break;
    //Modify an account
    case '7':
        system("cls");
        cout<<"Enter the account no : ";
        cin>>num;
        updation_bank_account(num);
        break;   
    //exit
    case '8':
        cout<<"Thank you for using Bank Management System";
        break;             
    }

    cin.ignore();
    cin.get();
    }

    while(ch!='8');
    return 0;

     
    // Bank_Account B;
    // B.create_account();
    // cout<<endl;
    // B.Display_account();
    // return 0;
}


void write_account()
{
    Bank_Account ac;
    ofstream outFile;
    outFile.open("account.dat",ios::binary|ios::app);
    ac.create_account();
    outFile.write(reinterpret_cast<char *>(&ac),sizeof(Bank_Account));
    outFile.close();
}

void delete_account(int n)
{
    Bank_Account ac;
    ifstream inFile;
    ofstream outFile;
    inFile.open("account.dat",ios::binary);
    if (!inFile)
    {
        cout<<"File could not be open || press any key...";
        return;
    }
    outFile.open("Temp.dat",ios::binary);
    inFile.seekg(0,ios::beg);
    while (inFile.read(reinterpret_cast<char *>(&ac),sizeof(Bank_Account)))
    {
        if(ac.retacno()!=n)
        {
          outFile.write(reinterpret_cast<char *>(&ac),sizeof(Bank_Account));
        }
    }
    inFile.close();
    outFile.close();
    remove("Bank_Account.dat");
    rename("Temp.dat","Bank_Acount.dat");
    cout<<"Record Deleted......."<<endl;
    
}

void display_details(int n)
{
    Bank_Account ac;
    bool flag=false;
    ifstream inFile;
    inFile.open("account.dat",ios::binary);
    if(!inFile)
    {
        cout<<"File could not be open || press any key...";
        return;
    }
    cout<<"Bank Account Details"<<endl;
    while (inFile.read(reinterpret_cast<char *>(&ac),sizeof(Bank_Account)))
    {
        if(ac.retacno()==n)
        {
            ac.Display_account();
            flag=true;
        }
    }
    inFile.close();
    if(flag==false)
    {
        cout<<"Account no does not exit"<<endl;
    }

}

void display_all()
{
    system("cls");
    Bank_Account ac;
    ifstream inFile;
    inFile.open("account.dat",ios::binary);
    if(!inFile)
    {
        cout<<"File could not be open || press any key...";
        return;
    }
    cout<<"Bank account holder list "<<endl;
    cout<<"=============================================================================="<<endl;
    cout<<"A/c No                  Name                  Type               Balance"<<endl;
    cout<<"=============================================================================="<<endl;
    while (inFile.read(reinterpret_cast<char *>(&ac),sizeof(Bank_Account)))
    {
        ac.report();
    }
    inFile.close();
}

void money_deposit_withdraw(int n, int option)
{
    int amt;
    bool found =false;
    Bank_Account ac;
    fstream File;
    File.open("account.dat",ios::binary|ios::in|ios::out);
    if(!File)
    {
        cout<<"File could not be open || press any key...";
        return;
    }
    while (!File.eof() && found==false)
    {
       File.read(reinterpret_cast<char *>(&ac),sizeof(Bank_Account));
       if(ac.retacno()==n)
       {
        ac.Display_account();
        if(option==1)
        {
            cout<<"Enter the amount of money to be deposit : ";
            cin>>amt;
            ac.dep(amt);
        }
        if(option==2)
        {
            cout<<"Enter the amount to be withdraw : ";
            cin>>amt;
            int balance = ac.retdeposit()-amt;
            if(balance<0)
            {
                cout<<"Insufficient balance"<<endl;
            }
            else{
                ac.draw(amt);
            }
        }
        int pos =(-1)*static_cast<int>(sizeof(Bank_Account));
        File.seekp(pos,ios::cur); //move the position to the position of the file
        File.write(reinterpret_cast<char *>(&ac),sizeof(Bank_Account)); //write the record in the file
        found=true;
       }
    }
    File.close();
     if(found==false)
        {
            cout<<"Record Not Found...."<<endl;
        }
    
}

void updation_bank_account(int n)
{
    bool found=false;
    Bank_Account ac;
    fstream File;
    File.open("account.dat",ios::binary|ios::in|ios::out); //open the file in binary number
    if(!File)
    {
        cout<<"File could not be open || press any key...";
        return;
    }
    while (!File.eof() && found==false)
    {
        File.read(reinterpret_cast<char *>(&ac),sizeof(Bank_Account)); //read the record from the file
         if(ac.retacno()==n)
         {
            ac.Display_account();
            cout<<"enter the new details of the account"<<endl;
            ac.modify();
            int pos =(-1)*static_cast<int>(sizeof(Bank_Account));
            File.seekp(pos,ios::cur); //move the position to the position of the file
            File.write(reinterpret_cast<char *>(&ac),sizeof(Bank_Account)); //write the record in the file
            cout<<"record updated"<<endl;
            found=true;
         }
    }
    File.close();
     if(found==false)
        {
            cout<<"Record Not Found...."<<endl;
        }

}