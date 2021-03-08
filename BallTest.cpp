#include <iostream>
#include <cmath>
#include "BallTest.hpp"

int BallTest::nb_ball = 0;

#define g 10 * 150
#define h 5
#define PI 3.14159265358979323846

BallTest::BallTest(): m_masse(5), m_radius(60), m_pos(sf::Vector2f(0,0)), m_vit(sf::Vector2f(0,0)), m_acc(sf::Vector2f(0,0))
{
    int color = randomi(1,5);

    if(color == 1) { m_color = sf::Color::White; }
    else if(color == 2) { m_color = sf::Color::Cyan; }
    else if(color == 3) { m_color = sf::Color::Red; }
    else if(color == 4) { m_color = sf::Color::Yellow; }
    else if(color == 5) { m_color = sf::Color::Green; }

    m_sprite.setFillColor(m_color);
    m_sprite.setRadius(m_radius);

    nb_ball++;
    ID = nb_ball;
}

BallTest::BallTest(const float X,const float Y): m_masse(5), m_radius(60), m_pos(sf::Vector2f(X,Y)), m_vit(sf::Vector2f(0,0)), m_acc(sf::Vector2f(0,0))
{
    int color = randomi(1,5);

    if(color == 1) { m_color = sf::Color::White; }
    else if(color == 2) { m_color = sf::Color::Cyan; }
    else if(color == 3) { m_color = sf::Color::Red; }
    else if(color == 4) { m_color = sf::Color::Yellow; }
    else if(color == 5) { m_color = sf::Color::Green; }

    m_sprite.setFillColor(m_color);
    m_sprite.setRadius(m_radius);

    nb_ball++;
    ID = nb_ball;
}

BallTest::BallTest(const float X,const float Y, const float radius): m_masse(5), m_radius(radius), m_pos(sf::Vector2f(X,Y)), m_vit(sf::Vector2f(0,0)), m_acc(sf::Vector2f(0,0))
{
    int color = randomi(1,5);

    if(color == 1) { m_color = sf::Color::White; }
    else if(color == 2) { m_color = sf::Color::Cyan; }
    else if(color == 3) { m_color = sf::Color::Red; }
    else if(color == 4) { m_color = sf::Color::Yellow; }
    else if(color == 5) { m_color = sf::Color::Green; }

    m_sprite.setFillColor(m_color);
    m_sprite.setRadius(m_radius);

    nb_ball++;
    ID = nb_ball;
}

void BallTest::update(const sf::Time& deltaTime)
{
    m_vit.x += m_acc.x * deltaTime.asSeconds();
    m_vit.y += m_acc.y * deltaTime.asSeconds();
    m_pos.x += m_vit.x * deltaTime.asSeconds();
    m_pos.y += m_vit.y * deltaTime.asSeconds();

    if(fabs(m_vit.x*m_vit.y + m_vit.y*m_vit.y) < 0.01f)
    {
        m_vit.x = 0;
        m_vit.y = 0;
    }
}

void BallTest::processPhysics(void) // Problème de la balle lancée en (x,y) à la vitesse V(v_x,v_y)
{

}

void BallTest::processCollision(void) // Rebond entre la balle et un support = lancer de la balle à une nouvelle vitesse au point de collision
{

}

void BallTest::launch(const float X, const float Y, const float vit_X, const float vit_Y)
{
    m_pos = sf::Vector2f(X,Y);
    m_vit = sf::Vector2f(vit_X,vit_Y);
}

void BallTest::draw(sf::RenderWindow& window)
{
    m_sprite.setPosition(m_pos.x - m_radius , m_pos.y - m_radius);
    window.draw(m_sprite);
}

float BallTest::dist(const sf::Vector2f& p1, const sf::Vector2f& p2) { return sqrtf((p1.x + p2.x)*(p1.x + p2.x) + (p1.y + p2.y)*(p1.y + p2.y)); }

BallTest::~BallTest() {}
