#include<iostream.h>
#include<fstream.h>
#include<stdio.h>
#include<string.h>
#include<conio.h>

//public variables
char encrypted_text[30],decrypted_text[30];

class contacts
{
	private:
			char name[20],addline_1[20],addline_2[20],email_id[30];
			char ph_no[10],mob_no[10];
			char index;
	public:
			void file_edit();
			void input(char q);    //get contacts details by input
			void display();
			void menu();
			void createnew();
			void edit(char temp[]);
			void deletecontact(char tmp[]);
			void Sort();
			void Scroll();
			void clrdsp();
			void charfix(char temp[],char letter,int mode);
			void encrypt(char temp[]);
			void decrypt(char temp[]);
}c,f;

void contacts::Sort()
{
	int i=0;
	char contact[100][20];
	char tmp[20];
	ifstream file;
	file.open("contacts.cf",ios::binary);
	while(file.read((char*)&c,sizeof(c)))
	{
		decrypt(name);
		strcpy(contact[i],decrypted_text);
		i++;
	}

	int n,j;
	n=i;

	for(i=0;i<n-1;i++)
	{
		for(j=i+1;j<n;j++)
		{
			if(strcmpi(contact[i],contact[j])>0)
			{
				strcpy(tmp,contact[i]);
				strcpy(contact[i],contact[j]);
				strcpy(contact[j],tmp);
			}
		}
	}

	cout<<endl;                      //debug info
	for(i=0;i<n;i++)
	{
		encrypt(contact[i]);
		strcpy(contact[i],encrypted_text);
	}
	file.close();
	ifstream file2;
	ofstream file3;
	file3.open("temp.cf",ios::binary);
	file2.open("contacts.cf",ios::binary);
	char sorted[100];
	i=0;

	for(int k=0;k<n;k++)
	{
		file2.seekg(0);
		while(file2.read((char*)&c,sizeof(c)))
		{
			if(strcmp(contact[k],name)==0)
			{
				file3.write((char*)&c,sizeof(c));
				i++;
				break;
			}
		}
	}
	cout<<endl;                      //debug info
	for(i=0;i<n;i++)                 //debug info
		cout<<int(sorted[i])<<endl;       //debug info
	remove("contacts.cf");
	rename("temp.cf","contacts.cf");
	file2.close();
	file3.close();
	file.close();
	clrscr();
}
void contacts :: clrdsp()
{
	gotoxy(38,8);cout<<"                                           ";
	gotoxy(38,9);cout<<"                                           ";
	gotoxy(38,10);cout<<"                                          ";
	gotoxy(38,11);cout<<"                                          ";
	gotoxy(38,12);cout<<"                                          ";
	gotoxy(38,13);cout<<"                                          ";
}
void contacts :: encrypt(char temp[])
{
	char ekeyl[]="gi*dhwp(k{}?|^y$x#fv'%q!ua@. ICFEUSWRVD";
	char ekeyu[]="coenXmZ&):<>+][_`jlOrz~s-=@.";
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
					output[i]=ekeyl[j];
					i++;
					if(i!=l)
						goto con;
					else
						goto exit;
				}

				if(dkeyu[j]==temp[i])
				{
					//cout<<"here2";                                                //debug info
					output[i]=ekeyu[j];
					i++;
					if(i!=l)
						goto con;
					else
						goto exit;
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
	char ekeyu[]="coenXmZ&):<>+][_`jlOrz~s-=@.";
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
				else
					goto exit;
			}

			if(ekeyu[j]==temp[i])
			{
				//cout<<"here2";                                                //debug info
				output[i]=dkeyu[j];
				i++;
				if(i!=l)
					goto con;
				else
					goto exit;
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
	int n;
	char i=0;
	cout<<"Enter number of contacts:";
	cin>>n;
	ofstream file;
	file.open("contacts.cf",ios::binary||ios::out);
	while(i<n)
	{
		c.input(i);
		i=i+1;
		file.write((char*)&c,sizeof(c));
	}
	file.close();
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
		cout<<"ERROR FILE READ ERROR";
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
	gotoxy(36,9);cout<<"                         ";
	gotoxy(41,10);cout<<"                         ";
	gotoxy(41,11);cout<<"                         ";
	gotoxy(41,12);cout<<"                         ";
	gotoxy(41,13);cout<<"                         ";     //cleaning screen

	gotoxy(38,8);
	cout<<"Contact Name:";
	decrypt(name);
	puts(decrypted_text);

	gotoxy(38,9);
	cout<<"Phone no:";
	cout<<ph_no<<endl;

	gotoxy(38,10);
	cout<<"Mobile no:";
	puts(mob_no);

	gotoxy(38,11);
	cout<<"Email id:";
	decrypt(email_id);
	puts(decrypted_text);

	gotoxy(38,12);
	cout<<"Address (line 1):";
	decrypt(addline_1);
	puts(decrypted_text);

	gotoxy(38,13);
	cout<<"Address (line 2):";
	decrypt(addline_2);
	puts(decrypted_text);

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
void contacts :: input(char q)    //get contacts details by input
{
	index=q;
	char a;
	gotoxy(38,8);
	cout<<"Contact Name:";
	a=getche();
	if(a==13)
		goto next0;
	else
		gets(name);
	charfix(name,a,1);
	encrypt(name);
	strcpy(name,encrypted_text);

	next0:

	gotoxy(38,9);
	cout<<"Phone no:";
	a=getche();
	if(a==13)
		goto next1;
	else
		gets(ph_no);
	charfix(ph_no,a,2);

	next1:

	gotoxy(38,10);
	cout<<"Mobile no:";
	a=getche();
	if(a==13)
		goto next2;
	else
		gets(mob_no);
	charfix(mob_no,a,3);

	next2:

	gotoxy(38,11);
	cout<<"Email id:";
	a=getche();
	if(a==13)
		goto next3;
	else
		gets(email_id);
	charfix(email_id,a,4);
	encrypt(email_id);
	strcpy(email_id,encrypted_text);

	next3:

	gotoxy(38,12);
	cout<<"Address (line 1):";
	a=getche();
	if(a==13)
		goto next4;
	else
		gets(addline_1);
	charfix(addline_1,a,5);
	encrypt(addline_1);
	strcpy(addline_1,encrypted_text);

	next4:

	gotoxy(38,13);
	cout<<"Address (line 2):";
	a=getche();
	if(a==13)
		goto next5;
	else
		gets(addline_2);
	charfix(addline_2,a,6);
	encrypt(addline_2);
	strcpy(addline_2,encrypted_text);

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
	int fail=1;
	fio.seekg(0);

	while(fio.read((char*)&c,sizeof(c)))   //testing if we can still read
	{
		if(strcmp(name,name1)==0)              //check name
		{
			input(recc+1);
			fout.seekp(recc*sizeof(c),ios::beg);
			fout.write((char*)&c,sizeof(c));
			fout.close();
			fail=0;
			break;
		}
		gotoxy(1,1);
		recc++;
	}
	if(fail==1)
		cout<<"FILE READ ERROR        ";
	fio.close();
	fio.close();
	//c.menu();
}

void contacts::createnew()
{
	//clear values
	name[0]='\0';
	ph_no[0]='\0';
	mob_no[0]='\0';
	email_id[0]='\0';
	addline_1[0]='\0';
	addline_2[0]='\0';

	ifstream file;
	ofstream temp;
	temp.open("$$.cf",ios::binary);
	file.open("contacts.cf",ios::binary);
	int recc=0;
	while(file.read((char*)&c,sizeof(c)))
	{
		temp.write((char*)&c,sizeof(c));
		recc++;
	}
	input(recc+1);
	temp.write((char*)&c,sizeof(c));
	temp.close();
	temp.close();
	file.close();
	file.close();
	remove("contacts.cf");
	rename("$$.cf","contacts.cf");
	clrscr();
	//clear values
	name[0]='\0';
	ph_no[0]='\0';
	mob_no[0]='\0';
	email_id[0]='\0';
	addline_1[0]='\0';
	addline_2[0]='\0';

	Sort();
	menu();
}

int recc=0,scroll=0;

void contacts::Scroll()
{
		clrscr();
		gotoxy(0,6);
		ifstream file3;
		int m=0;
		file3.open("contacts.cf",ios::binary);
		cout<<"Contacts List:"<<endl;
		cout<<"+Add New+"<<endl;

		while(file3.read((char*)&c,sizeof(c)))
		{
			m++;
			if(m>15)
			{
				decrypt(name);
				cout<<decrypted_text<<endl;
			}
		}
		file3.close();
		//int l=0;
		int x=20,z=15;
		int y=8;
		gotoxy(x,y);
		cout<<"<--";
		gotoxy(x,y);
		ifstream file7;
		file7.open("contacts.cf",ios::binary);
		file7.seekg(15*sizeof(c),ios::beg);
		file7.read((char*)&c,sizeof(c));
		c.display();
		int n=m-15;
		loop10:
		char a=getch();
		if(a=='s' && y==20)
		{
			clrscr();
			cout<<"MAXIMUM CONTACTS REACHED..";
		}
		if(a=='s' && y<n+7)
		{
			gotoxy(x,y);
			cout<<"   ";
			y++;
			gotoxy(x,y);
			cout<<"<--";
			file7.read((char*)&c,sizeof(c));
			c.display();
			z++;
		}

		if(a=='w' && y>=8)
		{
			gotoxy(x,y);
			cout<<"   ";
			y--;
			gotoxy(x,y);
			cout<<"<--";
			file7.seekg((--z)*sizeof(c),ios::beg);
			file7.read((char*)&c,sizeof(c));
			c.display();
		}
		if(a=='w' && y==7)
		{
			scroll=0;
			clrscr();
			menu();
		}
		if(a==13&&y!=7)
		goto enterkey;

		goto loop10;

	enterkey:

	gotoxy(0,24);
	cout<<"Use A & S keys to choose option                                              ";
	cout<<endl<<"Hit Enter to select option. Press B to go back. Press BackSpace to exit";
	gotoxy(10,y);
	cout<<"   ";
	int y1=18,x1=38;
	gotoxy(38,y1-1);
	cout<<"Edit Contact";
	gotoxy(55,y1-1);
	cout<<"Delete Contact";
	gotoxy(x1,y1);
	cout<<"************";

	loop11:

	char b=getch();
	if(b=='d')
	{
		x1=55;
		gotoxy(38,y1);
		cout<<"               ";
		gotoxy(55,y1);
		cout<<"               ";
		gotoxy(x1,y1);
		cout<<"***************";
	}

	if(b=='a')
	{
		x1=38;
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
		file7.close();
		gotoxy(38,8);
		edit(name);
	}
	if(b==13&&x1==55)
	{
		clrdsp();
		file7.close();
		decrypt(name);
		char name2[20];
		strcpy(name2,decrypted_text);
		deletecontact(name2);
	}
	if(b=='b'||b=='B')
	{
		clrscr();
		Scroll();
	}
	if(b==8)
		return;

	goto loop11;


}

void contacts :: menu()
{
	clrscr();
	gotoxy(0,24);
	cout<<"Use W & S keys to scroll through contacts";
	cout<<endl<<"Hit Enter to select contact. Press BackSpace to exit";
	gotoxy(38,17);
	cout<<"              ";
	gotoxy(38,18);
	cout<<"              ";
	gotoxy(55,17);
	cout<<"              ";
	gotoxy(55,18);
	cout<<"              ";
	gotoxy(30,1);
	cout<<endl<<endl<<endl;

	ifstream file;
	file.open("contacts.cf",ios::binary);
	cout<<endl<<endl;
	int n=0;
	cout<<"Contacts List:"<<endl;
	cout<<"+Add New+"<<endl;
	file.seekg(0);
	while(file.read((char*)&c,sizeof(c)))
	{
		n++;
		decrypt(name);
		cout<<decrypted_text<<endl;
		if(n==14)
			break;
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
	if(scroll==1)
		Scroll();
	else
	{
	if(a!=8)
	{	//return;
		if(a=='w'&&y==8)
		{
			clrdsp();
			gotoxy(x,y);
			cout<<"   ";
			y--;
			gotoxy(x,y);
			cout<<"<--";
		}

	if(a=='s'&&y<(n+9))
	{
		clrdsp();
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
		file1.seekg(((recc*(sizeof(c)))-sizeof(c)),ios::beg);
		file1.read((char*)&c,sizeof(c));
		c.display();
		recc--;
	}
	if(a=='s'&& y==22)
	{
		scroll=1;
		Scroll();
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
	cout<<"Use A & S keys to choose option                                              ";
	cout<<endl<<"Hit Enter to select option. Press B to go back. Press BackSpace to exit";
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
	{
		x1=55;
		gotoxy(38,y1);
		cout<<"               ";
		gotoxy(55,y1);
		cout<<"               ";
		gotoxy(x1,y1);
		cout<<"***************";
	}

	if(b=='a')
	{
		x1=38;
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
	if(b==8)
		return;

	goto loop2;

	}
	}
}
void main()
{
	clrscr();
	c.menu();
}
