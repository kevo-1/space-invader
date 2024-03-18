
#include <iostream>
#include "SFML/Graphics.hpp"
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "Player.h"
#include <vector>
#include <fstream>


int main() {


    //boosting up :
    sf::Sprite coffee;
    sf::Texture coffeetex;
    coffeetex.loadFromFile("final coffee.png");
    coffee.setTexture(coffeetex);
    coffee.setScale(4, 4);
    std::vector <sf::Sprite> coffees;


    //shooting sound;
    sf::Sound sound;
    sf::SoundBuffer buffer;
    buffer.loadFromFile("lsrshot.WAV");
    sound.setBuffer(buffer);
    sound.setVolume(10.0f);

    //music
    sf::Music music;
    music.openFromFile("music.mp3");
    music.setLoop(true);
    music.play();
    music.setVolume(35);


    //game over check
    bool gameover = false;


    sf::RenderWindow menu(sf::VideoMode(800, 900), "Space shooter", sf::Style::Close);
    //gameicon :
    sf::Image icon;
    icon.loadFromFile("ghost3.png");
    menu.setIcon(icon.getSize().x ,icon.getSize().y  , icon.getPixelsPtr());

    //framerate :
    menu.setFramerateLimit(60);

    //textures
    sf::Texture back;
    sf::Texture earth;
    sf::Texture play;
    sf::Texture missile;
    sf::Texture earthy;
    sf::Texture Enemyskin;

    //their files :
    play.loadFromFile("animation.png");
    back.loadFromFile("backnew.png");
    earth.loadFromFile("earth.png");
    earthy.loadFromFile("earth.png");
    missile.loadFromFile("bullet.png");
    Enemyskin.loadFromFile("enemy.png");


    //bullets :
    std::vector<sf::RectangleShape> bullets;
    sf::RectangleShape rockets(sf::Vector2f(2,6));
    rockets.setScale(3, 3);
    rockets.setTexture(&missile);
    bullets.push_back(rockets);
    

    //animation clock
    float dt = 0.0f;
    sf::Clock clock;
    sf::Clock enemytime;
    sf::Clock coffeetime;
    sf::Clock boosttime;
    
   
    //player
    Player player(&play, sf::Vector2u(2, 3), 0.5f, 450.0f);


    //background :
    sf::Sprite back1(back);
    back1.setScale(0.78125, 0.87890625);

    //earth :
    sf::CircleShape ear(256);
    ear.setTexture(&earthy);
    ear.setOrigin(256, 256);
    ear.setPosition(400, 960);

    //enemies :
    sf::RectangleShape enemy(sf::Vector2f(15,9));
    enemy.setTexture(&Enemyskin);
    enemy.setScale(5, 5);
    enemy.setOrigin(enemy.getSize().x / 2, enemy.getSize().y / 2);
    std::vector<sf::RectangleShape> enemies;
    
    //shoot delay :
    long long shootime = 0;





    //score :
    int score = 0;
    int highscore = 0;
    int speedtime = 20;
    bool isboosted = false;

    while (menu.isOpen()) 
    {
        dt = clock.restart().asSeconds();



        sf::Text text;
        sf::Font scorefont;
        scorefont.loadFromFile("good.ttf");
        text.setFont(scorefont);
        text.setCharacterSize(30);
        text.setFillColor(sf::Color::Green);
        text.setString("Score : " + std::to_string(score));


        sf::Text over;
        sf::Font overfont;
        overfont.loadFromFile("good.ttf");
        over.setFont(overfont);
        over.setCharacterSize(70);
        over.setFillColor(sf::Color::Red);
        over.setPosition(200, 350);
        over.setString("Game Over!");



        sf::Text reset;
        reset.setFont(overfont);
        reset.setCharacterSize(40);
        reset.setFillColor(sf::Color::Red);
        reset.setPosition(sf::Vector2f(over.getPosition().x - 75, over.getPosition().y + 100));
        reset.setString("Press Enter to Restart!");
        
        sf::Text high;
        sf::Font hightext;
        hightext.loadFromFile("good.ttf");
        high.setFont(hightext);
        high.setCharacterSize(30);
        high.setFillColor(sf::Color::Green);
        std::ifstream newscore;
        newscore.open("Text.txt");
        int totally;
        newscore >> totally;
        high.setString("High Score : " + std::to_string(std::max(totally ,score)));
        std::ofstream newhigh;
        newhigh.open("Text.txt");
        newhigh << std::max(totally, score);
        high.setPosition(0, 30);

        sf::Event evnt;
        while (menu.pollEvent(evnt)) 
        {
            //closing window :
            switch (evnt.type) 
            {
            case::sf::Event::Closed:
                menu.close();
                break;
            }
        }


        

        
        //shooting mechanism :
        //shoot timer reset :
        
        if (shootime <= speedtime) {
            shootime++;
        }
        //shoot initiation :
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && shootime >= speedtime && !gameover) 
        {
            rockets.setPosition(player.position().x + player.size().x/2 , player.position().y + 25);
            bullets.push_back(rockets);
            
            shootime = 0;
            sound.play();
            
        }

        //bullets animation :
        for (int i = 0; i < bullets.size(); i++)
        {
            bullets[i].move(0.0f, -15.0f);
            if (bullets[i].getPosition().y < 0)
                bullets.erase(bullets.begin() + i);
        }
        

        //enemy spawning
        if (enemytime.getElapsedTime().asSeconds() > 1.2f && !gameover) 
        {
            enemy.setPosition(190 + rand() % 420, 0.0f);
            enemies.push_back(enemy);
            enemytime.restart();
        }
        if (!gameover) 
        {
            for (int i = 0; i < enemies.size(); i++)
            {
                enemies[i].move(0.0f, 4.0f);
                if (enemies[i].getPosition().y > 900.0f) {
                    enemies.erase(enemies.begin() + i);
                }
            }
        }
        //enemies killing :
        for (int i = 0; i < enemies.size(); i++)
        {
            for (int j = 0; j < bullets.size(); j++)
            {
                if (enemies[i].getGlobalBounds().intersects(bullets[j].getGlobalBounds())) {
                    enemies.erase(enemies.begin() + i);
                    bullets.erase(bullets.begin() + j);
                    score++;
                    break;
                }
            }
        }
        //player animation :
        player.update(dt); 

        //boosting maintain :
        coffee.setPosition(190 + rand() % 420, 0.0f);
        if (coffeetime.getElapsedTime().asSeconds() > 20.0f && !gameover)
        {
            coffees.push_back(coffee);
            coffeetime.restart();
        }
        if (!gameover) {
            for (int i = 0; i < coffees.size(); i++)
            {
                coffees[i].move(0.0f, 5.0f);
                if (coffees[i].getPosition().y > 900)
                    coffees.erase(coffees.begin() + i);
            }
        }



        //collision system :
        for (int i = 0; i < enemies.size(); i++)
        {
            if (ear.getGlobalBounds().intersects(enemies[i].getGlobalBounds()) || player.collision(enemies[i]))
            {
                gameover = true;
                enemies.erase(enemies.begin(), enemies.end());
                bullets.erase(bullets.begin(), bullets.end());
            }
        }
        for (int i = 0; i < coffees.size(); i++)
        {
            if (player.collision1(coffees[i])) {
                coffees.erase(coffees.begin() + i);
                isboosted = true;
                boosttime.restart();
            }
        }

        //boost time :
        if (isboosted && boosttime.getElapsedTime().asSeconds() < 5.0f)
        {
            speedtime = 3;
        }
        else {
            speedtime = 20;
        }


        //drawing
        menu.clear();
        menu.draw(back1);
        menu.draw(ear);
        menu.draw(text);
        menu.draw(high);
        player.draw(menu);
        if (!gameover) {
            for (int i = 0; i < bullets.size(); i++)
            {
                menu.draw(bullets[i]);
            }
            for (int i = 0; i < enemies.size(); i++)
            {
                menu.draw(enemies[i]);
            }
            for (int i = 0; i < coffees.size(); i++)
            {
                menu.draw(coffees[i]);
            }
        }
        else {
            menu.draw(over);
            menu.draw(reset);
            score = 0;
            speedtime = 20;
            isboosted = false;
            music.stop();
        }
        menu.display();
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && gameover)
        {
            gameover = false;
            music.play();
        }
        
        
    }
    return 0;
}
