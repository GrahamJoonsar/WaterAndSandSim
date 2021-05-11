#include "raylib.h"
#include "stdio.h"

#define SCREEN_HEIGHT 500
#define SCREEN_WIDTH 500

#define NUM_OF_PARTICLES_PER_LINE 100

class Particle {
    public:
        int x, y, width = SCREEN_WIDTH/NUM_OF_PARTICLES_PER_LINE, height = SCREEN_WIDTH/NUM_OF_PARTICLES_PER_LINE;
        char type;
        
        Particle(){
            width = height = SCREEN_WIDTH / NUM_OF_PARTICLES_PER_LINE;
            type = 'e';
        }
        
        void draw(){
            switch (type){
                case 's':
                    DrawRectangle(x, y, width, height, BEIGE);
                    break;
                case 'w':
                    DrawRectangle(x, y, width, height, BLUE);
                    break;
                case 'e':
                    DrawRectangle(x, y, width, height, RAYWHITE);
                    break;
            }
        }
        
        void move();
};

Particle particles[NUM_OF_PARTICLES_PER_LINE][NUM_OF_PARTICLES_PER_LINE];
Particle emptyParticle;

void Particle::move(){
    if (type == 's' && y < SCREEN_HEIGHT - width){ // Sand movement
        //printf("Movement is run");
        if (particles[y/5 + 1][x/5].type == 'e' || particles[y/5 + 1][x/5].type == 'w'){
            // If the particle below is empty
            //printf("Below is empty");
            char temp = particles[y/5 + 1][x/5].type;
            particles[y/5 + 1][x/5].type = 's';
            particles[y/5][x/5].type = temp;
            //printf("check");
        } else if (x > 0 ? particles[y/5 + 1][x/5 - 1].type == 'e' : false && x > 0){
            // If the particle to the bottom left is empty
            particles[y/5 + 1][x/5 - 1].type = 's';
            particles[y/5][x/5].type = 'e';
        } else if (x < SCREEN_WIDTH - width ? particles[y/5 + 1][x/5 + 1].type == 'e' : false && x < SCREEN_WIDTH - 1){
            // If the particle to the bottom right is empty
            particles[y/5 + 1][x/5 + 1].type = 's';
            particles[y/5][x/5].type = 'e';
        }
    } else if (type == 'w' && y < SCREEN_HEIGHT - width){
        if (particles[y/5 + 1][x/5].type == 'e'){
            // If the particle below is empty
            //printf("Below is empty");
            particles[y/5 + 1][x/5].type = 'w';
            particles[y/5][x/5].type = 'e';
            //printf("check");
        } else if (x > 0 ? particles[y/5 + 1][x/5 - 1].type == 'e' : false && x > 0){
            // If the particle to the bottom left is empty
            particles[y/5 + 1][x/5 - 1].type = 'w';
            particles[y/5][x/5].type = 'e';
        } else if (x < SCREEN_WIDTH - width ? particles[y/5 + 1][x/5 + 1].type == 'e' : false && x < SCREEN_WIDTH - width){
            // If the particle to the bottom right is empty
            particles[y/5 + 1][x/5 + 1].type = 'w';
            particles[y/5][x/5].type = 'e';
        } else if (x > 0 && particles[y/5][x/5 - 1].type == 'e'){
            particles[y/5][x/5 - 1].type = 'w';
            particles[y/5][x/5].type = 'e';
        } else if (x < SCREEN_WIDTH - width && particles[y/5][x/5 + 1].type == 'e'){
            particles[y/5][x/5 + 1].type = 'w';
            particles[y/5][x/5].type = 'e';
        }
    }
}

void drawSand(){
    if (IsMouseButtonDown(0)){
        particles[GetMouseY()/5][GetMouseX()/5].type = 's';
    } else if (IsMouseButtonDown(1)){
        particles[GetMouseY()/5][GetMouseX()/5].type = 'w';
    }
}

int main(void)
{
    
    for (int y = 0; y < NUM_OF_PARTICLES_PER_LINE; y++){
        for (int x = 0; x < NUM_OF_PARTICLES_PER_LINE; x++){
            particles[y][x].x = x * (SCREEN_WIDTH / NUM_OF_PARTICLES_PER_LINE);
            particles[y][x].y = y * (SCREEN_HEIGHT / NUM_OF_PARTICLES_PER_LINE);
        }
    }
    /*
    for (int y = 0; y < NUM_OF_PARTICLES_PER_LINE; y++){
        for (int x = 0; x < NUM_OF_PARTICLES_PER_LINE; x++){
            y < 250 ? particles[y][x].type = 's' : particles[y][x].type = 'e';
        }
    }*/
    
    particles[4][50].type = 's';
    particles[20][50].type = 's';
    particles[20][49].type = 's';

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Particle Sim");

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(BLACK);
        
        for (int y = NUM_OF_PARTICLES_PER_LINE - 1; y >= 0; y--){
            for (int x = NUM_OF_PARTICLES_PER_LINE - 1; x >= 0; x--){
                particles[y][x].draw();
                particles[y][x].move();
            }
        }
        
        drawSand();
        
        //break;
        
        //particles[0][50].draw();
        //particles[0][50].move();
        
        EndDrawing();
    }

    CloseWindow();

    return 0;
}