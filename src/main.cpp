#include "main.h"
#include "timer.h"
#include "ball.h"
#include "player.h"
#include "magnet.h"
#include "ground.h"
#include "wall.h"
#include "display.h"
#include "fly_obj.h"
#include "fly_obj2.h"
#include "fly_obj3.h"
#include "fireline.h"
#include "firebeam.h"
#include "waterbubble.h"
#include "circularring.h"
#include "bomerang.h"
#include "viserion.h"
#include "bullet.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/
int ball_count = 100;
int magnet_count = 5;
int fly_count = 1;
int fly2_count = 2;
int fly3_count = 2;
int wall_count = 37;
int line_count = 10;
int beam_count = 4;
int ring_count = 2;
int boom_count = 2;

int level = 1,lives = 10;
int i, j = -96, k = 1;
int speed_var = 0;

Player player;
Wall wall[50];
Ground ground1,ground2;

Ball ball[100];
Magnet magnet[5];
Flyobj fly_obj[5];
Flyobj2 fly_obj2[5];
Flyobj3 fly_obj3[5];
Fireline fireline[25];
Firebeam firebeam[20];
Waterbubble waterbubble;
Circularring circularring[2];
Bomerang bomerang[2];
Viserion viserion;
Bullet bullet;

Timer magnet_life(1);
Timer bullet_life(3);
int shield_life = 0;
int cut_life = 0;
int run_life = 0;
Display digit_disp;
float init_x, init_y;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;

Timer t60(1.0 / 60);

void speedtick()
{
    for (i=0;i<ball_count;i++)
        ball[i].position.x -= 0.5;
    for (i=0;i<magnet_count;i++)
        magnet[i].position.x -= 0.5;
    ground1.position.x -= 0.5;
    ground2.position.x -= 0.5;
    for (i=0;i<wall_count;i++)
        wall[i].position.x -= 0.5;

    for (i=0;i<fly_count;i++)
        fly_obj[i].position.x -= 0.5;
    
    for (i=0;i<fly2_count;i++)
        fly_obj2[i].position.x -= 0.5;

    for (i=0;i<fly3_count;i++)
        fly_obj3[i].position.x -= 0.5;        

    for (i=0;i<line_count;i++)
        fireline[i].position.x -= 0.5;

    for (i=0;i<beam_count;i++)
        firebeam[i].position.x -= 0.5;

    for (i=0;i<boom_count;i++)
        bomerang[i].position.x -= 0.5;    

    for (i=0;i<ring_count;i++)
        circularring[i].position.x -= 0.5;

    player.position.x = 0;
    player.offset -= 0.5;
}

void screen_pan_left(){
    for (i=0;i<ball_count;i++)
        ball[i].position.x -= 2.5;
    for (i=0;i<magnet_count;i++)
        magnet[i].position.x -= 2.5;
    ground1.position.x -= 2.5;
    ground2.position.x -= 2.5;
    for (i=0;i<wall_count;i++)
        wall[i].position.x -= 2.5;

    for (i=0;i<fly_count;i++)
        fly_obj[i].position.x -= 3.5;
    
    for (i=0;i<fly2_count;i++)
        fly_obj2[i].position.x -= 3.5;

    for (i=0;i<fly3_count;i++)
        fly_obj3[i].position.x -= 3.5;        

    for (i=0;i<line_count;i++)
        fireline[i].position.x -= 2.5;

    for (i=0;i<beam_count;i++)
        firebeam[i].position.x -= 2.5;

    for (i=0;i<boom_count;i++)
        bomerang[i].position.x -= 2.5;    

    for (i=0;i<ring_count;i++)
        circularring[i].position.x -= 2.5;

    player.position.x = 0;
    player.offset -= 2.5;
}

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {

    if(speed_var){
        speedtick();
    }    
    if(player.position.x >=2.5)
        screen_pan_left();

    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    //Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
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
    digit_disp.draw(VP);
    
    ground1.draw(VP);
    ground2.draw(VP);
        
    for (i=0;i<wall_count;i++)
    {
        wall[i].draw(VP);
    }

    for (i=0;i<ring_count;i++)
    {
        circularring[i].draw(VP);
    }

    for (i=0;i<boom_count;i++)
    {   
        if(bomerang[i].alive == 1)
            bomerang[i].draw(VP);
    }
    
    for (i=0; i<magnet_count; i++) {
        if(magnet[i].alive == 1) {
            magnet[i].draw(VP);
        }    
    }

    for (i=0;i<fly_count;i++)
        if(fly_obj[i].alive == 1) {
            fly_obj[i].draw(VP);
        }

    for (i=0;i<fly2_count;i++)
        if(fly_obj2[i].alive == 1) {
            fly_obj2[i].draw(VP);
        }

    for (i=0;i<fly3_count;i++)
        if(fly_obj3[i].alive == 1) {
            fly_obj3[i].draw(VP);
        }        

    for (i=0;i<ball_count;i++)
        if(ball[i].alive == 1) {
            ball[i].draw(VP);
        }

    for (i=0;i<line_count;i++)
        if(fireline[i].alive == 1) {
            fireline[i].draw(VP);
        }

    for (i=0;i<beam_count;i++)
        if(firebeam[i].alive == 1) {
            firebeam[i].draw(VP);
        }    

    viserion.draw(VP);

    if(bullet.alive == 1){
        bullet.draw(VP);
    }
    if(waterbubble.alive == 1){
        waterbubble.draw(VP);
    }

    player.draw(VP);
}


