/*
	Computer Project: Library Management

     Soumya Khanna

     Class 12 - C

*/
#include<fstream.h>
#include<conio.h>
#include<string.h>
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<iomanip.h>

struct date
{
	int dd, mm, yy;
}cd;

class library
{
		public:
      		int acno;
                char subject[5], title[25], au[20], publisher[15];
                double price;
                int mcode;
                date doi;
                library()
                {mcode=0; doi.dd=doi.mm=doi.yy=0;}
 					 void libinput()
                {
                        cout<<"Accession Number: "; cin>>acno;
                        cout<<"Subject Code: "; gets(subject);
                        cout<<"Book Title: "; gets(title);
                        cout<<"Author: ";gets(au);
                        cout<<"Publisher: "; gets(publisher);
                        cout<<"Price: "; cin>>price;
                }
                void show_book()
		     {														cout<<"\nAccession no. : "<<acno;
			      cout<<"\nBook Name : ";puts(title);
				cout<<"Author Name : ";puts(au);
			}
			void modify_book()
			{
                  	cout<<"\nBook Accession no. : "<<acno;
                  	cout<<"\nModify Book Name : "; gets(title);
				cout<<"\nModify Author's Name of Book: "; 						gets(au);
			}
                void updatepr(double pr){price=pr;}
                double retprice(){return price;}
                char *rettitle(){return title;}
                int retmcode(){return mcode;}
                int retacno(){return acno;}

};
class member: public library
{
         char name[20], address[35], phone[9];
         int lim, nob;
            public:
                void maxlim()
                {
                        int ch=0;
                        while(ch!=1 || ch!=2 || ch!=3)
                      {

                            cout<<"MEMBERSHIP CARD DETAILS\n\n";
                            cout<<"1. GOLD\nMaximum Limit = 7\n";
                            cout<<"2. SILVER\nMaximum Limit = 5\n";
                            cout<<"3. REGULAR\nMaximum Limit = 3\n";
                            cout<<"Which membership card do you 							 want[1-3]? "; cin>>ch;
                            switch(ch)
                            {
                                       case 1:lim=7; break;
                                       case 2:lim=4; break;
                                       case 3:lim=3; break;
                                       default: cout<<"Sorry";
                            }
				}
       		}
                void memberinput()
                {
                        maxlim();
                        cout<<"PLEASE ENTER THE FOLLOWING DETAILS:\n";
                        cout<<"Member Name: "; gets(name);
                        cout<<"Member Address: "; gets(address);
                        cout<<"Phone Number: "; gets(phone);
                        cout<<"Books Issued: "; cin>>nob;
                        cout<<"CONGRATULATIONS, "<<name<<"! You have 					  finished registeration"<<endl;
                        mcode=random(1000);
                        cout<<"Your member code is "<<retmcode();
                }
                   void issueupdate()
                {
                        cout<<"Member Code: "; cin>>mcode;
                        cout<<"Date of Issue: "<<endl;
                        cout<<"Date : "; cin>>doi.dd;
                        cout<<"Month: "; cin>>doi.mm;
                        cout<<"Year: "; cin>>doi.yy;
                         nob++;
                }
                 void returnupdate()
                   {
                           mcode=0;
                          doi.dd=doi.mm=doi.yy=0;
                       	nob--;
                   }
                 void show_member()
			{
					cout<<"\nMember Code : "<<mcode;
					cout<<"\nMember Name : ";
					puts(name);
					cout<<"\nNo of Books issued : "<<nob;
			}

			void modify_member()
			{
					cout<<"\n Member Code  : "<<mcode;
                        	cout<<"\nModify Member Name: ";								gets(name);
                  }

                 void update2(char str[]){strcpy(address, str);}
                 void update3(char str[]){strcpy(phone, str);}
                 char *retname(){return name;}
                 char *retaddress(){return address;}
                 char *retphone(){return phone;}
                 int retlim(){return lim;}
                 int retnob(){return nob;}
};

void addreclib()
{
        ofstream fout("library.dat", ios::binary|ios::app);
        library a;
        int n;
        cout<<"No. of books to be added: "; cin>>n;
        for(int k=0; k<n; k++)
        {
                a.libinput();
                fout.write((char*)&a, sizeof(a));
        }
        fout.close();
}
void addrecmem()
{
        ofstream fout("member.dat", ios::binary|ios::app);
        member a;
        int n;
        cout<<"No. of books to be added        : "; cin>>n;
        for(int k=0; k<n; k++)
        {
                a.memberinput();
                fout.write((char*)&a, sizeof(a));
        }
        fout.close();
}
void price()
{
        ifstream fin("library.dat", ios::binary);
        ofstream fout("temp.dat", ios::binary);
        library a;
        int found=0;
        while(fin.read((char*)&a, sizeof(a)))
        {
                double pr;
                cout<<"Enter Updated Price  : "; cin>>pr;
                a.updatepr(pr);
                found=1;
                fout.write((char*)&a, sizeof(a));
        }
        fin.close();
        fout.close();
        remove("library.dat");
        rename("temp.dat", "library.dat");
        if(found==0)
                cout<<"Sorry wrong details! Please re-enter! ";

}

