#include <fstream.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <iomanip.h>
#include <process.h>
#include <conio.h>
#include <math.h>
#include <time.h>
#include<windows.h>

void border(char ch,int x,int y,int l,int b)
/*(x,y) is the top left corner point and l and b are the length and breadth of the rectangle*/
{
	int p,q,r,s;
	for(p=x;p<x+l;p++)
	{
		gotoxy(p,y);
		cout<<ch;
	}
	for(q=y,--p;q<y+b;q++)
	{
		gotoxy(p,q);
		cout<<ch;
	}
	for(r=x+l-1,--q;r>=x;r--)
	{
		gotoxy(r,q);
		cout<<ch;
	}
	for(s=y+b-1;s>=y;s--)
	{
		gotoxy(x,s);
		cout<<ch;
	}
}

void error_mssg(char mssg[],int x=27)
{
	clrscr();
	border('#',15,10,50,7);
	gotoxy(x,12);
	cout<<mssg;
	gotoxy(36,15);
	cout<<"Press any key to continue..";
	getch();
}

char create_menu(char* list_opt[],int no_of_elements)
{
	clrscr();
	border('#',1,1,81,24);
	gotoxy(41-strlen(list_opt[0])/2,3);
	cout<<list_opt[0];

	int step=6;
	for(int i=1; i<no_of_elements; ++i)
	{
		if(i%2==1)
			{
				border('+',11,step,25,5);
				gotoxy(13,step+2);
				cout<<list_opt[i];
			}
		if(i%2==0)
			{
				border('+',46,step,25,5);
				gotoxy(48,step+2);
				cout<<list_opt[i];
				step+=5;
			}
	}

	gotoxy(39,22);
	cout<<"___";
	gotoxy(34,23);
	cout<<"Press backspace to return to previous screen.";

	gotoxy(40,22);
	char opt=getch();
	return opt;
}

