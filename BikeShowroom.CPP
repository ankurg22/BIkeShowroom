#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<ctype.h>
#include<string>
#include<stdlib.h>
 class bikes
{ char delmark;
  int bcode;
  char brand[20];
  char bname[20];
  char dom[10];
  char color[10];
  char eng[10];
  char brakes[10];
  int mileage;
  int avgspeed;
  int qoh;
  float exprice;
  float orprice;
  public:
 void del(char ch);
 char retdelmark();
 void input();
 void display();
 void search();
 void searchbname();
 void searchbcode();
 int retbcode();
 char* retbname();
 char* retbrand();
 int calcorprice();
 int retqoh();
 void getqoh(int);
};

/*______________functions____________*/
void bp2();
void bikes :: getqoh(int a)
	{
	qoh=a;
	}
void bikes :: del(char ch)
	{
	delmark=ch;
	}
int bikes :: retbcode()
	{
	return bcode;
	}
char* bikes :: retbname()
	{
	return bname;
	}
char* bikes :: retbrand()
	{
	return brand;
	}

char bikes :: retdelmark()
	{
	return delmark;
	}
int bikes :: calcorprice()
	{
	orprice= (0.12*exprice)+ exprice+ 2000;
	return orprice;
	}
int bikes :: retqoh()
	{
	return qoh;
	}
/*________________INPUT/OUTPUT______________*/

void bikes::input()
{  delmark=' ';
  cout<<"Enter Bike Code                : ";
   cin>>bcode;
   cout<<"\nEnter Brand    	        : ";
   gets(brand);
   cout<<"\nEnter Name             	: ";
   gets(bname);
   cout<<"\nEnter Date of Manufacture   : ";
   gets(dom);
   cout<<"\nEnter Color 	        : ";
   gets(color);
   cout<<"\nEnter Engine 	        : ";
   gets(eng);
   cout<<"\nEnter Brakes 	        : ";
   gets(brakes);
   cout<<"\nEnter Mileage	        : ";
   cin>>mileage;
   cout<<"\nEnter Average Speed	        : ";
   cin>>avgspeed;
   cout<<"\nEnter Quantity	        : ";
   cin>>qoh;
   cout<<"\nEnter Ex-Showroom Price 	: ";
   cin>>exprice;
 }



void writedata()
	{
	ofstream ofile("bikes.dat",ios::binary|ios::app);
		if(!ofile)
			{
			cout<<"File not found... :-p.!!";
			getch();
			return;
			}
	char ans;
	bikes ob;

	do{
		ob.input();
		ofile.write((char*)&ob,sizeof(ob));
		cout<<"Enter More...?(Y/N)";
		cin>>ans;
		ans=toupper(ans);

	  }while(ans!='N');
	ofile.close();
	}

void bikes::display()
{

	cout<<"* Bike Code                   : "<<bcode<<endl;
	cout<<"* Brand name                  : "<<brand<<endl;
	cout<<"* Model name                  : "<<bname<<endl;
	cout<<"* Date of manufacture.        : "<<dom<<endl;
	cout<<"* Color Available             : "<<color<<endl;
	cout<<"* Engine (in cc)              : "<<eng<<endl;
	cout<<"* Brake type                  : "<<brakes<<endl;
	cout<<"* Mileage (in kmpl)           : "<<mileage<<endl;
	cout<<"* Average Speed (in kmp)      : "<<avgspeed<<endl;
	cout<<"* Quantity                    : "<<qoh<<endl;
	cout<<"* Ex-Showroom Price (in Rs.)  : "<<exprice<<endl;
	cout<<"* On Road Price (in Rs.)      : ";calcorprice();cout<<orprice<<endl;
	cout<<"\nNOTE- On road price includes 12% road tax and Rs.2000 Service charge";
 getch();
 clrscr();
}


/*_____________________SEARCH___________________*/


void bikes:: searchbname()
 {
	 char a[10];
	 int g=0;
	  ifstream ifile("bikes.dat",ios::binary);
	  if(!ifile)
  {
      cout<<"file not found"<<endl;return;
  }
	 bikes ob;
	 cout<<"Enter Bike name you want to search : "<<endl;
	 gets(a);
      while(ifile.read((char*)&ob,sizeof(ob)))
  {
      if(strcmpi(ob.retbname(),a)==0)
   {
      ob.display();
      cout<<endl;
      g=1;
   }
  }
       if(g==0)
      {
       cout<<"No match found";
       getch();
       return;
      }
}

void bikes ::searchbcode()
{	int dn,g=0;
	ifstream ifile("bikes.dat",ios::binary);
	if(!ifile)

	{
	cout<<"File not found";getch();return;
	}
	bikes ob;
		 cout<<"Enter number you want to search : "<<endl;
		 cin>>dn;

	  while(ifile.read((char*)&ob,sizeof(ob)))
  {
		 if(ob.retbcode()==dn)
		 {
		  ob.display();

		   g=1;
		  }
  }
    if(g==0)
    {
     cout<<"No match found";
     getch();
     return;
    }
}




