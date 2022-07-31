#include "Entities.h"
#include <cmath>


Entities::Entities()
{
sf::Joystick::update();

// sound initialization
for (int i=0; i<c_circles; i++) { soundWall[i].setBuffer(res.getBuff(shortSound::ID::Wall)); soundWall[i].setVolume(40);}
soundCollide.setBuffer(res.getBuff(shortSound::ID::Collide)); soundCollide.setVolume(50);
soundHealth.setBuffer(res.getBuff(shortSound::ID::Health_Unit)); soundHealth.setVolume(50);
soundScore.setBuffer(res.getBuff(shortSound::ID::Score_Unit)); soundScore.setVolume(50);

//triger to read inputs from keyboard
isKeyboard =  true;

Player.setVec(700,200);
Player.autoSetPos();
Player.setOutline(sf::Color::Red);
Player.setColor(sf::Color::White);
Player.setCollider();
Player.health = 1;
Player.score = 0;

player_Up = false;
player_Down = false;
player_Left = false;
player_Right = false;

std::cout << "Bools " << player_Up <<" "<< player_Down <<" "<< player_Left <<" "<< player_Right << std::endl;

// health rect hayze line coordinats
line[0] = sf::Vector2f(10,10);
line[1] = sf::Vector2f(100,100);

    // making rectangles of score and health
    A.autoSetPos();
    B.autoSetPos();
    B.setFillColor(sf::Color::Blue);
    B.setOutlineColor(sf::Color::White);

    A.health = 0; A.score = 1; // score unit
    B.health = 1; B.score = 0; // health unit

    // sound events
    for (int i=0; i < 3 ; i++) { sounder[i] = false; std::cout << " sounder "  << i << " " << sounder[i]; }
    for (int i=0; i < c_circles ; i++) { getballS[i] = false; std::cout << " getballS "  << i << " " << getballS[i]; }
}

Entities::~Entities() {}

void Entities::resetEntitiesPosition()
{
    sf::Joystick::update();

    // player goes to start place
    Player.setVec(700,200);
    Player.autoSetPos();
    Player.setOutline(sf::Color::Red);
    Player.setColor(sf::Color::White);
    Player.setCollider();
    Player.health = 1;
    Player.score = 0;

    player_Up = false;
    player_Down = false;
    player_Left = false;
    player_Right = false;

    // circles goes to starting position
    this->setCirclesDirectPos();
    this->setCirclesRandomDirections();
}

int Entities::getCirclesSize() {  return sizeof (circles) / sizeof (Circle());  }

void Entities::setCirclesDirectPos()
{
    float bum = 100.f;
    for (int i=0; i<c_circles; i++)
    {
       circles[i].setVec(bum,bum);
       bum += 100.f;
    }
}

void Entities::setCirclesRandomDirections()
{
    //srand(time(nullptr));
    for (int i=0; i<c_circles; i++)
    {

        float x = 100 - rand()%100;
        float y = 100 - rand()%100;
        std::cout << " float x y " << x << " " << y << std::endl;

        if (x >= 50) circles[i].setDirection(direction::ID_X::LEFT);
        if (x < 50) circles[i].setDirection(direction::ID_X::RIGHT);
        if (y >= 50) circles[i].setDirection(direction::ID_Y::UP);
        if (y < 50) circles[i].setDirection(direction::ID_Y::DOWN);
    }

}

void Entities::setCirclesRandomColor() { for (int i=0; i<c_circles; i++) circles[i].setRandColor(); }

void Entities::update_Entities()
{
    // for enemy entityes
    for (int i=0; i<c_circles; i++)
    {
        if (circles[i].getDirectionX() == direction::ID_X::LEFT)  circles[i].moveVec(-1.f,0.f); // cout << "DIR" << endl;
        if (circles[i].getDirectionX() == direction::ID_X::RIGHT) circles[i].moveVec(1.f,0.f); // cout << "DIR" << endl;
        if (circles[i].getDirectionY() == direction::ID_Y::UP) circles[i].moveVec(0.f,-1.f); // cout << "DIR" << endl;
        if (circles[i].getDirectionY() == direction::ID_Y::DOWN) circles[i].moveVec(0.f,1.f); // cout << "DIR" << endl;
    }

    // for Player
    if (player_Up) {Player.moveVec(0, -1); };
    if (player_Down) {Player.moveVec(0, +1); };
    if (player_Left) {Player.moveVec(-1, 0); };
    if (player_Right) {Player.moveVec(+1, 0); };

    // for hayze line
    this->setLinePoints(Player.getX(), Player.getY(), A.centrX, A.centrY);
};

