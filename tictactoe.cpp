#include<iostream>
#include<Windows.h>
#include<time.h>
#include<cstdlib>
#include <fstream> 
#include <string>
#include <iostream>


#define SIZE 10

using namespace std;
//////////////////////////////////////////////////////////////----User's Data----//////////////////////////////////////////////////////////
fstream player1_data;
fstream player2_data;

int player_1 = 1; // thông tin player 1
int player_2 = 2; // như cái trên

char tick_1 = 'X';
char tick_2 = 'O';

char boardshow[SIZE][SIZE]; //cái này để hiện thị x o
int boardscore[SIZE][SIZE] = { 0 }; // cái này để biểu diễn thông tin người chơi trên mỗi ô, có giá trị = 1 với player 1 và = 2 với player 2


///////////////////////////////////////////////////-------------Functions Declaration--------------///////////////////////////////////////////
void initboard();							// khởi tạo giá trị cho mỗi ô là một dấu cách để bảng đỡ bị lệch
void printboard();							// in bảng
int check(int(*arr)[SIZE], int n);			// kiểm tra điều kiện thắng.
void ticking(int turn);						// yêu cầu lượt chơi tới 2 người chơi (đánh dấu vào ô nào)
void menu();								// tạo game menu
void inline player1_turn();					//Lượt đi của người chơi 1
void inline player2_turn();					//Lượt đi của người chơi 2
void inline gameplay_p2p();					//Gọi hàm lượt đi của 2 players đến khi win 
void inline man_turn();
void inline bot_turn_newbie();
void ticking_bot_newbie();
void inline gameplay_p2c_newbie();
void inline bot_turn_normal();
void ticking_bot_normal();
void inline gameplay_p2c_normal();
bool isRemainedMove(int(*arr)[SIZE], int n);
int accumulate_point(int(*arr)[SIZE], int n);
int minimax(int(*arr)[SIZE], int n, int depth, bool isBot);
void ticking_bot_expert();
void inline bot_turn_expert();
void inline gameplay_p2c_expert();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//------------main and menu-------------//
int main()
{
	menu();
	system("pause");
	return 0;
}
void menu()
{
	system("CLS");
	cout << endl << "----------------------------Tic Tac Toe Game-----------------------------------";
	cout << endl << "\tPress the corresponding number to choose!";
	cout << endl << "\t1. Play with other player";
	cout << endl << "\t2. Play with bot";
	cout << endl << "\t3. Replay";
	cout << endl << "\t4. Player's information";
	cout << endl << "\t5. Guild";
	cout << endl << "\t6. Exit\n";
	int choice = 0;  cin >> choice;
	switch (choice)
	{
	case 1:
		initboard();
		printboard();
		gameplay_p2p();
		break;
	case 2:
	{
		cout << endl << "\t\tYou have chosen play with bot. Please choose the bot level!";
		cout << endl << "\t\t\t 1. Easy.";
		cout << endl << "\t\t\t 2. Normal.";
		cout << endl << "\t\t\t 3. Hard.";
		cout << endl << "\t\t\t 0. Back to the main menu.\n";
		int subchoice; cin >> subchoice;
		switch (subchoice)
		{
		case 1:
			initboard();
			printboard();
			gameplay_p2c_newbie();
			break;
		case 2:
			initboard();
			printboard();
			gameplay_p2c_normal();
			break;
		case 3:
			initboard();
			printboard();
			gameplay_p2c_expert();
			break;
		case 0:
			menu();
			break;
		default:
			cout << "Please enter a valid choice(1, 2, 3 or 0)\n";
		}
		break;
	}
	case 3:
		cout << endl << "\t\tYou have chosen replaying the previous match!";
		break;
	case 4:
		cout << endl << "\t\tPlayers Informaltion: ";
		cout << endl << "\t\t";
		break;
	case 5:
		cout << endl << "\t\t-------------------Game Guild----------------------";
		cout << endl << "\t\tShow game guild here";
		break;
	case 6:
		exit(1);
	default:
		cout << "Please enter a valid choice(1, 2 or 3)\n";
		system("pause");
		menu();
	}
}



