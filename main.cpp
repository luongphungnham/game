#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <chrono>

#include <SDL.h>
#include<SDL_image.h>
#include<Windows.h>
#include <SDL_render.h>

#include "SDL_utils.h"
#include "Game.h"
#include "Gallery.h"




using namespace std;



const int SCREEN_WIDTH = 1300;
const int SCREEN_HEIGHT= 800;
const  char WINDOW_TITLE[]= "Snake";

const int BOARD_WIDTH = 30;
const int BOARD_HEIGHT = 20;
const int CELL_SIZE = 40;


const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B= 188;


const SDL_Color BOARD_COLOR = {0, 0, 0, 0};
const SDL_Color LINE_COLOR = {0, 0, 255, 255};

const double STEP_DELAY = 0.1;
#define CLOCK_NOW chrono::system_clock::now
typedef chrono::duration<double> ElapsedTime;

void renderSplashScreen();
void renderGamePlay(SDL_Renderer*, const Game& game);
void renderGameOver(SDL_Renderer* renderer, const Game& game);
void interpretEvent(SDL_Event e, Game& game);
//void updateRankingTable(const Game& game);

Gallery* gallery = nullptr;
bool success = true;

/*void renderScore(SDL_Renderer* renderer, int tailLength, int w_size, int ww_size, TTF_Font* font) {
	SDL_Color Black = { 0, 0, 0 };

	// Get the font used for displaying text

	if (font == NULL) {
		cout << "Font loading error" << endl;
		return;
	}

	SDL_Surface* score = TTF_RenderText_Solid(font, (string("Score: ") + to_string(tailLength * 10)).c_str(), Black);
	SDL_Texture* scoreMessage = SDL_CreateTextureFromSurface(renderer, score);
	SDL_Rect scoreRect;
	scoreRect.w = 100;
	scoreRect.h = 30;
	scoreRect.x = ((w_size * ww_size) / 2) - (scoreRect.w / 2);
	scoreRect.y = 0;
	SDL_RenderCopy(renderer, scoreMessage, NULL, &scoreRect);

}

*/



int main(int argc, char* argv[])
{
  //  srand(time(0));
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    gallery = new Gallery(renderer);
    Game game(BOARD_WIDTH, BOARD_HEIGHT);
    SDL_Event e;






    renderSplashScreen();
    auto start = CLOCK_NOW();
    renderGamePlay(renderer, game);
    while (game.isGameRunning()) {
        while (SDL_PollEvent(&e)) {
            interpretEvent(e, game);
        }

        auto end = CLOCK_NOW();
        ElapsedTime elapsed = end-start;
        if (elapsed.count() > STEP_DELAY) {
            game.nextStep();
            renderGamePlay(renderer, game);
            start = end;
        }
        SDL_Delay(100);
    }
  renderGameOver(renderer, game);


    delete gallery;
    quitSDL(window, renderer);
    return 0;


}

float generateRandomNumber()
{
    return (float) rand() / RAND_MAX;
}

void renderSplashScreen()
{
    cout << "In stitches" << endl;
    waitUntilKeyPressed();
}

void drawCell(SDL_Renderer* renderer, int left, int top, Position pos, SDL_Texture* texture, int wid, int hei)
{
	SDL_Rect cell;
	cell.x = left + pos.x * CELL_SIZE + 5;
	cell.y = top + pos.y * CELL_SIZE + 5;
	cell.w = wid;
	cell.h = hei;
	SDL_RenderCopy(renderer, texture, NULL, &cell);
}

void drawBack(SDL_Renderer* renderer,  SDL_Texture* texture)
{
    SDL_RenderCopy(renderer, texture, NULL, NULL);
}

void drawFrog(SDL_Renderer* renderer, int left, int top, Position pos)
{
    drawCell(renderer, left, top, pos, gallery->getImage(PIC_FROG), CELL_SIZE, CELL_SIZE);
}

void drawSnake(SDL_Renderer* renderer, int left, int top, vector<Position> pos)
{
//	 snake's head
	drawCell(renderer, left, top, pos[pos.size()-1], gallery->getImage(PIC_SNAKE_HEAD), CELL_SIZE - 10, CELL_SIZE - 10);

	// snake's body
    for (int i = pos.size() - 2; i >= 0; i--) {
        SDL_Texture* texture = gallery->getImage(
			pos[i].y == pos[i+1].y ? PIC_SNAKE_HORIZONTAL : PIC_SNAKE_VERTICAL);
        drawCell(renderer, left, top, pos[i], texture,  CELL_SIZE - 5, CELL_SIZE - 10);
    }
}




void drawVerticalLine(SDL_Renderer* renderer, int left, int top, int cells)
{
   SDL_SetRenderDrawColor(renderer, LINE_COLOR.r, LINE_COLOR.g, LINE_COLOR.b, 0);
   SDL_RenderDrawLine(renderer, left, top, left, top + cells * CELL_SIZE);
}

void drawHorizontalLine(SDL_Renderer* renderer, int left, int top, int cells)
{
  SDL_SetRenderDrawColor(renderer, LINE_COLOR.r, LINE_COLOR.g, LINE_COLOR.b, 0);
    SDL_RenderDrawLine(renderer, left, top, left + cells * CELL_SIZE, top);
}

void renderGamePlay(SDL_Renderer* renderer, const Game& game)
{
    int top = 0, left = 0;
  SDL_SetRenderDrawColor(renderer, BOARD_COLOR.r, BOARD_COLOR.g, BOARD_COLOR.b, 0);
    SDL_RenderClear(renderer);
/*
    for (int x = 0; x <= BOARD_WIDTH; x++)
        drawVerticalLine(renderer, left + x*CELL_SIZE, top, BOARD_HEIGHT);
    for (int y = 0; y <= BOARD_HEIGHT; y++)
        drawHorizontalLine(renderer, left, top+y * CELL_SIZE, BOARD_WIDTH);
*/

/*        SDL_Texture* background = loadTexture("background.jpg", renderer);
        SDL_RenderCopy(renderer, background, NULL, NULL);
*/
    drawBack(renderer, gallery->getImage(PIC_BACKGROUND));
    drawFrog(renderer, left, top, game.getFrogPosition());
    drawSnake(renderer, left, top, game.getSnakePositions());

    SDL_RenderPresent(renderer);
}

void renderGameOver(SDL_Renderer* renderer, const Game& game)
{

}

void interpretEvent(SDL_Event e, Game& game)
{
    if (e.type == SDL_KEYDOWN) {
        // cerr << "_" <<SDL_GetKeyName(e.key.keysym.sym) << "_" <<endl;
        switch (e.key.keysym.sym) {
            case SDLK_u:
        	case SDLK_UP: game.processUserInput(UP); break;
        	 case SDLK_m:
        	case SDLK_DOWN: game.processUserInput(DOWN); break;
        	 case SDLK_h:
        	case SDLK_LEFT: game.processUserInput(LEFT); break;
        	 case SDLK_k:
        	case SDLK_RIGHT: game.processUserInput(RIGHT); break;
        }
    }
}