void readundeleted()
	{
	ifstream ifile("bikes.dat",ios::binary);
		if(!ifile)
			{
			cout<<"File not found";
			}
	bikes ob;
	while(ifile.read((char*)&ob,sizeof(ob)))
		{
		if(ob.retdelmark()!='*')
		ob.display();
		}
	ifile.close();
	}
void readdeleted()
	{
	ifstream ifile("bikes.dat",ios::binary);
		if(!ifile)
		{
		 cout<<"File not found";
		}
 bikes ob;
	while(ifile.read((char*)&ob,sizeof(ob)))
	{
	if(ob.retdelmark()=='*')
	ob.display();
	}
 ifile.close();
}


void pack()
	{
	 bikes ob;
	ifstream ifile("bikes.dat",ios::binary);
		if(!ifile)
		{
		cout<<"error";
		getch();
		return;
		}
	ofstream ofile("temp.dat",ios::binary);
		if(!ofile)
		{
		return;
		}
	 while (ifile.read((char*)&ob,sizeof(ob)))
	 {
		if(ob.retdelmark()!='*')
		{
		ofile.write((char*)&ob,sizeof(ob));
		}
	 }
 ifile.close();
 ofile.close();
 remove("bikes.dat");
 rename("temp.dat","bikes.dat");
 }


void undelete()
{
    fstream ifile("bikes.dat", ios::in | ios::out | ios::binary | ios::ate);
    if(!ifile)
	   {
	     cout<<"error";
	     getch();
	     return;
	   }
    bikes ob;
    ifile.seekg(0,ios::beg);
	int dno;
	int f=0;
	char ans;
	char l;
    cout<<"Enter number you want to undelete?";
    cin>>dno;
	 while(ifile.read((char*)&ob,sizeof(ob)))
		{
		if(dno==ob.retbcode() && ob.retdelmark()=='*')
		{
		ob.display();
		f=1;
			cout<<"Do you want to undelete...?(Y/N)";
			cin>>ans;
			  ans=toupper(ans);
			if(ans=='Y')
			{l=' ';
			ob.del(l);
		int c=-1*sizeof(ob);
		ifile.seekg(c,ios::cur);
		ifile.write((char*)&ob,sizeof(ob));
		}break;
		}

	ifile.close();
	}
	if(f==0)
	cout<<"not found";
}

void deleterecord()
	{
	fstream ifile("bikes.dat", ios::in | ios::out | ios::binary | ios::ate);
	bikes ob;
	ifile.seekg(0,ios::beg);
	int dno;
	int f=0;
	char ans;
	char l;
	cout<<"Enter Bike code you want to delete : ";
	cin>>dno;
   while(ifile.read((char*)&ob,sizeof(ob)))
	{
	    if(dno==ob.retbcode() && ob.retdelmark()!='*')
		{
		ob.display();
		f=1;
		cout<<"Do you want to delete?(Y/N) ";
		cin>>ans;
		ans=toupper(ans);
			if(ans=='Y')
				{
				l='*';
				ob.del(l);
				int c=-1*sizeof(ob);
				ifile.seekg(c,ios::cur);
				ifile.write((char*)&ob,sizeof(ob));
				break;
				}
		}
	}
		ifile.close();
		if(f==0)
		{
		cout<<"Not Found!";}
		}


void modify()
{
	fstream ifile("bikes.dat",ios::in|ios::out|ios::binary|ios::ate);
	int f,no;
	char ans;
	bikes ob;
		cout<<"Enter bike code : "<<endl;
		cin>>no;
		ifile.seekg(0,ios::beg);
		while(ifile.read((char*)&ob,sizeof(ob)))
		{
		if(no==ob.retbcode()&&ob.retdelmark()!='*')
		{
		ob.display();
		f=1;
			cout<<"Do you want to change?(Y/N) : ";
			cin>>ans;
			ans=toupper(ans);
			if(ans=='Y')
			{
			ob.input();
		int c=-1*sizeof(ob);
		ifile.seekg(c,ios::cur);
		ifile.write((char*)&ob,sizeof(ob));
	}break;
	}
	}
    ifile.close();
    if(f==0)
      cout<<"Not found";
}
void  search ()
{ int k;
  bikes ob;
do
  {
    clrscr();
 cout<<"--------SEARCH MENU---------"<<endl;
 cout<<"1. Search via bike code "<<endl;
 cout<<"2. Search via bike name "<<endl;
 cout<<"3. Exit"<<endl;
 cout<<" ENTER YOUR CHOICE : "<<endl;
 cin>>k;
 switch(k)
 {
  case 1  :{ ob.searchbcode();
	     getch();
	     break;
	   }
  case 2  :{ ob.searchbname();
	     getch();
	     break;
	   }
  case 3  :{
	     break;
	   }
  default :{ cout<<"Wrong Choice ";
	     getch();
	     break;
	   }
 }

   }while(k!=3);
}