void Entities::brainwashCollide()
{
    // circles with wall
    for(int i=0; i<c_circles; i++)
    {
        for (int w=0; w<8; w++)
        {
            if (circles[i].getCollidePoints(w).x <= 0) { circles[i].setDirection(direction::ID_X::RIGHT); getballS[i] = true; };
            if (circles[i].getCollidePoints(w).x >= world_S.x) { circles[i].setDirection(direction::ID_X::LEFT); getballS[i] = true; };
            if (circles[i].getCollidePoints(w).y <= 0) { circles[i].setDirection(direction::ID_Y::DOWN); getballS[i] = true; };
            if (circles[i].getCollidePoints(w).y >= world_S.y) { circles[i].setDirection(direction::ID_Y::UP); getballS[i] = true; };
        }
    }

    // player with score and health units
    float HyuzeA = sqrt(  pow((Player.getX() - A.centrX), 2) + pow((Player.getY() - A.centrY), 2)  );
    float HyuzeB = sqrt(  pow((Player.getX() - B.centrX), 2) + pow((Player.getY() - B.centrY), 2)  );

    if ( HyuzeA < A.touch_line * 2 && A.trigerAble && Player.getColor() == sf::Color::White)
                {
                    Player.health += A.health;
                    Player.score  += A.score;
                    A.trigerAble = false;

                    std::cout << " A Trigged " << std::endl;
                    sounder[2] = true; // score unit
                };

    if ( HyuzeB < B.touch_line * 2 && B.trigerAble)

                {
                    Player.setColor(sf::Color::White);
                    Player.health += B.health;
                    Player.score  += B.score;
                    B.trigerAble = false;

                    std::cout << " B Trigged " << std::endl;
                    sounder[1] = true; // health unit
                };

    // player with circles
    for(int i=0; i<c_circles; i++)
    {
        float Hyuze = sqrt(  pow((Player.getX() - circles[i].getX()), 2) + pow((Player.getY() - circles[i].getY()), 2)  );

        if ( (Hyuze < (Player.getRadius()*2)) )
            {
             circles[i].reverseAndForce(20); // forced mooving
             Player.setColor(circles[i].getColor());
             Player.health += circles[i].health;
             Player.score += circles[i].score;

             sounder[0] = true; // enemy collide
            }
     }
};

void Entities::resetScoreHealthPlayer()
{
 Player.score = 0;
 Player.health = 2;
}


void Entities::HandlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
    if(key == sf::Keyboard::Up) {player_Up = isPressed;}
    else if(key == sf::Keyboard::Down) {player_Down = isPressed;}
    else if(key == sf::Keyboard::Left) {player_Left = isPressed;}
    else if(key == sf::Keyboard::Right) {player_Right = isPressed;}
    else {};
}

void Entities::gamePad()
{
   // retriging to Game Pad inputs
   if (sf::Joystick::hasAxis(1, sf::Joystick::X))  isKeyboard = false;
   if (sf::Joystick::hasAxis(1, sf::Joystick::Y))  isKeyboard = false;

   if(!isKeyboard)
    {

    // entering the value from the joystick into a variable
    float X = sf::Joystick::getAxisPosition(1, sf::Joystick::X);
    float Y = sf::Joystick::getAxisPosition(1, sf::Joystick::Y);

    // каждую ось проверяем отдельно так как значения приходят последовательно.
    if (Y < -10.f) {player_Up = true; }
    else if (10.f < Y) {player_Down = true; }
    else if (-10 < Y < 10.f) {player_Up = false; player_Down = false; }
    else {};

    if (X < -10.f) {player_Left = true; }
    else if (10.f < X) {player_Right = true; }
    else if (-10.f < X < 10.f) {player_Left = false; player_Right = false; }
    else {};
    }
}

void Entities::keyBoard()
{
    //his func making player moving with game pad inputing
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) isKeyboard = true;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) isKeyboard = true;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) isKeyboard = true;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) isKeyboard = true;

    if(isKeyboard)
    {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {player_Up = true; }
    else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {player_Up = false; }
    else{};

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {player_Down = true; }
    else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {player_Down = false; }
    else{};

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {player_Left = true; }
    else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {player_Left = false; }
    else{};

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {player_Right = true; }
    else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {player_Right = false; }
    else {};
    }

}

sf::Vector2f Entities::get_Entity_CollidePoints(int number, int i)
{
    sf::Vector2f ret(circles[number].getCollidePoints(i).x, circles[number].getCollidePoints(i).y);
    return ret;
}

sf::CircleShape& Entities::getDraw(int i)
{
    return circles[i].getCircle();
}

sf::CircleShape& Entities::getPlayer()
{
    return Player.getCircle();
}

void Entities::setLinePoints(float a, float b, float c, float d)
{
    float r = Player.getRadius();

    line[0] = sf::Vector2f(a + r,b + r);
    line[1] = sf::Vector2f(c + r,d + r);
}

sf::Vector2f& Entities::getPlayerCoordinates()
{
    return Player.getVec();
}