//****************Board****************//
void initboard()
{
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
		{
			boardshow[i][j] = ' ';
			boardscore[i][j] = 0;
		}
			
	return;
}
void printboard()
{
	system("CLS");
	cout << "\n\n\n\n";
	cout << "\t\t\t\t   1     2     3     4     5     6     7     8     9     10  \n";
	cout << "\t\t\t\t+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+\n";
	cout << "\t\t\t\t|     |     |     |     |     |     |     |     |     |     |\n";
	cout << "\t\t\t      1 |  " << boardshow[0][0] << "  |  " << boardshow[0][1] << "  |  " << boardshow[0][2] << "  |  " << boardshow[0][3] << "  |  " << boardshow[0][4] << "  |  " << boardshow[0][5] << "  |  " << boardshow[0][6] << "  |  " << boardshow[0][7] << "  |  " << boardshow[0][8] << "  |  " << boardshow[0][9] << "  |\n";
	cout << "\t\t\t\t|     |     |     |     |     |     |     |     |     |     |\n";

	cout << "\t\t\t\t+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+\n";
	cout << "\t\t\t\t|     |     |     |     |     |     |     |     |     |     |\n";
	cout << "\t\t\t      2 |  " << boardshow[1][0] << "  |  " << boardshow[1][1] << "  |  " << boardshow[1][2] << "  |  " << boardshow[1][3] << "  |  " << boardshow[1][4] << "  |  " << boardshow[1][5] << "  |  " << boardshow[1][6] << "  |  " << boardshow[1][7] << "  |  " << boardshow[1][8] << "  |  " << boardshow[1][9] << "  |\n";
	cout << "\t\t\t\t|     |     |     |     |     |     |     |     |     |     |\n";
	cout << "\t\t\t\t+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+\n";
	cout << "\t\t\t\t|     |     |     |     |     |     |     |     |     |     |\n";
	cout << "\t\t\t      3 |  " << boardshow[2][0] << "  |  " << boardshow[2][1] << "  |  " << boardshow[2][2] << "  |  " << boardshow[2][3] << "  |  " << boardshow[2][4] << "  |  " << boardshow[2][5] << "  |  " << boardshow[2][6] << "  |  " << boardshow[2][7] << "  |  " << boardshow[2][8] << "  |  " << boardshow[2][9] << "  |\n";
	cout << "\t\t\t\t|     |     |     |     |     |     |     |     |     |     |\n";
	cout << "\t\t\t\t+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+\n";
	cout << "\t\t\t\t|     |     |     |     |     |     |     |     |     |     |\n";
	cout << "\t\t\t      4 |  " << boardshow[3][0] << "  |  " << boardshow[3][1] << "  |  " << boardshow[3][2] << "  |  " << boardshow[3][3] << "  |  " << boardshow[3][4] << "  |  " << boardshow[3][5] << "  |  " << boardshow[3][6] << "  |  " << boardshow[3][7] << "  |  " << boardshow[3][8] << "  |  " << boardshow[3][9] << "  |\n";
	cout << "\t\t\t\t|     |     |     |     |     |     |     |     |     |     |\n";
	cout << "\t\t\t\t+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+\n";
	cout << "\t\t\t\t|     |     |     |     |     |     |     |     |     |     |\n";
	cout << "\t\t\t      5 |  " << boardshow[4][0] << "  |  " << boardshow[4][1] << "  |  " << boardshow[4][2] << "  |  " << boardshow[4][3] << "  |  " << boardshow[4][4] << "  |  " << boardshow[4][5] << "  |  " << boardshow[4][6] << "  |  " << boardshow[4][7] << "  |  " << boardshow[4][8] << "  |  " << boardshow[4][9] << "  |\n";
	cout << "\t\t\t\t|     |     |     |     |     |     |     |     |     |     |\n";
	cout << "\t\t\t\t+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+\n";
	cout << "\t\t\t\t|     |     |     |     |     |     |     |     |     |     |\n";
	cout << "\t\t\t      6 |  " << boardshow[5][0] << "  |  " << boardshow[5][1] << "  |  " << boardshow[5][2] << "  |  " << boardshow[5][3] << "  |  " << boardshow[5][4] << "  |  " << boardshow[5][5] << "  |  " << boardshow[5][6] << "  |  " << boardshow[5][7] << "  |  " << boardshow[5][8] << "  |  " << boardshow[5][9] << "  |\n";
	cout << "\t\t\t\t|     |     |     |     |     |     |     |     |     |     |\n";

	cout << "\t\t\t\t+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+\n";
	cout << "\t\t\t\t|     |     |     |     |     |     |     |     |     |     |\n";
	cout << "\t\t\t      7 |  " << boardshow[6][0] << "  |  " << boardshow[6][1] << "  |  " << boardshow[6][2] << "  |  " << boardshow[6][3] << "  |  " << boardshow[6][4] << "  |  " << boardshow[6][5] << "  |  " << boardshow[6][6] << "  |  " << boardshow[6][7] << "  |  " << boardshow[6][8] << "  |  " << boardshow[6][9] << "  |\n";
	cout << "\t\t\t\t|     |     |     |     |     |     |     |     |     |     |\n";
	cout << "\t\t\t\t+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+\n";
	cout << "\t\t\t\t|     |     |     |     |     |     |     |     |     |     |\n";
	cout << "\t\t\t      8 |  " << boardshow[7][0] << "  |  " << boardshow[7][1] << "  |  " << boardshow[7][2] << "  |  " << boardshow[7][3] << "  |  " << boardshow[7][4] << "  |  " << boardshow[7][5] << "  |  " << boardshow[7][6] << "  |  " << boardshow[7][7] << "  |  " << boardshow[7][8] << "  |  " << boardshow[7][9] << "  |\n";
	cout << "\t\t\t\t|     |     |     |     |     |     |     |     |     |     |\n";
	cout << "\t\t\t\t+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+\n";
	cout << "\t\t\t\t|     |     |     |     |     |     |     |     |     |     |\n";
	cout << "\t\t\t      9 |  " << boardshow[8][0] << "  |  " << boardshow[8][1] << "  |  " << boardshow[8][2] << "  |  " << boardshow[8][3] << "  |  " << boardshow[8][4] << "  |  " << boardshow[8][5] << "  |  " << boardshow[8][6] << "  |  " << boardshow[8][7] << "  |  " << boardshow[8][8] << "  |  " << boardshow[8][9] << "  |\n";
	cout << "\t\t\t\t|     |     |     |     |     |     |     |     |     |     |\n";
	cout << "\t\t\t\t+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+\n";
	cout << "\t\t\t\t|     |     |     |     |     |     |     |     |     |     |\n";
	cout << "\t\t\t      10|  " << boardshow[9][0] << "  |  " << boardshow[9][1] << "  |  " << boardshow[9][2] << "  |  " << boardshow[9][3] << "  |  " << boardshow[9][4] << "  |  " << boardshow[9][5] << "  |  " << boardshow[9][6] << "  |  " << boardshow[9][7] << "  |  " << boardshow[9][8] << "  |  " << boardshow[9][9] << "  |\n";
	cout << "\t\t\t\t|     |     |     |     |     |     |     |     |     |     |\n";
	cout << "\t\t\t\t+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+\n";
}



