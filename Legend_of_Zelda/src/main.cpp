#include <ao/ao.h>
#include <mpg123.h>

#define BITS 8
#include "main.h"
#include "timer.h"
#include "boat.h"
#include "sea.h"
#include "wave.h"
#include "rock.h"
#include "barrel.h"
#include "cannon.h"
#include "monster.h"
#include "boss.h"
#include "booster.h"
#include "gift.h"

using namespace std;

mpg123_handle *mh;
unsigned char *buffer;
size_t buffer_size;
size_t done;
int err;

int driver;
ao_device *dev;

ao_sample_format format;
int channels, encoding;
long rate;

pid_t pid = 0;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

Boat boat;
Sea sea;
Wave wave[10010];
Rock rock[10010];
Barrel barrel[10010];
Cannon cannon;
Monster monster[10010];
Boss boss;
Gift gift[10010];
Booster booster[10010];

int isPerspective = 1,flagc = 0, mxmons = 6, v = 1, tc, flagw = 0, tw, tw2, monskilled = 0, tpgift = 1, tpbooster = 1, pts = 0, health = 100, tmbooster;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0, wvelz, wvelx, waccz, waccx, mxmonsdis = 800;
double eyeX=0, eyeY=90, eyeZ=100, tarX=0, tarY=90, tarZ=0;

Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    glm::vec3 eye (eyeX, eyeY, eyeZ);
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (tarX, tarY, tarZ);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    sea.draw(VP);
    boat.draw(VP);
    int tp = 100;
    while(tp--)
    {
        wave[tp].draw(VP);
        rock[tp].draw(VP);
        if(tp < 70)
            barrel[tp].draw(VP);
        if(tp < mxmons && monster[tp].isAlive == 1)
            monster[tp].draw(VP);
    }
    if(cannon.isAlive == 1)
        cannon.draw(VP);
    if(boss.isAlive == 1)
        boss.draw(VP);

    for(int i=1; i<tpbooster; i++)
        if(booster[i].isAlive == 1)
            booster[i].draw(VP);
    
    for(int i=1; i<tpgift; i++)
        if(gift[i].isAlive == 1)
            gift[i].draw(VP);
}

void tick_input(GLFWwindow *window) {
    int pers = glfwGetKey(window, GLFW_KEY_V);
    int change = glfwGetKey(window, GLFW_KEY_C);
    int fire = glfwGetKey(window, GLFW_KEY_F);
    int jump = glfwGetKey(window, GLFW_KEY_SPACE);
    int f = glfwGetKey(window, GLFW_KEY_F);
    int forward = glfwGetKey(window, GLFW_KEY_UP);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);

    if(pers)
    {
        if(isPerspective == 1)
            isPerspective = 0;
        else
            isPerspective = 1;
    }
    if(change)
        flagc = 1;
    if((!change) && flagc == 1)
    {
        flagc = 0;
        v++;
    }
    if (left)
    {
        boat.rotation += (boat.vel-2)*0.6;
    }
    if(right)
    {
        boat.rotation -= (boat.vel-2)*0.6;
    }
    if(forward)
    {
        double tp = (boat.rotation - 90) * (M_PI/180);
        boat.position.z -= boat.vel*cos(tp);
        boat.position.x -= boat.vel*sin(tp);
    }
    if(jump && boat.position.y < 61)
    {
        boat.vely = 1.5;
        boat.g = 0.05;
    }
    if(f && cannon.isAlive == 0)
    {
        tc = 0;
        cannon.theta = (boat.rotation - 90) * M_PI / 180;
        cannon.isAlive = 1;
        cannon.vel = 8;
    }

}

