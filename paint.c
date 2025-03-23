//Basic  paint here's how's to execute it
//clang -o tudu paint.c `pkg-config --cflags --libs sdl2` && ./tudu
/*--------------------------------------------------------------------*/
        //Basic feature like paint from key only with mouse movement.
        //-> it has a problem as changing color from keystroke makes the prev colored circle to new color selected .
        //-> it doesn't allow you to change stroke of brush.
        //->Brush is also of one type solid plane .
//try to make more realistic and also allow saving as picture




#include <stdio.h>
#include <SDL2/SDL.h>
#include<math.h>
#define WIDTH 900
#define HEIGHT 600
#define COLOR_WHITE 0xFFFFFFFF
#define COLOR_RED 0xFFFF0000
#define COLOR_BLUE  0xff000fff
#define COLOR_GREEN 0xFF00FF00
struct Circle{
    double x;
    double y;
    double radius;
};


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
    SDL_Window *window = SDL_CreateWindow("PAint",
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
                simul_run = 0;  // Exit loop when window is closed or ESC is pressed
            }
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_r) {
                colour=COLOR_RED;
            }
            else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_b) {
                colour=COLOR_BLUE;
            }
            else if(event.type==SDL_KEYDOWN && event.key.keysym.sym==SDLK_g){
                colour=COLOR_GREEN;
            }
            else if(event.type==SDL_KEYDOWN && event.key.keysym.sym==SDLK_w){
                colour=COLOR_WHITE;
            }
            if(event.type==SDL_KEYDOWN && event.key.keysym.sym==SDLK_RETURN){
                simul_run=0;
            }
            
            if(event.type==SDL_MOUSEMOTION && event.motion.state!=0)
            {
                circle.x=event.motion.x;
                circle.y=event.motion.y;
                
            }
        }
        FillCircle(surface,circle,colour);
        SDL_UpdateWindowSurface(window);
    }
    
    // Cleanup SDL resources
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