void tick_elements_right() { 
    for (i=0;i<ball_count;i++)
        ball[i].righttick();
    for (i=0; i<magnet_count; i++)
        magnet[i].righttick();
    for (i=0; i<wall_count; i++)
        wall[i].righttick();
    
    ground1.righttick();
    ground2.righttick();
    
    for (i=0;i<fly_count;i++)
        fly_obj[i].righttick();

    for (i=0;i<fly2_count;i++)
        fly_obj2[i].righttick();

    for (i=0;i<fly3_count;i++)
        fly_obj3[i].righttick();        

    for (i=0;i<line_count;i++)
        fireline[i].righttick();

    for (i=0;i<beam_count;i++)
        firebeam[i].righttick();

    for (i=0;i<boom_count;i++)
        bomerang[i].righttick();

    for (i=0;i<ring_count;i++)
        circularring[i].righttick();    
    
    player.offset += 0.1;
    camera_rotation_angle += 1;
}

void tick_elements_left() { 
    for (i=0;i<ball_count;i++)
        ball[i].lefttick();
    for (i=0;i<magnet_count;i++)
        magnet[i].lefttick();
    for (i=0; i<wall_count; i++)
        wall[i].lefttick();
    ground1.lefttick();
    ground2.lefttick();
    
    for (i=0;i<fly_count;i++)
        fly_obj[i].lefttick();

    for (i=0;i<fly2_count;i++)
        fly_obj2[i].lefttick();

    for (i=0;i<fly3_count;i++)
        fly_obj3[i].lefttick();        

    for (i=0;i<line_count;i++)
        fireline[i].lefttick();

    for (i=0;i<beam_count;i++)
        firebeam[i].lefttick();

    for (i=0;i<boom_count;i++)
        bomerang[i].lefttick();

    for (i=0;i<ring_count;i++)
        circularring[i].lefttick();

    if(viserion.position.x > 3)
        viserion.lefttick();            

    player.offset -= 0.1;
    camera_rotation_angle += 1;
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_SPACE);
    int shootup = glfwGetKey(window, GLFW_KEY_UP);
    int shootdown = glfwGetKey(window, GLFW_KEY_DOWN);

    if (left) {
        tick_elements_right();
    }
    if (right) {
        tick_elements_left();
    }
    if (up == GLFW_PRESS) {
        player.jump = 1;
        player.uptick();
    }
    if (up == GLFW_RELEASE) {
        player.jump = 0;
        player.downtick();
    }
    if (shootup || shootdown){
        waterbubble.alive = 1;
        waterbubble.position.x = player.position.x;
        waterbubble.position.y = player.position.y;

        if(shootup)
        {
            waterbubble.up = 1;
        }
        if(shootdown)
        {
            waterbubble.up = 0;
        }
    }
    if(player.shield == 1)
        shield_life += 1;

    if(speed_var == 1)
        run_life += 1;    

    if(player.cut == 1)
        cut_life += 1;    

    for (i=0;i<beam_count;i++)
        firebeam[i].uptick();

    for (i=0;i<boom_count;i++)
        bomerang[i].tick();    

    if(!left && !right)
    {    for (i=0;i<fly_count;i++)
            if(fly_obj[i].position.x < 5)
                fly_obj[i].slowtick();    
    }

    for (i=0;i<fly2_count;i++)
        if(fly_obj2[i].position.x < 5)
            fly_obj2[i].sinetick();    
    
    for (i=0;i<fly3_count;i++)
        if(fly_obj3[i].position.x < 5)
            fly_obj3[i].costick();

    for (i = 0; i< ball_count;i++)
    {
        if(detect_collision(player.getboundingbox(),ball[i].getboundingbox())&& ball[i].alive)
        {
            ball[i].alive = 0;
            if(i<20)
                player.score += 5;
            else
                player.score += 10;
        }
    }

    for (i = 0; i< magnet_count; i++)
    {
        if(detect_collision(player.getboundingbox(), magnet[i].getboundingbox()) && magnet[i].alive)
        {
           player.righttick();  
        }
    }

    for (i = 0; i<fly_count; i++)
    {
        if(detect_collision(fly_obj[i].getboundingbox(), player.getboundingbox()) && fly_obj[i].alive)
        {
            fly_obj[i].alive = 0;
            speed_var = 1;
            player.score += 15;
        }
    }

    for (i = 0; i<fly2_count; i++)
    {
        if(detect_collision(fly_obj2[i].getboundingbox(), player.getboundingbox()) && fly_obj2[i].alive)
        {
            fly_obj2[i].alive = 0;
            player.cut = 1;
            player.score += 20;
        }
    }

    for (i = 0; i<fly3_count; i++)
    {
        if(detect_collision(fly_obj3[i].getboundingbox(), player.getboundingbox()) && fly_obj3[i].alive)
        {
            fly_obj3[i].alive = 0;
            player.shield = 1;
            player.score += 20;
        }
    }

    for (i = 0; i<boom_count; i++)
    {
        if(detect_collision(bomerang[i].getboundingbox(), player.getboundingbox()) && bomerang[i].alive)
        {
            if(player.cut)
            {
                bomerang[i].alive = 0;
                player.score += 25;
            }
            else if(!player.safe && !player.shield)
            {
                player.position.x = 0;
                player.position.y = -2;
                lives -= 1;
            }
            
        }
    }

    for (i = 0; i<line_count; i++)
    {
        if(detect_collision(fireline[i].getboundingbox(), player.getboundingbox()) && fireline[i].alive  )
        {      
            if(!player.safe && !player.shield &&!fireline[i].killed)      
            {    player.position.x = 0;
                player.position.y = -2;
                fireline[i].killed = 1;
                lives -= 1;
            }
            if(player.cut)
                fireline[i].alive = 0;    
        }
        if(detect_collision(fireline[i].getboundingbox(), waterbubble.getboundingbox()) && fireline[i].alive && waterbubble.alive)
        {
            fireline[i].alive = 0;
            player.score += 20;
            waterbubble.alive = 0;
            waterbubble.yspeed = 0;
        }

    }

    for (i = 0; i<beam_count; i++)
    {
        if(detect_collision(firebeam[i].getboundingbox(), player.getboundingbox()) && firebeam[i].alive)
        {
            if(!firebeam[i].killed && !player.safe && !player.shield)
            {
                player.position.x = 0;
                player.position.y = -2;
                firebeam[i].killed = 1;
                lives -= 1;
            }
            if(player.cut)
                firebeam[i].alive = 0;    
        }
        if(detect_collision(firebeam[i].getboundingbox(), waterbubble.getboundingbox()) && firebeam[i].alive && waterbubble.alive)
        {
            firebeam[i].alive = 0;
            player.score += 20;
            waterbubble.alive = 0;
            waterbubble.yspeed = 0;
        }

    } 

    if(waterbubble.position.y < -2 || waterbubble.position.y > 3)
    {    
        waterbubble.alive = 0;
        waterbubble.yspeed = 0;
    }

    if(bullet.position.x > 3)
    {    
        bullet.alive = 0;
    }

    if(detect_collision(bullet.getboundingbox(), player.getboundingbox()) && bullet.alive && !player.shield && !player.safe)
    {
        lives -= 1;
        bullet.alive = 0;
    }

    for (i = 0; i<ring_count; i++)
    {
        if(detect_collision(circularring[i].getboundingbox(), player.getboundingbox()))
        {
            player.safe = i+1;
        }
    }

    if(viserion.position.x < 3)
    {
        viserion.position.x = player.position.x - 3;
        viserion.position.y = player.position.y;
    }
}  