void tick_elements()
{
    // Update for boat
    boat.position.y += boat.vely - boat.g;
    boat.vely -= boat.g;
    if(boat.position.y<60)
    {
        boat.g = 0;
        boat.vely = boat.g;
        boat.position.y = 60;
    }
    if(boat.ay > 0)
    {
        if(boat.position.y + boat.vely <= 61)
        {
            boat.vel_y -= boat.ay;
            boat.position.y += boat.vel_y;
        }
        else
        {
            boat.vel_y = 0.02;
            boat.ay *= (-1);
        }
    }
    if(boat.ay < 0)
    {
        if(boat.position.y - boat.vel_y >= 60.1)
        {
            boat.vel_y += boat.ay;
            boat.position.y -= boat.vel_y;
        }
        else
        {
            boat.vel_y = 0.02;
            boat.ay *= (-1);
        }
    }
    if(!(abs(boat.ltheta)<=5.0f))
        boat.omega *= (-1);

    boat.ltheta += boat.omega;

    // boat process endeds

    if(!cannon.isAlive)
    {
        cannon.position.z = boat.position.z;
        cannon.position.y = boat.position.y;
        cannon.position.x = boat.position.x;
    }
    else
    {
        cannon.position.x -= cannon.vel * sin(cannon.theta);
        cannon.position.z -= cannon.vel * cos(cannon.theta);
        tc++;
        if(tc == 100)
        {
            cannon.theta = 0;
            cannon.vel = 0;
            cannon.isAlive = 0;
        }
    }

    int tp = mxmons;
    while(tp--)
    {
        if(monster[tp].isAlive == 1)
        {
            float tp2 = (monster[tp].rotation - 90) * M_PI/180;
            monster[tp].position.z -= monster[tp].vel * cos(tp2);
            monster[tp].position.x -= monster[tp].vel * sin(tp2);
        }

    }

    tp = mxmons;
    float tpx = boat.position.x, tpy = boat.position.y, tpz = boat.position.z;
    while(tp--)
    {
        if((abs(tpx - monster[tp].position.x) + abs(tpy - monster[tp].position.y) + abs(tpz - monster[tp].position.z)) > mxmonsdis)
            monsterSpawn(tp);
    }

    if(boss.isAlive == 1)
    {
        float tp2 = (boss.rotation - 90) * M_PI/180;
        boss.position.z -= boss.vel * cos(tp2);
        boss.position.x -= boss.vel * sin(tp2);

        if((abs(tpx - boss.position.x) + abs(tpy - boss.position.y) + abs(tpz - boss.position.z)) > mxmonsdis)
            bossSpawn();

        if(detect_collision(boat.position.x, boat.position.y, boat.position.z, 20, 4, 10, boss.position.x, boss.position.y, boss.position.z, 20, 20, 20))
        {
            health -= 15;
            boat.g = 0.05;
            boat.vely = 1.5;
        }

        if(cannon.isAlive && detect_collision(cannon.position.x, cannon.position.y, cannon.position.z, 4, 4, 4, boss.position.x, boss.position.y, boss.position.z, 20, 20, 20))
        {
            boss.life -= 1;
            pts += (rand()%10) + 1;
            if(boss.life == 0)
            {
                booster[tpbooster++] = Booster(boss.position.x, boss.position.y, boss.position.z);
                pts += (rand()%30) + 1;
                monskilled = 0;
                boss.isAlive = 0;
            }
            cannon.vel = 0;
            cannon.isAlive = 0;
            cannon.theta = 0;
        }

    }
    else if(boss.isAlive == 0 && monskilled >= 3)
        bossSpawn();


    for(int i = 1; i<tpbooster; i++)
        if(booster[i].isAlive == 1)
            booster[i].rotation += 2.5;

    for(int i = 1; i<tpgift; i++)
        if(gift[i].isAlive == 1)
            gift[i].rotation += 2.5;

    // For Handelling wind
    if(flagw == 0 && tw2 == 500)// Change this
    {
        flagw = (rand()%4) + 1;
        tw = 0;
        waccz = 0.01;
        waccx = 0.01;
        wvelz = 0;
        wvelx = 0;
    }
    else if (flagw == 0)
    {
        tw2++;
    }
    else if(flagw == 1)
    {
        tw++;
        if(tw == 180)
        {
            tw2 = 0;
            flagw = 0;
        }
        wvelz += waccz;
        wvelx += waccx;
        boat.position.z += wvelz;
        boat.position.x += wvelx;
    }
    else if(flagw == 2)
    {
        tw++;
        if(tw == 180)
        {
            tw2 = 0;
            flagw = 0;
        }
        wvelz += waccz;
        wvelx += waccx;
        boat.position.z -= wvelz;
        boat.position.x -= wvelx;
    }
    else if(flagw == 3)
    {
        tw++;
        if(tw == 180)
        {
            tw2 = 0;
            flagw = 0;
        }
        wvelz += waccz;
        wvelx += waccx;
        boat.position.z += wvelz;
        boat.position.x -= wvelx;
    }
    else if(flagw == 4)
    {
        tw++;
        if(tw == 180)
        {
            tw2 = 0;
            flagw = 0;
        }
        wvelz += waccz;
        wvelx += waccx;
        boat.position.z -= wvelz;
        boat.position.x += wvelx;
    }

    tp = 100;
    while(tp--)
    {
        if(detect_collision(boat.position.x, boat.position.y, boat.position.z, 20, 4, 10, rock[tp].position.x, rock[tp].position.y, rock[tp].position.z, 6, 6, 6))
        {
            rock[tp] = Rock(60);
            health -= 5;
            boat.g = 0.05;
            boat.vely = 1.5;
        }
    }

    tp = mxmons;
    while(tp--)
    {
        if(detect_collision(boat.position.x, boat.position.y, boat.position.z, 20, 4, 10, monster[tp].position.x, monster[tp].position.y, monster[tp].position.z, 16, 16, 16))
        {
            monsterSpawn(tp);
            health -= 10;
            boat.g = 0.05;
            boat.vely = 1.5;
        }
    }

    tp = 100;
    while(tp-- && cannon.isAlive)
    {
        if(detect_collision(cannon.position.x, cannon.position.y, cannon.position.z, 4, 4, 4, rock[tp].position.x, rock[tp].position.y, rock[tp].position.z, 6, 6, 6))
        {
            rock[tp] = Rock(60);
            pts += (rand()%10) + 1;
            cannon.vel = 0;
            cannon.isAlive = 0;
            cannon.theta = 0;
        }
    }

    tp = mxmons;
    while(tp-- && cannon.isAlive)
    {
        if(detect_collision(cannon.position.x, cannon.position.y, cannon.position.z, 4, 4, 4, monster[tp].position.x, monster[tp].position.y, monster[tp].position.z, 16, 16, 16))
        {
            gift[tpgift++] = Gift(monster[tp].position.x, monster[tp].position.y, monster[tp].position.z);
            monsterSpawn(tp);
            monskilled++;
            cannon.vel = 0;
            cannon.isAlive = 0;
            cannon.theta = 0;
        }
    }
    tp = 70;
    while(tp--)
    {
        if(detect_collision(boat.position.x, boat.position.y, boat.position.z, 20, 4, 10, barrel[tp].position.x, barrel[tp].position.y + 10, barrel[tp].position.z, 4, 4, 4))
        {
            barrel[tp] = Barrel(60);
            pts += (rand()%20) + 1;
        }
    }

    for(int i=1; i<tpgift; i++)
        if(gift[i].isAlive == 1)
        {
            if(detect_collision(boat.position.x, boat.position.y, boat.position.z, 20, 4, 10, gift[i].position.x, gift[i].position.y, gift[i].position.z, 3, 3, 3))
            {
                pts += (rand()%20) + 1;
                gift[i].isAlive = 0;
            }            
        }


    for(int i=1; i<tpbooster; i++)
        if(booster[i].isAlive == 1)
        {
            if(detect_collision(boat.position.x, boat.position.y, boat.position.z, 20, 4, 10, booster[i].position.x, booster[i].position.y, booster[i].position.z, 8, 4, 4))
            {
                booster[i].isAlive = 0;
                boat.vel = 15;
                tmbooster = 0;
            }            
        }
    if(tmbooster <= 300)
        tmbooster++;
    if(tmbooster > 300)
    {
        boat.vel = 4;
    }

}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

