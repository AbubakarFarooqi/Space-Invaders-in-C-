#include <iostream>
#include <fstream>
#include <conio.h>
#include <iomanip>
#include <cmath>
#include <windows.h>
using namespace std;
// .......................Color Handle.........................

HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
//............................STRUCTURES.................................
struct enemy
{
    int x1;
    int y1;
    int x2;
    int y2;
    bool flag = 1;
};
struct enemyFire
{
    int x;
    int y;
    bool flag = 0;
};
struct gamer
{
    string name;
    int score;
    gamer *next = NULL;
};
//............................DATA STRUCTURES.................................

char Border[36][35];
enemy Enemies[24];
enemyFire EnemyFire[4];
gamer *Head = NULL;

//.....................................Flags & Control Variables..............

int EnemyMovementFlag = 0;
int ShipFireFlag = 0;
int ShipNextFireFlag = 1;
bool EnemyFireMovementFlag = 1;
bool isFinalEnemy = 0;
int Life = 3;
int FireCount = 0;
int Score = 0;
int FinalEnemyLives = 15;
//............................Variables for Space Ship.......................

int S1_x = 11;
int S1_y = 32;
int S2_x = 12;
int S2_y = 31;
int S3_x = 13;
int S3_y = 32;
int S_Fire_x;
int S_Fire_y;
//............................................................................

//............................Variables for Final Enemy.......................

int Fx = 10;
int Fy = 11;
int FEF_x_1;
int FEF_x_2;
int FEF_x_3;
int FEF_x_4;
int FEF_y_1;
int FEF_y_2;
int FEF_y_3;
int FEF_y_4;
bool FinalEnemyFireFlag = 1;
bool FinalEnemyFireMovementFlag = 0;
//............................................................................

//.........................Functions Prototypes...............................

