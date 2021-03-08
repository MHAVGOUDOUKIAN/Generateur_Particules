#include "ParticuleGenerator.hpp"
#include <iostream>

ParticuleGenerator::ParticuleGenerator() : pos(sf::Vector2f(0,0)), typeParticule(0), working(false), EnableDuration(false), duration(2.f),
lifeTime(0), particulePerSecond(150), timeLastParticuleAdded(0), lifeTimeParticule(0.5f) {}

ParticuleGenerator::ParticuleGenerator(const float X, const float Y): pos(sf::Vector2f(X,Y)), typeParticule(0), working(false), EnableDuration(false),
duration(2.f), lifeTime(0), particulePerSecond(150), timeLastParticuleAdded(0), lifeTimeParticule(0.5f) {}
void ParticuleGenerator::update(sf::Time deltaTime)
{
    lifeTime += deltaTime.asSeconds();

    if(isWorking()) { emit(deltaTime); }

    if(EnableDuration && lifeTime > duration) {
        stop();
        lifeTime = 0;
    }

    for(int i=0; i < int(lParticules.size()); i++) {
        if(!lParticules[i]->isDead()) {
            lParticules[i]->update(deltaTime);
        }
        else {
            delete lParticules[i];
            lParticules.erase(lParticules.begin()+i);
            i--;
        }
    }
}

/*
void ParticuleGenerator::add(const float X, const float Y)
{
    lParticules.push_back(new Particule_Dot(sf::Mouse::getPosition().x + this->pos.x ,sf::Mouse::getPosition().y + this->pos.y, lifeTimeParticule));
    lParticules[lParticules.size()-1]->launch(lParticules[lParticules.size()-1]->getPosition().x, lParticules[lParticules.size()-1]->getPosition().y, randomf(-700,700), randomf(-1000,1000));
}

void ParticuleGenerator::add()
{
    lParticules.push_back(new Particule_Dot(this->pos.x ,this->pos.y, lifeTimeParticule));
    lParticules[lParticules.size()-1]->launch(lParticules[lParticules.size()-1]->getPosition().x, lParticules[lParticules.size()-1]->getPosition().y, randomf(-700,700), randomf(-1000,1000));
}*/

void ParticuleGenerator::add(const float X, const float Y)
{
    if(typeParticule == 0) {lParticules.push_back(new Particule_Ball(sf::Mouse::getPosition().x + this->pos.x ,sf::Mouse::getPosition().y + this->pos.y, lifeTimeParticule)); setParticulePerSecond(200);}
    else if(typeParticule == 1) {lParticules.push_back(new Particule_Snow(sf::Mouse::getPosition().x + this->pos.x ,sf::Mouse::getPosition().y + this->pos.y, lifeTimeParticule)); setParticulePerSecond(200);}
    else if(typeParticule == 2) {lParticules.push_back(new Particule_Dot(sf::Mouse::getPosition().x + this->pos.x ,sf::Mouse::getPosition().y + this->pos.y, lifeTimeParticule));
    setParticulePerSecond(500);}
    else if(typeParticule == 3) {lParticules.push_back(new Particule_Fire(sf::Mouse::getPosition().x + this->pos.x ,sf::Mouse::getPosition().y + this->pos.y, lifeTimeParticule)); setParticulePerSecond(200);}
    lParticules[lParticules.size()-1]->launch(lParticules[lParticules.size()-1]->getPosition().x, lParticules[lParticules.size()-1]->getPosition().y, randomf(-700,700), randomf(-1000,1000));
}

void ParticuleGenerator::add()
{
    if(typeParticule == 0) {lParticules.push_back(new Particule_Ball(this->pos.x ,this->pos.y, lifeTimeParticule));setParticulePerSecond(200);}
    else if(typeParticule == 1) {lParticules.push_back(new Particule_Snow(this->pos.x ,this->pos.y, lifeTimeParticule));setParticulePerSecond(200);}
    else if(typeParticule == 2) {lParticules.push_back(new Particule_Dot(this->pos.x ,this->pos.y, lifeTimeParticule));setParticulePerSecond(500);}
    else if(typeParticule == 3) {lParticules.push_back(new Particule_Fire(this->pos.x ,this->pos.y, lifeTimeParticule));setParticulePerSecond(200);}
    lParticules[lParticules.size()-1]->launch(lParticules[lParticules.size()-1]->getPosition().x, lParticules[lParticules.size()-1]->getPosition().y, randomf(-700,700), randomf(-1000,1000));
}

void ParticuleGenerator::draw(sf::RenderWindow& window)
{
    for(int i=0; i < int(lParticules.size()) ; i++) {
        lParticules[i]->draw(window);
    }
}

void ParticuleGenerator::emit(sf::Time deltaTime)
{
    timeLastParticuleAdded = timeLastParticuleAdded + deltaTime.asSeconds() * (particulePerSecond); // On calcule le temps qu'il s'est écoulé depuis la dernière update et donc le nombre d'image qui doit être affichées pour respecter la cadence particulePerSecond
    if(timeLastParticuleAdded >= 1) // Si on doit ajouter au moins une particule;;
    {
        for(int i=0; i < int(timeLastParticuleAdded); i++) // On ajoute le bon nombre de particules
        {
            add();

        }
        timeLastParticuleAdded -= int(timeLastParticuleAdded); // On retire le nombre de particules retirées du compteur
    }
}

ParticuleGenerator::~ParticuleGenerator() {}
