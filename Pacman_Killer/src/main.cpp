#include "main.h"
#include "timer.h"
#include "ball.h"
#include "ground.h"
#include "grass.h"
#include "enemy.h"
#include "trampoline.h"
#include "pond.h"
#include "magnet.h"
#include "porcupine.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Ball ball1;
Ground ground1;
Grass grass1;
Enemy e[110];
int n=5, ti=0, f2, mflag=0, ti2=0, isPor=0, life=3, score=0, level=1, tl=60, th=0, tp3=30;
Trampoline tr;
Pond p1;
Magnet m1;
Porcupine por1;
extern double xo, yo;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;

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
    // glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    // glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    // glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    // Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    for(int i=1;i<=n;i++)
        if(e[i].flag==1)
            e[i].draw(VP);
    ground1.draw(VP);
    grass1.draw(VP);
    p1.draw(VP);
    ball1.draw(VP);
    tr.draw(VP);

    if(level>1)
    {
        ti++;
        if(ti==600)
        {
            if((rand()%2)==1)
            {
                m1 = Magnet(0, 0, COLOR_MAGNET, 1);
                ball1.ax=0.0002;
            }
            else
            {
                m1 = Magnet(0, 0, COLOR_MAGNET, 0);
                ball1.ax=-0.0002;
            }
        }
        if(ti==900)
        {
            ti=0;
            ball1.ax=0;
            ball1.velx=0;
        }
        if(ti>=600)
            m1.draw(VP);   
    }

    if(level>2)
    {
        if(ti2<205)
        {
            ti2++;
        }
        if(ti2==200)
        {
            f2=0;
            isPor=1;
            por1 = Porcupine(-4, 0.002, COLOR_BROWN);
        }
        if(ti2>=200)
            por1.draw(VP);

        if(ti2==205 && f2==1)
        {
            isPor=0;
            ti2=0;
        }        
        if(isPor==1 && (ball1.position[0]-ball1.r<=por1.position.x+1) && (ball1.position[0]+ball1.r>=por1.position.x) && (ball1.position.y-ball1.r<=-0.65))
        {
            if(f2==0)
                life--;
            f2=1;
            ball1.vely=0.20;
            ball1.ay = -0.006;
            ti2=200;
            ti2++;
        }
    }
}

void tick_input(GLFWwindow *window)
{
    if(tp3==30)
    {
    bounding_box_t bbox = ball1.bounding_box();
    int mouse_clicked = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    

    if (up && screen_center_y+4/screen_zoom<4)
    {
        screen_center_y += 0.06;
        reset_screen();
    }
    if (right && screen_center_x+4/screen_zoom<4)
    {
        screen_center_x += 0.06;
        reset_screen();
    }
    if (down && screen_center_y-4/screen_zoom>-4)
    {
        screen_center_y -= 0.06;
        reset_screen();
    }
    if (left && screen_center_x-4/screen_zoom>-4)
    {
        screen_center_x -= 0.06;
        reset_screen();
    }

    if (mouse_clicked)
    {
        if (yo!=-1 || xo!=-1)
        {
            double xn, yn;
            glfwGetCursorPos(window, &xn, &yn);
            
            int w, h;
            glfwGetWindowSize(window, &w, &h);
            
            screen_center_y += 8*(yn-yo)/(h*screen_zoom);
            screen_center_x -= 8*(xn-xo)/(w*screen_zoom);
            
            if(screen_center_x+4/screen_zoom > 4)
                screen_center_x = 4-4/screen_zoom;
            if(screen_center_y+4/screen_zoom > 4)
                screen_center_y = 4-4/screen_zoom;
            if(screen_center_x-4/screen_zoom < -4)
                screen_center_x = -4+4/screen_zoom;
            if(screen_center_y-4/screen_zoom < -4)
                screen_center_y = -4+4/screen_zoom;

            yo = yn;
            xo = xn;
            
            reset_screen();
        }
        else
            glfwGetCursorPos(window, &xo, &yo);
    
    }

    int aa = glfwGetKey(window, GLFW_KEY_A);
    int dd = glfwGetKey(window, GLFW_KEY_D);
    int ss = glfwGetKey(window, GLFW_KEY_SPACE);

    if((bbox.x)>=-2.25 && (bbox.x)<=0.25 && (bbox.y-bbox.r)<=-1)
    {
        double tp3,tp;
        if(bbox.x-bbox.r<=-2.25)
            ball1.position.x=-2.25+bbox.r;
        if(bbox.x+bbox.r>=0.25)
            ball1.position.x=0.25-bbox.r;
        bbox = ball1.bounding_box();
        if((bbox.y-bbox.r)>=-1)
        {
            tp3=-sqrt(abs((1.25-bbox.r)*(1.25-bbox.r)-(bbox.x+1)*(bbox.x+1)))-1;
            ball1.position[1]=tp3;
            tp = (double)(atan((double)(tp3+1)/(double)(bbox.x+1))*180)/(double)(M_PI);
        }
        else
            tp = (double)(atan((double)(bbox.y+1)/(double)(bbox.x+1))*180)/(double)(M_PI);
        double tp2 = 1.25-bbox.r;
        bbox = ball1.bounding_box();
        if(tp>0)
            tp-=180;
        if(ss && abs((bbox.x+1)*(bbox.x+1)+(bbox.y+1)*(bbox.y+1)-(1.25-bbox.r)*(1.25-bbox.r))<=0.1)
        {
            ball1.vely=0.12;
            ball1.ay=-0.004;
        }
        if(aa)
        {
            tp-=2;
            if(tp<=-180)
            {
                ball1.position[0]=-2.26;
                ball1.position[1]=-1+bbox.r;
            }
            else
            {
                ball1.position[0]=-1+tp2*cos((double)(tp*M_PI)/(double)(180));
                ball1.position[1]=-1+tp2*sin((double)(tp*M_PI)/(double)(180));
            }
        }
        if(dd)
        {
            tp+=2;
            if(tp>=0)
            {
                ball1.position[0]=0.26;
                ball1.position[1]=-1+bbox.r;
            }
            else
            {
                ball1.position[0]=-1+tp2*cos((double)(tp*M_PI)/(double)(180));
                ball1.position[1]=-1+tp2*sin((double)(tp*M_PI)/(double)(180));

            }
        }
    }
    else
    {
        if(aa)
        {
            ball1.position[0]-=0.1;        
        }
        if(dd)
        {
            ball1.position[0]+=0.1;
        }
        if(ss && is_on_ground(bbox))
        {
            ball1.vely=0.17;
            ball1.ay = -0.006;
        }
    }
}
    else
    {
        tp3++;
        if(tp3==30)
        {
            ball1.velx=0;
            ball1.ax=0;
        }
    }
}