int searchcode()
{
        int code;
        cout<<"Input code  : "; cin>>code;
        ifstream fin("member.dat", ios::binary);
        member a;
        int found=0;
        while(fin.read((char*)&a,sizeof(a)))
                if(code==a.retmcode())
                        found=1;
        fin.close();
        return found;
}
int searchacno()
{
        ifstream fin("library.dat", ios::binary);
        library a;
        int found=0, l=0, c=0, acno;
        cout<<"Input Book's Accession Number  : "; cin>>acno;
        while(fin.read((char*)&a,sizeof(a)) && l>=0)
	  {
                c++;
                if(a.retacno()==acno)
                        found=1; l=-1;
        }
        fin.close();
        if(found==0)
                cout<<"Invalid Accession Number\n"; c=0;
        return c;
}
int searchbook()
{
        ifstream fin("library.dat", ios::binary);
        library a;
        int n=0;
        char book[25];
        cout<<"Enter the book name  : "; gets(book);
        while(fin.read((char*)&a,sizeof(a)))
                if(strcmpi(book, a.rettitle())==0 && a.retmcode()==0)
                         n=(fin.tellg())/(sizeof(a));
        fin.close();
        return n;
}
int dater(int x)
{
        int y=0;
           switch(x)
           {
               case 1: y=0; break;
               case 2: y=31; break;
               case 3: y=59; break;
               case 4: y=90; break;
               case 5: y=120;break;
               case 6: y=151; break;
               case 7: y=181; break;
               case 8: y=212; break;
               case 9: y=243; break;
               case 10:y=273; break;
               case 11:y=304; break;
               case 12:y=334; break;
               default: cout<<"Invalid Input\n\n\n\n"; break;
           }
           return y;
}
int numofdays(date dt)
{
           int ref,dd1,dd2,i;
           printf("Enter Today's Date [day, month, year]\n");
           scanf("%d%d%d",&cd.dd,&cd.mm,&cd.yy);
           ref=dt.yy;
           if(cd.yy<dt.yy)
                   ref=cd.yy;
           dd1=0;
           dd1=dater(dt.mm);
           for(i=ref;i<dt.yy;i++)
           {
               if(i%4==0)
               dd1+=1;
           }
           dd1+=dt.dd+(dt.yy-ref)*365;
           dd2=0;
           for(i=ref;i<cd.yy;i++)
           {
               if(i%4==0)
               dd2+=1;
           }
           dd2+=dater(cd.mm)+cd.dd+((cd.yy-ref)*365);
           int nod=abs(dd2-dd1);
        return nod;
}


