#include <fstream.h>
#include <string.h>
#include <conio.h>
#include<ctype.h>
#include<stdio.h>
#include<stdlib.h>

int checkwin(char square[]);
void board(char square [10]) ;
void registernew();
void userdetails() ;
void run();
void tournament();

class user                                  //defines class, how we entered all user data
{
  char name[30];
  int won;
  int id;
  int lost;

  public:
			user()
			{
				strcpy(name, "Not Entered");
				won=0;
				lost=0;
				id=NULL;
			}

			int retid()
			{
				return id;
			}

			int comparenames(char nm[])
			{
				return(strcmpi(name, nm));
			}

			void showname()
			{
				cout<<name;
			}

			void retname(char nm[30])
			{
				nm=name;
			}

			void win()
			{
				won++;
			}

			void loss()
			{
				lost++;
			}

			void read()                                              //to add user name and id
			{
				cout<<"Enter unique user name: ";
				gets(name);
				cout<<"Enter unique user id (3 digit number): ";
				cin>>id;
			}

			void display()                                                //to display all user details
			{
				cout<<"User Name: ";
				puts(name);
				cout<<"User Id: "<<id<<endl;
				cout<<"No of games won: "<<won<<endl;
				cout<<"No of tournamentswon: "<<twon<<endl;
				cout<<"No of games lost: "<<lost;
			}

			~user()
			{
			}

};

int checkwin(char square[])              //to return game status
		{
			if (square[1] == square[2] && square[2] == square[3])
				return 1;
			else if (square[4] == square[5] && square[5] == square[6])
				return 1;
			else if (square[7] == square[8] && square[8] == square[9])
				return 1;
			else if (square[1] == square[4] && square[4] == square[7])
				return 1;
			else if (square[2] == square[5] && square[5] == square[8])
				return 1;
			else if (square[3] == square[6] && square[6] == square[9])
				return 1;
			else if (square[1] == square[5] && square[5] == square[9])
				return 1;
			else if (square[3] == square[5] && square[5] == square[7])
				return 1;
			else if (square[1] != '1' && square[2] != '2' && square[3] != '3' && square[4] != '4'
						&& square[5] != '5' && square[6] != '6' && square[7] != '7' && square[8] != '8' && square[9] != '9')
				return 0;
			else
				return -1;
		}

void board(char square [10])               //to draw the board
		{
			cout << "";
			cout << " 1 (X) –  2 (O)" << endl << endl;
			cout << endl;

			cout << " " << square[1] << " | " << square[2] << " | " << square[3] << endl;

			cout << " --|---|-- " << endl;
			cout << " " << square[4] << " | " << square[5] << " | " << square[6] << endl;
			cout << " --|---|-- " << endl;
			cout << " " << square[7] << " | " << square[8] << " | " << square[9] << endl<<endl;
		}