void LevelUp()
{
    if(player.score > 90)
    {
        level = 2;
    }
    
    if(player.score > 150)
    {
        level = 3;
    }
    if(player.score >750)
    {
        cout << "CONGRATS!!!!MISSION COMPLETED!! Score:" << player.score;
        quit(window);
    }
    if(lives == 0)
    {
        cout << "You LOSE!! Score:" << player.score;
        quit(window);
    }
    if(ground1.getboundingbox().x < -198)
    {
        cout << "GAMEOVER...Score:"<<player.score;
        quit(window);
    }
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models
   
    player      = Player(0, -2, 0.25, COLOR_LIGHT_BLUE);
    
    ground1     = Ground(0, -3, COLOR_BLACK);
    ground2     = Ground(0, 6, COLOR_BLACK);

    fly_obj[0]      = Flyobj (11, -1, COLOR_DARK_BLUE);
    fly_obj2[0]      = Flyobj2 (41, 0, COLOR_YELLOW);
    fly_obj2[1]      = Flyobj2 (79, 0, COLOR_YELLOW);
    fly_obj3[0]      = Flyobj3 (9, 0, COLOR_DARK_RED);
    fly_obj3[1]      = Flyobj3 (149, 0, COLOR_DARK_RED);

    firebeam[0]     = Firebeam(39, -1, COLOR_GREEN);
    firebeam[1]     = Firebeam(64, -1, COLOR_GREEN);
    firebeam[2]     = Firebeam(123, -1, COLOR_GREEN);
    firebeam[3]     = Firebeam(161, -1, COLOR_GREEN);
    
    circularring[0]    = Circularring(52, 1 , COLOR_PURPLE);
    circularring[1]    = Circularring(84, 1 , COLOR_PURPLE); 

    bomerang[0]        = Bomerang(67, 0, COLOR_RED);
    bomerang[1]        = Bomerang(85, 0, COLOR_RED);

    viserion           = Viserion(150, player.position.y, COLOR_DARK_BLACK); 
    bullet             = Bullet(viserion.position.x + 0.5, viserion.position.y, COLOR_PURPLE);

    waterbubble        = Waterbubble(player.position.x, player.position.y, COLOR_BLUE);

    for(i =0; i< wall_count; i++){
        wall[i]        = Wall(j, 0.5, COLOR_BROWN);
        j += 8;
    }

    for(i =0; i<line_count; i++){
        fireline[i]    = Fireline(rand()%190, -rand()%2, COLOR_DARK_RED);
    }

    for(i = 0; i < ball_count; i++){
        if(i<50)
            ball[i]    = Ball(rand()%190, rand()%3, COLOR_YELLOW);            
        
        else
            ball[i]    = Ball(rand()%190, rand()%3, COLOR_DARK_GREEN);
    }
    
    for(i =0; i<magnet_count; i++){
        magnet[i]      = Magnet(k, 2, COLOR_RED);
        k += 10;
    }

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
    char score_disp[1000];
    digit_disp.set_position(-7,3.25);

    window = initGLFW(width, height);

    initGL (window, width, height);

    // Matrices.projection = glm::perspective(glm::radians(screen_zoom), (float)height / (float)width, 0.1f, 100.0f);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            digit_disp.update(player.score);
            sprintf(score_disp, "Level: %d Lives: %d ", level, lives);
            glfwSetWindowTitle(window, score_disp);
    
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            // tick_elements();
             tick_input(window);
             
             LevelUp();
        }

        if(magnet_life.processTick()){
            for (i=0;i<magnet_count;i++)
                magnet[i].disappear();
        }

        if(bullet_life.processTick()){
            bullet.alive = 1;
            bullet.position.x = viserion.position.x + 0.5;
            bullet.position.y = viserion.position.y;
        }

        if(run_life >= 25){
            speed_var = 0;
            run_life = 0;
        }

        if(shield_life >= 500){
                player.shield = 0;
                shield_life = 0;
        }
        if(cut_life >= 500){
                player.cut = 0;
                cut_life = 0;
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}

