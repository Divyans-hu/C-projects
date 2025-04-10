// clang -o myprogram PaintingInC.c `pkg-config --cflags --libs sdl2` -lSDL2_image && ./myprogram

//--> to run.
/*------------------------------------------------------------------------------------------------*/
//tackles some problems of paint.c i.e color movement is smooth now
//also
// press Enter or Return saves the then current window as PNG file->(.-.) ^(*_*)
        // :g or G changes brush color to Green
        // :w or W -> white ; B or b -> Blue ; r or R -> Red 
        // :press escape to exit and not save 
//Also
//u can paint along with the stroke + and minus that is (mouse click adn move ) with + or - (*_*)


/* -----------------------------------------------------------------------------------------------*/

        //still not have insertion of a image 
        //And Color filing to shapes a, as no shapes are being identified



#include<SDL2/SDL_image.h>
#include <stdio.h>
#include <SDL2/SDL.h>

#include<math.h>
#define WIDTH 900
#define HEIGHT 900
#define COLOR_WHITE 0xFFFFFFFF
#define COLOR_RED 0xFFFF0000
#define COLOR_BLUE  0xff000fff
#define COLOR_GREEN 0xFF00FF00


struct Circle{
    double x;
    double y;
    double radius;
};

void saveScreenshot(SDL_Window* window) {
    SDL_Surface* surface = SDL_GetWindowSurface(window);
    if (!surface) {
        printf("Failed to get window surface: %s\n", SDL_GetError());
        return;
    }

    // Save the screenshot as PNG
    if (IMG_SavePNG(surface, "screenshot.png") != 0) {
        printf("Failed to save screenshot: %s\n", SDL_GetError());
    } else {
        printf("Screenshot saved as 'screenshot.png'\n");
    }
}


void FillCircle(SDL_Surface * surface ,struct Circle circle, u_int32_t color){
    double rad_sqr=pow(circle.radius,2);
    for(double x = circle.x-circle.radius;x<=circle.x+circle.radius;x++){
        for(double y= circle.y-circle.radius; y<=circle.y+circle.radius;y++){

                double distance_sqrd = pow(x-circle.x,2)+pow(y-circle.y,2);
                if(distance_sqrd < rad_sqr ){
                    SDL_Rect pixel = (SDL_Rect){x,y,1,1};
                    SDL_FillRect(surface,&pixel,color);
                }

        }
    }

}

int main() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create SDL window
    SDL_Window *window = SDL_CreateWindow("DV_PAINT",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          WIDTH, HEIGHT,
                                          SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Get window surface
    SDL_Surface *surface = SDL_GetWindowSurface(window);


    if (!surface) {
        printf("Surface could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    struct Circle circle={10,10,25};
    // Event loop
    SDL_Event event;
    int simul_run = 1;
    u_int32_t colour=COLOR_WHITE;
    while (simul_run) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || 
                (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) {
                simul_run = 0; 
            }

            if(event.type==SDL_KEYDOWN && event.key.keysym.sym==SDLK_MINUS){
                circle.radius--;
            }
            else if(event.type==SDL_KEYDOWN && event.key.keysym.sym==SDLK_EQUALS){
                circle.radius++;
            }
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_r) {
                FillCircle(surface,circle,colour);
                SDL_UpdateWindowSurface(window);
                colour=COLOR_RED;
                continue;
            }
            else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_b) {
               
                colour=COLOR_BLUE;
                continue;
            }
            else if(event.type==SDL_KEYDOWN && event.key.keysym.sym==SDLK_g){
            
                colour=COLOR_GREEN;
                continue;
            }
            else if(event.type==SDL_KEYDOWN && event.key.keysym.sym==SDLK_w){
            
                colour=COLOR_WHITE;
                continue;
            }
            if(event.type==SDL_KEYDOWN && event.key.keysym.sym==SDLK_RETURN){
                saveScreenshot(window);
            }
            
            if(event.type==SDL_MOUSEMOTION && event.motion.state!=0)
            {
                circle.x=event.motion.x;
                circle.y=event.motion.y;
                FillCircle(surface,circle,colour);
                SDL_UpdateWindowSurface(window);
                
            }

        }

    }
    
    // Cleanup SDL resources
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