void issue1()
{
        int f=searchcode();
        if(f==1)
        {
                int g=searchbook();
                if(g)
                {
                         ifstream fin("member.dat", ios::binary);
                        ofstream fout("temp.date", ios::binary);
                        member a;
                         int found=0;
                        fin.seekg((g-1)*sizeof(a));
                         while(fin.read((char*)&a, sizeof(a)))
                         {
                                if(a.retnob()<=a.retlim())
                                {
                                        a.issueupdate();
                                    found=1;
                                }
                                fout.write((char*)&a, sizeof(a));
                          }
                          fin.close();
                          fout.close();
                          remove("member.dat");
                          rename("temp.date", "member.dat");
                          if(found==0)
                                cout<<"Member has already issued upto MAX LIMIT\n";
              }
              else
                        cout<<"Book not present in the library\n";
        }
        else
                cout<<"Member code is INVALID\n";
}
void back()
{
        int acno;
        double fine;
        cout<<"Enter the book's accession number  : "; cin>>acno;
        ifstream fin("library.dat", ios::binary);
        member a;
        int found=0;
        while(fin.read((char*)&a,sizeof(a)))
                if(a.retacno()==acno)
                {
                        found=1;
                        int nod=numofdays(a.doi);
                        if(nod==0)
                                fine=0;
                        else
                        if(nod>0 && nod<=7)
                                fine=nod*0.5;
                        else
                        if(nod>7 && nod<=15)
                                fine=nod*1;
                        else
                        if(nod>15)
                                fine=nod*2;
                        if(nod>0)
                         {
                                cout<<"Member has to pay fine\n";
                                a.returnupdate();
                         }
                }
         fin.close();
         if(found==0)
                cout<<"ERROR"<<endl;
}
void modify_book()
{
	int n;  library b;
	int found=0;
	clrscr();
	cout<<"\n\n\tMODIFY BOOK REOCORD.... ";
	cout<<"\n\n\tEnter the accession code of the book";
	cin>>n;
   fstream fin;
	fin.open("library.dat",ios::in|ios::out| ios:: binary);
	while(fin.read((char*)&b,sizeof(b)) && found==0)
	{
		if(b.retacno()==n)
		{
			b.show_book();
			cout<<"\nEnter The New Details of book"<<endl;
			b.modify_book();
		    	fin.write((char*)&b,sizeof(b));
	    	cout<<"\n\n\t Record Updated";
		    	found=1;
		}
	}

    	fin.close();
    	if(found==0)
    		cout<<"\n\n Record Not Found ";
    	getch();
}
void modify_member()
{
	int n; member a;
	int found=0;
	clrscr();
	cout<<"\n\n\tMODIFY STUDENT RECORD... ";
	cout<<"\n\n\tEnter the member code";
	cin>>n;
   	fstream fin;
	fin.open("member.dat",ios::in|ios::out);
	while(fin.read((char*)&a,sizeof(a)) && found==0)
	{
		if(a.retacno()==n)
		{
			cout<<"\nEnter The New Details of member"<<endl;
			a.modify_member();
			fin.write((char*)&a,sizeof(a));
			cout<<"\n\n\t Record Updated";
			found=1;
		}
	}

	fin.close();
	if(found==0)
		cout<<"\n\n Record Not Found ";
	getch();
}
void deletebook()
{
			int found=0;
        ifstream fin("library.dat", ios::binary);
        ofstream fout("temp.dat", ios::binary);
        library a,b;
        cout<<"Enter book title to delete: "; cin>>b.rettitle();
        while(fin.read((char*)&a, sizeof(a)))
        {
        		if(stricmp(a.rettitle(),b.rettitle())!=0)
                fout.write((char*)&a, sizeof(a));
        }
        fin.close();
        fout.close();
        remove("library.dat");
        rename("temp.dat", "library.dat");
        if(found==0)
                cout<<"Sorry wrong details! Please re-enter! ";
}
void deletemember()
{
	   int found=0;
        ifstream fin("member.dat", ios::binary);
        ofstream fout("temp.dat", ios::binary);
        member a,b;
        cout<<"Enter member name to delete: "; cin>>b.retname();
        while(fin.read((char*)&a, sizeof(a)))
        {
        		if(stricmp(a.retname(),b.retname())!=0)
                fout.write((char*)&a, sizeof(a));
        }
        fin.close();
        fout.close();
        remove("member.dat");
        rename("temp.dat", "member.dat");
        if(found==0)
                cout<<"Sorry wrong details! Please re-enter! ";
}
void line()
{
	for(int i=1;i<41;i++)
          cout<<"--";
     cout<<"\n";
}
void star()
{
      for(int i=1;i<41;i++)
          cout<<"**";
      cout<<"\n";

}
void report1()
{
		ifstream fin("library.dat", ios::binary);
      	library b;
		cout<<"\n\n\n";
		cout<<setw(49)<<"BOOKS  TABLE\n";
		line();
		cout<<setw(25)<<"Title"<<setw(16)<<"Accession 					Number"<<setw(7)<<"Subject"<<setw(20)<<"Author"
		<<setw(15)<<"Publisher"<<setw(7)<<"Price\n";
		line();
		while(fin.read((char*)&b, sizeof(b)))
		{
				cout<<setw(25)<< 										b.rettitle()<<setw(16)<<b.retacno()
				<<setw(7)<<b.subject<<setw(20)<<b.au<<
				setw(15)<<b.publisher<<setw(7)<<b.price<<endl;
		}
		line();
      	fin.close();
		cout<<endl<<endl<<endl;
		star();
		cout<<setw(43)<<"Finish\n";
		star();
		getch();
}
void report2()
{
	ifstream fin("members.dat", ios::binary);
	member a;
      cout<<"\n\n\n";
	cout<<setw(49)<<"MEMBERS  TABLE\n";
	line();
	cout<<setw(20)<<"Name"<<setw(15)<<"Member 	Code"<<setw(35)<<"Address"
     <<setw(9)<<"Phone"<<setw(5)<<"Limit"<<setw(5)<<"NOB\n";
	line();
	while(fin.read((char*)&a, sizeof(a)))
	{
				cout<<setw(25)<<a.retname()<<setw(16)<<a.retmcode()<<setw(7)<<a.r	etaddress()<<setw(20)<<a.retphone()<<setw(15)<<a.retlim()<<setw(7	)<<a.retnob()<<endl;
	}
	line();
      fin.close();
	cout<<endl<<endl<<endl;
	star();
	cout<<setw(43)<<"Finish\n";
	star();
	getch();
}
void get_option()
{
      	int opt, b1, m1, t1, r1,s1;
		cout<<"\t \t MAIN MENU: \t \t \n";
		cout<<"1. Books \n 2. Members \n 3. Transactions \n 4. 			Search \n 5. Reports 0. Exit \n";
      	cout<<"Input your option: ";
      	cin>>opt;
      	do
      	 switch(opt)
            {
        		   case 1:	cout<<"1. Add a book \n 2. Delete a book 					\n";
                		cout<<"3. Modify a book \n 0. Back to Main Menu 					\n";
         		   cout<<"Enter your option";
         			cin>>b1;
                      switch(b1)
                      {
                           		case 1 : addreclib(); break;
                                 case 2 : deletebook();break;
                                 case 3 : modify_book(); break;
                                 default: get_option(); break;
                       }
                       break;
             	 case 2:  cout<<" 1. Add a member \n 2. Remove a 						member \n";
                   	cout<<"3. Modify a member \n 0. Back to Main Menu 				\n";
                       cout<<"Enter your option";
                 	cin>>m1;
                      switch(m1)
                      {
                           		case 1 : addrecmem();  break;
                                 case 2 : deletemember(); break;
                                 case 3 : modify_member(); break;
                                 default: get_option(); break;
                      }
                      break;
			case 3:  cout<<" 1. Issue \n 2. Return \n 0. Back to 				Main Menu \n";
           	cout<<"Enter your option";
                	cin>>t1;
			switch(t1)
                 {
                          	case 1 : issue1() ;break;
                            case 2 : back();break;
                            default: get_option(); break;                           			}
                 break;
                 case 4: cout<<"1. Search using member code \n 2. 				Search using Accession Code \n";         						cout<<"3. Search using title \n 0. Back to main menu 				\n";
                 cout<<"Enter your option: ";
                 cin>>s1;
                 switch(s1)
                 {
                   		case 1 : searchcode();break;
                           case 2 : searchacno();break;
                           case 3 : searchbook();break;
                           default: get_option(); break;                                   			}
                 break;
                case 5: cout<<"1. List of books \n 2.List of members				 \n 0. Back to Main Menu";
           	cout<<"Enter your option";
                	cin>>r1;
                	switch(r1)
                	{
                			case 1 : report1(); break;
                     		case 2 : report2();  break;
                     		default: get_option(); break;             				}
                	break;
            }
       while(opt);
}
void main()
{
		 library b;
		 member a;
            get_option();
            getch();
}