void run()                                              //to run a single game
{
			char square[10] = {'o','1','2','3','4','5','6','7','8','9'};

			user player1, player2;
			int p1, p2;

			fstream fin;
														  //player 1 details
			fin.open("records.dat", ios::binary|ios::in);
			cout<<"\nEnter user id of player 1\n";
			cin>>p1;

				user u;
				fin.read((char*)&u, sizeof(u));
				int found=0;

				while(fin)
				{
					if(u.retid()==p1)
					{ player1=u;
						found++;
					}

					fin.read((char*)&u, sizeof(u));
				}

				if(found==0)
					{
						cout<<"User id not found\n";
						exit(0);
					}
				fin.close();


			fin.open("records.dat", ios::binary|ios::in);                  //player 2 details
			fin.seekg(0);
			cout<<"Enter user id of player 2\n";
			cin>>p2;


				fin.read((char*)&u, sizeof(u));
				found=0;

				while(fin)
				{
					if(u.retid()==p2)
					{ player2=u;
						found++;
					}

					fin.read((char*)&u, sizeof(u));
				}

				if(found==0)
					{
						cout<<"User id not found\n";
						exit(0);
					}
				fin.close();

			clrscr();
			cout<<"\nGAME BEGINNING\n\n";
			cout<<"Welcome, ";
			player1.showname();
			cout<<" and ";
			player2.showname();
        			cout<<endl;

			int choice;                                        //actual code for the game
			char player[25];
			int p;
			int turn_no=1;
			char mark;
			do
			{
				board(square);

				if(turn_no%2==0)
					p=2;
				else
					p=1;

				if (p==1)
					player1.showname();
				else if (p==2)
					player2.showname();

				cout<<" : Enter number to insert marker ";
				cin >> choice;
				mark=(p== 1) ? 'X' : 'O';
				if ((choice == 1) && (square[1] == '1'))
					square[1] = mark;
				else if ((choice == 2) && (square[2] == '2'))
					square[2] = mark;
				else if ((choice == 3) && (square[3] == '3'))
					square[3] = mark;
				else if ((choice == 4) && (square[4] == '4'))
					square[4] = mark;
				else if ((choice == 5) && (square[5] == '5'))
					square[5] = mark;
				else if ((choice == 6) && (square[6] == '6'))
					square[6] = mark;
				else if ((choice == 7) && (square[7] == '7'))
					square[7] = mark;
				else if ((choice == 8) && (square[8] == '8'))
					square[8] = mark;
				else if ((choice == 9) && (square[9] == '9'))
					square[9] = mark;

				clrscr();
				turn_no++;

			}while (checkwin(square)==-1);                                  //code for game ends here

			if(checkwin(square)==0)                                        //to check for winners and update wins and losses
				cout<<"draw!";
			else if (checkwin(square)==1)
				{
					board(square);
					if (p==1)                                //player1 won
					{
						player1.showname();
						cout<<" won!";

						fin.open("records.dat", ios::binary|ios::in|ios::out);           //to update player1 details
						fin.seekg(0);
						user u;

						while(fin.read((char*)&u, sizeof(u)))
						 {
							if(u.retid()==p1)
								{
									u.win();
									int n=fin.tellg()-sizeof(u);
									fin.seekp(n);
									fin.write((char*)&u, sizeof(u));
								}
						 }
						fin.close();

						fin.open("records.dat", ios::binary|ios::in|ios::out);           //to update player2 details
						fin.seekg(0);

						while(fin.read((char*)&u, sizeof(u)))
						 {
							if(u.retid()==p2)
								{
									u.loss();
									int n=fin.tellg()-sizeof(u);
									fin.seekp(n);
									fin.write((char*)&u, sizeof(u));
								}
						 }
						fin.close();

					}

					else if(p==2)                             //player 2 won
					 {
						player2.showname();
						cout<<" won!";

						fin.open("records.dat", ios::binary|ios::in|ios::out);        //to update player1 details
						fin.seekg(0);
						user u;

						while(fin.read((char*)&u, sizeof(u)))
						 {
							if(u.retid()==p1)
								{
									u.loss();
									int n=fin.tellg()-sizeof(u);
									fin.seekp(n);
									fin.write((char*)&u, sizeof(u));
								}
						 }
						fin.close();
						fin.open("records.dat", ios::binary|ios::in|ios::out);           //to update player2 details
						fin.seekg(0);

						while(fin.read((char*)&u, sizeof(u)))
						 {
							if(u.retid()==p2)
								{
									u.win();
									int n=fin.tellg()-sizeof(u);
									fin.seekp(n);
									fin.write((char*)&u, sizeof(u));
								}
						 }
						fin.close();
					}
				}

}


void registernew()           //to register a new user
{
	fstream fin;
	fin.open("records.dat", ios::binary|ios::app);
	user u;
	u.read();
	fin.write((char*)&u, sizeof(u));
	fin.close();
}

void userdetails()          //to search for an existing user with the user name or user id
{
	int ch;
	cout<<"\nSearch by\n1.User Id\n2.User Name\n";
	cin>>ch;
	if (ch==1)
	{
		fstream fin;
		fin.open("records.dat", ios::binary|ios::in);
		fin.seekg(0);
		int uid;
		cout<<"\nEnter user id(3 digits): ";
		cin>>uid;
		user u;
		fin.read((char*)&u, sizeof(u));
		int found=0;

		while(fin)
		{
			if(u.retid()==uid)
			{	u.display();
				found++;
			}

			fin.read((char*)&u, sizeof(u));
		}

		if(found==0) cout<<"User id not found\n";
		fin.close();
	}

	else
	if (ch==2)
	{
		fstream fin;
		fin.open("records.dat", ios::binary|ios::in);
		char unm[30];
		cout<<"\nEnter user name: ";
		gets(unm);
		user u;
		int found=0;

		while(fin.read((char*)&u, sizeof(u)))
		{
			if(!u.comparenames(unm))
			{
				u.display();
				found++;
			}
		}

		if(found==0) cout<<"User name not found\n";
		fin.close();
	}

	else cout<<"Invalid choice";
}

	void main()
{
	cout<<"***TIC TAC TOE***"<<endl;
	char c;
	do
	{
		cout<<"\n1.Play a game\n2.Register a new user\n3.View existimg user's details\n4. Start a                   tournament\n\nNOTE:New users must be registered\n";                  
		int ch;
		cin>>ch;

		switch(ch)
		{
			case 1: run();
						break;
			case 2: registernew();
						break;
			case 3: userdetails();
						break;
			case 4: tournament();
						break;
		 }

		cout<<"\n\nWould you like to continue?";
		cin>>c;
	}while (c=='Y'||c=='y');
}