void create_list(char* list_elements[], int no_of_elements, int y_start, float no_of_columns=1)
{
	int longest_element=1;
	for(int i=0; i<no_of_elements; ++i)
		if(longest_element<strlen(list_elements[i]))
			longest_element=strlen(list_elements[i]);

	int y=y_start;
	i = 0;
	for(int h=1; h<=no_of_columns; ++h)
	{
		int y=y_start;
		for(; i<(no_of_elements/no_of_columns)*h; ++i)
		{
			gotoxy(((81/no_of_columns-longest_element)/2)/*centers the list in the column*/+(h-1)*(81/no_of_columns)/*shifts the column*/,y++);
			cout<<list_elements[i];
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////
class User
{
	private:
	
	char username[30];
	char password[30];
	int initial_run;
	
	public:
	
	char* ret_user()
	{
		return username;
	}
	
	char* ret_pass()
	{
		return password; 
	}
	
	int ret_ir()
	{
		return initial_run;
	}
	
	void initial_login(char*);
	
	User :: User()
	{
		initial_run=1;
	}
}U;

class contacts
{
	private:
			char name[20],addline_1[20],addline_2[20],email_id[30];
			char ph_no[10],mob_no[10],encrypted_text[30],decrypted_text[30];
	public:
			void file_edit();
			void input();    //get contacts details by input
			void display();
			void menu();
			void view();
			void createnew();
			void edit(char temp[]);
			void search();
			void deletecontact(char tmp[]);
			void sort();
			void clrdsp();
			void charfix(char temp[],char letter,int mode);
			void encrypt(char temp[]);
			void decrypt(char temp[]);
}c,f;
//////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////login starts/////////////////////////////////////////////
char* getpass(char* keyword="nor")
{
	void login(char*);

	char pass[30];
	for(int i=0;i<30;i++)
	{
		pass[i]=getch();
		
		if(i>=1 && pass[i]==8)
		{
			--i;
			gotoxy(40+i,14);
			cout<<' ';
			gotoxy(40+i,14);
			continue;
		}
		
		if(strcmp(keyword,"ini")==0)
			if(!(pass[i]>96&&pass[i]<123 || pass[i]>64&&pass[i]<91 || pass[i]>32&&pass[i]<43 || pass[i]==13))
			{
				error_mssg("Use characters A-Z, a-z, ! \" # $ % & ' ( ) *",17);
				U.initial_login("pass");
			}
		
		if(pass[i]==13)
		{
			pass[i]='\0';
			break;
		}
		
		cout<<'*';	
	}
	return pass;
}

void User :: initial_login(char* keyword="user")
{
	ofstream fout;
	fout.open("dduser.dat",ios::out|ios::binary);
	
	if(strcmp(keyword,"user")==0)
		goto enter_username;
	else if(strcmp(keyword,"pass")==0)
		goto wrong_password_entered;
	/////////////////////////////////////////////////////////
	
	enter_username:
	
	char temp_user[30];
	
	clrscr();
	border('~',20,8,40,5);
	gotoxy(21,14);
	cout<<"Username should be less than 30 char";
	gotoxy(30,10);
	cout<<"Username: ";
	gets(temp_user);
	
	if(strlen(temp_user)<30)
		strcpy(username,temp_user);
	else
		goto enter_username;
	/////////////////////////////////////////////////////////
	
	enter_password:
	
	border('~',20,12,40,5);
	gotoxy(18,18);
	cout<<"Use characters A-Z, a-z, ! \" # $ % & ' ( ) *";
	gotoxy(21,14);
	cout<<"         Password:                    ";
	gotoxy(40,14);
	strcpy(password,getpass("ini"));
	
	initial_run=0;
	
	fout.seekp(0,ios::beg);
	fout.write((char*)&U,sizeof(User));
	fout.close();
	return;
	////////////////////////////////////////////////////////
	
	wrong_password_entered:
	
	clrscr();
	border('~',20,8,40,5);
	gotoxy(30,10);
	cout<<"Username: ";
	cout<<username;
	goto enter_password;
}

void login(char* keyword="user")
{
	ifstream fin;
	fin.open("dduser.dat",ios::in|ios::binary);
	
	if(!fin)
	{
		U.initial_login();
		return;
	}
	
	fin.seekg(0,ios::beg);
	fin.read((char*)&U,sizeof(User));
		
	if(U.ret_ir()==0)
	{
		char uname[30],pass[30];
		int bool=0;

		if(strcmp(keyword,"user")==0)
			goto enter_username;
		else if(strcmp(keyword,"pass")==0)
			goto wrong_password_entered;

		enter_username:

		clrscr();
		border('~',20,8,40,5);
		gotoxy(30,10);
		cout<<"Username: ";
		gets(uname);

		if(strcmp(uname,U.ret_user())==0)
			bool=1;

		if(bool==0)
		{
			error_mssg("Username is incorrect",29);
			goto enter_username;
		}
		//////////////////////////////////////////////////////////////////////////

		enter_password:

		bool=0;

		border('~',20,12,40,5);
		gotoxy(30,14);
		cout<<"Password:                    ";
		gotoxy(40,14);
		strcpy(pass,getpass());

		if(strcmp(pass,U.ret_pass())==0)
		{
			bool=1;
			return;
		}

		if(bool==0)
		{
			error_mssg("Password is incorrect",29);
			goto wrong_password_entered;
		}
		///////////////////////////////////////////////////////////////////////////

		wrong_password_entered:

		clrscr();
		border('~',20,8,40,5);
		gotoxy(30,10);
		cout<<"Username: ";
		cout<<U.ret_user();
		goto enter_password;
	}
}
//////////////////////////////////////login ends//////////////////////////////////////////////
/////////////////////////////////////menu starts//////////////////////////////////////////////
void menu()
{
	void world_clock();
	void converter();
	void snake();
	contacts c;

	char* main_menu[]={"Digital Diary","1. Contacts","2. Calc. & Conv.","3. World Clock","4. Notes","5. Horoscope","6. Games"};
	char option=create_menu(main_menu,sizeof(main_menu)/4);

	switch(option)
	{
		case '1':	c.menu();
				break;
		case '2':	converter();
				break;
		case '3':	world_clock();
				break;
		case '4':	cout<<"notes";
				break;
		case '6':	snake();
				break;
		case 8	:	login();
		default:	error_mssg("Invalid option!",32);
				menu();
	}
}
/////////////////////////////////////menu ends////////////////////////////////////////////////
////////////////////////////////////contacts starts///////////////////////////////////////////

void contacts :: clrdsp()
{
gotoxy(38,8);cout<<"                                    ";
gotoxy(38,9);cout<<"                                    ";
gotoxy(38,10);cout<<"                                    ";
gotoxy(38,11);cout<<"                                    ";
gotoxy(38,12);cout<<"                                    ";
gotoxy(38,13);cout<<"                                    ";
}
void contacts :: encrypt(char temp[])
{
char ekeyl[]="gi*dhwp(k{}?|^y$x#fv'%q!ua@. ICFEUSWRVD";
char ekeyu[]="coenXmZ&):<>+][_`jlorz~s-=@.";
char dkeyl[]="abcdefghijklmnopqrstuvwxyz@. 0123456789";
char dkeyu[]="ABCDEFGHIJKLMNOPQRSTUVWXYZ@.";

char output[100];
//gets(temp);
int l=strlen(temp);
for(int i=0;i<=l-1;i++)
{
con:
for(int j=0;j<=39;j++)
{

//cout<<i<<dkeyl[j]<<"."<<temp[i]<<endl<<output<<endl;          //debug info
if(temp[i]==dkeyl[j])
{
//cout<<"here1";                                                //debug info
output[i]=ekeyl[j];
i++;
if(i!=l)
goto con;
else goto exit;
}
if(dkeyu[j]==temp[i])
{
//cout<<"here2";                                                //debug info
output[i]=ekeyu[j];
i++;
if(i!=l)
goto con;
else goto exit;
}
}
}
exit:
output[i]='\0';
//cout<<endl<<output;                                           //debug info
strcpy(encrypted_text,output);
}

void contacts :: decrypt(char temp[])
{
char ekeyl[]="gi*dhwp(k{}?|^y$x#fv'%q!ua@. ICFEUSWRVD";
char ekeyu[]="coenXmZ&):<>+][_`jlorz~s-=@.";
char dkeyl[]="abcdefghijklmnopqrstuvwxyz@. 0123456789";
char dkeyu[]="ABCDEFGHIJKLMNOPQRSTUVWXYZ@.";

char output[100];
//gets(temp);
int l=strlen(temp);
for(int i=0;i<=l-1;i++)
{
con:
for(int j=0;j<=39;j++)
{

//cout<<i<<dkeyl[j]<<"."<<temp[i]<<endl<<output<<endl;          //debug info
if(temp[i]==ekeyl[j])
{
//cout<<"here1";                                                //debug info
output[i]=dkeyl[j];
i++;
if(i!=l)
goto con;
else goto exit;
}
if(ekeyu[j]==temp[i])
{
//cout<<"here2";                                                //debug info
output[i]=dkeyu[j];
i++;
if(i!=l)
goto con;
else goto exit;
}
}
}
exit:
output[i]='\0';
//cout<<endl<<output;                                           //debug info
strcpy(decrypted_text,output);
}

void contacts :: file_edit()
{
int n,i=0;
cout<<"Enter number of contacts:";
cin>>n;
ofstream file;
file.open("contacts.cf",ios::binary||ios::out);
while(i<n)
{
c.input();
file.write((char*)&c,sizeof(c));i++;
}
file.close();

char a;
again:
cout<<"Do You Want to View Contacts:(Y/N)";
a=getchar();
if(a=='Y'||a=='y')
view();
else if(a=='N'||a=='n')
goto exit;
else
{
cout<<"Invalid input, Enter again";
goto again;}
exit:
}

void contacts :: deletecontact(char tmp[])
{
ifstream file;
ofstream temp;
int fail=1;
temp.open("$$.cf",ios::binary);
file.open("contacts.cf",ios::binary);
while(file.read((char*)&c,sizeof(c)))
{
decrypt(name);
if(!(strcmpi(decrypted_text,tmp)==0))
{
temp.write((char*)&c,sizeof(c));
continue;
}
fail=0;
}
temp.close();
file.close();
remove("contacts.cf");
rename("$$.cf","contacts.cf");
gotoxy(38,8);
if(fail==0)
cout<<"Contact Deleted";
if(fail!=0)
cout<<"ERROR 2";
gotoxy(38,9);
cout<<"Hit Enter to continue.....";
char c=getch();
if(c==13)
{
clrscr();
menu();
}
}

void contacts :: display()
{
gotoxy(51,8);cout<<"                         ";
gotoxy(40,9);cout<<"                         ";
gotoxy(41,10);cout<<"                         ";
gotoxy(41,11);cout<<"                         ";
gotoxy(41,12);cout<<"                         ";
gotoxy(41,13);cout<<"                         ";
gotoxy(38,8);
cout<<"Contact Name:";
decrypt(name);puts(decrypted_text);
gotoxy(38,9);
cout<<"Phone no:";
cout<<ph_no<<endl;
gotoxy(38,10);
cout<<"Mobile no:";
puts(mob_no);
gotoxy(38,11);
cout<<"Email id:";
decrypt(email_id);puts(decrypted_text);
gotoxy(38,12);
cout<<"Address (line 1):";
decrypt(addline_1);puts(decrypted_text);
gotoxy(38,13);
cout<<"Address (line 2):";
decrypt(addline_2);puts(decrypted_text);
}
void contacts :: charfix(char temp[],char letter,int mode)
{
int l=strlen(temp);
//temp[l]='o';                //just increasing the array size by 1
memmove(temp+1,temp,l);     //move all characters +1 unit to the right
temp[0]=letter;             //now replace 1st letter
temp[l+1]='\0';
if(mode==1)
strcpy(name,temp);
else if (mode==2)
strcpy(ph_no,temp);
else if (mode==3)
strcpy(mob_no,temp);
else if (mode==4)
strcpy(email_id,temp);
else if (mode==5)
strcpy(addline_1,temp);
else if (mode==6)
strcpy(addline_2,temp);
}
void contacts :: input()    //get contacts details by input
{
char a;
gotoxy(38,8);
cout<<"Contact Name:";
a=getche();
if(a==13)goto next0;
else
gets(name);charfix(name,a,1);encrypt(name);strcpy(name,encrypted_text);
next0:
gotoxy(38,9);
cout<<"Phone no:";
a=getche();
if(a==13)goto next1;
else
gets(ph_no);charfix(ph_no,a,2);
next1:
gotoxy(38,10);
cout<<"Mobile no:";
a=getche();
if(a==13)goto next2;
else
gets(mob_no);charfix(mob_no,a,3);
next2:
gotoxy(38,11);
cout<<"Email id:";
a=getche();
if(a==13)goto next3;
else
gets(email_id);charfix(email_id,a,4);encrypt(email_id);strcpy(email_id,encrypted_text);
next3:
gotoxy(38,12);
cout<<"Address (line 1):";
a=getche();
if(a==13)goto next4;
else
gets(addline_1);charfix(addline_1,a,5);encrypt(addline_1);strcpy(addline_1,encrypted_text);
next4:
gotoxy(38,13);
cout<<"Address (line 2):";
a=getche();
if(a==13)goto next5;
else
gets(addline_2);charfix(addline_2,a,6);encrypt(addline_2);strcpy(addline_2,encrypted_text);
next5:
}

void contacts :: edit(char tmpp[])
{
fstream fio;
ofstream fout;
fout.open("contacts.cf",ios::out||ios::binary);
int recc=0;
fio.open("contacts.cf",ios::out||ios::in||ios::binary);
char name1[20];
strcpy(name1,tmpp);

while(fio.read((char*)&c,sizeof(c)))   //testing if we can still read
{

if(strcmp(name,name1)==0)              //check name
{
input();
fout.seekp(recc*sizeof(c),ios::beg);
fout.write((char*)&c,sizeof(c));
fout.close();
break;
}gotoxy(1,1);
recc++;
}
fio.close();
c.menu();
}

void contacts:: view()
{
ifstream file;
file.open("contacts.cf",ios::binary);
file.seekg(0,ios::beg);
while(file.read((char*)&c,sizeof(c)))
{c.display();cout<<endl;}
file.close();
}


void contacts::createnew()
{

ifstream file;
ofstream temp;
temp.open("$$.cf",ios::binary);
file.open("contacts.cf",ios::binary);
while(file.read((char*)&c,sizeof(c)))
temp.write((char*)&c,sizeof(c));
c.input();
temp.write((char*)&c,sizeof(c));
temp.close();
file.close();
remove("contacts.cf");
rename("$$.cf","contacts.cf");
clrscr();
menu();
}
/*
void contacts :: sort()
{
ifstream file;
ofstream temp;
char name1[20],name2[20],contact[100],sort[100];
int i=0,j,k;
temp.open("$$.cf",ios::binary);
file.open("contacts.cf",ios::binary);
while(file.read((char*)&c,sizeof(c)))
{contact[i]=name;i++;}
for(j=0;j<=i;j++)
{
	for(k=0;k<=i;k++)
	{
	if(strcmp(contact[i],contact[j])<0)
	char tmp[]=contact[i];
	contact[i]=contact[j];
	strcpy(contact[j],tmp);
	}
}
}*/

void contacts :: search()
{
char tmp[20];
cout<<"Enter Contact's Name:";
gets(tmp);
ifstream file;
file.open("contacts.cf",ios::binary);
while(file.read((char*)&c,sizeof(c)))
{
decrypt(name);
if(strcmpi(decrypted_text,tmp)==0)
display();
}
file.close();
}

void contacts :: menu()
{
gotoxy(0,24);
cout<<"Use W & D keys to scroll through contacts";
cout<<endl<<"Hit Enter to select contact";
gotoxy(38,17);
cout<<"              ";
gotoxy(38,18);
cout<<"              ";
gotoxy(55,17);
cout<<"              ";
gotoxy(55,18);
cout<<"              ";
gotoxy(30,1);
cout<<" __   __         _____        __  _____  ___ "<<endl;
gotoxy(30,2);
cout<<"|    |  |  |\\  |   |    /\\   |      |   |__  "<<endl;
//gotoxy(30,3);
//cout<<"|    |  |  | \\ |   |   /__\\   |      |      | "<<endl;
gotoxy(30,3);
cout<<"|__  |__|  |  \\|   |   /  \\  |__    |   ___| "<<endl;
ifstream file;
file.open("contacts.cf",ios::binary);
cout<<endl<<endl;
int n=0;
cout<<"Contacts List:"<<endl;
cout<<"+Add New+"<<endl;;
while(file.read((char*)&c,sizeof(c)))
{
n++;
decrypt(name);
cout<<decrypted_text<<endl;
}

file.close();
ifstream file1;
file1.open("contacts.cf",ios::binary);
int y=8,x=20,recc=0;
gotoxy(x,y);
cout<<"<--";
file1.read((char*)&c,sizeof(c));
c.display();
n--;
loop:
char a=getch();
if(a=='w'&&y==8)
{
clrdsp();
gotoxy(x,y);
cout<<"   ";y--;
gotoxy(x,y);
cout<<"<--";
}
if(a=='s'&&y<(n+8))
{
gotoxy(x,y);
cout<<"   ";y++;
gotoxy(x,y);
cout<<"<--";
if(y>8)
{file1.read((char*)&c,sizeof(c));recc++;}
c.display();
}
if(a=='w'&&y>(n-5)&&y!=7)
{
gotoxy(x,y);
cout<<"   ";y--;
gotoxy(x,y);
cout<<"<--";
file1.seekg(((recc*sizeof(c))-sizeof(c)),ios::beg);
file1.read((char*)&c,sizeof(c));
c.display();
recc--;
}
if(a==13&&y!=7)
goto enterkey;
if(a==13&&y==7)
{
createnew();
}

goto loop;
enterkey:
gotoxy(0,24);
cout<<"Use A & S keys to choose option";
cout<<endl<<"Hit Enter to select option. Press B to go back";
gotoxy(10,y);
cout<<"   ";
int y1=18,x1=38;
gotoxy(38,y1-1);
cout<<"Edit Contact";
gotoxy(55,y1-1);
cout<<"Delete Contact";
gotoxy(x1,y1);
cout<<"************";
loop2:
char b=getch();
if(b=='d')
{x1=55;
gotoxy(38,y1);
cout<<"               ";
gotoxy(55,y1);
cout<<"               ";
gotoxy(x1,y1);
cout<<"***************";
}
if(b=='a')
{x1=38;
gotoxy(38,y1);
cout<<"               ";
gotoxy(55,y1);
cout<<"               ";
gotoxy(x1,y1);
cout<<"************";
}
if(b==13&&x1==38)
{
//clrdsp();
file1.close();
gotoxy(38,8);
edit(name);
}
if(b==13&&x1==55)
{
clrdsp();
file1.close();
decrypt(name);
char name2[20];
strcpy(name2,decrypted_text);
deletecontact(name2);
}
if(b=='b'||b=='B')
{
clrscr();
menu();
}

goto loop2;

}
///////////////////////////////////contacts ends//////////////////////////////////////////////
/////////////////////////////////////converter starts/////////////////////////////////////////

double convert(char enter_unit[], double enter_amt, char* valid_units[], int no_of_units, double mltip_values[])
{
	for(int i=0; i<no_of_units; ++i)   //If the strcmp is used here it terminates the loop
		if(strcmpi(enter_unit,valid_units[i])==0)
		{
			double ret_amt=enter_amt*mltip_values[i];
			return ret_amt;

		}
	return 0;   //Prevents crashes in case of invalid units
}

void converter_ui(char* header,char* unit="Unit")
{
	clrscr();
	border('#',1,1,81,24);
	gotoxy(34,4);
	cout<<header;

	border('.',10,6,25,5);
	gotoxy(12,7);
	cout<<unit<<": ___";
	gotoxy(12,9);
	cout<<"Amount: ______________";

	gotoxy(39,8);
	cout<<"TO";

	border('.',45,6,25,5);
	gotoxy(47,7);
	cout<<unit<<": ___";
	gotoxy(47,9);
	cout<<"Amount: ______________";
}

void converter()
{
	void currency();
	void unit();
	void calc();

	char* converter_menu[]={"Calc. & Conv.","1. Currency","2. Unit","3. Calculator"};
	char option=create_menu(converter_menu,sizeof(converter_menu)/4);
	
	switch(option)
	{
		case '1':	currency();
				break;
		case '2':	unit();
				break;
		case '3':	calc();
				break;
		case 8	:	menu();
				break;
		default :	error_mssg("Invalid option!");
				converter();
	}
}

/////////////////////////////////////////////////
void currency()
{
	char* currencies[]={"American Dollar	USD","Bahraini Dinar		BHD","Euro			EUR","Indian Rupee	INR","Japanese Yen	YEN","Saudi Riyal	SAR"};
	char* currency_units[]={"BHD","INR","SAR","EUR","YEN","USD"};
	double to_usd[]={2.65,0.016,0.27,1.14,0.0088,1};
	double from_usd[]={0.375,64.46,3.75,0.88,112.98,1};
		
	converter_ui("Currency Converter","Currency");

	create_list(currencies,sizeof(currencies)/4,13,2);
	
	gotoxy(22,7);
	char in_cur[4];
	gets(in_cur);
	if(strcmpi(in_cur,"BHD")&&strcmpi(in_cur,"USD")&&strcmpi(in_cur,"INR")&&strcmpi(in_cur,"YEN")&&strcmpi(in_cur,"SAR")&&strcmpi(in_cur,"EUR"))	//checks if entered currency is valid
	{
		error_mssg("Invalid currency!",31);
		currency();
	}
	gotoxy(20,9);
	double in_amt;
	cin>>in_amt;
		
	double temp_amt=convert(in_cur,in_amt,currency_units,sizeof(currency_units)/4,to_usd);
	
	gotoxy(57,7);
	char out_cur[4];
	gets(out_cur);
	if(strcmpi(out_cur,"BHD")&&strcmpi(out_cur,"USD")&&strcmpi(out_cur,"INR")&&strcmpi(out_cur,"YEN")&&strcmpi(out_cur,"SAR")&&strcmpi(out_cur,"EUR"))	//checks if entered currency is valid
	{
		error_mssg("Invalid currency!",31);
		currency();
	}
	
	double out_amt=convert(out_cur,temp_amt,currency_units,sizeof(currency_units)/4,from_usd);
	
	gotoxy(55,9);
	cout<<out_amt;

	gotoxy(50,23);
	cout<<"Press Backspace to go back..";
	gotoxy(10,23);
	cout<<"Press Enter to use again..";
	char temp=getch();
	if(temp==13)
		currency();
	if(temp==8)
		converter();
}
/////////////////////////////////////////////////
void unit()
{
	void mass();
	void length();
	void area();
	void volume();
	
	char* unit_menu[]={"Unit Converter","1. Mass","2. Length","3. Area","4. Volume"};
	char option=create_menu(unit_menu,sizeof(unit_menu)/4);

	switch(option)
	{
		case '1':	mass();
				break;
		case '2':	length();
				break;
		case '3':	area();
				break;
		case '4':	volume();
				break;
		case 8	:	converter();
		default	:	error_mssg("Invalid option!",32);
				unit();
	}
}

void mass()
{
	char* masses[]={"Tonne		t","Kilogram	kg","Gram		g","Milligram	mg","Microgram	ug","Imperial Ton	imt","US Ton		ust","Stone		st","Pound		lb","Ounce		oz"};
	char* mass_units[]={"t","kg","g","mg","ug","imt","ust","st","lb","oz"};
	double to_gram[]={1000000.0,1000.0,1.0,0.001,0.000001,1016000.0,907185.0,6350.29,453.592,28.3495};
	double from_gram[]={0.000001,0.001,1.0,1000.0,1000000.0,0.00000098,0.0000011,0.0001575,0.0022046,0.035274};
		
	converter_ui("Mass Converter");

	create_list(masses,sizeof(masses)/4,15,2);
	
	gotoxy(18,7);
	char in_unit[4];
	gets(in_unit);
	if(strcmpi(in_unit,"t")&&strcmpi(in_unit,"kg")&&strcmpi(in_unit,"g")&&strcmpi(in_unit,"mg")&&strcmpi(in_unit,"ug")&&strcmpi(in_unit,"imt")&&strcmpi(in_unit,"ust")&&strcmpi(in_unit,"st")&&strcmpi(in_unit,"lb")&&strcmpi(in_unit,"oz"))	//checks if entered unit is valid
	{
		error_mssg("Invalid Mass Unit!");
		mass();
	}
	gotoxy(18,9);
	double in_amt;
	cin>>in_amt;
	
	double temp_amt=convert(in_unit,in_amt,mass_units,sizeof(mass_units)/4,to_gram);

	gotoxy(53,7);
	char out_unit[4];
	gets(out_unit);
	if(strcmpi(out_unit,"t")&&strcmpi(out_unit,"kg")&&strcmpi(out_unit,"g")&&strcmpi(out_unit,"mg")&&strcmpi(out_unit,"ug")&&strcmpi(out_unit,"imt")&&strcmpi(out_unit,"ust")&&strcmpi(out_unit,"st")&&strcmpi(out_unit,"lb")&&strcmpi(out_unit,"oz"))
	{
		error_mssg("Invalid Mass Unit!");
		mass();
	}

	double out_amt=convert(in_unit,in_amt,mass_units,sizeof(mass_units)/4,from_gram);
	
	gotoxy(53,9);
	cout<<out_amt;

	gotoxy(50,23);
	cout<<"Press Backspace to go back..";
	gotoxy(10,23);
	cout<<"Press Enter to use again..";
	char temp=getch();
	if(temp==13)
		mass();
	if(temp==8)
		converter();
}

void length()
{
	char* lengths[]={"Kilometre	km","Metre		m","Centimetre	cm","Millimetre	mm","Nanometre	nm","Mile		mi","Yard		yd","Foot		ft","Inch		in","Nautical mile	nmi"};
	char* length_units[]={"km","m","cm","mm","nm","mi","yd","ft","in","nmi"};
	double to_metre[]={1000.0,1.0,0.01,0.001,0.000000001,1609.34,0.9144,0.3048,0.0254,1852.0};
	double from_metre[]={0.001,1.0,100.0,1000.0,1000000000.0,0.000621371,1.09361,3.28084,39.3701,0.000539957};
		
	converter_ui("Length Converter");

	create_list(lengths,sizeof(lengths)/4,15,2);

	gotoxy(18,7);
	char in_unit[4];
	gets(in_unit);
	if(strcmpi(in_unit,"km")&&strcmpi(in_unit,"m")&&strcmpi(in_unit,"cm")&&strcmpi(in_unit,"mm")&&strcmpi(in_unit,"nm")&&strcmpi(in_unit,"mi")&&strcmpi(in_unit,"yd")&&strcmpi(in_unit,"ft")&&strcmpi(in_unit,"in")&&strcmpi(in_unit,"nmi"))	//checks if entered unit is valid
	{
		error_mssg("Invalid length unit!");
		length();
	}
	gotoxy(20,9);
	double in_amt;
	cin>>in_amt;

	double temp_amt=convert(in_unit,in_amt,length_units,sizeof(length_units)/4,to_metre);
	
	gotoxy(53,7);
	char out_unit[4];
	gets(out_unit);
	if(strcmpi(out_unit,"km")&&strcmpi(out_unit,"m")&&strcmpi(out_unit,"cm")&&strcmpi(out_unit,"mm")&&strcmpi(out_unit,"nm")&&strcmpi(out_unit,"mi")&&strcmpi(out_unit,"yd")&&strcmpi(out_unit,"ft")&&strcmpi(out_unit,"in")&&strcmpi(out_unit,"nmi"))
	{
		error_mssg("Invalid length unit!");
		length();
	}

	double out_amt=convert(out_unit,temp_amt,length_units,sizeof(length_units)/4,from_metre);
	
	gotoxy(55,9);
	cout<<out_amt;

	gotoxy(50,23);
	cout<<"Press Backspace to go back..";
	gotoxy(10,23);
	cout<<"Press Enter to use again..";
	char temp=getch();
	if(temp==13)
		length();
	if(temp==8)
		converter();
}

void area()
{
	char* areas[]={"Square kilometre	sq km","Square metre	sq m","Square mile	sq mi","Square yard	sq yd","Square foot	sq ft","Square inch	sq in","Hectare		ha","Acre		ac"};
	char* area_units[]={"sq km","sq m","sq mi","sq yd","sq ft","sq in","ha","ac"};
	double to_metre_sq[]={1000000.0,1.0,2590000.0,0.836127,0.092903,0.00064516,10000.0,4046.86};
	double from_metre_sq[]={0.000001,1.0,0.0000003861,1.19599,10.7639,1550,0.0001,0.000247105};
		
	converter_ui("Area Converter");

	create_list(areas,sizeof(areas)/4,15,2);
	
	gotoxy(18,7);
	char in_unit[6];
	gets(in_unit);
	if(strcmpi(in_unit,"sq km")&&strcmpi(in_unit,"sq m")&&strcmpi(in_unit,"sq mi")&&strcmpi(in_unit,"sq yd")&&strcmpi(in_unit,"sq ft")&&strcmpi(in_unit,"sq in")&&strcmpi(in_unit,"ac")&&strcmpi(in_unit,"ha"))
	{
		error_mssg("Invalid area unit!");
		area();
	}
	gotoxy(18,9);
	double in_amt;
	cin>>in_amt;
	
	double temp_amt=convert(in_unit,in_amt,area_units,sizeof(area_units)/4,to_metre_sq);
		
	gotoxy(53,7);
	char out_unit[4];
	gets(out_unit);
	if(strcmpi(out_unit,"sq km")&&strcmpi(out_unit,"sq m")&&strcmpi(out_unit,"sq mi")&&strcmpi(out_unit,"sq yd")&&strcmpi(out_unit,"sq ft")&&strcmpi(out_unit,"sq in")&&strcmpi(out_unit,"ac")&&strcmpi(out_unit,"ha"))
	{
		error_mssg("Invalid area unit!");
		area();
	}

	double out_amt=convert(out_unit,temp_amt,area_units,sizeof(area_units)/4,from_metre_sq);
	
	gotoxy(53,9);
	cout<<out_amt;

	gotoxy(50,23);
	cout<<"Press Backspace to go back..";
	gotoxy(10,23);
	cout<<"Press Enter to use again..";
	char temp=getch();
	if(temp==13)
		area();
	if(temp==8)
		converter();
}

void volume()
{
	char* volumes[]={"US liquid gallon	US gal","US quart		US qt","US pint		US pt","US fluid ounce	US fl oz","US cup		US cp","Cubic metre		m3","Litre		L","Millilitre		ml","Imperial gallon	im gal","Imperial quart	im qt","Imperial pint	im pt","Imperial fluid ounce    im fl oz","Imperial cup		im cp","Cubic foot		ft3","Cubic inch		in3"};
	char* volume_units[]={"US gal","US qt","US pt","US fl oz","US cp","m3","L","ml","im gal","im qt","im pt","im fl oz","im cp","ft3","in3"};
	double to_litre[]={3.785411784,0.946352946,0.473176473,0.0295735295625,0.2365882365,1000.0,1.0,0.001,4.54609,1.1365225,0.56826125,0.0284130625,0.284131,28.3168,0.0163871};
	double from_litre[]={0.264172,1.05669,2.11338,33.81405,4.16667,0.001,1.0,1000.0,0.219969,0.879877,1.75975,35.1951,3.51951,0.0353147,61.0237};
	
	converter_ui("Volume Converter");
	
	create_list(volumes,sizeof(volumes)/4,15,2);
	
	gotoxy(18,7);
	char in_unit[4];
	gets(in_unit);
	/*if(strcmpi(in_unit,"t")&&strcmpi(in_unit,"kg")&&strcmpi(in_unit,"g")&&strcmpi(in_unit,"mg")&&strcmpi(in_unit,"ug")&&strcmpi(in_unit,"imt")&&strcmpi(in_unit,"ust")&&strcmpi(in_unit,"st")&&strcmpi(in_unit,"lb")&&strcmpi(in_unit,"oz"))	//checks if entered unit is valid
	{
		error_mssg("Invalid Mass Unit!");
		mass();
	}*/
	gotoxy(20,9);
	double in_amt;
	cin>>in_amt;
	
	double temp_amt=convert(in_unit,in_amt,volume_units,sizeof(volume_units)/4,to_litre);

	gotoxy(53,7);
	char out_unit[4];
	gets(out_unit);
	/*if(strcmpi(out_unit,"t")&&strcmpi(out_unit,"kg")&&strcmpi(out_unit,"g")&&strcmpi(out_unit,"mg")&&strcmpi(out_unit,"ug")&&strcmpi(out_unit,"imt")&&strcmpi(out_unit,"ust")&&strcmpi(out_unit,"st")&&strcmpi(out_unit,"lb")&&strcmpi(out_unit,"oz"))
	{
		error_mssg("Invalid Mass Unit!");
		mass();
	}*/

	double out_amt=convert(in_unit,in_amt,volume_units,sizeof(volume_units)/4,from_litre);
	
	gotoxy(55,9);
	cout<<out_amt;

	gotoxy(50,23);
	cout<<"Press Backspace to go back..";
	gotoxy(10,23);
	cout<<"Press Enter to use again..";
	char temp=getch();
	if(temp==13)
		volume();
	if(temp==8)
		converter();
}
/////////////////////////////////////////////////
void calc()					//yet to optimize
 {
  char l,l1,l2,l3,l4,ch[10];
  int a,b;
  double a1,b1;
	cout<<"***************CALCULATOR***************";
  do
	{
	  cout<<'\t'<<'\t'<<"\n 1:Arithemetic Operations";
  cout<<'\t'<<'\t'<<"\n 2:Trignometric Functions";
  cout<<'\t'<<'\t'<<"\n 3:Logarithmic Functions";
  cout<<'\t'<<'\t'<<"\n 4:Power Functions";
  l=getch();
  switch(l)
	{
	case'1':
		 {
		 cout<<'\t'<<'\t'<<"\n ADDITION         A";
		 cout<<'\t'<<'\t'<<"\n SUBRACTION       S";
		 cout<<'\t'<<'\t'<<"\n MULTIPLICATION   M";
		 cout<<'\t'<<'\t'<<"\n DIVISION         D";
		 cout<<'\t'<<'\t'<<"\n PERCENTAGE       P";
		 l1=getch();
		 if(l1=='A')
		  {
			cout<<"\n enter the numbers";
			cin>>a>>b;
			cout<<"\n the sum is"<<a+b;
		  }
		 else if(l1=='S')
		  {
			cout<<"\n enter the numbers";
			cin>>a>>b;
			cout<<"\n the difference is"<<a-b;
		  }
		 else if(l1=='M')
		  {
			cout<<"\n enter the numbers";
			cin>>a>>b;
			cout<<"\n the product is"<<a*b;
		  }
		 else if(l1=='D')
		  {
			cout<<"\n enter the numbers";
			cin>>a>>b;
			cout<<"\n the quotient is"<<a/b;
		  }
		 else if(l1=='P')
		  {
			cout<<"\n enter the numbers";
			cin>>a>>b;
			cout<<"\n the percent is"<<a%b;
		  }
		 else
			cout<<"\n invalid operator \n";
		break;
		}
	case'2':
		 {
		 cout<<'\t'<<'\t'<<"\n COS FUNCTION     C";
		 cout<<'\t'<<'\t'<<"\n SIN FUNCTION     S";
		 cout<<'\t'<<'\t'<<"\n TAN FUNCTION     T";
		 l2=getch();
		 if(l2=='C')
		  {
			cout<<"\n enter the number";
			cin>>a1;
			cout<<"\n the value is"<<cos(a1);
		  }
		 else if(l2=='S')
		  {
			cout<<"\n enter the number";
			cin>>a1;
			cout<<"\n the value is"<<sin(a1);
		  }
		 else if(l2=='T')
		  {
			cout<<"\n enter the numbers";
			cin>>a1;
			cout<<"\n the value  is"<<tan(a1);
		  }
		 else
			cout<<"\n invalid operator \n";
		break;
		}
	case'3':
		 {
		 cout<<'\t'<<'\t'<<"\n NATURAL LOG         N";
		 cout<<'\t'<<'\t'<<"\n LOG WITH BASE 10    L";
		 l3=getch();
		 if(l3=='N')
		  {
			cout<<"\n enter the number";
			cin>>a1;
			cout<<"\n the value is"<<log(a1);
		  }
		 else if(l3=='S')
		  {
			cout<<"\n enter the number";
			cin>>a1;
			cout<<"\n the value is"<<log10(a1);
		  }
		 else
			cout<<"\n invalid operator \n";
		break;
		}
	case'4':
		 {
		 cout<<'\t'<<'\t'<<"\n POWER         P";
		 cout<<'\t'<<'\t'<<"\n SQURE ROOT    S";
		 l4=getch();
		 if(l4=='P')
		  {
			cout<<"\n enter the number and power";
			cin>>a1>>b1;
			cout<<"\n the value is"<<pow(a1,b1);
		  }
		 else if(l4=='S')
		  {
			cout<<"\n enter the number";
			cin>>a1;
			cout<<"\n the value is"<<sqrt(a1);
		  }
		 else
			cout<<"\n invalid operator \n";
		break;
		}
	}
  cout<<"\n do you want to continue";
	gets(ch);
 }while(ch[0]=='Y');
}
///////////////////////////////////////converter ends///////////////////////////////////////////
//////////////////////////////////////world clock starts////////////////////////////////////////
void world_clock()
{
	char* cities[]={"1. Los Angeles","2. New York","3. Buenos Aires","4. London","5. Paris","6. Riyadh","7. Delhi","8. Beijing","9. Sydney"};
	
	void display_time(char city[],int hr,int mn);

	ask_time_option:
	
	clrscr();
	border('*',1,1,80,24);
	gotoxy(30,3);
	cout<<"World Clock\n";
	gotoxy(3,5);
	cout<<"Choose the city:";
	
	create_list(cities,sizeof(cities)/4,7);
	
	gotoxy(43,23);
	cout<<"Press backspace to go to main menu..";
	gotoxy(39,19);
	cout<<"___";
	gotoxy(40,19);
	char opt=getch();
	
	switch(opt)
	{
		case '1':	display_time("Los Angeles",-8,0);
				break;
		case '2':	display_time("New York",-5,0);
				break;
		case '3':	display_time("Buenos Aires",-3,0);
				break;
		case '4':	display_time("London",0,0);
				break;
		case '5':	display_time("Paris",1,0);
				break;
		case '6':	display_time("Riyadh",3,0);
				break;
		case '7':  	display_time("Delhi",5,30);
				break;
		case '8':  	display_time("Beijing",8,0);
				break;
		case '9':	display_time("Sydney",10,0);
				break;
		case 8	:	menu();
				break;
		default	:	error_mssg("Invalid option!",32);
				goto ask_time_option;
	}
}

void display_time(char city[],int hr,int mn)
{
	get_time:
	
	time_t rawtime=time(0);		//gets the unix timestamp. ie, no. of seconds since 1 Jan 1970
	struct tm *gmt;
	gmt=gmtime(&rawtime);		//converts rawtime to UTC and stores in struct gmt

	clrscr();
	border('*',1,1,80,24);
	border('.',25,9,30,5);
	gotoxy(31,11);
	cout<<city<<" --- "<<(17+24+hr+(gmt->tm_hour))%24+(mn+(gmt->tm_min))/60<<':'<<(mn+(gmt->tm_min))%60<<':'<<(gmt->tm_sec)<<endl; // +17 because the utc time was off by 17 (temporary fix)
	
	time_refresh:
	gotoxy(3,23);
	cout<<"Press r to refresh";
	gotoxy(50,23);
	cout<<"Press backspace to return";
	char temp=getch();
	if(temp=='r'||temp=='R')
		goto get_time;
	else if(temp==8)
		world_clock();
	else				//this is so that it rejects other key presses
		goto time_refresh;
}
/////////////////////////////////////world clock ends///////////////////////////////////////////
/////////////////////////////////////snake game starts//////////////////////////////////////////
void delay()
{
	long i;
	for(i=0;i<30000000;i++);
}

int left=0,right=0,up=0,down=0,escape=0;

void check()
{
	if(GetAsyncKeyState(VK_LEFT))
	{
		left=1,right=0,up=0,down=0;
	}
	else if(GetAsyncKeyState(VK_RIGHT))
	{
		left=0,right=1,up=0,down=0;
	}
	else if(GetAsyncKeyState(VK_UP))
	{
		left=0,right=0,up=1,down=0;
	}
	else if(GetAsyncKeyState(VK_DOWN))
	{
		left=0,right=0,up=0,down=1;
	}
	else if(GetAsyncKeyState(VK_ESCAPE))
		escape=1;
}

void snake()
{
	int x=2,y=2;
	left=0;
	right=0;
	up=0;
	down=1;
	int score=0,eaten=1,a,b;
	while(!GetAsyncKeyState(VK_ESCAPE))
	{
		randomize();
		//score report
		gotoxy(70,0);
		cout<<score;
		if(eaten)
		{
			b=rand()%10+rand()%10+10;
			a=rand()%10+rand()%10+rand()%10+rand()%10+rand()%10+rand()%10+rand()%10+rand()%10+10;
			gotoxy(a,b);
			cout<<"#";
			eaten=0;
		}

		while(down)
		{
			if(x==a&&y==b)
			{
				score++;eaten=1;
			}
			check();
			gotoxy(x,y);
			cout<<"*"<<endl;
			gotoxy(x,y-1);
			cout<<" ";
			delay();
			if(y==24)
			{
				gotoxy(x,y);
				cout<<" ";
				y=1;
			}
			y++;

			if(left||right||up||escape)
			{
				gotoxy(x,y-1);
				cout<<" ";
				goto out0;
			}
		}

		out0:
		while(up)
		{
			if(x==a&&y==b)
			{
				score++;
				eaten=1;
			}
			check();
			gotoxy(x,y);
			cout<<"*"<<endl;
			gotoxy(x,y+1);
			cout<<" ";
			delay();
			if(y==2)
			{
				gotoxy(x,y);
				cout<<" ";
				y=25;
			}
			y--;
			check();
			if(left||right||down||escape)
			{
				gotoxy(x,y+1);cout<<" ";goto out1;
			}
		}
	
		out1:
		while(left)
		{
			check();
			if(x==a&&y==b)
			{
				score++;
				eaten=1;
			}
			gotoxy(x,y);
			cout<<"*"<<endl;
			gotoxy(x+1,y);
			cout<<" ";
			delay();
			if(x==0)
			{
				gotoxy(x,y);
				cout<<" ";
				x=80;
			}
			x--;
			check();
			if(down||right||up||escape)
			{
				gotoxy(x+1,y);
				cout<<" ";
				gotoxy(x,y);
				cout<<" ";
				goto out2;
			}
		}
		
		out2:
		while(right)
		{
			check();
			if(x==a&&y==b)
			{
				score++;
				eaten=1;
			}
			gotoxy(x,y);
			cout<<"*"<<endl;
			gotoxy(x-1,y);
			cout<<" ";
			delay();
			if(x==80)
			{
				gotoxy(x,y);
				cout<<" ";
				x=0;
			}
			x++;
			check();
			if(left||down||up||escape)
			{
				gotoxy(x-1,y);
				cout<<" ";
				goto out3;
			}
		}
		
		out3:
	}
}
////////////////////////////////////snake game ends///////////////////////////////////////////
void main()
{
	login();
	menu();
}
