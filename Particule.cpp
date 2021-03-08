#include "Particule.hpp"
#include <cmath>

#define g 10 * 150
#define h 5
#define PI 3.14159265358979323846

    //////////////////////////////////////////////////////////////
    ////////////// Particule de base /////////////////////////////
    //////////////////////////////////////////////////////////////

Particule::Particule() : m_isDead(false), m_pos(sf::Vector2f(0,0)), m_vit(sf::Vector2f(0,0)), m_lifeTime(0.f), m_lifeTimeMax(0.2f) {}

Particule::Particule(const float X,const float Y, sf::PrimitiveType type, std::size_t nb_vertex) : m_isDead(false), m_pos(sf::Vector2f(X,Y)), m_vit(sf::Vector2f(0,0)),
m_lifeTime(0.f), m_lifeTimeMax(0.2f), m_forme(type, nb_vertex) {}

Particule::Particule(const float X,const float Y, sf::PrimitiveType type, std::size_t nb_vertex, float dureeVie): m_isDead(false), m_pos(sf::Vector2f(X,Y)),
m_vit(sf::Vector2f(0,0)), m_lifeTime(0.f), m_lifeTimeMax(dureeVie), m_forme(type, nb_vertex) {}
Particule::~Particule() {}



    //////////////////////////////////////////////////////////////
    ////////////// Particule Ball ////////////////////////////////
    //////////////////////////////////////////////////////////////

Particule_Ball::Particule_Ball() : Particule(0,0, sf::Triangles, 75), m_posInit(sf::Vector2f(m_pos.x, m_pos.y)), m_vitInit(sf::Vector2f(m_vit.x, m_vit.y)),
m_timeElapsedJump(0), m_radius(15), m_radiusInit(m_radius), m_masse(10)
{
    m_lifeTimeMax = 2.f;
    int color = randomi(1,5);

    if(color == 1) { m_color = sf::Color::Blue; }
    else if(color == 2) { m_color = sf::Color::Cyan; }
    else if(color == 3) { m_color = sf::Color::Red; }
    else if(color == 4) { m_color = sf::Color::Yellow; }
    else if(color == 5) { m_color = sf::Color::Green; }
}

Particule_Ball::Particule_Ball(const float X, const float Y) : Particule(X,Y,sf::Triangles, 75), m_posInit(sf::Vector2f(m_pos.x, m_pos.y)), m_vitInit(sf::Vector2f(m_vit.x, m_vit.y)),
m_timeElapsedJump(0), m_radius(15), m_radiusInit(m_radius), m_masse(10)
{
    int color = randomi(1,5);
    m_lifeTimeMax = 2.f;

    if(color == 1) { m_color = sf::Color::Blue; }
    else if(color == 2) { m_color = sf::Color::Cyan; }
    else if(color == 3) { m_color = sf::Color::Red; }
    else if(color == 4) { m_color = sf::Color::Yellow; }
    else if(color == 5) { m_color = sf::Color::Green; }
}

Particule_Ball::Particule_Ball(const float X,const float Y, const float dureeVie): Particule(X,Y,sf::Triangles, 75, dureeVie), m_posInit(sf::Vector2f(m_pos.x, m_pos.y)), m_vitInit(sf::Vector2f(m_vit.x, m_vit.y)),
m_timeElapsedJump(0), m_radius(15), m_radiusInit(m_radius), m_masse(10)
{
    int color = randomi(1,5);

    if(color == 1) { m_color = sf::Color::Blue; }
    else if(color == 2) { m_color = sf::Color::Cyan; }
    else if(color == 3) { m_color = sf::Color::Red; }
    else if(color == 4) { m_color = sf::Color::Yellow; }
    else if(color == 5) { m_color = sf::Color::Green; }
}

