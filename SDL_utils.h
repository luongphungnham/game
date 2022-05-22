
#ifndef SDL_UTILS__H
#define SDL_UTILS__H

#include <iostream>
#include <SDL.h>
#include<SDL_image.h>
#include<Windows.h>
#include <SDL_render.h>
void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal = false);

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer,
	int screenWidth, int screenHeight, const char* windowTitle) ;

void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

void waitUntilKeyPressed();

//SDL_Texture* loadTexture( std::string path, SDL_Renderer* renderer )

/*SDL_Texture* loadTexture( std::string  path,  SDL_Renderer*  renderer);

void refreshScreen(SDL_Window* window, SDL_Renderer* renderer, const SDL_Rect& filled_rect)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);   // blue
    SDL_RenderClear(renderer);

    SDL_Texture* background  =  loadTexture( "background.jpg", renderer);
    SDL_RenderCopy( renderer, background, NULL, NULL);

    SDL_Texture* spongeBob =  loadTexture( "human64x91.png", renderer);

    SDL_Rect spongeBobRect;
    SDL_QueryTexture( spongeBob, NULL, NULL, &spongeBobRect.w, &spongeBobRect.h);
    spongeBobRect.x  = 200;
    spongeBobRect.y  = 505;
    spongeBobRect.w = spongeBobRect.w ;
    spongeBobRect.h  = spongeBobRect.h ;
    SDL_RenderCopy( renderer, spongeBob, NULL, &spongeBobRect);


    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);   // white
    SDL_RenderFillRect(renderer, &filled_rect);


    SDL_RenderPresent(renderer);

}
*/

#endif
