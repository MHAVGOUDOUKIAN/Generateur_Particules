#include <iostream>
#include <time.h>
#include <cmath>
#include "Engine.hpp"
#include "BallTest.hpp"
#include "Ball.hpp"

Engine::Engine(): m_window(sf::VideoMode(1920,1080), "Ma fenêtre", sf::Style::Fullscreen), generator(50,50)
{
    TimePerFrame = sf::seconds(1.f/120.f);
    srand(time(NULL));
    generator.setDuration(2.f);
    generator.setLifeTimeParticule(2.f);
    generator.enableDuration(false);
}

void Engine::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (m_window.isOpen())
    {
        processEvents();
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > TimePerFrame)
        {
            processEvents();
            timeSinceLastUpdate -= TimePerFrame;
            update(TimePerFrame);
        }
        render();
    }
}

void Engine::processEvents(void)
{
    sf::Event event;
    while(m_window.pollEvent(event))
    {
        switch(event.type)
        {
            case sf::Event::KeyPressed:
                handleKeyInput(event.key.code, true);
                break;

            case sf::Event::KeyReleased:
                handleKeyInput(event.key.code, false);
                break;

            case sf::Event::MouseButtonPressed:
                handleMouseInput(event.mouseButton.button, true);
                break;

            case sf::Event::MouseButtonReleased:
                handleMouseInput(event.mouseButton.button, false);
                break;
        }
    }
}

void Engine::handleKeyInput(sf::Keyboard::Key key, bool isPressed)
{
    if(key == sf::Keyboard::Escape) { this-> Echap = isPressed; }
    if(key == sf::Keyboard::Left) {
        this-> Left = isPressed;
        if(!isPressed) { this->LeftPressed=false; }
    }
    if(key == sf::Keyboard::Right) {
        this-> Right = isPressed;
        if(!isPressed) { this->RightPressed=false; }
    }
    if(key == sf::Keyboard::Down) {
        this-> Down = isPressed;
        if(!isPressed) { this->DownPressed=false; }
    }
    if(key == sf::Keyboard::Up) {
        this-> Up = isPressed;
        if(!isPressed) { this->UpPressed=false; }
    }
    if(key == sf::Keyboard::Space) {
        this-> Space = isPressed;
        if(!isPressed) { this->SpacePressed=false; }
    }
}

void Engine::handleMouseInput(sf::Mouse::Button mouse, bool isPressed)
{
    if(mouse == sf::Mouse::Left) { this-> MouseL = isPressed; }
    if(mouse == sf::Mouse::Right) {
        this-> MouseR = isPressed;
        if(!isPressed) { this->MouseRPressed=false; }
    }
}

void Engine::update(sf::Time deltaTime)
{
    //////////////////////////////////////////////////////////////
    ////////////// Réponse aux inputs ////////////////////////////
    //////////////////////////////////////////////////////////////

    if(Echap) { m_window.close(); }
    if(MouseL) {
        generator.setPosition(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
        generator.start();
    } else { generator.stop(); }
    if(MouseR && !MouseRPressed) {
        generator.setTypeParticule(generator.getTypeParticule()+1);
        if(generator.getTypeParticule() > 3)
        {
            generator.setTypeParticule(0);
        }
        MouseRPressed = true;
    }

    if(Left) { }
    if(Right) { }
    if(Up) {  }
    if(Down) {  }
    if(Space) { }

    //////////////////////////////////////////////////
    ////////////// Update ////////////////////////////
    //////////////////////////////////////////////////

    generator.update(deltaTime);
}

void Engine::render(void)
{
    m_window.clear();
    generator.draw(m_window);
    m_window.display();
}

Engine::~Engine()
{}