gamer *getLastRecord(gamer *temp);
gamer *AddDataInList(string name);
gamer *InputData();
gamer *SearchUserNameInList(string name, bool &isfound);
string ExtractionOfField(string source, int field);
void FillingListFromFile(string name, int score);
void ExtractingUserFile();
void Header();
void GameStartingStory();
char Menu();
void ResetShipPosition();
void ResetAllValues();
void LoadBorderFromFile();
void gotoxy(int x, int y);
void GameOpeningScreen();
void DisplayShip();
void DisplayBorders();
void DisplayFinalEnemy();
void FinalEnemyRandomMovement();
void ChkFinalEnemyFire();
void FinalEnemyFireMovement();
void MovementInEnemies();
void MovementInShip();
void ChkShipFire();
int ShipFireMovement();
void WhichEnemyFire(int temp);
void ChkEnemyFire();
void EnemyFireMovement();
void DecrementInEnemyY_Axis();
void GameLose();
void DisplayStatus();
void Lvl_1_OpeningScreen();
void Lvl_2_OpeningScreen();
void Lvl_3_OpeningScreen();
void Lvl_4_OpeningScreen();
void Level_1(gamer *temp);
void Level_2(gamer *temp);
void Level_3(gamer *temp);
void Level_4(gamer *temp);
void GameWinningScreen();
void initializingEnemiesCoordinate();
void DisplayEnemies();
void ClearingEnemiesPreviousPositions();
void PutListInUserFile();
void DisplayList(gamer *list);
void SortingInList(gamer *list);
//.........................Functions Implementations...........................
void ResetFlagsAndControls()
{
    EnemyMovementFlag = 0;
    ShipFireFlag = 0;
    ShipNextFireFlag = 1;
    EnemyFireMovementFlag = 1;
    isFinalEnemy = 0;
    Life = 3;
    FireCount = 0;
    Score = 0;
    FinalEnemyLives = 15;
}
gamer *getLastRecord(gamer *temp)
{
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    return temp;
}
gamer *AddDataInList(string name)
{
    gamer *Record = new gamer;
    Record->name = name;
    if (Head == NULL)
    {
        Head = Record;
    }
    else
    {
        gamer *temp = getLastRecord(Head);
        temp->next = Record;
    }
    return Record;
}
gamer *InputData()
{
    string name;
    cout << "ENter NAme of Player : ";
    cin >> name;
    return AddDataInList(name);
}
gamer *SearchUserNameInList(string name, bool &isfound)
{
    gamer *temp = Head;
    if (Head == NULL)
    {
        isfound = 0;
        return NULL;
    }
    while (1)
    {
        if (temp->name == name)
        {
            isfound = 1;
            return temp;
        }
        if (temp->next == NULL)
            break;
        temp = temp->next;
    }
    isfound = 0;
    return NULL;
}
string ExtractionOfField(string source, int field)
{
    int comma = 1;
    string retrn = "";
    for (int i = 0; i < source.length(); i++)
    {
        if (source[i] == ',')
        {
            comma++;
            i++;
        }
        if (comma == field)
            retrn = retrn + source[i];
    }
    return retrn;
}
void FillingListFromFile(string name, int score)
{
    gamer *Record = new gamer;
    Record->name = name;
    Record->score = score;
    if (Head == NULL)
    {
        Head = Record;
    }
    else
    {
        gamer *temp = getLastRecord(Head);
        temp->next = Record;
    }
}
void ExtractingUserFile()
{
    fstream file("users.txt", ios ::in);
    // chcking file is empty or not
    char chk;
    file >> chk;
    if (!file.eof())
    {
        file.seekg(0, ios::beg);
        string temp;
        while (1)
        {
            getline(file, temp);
            if (file.eof())
                break;
            string name;
            int score;
            name = ExtractionOfField(temp, 1);
            score = stoi(ExtractionOfField(temp, 2));
            FillingListFromFile(name, score);
        }
    }
}
void Header()
{
    system("cls");
    SetConsoleTextAttribute(color, 12);
    cout << "///////////////////////////////////////////////" << endl;
    SetConsoleTextAttribute(color, 11);
    cout << "                Space Invaders                " << endl;
    SetConsoleTextAttribute(color, 12);
    cout << "///////////////////////////////////////////////" << endl;
}
void GameStartingStory()
{
    DisplayFinalEnemy();
    cout << endl
         << endl;
    fstream file("story.txt", ios::in);
    string temp;
    int line = 1;
    int character = 1;
    while (!file.eof())
    {
        getline(file, temp);
        for (int i = 0; i < temp.length(); i++)
        {
            if (line == 1 && character >= 4 && character <= 9)
                SetConsoleTextAttribute(color, 12);
            else if (line == 3 && character >= 30 && character <= 34)
                SetConsoleTextAttribute(color, 10);
            else if (line == 5)
                SetConsoleTextAttribute(color, 12);
            else
                SetConsoleTextAttribute(color, 15);
            cout << temp[i];
            Sleep(50);
            character++;
        }
        SetConsoleTextAttribute(color, 15);
        cout << endl;
        line++;
        character = 1;
    }
    getch();
}
char Menu()
{
    cout << endl
         << endl;
    SetConsoleTextAttribute(color, 14);
    cout << "..............................................." << endl;
    cout << "......................MENU....................." << endl
         << endl;
    SetConsoleTextAttribute(color, 15);
    cout << "1. Play Game" << endl;
    cout << "2. High Scores" << endl;
    cout << "3. Load Game" << endl;
    cout << "4. Exit" << endl
         << endl;
    SetConsoleTextAttribute(color, 10);
    cout << "Your Option...";
    char option;
    cin >> option;
    return option;
}
void ResetShipPosition()
{
    S1_x = 11;
    S1_y = 32;
    S2_x = 12;
    S2_y = 31;
    S3_x = 13;
    S3_y = 32;
}
void ResetAllValues()
{
    EnemyMovementFlag = 0;
    ShipFireFlag = 0;
    ShipNextFireFlag = 1;
    EnemyFireMovementFlag = 1;
    // FireCount = 0;
    initializingEnemiesCoordinate();
    for (int i = 0; i < 4; i++)
    {
        EnemyFire[i].flag = 0;
    }
    S1_x = 11;
    S1_y = 32;
    S2_x = 12;
    S2_y = 31;
    S3_x = 13;
    S3_y = 32;
}
void LoadBorderFromFile()
{
    fstream file("Borders.txt", ios::in);
    for (int i = 0; i < 36; i++)
    {
        string temp;
        getline(file, temp);
        for (int j = 0; j < 35; j++)
        {
            Border[i][j] = temp[j];
        }
    }
}
void gotoxy(int x, int y)
{
    COORD cursorPosition;
    cursorPosition.X = x;
    cursorPosition.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}