void tournament()                                              //to organise a tournament
{
			user player1, player2, player3, player4;
			int p1, p2, p3, p4;

			fstream fin;
														  //player 1 details
			fin.open("records.dat", ios::binary|ios::in);
			cout<<"\nEnter user id of player 1\n";
			cin>>p1;

				user u;
				fin.read((char*)&u, sizeof(u));
				int found=0;

				while(fin)
				{
					if(u.retid()==p1)
					{ player1=u;
						found++;
					}

					fin.read((char*)&u, sizeof(u));
				}

				if(found==0)
					{
						cout<<"User id not found\n";
						exit(0);
					}
				fin.close();


			fin.open("records.dat", ios::binary|ios::in);                  //player 2 details
			fin.seekg(0);
			cout<<"Enter user id of player 2\n";
			cin>>p2;


				fin.read((char*)&u, sizeof(u));
				found=0;

				while(fin)
				{
					if(u.retid()==p2)
					{ player2=u;
						found++;
					}

					fin.read((char*)&u, sizeof(u));
				}

				if(found==0)
					{
						cout<<"User id not found\n";
						exit(0);
					}
				fin.close();

			fin.open("records.dat", ios::binary|ios::in);                  //player 3 details
			fin.seekg(0);
			cout<<"Enter user id of player 3\n";
			cin>>p3;


				fin.read((char*)&u, sizeof(u));
				found=0;

				while(fin)
				{
					if(u.retid()==p3)
					{ player3=u;
						found++;
					}

					fin.read((char*)&u, sizeof(u));
				}

				if(found==0)
					{
						cout<<"User id not found\n";
						exit(0);
					}
				fin.close();

			fin.open("records.dat", ios::binary|ios::in);                  //player 4 details
			fin.seekg(0);
			cout<<"Enter user id of player 4\n";
			cin>>p4;


				fin.read((char*)&u, sizeof(u));
				found=0;

				while(fin)
				{
					if(u.retid()==p4)
					{ player4=u;
						found++;
					}

					fin.read((char*)&u, sizeof(u));
				}

				if(found==0)
					{
						cout<<"User id not found\n";
						exit(0);
					}
				fin.close();

			clrscr();
			cout<<"\nTOURNAMENT BEGINNING\n\n";

			cout<<"The match ups for the first round are as follows: \n" ;
			player1.showname();
			cout<<" V/S ";
			player2.showname();
			cout<<endl;
			player3.showname();
			cout<<" V/S ";
			player4.showname();
			cout<<endl;

			cout<<"Round 1, Match 1\n";                                //round 1 , match 1
			cout<<"\nGAME BEGINNING\n\n";
			cout<<"Welcome, ";
			player1.showname();
			cout<<" and ";
			player2.showname();
			cout<<endl;

			char square[10] = {'o','1','2','3','4','5','6','7','8','9'};
			int choice;                                        //actual code for the game
			char player[25];
			int p;
			int turn_no=1;
			char mark;
			do
			{
				board(square);

				if(turn_no%2==0)
					p=2;
				else
					p=1;

				if (p==1)
					player1.showname();
				else if (p==2)
					player2.showname();

				cout<<" : Enter number to insert marker ";
				cin >> choice;
				mark=(p== 1) ? 'X' : 'O';
				if ((choice == 1) && (square[1] == '1'))
					square[1] = mark;
				else if ((choice == 2) && (square[2] == '2'))
					square[2] = mark;
				else if ((choice == 3) && (square[3] == '3'))
					square[3] = mark;
				else if ((choice == 4) && (square[4] == '4'))
					square[4] = mark;
				else if ((choice == 5) && (square[5] == '5'))
					square[5] = mark;
				else if ((choice == 6) && (square[6] == '6'))
					square[6] = mark;
				else if ((choice == 7) && (square[7] == '7'))
					square[7] = mark;
				else if ((choice == 8) && (square[8] == '8'))
					square[8] = mark;
				else if ((choice == 9) && (square[9] == '9'))
					square[9] = mark;

				clrscr();
				turn_no++;

			}while (checkwin(square)==-1);                                  //code for game ends here

			if(checkwin(square)==0)                                        //to check for winners and update wins and losses
				cout<<"draw!";
			else if (checkwin(square)==1)
				{
					board(square);
					if (p==1)                                //player1 won
					{
						player1.showname();
						cout<<" won!";
					}

					else if(p==2)                             //player 2 won
					{
						player2.showname();
						cout<<" won!";
						p1=p2;
						player1=player2;
					}
				}

			cout<<"\n\nRound 1, Match 2\n";                                //round 1 , match 2
			char square2[10] = {'o','1','2','3','4','5','6','7','8','9'};
			cout<<"\nGAME BEGINNING\n\n";
			cout<<"Welcome, ";
			player3.showname();
			cout<<" and ";
			player4.showname();
			cout<<endl;

			turn_no=1;
			do
			{
				board(square2);

				if(turn_no%2==0)
					p=2;
				else
					p=1;

				if (p==1)
					player3.showname();
				else if (p==2)
					player4.showname();

				cout<<" : Enter number to insert marker ";
				cin >> choice;
				mark=(p== 1) ? 'X' : 'O';
				if ((choice == 1) && (square2[1] == '1'))
					square2[1] = mark;
				else if ((choice == 2) && (square2[2] == '2'))
					square2[2] = mark;
				else if ((choice == 3) && (square2[3] == '3'))
					square2[3] = mark;
				else if ((choice == 4) && (square2[4] == '4'))
					square2[4] = mark;
				else if ((choice == 5) && (square2[5] == '5'))
					square2[5] = mark;
				else if ((choice == 6) && (square2[6] == '6'))
					square2[6] = mark;
				else if ((choice == 7) && (square2[7] == '7'))
					square2[7] = mark;
				else if ((choice == 8) && (square2[8] == '8'))
					square2[8] = mark;
				else if ((choice == 9) && (square2[9] == '9'))
					square2[9] = mark;

				clrscr();
				turn_no++;

			}while (checkwin(square2)==-1);                                  

			if(checkwin(square2)==0)                                        
				cout<<"draw!";
			else if (checkwin(square2)==1)
				{
					board(square2);
					if (p==1)                                //player 3 won
					{
						player3.showname();
						cout<<" won!";
						p2=p3;
						player2=player3;
					}

					else if(p==2)                             //player 4 won
					{
						player4.showname();
						cout<<" won!";
						p2=p3;
						player2=player3;
					}
				}

			cout<<endl;
			player1.showname();
			cout<<" and ";
			player2.showname();
			cout<<" made it to the final!!!";

			char square3[10] = {'o','1','2','3','4','5','6','7','8','9'};       //final
			cout<<"\n\nFINAL\n\nGAME BEGINNING\n\n";
			cout<<"Welcome, ";
			player1.showname();
			cout<<" and ";
			player2.showname();
			cout<<endl;

			turn_no=1;
			do
			{
				board(square3);

				if(turn_no%2==0)
					p=2;
				else
					p=1;

				if (p==1)
					player1.showname();
				else if (p==2)
					player2.showname();

				cout<<" : Enter number to insert marker ";
				cin >> choice;
				mark=(p== 1) ? 'X' : 'O';
				if ((choice == 1) && (square3[1] == '1'))
					square3[1] = mark;
				else if ((choice == 2) && (square3[2] == '2'))
					square3[2] = mark;
				else if ((choice == 3) && (square3[3] == '3'))
					square3[3] = mark;
				else if ((choice == 4) && (square3[4] == '4'))
					square3[4] = mark;
				else if ((choice == 5) && (square3[5] == '5'))
					square3[5] = mark;
				else if ((choice == 6) && (square3[6] == '6'))
					square3[6] = mark;
				else if ((choice == 7) && (square3[7] == '7'))
					square3[7] = mark;
				else if ((choice == 8) && (square3[8] == '8'))
					square3[8] = mark;
				else if ((choice == 9) && (square3[9] == '9'))
					square3[9] = mark;

				clrscr();
				turn_no++;

			}while (checkwin(square3)==-1);                                  //code for game ends here

			if(checkwin(square3)==0)                                        //to check for winners and update wins and losses
				cout<<"draw!";
			else if (checkwin(square3)==1)
				{
					board(square);
					if (p==1)                                //player1 won
					{
						player1.showname();
						cout<<" won the tournament!";

						fin.open("records.dat", ios::binary|ios::in|ios::out);           //to update player1 details
						fin.seekg(0);
						user u;

						while(fin.read((char*)&u, sizeof(u)))
						 {
							if(u.retid()==p1)
								{
									u.twin();
									int n=fin.tellg()-sizeof(u);
									fin.seekp(n);
									fin.write((char*)&u, sizeof(u));
								}
						 }
						fin.close();
					}

					else if(p==2)                             //player 2 won
					 {
						player2.showname();
						cout<<" won the tournament!";

						fin.open("records.dat", ios::binary|ios::in|ios::out);           //to update player2 details
						fin.seekg(0);

						while(fin.read((char*)&u, sizeof(u)))
						 {
							if(u.retid()==p2)
								{
									u.twin();
									int n=fin.tellg()-sizeof(u);
									fin.seekp(n);
									fin.write((char*)&u, sizeof(u));
								}
						 }
						fin.close();
					}
				}
}
