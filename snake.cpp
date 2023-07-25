#include<iostream>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<stdbool.h>
#define  ARRIBA 72
#define ABAJO 80
#define DERECHA 77
#define IZQUIERDA 75
#define ESC 27
using namespace std;

//PROTOTIPOS DE FUNCIONES

void gotoxy(int x, int y);
void ocultar_cursor();
void mapa();
void posicion_serpiente();
void dibujar_serpiente();
void borrar_serpiente();
void teclado();
void comida();
bool choque();

//VARIABLES GLOBALES (se declaran por fuera para poder tener acceso en todo momento)

int cuerpo[200][2];
int n=1, tamaño=10, direc=3;
int x=10, y=12;
int xc=30, yc=15;
int velocidad=50;
int puntos=0;
char teclas;


//INT MAIN (principal)

int main(){
    system("mode con cols=80 lines=25");
    gotoxy(35,1);
    cout<<"~~~~~~ JUEGO DE LA SERPIENTE - SNAKE GAME ~~~~~~";
    ocultar_cursor();
    mapa();
    gotoxy(xc, yc);
    cout<<char(4);

    while(teclas != ESC && choque()){
        gotoxy(3,2);
        cout<<"PUNTUACION: "<<puntos<<endl;
        borrar_serpiente();
        posicion_serpiente();
        dibujar_serpiente();
        comida();
        teclado();
        teclado();

        if(direc==1){
            y--;
        }
         if(direc==2){
            y++;
        }
         if(direc==3){
            x++;
        }
         if(direc==4){
            x--;
        }

        Sleep(velocidad);

    }

    gotoxy(35,1);
    cout<<"~~~~~~ JUEGO DE LA SERPIENTE - SNAKE GAME ~~~~~~";
    mapa();
    gotoxy(22,12);
    cout<<"OBTUVISTE UNA PUNTUACION DE "<<puntos;
    gotoxy(22,14);
    cout<<"Presione una tecla para continuar ...";
    getch();

    return 0;


}


//FUNCIONES:

// 1) Funcion GOTOXY, se envian coordenada para x e y,
//   logramos posicionar un "mensaje" en la consola

void gotoxy(int x, int y){
 	HANDLE hCon;
 	COORD dwPos;

 	dwPos.X = x;
 	dwPos.Y = y;
 	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
 	SetConsoleCursorPosition(hCon,dwPos);
}


// 2) Funcion que imprime el mapa del juego

void mapa(){
  
    for(int i=2;i<80;i++){
        gotoxy(i,4);
        cout<<char(205);
        gotoxy(i,23);
        cout<<char(205);
    }

    for(int v=4;v<23;v++){
        gotoxy(2,v);
        cout<<char(186);
        gotoxy(77,v);
        cout<<char(186);
    }

    gotoxy (2,4); 
    cout<<char(201);
 	gotoxy (2,23); 
    cout<<char(200);
 	gotoxy (77,4); 
    cout<<char(187);
 	gotoxy(77,23); 
    cout<<char(188);
}

// 3) Funcion que guarda la posicion en la que se encuentra la serpiente

void posicion_serpiente(){
    cuerpo[n][0]=x;
    cuerpo[n][1]=y;
    n++;
    
    if(n==tamaño){
        n=1;
    }
}

// 4) Funcion que dibuja el cuerpo de la serpiente

void dibujar_serpiente(){

    for(int i=1;i<tamaño;i++){
        gotoxy(cuerpo[i][0], cuerpo[i][1]);
        cout<<"*";
    }

}

// 5) Funcion que borra el cuerpo de la serpiente (la ultima parte)

void borrar_serpiente(){

    gotoxy(cuerpo[n][0],cuerpo[n][1]);
    cout<<" ";
}


// 6) Funcion que detecta la tecla que uno toca (UP, DOWN, RIGHT, LEFT)

void teclado(){

    if(kbhit()){  //kbhit() esta funcion me verifica si se ingreso alguna tecla
        teclas=getch();
        switch (teclas){
        case ARRIBA:
            if(direc!=2){
                direc=1;
            }
            break;
        case ABAJO:
            if(direc!=1){
                direc=2;
            }
            break;
        case DERECHA:
            if(direc!=4){
                direc=3;
            }
            break;
        case IZQUIERDA:
            if(direc!=3){
                direc=4;
            }
            break;
        }
    }
}

// 7) Funcion que muestra la comida de forma aleatoria en alguna zona de la pantalla

void comida(){
    if(x==xc && y==yc){
        xc=(rand() % 73) + 4;
        yc=(rand() % 18) + 5;
        tamaño++;
        puntos+=100;
        gotoxy(xc,yc);
        cout<<char(4);
    }
}

// 8) Funcion que me verifica si se choco con el borde
//    del mapa o con su mismo cuerpo

bool choque(){

    if(y == 4 || y == 23 || x == 2 || x == 77){
        return false; 
    }

    for(int j=tamaño-1;j>0;j--){
        if(cuerpo[j][0]==x && cuerpo[j][1]==y){
            return false;
        }
    }

    return true;
}

// 9) Funcion que oculta el cursor

void ocultar_cursor(){
    CONSOLE_CURSOR_INFO cci = {100, FALSE};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
}