void tick_elements() {
    ball1.tick();
    int flag2=0;
    if(ball1.vely<=0)
    {
        bounding_box_t bbox = ball1.bounding_box();
        for(int i=1;i<=n;i++)
        {
            if(e[i].flag==0)
                e[i]=Enemy(0, 0);
            else if(is_collision(e[i].bounding_box(), bbox))
            {
                if(e[i].clr!=-1)
                {
                    if(e[i].clr==0)
                        life--;
                    else
                        score+=n*10;
                    for(i=1;i<=n;i++)
                        e[i]=Enemy(0,0);
                }
                else
                {
                    if(e[i].pl==1)
                    {
                        if(ball1.velx>=0)
                        {
                            ball1.velx=-0.1;
                            ball1.ax=0.003;
                        }
                        else
                        {
                            ball1.velx=0.1;
                            ball1.ax=-0.003;
                        }
                        tp3=0;
                        e[i]=Enemy(0, 0);
                        flag2=2;
                        break;
                    }
                    else
                        e[i]=Enemy(0, 0);
                }
                flag2=1;
            }
            else
            {
                e[i].tick();
            }
        }
        if(flag2==1)
             ball1.vely=0.13;
        else if(flag2==2)
            ball1.vely=0.1;
        else if(bbox.x>=tr.beg && bbox.x<=tr.end && abs(bbox.y-bbox.r-tr.top)<=0.1)
            ball1.vely=0.2;
    }
    else
    {
        for(int i=1;i<=n;i++)
           if(e[i].flag==0)
               e[i]=Enemy(0, 0);
           else
               e[i].tick();
    }
    if(isPor==1)
    {
        por1.tick();
    }
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    ball1   = Ball(0, -1, COLOR_RED);
    ground1 = Ground(0 , 0 ,COLOR_GROUND);
    grass1 = Grass(0, 0, COLOR_GRASS);

    for(int i=1;i<=n;i++)
        e[i] = Enemy(0, 0);

    tr = Trampoline(0, 0, COLOR_GREY);
    p1 = Pond(-1, -1, COLOR_LBLUE);
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


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 600;
    int height = 600;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick())
        {
            th++;
            if(th%60==0)
            {
                th=0;
                tl--;
            }
            if(tl==0)
                break;    
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            char strf[120] = "Score : ";
            char str[30];
            sprintf(str, "%d", score);
            strcat(strf, str);

            if(score>=100 && level==1)
            {
                level++;
                tl=60;
            }

            if(score>=200 && level==2)
            {
                level++;
                // ti=0;
                tl=60;
            }
            if(score>=300 && level==3)
            {
                tl=30;
                level++;
            }
            if(score>=400 && level==4)
            {
                level++;
                tl=10;
            }
            if(score>=500 && level==5)
            {
                level++;
                tl=5;
            }
            if(score>=600 && level==6)
            {
                tl=3;
                level++;
            }
            if(score>=650 && level==7)
            {
                level++;
                tl=2;
            }
            if(score>=700 && level==8)
                break;
            strcat(strf, "     Level : ");
            sprintf(str, "%d", level);
            strcat(strf, str);

            strcat(strf, "     Lives : ");
            sprintf(str, "%d", life);
            strcat(strf, str);

            strcat(strf, "     Time Left : ");
            sprintf(str, "%d", tl);
            strcat(strf, str);

            glfwSetWindowTitle(window, strf);
            

            tick_elements();
            tick_input(window);
            if(life==0)
                break;
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }
    if(score>=700)
        cout<<"Congrats: You completed the game :)"<<endl;
    else
        cout<<"Game Over :("<<endl<<"Final Score: "<<score<<endl;
    quit(window);
}

bool is_on_ground(const bounding_box_t &a)
{
    if(a.y - a.r<=-1)
        return 1;
    return 0;
}

bool is_collision(const bounding_box_t &a,const bounding_box_t &b)
{
    if((abs((b.y-b.r)-(a.y+a.r)) <= 0.05) && (abs(a.x-b.x)<=0.5))
    {
        score+=10;
        return 1;
    }
    return 0;
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