//***************Gameplay***************//
int check(int(*arr)[SIZE], int n)
{
	int game = -1;
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < n; j++) {
			if ((arr[i][j] == 1 && arr[i][j] == arr[i + 1][j] && arr[i + 1][j] == arr[i + 2][j] && arr[i + 2][j] == arr[i + 3][j] && arr[i + 3][j] == arr[i + 4][j]))
				game = 1;
			if (arr[i][j] == 2 && arr[i + 1][j] == 2 && arr[i + 2][j] == 2 && arr[i + 3][j] == 2 && arr[i + 4][j] == 2)
				game = 2;
		}

	for (int i = 0; i < n; i++)
		for (int j = 0; j < 6; j++) {
			if (arr[i][j] == 1 && arr[i][j + 1] == 1 && arr[i][j + 2] == 1 && arr[i][j + 3] == 1 && arr[i][j + 4] == 1)
				game = 1;
			if (arr[i][j] == 2 && arr[i][j + 1] == 2 && arr[i][j + 2] == 2 && arr[i][j + 3] == 2 && arr[i][j + 4] == 2)
				game = 2;
		}

	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 6; j++) {
			if ((arr[j][i] == 1 && arr[j + 1][i + 1] == 1 && arr[j + 2][i + 2] == 1 && arr[j + 3][i + 3] == 1 && arr[j + 4][i + 4] == 1) ||
				(arr[j][i + 4] == 1 && arr[j + 1][i + 3] == 1 && arr[j + 2][i + 2] == 1 && arr[j + 3][i + 1] == 1 && arr[j + 4][i] == 1))
				game = 1;
			if ((arr[j][i] == 2 && arr[j + 1][i + 1] == 2 && arr[j + 2][i + 2] == 2 && arr[j + 3][i + 3] == 2 && arr[j + 4][i + 4] == 2) ||
				(arr[j][i + 4] == 2 && arr[j + 1][i + 3] == 2 && arr[j + 2][i + 2] == 2 && arr[j + 3][i + 1] == 2 && arr[j + 4][i] == 2))
				game = 2;
		}
	return game;
}
void ticking(int turn)
{
	cout << "Enter your ticking coordinates (by the format: x y):  "; int r, c; cin >> r >> c;
	r--; c--; //vì tọa độ nhập vào là từ 1 đến 10 nên cần trừ đi 1 để xử lý
	if (r >= 0 && r < 10 && c>=0 && c < 10)
	{
		if (boardshow[r][c] == ' ')
		{
			if (turn == player_1)
			{
				boardscore[r][c] = player_1;
				boardshow[r][c] = tick_1;
			}
			else 
			{
				boardscore[r][c] = player_2;
				boardshow[r][c] = tick_2;
			}
		}
		else {
			cout << "Please choose an empty cell!" << endl;
			ticking(turn); // gọi lại hàm ticking cho đến khi nhập vào 1 ô hợp lý
		}
	}
	else {
		cout << "Please choose a valid cell!" << endl;
		ticking(turn); // gọi lại hàm ticking cho đến khi nhập vào 1 ô hợp lý
	}
}

