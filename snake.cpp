#include <iostream>
#include <ctime>
#include <windows.h> 
#include <conio.h>
#include <sstream>


using namespace std;

bool gameOver;

//Variaveis

    //Tela

const int width= 25;
const int height= 8;
    //Player
int playerX, playerY;
    //Tail
int tailX[100], tailY[100], tailLenght;
    //Tail Cord
int fposX, fposY, sposX, sposY;
int spd= 1;
    //Frutas
int fruitX, fruitY;
    //Game 
int score;
enum eDirection {STOP= 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

void Setup(){
    
    gameOver= false;
    dir= STOP;
    srand(time(0));

    playerX= rand() % width;
    playerY= rand() % height;
    fruitX= rand() % (width-2) + 1;
    fruitY= rand() % (height-2) + 1;
    score= 0;

    while(playerX == fruitX || playerY == fruitY){

        playerX= rand() % width;
        playerY= rand() % height;   
        fruitX= rand() % (width-2) + 1;
        fruitY= rand() % (height-2) + 1;
        
    }
}

void Draw(){
    stringstream map;

    system("Cls");

    //Borda Cima
    for(int i= 0; i < width; i++){
        map << "<>";
    }
    map << endl;

    //Print Mapa

    for (int i= 0; i < height; i++){
        for (int j= 0; j < width; j++){
            
            if(j == 0 || j == width-1){
                map << "<>";
            }
            else if(i == playerY && j == playerX){
                map << "O" << " ";
            }
            else if(i == fruitY && j == fruitX){
                map << "@" << " ";
            }
            else{
                bool tail= false;
                for(int k= 0; k < tailLenght; k++){
                    if(j == tailX[k] && i == tailY[k]){
                        map << "o" << " ";
                        tail= true;
                    }
                }
                if(!tail){
                    map << "  ";
                }
            }
        }
        map << endl;
    }

    //Borda BaiplayerXo
    for(int i= 0; i < width; i++){
        map << "<>";
    }
    map << endl;
    
    map << "Pontuacao: " << score << "        W/A/S/D PARA MOVER";

    cout << map.str();
}

void Input(){

    //Map KB
    if(_kbhit()){
      switch(_getch()){
        case 'w':
            if(dir != DOWN)
            dir= UP;
            break;
        case 'a':
            if(dir != RIGHT){
            dir= LEFT;
            }
            break;
        case 's':
            if(dir != UP){
            dir= DOWN;
            }
            break;
        case 'd':
            if(dir != LEFT){
            dir= RIGHT;
            }
            break;
        case '0':
            gameOver= true;
            break;
      }
    }
}

void Logic(){

    //Tail
    fposX= tailX[0];
    fposY= tailY[0];
    tailX[0]= playerX;
    tailY[0]= playerY;

    for(int i= 1; i < tailLenght; i++){
        
        sposX= tailX[i];
        sposY= tailY[i];
        tailX[i]= fposX;
        tailY[i]= fposY;
        fposX= sposX;
        fposY= sposY;

    }

    //Move
    switch(dir){
        case UP:
            playerY -= spd;
            break;
        case DOWN:
            playerY += spd;
            break;
        case LEFT:
            playerX -= spd;
            break;
        case RIGHT:
            playerX += spd;
            break;
    }

    //Cobra hit borda
    if (playerX <= 0 || playerX >= width-1 || playerY < 0 || playerY > height-1) {
        gameOver= true;
    }

    //Cobra hit fruta
    if(playerX == fruitX && playerY == fruitY){
        fruitX= rand() % (width-2) + 1;
        fruitY= rand() % (height-2) + 1;
        score += 1;
        tailLenght++;
    }

    //Cobra hit Tail
    for(int i= 1; i < tailLenght; i++){ 
        if(playerX == tailX[i] && playerY == tailY[i]){
            gameOver= true;
        }
    }    
}

//MAIN GAME LOOP
int main(){
    
    Setup();

    while(!gameOver){
    
        Draw();
        Input();
        Logic();
        
        Sleep(150);

    }

    return 0;
}