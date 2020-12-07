//Powered by Zannatinha e Joao

#include<SFML/Graphics.hpp>
#include<time.h>

using namespace sf;


int main(){

    srand(time(0));

    RenderWindow app(VideoMode(400, 400), "Minesweeper"); //abre janela e da o nome de "Minesweeper"

    //declarando variaveis e vetores
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

    for (int i=1; i<11; i++) //define os valores do vetor grid, para colocar as respectivas texturas depois
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
                if(e.key.code == Mouse::Left) sgrid[x][y] = grid[x][y];
                else if(e.key.code == Mouse::Right) sgrid[x][y] = 11;
        }

        app.clear(Color::Transparent);

        for(int i=1; i<11; i++)
            for(int j=1; j<11; j++){

                if(sgrid[x][y] == 9) sgrid[i][j] = grid[i][j];

                s.setTextureRect(IntRect(sgrid[i][j] * w, 0, w, w)); //define a posicao do sgrid na textura e na janela e desenha
                s.setPosition(i * w, j * w);
                app.draw(s);
            }

        app.display();
        
    }

  return 0;
}

