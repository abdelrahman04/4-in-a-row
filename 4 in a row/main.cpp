#include <iostream>
#include <bits/stdc++.h>
using namespace std;
class Tile{
private:


public:
    string color;
    string win_scheme;
    Tile(){
        color ="Blank";
        win_scheme="";
    }
    Tile(int c){
        switch(c) {
            case 0:
                color = "Orange";
                win_scheme = "V";
                break;
            case 1:
                color = "Green";
                win_scheme = "H";
                break;
            case 2:
                color = "Yellow";
                win_scheme = "LTR";
                break;
            case 3:
                color = "Purple";
                win_scheme = "RTL";
                break;
            default:
                color ="Blank";

        }
    }
    bool isEmpty(){
        return this->color=="Blank";
    }
    bool operator==(Tile const& a){
        return color==a.color;
    }
    Tile operator=(Tile const& a){
        color=a.color;
        win_scheme=a.win_scheme;
        return *this;
    }
    Tile operator=(Tile const* a){
        this->color=a->color;
        this->win_scheme=a->win_scheme;
        return *this;
    }
    void display(){
        cout<<"color: "<<color<<'\t';
        cout<<"win_scheme "<<win_scheme<<'\n';
    }
    void print(){
        cout<<color<<" ";
    }

};
class Board{
public:
    int no_of_rows=6, no_of_cols=7;
    Tile board[6][7];
    int blankCount;
    Board(){
        for(int i=0;i<6;i++){
            for(int j=0;j<7;j++)
                board[i][j]=new Tile();
        }
        blankCount=42;
    }
    void displayBoard(){
        for(int i=0;i<7;i++){
            cout<<"col "<<i+1<<' ';
        }
        cout<<'\n';
        for(int i=0;i<6;i++){
            for(int j=0;j<7;j++){
                board[i][j].print();
            }
            cout<<'\n';
        }
    }
    void insert(int column,Tile t) {
        int i=0;
        if(board[i][column].isEmpty()){
            while(i<5&&board[i+1][column].isEmpty()){
                i++;
            }
            board[i][column]=t;
            blankCount--;
        }else{
            cout<<"No insert possible"<<'\n';
        }
    }
    bool checkRTLConnected(Tile * winner){
        for(int i=3;i<6;i++){
            for(int j=0;j<4;j++){
                if(board[i][j]==*winner&&checkwinrtl(i,j)){
                    *winner=board[i][j];
                    return true;
                }
            }
        }
        return false;
    }
    bool checkwinrtl(int i,int j){
        for(int x=i-1, y=j+1;x>i-4&&x>=0&&y<j+4;x--,y++){
            if(!(board[i][j]==board[x][y])){
                return false;
            }
        }
        return true;
    }
    bool checkwinltr(int i,int j){
        for(int x=i+1, y=j+1;x<i+4&&y<j+4;x++,y++){
            if(!(board[i][j]==board[x][y])){
                return false;
            }
        }
        return true;
    }
    bool checkLTRConnected(Tile *winner){
        for(int i=0;i<3;i++){
            for(int j=0;j<4;j++){
                if(board[i][j]==*winner&&checkwinltr(i,j)){
                    *winner=board[i][j];
                    return true;
                }
            }
        }
        return false;
    }
    bool checkwinh(int i,int j){
        for(int y=j+1;y<j+4;y++){
            if(!(board[i][j]==board[i][y])){
                return false;
            }
        }
        return true;
    }

    bool checkHorizontallyConnected(Tile *winner){
        for(int i=0;i<6;i++){
            for(int j=0;j<4;j++){
                if(board[i][j]==*winner&&checkwinh(i,j)){
                    *winner=board[i][j];
                    return true;
                }
            }
        }
        return false;
    }
    bool checkwinv(int i,int j){
        for(int x=i+1;x<i+4;x++){
            if(!(board[i][j]==board[x][j])){
                return false;
            }
        }
        return true;
    }

    bool checkVerticallyConnected(Tile *winner){
        for(int i=0;i<3;i++){
            for(int j=0;j<7;j++){
                if(board[i][j]==*winner&&checkwinv(i,j)){
                    *winner=board[i][j];
                    return true;
                }
            }
        }
        return false;
    }
};
class Player{
public:
    string name;
    int number;
    Tile tile;
    Player(string n,int num,Tile t){
        name=n;
        number=num;
        tile=t;
    }
    void info (){
        cout<<"name: "<<name<<"\n number: "<<number<<"\n tile: "<<tile.color<<"\n";
    }
};
class Game{
public:
    int* score;
    int* tilenumber;
    int* playernumber;
    int numberofplayers;
    Player** player;
    Board* board;
    Tile* winner;
    bool win;
    Game() {
        board = new Board();
        winner = new Tile();
    }
    void GameStart(){
        cout<<"Welcome to the Giu Game:\n";
        cout<<"enter the number of players:";
        cin>>numberofplayers;
        score = new int[numberofplayers];
        tilenumber = new int[numberofplayers];
        playernumber = new int[numberofplayers];
        player = new Player*[numberofplayers];
        this->IntializeTeams();
        board->displayBoard();
        this->PlayStart();
    }
    void IntializeTeams(){
        choosetile(numberofplayers);
        for(int i=0;i<numberofplayers;i++){
            cout<<"enter the name of player number "<<i+1<<' ';
            string s;
            cin>>s;
            player[i]=new Player(s,i+1,Tile(tilenumber[i]));
        }
        for(int i=0;i<numberofplayers;i++){
            cout<<"player number "<<i+1<<" named "<<player[i]->name<<" got color "<<player[i]->tile.color<<'\n';
        }

    }
    void choosetile(int numberofplayers){
        tilenumber=new int[numberofplayers];
        for(int i=0;i<numberofplayers;i++){
            int x=rand()%4;
            bool flag=true;
            while(flag){
                flag=false;
                for(int j=0;j<i;j++){
                    if(x==tilenumber[j]){
                        x=rand()%4;
                        flag=true;
                    }
                }
            }
            tilenumber[i]=x;
        }
    }

    void PlayStart(){
        bool win=false;
        while(!win){
            for(int i=0;i<numberofplayers;i++){
                cout<<"choose column: ";
                int col;
                cin>>col;
                board->insert(col-1,player[i]->tile);
                *winner=player[i]->tile;
                board->displayBoard();
                if(checkState()){
                    cout<<player[i]->name<<" is the winner";
                    win=true;
                    break;
                }else{
                    if(board->blankCount==0){
                        cout<<"DRAW";
                        win=true;
                        break;
                    }
                }
            }
        }
    }
    bool checkState(){
        win=false;
        int x=(winner->win_scheme=="H"?0:winner->win_scheme=="V"?1:winner->win_scheme=="LTR"?2:3);
        switch(x){
            case 0:win=board->checkHorizontallyConnected(winner);
                break;
            case 1:win=board->checkVerticallyConnected(winner);
                break;
            case 2:win=board->checkLTRConnected(winner);
                break;
            case 3:win=board->checkRTLConnected(winner);
        }
        return win;
    }

};
int main() {
    Game g1;
    g1.GameStart();
    return 0;
}