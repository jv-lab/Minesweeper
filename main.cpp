//Powered by Zannatinha e Joao

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <fstream>
#include <iostream>
#include <ctime>
#include <algorithm>


using namespace sf;
using namespace std;

struct info{
    int cliques, sec;
};

bool cmp(const info &a, const info &b) { //para ordenacao
    return a.cliques > b.cliques || (a.cliques == b.cliques && a.sec < b.sec);
}

info ranking[6];

int main(){

    //declarando variaveis

    info player;
    player.cliques = 0;
    
    time_t t1, t2;
    t1 = time(NULL); //tempo inicial

    //configurando fonte e texto de game over
    Font font;
    font.loadFromFile("images/small_font.ttf");
    Text text;
    text.setFont(font); 
    text.setCharacterSize(48); 
    text.setOutlineColor(Color::Black);
    text.setFillColor(Color::Red);
    text.setStyle(Text::Style::Bold);
    text.setString("Game Over!");

    //arquivo txt para ranking
    string file = "images/ranking.txt";
    ifstream arq;
    ofstream out;
    out.open(file);
    arq.open(file);

    srand(time(0));

    RenderWindow app(VideoMode(400,400), "Minesweeper"); //abre janela e da o nome de "Minesweeper"

    int w = 32;
    int grid[12][12];
    int sgrid[12][12]; // Para mostrar o grid

    //carrega textura de um arquivo e inicializa o sprite
    Texture t;  
    t.loadFromFile("images/field.jpg"); 
    Sprite s(t);

    for(int i=1; i<11; i++) // inicializa o grid com a textura (a que oculta os numeros, vazio ou bomba)
        for(int j=1; j <11; j++){
            sgrid[i][j] = 10;

            if (rand() % 5 == 0) grid[i][j] = 9; //inicializa o grid que sera revelado quando se clicar no primeiro
            else grid[i][j] = 0;
        }

    for (int i=1; i<11; i++) //atualiza os valores do vetor grid, para colocar as respectivas texturas com numeros
        for (int j=1; j<11; j++){
            int n = 0;
            if (grid[i][j] == 9) continue;
            if (grid[i + 1][j] == 9) n++;
            if (grid[i][j + 1] == 9) n++;
            if (grid[i - 1][j] == 9) n++;
            if (grid[i][j - 1] == 9) n++;

            if (grid[i + 1][j + 1] == 9) n++;
            if (grid[i - 1][j - 1] == 9) n++;
            if (grid[i - 1][j + 1] == 9) n++;
            if (grid[i + 1][j - 1] == 9) n++;

            grid[i][j] = n;
        }

    while (app.isOpen()){ //loop do jogo
        Vector2i pos = Mouse::getPosition(app); //pega a posicao do mouse dentro da janela e guarda em variaveis
        int x = pos.x / w;
        int y = pos.y / w;

        Event e;
        
        while(app.pollEvent(e)){ //detecta se um evento fecha o programa ou se um evento de mouse indica uma jogada, e a realiza
            if(e.type == Event::Closed)
                app.close();

            if(e.type == Event::MouseButtonPressed)
                if(e.key.code == Mouse::Left){
                    sgrid[x][y] = grid[x][y];
                    if(grid[x][y] == 9){ 
                        t2 = time(NULL); //pega o tempo do game over
                        app.draw(text);
                    } else if(grid[x][y] != 8 && grid[x][y] != 9 && grid[x][y] != 10 && grid[x][y] != 11)
                        player.cliques += 1; //quantidade de jogadas +1
                }
                else if(e.key.code == Mouse::Right) sgrid[x][y] = 11; //colocar bandeira
                
        }

        app.clear(Color::White);

        for(int i=1; i<11; i++)
            for(int j=1; j<11; j++){

                if(sgrid[x][y] == 9) sgrid[i][j] = grid[i][j];

                s.setTextureRect(IntRect(sgrid[i][j] * w, 0, w, w)); //define a posicao do sgrid na textura e na janela e desenha
                s.setPosition(i * w, j * w);
                app.draw(s);
            }

        app.display();
        
    }

    player.sec = difftime(t2, t1);

    for(int i=1; i<7; i++){ //ler txt
        arq >> ranking[i].cliques;
        arq >> ranking[i].sec;
    }

    ranking[0].cliques = player.cliques;
    ranking[0].sec = player.sec;

    stable_sort(ranking, ranking+6, cmp); //ordenar ranking

    for(int i=0; i<6; i++){ //printar ranking atualizado no txt
        out << ranking[i].cliques << " ";
        out << ranking[i].sec << endl;
    }

    arq.close();
    out.close();
    
    return 0;
}

