class user
{
	private:
			char password[50];
			char username[50];
	public:
			char* retpassword()
			{
				return password;
			}
			char* retusername()
			{
				return username;
			}
};

void login()
{
	char uname[50],pass[50];
	int bool=0;
	user U;

	enter_username:
	clrscr();
	gotoxy(30,10);
	cout<<"Username: ";
	gets(uname);
	ifstream infile("user.dat",ios::in|ios::binary);
	if(!infile)
	{
		error_mssg("File doesn't exist!!",30);
		exit(1);
	}
	while(!infile.eof())
	{
		infile.read((char*)&U,sizeof(user));
		if(strcmp(U.retusername(),uname)==0)
		{
			bool=1;
			infile.close();
			break;
		}
	}
	if(bool==0)
	{
		error_mssg("Username is incorrect",29);
		infile.close();
		goto enter_username;
	}
				/////////////////////////////////////////////////////
	enter_password:

	bool=0;
	gotoxy(30,12);
	cout<<"Password: ";
	strcpy(pass,getpass());
	infile.open("user.dat",ios::in|ios::binary);
	if(!infile)
	{
		error_mssg("File doesn't exist!!",30);
		exit(1);
	}
	while(!infile.eof())
	{
		infile.read((char*)&U,sizeof(user));
		if(strcmp(U.retpassword(),pass)==0)
		{
			infile.close();
			bool=1;
			break;
		}
	}
	if(bool==0)
	{
		error_mssg("Password is incorrect",29);
		infile.close();
		goto enter_username;
	}			////////////////////////////////////////////////////////
}