// Not working for 60 ?

    sea = Sea(40);
    boat = Boat(0, 62, 40);

    int tp = 100;
    while(tp--)
    {
        wave[tp] = Wave(60);
        rock[tp] = Rock(60);
        if(tp<70)
            barrel[tp] = Barrel(60);
    }

    cannon = Cannon(boat.position.x, boat.position.y, boat.position.z);

    tp = mxmons;
    while(tp--)
    {
        monster[tp] = Monster(60);
    }

    boss = Boss(45, 60, 65);

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}

void audio_close()
{
    free(buffer);
    ao_close(dev);
    mpg123_close(mh);
    mpg123_delete(mh);
    mpg123_exit();
    ao_shutdown();
}

int main(int argc, char **argv) {
    srand(time(0));
    int width  = 600;
    int height = 600;

    window = initGLFW(width, height);

    initGL (window, width, height);

    pid = fork();

    if (pid == 0) {
        while (true) {
            ao_initialize();
            driver = ao_default_driver_id();
            mpg123_init();
            mh = mpg123_new(NULL, &err);
            buffer_size = mpg123_outblock(mh);
            buffer = (unsigned char*) malloc(buffer_size * sizeof(unsigned char));

            /* open the file and get the decoding format */
            mpg123_open(mh, "game.mp3");
            mpg123_getformat(mh, &rate, &channels, &encoding);

            /* set the output format and open the output device */
            format.bits = mpg123_encsize(encoding) * BITS;
            format.rate = rate;
            format.channels = channels;
            format.byte_format = AO_FMT_NATIVE;
            format.matrix = 0;
            dev = ao_open_live(driver, &format, NULL);

            while (mpg123_read(mh, buffer, buffer_size, &done) == MPG123_OK)
            {
                ao_play(dev, (char *)buffer, done);
            }

            audio_close();
        }
    }


    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            char strf[120] = "Score : ";
            char str[30];
            sprintf(str, "%d", pts);
            strcat(strf, str);

            strcat(strf, "     Health : ");
            sprintf(str, "%d", health);
            strcat(strf, str);

            glfwSetWindowTitle(window, strf);

            tick_elements();
            tick_input(window);
            handleView();
            if(health <= 0)
                break;
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }
    cout<<"Game Over :("<<endl<<"Final Score: "<<pts<<endl;
    quit(window);
}

