#include <iostream>
#include <cstring>
#include<map>
#include<cstdlib>
#include<cstdio>
#include<fstream>
#include<windows.h>
using namespace std;

map<string,bool>isMember;
map<string,int>searchBook;
map<string,int>UserID;

void loading();
int no_of_book=0;

class Book
{
protected:
  string Serial_no;
  int Shelf_no;
  string book_name;
  string Author;
  float price;
  string edition;
  int year_pub;
  string status;
public:

    //friend istream& operator>>(istream &,Book &);
//    friend ostream& operator<< (ostream &,Book &);
    //void display_dtls();
    void getInfo()
    {
        char eat;
        fstream in;
        if(no_of_book==1)
            in.open("BookInfo1.txt",ios::in);
            if(no_of_book==2)
                in.open("BookInfo2.txt",ios::in);
            if(no_of_book==3)
                in.open("BookInfo3.txt",ios::in);
                if(no_of_book==4)
                in.open("BookInfo4.txt",ios::in);
            getline(in,book_name);
            in>>Shelf_no;
            in>>eat;
            getline(in,Author);
            in>>price;
            in>>edition;
            in>>year_pub;
            in>>status;
            searchBook[book_name]=no_of_book;
            cout<<no_of_book<<"\n";
                in.close();
    }
    void DisplayInfo();
};
 /*istream & operator >>(istream& in,Book &b)
 {
     cout<<"Enter Serial no:";
     getline(in,b.Serial_no);
     cout<<"Enter Shelf no:";
     in>>b.Shelf_no;
     cout <<"Enter Book name:";
     getline(in,b.book_name);
     cout<<"Enter Author name:";
     getline(in,b.Author);
     cout<<"Enter Price:";
     in>>b.price;
     cout<<"Enter Edition:";
     in>>b.edition;
     cout<<"Enter year of publication:";
     in>>b.year_pub;
     cout<<"Enter book status:";
     in>>b.status;
     searchBook[b.book_name]=b.Shelf_no;
     return in;
 }*/
void Book::DisplayInfo()
 {

     cout<<"Serial no:"<<no_of_book<<endl;
     cout<<"Shelf no:"<<Shelf_no<<endl;
     cout<<"book name:"<<book_name<<endl;
     cout<<"Author:"<<Author<<endl;
     cout<<"price:"<<price<<endl;
     cout<<"edition:"<<edition<<endl;
     cout<<"year of publication:"<<year_pub<<endl;
     cout<<"Book Status:"<<status<<endl;
 }
 class Member_info
 {
 protected:
     string memberid;
     string sex;
     int no_books_issued;
     string Name;
     string department;
     string address;
     string mobile_no;
     string email;
     int max_book_issued;
     //string Fbaccount;
 public:
    void getinfo();
    void display_dtls();
    string getName(){return Name;};
    Member_info()
    {
        memberid="";
        sex="";
        Name="";
        department="";
        address="";
        mobile_no="";
        email="";
        no_books_issued=0;
        max_book_issued=3;
    }

 };
 void Member_info::getinfo()
 {
     cout <<"\n\tEnter member id:";
     cin>>memberid;
     isMember[memberid]=true;
     cout<< "\n\tEnter sex:";
     cin>>sex;
     cout <<"\n\tEnter Number of book issued:";
     cin>>no_books_issued;
     cout<<"\n\tMaximum nymber of book issued in a semester:3\n";
     cout<<"\n\tEnter Name:";
     fflush(stdin);
     getline(cin,Name);
     cout<<"\n\tEnter Department:";
     cin>>department;
     cout <<"\n\tPlease enter your mobile no:";
     cin>>mobile_no;
     cout<<"\n\tEnter your mail address:";
     cin>>email;

 }
 void Member_info::display_dtls()
 {
     cout <<"\n\t\tMember id:"<<memberid<<"\n";
     cout<< "\n\t\tSex:"<<sex<<"\n";
     cout <<"\n\t\tNumber of book issued:"<<no_books_issued<<"\n";
     cout<<"\n\t\tMaximum nymber of book issued in a semester:3\n";
     cout<<"\n\t\tName:"<<Name<< "\n";
     cout<<"\n\t\tDepartment:"<<department<< "\n";
     cout <<"\n\t\tMobile no:"<<mobile_no<< "\n";
     cout<<"\n\t\tMail address:"<<email<< "\n";
 }

 class Librarian:public Book,public Member_info
{
protected:
    int fine;
public:
    void check_id(string);
    void search_books(string);
    void issue_books();
    void return_books(int);
    void addNewUser();
    Librarian()
    {
        fine=0;

    }

} ;
void Librarian::addNewUser()
{
    Member_info NewUser;
    NewUser.getinfo();
}
void Librarian::search_books(string input)
{
    if(searchBook[input])
    {
        status="Available";
        cout<<"Book number:"<<searchBook[input]<<"\n";
    }
    else
    {
        status="Unavailable";
        cout<<"This book is not available right now!\n";

    }
}
void Librarian::issue_books()
{
    if(status=="Available")
        cout<<"This book is issued for you,return it before 30 days,or renew it!\n";
        else
            cout<<"This book is currently unavailable right now.please contact later\n";

}
void Librarian::return_books(int days)
{
    HANDLE txtcolor;
    txtcolor=GetStdHandle(STD_OUTPUT_HANDLE);
    if(days>30)
    {
        cout<<"You have used this book for more than 30 days.so u have to pay fine!\n";
    SetConsoleTextAttribute(txtcolor,4);
    fine=1*(days-30);  //Fine per day is 1 taka only!!
    cout<<"\nYOUR FINE IS:"<<fine<<"TAKA\n";
    SetConsoleTextAttribute(txtcolor,7);
    }
    else cout<<"You have successfully returned your book.THANK YOU!\n";
}
void Librarian::check_id(string input)
{
    if(isMember[input]==true)
        cout<<"Valid ID\n";
    else cout<<"Invalid ID,check your Member ID number\n";

}



