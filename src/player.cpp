#include "player.h"
#include "main.h"

Player::Player(float x, float y,float speed, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->score = 0;
    this->speed = speed;
    this->jump = 0;
    this->safe = 0;
    this->cut = 0;
    this->shield = 0;
    this -> var = 0;
    this->offset = 0;
    this->t = 0;
    speed2 = speed;
    acceleration = 0.05;

    GLfloat vertex_buffer_data5[1000];
    int n = 100, i, t = 0;

    static const GLfloat vertex_buffer_data1[] = {

        -0.5f, -0.25f, -1.0f,
        -0.5f, -0.5f, -1.0f,
        0.5f, -0.25f, -1.0f,

        -0.5f, -0.25f, -1.0f,
        0.5f, -0.5f, -1.0f,
        0.5f, -0.25f, -1.0f,
        
        0.5f, -1.0f,-1.0f, 
        0.0f, -0.25f,-1.0f,
        -0.5f, -1.0f, -1.0f


    };
    static const GLfloat vertex_buffer_data[] = {

        -0.57f, -0.2f, -1.0f,
        -0.57f, -0.45f, -1.0f,
        0.57f, -0.2f, -1.0f,

        -0.57f, -0.2f, -1.0f,
        0.57f, -0.45f, -1.0f,
        0.57f, -0.2f, -1.0f,
        
        0.57f, -1.0f,-1.0f, 
        0.0f, -0.2f,-1.0f,
        -0.57f, -1.0f, -1.0f


    };
    static const GLfloat vertex_buffer_data2[] = {
        0.05, -1.6, -1.0, 
        0.0,  -1.0, -1.0, 
        0.1,  -1.0, -1.0, 

        0.15,-1.6, -1.0,
        0.1, -1.0, -1.0, 
        0.2, -1.0, -1.0, 

        -0.05, -1.6, -1.0,
        0.0, -1.0, -1.0, 
        -0.1, -1.0, -1.0,

        -0.15, -1.6, -1.0,
        -0.1, -1.0, -1.0,
        -0.2, -1.0, -1.0 
    };

    static const GLfloat vertex_buffer_data3[] = {
       -0.6, -0.2, -1.0,
       0.6, -0.2, -1.0,
       -0.6, -1.05, -1.0,

       0.6, -0.2, -1.0,
       -0.6, -1.05, -1.0,
       0.6, -1.05, -1.0
    };

    static const GLfloat vertex_buffer_data4[] = {
       0.5, -0.55, -1.0,
       0.5, -0.8, -1.0,
       1.0, -0.625, -1.0,

       -0.5, -0.55, -1.0,
       -0.5, -0.8, -1.0,
       -1.0, -0.625, -1.0,

       -0.125, -0.25, -1.0,
       0.125, -0.25, -1.0,
       0.0, 0.25, -1.0
    };

    for(i=0;i<9*n;i=i+9)
    {
        vertex_buffer_data5[i]=0.0f;
        vertex_buffer_data5[i+1]=-0.75f;
        vertex_buffer_data5[i+2]=-1.0f;

        vertex_buffer_data5[i+3]=0.35f*(cos(2*3.14*t/n));
        vertex_buffer_data5[i+4]=0.35f*(sin(2*3.14*t/n)) - 0.75;
        vertex_buffer_data5[i+5]=-1.0f;

        vertex_buffer_data5[i+6]=0.35f*(cos(2*3.14*(t+1)/n));
        vertex_buffer_data5[i+7]=0.35f*(sin(2*3.14*(t+1)/n)) - 0.75;
        vertex_buffer_data5[i+8]=-1.0f;
        t=t+1;
    };
    this->object = create3DObject(GL_TRIANGLES, 3*3, vertex_buffer_data, COLOR_DARK_BLUE, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, 3*3, vertex_buffer_data1, color, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data2, COLOR_RED, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data3, COLOR_BLACK, GL_FILL);
    this->object4 = create3DObject(GL_TRIANGLES, 3*3, vertex_buffer_data4, COLOR_BLACK, GL_FILL);
    this->object5 = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data5, COLOR_YELLOW, GL_FILL);
}

void Player::draw(glm::mat4 VP) {
    int n=100;

    if(this->safe && var < n){
        if(this->safe == 1)
            this->position.x= offset+ 52 + 1.35f*(sin(3.14*t/n));
        
        if(this->safe == 2)
            this->position.x= offset+ 84 + 1.35f*(sin(3.14*t/n));
        this->position.y= 1.25 + 1.35f*(cos(3.14*t/n));
        
        t=t+1;
        var += 1;
    }
    else{
        safe = 0;
        var = 0;
        t = 0;
    }     
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    if(this->shield)
        draw3DObject(this->object3);
    if(this->cut){
        draw3DObject(this->object4);
        draw3DObject(this->object5);
    }
    draw3DObject(this->object);            
    draw3DObject(this->object1);
    if(this->jump)
        draw3DObject(this->object2);    
}

void Player::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Player::lefttick() {
     this->position.x -= this->speed;
}

void Player::righttick() {
     this->position.x += this->speed;
}

void Player::uptick() {
    if(this->position.y < 3)
    {
        this->position.y += this->speed;
    }
}

void Player::downtick() {
    if(this->position.y > -1.9)
    {
        this->speed = 0;
        this->speed += acceleration;
        this->position.y -= this->speed;
    }
    this->speed = speed2;
}

void Player::update_score(int x) {
    if(x == 1)
        this->score += 5;
    if(x == 2)
        this->score += 10;
}

bounding_box_t Player::getboundingbox() {

    bounding_box_t temp;
    temp.x = this->position.x;
    temp.y = this->position.y;
    temp.height = 0.75;
    temp.width = 1;
    return temp;
}