void Particule_Ball::update(const sf::Time& deltaTime)
{
    m_timeElapsedJump += deltaTime.asSeconds();
    m_lifeTime += deltaTime.asSeconds();

    if(m_lifeTime>m_lifeTimeMax) { m_isDead = true; }

    processPhysics();

    processCollision();

    m_radius = m_radiusInit * (m_lifeTimeMax-m_lifeTime)/m_lifeTimeMax;

    for(int i=0; i < int(m_forme.getVertexCount()) ; i+=3)
    {
        m_forme[i].position = sf::Vector2f(m_pos.x,m_pos.y);
        m_forme[i+1].position = sf::Vector2f(cos(15*(i/3)* PI/180)*m_radius + m_pos.x, sin(15*(i/3)* PI/180)*m_radius + m_pos.y);
        m_forme[i+2].position = sf::Vector2f(cos(15*(i/3+1)* PI/180)*m_radius + m_pos.x, sin(15*(i/3+1)* PI/180)*m_radius + m_pos.y);

        m_forme[i].color = m_color;
        m_forme[i+1].color = m_color;
        m_forme[i+2].color = m_color;
    }
}

void Particule_Ball::processPhysics(void) // Problème de la balle lancée en (x,y) à la vitesse V(v_x,v_y)
{
        m_pos.y = -((-0.5) * g * m_timeElapsedJump * m_timeElapsedJump + m_vitInit.y * m_timeElapsedJump) + m_posInit.y;
        //m_pos.x = m_vitInit.x * m_timeElapsedJump + m_posInit.x; // Cas sans frottements
        m_pos.x = (m_masse/h) * m_vitInit.x * (1-exp(-h * m_timeElapsedJump / m_masse)) + m_posInit.x; // Cas avec frottements (air)

        m_vit.y = (-1) * g * m_timeElapsedJump + m_vitInit.y;
        //m_vit.x = m_vitInit.x; // Cas sans frottements
        m_vit.x = m_vitInit.x * exp((-h*m_timeElapsedJump)/m_masse); // Cas avec frottements de (air)
}

void Particule_Ball::processCollision(void) // Rebond entre la balle et un support = lancer de la balle à une nouvelle vitesse au point de collision
{
    if(m_pos.y - m_radius < 0) {
        m_pos.y = m_radius;
        m_vit.y = m_vit.y*(-1);
    }
    else if(m_pos.y + m_radius > 1080) {
        if(m_vit.y > 0 && m_vit.y < 5) {// Cas ou la balle ne rebondit plus
            m_pos.y = 1080-m_radius;
            m_vit.y = 0;
        }
        else { // Cas du rebond
            m_pos.y = 1080-m_radius;
            m_vit.y = m_vit.y*(-1) * 0.65 /* Facteur d'Adhérence du sol */;
        }
    }

    if(m_pos.x - m_radius < 0) {
        m_pos.x = m_radius;
        m_vit.x = m_vit.x * (-1);
    } // Rebond sur les cotés
    else if(m_pos.x + m_radius > 1920) {
        m_pos.x = 1920 - m_radius;
        m_vit.x = m_vit.x * (-1);
    }
    if(abs(m_vit.x) < 10) {
        m_vit.x = 0;
    }

    launch(m_pos.x, m_pos.y, m_vit.x, m_vit.y);
}

void Particule_Ball::launch(const float X, const float Y, const float vit_X, const float vit_Y)
{
    m_pos = sf::Vector2f(X,Y);
    m_posInit = m_pos;

    m_vit = sf::Vector2f(vit_X,vit_Y);
    m_vitInit = m_vit;

    m_timeElapsedJump = 0;
}

void Particule_Ball::draw(sf::RenderWindow& window)
{
    window.draw(m_forme);
}

Particule_Ball::~Particule_Ball() {}



    //////////////////////////////////////////////////////////////
    ////////////// Particule Snow ////////////////////////////////
    //////////////////////////////////////////////////////////////

Particule_Snow::Particule_Snow() : Particule(0,0,sf::Triangles, 54), m_radius(5), m_radiusInit(m_radius)
{
    m_color = sf::Color::White;
    m_lifeTimeMax = 4.f;
}