//////////////////////////////////////////////////////////////----Chơi với người----//////////////////////////////////////////////////////////


void inline player1_turn()
{
	system("CLS");
	
	// player1_data.open("player1_data.txt", ios::out);
	// string player1_name;
	// cout << "Enter your name to begin: ";
	// cin.ignore(); getline(cin, player1_name);
	// player1_data << "Player1's Name: " << player1_name;
	printboard();
	cout << "Player 1 [X] Your Turn \n";
	ticking(player_1);
}
void inline player2_turn()
{
	system("CLS");
	printboard();
	cout << "Player 2 [O] Your Turn\n";
	ticking(player_2);
}
void inline gameplay_p2p()
{
	string player1_name, player2_name;
	cout << "Enter name of player 1: " << endl;
	cin.ignore();
	getline(cin, player1_name);
	cout << "Enter name of player 2: " << endl;
	getline(cin, player2_name);
	cin.ignore();

	for (int i = 0; i < 50; i++)
	{
		player1_turn();
		player1_data.open("player1_data.txt", ios::out);
		player1_data << "Player1's Name: " << player1_name;
		player1_data << endl;
		if (i > 3)
		{
			if (check(boardscore, SIZE) == player_1)
			{
				system("CLS");
				printboard();
				cout << "\n\t\t\t\tCongrats! Player 1 Won the Game!\n";
				player1_data << "Player 1 Won the Game!" << endl;
				cout << "\n\t\t\t\t";
				system("pause");
				menu();
			}
		}
		if (i == 49){
			system("CLS");
			printboard();
			cout << "\n\t\t\t\tGame Tied!\n";
			system("pause");
			menu();
		}
		player2_turn();
		player2_data.open("player2_data.txt", ios::out);
		player2_data << "Player2's Name: " << player2_name;
		player2_data << endl;
		if (i > 3)
		{
			if (check(boardscore, SIZE) == player_2)
			{
				system("CLS");
				printboard();
				cout << "\n\t\t\t\tCongrats! Player 2 Won the Game!\n";
				player2_data << "Player 2 Won the Game!" << endl;
				cout << "\n\t\t\t\t";
				system("pause");
				menu();
			}
		}
		player1_data.close();
		player2_data.close();
	}
}



//////////////////////////////////////////////////////////////----Chơi với máy----///////////////////////////////////////////////////////////

void inline man_turn()
{
	system("CLS");
	printboard();
	cout << "Your Turn\n";
	ticking(player_1);
}

//*************** Máy dễ nhất****************//
void inline bot_turn_newbie()
{
	system("CLS");
	printboard();
	ticking_bot_newbie();
}
void ticking_bot_newbie()
{
	int r, c;
	r = rand() % 10;
	c = rand() % 10;
	if (boardshow[r][c] == ' ')
	{
		boardscore[r][c] = player_2;
		boardshow[r][c] = tick_2;
	} else ticking_bot_newbie(); // gọi lại hàm ticking cho đến khi nhập vào 1 ô hợp lý
}
void inline gameplay_p2c_newbie()
{
	for (int i = 0; i < 50; i++)
	{
		man_turn();
		if (i > 3)
		{
			if (check(boardscore, SIZE) == player_1)
			{
				system("CLS");
				printboard();
				cout << "\n\t\t\t\tCongrats! You Won the Game!\n";
				cout << "\n\t\t\t\t";
				system("pause");
				menu();
			}
		}
		if (i == 49) {
			system("CLS");
			printboard();
			cout << "\n\t\t\t\tGame Tied!\n";
			system("pause");
			menu();
		}
		bot_turn_newbie();
		if (i > 3)
		{
			if (check(boardscore, SIZE) == player_2)
			{
				system("CLS");
				printboard();
				cout << "\n\t\t\t\tOpps! You lose!\n";
				cout << "\n\t\t\t\t";
				system("pause");
				menu();
			}
		}
	}
}