void maintain()
	{int x;
	clrscr();
		do{
		cout<<"1.Input"<<endl;
		cout<<"2.Delete"<<endl;
		cout<<"3.Display Deleted"<<endl;
		cout<<"4.Undelete"<<endl;
		cout<<"5.Modify"<<endl;
		cout<<"6.Pack"<<endl;
		cout<<"7.Exit"<<endl;
		cout<<"Enter Your Choice : ";
		cin>>x;

		switch(x)
			{
			case 1 :	{
					writedata();
					break;
					}
			case 2:		{
					deleterecord();
					getch();
					break;
					}
			case 3:         {
					readdeleted();
					getch();
					break;
					}
			case 4:		{
					undelete();
					getch();
					break;
					}
			case 5:		{
					modify();
					getch();
					break;
					}
			case 6:		{
					pack();
					getch();
					break;
					}
			case 7:		{
					break;
					}
			default:	{
					cout<<"Wrong Choice!!";
					getch();
					break;
					}
			}
		}while(x!=7);
	}




/*_____________________MAIN_____________________*/
int main()
{
	clrscr();
	int p;
   do
 {
  clrscr();
	cout<<"--------MENU--------"<<endl;
	cout<<"1.  Display All"<<endl;
	cout<<"2.  Search"<<endl;
	cout<<"3.  Buy"<<endl;
	cout<<"4.  Exit"<<endl;
	cout<<"ENTER CHOICE"<<endl;
  cin>>p;

 switch(p)
{
 case 1 :{
	   readundeleted();
	   getch();
	   break;
	 }

 case 2 :{
	   search();
	   getch();
	   break;
	 }


 case 3 : {
	   bp2();
	   getch();
	   break;
	  }

 case 4 : {
	   break;
	  }
 case 1234 : {
	      maintain();
	      getch();
	      break;
	      }
 default:{
	   cout<<"Wrong Choice";
	   getch();
	   break;
	 }
 }
 } while(p!=4);
 }


class sales
{
 int invno;
 char invdt[25];
 char qty;
 int price;
 public:

 void getinvdt();
 void getinvno(int);

 int retqty();
 void getprice(int);

};

int sales::retqty()
	{
	return qty;
	}

void sales::getprice(int x)
	{
	price=x;
	}

void sales::getinvdt()
	{
	gets(invdt);
	}

void sales::getinvno(int d)
	{

	invno=d;
	}


void buy()
	{  sales os;
	bikes ob;
	ofstream ofile("sales.dat",ios::binary|ios::app);
		if(!ofile)
			{
			cout<<"File not found... :-p.!!";
			getch();
			return;
			}
	 int inv =ofile.tellp()/sizeof(os);
	 inv++;
       fstream ff("bikes.dat",ios::binary|ios::ate|ios::in|ios::out);
		if(!ff)
			{
			cout<<"File not found... :-p.!!";
			getch();
			return;
			}
		char ans;
		ff.seekg(0,ios::beg);
		int b,q;
		cout<<"Bike code of the bike you want to buy : ";
		cin>>b;
	   int f =0;
	   while(ff.read( (char*)&ob,sizeof(ob)))
	   {

	   if(b==ob.retbcode())
	    {
		  ob.display();
		  f=1;
		  cout<<"Enter qauntity : ";
		  cin>>q;
		  if(ob.retqoh()< q)
		     {
		     cout<<"Not sufficient quantity available";
		     getch();
		     ff.close();
		     ofile.close();
		     return;
		     }
		  cout<<"CONFIRM ORDER (Y/N) : ";
		  cin>>ans;
		  ans=toupper(ans);
		  if(ans=='Y')
			{

			int e= ob.retqoh()-q;
			ob.getqoh(e);
			os.getinvno(inv);
			cout<<"Invoice Number is : "<<inv<<endl;
			cout<<"Enter date : ";
			os.getinvdt();
			int f=os.retqty() * ob.calcorprice();
			os.getprice(f);
			cout<<"Total Amount : "<<f<<endl;
			ofile.write((char*) & os,sizeof(os));
			int c=-1*sizeof(ob);
			ff.seekp(c,ios::cur);
			ff.write((char*) & ob,sizeof(ob));
			 }
		   else
			{
			cout<<"You cancelled your order.";
			return;
			}
		}
	     }
		 if(f == 0 )
		  {
			cout<<"Your bike code did not match.";
			getch();
			return;
		  }

		ofile.close();
		ff.close();
	}




//___________MAIN FUNCTION_____________

void bp2()
{
  int a;
  sales os;

  do {
   clrscr();
	 cout<<"1. Buy a bike "<<endl;
	 cout<<"2. Exit "<<endl;
	 cout<<"ENTER YOUR CHIOICE : ";
     cin>>a;

  switch(a)
	{
	   case 1 :{ buy();
		     getch();
		     break;
		   }
	   case 2 :{
		     break;
		   }
	   default:{
		     cout<<"Wrong choice...!!";
		     getch();
		     break;
		   }
	}

     }while(a!=2);
}





