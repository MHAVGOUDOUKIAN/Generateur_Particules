#ifndef BALLTEST_HPP_INCLUDED
#define BALLTEST_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "inline.h"

class BallTest
{
    public:
        BallTest();
        BallTest(const float X,const float Y);
        BallTest(const float X,const float Y, const float radius);
        ~BallTest();

        void update(const sf::Time& deltaTime);
        void draw(sf::RenderWindow& window);
        void launch(const float X, const float Y, const float vit_X, const float vit_Y); // Lancer la balle au point (X,Y) à la vitesse V(vit_x, vit_y)
        void processPhysics(void);
        void processCollision(void);
        float dist(const sf::Vector2f& p1, const sf::Vector2f& p2);
    
    public:
        float m_masse, m_radius;
        sf::Vector2f m_pos, m_vit, m_acc;
        sf::CircleShape m_sprite;
        sf::Color m_color;
        static int nb_ball;
        int ID;
};

#endif // BALLTEST_HPP_INCLUDED
