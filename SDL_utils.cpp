#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <string>

void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}
void initSDL(SDL_Window* &Window, SDL_Renderer* &renderer,
int screenWidth, int screenHeight, const char* windowTitle)

  {
      if (SDL_Init(SDL_INIT_EVERYTHING)   != 0)
        logSDLError(std::cout, " SDL_Init ", true);

      Window =  SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_CENTERED,
               SDL_WINDOWPOS_CENTERED,  screenWidth,  screenHeight,  SDL_WINDOW_SHOWN );


      if( Window  ==  nullptr)  logSDLError(std::cout, " CreateWindow ",  true);
      renderer =  SDL_CreateRenderer(Window , -1 , SDL_RENDERER_ACCELERATED  |
                                                                                         SDL_RENDERER_PRESENTVSYNC) ;

     if(  renderer == nullptr)   logSDLError(std::cout, " CreateRenderer ",  true);

      SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,  "linear");
      SDL_RenderSetLogicalSize(renderer,  screenWidth,  screenHeight  );
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
/*
SDL_Texture* loadTexture( string path, SDL_Renderer* renderer )
{
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if ( loadedSurface == NULL )
        cout << "Unable to load image " << path << " SDL_image Error: "
             << IMG_GetError() << endl;
    else {
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( newTexture == NULL )
            cout << "Unable to create texture from " << path << " SDL Error: "
                 << SDL_GetError() << endl;
        SDL_FreeSurface( loadedSurface );
    }
    return newTexture;
}

*/