//****************Máy trung bình****************//
void inline bot_turn_normal()
{
	system("CLS");
	printboard();
	ticking_bot_normal();
}
void ticking_bot_normal()
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			if (boardscore[i][j] == 0) continue;
			else if (boardscore[i][j] == 1)
				/*if (j < 9 && boardscore[i][j + 1] == 0) { boardscore[i][j + 1] = player_2; boardshow[i][j + 1] = tick_2; return; }
				else if (j > 0 && boardscore[i][j - 1] == 0) { boardscore[i][j - 1] = player_2; boardshow[i][j - 1] = tick_2; return;}
				else if (i > 0 &&boardscore[i - 1][j] == 0) { boardscore[i - 1][j] = player_2; boardshow[i - 1][j] = tick_2; return;}
				else if ( i < 9 && boardscore[i + 1][j] == 0) { boardscore[i + 1][j] = player_2; boardshow[i + 1][j] = tick_2; return;}
				else if (i > 0 && j > 0 && boardscore[i - 1][j - 1] == 0) { boardscore[i - 1][j - 1] = player_2; boardshow[i - 1][j - 1] = tick_2; return;}
				else if (i < 9 && j > 0 && boardscore[i + 1][j - 1] == 0) { boardscore[i + 1][j - 1] = player_2; boardshow[i + 1][j - 1] = tick_2; return;}
				else if (i > 0 && j < 9 && boardscore[i - 1][j + 1] == 0) { boardscore[i - 1][j + 1] = player_2; boardshow[i - 1][j + 1] = tick_2; return;}
				else if (i < 9 && j < 9 && boardscore[i + 1][j + 1] == 0) { boardscore[i + 1][j + 1] = player_2; boardshow[i + 1][j + 1] = tick_2; return;}*/

				if (
					(j < 9 && boardscore[i][j + 1] == 0)
					|| (j > 0 && boardscore[i][j - 1] == 0)
					|| (i > 0 && boardscore[i - 1][j] == 0)
					|| (i < 9 && boardscore[i + 1][j] == 0)
					|| (i > 0 && j > 0 && boardscore[i - 1][j - 1] == 0)
					|| (i < 9 && j > 0 && boardscore[i + 1][j - 1] == 0)
					|| (i > 0 && j < 9 && boardscore[i - 1][j + 1] == 0)
					|| (i < 9 && j < 9 && boardscore[i + 1][j + 1] == 0)
					)
				{
					int r = 0 , c = 0;
					do
					{
						r = -1 + rand() % 3;
						c = -1 + rand() % 3;
					} while (boardscore[i+r][j+c] == 1 || boardscore[i + r][j + c] == 2 || i + r < 0 || i + r > 9 || j + c < 0 || j + c > 9 );
					boardscore[i + r][j + c] = player_2;
					boardshow[i + r][j + c] = tick_2;
					return;
				} else continue;
			else continue;
}
void inline gameplay_p2c_normal() 
{
	for (int i = 0; i < 50; i++)
	{
		man_turn();
		if (i > 3)
		{
			if (check(boardscore, SIZE) == player_1)
			{
				system("CLS");
				printboard();
				cout << "\n\t\t\t\tCongrats! You Won the Game!\n";
				cout << "\n\t\t\t\t";
				system("pause");
				menu();
			}
		}
		if (i == 49) {
			system("CLS");
			printboard();
			cout << "\n\t\t\t\tGame Tied!\n";
			system("pause");
			menu();
		}
		bot_turn_normal();
		if (i > 3)
		{
			if (check(boardscore, SIZE) == player_2)
			{
				system("CLS");
				printboard();
				cout << "\n\t\t\t\tOpps! You lose!\n";
				cout << "\n\t\t\t\t";
				system("pause");
				menu();
			}
		}
	}
}