void GameOpeningScreen()
{
    SetConsoleTextAttribute(color, 10);
    cout << "\t\t\t\t\t\t\t\tPlay" << endl
         << endl;
    SetConsoleTextAttribute(color, 15);
    cout << "\t\t\t\t\t\t\t   S";
    Sleep(150);
    cout << "p";
    Sleep(150);
    cout << "a";
    Sleep(150);
    cout << "c";
    Sleep(150);
    cout << "e";
    cout << "   ";
    Sleep(150);
    SetConsoleTextAttribute(color, 12);
    cout << "I";
    Sleep(150);
    cout << "n";
    Sleep(150);
    cout << "v";
    Sleep(150);
    cout << "a";
    Sleep(150);
    cout << "d";
    Sleep(150);
    cout << "e";
    Sleep(150);
    cout << "r";
    Sleep(150);
    cout << "s";
    cout << endl
         << endl
         << endl;
    SetConsoleTextAttribute(color, 11);
    cout << "\t\t\t\t\t\t\t< Score Advance Table >" << endl;
    SetConsoleTextAttribute(color, 14);
    cout << "\t\t\t\t\t\t\t\t++ = " << endl
         << "\t\t\t\t\t\t\t\t-- = " << endl
         << "\t\t\t\t\t\t\t\t** = " << endl
         << "\t\t\t\t\t\t\t\t() = " << endl;
    gotoxy(70, 6);
    cout << "1";
    Sleep(250);
    cout << "0";
    gotoxy(70, 7);
    cout << "2";
    Sleep(250);
    cout << "0";
    gotoxy(70, 8);
    cout << "3";
    Sleep(250);
    cout << "0";
    gotoxy(70, 9);
    cout << "4";
    Sleep(250);
    cout << "0";
    Sleep(300);
}
void DisplayShip()
{
    SetConsoleTextAttribute(color, 15);
    gotoxy(S1_x, S1_y);
    cout << "<";
    gotoxy(S2_x, S2_y);
    cout << "^";
    gotoxy(S3_x, S3_y);
    cout << ">";
}
void DisplayBorders()
{
    for (int i = 0; i < 36; i++)
    {
        for (int j = 0; j < 35; j++)
        {
            cout << Border[i][j];
        }
        cout << endl;
    }
}
void DisplayFinalEnemy()
{
    SetConsoleTextAttribute(color, 12);
    gotoxy(Fx, Fy);
    cout << "/";
    gotoxy(Fx + 1, Fy - 1);
    cout << "-";
    gotoxy(Fx + 2, Fy - 3);
    cout << "-^^^-";
    gotoxy(Fx + 2, Fy - 2);
    cout << "|O O|";
    gotoxy(Fx + 2, Fy - 1);
    cout << "| > |-";
    gotoxy(Fx + 2, Fy);
    cout << "| - | \\";
    gotoxy(Fx + 2, Fy + 1);
    cout << "-----";
}
void FinalEnemyRandomMovement()
{
    gotoxy(Fx, Fy);
    cout << " ";
    gotoxy(Fx + 1, Fy - 1);
    cout << " ";
    gotoxy(Fx + 2, Fy - 3);
    cout << "     ";
    gotoxy(Fx + 2, Fy - 2);
    cout << "     ";
    gotoxy(Fx + 2, Fy - 1);
    cout << "      ";
    gotoxy(Fx + 2, Fy);
    cout << "       ";
    gotoxy(Fx + 2, Fy + 1);
    cout << "     ";
    Fx = 1 + rand() % 25;
    Fy = 4 + rand() % 23;
}
void ChkFinalEnemyFire()
{
    if (FinalEnemyFireFlag)
    {
        FEF_x_1 = Fx;
        FEF_y_1 = Fy + 1;
        FEF_x_2 = Fx + 2;
        FEF_y_2 = Fy + 2;
        FEF_x_3 = Fx + 6;
        FEF_y_3 = Fy + 2;
        FEF_x_4 = Fx + 8;
        FEF_y_4 = Fy + 1;
        FinalEnemyFireMovementFlag = 1;
        FinalEnemyFireFlag = 0;
    }
}
void FinalEnemyFireMovement()
{
    if (FinalEnemyFireMovementFlag)
    {
        gotoxy(FEF_x_1, FEF_y_1);
        cout << " ";
        gotoxy(FEF_x_2, FEF_y_2);
        cout << " ";
        gotoxy(FEF_x_3, FEF_y_3);
        cout << " ";
        gotoxy(FEF_x_4, FEF_y_4);
        cout << " ";
        FEF_y_1++;
        FEF_y_2++;
        FEF_y_3++;
        FEF_y_4++;
        if (FEF_y_1 != 33)
        {
            SetConsoleTextAttribute(color, 14);
            gotoxy(FEF_x_1, FEF_y_1);
            cout << "*";
            gotoxy(FEF_x_2, FEF_y_2);
            cout << "*";
            gotoxy(FEF_x_3, FEF_y_3);
            cout << "*";
            gotoxy(FEF_x_4, FEF_y_4);
            cout << "*";
            if ((FEF_x_1 == S1_x && FEF_y_1 == S1_y) || (FEF_x_1 == S2_x && FEF_y_1 == S2_y) || (FEF_x_1 == S3_x && FEF_y_1 == S3_y) || (FEF_x_2 == S1_x && FEF_y_2 == S1_y) || (FEF_x_2 == S2_x && FEF_y_2 == S2_y) || (FEF_x_2 == S3_x && FEF_y_2 == S3_y) || (FEF_x_3 == S1_x && FEF_y_3 == S1_y) || (FEF_x_3 == S2_x && FEF_y_3 == S2_y) || (FEF_x_3 == S3_x && FEF_y_3 == S3_y) || (FEF_x_4 == S1_x && FEF_y_4 == S1_y) || (FEF_x_4 == S2_x && FEF_y_4 == S2_y) || (FEF_x_4 == S3_x && FEF_y_4 == S3_y))
            {
                FireCount++;
                gotoxy(S1_x, S1_y);
                cout << " ";
                gotoxy(S2_x, S2_y);
                cout << " ";
                gotoxy(S3_x, S3_y);
                cout << " ";
                ResetShipPosition();
            }
        }
        else
        {
            FinalEnemyFireMovementFlag = 0;
            FinalEnemyFireFlag = 1;
        }
    }
}
void MovementInEnemies()
{
    if (Enemies[5].x2 + 1 == 34)
        EnemyMovementFlag = 1;
    if (Enemies[0].x1 - 1 == 1)
        EnemyMovementFlag = 0;
    if (EnemyMovementFlag == 0)
    {
        ClearingEnemiesPreviousPositions();
        for (int i = 0; i < 24; i++)
        {
            Enemies[i].x1++;
            Enemies[i].x2++;
        }
    }
    if (EnemyMovementFlag == 1)
    {
        ClearingEnemiesPreviousPositions();
        for (int i = 0; i < 24; i++)
        {
            Enemies[i].x1--;
            Enemies[i].x2--;
        }
    }
}
void MovementInShip()
{
    if (GetAsyncKeyState(VK_RIGHT))
    {
        if (S3_x + 1 != 34)
        {
            gotoxy(S1_x, S1_y);
            cout << " ";
            gotoxy(S2_x, S2_y);
            cout << " ";
            gotoxy(S3_x, S3_y);
            cout << " ";
            S1_x++;
            S2_x++;
            S3_x++;
        }
    }
    if (GetAsyncKeyState(VK_LEFT))
    {
        if (S1_x - 1 != 0)
        {
            gotoxy(S1_x, S1_y);
            cout << " ";
            gotoxy(S2_x, S2_y);
            cout << " ";
            gotoxy(S3_x, S3_y);
            cout << " ";
            S1_x--;
            S2_x--;
            S3_x--;
        }
    }
}
void ChkShipFire()
{
    if (ShipNextFireFlag == 1)
    {
        if (GetAsyncKeyState(VK_SPACE))
        {
            ShipFireFlag = 1;
            S_Fire_x = S2_x;
            S_Fire_y = S2_y - 1;
            ShipNextFireFlag = 0;
        }
    }
}
int ShipFireMovement()
{
    SetConsoleTextAttribute(color, 11);
    if (ShipFireFlag == 1)
    {
        for (int i = 0; i < 24; i++)
        {
            if (((S_Fire_x == Enemies[i].x1 && S_Fire_y == Enemies[i].y1) || (S_Fire_x == Enemies[i].x2 && S_Fire_y == Enemies[i].y2)) && Enemies[i].flag)
            {
                ShipFireFlag = 0;
                ShipNextFireFlag = 1;
                gotoxy(S_Fire_x, S_Fire_y);
                cout << " ";
                gotoxy(S_Fire_x + 1, S_Fire_y);
                cout << " ";
                gotoxy(S_Fire_x - 1, S_Fire_y);
                cout << " ";
                Enemies[i].flag = 0;
                if (i >= 0 && i < 6)
                    Score = Score + 40;
                if (i >= 6 && i < 12)
                    Score = Score + 30;
                if (i >= 12 && i < 18)
                    Score = Score + 20;
                if (i >= 18 && i < 24)
                    Score = Score + 10;
                return 0;
            }
        }
        if (((S_Fire_x == Fx && S_Fire_y == Fy) || (S_Fire_x == Fx + 1 && S_Fire_y == Fy - 1) || ((S_Fire_x >= Fx + 2 && S_Fire_x <= Fx + 6) && S_Fire_y == Fy + 1) || (S_Fire_x == Fx + 7 && S_Fire_y == Fy - 1) || (S_Fire_x == Fx + 8 && S_Fire_y == Fy)) && isFinalEnemy)
        {
            ShipFireFlag = 0;
            ShipNextFireFlag = 1;
            gotoxy(S_Fire_x, S_Fire_y);
            cout << " ";
            Score = Score + 50;
            FinalEnemyLives--;
        }
        else if (S_Fire_y != 1)
        {
            gotoxy(S_Fire_x, S_Fire_y);
            cout << " ";
            S_Fire_y--;
            gotoxy(S_Fire_x, S_Fire_y);
            cout << "^";
        }
        else
        {
            ShipFireFlag = 0;
            ShipNextFireFlag = 1;
            gotoxy(S_Fire_x, S_Fire_y);
            cout << " ";
        }
    }
}
void WhichEnemyFire(int temp)
{
    for (int i = 1; i <= 24; i++)
    {
        if (i == temp)
        {
            if (i >= 1 && i <= 6)
                if (!EnemyFire[0].flag)
                {
                    EnemyFire[0].x = Enemies[i - 1].x1;
                    EnemyFire[0].y = Enemies[i - 1].y1;
                    break;
                }
            if (i >= 7 && i <= 12)
                if (!EnemyFire[1].flag)
                {
                    EnemyFire[1].x = Enemies[i - 1].x1;
                    EnemyFire[1].y = Enemies[i - 1].y1;
                    break;
                }
            if (i >= 13 && i <= 18)
                if (!EnemyFire[2].flag)
                {
                    EnemyFire[2].x = Enemies[i - 1].x1;
                    EnemyFire[2].y = Enemies[i - 1].y1;
                    break;
                }
            if (i >= 19 && i <= 24)
                if (!EnemyFire[3].flag)
                {
                    EnemyFire[3].x = Enemies[i - 1].x1;
                    EnemyFire[3].y = Enemies[i - 1].y1;
                    break;
                }
        }
    }
}
void ChkEnemyFire()
{
    srand(time(0));
    int temp = 1 + rand() % 24;
    WhichEnemyFire(temp);
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 24; j++)
        {
            if (EnemyFireMovementFlag)
            {

                if ((EnemyFire[i].x == Enemies[j].x1 && EnemyFire[i].y == Enemies[j].y1 && Enemies[j].flag))
                {
                    EnemyFire[i].y++;
                    EnemyFire[i].flag = 1;
                    EnemyFireMovementFlag = 0;
                    i = 5;
                    break;
                }
            }
        }
    }
}
void EnemyFireMovement()
{
    for (int i = 0; i < 4; i++)
    {

        if (EnemyFire[i].flag)
        {
            gotoxy(EnemyFire[i].x, EnemyFire[i].y);
            cout << " ";
            EnemyFire[i].y++;
            if (EnemyFire[i].y != 33)
            {
                SetConsoleTextAttribute(color, 12);
                gotoxy(EnemyFire[i].x, EnemyFire[i].y);
                cout << "*";
                if ((EnemyFire[i].x == S1_x && EnemyFire[i].y == S1_y) || (EnemyFire[i].x == S2_x && EnemyFire[i].y == S2_y) || (EnemyFire[i].x == S3_x && EnemyFire[i].y == S3_y))
                {
                    FireCount++;
                    gotoxy(S1_x, S1_y);
                    cout << " ";
                    gotoxy(S2_x, S2_y);
                    cout << " ";
                    gotoxy(S3_x, S3_y);
                    cout << " ";
                    ResetShipPosition();
                }
            }
            else
            {
                EnemyFireMovementFlag = 1;
                EnemyFire[i].flag = 0;
            }
        }
    }
}
void DecrementInEnemyY_Axis()
{
    if (Enemies[23].y1 < 28)
    {
        for (int i = 0; i < 24; i++)
        {
            gotoxy(Enemies[i].x1, Enemies[i].y1);
            cout << " ";
            gotoxy(Enemies[i].x2, Enemies[i].y2);
            cout << " ";
            Enemies[i].y1++;
            Enemies[i].y2++;
        }
    }
    else
    {
        system("cls");
        SetConsoleTextAttribute(color, 9);
        DisplayBorders();
        ResetAllValues();
        Score = 1200;
        FireCount = 5;
    }
}
void GameLose()
{
    system("cls");
    fstream file("GameLose.txt", ios ::in);
    string temp;
    int line = 1;
    int character = 1;
    DisplayFinalEnemy();
    cout << endl;
    while (!file.eof())
    {

        getline(file, temp);
        for (int i = 0; i < temp.length(); i++)
        {
            if (line == 1 && character >= 9 && character <= 13)
                SetConsoleTextAttribute(color, 10);
            else if (line == 3 && character >= 26 && character < 30)
                SetConsoleTextAttribute(color, 12);
            else
                SetConsoleTextAttribute(color, 15);
            cout << temp[i];
            Sleep(50);
            character++;
        }
        line++;
        character = 0;
        cout << endl;
    }
    getch();
    getch();
    getch();
}
void DisplayStatus()
{
    gotoxy(40, 16);
    cout << "Score = ";
    SetConsoleTextAttribute(color, 15);
    cout << Score;
    gotoxy(40, 18);
    SetConsoleTextAttribute(color, 11);
    cout << "Lives = ";
    SetConsoleTextAttribute(color, 15);
    cout << Life;
    gotoxy(40, 20);
    SetConsoleTextAttribute(color, 11);
    cout << "Health = ";
    for (int i = 10; i >= 0; i--) // for clearing prev screen
        cout << " ";
    gotoxy(49, 20);
    SetConsoleTextAttribute(color, 10);
    for (int i = 5; i > FireCount; i--)
        cout << "|";
    if (isFinalEnemy)
    {
        gotoxy(40, 22);
        SetConsoleTextAttribute(color, 12);
        cout << "ATTIC = ";
        for (int i = 1; i <= 15; i++)
        {
            cout << " ";
        }
        gotoxy(48, 22);
        SetConsoleTextAttribute(color, 14);
        for (int i = 1; i <= FinalEnemyLives; i++)
        {
            cout << "|";
        }
        SetConsoleTextAttribute(color, 15);
    }
}
void Lvl_1_OpeningScreen()
{

    for (int i = 1; i <= 15; i++)
    {
        system("cls");
        SetConsoleTextAttribute(color, i);
        if (i == 15)
            SetConsoleTextAttribute(color, 14);
        cout << endl
             << endl
             << endl
             << endl
             << endl
             << endl
             << endl;
        cout << "                            |            ___________  \\            /  ___________   |               /|" << endl;
        cout << "                            |           |              \\          /  |              |              / |" << endl;
        cout << "                            |           |               \\        /   |              |             /  |" << endl;
        cout << "                            |           |----------      \\      /    |-----------   |                |" << endl;
        cout << "                            |           |                 \\    /     |              |                |" << endl;
        cout << "                            |           |                  \\  /      |              |                |" << endl;
        cout << "                            |_________  |__________         \\/       |___________   |__________   ________" << endl;
        Sleep(80);
    }
    SetConsoleTextAttribute(color, 15);
}
void Lvl_2_OpeningScreen()
{

    for (int i = 1; i <= 15; i++)
    {
        system("cls");
        SetConsoleTextAttribute(color, i);
        if (i == 15)
            SetConsoleTextAttribute(color, 14);
        cout << endl
             << endl
             << endl
             << endl
             << endl
             << endl
             << endl;
        cout << "                            |            ___________  \\            /  ___________   |             ________" << endl;
        cout << "                            |           |              \\          /  |              |            |        |" << endl;
        cout << "                            |           |               \\        /   |              |                     |" << endl;
        cout << "                            |           |----------      \\      /    |-----------   |              _______|" << endl;
        cout << "                            |           |                 \\    /     |              |             |" << endl;
        cout << "                            |           |                  \\  /      |              |             |" << endl;
        cout << "                            |_________  |__________         \\/       |___________   |__________   |_______|" << endl;
        Sleep(80);
    }
    SetConsoleTextAttribute(color, 15);
}
void Lvl_3_OpeningScreen()
{

    for (int i = 1; i <= 15; i++)
    {
        system("cls");
        SetConsoleTextAttribute(color, i);
        if (i == 15)
            SetConsoleTextAttribute(color, 14);
        cout << endl
             << endl
             << endl
             << endl
             << endl
             << endl
             << endl;
        cout << "                            |            ___________  \\            /  ___________   |             ________" << endl;
        cout << "                            |           |              \\          /  |              |            |        |" << endl;
        cout << "                            |           |               \\        /   |              |                     |" << endl;
        cout << "                            |           |----------      \\      /    |-----------   |              _______|" << endl;
        cout << "                            |           |                 \\    /     |              |                     |" << endl;
        cout << "                            |           |                  \\  /      |              |                     |" << endl;
        cout << "                            |_________  |__________         \\/       |___________   |__________   |_______|" << endl;
        Sleep(80);
    }
    SetConsoleTextAttribute(color, 15);
}
void Lvl_4_OpeningScreen()
{

    for (int i = 1; i <= 15; i++)
    {
        system("cls");
        SetConsoleTextAttribute(color, i);
        if (i == 15)
            SetConsoleTextAttribute(color, 14);
        cout << endl
             << endl
             << endl
             << endl
             << endl
             << endl
             << endl;
        cout << "                            |            ___________  \\            /  ___________   |                     " << endl;
        cout << "                            |           |              \\          /  |              |            |        |" << endl;
        cout << "                            |           |               \\        /   |              |            |        |" << endl;
        cout << "                            |           |----------      \\      /    |-----------   |            |________|" << endl;
        cout << "                            |           |                 \\    /     |              |                     |" << endl;
        cout << "                            |           |                  \\  /      |              |                     |" << endl;
        cout << "                            |_________  |__________         \\/       |___________   |__________           |" << endl;
        Sleep(80);
    }
    SetConsoleTextAttribute(color, 15);
}
void Level_1(gamer *temp)
{
    system("cls");
    SetConsoleTextAttribute(color, 9);
    DisplayBorders();

    while (1)
    {
        // star
        gotoxy(0, 0);
        DisplayEnemies();
        MovementInShip();
        ChkEnemyFire();
        EnemyFireMovement();
        DisplayShip();
        ChkShipFire();
        ShipFireMovement();
        DisplayStatus();
        if (FireCount == 5)
        {
            Life--;
            FireCount = 0;
        }
        if (Life == 0)
            break;
        // Score = 600;
        if (Score == 600)
        {
            temp->score = 600;
            break;
        }
    }
}
void Level_2(gamer *temp)
{
    ResetAllValues();
    system("cls");
    int SpeedControler = 1;
    int Speed = 10;
    SetConsoleTextAttribute(color, 9);
    DisplayBorders();
    while (1)
    {
        gotoxy(0, 0);
        if (SpeedControler % Speed == 0)
            MovementInEnemies();
        DisplayEnemies();
        MovementInShip();
        ChkEnemyFire();
        DisplayShip();
        ChkShipFire();
        EnemyFireMovement();
        ShipFireMovement();
        SpeedControler++;
        DisplayStatus();
        if (SpeedControler % 60 == 0)
            if (Speed > 5)
                Speed--;
        if (FireCount == 5)
        {
            Life--;
            FireCount = 0;
        }
        if (Life == 0)
            break;
        // Score = 1200;
        if (Score == 1200)
        {
            temp->score = 1200;
            break;
        }
    }
}
void Level_3(gamer *temp)
{
    int tempScore = Score;
    int SpeedControler = 1;
    int Speed = 10;
    int EnemiesVerticalDistance = 1;
    ResetAllValues();
    system("cls");
    SetConsoleTextAttribute(color, 9);
    DisplayBorders();
    while (1)
    {
        gotoxy(0, 0);
        if (EnemiesVerticalDistance % 100 == 0)
            DecrementInEnemyY_Axis();
        if (SpeedControler % Speed == 0)
            MovementInEnemies();
        DisplayEnemies();
        MovementInShip();
        ChkEnemyFire();
        EnemyFireMovement();
        DisplayShip();
        ChkShipFire();
        ShipFireMovement();
        SpeedControler++;
        DisplayStatus();
        if (SpeedControler % 60 == 0)
            if (Speed > 5)
                Speed--;
        if (FireCount == 5)
        {
            Life--;
            FireCount = 0;
        }
        if (Life == 0)
            break;
        // Score = 1800;
        if (Score == 1800)
        {
            temp->score = 1800;
            break;
        }

        EnemiesVerticalDistance++;
    }
}
void Level_4(gamer *temp)
{
    ResetAllValues();
    system("cls");
    SetConsoleTextAttribute(color, 9);
    DisplayBorders();
    int fireControl = 1;
    int fireMovement = 1;
    isFinalEnemy = 1;
    while (1)
    {
        gotoxy(0, 0);
        DisplayFinalEnemy();
        if (fireMovement % 3 == 0)
            FinalEnemyFireMovement();
        if (fireControl % 100 == 0)
        {
            FinalEnemyRandomMovement();
        }
        ChkFinalEnemyFire();
        fireControl++;
        fireMovement++;
        MovementInShip();
        DisplayShip();
        ChkShipFire();
        ShipFireMovement();
        DisplayStatus();
        if (FireCount == 5)
        {
            Life--;
            FireCount = 0;
        }
        if (Life == 0)
            break;
        if (FinalEnemyLives == 0)
        {
            temp->score = Score;
            break;
        }
    }
}
void GameWinningScreen()
{
    system("cls");
    fstream file("winmsg.txt", ios ::in);
    cout << endl
         << endl;
    gotoxy(70, 10);
    cout << "^";
    gotoxy(69, 11);
    cout << "<";
    gotoxy(71, 11);
    cout << ">";
    gotoxy(70, 12);
    cout << "*";
    gotoxy(70, 13);
    cout << "*";
    gotoxy(70, 14);
    cout << "*";
    gotoxy(70, 15);
    cout << "*";
    gotoxy(0, 3);
    int line = 1;
    int character = 1;
    string temp;
    while (!file.eof())
    {
        getline(file, temp);
        for (int i = 0; i < temp.length(); i++)
        {
            if (line == 1 && character >= 18 && character <= 25)
                SetConsoleTextAttribute(color, 10);
            else if (line == 1 && character >= 45)
                SetConsoleTextAttribute(color, 12);
            else
                SetConsoleTextAttribute(color, 15);
            cout << temp[i];
            Sleep(50);
            character++;
        }
        SetConsoleTextAttribute(color, 15);
        cout << endl;
        line++;
        character = 1;
    }

    int y1 = 11;

    int y2 = 10;

    int y3 = 11;
    for (int i = 0; i < 9; i++)
    {
        gotoxy(69, y1);
        cout << " ";
        gotoxy(70, y2);
        cout << " ";
        gotoxy(71, y3);
        cout << " ";
        gotoxy(70, y1);
        cout << "*";
        y1--;
        y2--;
        y3--;
        gotoxy(69, y1);
        cout << "<";
        gotoxy(70, y2);
        cout << "^";
        gotoxy(71, y3);
        cout << ">";
        Sleep(100);
    }
    getch();
    getch();
    getch();
}
void initializingEnemiesCoordinate()
{
    for (int i = 0; i < 24; i++)
    {
        Enemies[i].flag = 1;
        if (i >= 0 && i < 6)
        {
            Enemies[i].y1 = 5;
            Enemies[i].y2 = 5;
        }
        if (i >= 6 && i < 12)
        {
            Enemies[i].y1 = 7;
            Enemies[i].y2 = 7;
        }
        if (i >= 12 && i < 18)
        {
            Enemies[i].y1 = 9;
            Enemies[i].y2 = 9;
        }
        if (i >= 18 && i < 24)
        {
            Enemies[i].y1 = 11;
            Enemies[i].y2 = 11;
        }
    }
    for (int i = 0; i < 24; i += 6)
    {
        Enemies[i].x1 = 6;
        Enemies[i].x2 = 7;
        Enemies[i + 1].x1 = 9;
        Enemies[i + 1].x2 = 10;
        Enemies[i + 2].x1 = 12;
        Enemies[i + 2].x2 = 13;
        Enemies[i + 3].x1 = 15;
        Enemies[i + 3].x2 = 16;
        Enemies[i + 4].x1 = 18;
        Enemies[i + 4].x2 = 19;
        Enemies[i + 5].x1 = 21;
        Enemies[i + 5].x2 = 22;
    }
}
void DisplayEnemies()
{
    SetConsoleTextAttribute(color, 14);
    for (int i = 0; i < 24; i++)
    {
        if (i >= 0 && i < 6)
        {
            if (Enemies[i].flag)
            {
                gotoxy(Enemies[i].x1, Enemies[i].y1);
                cout << "(";
                gotoxy(Enemies[i].x2, Enemies[i].y2);
                cout << ")";
            }
        }
        if (i >= 6 && i < 12)
        {
            if (Enemies[i].flag)
            {
                gotoxy(Enemies[i].x1, Enemies[i].y1);
                cout << "-";
                gotoxy(Enemies[i].x2, Enemies[i].y2);
                cout << "-";
            }
        }
        if (i >= 12 && i < 18)
        {
            if (Enemies[i].flag)
            {
                gotoxy(Enemies[i].x1, Enemies[i].y1);
                cout << "*";
                gotoxy(Enemies[i].x2, Enemies[i].y2);
                cout << "*";
            }
        }
        if (i >= 18 && i < 24)
        {
            if (Enemies[i].flag)
            {
                gotoxy(Enemies[i].x1, Enemies[i].y1);
                cout << "+";
                gotoxy(Enemies[i].x2, Enemies[i].y2);
                cout << "+";
            }
        }
    }
}
void ClearingEnemiesPreviousPositions()
{
    for (int i = 0; i < 24; i++)
    {
        gotoxy(Enemies[i].x1, Enemies[i].y1);
        cout << " ";
        gotoxy(Enemies[i].x2, Enemies[i].y2);
        cout << " ";
    }
}
void PutListInUserFile()
{
    fstream file("users.txt", ios::out);
    gamer *temp = Head;
    while (1)
    {
        file << temp->name << "," << temp->score << endl;
        if (temp->next == NULL)
            break;
        temp = temp->next;
    }
    file.close();
}
void DisplayList(gamer *list)
{

    while (1)
    {
        cout << list->name << "\t" << list->score << endl;
        if (list->next == NULL)
            break;
        list = list->next;
    }
    getch();
}
void SortingInList(gamer *list)
{
    string temp_name;
    int temp_score;
    if (list != NULL)
    {
        if (list->next != NULL)
        {
            while (1)
            {
                // cout << "usman" << endl;
                gamer *temp1 = Head;
                gamer *temp2 = temp1->next;
                while (1)
                {
                    if (temp1->next == NULL)
                        break;
                    if (temp2->score > temp1->score)
                    {
                        temp_name = temp1->name;
                        temp_score = temp1->score;
                        temp1->name = temp2->name;
                        temp1->score = temp2->score;
                        temp2->name = temp_name;
                        temp2->score = temp_score;
                    }
                    temp1 = temp2;
                    temp2 = temp2->next;
                }
                if (list->next == NULL)
                    break;
                list = list->next;
            }
        }
        DisplayList(Head);
    }
    else
    {
        cout << "NO DATA FOUND";
        getch();
    }
}
//--------------------------------------------------------------------------
int main()
{

    system("cls");
    LoadBorderFromFile();
    initializingEnemiesCoordinate();
    char option = ' ';
    while (option != '4')
    {
        Header();
        option = Menu();
        if (option == '1')
        {
            ResetFlagsAndControls();
            initializingEnemiesCoordinate();
            system("cls");
            Head = NULL;
            ExtractingUserFile();
            gamer *temp = InputData();
            system("cls");
            GameOpeningScreen();
            system("cls");
            GameStartingStory();
            Lvl_1_OpeningScreen();
            Level_1(temp);
            // Stage 2

            if (Score == 600)
            {
                Lvl_2_OpeningScreen();
                Level_2(temp);

                // stage 3
                if (Score == 1200)
                {

                    Lvl_3_OpeningScreen();
                    Level_3(temp);
                }
                if (Score == 1800)
                {
                    Lvl_4_OpeningScreen();
                    Level_4(temp);
                }
                if (FinalEnemyLives == 0)
                {
                    GameWinningScreen();
                }
                else
                {
                    GameLose();
                    temp->score = 0;
                }
            }
            else
            {
                GameLose();
                temp->score = 0;
            }
            PutListInUserFile();
        } // end of opion 1
        if (option == '2')
        {
            Head = NULL;
            ExtractingUserFile();
            SortingInList(Head);
        }
        if (option == '3')
        {
            Head = NULL;
            initializingEnemiesCoordinate();
            ResetFlagsAndControls();
            ExtractingUserFile();
            cout << "Enter Your Name : ";
            string name;
            cin >> name;
            bool isfound;
            gamer *user = SearchUserNameInList(name, isfound);
            if (isfound)
            {
                bool iswin = false;
                Score = user->score;
                if (Score < 600)
                {
                    Lvl_1_OpeningScreen();
                    Level_1(user);
                    if (Score == 600)
                        iswin = true;
                    else
                        iswin = false;
                }
                if (Score >= 600 && Score < 1200)
                {

                    Lvl_2_OpeningScreen();
                    Level_2(user);
                    if (Score == 1200)
                        iswin = true;
                    else
                        iswin = false;
                }
                // stage 3
                if (Score >= 1200 && Score < 1800)
                {

                    Lvl_3_OpeningScreen();
                    Level_3(user);
                    if (Score == 1800)
                        iswin = true;
                    else
                        iswin = false;
                }
                if (Score >= 1800)
                {
                    Lvl_4_OpeningScreen();
                    Level_4(user);
                    if (FinalEnemyLives == 0)
                    {
                        GameWinningScreen();
                    }
                    else
                    {
                        GameLose();
                        user->score = 0;
                    }
                }
                else
                {
                    if (!iswin)
                    {
                        GameLose();
                        user->score = 0;
                    }
                }

                PutListInUserFile();
            }
            else
            {
                cout << endl
                     << "Player Not Found...";
                getch();
            }
        }
    }

} //..End of main