/*OUTPUT
--------------

MAIN MENU:
1. Books
 2. Members
 3. Transactions
 4. Search
 5. Reports 0. Exit
Input your option: 1
 1. Add a book
 2. Delete a book
0. Back to Main Menu
Enter your option1
No. of books to be added        : 2
Accession Number        : 234
Subject Code     : 345
Book Title              : science
Author                     : ratna sagar
Publisher               : oxford
Price                : 230
Accession Number        : 234
Subject Code     : 122
Book Title              : maths
Author                     : rd sharma
Publisher               : sagar
Price                : 220

MAIN MENU:
1. Books
 2. Members
 3. Transactions
 4. Search
 5. Reports 0. Exit
Input your option: 2
 1. Add a member
 2. Remove a member
0. Back to Main Menu
Enter your option1
No. of books to be added        : 2
MEMBERSHIP CARD DETAILS

1. GOLD
Maximum Limit = 7
2. SILVER
Maximum Limit = 5
3. REGULAR
Maximum Limit = 3
Which membership card do you want[1-3]? 1
                 MAIN MENU:
1. Books
 2. Members
 3. Transactions
 4. Search
 5. Reports 0. Exit
Input your option: 1
1. Add a book
 2. Delete a book
3. Modify a book
 0. Back to Main Menu
Enter your option 1
No. of books to be added        : 2
Accession Number        : 123
Subject Code     : 45
Book Title              : The Story of my Life
Author                     : Soumya Khanna
Publisher               : Madhurima Dutta
Price                : 675
Accession Number        : 345
Subject Code     : 35
Book Title              : Confessions of a K-drama girl
Author                     : Madhurima Dutta
Publisher               : Soumya Khanna
Price                : 523
1. Add a book
 2. Delete a book
3. Modify a book
 0. Back to Main Menu
Enter your option 0
                 MAIN MENU:
1. Books
 2. Members
 3. Transactions
 4. Search
 5. Reports 0. Exit
Input your option:  2
 1. Add a member
 2. Remove a member
3. Modify a member
 0. Back to Main Menu

 */