//****************Máy khó nhất*****************//
bool isRemainedMove(int(*arr)[SIZE], int n)
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			if (arr[i][j] == 0) return true;
	return false;
}
int accumulate_point(int(*arr)[SIZE], int n)
{
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < n; j++) 
		{
			if ((arr[i][j] == 1 && arr[i][j] == arr[i + 1][j] && arr[i + 1][j] == arr[i + 2][j] && arr[i + 2][j] == arr[i + 3][j] && arr[i + 3][j] == arr[i + 4][j]))
				return -10;
 			if (arr[i][j] == 2 && arr[i + 1][j] == 2 && arr[i + 2][j] == 2 && arr[i + 3][j] == 2 && arr[i + 4][j] == 2)
				return +10;
		}

	for (int i = 0; i < n; i++)
		for (int j = 0; j < 6; j++) 
		{
			if (arr[i][j] == 1 && arr[i][j + 1] == 1 && arr[i][j + 2] == 1 && arr[i][j + 3] == 1 && arr[i][j + 4] == 1)
				return -10;
			if (arr[i][j] == 2 && arr[i][j + 1] == 2 && arr[i][j + 2] == 2 && arr[i][j + 3] == 2 && arr[i][j + 4] == 2)
				return +10;
		}

	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 6; j++) 
		{
			if ((arr[j][i] == 1 && arr[j + 1][i + 1] == 1 && arr[j + 2][i + 2] == 1 && arr[j + 3][i + 3] == 1 && arr[j + 4][i + 4] == 1) ||
				(arr[j][i + 4] == 1 && arr[j + 1][i + 3] == 1 && arr[j + 2][i + 2] == 1 && arr[j + 3][i + 1] == 1 && arr[j + 4][i] == 1))
				return -10;
			if ((arr[j][i] == 2 && arr[j + 1][i + 1] == 2 && arr[j + 2][i + 2] == 2 && arr[j + 3][i + 3] == 2 && arr[j + 4][i + 4] == 2) ||
				(arr[j][i + 4] == 2 && arr[j + 1][i + 3] == 2 && arr[j + 2][i + 2] == 2 && arr[j + 3][i + 1] == 2 && arr[j + 4][i] == 2))
				return +10;
		}
	return 0;
}
int minimax(int(*arr)[SIZE], int n, int depth, bool isBot)
{
	int score = accumulate_point(arr, SIZE);
	if (score == 10 || score == -10) return score;
	if (isRemainedMove(arr, SIZE) == false) return 0;
	if (isBot)
	{
		int best = -100;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (arr[i][j] == 0)
				{
					arr[i][j] = player_2;
					best = max(best, minimax(arr, SIZE, depth + 1, !isBot));
					arr[i][j] = 0;
				}
				else continue;
			}
		}
		return best;
	}
	else {
		int best = 100;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (arr[i][j] == 0)
				{
					arr[i][j] = player_1;
					best = min(best, minimax(arr, SIZE, depth + 1, !isBot));
					arr[i][j] = 0;
				}
				else continue;
			}
		}
		return best;
	}
	return 0;
}
void ticking_bot_expert()
{
	int r = -1, c = -1;
	int best = -100;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (boardscore[i][j] == 0)
			{
				boardscore[i][j] = player_2;
				int movePoint = minimax(boardscore, 10, 0, false);
				boardscore[i][j] = 0;

				if (movePoint > best)
				{
					r = i; c = j;
					best = movePoint;
				}
			}
		}
	}
	boardscore[r][c] = player_2;
	boardshow[r][c] = tick_2;
	return;
}
void inline bot_turn_expert()
{
	system("CLS");
	printboard();
	ticking_bot_expert();
}
void inline gameplay_p2c_expert() 
{
	for (int i = 0; i < 50; i++)
	{
		man_turn();
		if (i > 3)
		{
			if (check(boardscore, SIZE) == player_1)
			{
				system("CLS");
				printboard();
				cout << "\n\t\t\t\tCongrats! You Won the Game!\n";
				cout << "\n\t\t\t\t";
				system("pause");
				menu();
			}
		}
		if (i == 49) {
			system("CLS");
			printboard();
			cout << "\n\t\t\t\tGame Tied!\n";
			system("pause");
			menu();
		}
		bot_turn_expert();
		if (i > 3)
		{
			if (check(boardscore, SIZE) == player_2)
			{
				system("CLS");
				printboard();
				cout << "\n\t\t\t\tOpps! You loose!\n";
				cout << "\n\t\t\t\t";
				system("pause");
				menu();
			}
		}
	}
}