void monsterSpawn(int tp)
{
    int tp3 = rand()%360;
    monster[tp].rotation = 90;

    if (rand()%2)
        monster[tp].rotation += tp3;
    else
        monster[tp].rotation -= tp3;

    monster[tp].isAlive = 1;

    int tpx1, tpx2, tpz1, tpz2;
    tpx1 = (rand() % 500) + 100;
    tpz1 = (rand() % 500) + 100;
    tpx2 = (-1)*(rand() % 500) - 100;
    tpz2= (-1)*(rand() % 500) - 100;
    if(rand()%2)
        tpx1 = tpx2;
    if(rand()%2)
        tpz1 = tpz2;

    monster[tp].position.z = boat.position.z + tpz1;
    monster[tp].position.x = boat.position.x + tpx1;
}

void bossSpawn()
{
    int tp3 = rand()%360;
    boss.rotation = 90;
    
    monskilled = 0;
    boss.life = 3;

    if (rand()%2)
        boss.rotation += tp3;
    else
        boss.rotation -= tp3;

    boss.isAlive = 1;

    int tpx1, tpx2, tpz1, tpz2;
    tpx1 = (rand() % 500) + 100;
    tpz1 = (rand() % 500) + 100;
    tpx2 = (-1)*(rand() % 500) - 100;
    tpz2= (-1)*(rand() % 500) - 100;
    if(rand()%2)
        tpx1 = tpx2;
    if(rand()%2)
        tpz1 = tpz2;

    boss.position.z = boat.position.z + tpz1;
    boss.position.x = boat.position.x + tpx1;

}


void handleView()
{
    double x = boat.position.x, y = boat.position.y, z = boat.position.z;
    float theta = (boat.rotation-90)*(M_PI/180);
    if(v%5 == 3)
    {
        tarY = eyeY = y+10;

        tarZ = z+40*cos(theta+M_PI);
        eyeZ = z+20*cos(theta);

        tarX = x+40*sin(theta+M_PI);
        eyeX = x+20*sin(theta);
    }
    else if(v%5 == 1)
    {
        tarY = eyeY = 90;

        tarZ = z+cos(theta+M_PI);
        eyeZ = z+80*cos(theta);

        tarX = x+sin(theta+M_PI);
        eyeX = x+80*sin(theta);
    }
    else if(v%5 == 0)
    {
        tarY = y;
        eyeY = 200;

        tarZ = eyeZ = z;

        tarX = x;
        eyeX = x+100;
    }
    else if(v%5 == 2)
    {
        eyeY = 100;
    }
    else if(v%5 == 4)
    {
        tarY = y;
        eyeY = 200;

        tarZ = eyeZ = z;
        
        tarX = x+1;
        eyeX = x;
    }
}

void reset_screen()
{
    if(isPerspective)
        Matrices.projection = glm::perspective(45.0f, 1.0f, 50.0f, 10000.0f);
    else
    {
        float top    = screen_center_y + 50 / screen_zoom;
        float bottom = screen_center_y - 50 / screen_zoom;
        float left   = screen_center_x - 50 / screen_zoom;
        float right  = screen_center_x + 50 / screen_zoom;
        Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
    }
}

void zoom(int arg)
{
    if(v%5 == 2)
    {
        
        if(arg ==1 && (eyeZ - 10) > tarZ)
                eyeZ-=10;
        else if(arg == -1)
            eyeZ+=10;

        float tp = tarZ-eyeZ;
        eyeX = tarX + (tarX-eyeX)*(eyeZ-tarZ)/tp;
        eyeY = tarY + (tarY-eyeY)*(eyeZ-tarZ)/tp;
    }
}

void helper(float x, float y)
{
    if(v%5 == 2)
    {
        tarX = boat.position.x+2*(x-300);
        if(y<=300)
            tarY = boat.position.y+(300-y)/2;
    }
}

bool detect_collision(float a, float b, float c, float d, float e, float f, float g, float h, float i, float j, float k, float l)
{
    return (abs(a - g) * 2 < (d + j)) && (abs(b - h) * 2 < (f + l)) && (abs(c - i) * 2 < (e + k));
}