int main()
{
    HANDLE txtcolor;
    txtcolor=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(txtcolor,7);

    int input=100,counts=0;



    Book NewBook[100];
    while(no_of_book<=4)
        NewBook[++no_of_book].getInfo();



    Librarian lib;
    Member_info user[100];
    do
    {

        if(input==1)
        {
            loading();

            int option;
        cout<<"Welcome to library management system.\n\n\t\t\tMenu\n\t\t1>>Add new user\n\t\t2>>check Member ID\n\t\t3>>Search Books\n\t\t4>>Issue Books\n\t\t5>>Return Books\n\n";
        cout<<"Enter your choice:";
        cin>>option;
        if(option==1)
            {
                user[++counts].getinfo();
                string temp=user[counts].getName();
                UserID[temp]=counts;
            }
        if(option==2)
            {
                string habijabi;
                cout<<"Enter ID name to check status:";
                cin>>habijabi;
                lib.check_id(habijabi);
            }
        if(option==3)
            {
                string habijabi;
                cout<<"Enter Book name to search:";
                fflush(stdin);
                getline(cin,habijabi);
                lib.search_books(habijabi);
            }
        if(option==4)
            lib.issue_books();
        if(option==5)
            {
                int daysAfterBookIssued;
                cout<<"Enter number of days passed after the book has been issued:";
                cin>>daysAfterBookIssued;
                lib.return_books(daysAfterBookIssued);
            }
        }
        if(input==2)
        {
            loading();
            int option;
            cout<<"Welcome to the information Zone!\n\n\t\t1>>Book information\n\t\t2>>Member information\n\n";
            cout<<"Enter your choice\n";
            cin>>option;
            if(option==1)
            {
                fflush(stdin);
                string findBook;
                cout<<"Search book by name:";
             getline(cin,findBook);
            int serial_of_books=searchBook[findBook];
            NewBook[serial_of_books].DisplayInfo();
            }
            if(option==2)
            {
                string UserName;
                cout<<"Enter User Name to see information:";
                fflush(stdin);
                getline(cin,UserName);
                int serial=UserID[UserName];
                user[serial].display_dtls();
            }
        }
        if(input!=100)
        {
            cout<<"\n\n\t\tThank you for using this software..\n";
        Sleep(700);
        system("cls");
        }
      if(input)
      {
        loading();
        cout<<"\n\n\t\t~~Main Menu~~\n\n\t\t1>>Library Management system\n\t\t2>>Information Zone\n\t\t3>>Exit\n\nEnter your choice:";
      }
    }
    while(cin>>input &&input!=3);
    return 0;
}



void loading()
{
    system("cls");
    cout<<"\n\n\t\tSystem is Loading";
        for(int i=1,j=1;i<10;i++)
        {
            if(j==5)
                break;
            cout<<".",Sleep(100);
            if(i==9)
                system("cls"),cout<<"\n\n\t\tSystem is Loading",i=0,j++;
        }
        system("cls");
}
