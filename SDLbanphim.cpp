#include <iostream>
#include <SDL.h>
#include<SDL_image.h>
#include<Windows.h>
#include <SDL_render.h>
using namespace std;

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 400;
const string WINDOW_TITLE = "Snake";

void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal = false);
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void waitUntilKeyPressed();
SDL_Texture* loadTexture( string  path,  SDL_Renderer*  renderer);

int main(int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);

    SDL_Texture* background  =  loadTexture( "background.jpg", renderer);
    SDL_RenderCopy( renderer, background, NULL, NULL);

    /*SDL_Texture* spongeBob =  loadTexture( "snake_corner.png", renderer);
    SDL_Rect spongeBobRect;
    SDL_QueryTexture( spongeBob, NULL, NULL, &spongeBobRect.w, &spongeBobRect.h);
    spongeBobRect.x = 100;
    spongeBobRect.y = 100;
    spongeBobRect.w =  spongeBobRect.w / 2.0;
    spongeBobRect.h =  spongeBobRect.h / 2.0;
    SDL_RenderCopy( renderer, spongeBob, NULL, &spongeBobRect );*/



    SDL_RenderPresent( renderer );

   waitUntilKeyPressed();
   quitSDL(window, renderer);
    return 0;
}
SDL_Texture* loadTexture( string path, SDL_Renderer* renderer)
{
          SDL_Texture* newTexture = nullptr;
          SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
          if( loadedSurface == nullptr)
            cout<< " Unable to load image " << path << " SDL_image Error: "
                    <<  IMG_GetError() << endl;
          else {
            newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
            if( newTexture == nullptr )
                cout<< " Unable to create texture from " << path <<  " SDL Error: "
                        << SDL_GetError() << endl;
            SDL_FreeSurface( loadedSurface );
          }
          return newTexture;
}
void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}

void initSDL(SDL_Window* &Window, SDL_Renderer* &renderer)
  {
      if (SDL_Init(SDL_INIT_EVERYTHING)   != 0)
        logSDLError(std::cout, " SDL_Init", true);

      Window =  SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
               SDL_WINDOWPOS_CENTERED,  SCREEN_WIDTH,  SCREEN_HEIGHT,  SDL_WINDOW_SHOWN );
               //HGJHKJ
               //VHNBJB
      if( Window  ==  nullptr)  logSDLError(std::cout, " CreateWindow ",  true);
      renderer =  SDL_CreateRenderer(Window , -1 , SDL_RENDERER_ACCELERATED  |
                                                                                         SDL_RENDERER_PRESENTVSYNC) ;
                //BJHJ
     if(  renderer == nullptr)   logSDLError(std::cout, " CreateRenderer ",  true);

      SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,  "linear");
      SDL_RenderSetLogicalSize(renderer,  SCREEN_WIDTH,  SCREEN_HEIGHT  );
}

void quitSDL(SDL_Window* window,  SDL_Renderer* renderer)
{
       SDL_DestroyRenderer(renderer);
       SDL_DestroyWindow(window);
       SDL_Quit;
}

void waitUntilKeyPressed()
{
    SDL_Event e;
    while  (true) {
           if( SDL_WaitEvent(&e)  != 0  && (e.type  ==  SDL_KEYDOWN  ||  e.type  ==  SDL_QUIT)  )
             return;
           SDL_Delay(100);
    }
}







