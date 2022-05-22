#include "Gallery.h"
#include "SDL_utils.h"
#include <SDL_image.h>

Gallery::Gallery(SDL_Renderer* renderer_)
    : renderer(renderer_)
{
    loadGamePictures();
}

SDL_Texture* Gallery::loadTexture(std::string path )
{
    SDL_Texture* newTexture = NULL;
          SDL_Surface* loadedSurface = IMG_Load(path.c_str());

          if( loadedSurface == nullptr)
          {

            std::cout<< " Unable to load image " << path << " SDL_image Error: "
                    <<  IMG_GetError() << std::endl;

         } else {
            newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
            if( newTexture == nullptr )
                std::cout<< " Unable to create texture from " << path <<  " SDL Error: "
                        << SDL_GetError() << std::endl;
           SDL_FreeSurface( loadedSurface );

          }
          return newTexture;
}
   /* SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if ( loadedSurface == NULL )
        logSDLError(std::cout, "Unable to load image " + path + " SDL_image Error: " + IMG_GetError());
    else {
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( newTexture == NULL )
            logSDLError(std::cout, "Unable to create texture from " + path + " SDL Error: " + SDL_GetError());
        SDL_FreeSurface( loadedSurface );

        /*SDL_SetColorKey(loadedSurface,SDL_TRUE,SDL_MapRGB(loadedSurface->format,
         newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface));
    }
    return newTexture;
}
*/
void Gallery::loadGamePictures()
{

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);   // blue
    SDL_RenderClear(renderer);

    pictures[PIC_BACKGROUND]  =  loadTexture( "background.jpg");


    pictures[PIC_FROG] = loadTexture("frog.png");
    pictures[PIC_SNAKE_VERTICAL] = loadTexture("snake_vertical.png");
    pictures[PIC_SNAKE_HORIZONTAL] = loadTexture("snake_horizontal.png");
    pictures[PIC_SNAKE_HEAD] = loadTexture("snake_head.png");
}