Particule_Snow::Particule_Snow(const float X, const float Y) : Particule(X,Y,sf::Triangles, 54), m_radius(5), m_radiusInit(m_radius)
{
    m_color = sf::Color::White;
    m_lifeTimeMax = 4.f;
}

Particule_Snow::Particule_Snow(const float X,const float Y, const float dureeVie) : Particule(X,Y,sf::Triangles, 54, dureeVie), m_radius(5), m_radiusInit(m_radius)
{
    m_color = sf::Color::White;
}

void Particule_Snow::update(const sf::Time& deltaTime)
{
    m_lifeTime += deltaTime.asSeconds();

    if(m_lifeTime>m_lifeTimeMax || m_pos.x < 0 || m_pos.x > 1920 + m_radius) { m_isDead = true; }

    processPhysics();
    processCollision();

    m_radius = m_radiusInit * (m_lifeTimeMax-m_lifeTime)/m_lifeTimeMax;

    for(int i=0; i < int(m_forme.getVertexCount()) ; i+=3)
    {
        m_forme[i].position = sf::Vector2f(m_pos.x,m_pos.y);
        m_forme[i+1].position = sf::Vector2f(cos(20*(i/3)* PI/180)*m_radius + m_pos.x, sin(20*(i/3)* PI/180)*m_radius + m_pos.y);
        m_forme[i+2].position = sf::Vector2f(cos(20*(i/3+1)* PI/180)*m_radius + m_pos.x, sin(20*(i/3+1)* PI/180)*m_radius + m_pos.y);

        m_forme[i].color = m_color;
        m_forme[i+1].color = m_color;
        m_forme[i+2].color = m_color;
    }

}

void Particule_Snow::processPhysics(void) // Problème de la balle lancée en (x,y) à la vitesse V(v_x,v_y)
{
    m_pos.x += m_vit.x;
    m_pos.y += m_vit.y;
}

void Particule_Snow::launch(const float X, const float Y, const float vit_X, const float vit_Y)
{
    m_pos = sf::Vector2f(randomf(0.f, 1920.f),-1);
    m_vit = sf::Vector2f(randomf(-2.f,2.f),randomf(2,7));
}

void Particule_Snow::draw(sf::RenderWindow& window)
{
    window.draw(m_forme);
}

Particule_Snow::~Particule_Snow() {}



    //////////////////////////////////////////////////////////////
    ////////////// Particule Dot ////////////////////////////////
    //////////////////////////////////////////////////////////////

Particule_Dot::Particule_Dot() : Particule(0,0,sf::Quads, 4), m_taille(2) {
    m_color = sf::Color::Yellow;
    m_lifeTimeMax = 2.f;
}

Particule_Dot::Particule_Dot(const float X, const float Y) : Particule(X,Y,sf::Quads, 4), m_taille(2) {
    m_color = sf::Color::Yellow;
    m_lifeTimeMax = 2.f;
}

Particule_Dot::Particule_Dot(const float X,const float Y, const float dureeVie) : Particule(X,Y,sf::Quads, 4, dureeVie), m_taille(2) {
    m_color = sf::Color::Yellow;
}

void Particule_Dot::update(const sf::Time& deltaTime)
{
    m_lifeTime += deltaTime.asSeconds();

    if(m_lifeTime>m_lifeTimeMax || m_pos.x < 0 || m_pos.x > 1920) { m_isDead = true; }

    processPhysics();
    processCollision();

    m_forme[0].position = sf::Vector2f(m_pos.x - m_taille/2, m_pos.y - m_taille/2);
    m_forme[1].position = sf::Vector2f(m_pos.x + m_taille/2, m_pos.y - m_taille/2);
    m_forme[2].position = sf::Vector2f(m_pos.x + m_taille/2, m_pos.y + m_taille/2);
    m_forme[3].position = sf::Vector2f(m_pos.x - m_taille/2, m_pos.y + m_taille/2);

    m_forme[0].color = m_color;
    m_forme[1].color = m_color;
    m_forme[2].color = m_color;
    m_forme[3].color = m_color;
}

void Particule_Dot::processPhysics(void) // Problème de la balle lancée en (x,y) à la vitesse V(v_x,v_y)
{
    m_pos.x += m_vit.x;
    m_pos.y += m_vit.y;
}

void Particule_Dot::launch(const float X, const float Y, const float vit_X, const float vit_Y)
{
    m_pos = sf::Vector2f(X,Y);
    m_vit = sf::Vector2f(randomf(-10.f,10.f),randomf(-10.f,10.f));
}

void Particule_Dot::draw(sf::RenderWindow& window)
{
    window.draw(m_forme);
}

Particule_Dot::~Particule_Dot() {}



    //////////////////////////////////////////////////////////////
    ////////////// Particule Fire ////////////////////////////////
    //////////////////////////////////////////////////////////////

Particule_Fire::Particule_Fire() : Particule(0,0,sf::Quads, 4), m_taille(5), phase(randomf(0,6)), amplitude(randomf(0.2,0.5)) {
    int color = randomi(1,3);

    if(color == 1) { m_color = sf::Color::Red; }
    else if(color == 2) { m_color = sf::Color::Yellow; }
    else if(color == 3) { m_color = sf::Color(255,128,0); }

    m_lifeTimeMax = 0.5f;
}

Particule_Fire::Particule_Fire(const float X, const float Y) : Particule(X,Y,sf::Quads, 4), m_taille(5), phase(randomf(0,6)), amplitude(randomf(0.2,0.5))  {
    int color = randomi(1,3);

    if(color == 1) { m_color = sf::Color::Red; }
    else if(color == 2) { m_color = sf::Color::Yellow; }
    else if(color == 3) { m_color = sf::Color(255,128,0); }

    m_lifeTimeMax = 0.5f;
}

Particule_Fire::Particule_Fire(const float X,const float Y, const float dureeVie) : Particule(X,Y,sf::Quads, 4, randomf(0.3,1.5)), m_taille(5), phase(randomf(0,6)), amplitude(randomf(0.2,0.5))  {
    int color = randomi(1,3);

    if(color == 1) { m_color = sf::Color::Red; }
    else if(color == 2) { m_color = sf::Color::Yellow; }
    else if(color == 3) { m_color = sf::Color(255,128,0); }
}

void Particule_Fire::update(const sf::Time& deltaTime)
{
    m_lifeTime += deltaTime.asSeconds();

    if(m_lifeTime>m_lifeTimeMax || m_pos.x < 0 || m_pos.x > 1920) { m_isDead = true; }

    processPhysics();
    processCollision();

    m_forme[0].position = sf::Vector2f(m_pos.x - m_taille/2, m_pos.y - m_taille/2);
    m_forme[1].position = sf::Vector2f(m_pos.x + m_taille/2, m_pos.y - m_taille/2);
    m_forme[2].position = sf::Vector2f(m_pos.x + m_taille/2, m_pos.y + m_taille/2);
    m_forme[3].position = sf::Vector2f(m_pos.x - m_taille/2, m_pos.y + m_taille/2);

    m_forme[0].color = m_color;
    m_forme[1].color = m_color;
    m_forme[2].color = m_color;
    m_forme[3].color = m_color;
}

void Particule_Fire::processPhysics(void) // Problème de la balle lancée en (x,y) à la vitesse V(v_x,v_y)
{
    m_pos.x += amplitude*cos(m_lifeTime*5+phase);
    m_pos.y += m_vit.y*0.5;
}

void Particule_Fire::launch(const float X, const float Y, const float vit_X, const float vit_Y)
{
    m_pos = sf::Vector2f(randomi(X-5,X+5), randomi(Y-5,Y+5));
    m_vit = sf::Vector2f(0,randomf(-2.f,-1.f));
}

void Particule_Fire::draw(sf::RenderWindow& window)
{
    window.draw(m_forme);
}

Particule_Fire::~Particule_Fire() {}
