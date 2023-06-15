#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <iomanip>
#include <string>
#include <SFML/Audio.hpp>


using namespace std;

class CustomRectangleShape : public sf::RectangleShape
{
private:
    int main_rect_speed1x = 0;
    int main_rect_speed1y = 0;
    int main_rect_speed2x = 0;
    int main_rect_speed2y = 0;
public:
    bool is_selected = false;

    CustomRectangleShape(const sf::Vector2f& size) : sf::RectangleShape(size) {}

    void animate1(const sf::Time& elapsed)
    {
        main_rect_speed1x = 0;
        main_rect_speed1y = 0;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            if (is_selected && getPosition().x > 10.0)
            {
                main_rect_speed1x = -200;
                std::cout << "Left is pressed" << std::endl;
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            if (is_selected && getPosition().x + getSize().x < 710.0)
            {
                main_rect_speed1x = 200;
                std::cout << "Right is pressed" << std::endl;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            if (is_selected && getPosition().y > 700.0)
            {
                main_rect_speed1y = -100;
                std::cout << "Up is pressed" << std::endl;
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            if (is_selected && getPosition().y + getSize().y < 900.0)
            {
                main_rect_speed1y = 100;
                std::cout << "Down is pressed" << std::endl;
            }
        }
        move(sf::Vector2f(main_rect_speed1x * elapsed.asSeconds(), main_rect_speed1y * elapsed.asSeconds()));
    }

    void animate2(const sf::Time& elapsed)
    {
        main_rect_speed2x = 0;
        main_rect_speed2y = 0;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            if (is_selected && getPosition().x > 10.0)
            {
                main_rect_speed2x = -200;
                std::cout << "A is pressed" << std::endl;
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            if (is_selected && getPosition().x + getSize().x < 710.0)
            {
                main_rect_speed2x = 200;
                std::cout << "D is pressed" << std::endl;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            if (is_selected && getPosition().y > 0.0)
            {
                main_rect_speed2y = -100;
                std::cout << "W is pressed" << std::endl;
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            if (is_selected && getPosition().y + getSize().y < 200.0)
            {
                main_rect_speed2y = 100;
                std::cout << "S is pressed" << std::endl;
            }
        }
        move(sf::Vector2f(main_rect_speed2x * elapsed.asSeconds(), main_rect_speed2y * elapsed.asSeconds()));
    }
};

class HitRectangleShape : public sf::RectangleShape
{
private:
    bool is_visible = true;
    bool is_destroyed = false;
    int life = 0;

public:
    HitRectangleShape(const sf::Vector2f& size) : sf::RectangleShape(size) {}

    sf::FloatRect getGlobalBounds() const
    {
        return getTransform().transformRect(getLocalBounds());
    }

    int getLife() const {
        return life;
    }

    void setLife(int new_life)
    {
        life = new_life;
        setColorByLife();
    }

    void setColorByLife()
    {
        if (life == 0)
            setFillColor(sf::Color::Black);
        else if (life == 1)
            setFillColor(sf::Color::Green);
        else if (life == 2)
            setFillColor(sf::Color::Yellow);
        else if (life == 3)
            setFillColor(sf::Color::Red);
    }

    bool isDestroyed() const
    {
        return is_destroyed;
    }

    void destroy()
    {
        if (life == 3)
        {
            life = 2;
            setColorByLife();
        }
        else if (life == 2)
        {
            life = 1;
            setColorByLife();
        }
        else if (life == 1)
        {
            is_destroyed = true;
            setColorByLife();
        }
        else if (life == 0)
        {
            is_destroyed = true;
            setColorByLife();
        }
    }
};

class CustomCircleShape : public sf::CircleShape
{
public:

    int speed_x = 150;
    int speed_y = -150;

    CustomCircleShape(float radius) : sf::CircleShape(radius) {}

    void setSpeed(int circle_speed_x, int circle_speed_y)
    {
        speed_x = circle_speed_x;
        speed_y = circle_speed_y;
    }

    int getSpeedX() const
    {
        return speed_x;
    }

    int getSpeedY() const
    {
        return speed_y;
    }
};

bool checkCollision(const sf::CircleShape& circle, const sf::RectangleShape& rectangle)
{
    sf::FloatRect circleBounds = circle.getGlobalBounds();
    sf::FloatRect rectangleBounds = rectangle.getGlobalBounds();
    return circleBounds.intersects(rectangleBounds);
}





bool pong_choosen = false;
bool arkanoid_choosen = false;
bool ponkanoid_choosen = false;

int main()
{
    sf::RenderWindow window(sf::VideoMode(930, 900), "MENU");
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cerr << "Failed to load font!" << std::endl;
        return -1;
    }

    sf::SoundBuffer buffer1;
    if (!buffer1.loadFromFile("gameend.wav"))
    {
        cout << "Failed to load buffer1!" << std::endl;
        return -1;
    }

    sf::Sound gameend;
    gameend.setBuffer(buffer1);



    sf::SoundBuffer buffer2;
    if (!buffer2.loadFromFile("pop.wav"))
    {
        cout << "Failed to load buffer2!" << std::endl;
        return -2;
    }

    sf::Sound pop;
    pop.setBuffer(buffer2);



    sf::SoundBuffer buffer3;
    if (!buffer3.loadFromFile("pop2.wav"))
    {
        cout << "Failed to load buffer3!" << std::endl;
        return -3;
    }

    sf::Sound pop2;
    pop2.setBuffer(buffer3);



    sf::SoundBuffer buffer4;
    if (!buffer4.loadFromFile("menuoption.wav"))
    {
        cout << "Failed to load buffer3!" << std::endl;
        return -3;
    }

    sf::Sound menuoption;
    menuoption.setBuffer(buffer4);



    sf::Music menumusic;
    if (!menumusic.openFromFile("menumusic.wav"))
    {
        cout << "Failed to load music!" << std::endl;
        return -1;
    }



    sf::Texture texture1;
    if (!texture1.loadFromFile("pong.png"))
    {
        cout << "Failed to load pong!" << std::endl;
        return -1;
    }



    sf::Texture texture2;
    if (!texture2.loadFromFile("arkanoid.png"))
    {
        cout << "Failed to load arkanoid!" << std::endl;
        return -1;
    }



    sf::Texture texture3;
    if (!texture3.loadFromFile("ponkanoid.png"))
    {
        cout << "Failed to load ponkanoid!" << std::endl;
        return -1;
    }

    sf::Text txt9;
    txt9.setFont(font);
    txt9.setString("PONKANOID");
    txt9.setCharacterSize(40);
    txt9.setPosition(330, 330);

    sf::Text txt0;
    txt0.setFont(font);
    txt0.setString("Wybierz tryb gry");
    txt0.setCharacterSize(24);
    txt0.setPosition(360, 400);

    sf::Text option1;
    option1.setFont(font);
    option1.setString("Pong");
    option1.setCharacterSize(24);
    option1.setPosition(420, 450);

    sf::Text option2;
    option2.setFont(font);
    option2.setString("Arkanoid");
    option2.setCharacterSize(24);
    option2.setPosition(400, 490);

    sf::Text option3;
    option3.setFont(font);
    option3.setString("Ponkanoid");
    option3.setCharacterSize(24);
    option3.setPosition(395, 530);

    sf::Sprite pong;
    pong.setTexture(texture1);

    sf::Sprite arkanoid;
    arkanoid.setTexture(texture2);

    sf::Sprite ponkanoid;
    ponkanoid.setTexture(texture3);



    sf::RectangleShape menu_rectangle1(sf::Vector2f(400, 300));
    menu_rectangle1.setPosition(250.0, 300.0);
    menu_rectangle1.setFillColor(sf::Color(250, 143, 5));



    sf::RectangleShape menu_rectangle2(sf::Vector2f(380, 280));
    menu_rectangle2.setPosition(260.0, 310.0);
    menu_rectangle2.setFillColor(sf::Color(0, 0, 0));



    menumusic.setLoop(true);
    menumusic.play();

    bool najechanonapong = false;
    bool najechanonaarkanoid = false;
    bool najechanonaponkanoid = false;


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                return 0;
            }
            if (event.type == sf::Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

                    if (option1.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                    {
                        menuoption.play();
                        std::cout << "Pong selected!" << std::endl;
                        pong_choosen = true;
                        window.close();
                    }
                    else if (option2.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                    {
                        menuoption.play();
                        std::cout << "Arkanoid selected!" << std::endl;
                        arkanoid_choosen = true;
                        window.close();
                    }
                    else if (option3.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                    {
                        menuoption.play();
                        std::cout << "Ponkanoid selected!" << std::endl;
                        ponkanoid_choosen = true;
                        window.close();
                    }
                }
            }
            if (event.type == sf::Event::MouseMoved)
            {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

                if (option1.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                {
                    najechanonapong = true;
                    najechanonaarkanoid = false;
                    najechanonaponkanoid = false;
                    std::cout << "Najechano na opcję 1" << std::endl;
                }
                else if (option2.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                {
                    najechanonaarkanoid = true;
                    najechanonapong = false;
                    najechanonaponkanoid = false;
                    std::cout << "Najechano na opcję 2" << std::endl;
                }
                else if (option3.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                {
                    najechanonaponkanoid = true;
                    najechanonapong = false;
                    najechanonaarkanoid = false;
                    std::cout << "Najechano na opcję 3" << std::endl;
                }
            }
        }

        window.clear();
        if (najechanonapong)
        {
            najechanonaarkanoid = false;
            najechanonaponkanoid = false;
            window.draw(pong);
        }
        else if (najechanonaarkanoid)
        {
            najechanonapong = false;
            najechanonaponkanoid = false;
            window.draw(arkanoid);
        }
        else if (najechanonaponkanoid)
        {
            najechanonapong = false;
            najechanonaarkanoid = false;
            window.draw(ponkanoid);
        }


        window.draw(menu_rectangle1);
        window.draw(menu_rectangle2);
        window.draw(txt9);
        window.draw(txt0);
        window.draw(option1);
        window.draw(option2);
        window.draw(option3);
        window.display();
    }

    menumusic.stop();







    sf::RenderWindow window2(sf::VideoMode(930, 900), "window2");



    sf::Text text1;
    text1.setFont(font);
    text1.setString("Press 'SPACE'");
    text1.setCharacterSize(24);
    text1.setFillColor(sf::Color::White);
    text1.setPosition(740, 20);

    sf::Text text2;
    text2.setFont(font);
    text2.setString("to start the game");
    text2.setCharacterSize(24);
    text2.setFillColor(sf::Color::White);
    text2.setPosition(725, 50);

    sf::Text text3;
    text3.setFont(font);
    text3.setString("Score player1: ");
    text3.setCharacterSize(24);
    text3.setFillColor(sf::Color::White);
    text3.setPosition(725, 80);

    sf::Text text4;
    text4.setFont(font);
    text4.setString("Score player2: ");
    text4.setCharacterSize(24);
    text4.setFillColor(sf::Color::White);
    text4.setPosition(725, 110);

    sf::Text text5;
    text5.setFont(font);
    text5.setString("0");
    text5.setCharacterSize(24);
    text5.setFillColor(sf::Color::White);
    text5.setPosition(890, 80);

    sf::Text text6;
    text6.setFont(font);
    text6.setString("0");
    text6.setCharacterSize(24);
    text6.setFillColor(sf::Color::White);
    text6.setPosition(890, 110);

    CustomCircleShape circle(10.0);
    circle.setPosition(350.0, 780.0);
    circle.setFillColor(sf::Color(150, 10, 10));

    CustomRectangleShape main_rectangle1(sf::Vector2f(80, 10));
    main_rectangle1.setPosition(320.0, 800.0);
    main_rectangle1.setFillColor(sf::Color(100, 50, 250));

    CustomRectangleShape main_rectangle2(sf::Vector2f(80, 10));
    main_rectangle2.setPosition(320.0, 100.0);
    main_rectangle2.setFillColor(sf::Color(100, 50, 250));

    sf::RectangleShape green_rectangle(sf::Vector2f(930, 900));
    green_rectangle.setPosition(0.0, 0.0);
    green_rectangle.setFillColor(sf::Color(2, 222, 6));

    sf::RectangleShape black_rectangle1(sf::Vector2f(700, 910));
    black_rectangle1.setPosition(10.0, 0.0);
    black_rectangle1.setFillColor(sf::Color(0, 0, 0));

    sf::RectangleShape black_rectangle2(sf::Vector2f(200, 900));
    black_rectangle2.setPosition(720.0, 10.0);
    black_rectangle2.setFillColor(sf::Color(20, 107, 46));

    sf::RectangleShape grey_rectangle1(sf::Vector2f(700, 5));
    grey_rectangle1.setPosition(10.0, 695.0);
    grey_rectangle1.setFillColor(sf::Color(47, 48, 48));

    sf::RectangleShape grey_rectangle2(sf::Vector2f(700, 5));
    grey_rectangle2.setPosition(10.0, 200.0);
    grey_rectangle2.setFillColor(sf::Color(47, 48, 48));

    sf::Text timeText("", font, 24);
    timeText.setPosition(300, 20);
    sf::Clock totalClock;
    sf::Time totalTime;
    bool isRunning;

    int numRectangles = 6;
    int numColumns = 6;
    float rectangleWidth = 80.0f;
    float rectangleHeight = 30.0f;
    float startX = 65.0f;
    float startY = 350.0f;
    float paddingX = 20.0f;
    float paddingY = 20.0f;


    int ylim = 0;


    std::vector<std::vector<HitRectangleShape>> hitRectangles(numColumns, std::vector<HitRectangleShape>(numRectangles, HitRectangleShape(sf::Vector2f(rectangleWidth, rectangleHeight))));

    srand(time(0));

    if(arkanoid_choosen == true)
    {
        startY = 150.0f;
        black_rectangle1.setPosition(10, 85);
        black_rectangle1.setSize(sf::Vector2f(700, 825));
        ylim = 85;
    }

    if(ponkanoid_choosen == true)
        numRectangles = 4;

    if(ponkanoid_choosen == true || arkanoid_choosen == true)
    {
        for (int i = 0; i < numColumns; ++i)
        {
            for (int j = 0; j < numRectangles; ++j)
            {
                HitRectangleShape& hitRectangle = hitRectangles[i][j];
                hitRectangle.setSize(sf::Vector2f(rectangleWidth, rectangleHeight));
                hitRectangle.setPosition(startX + i * (rectangleWidth + paddingX), startY + j * (rectangleHeight + paddingY));

                int randomLife = rand() % 4;
                hitRectangle.setLife(randomLife);
            }
        }
    }

    for (auto& column : hitRectangles)
    {
        for (auto& rectangle : column)
        {
            if (rectangle.getLife() == 0)
            {
                rectangle.destroy();
            }
        }
    }



    sf::Clock clock;
    bool shouldMoveCircle = false;
    int licznik = 0;
    bool moznawywolac = true;
    bool ostatnie_odbicie = true; //ostatnie odbicie gracza 1 -> bool = true  //ostatnie odbicie gracza 2 -> bool = false
    int licznik1 = 0;
    int licznik2 = 0;
    bool who_won; // wygrał gracz1 -> zmienna = true // wygrał gracz2 -> zmienna = false
    string czas;
    bool result;
    string wynik;

    while (window2.isOpen())
    {
        sf::Time elapsed = clock.restart();
        wynik = "roznica " + std::to_string(abs(licznik2-licznik1)) + " pkt";

        if (isRunning)
        {
            sf::Time elapsed = totalClock.restart();
            totalTime += elapsed;
            float deltaTime = totalTime.asSeconds();
            std::stringstream ss;
            ss << std::fixed << std::setprecision(3) << deltaTime;
            std::string timeString = "Twoj czas to: " + ss.str() + "s";
            timeText.setString(timeString);
            czas = timeString;
        }

        if (shouldMoveCircle)
        {
            sf::Vector2f currentPosition = circle.getPosition();
            sf::Vector2f velocity = sf::Vector2f(circle.getSpeedX(), circle.getSpeedY());
            sf::Vector2f newPosition = currentPosition + velocity * elapsed.asSeconds();
            circle.setPosition(newPosition);



            if(arkanoid_choosen == true)
            {
                if (moznawywolac)
                {
                    if (checkCollision(circle, main_rectangle1))
                    {
                        pop2.play();
                        circle.setSpeed(circle.getSpeedX(), -circle.getSpeedY());
                        cout << "wywolane" << endl;
                        moznawywolac = false;
                    }

                }

                licznik++;
                if (licznik == 200)
                {
                    licznik = 0;
                    moznawywolac = true;
                }
            }
            else if (ponkanoid_choosen == true)
            {
                if(moznawywolac)
                {
                    if (checkCollision(circle, main_rectangle1))
                    {
                        pop2.play();
                        circle.setSpeed(circle.getSpeedX(), -circle.getSpeedY());
                        cout << "wywolane" << endl;
                        moznawywolac = false;
                        ostatnie_odbicie = true;
                    }
                    if (checkCollision(circle, main_rectangle2))
                    {
                        pop2.play();
                        circle.setSpeed(circle.getSpeedX(), -circle.getSpeedY());
                        cout << "wywolane" << endl;
                        moznawywolac = false;
                        ostatnie_odbicie = false;
                    }
                }

                licznik++;
                if (licznik == 200)
                {
                    licznik = 0;
                    moznawywolac = true;
                }
            }
            else if (pong_choosen == true)
            {
                if(moznawywolac)
                {
                    if (checkCollision(circle, main_rectangle1))
                    {
                        pop2.play();
                        circle.setSpeed(circle.getSpeedX(), -circle.getSpeedY());
                        cout << "wywolane" << endl;
                        moznawywolac = false;

                        if (circle.getSpeedX() > 0)
                                circle.setSpeed(circle.getSpeedX() + 10, circle.getSpeedY());
                        else if (circle.getSpeedX() < 0)
                                circle.setSpeed(circle.getSpeedX() - 10, circle.getSpeedY());

                        if (circle.getSpeedY() > 0)
                                circle.setSpeed(circle.getSpeedX(), circle.getSpeedY() + 10);
                        else if (circle.getSpeedY() < 0)
                                circle.setSpeed(circle.getSpeedX(), circle.getSpeedY() - 10);

                        who_won = true;
                    }

                    if (checkCollision(circle, main_rectangle2))
                    {
                        pop2.play();
                        circle.setSpeed(circle.getSpeedX(), -circle.getSpeedY());
                        cout << "wywolane" << endl;
                        moznawywolac = false;

                        if (circle.getSpeedX() > 0)
                                circle.setSpeed(circle.getSpeedX() + 10, circle.getSpeedY());
                        else if (circle.getSpeedX() < 0)
                                circle.setSpeed(circle.getSpeedX() - 10, circle.getSpeedY());

                        if (circle.getSpeedY() > 0)
                                circle.setSpeed(circle.getSpeedX(), circle.getSpeedY() + 10);
                        else if (circle.getSpeedY() < 0)
                                circle.setSpeed(circle.getSpeedX(), circle.getSpeedY() - 10);

                        who_won = false;
                    }
                }

                licznik++;
                if (licznik == 200)
                {
                    licznik = 0;
                    moznawywolac = true;
                }
            }

            if(moznawywolac)
                cout << "moznawywolac" << endl;
            else
                cout << "NIEmoznawywolac" << endl;



            if (currentPosition.x < 10 && circle.getSpeedX() < 0)
            {
                pop2.play();
                circle.setSpeed(abs(circle.getSpeedX()), circle.getSpeedY());
            }
            else if (currentPosition.x + circle.getGlobalBounds().width > 710 && circle.getSpeedX() > 0)
            {
                pop2.play();
                circle.setSpeed(-abs(circle.getSpeedX()), circle.getSpeedY());
            }



            if (currentPosition.y < ylim && circle.getSpeedY() < 0)
            {
                if(arkanoid_choosen == true)
                {
                    pop2.play();
                    circle.setSpeed(circle.getSpeedX(), -circle.getSpeedY());
                }
                else
                {
                    circle.setSpeed(0, 0);
                    who_won = true;
                    window2.close();
                }
            }
            else if (currentPosition.y + circle.getGlobalBounds().height > 910 && circle.getSpeedY() > 0)
            {
                circle.setSpeed(0, 0);
                who_won = false;
                window2.close();
            }


            for (int i = 0; i < numColumns; ++i)
            {
                for (int j = 0; j < numRectangles; ++j)
                {
                    HitRectangleShape& hitRectangle = hitRectangles[i][j];
                    if (!hitRectangle.isDestroyed() && checkCollision(circle, hitRectangle))
                    {

                        //circle.setSpeed(circle.getSpeedX(), -circle.getSpeedY());

                        sf::FloatRect circleBounds = circle.getGlobalBounds();
                        sf::FloatRect rectangleBounds = hitRectangle.getGlobalBounds();



                        // Kolizja z lewą ścianką prostokąta
                        if (circleBounds.left + circleBounds.width > rectangleBounds.left && circleBounds.left < rectangleBounds.left)
                        {
                            pop.play();
                            circle.setSpeed(-circle.getSpeedX(), circle.getSpeedY());
                            cout << "Kolizja z lewą ścianką prostokąta" << endl;
                        }

                        // Kolizja z prawą ścianką prostokąta
                        else if (circleBounds.left < rectangleBounds.left + rectangleBounds.width && circleBounds.left + circleBounds.width > rectangleBounds.left + rectangleBounds.width)
                        {
                            pop.play();
                            circle.setSpeed(-circle.getSpeedX(), circle.getSpeedY());
                            cout << "Kolizja z prawą ścianką prostokąta" << endl;
                        }

                        // Kolizja z górną krawędzią prostokąta
                        else if (circleBounds.top + circleBounds.height > rectangleBounds.top && circleBounds.top < rectangleBounds.top)
                        {
                            pop.play();
                            circle.setSpeed(circle.getSpeedX(), -circle.getSpeedY());
                            cout << "Kolizja z górną krawędzią prostokąta" << endl;
                        }

                        // Kolizja z dolną krawędzią prostokąta
                        else if (circleBounds.top < rectangleBounds.top + rectangleBounds.height && circleBounds.top + circleBounds.height > rectangleBounds.top + rectangleBounds.height)
                        {
                            pop.play();
                            circle.setSpeed(circle.getSpeedX(), -circle.getSpeedY());
                            cout << "Kolizja z dolną krawędzią prostokąta" << endl;
                        }
                        // Sprawdź kolizję z lewym górnym rogiem prostokąta
                        if (circleBounds.intersects(sf::FloatRect(rectangleBounds.left, rectangleBounds.top, 1.0f, 1.0f)))
                        {
                            pop.play();
                            // Odbicie od lewego górnego rogu prostokąta
                            circle.setSpeed(-std::abs(circle.getSpeedX()), -std::abs(circle.getSpeedY()));
                            cout << "Odbicie od lewego górnego rogu prostokąta" << endl;
                        }

                        // Sprawdź kolizję z prawym górnym rogiem prostokąta
                        if (circleBounds.intersects(sf::FloatRect(rectangleBounds.left + rectangleBounds.width, rectangleBounds.top, 1.0f, 1.0f)))
                        {
                            pop.play();
                            // Odbicie od prawego górnego rogu prostokąta
                            circle.setSpeed(std::abs(circle.getSpeedX()), -std::abs(circle.getSpeedY()));
                            cout << "Odbicie od prawego górnego rogu prostokąta" << endl;
                        }

                        // Sprawdź kolizję z lewym dolnym rogiem prostokąta
                        if (circleBounds.intersects(sf::FloatRect(rectangleBounds.left, rectangleBounds.top + rectangleBounds.height, 1.0f, 1.0f)))
                        {
                            pop.play();
                            // Odbicie od lewego dolnego rogu prostokąta
                            circle.setSpeed(-std::abs(circle.getSpeedX()), std::abs(circle.getSpeedY()));
                            cout << "Odbicie od lewego dolnego rogu prostokąta" << endl;
                        }

                        // Sprawdź kolizję z prawym dolnym rogiem prostokąta
                        if (circleBounds.intersects(sf::FloatRect(rectangleBounds.left + rectangleBounds.width, rectangleBounds.top + rectangleBounds.height, 1.0f, 1.0f)))
                        {
                            pop.play();
                            // Odbicie od prawego dolnego rogu prostokąta
                            circle.setSpeed(std::abs(circle.getSpeedX()), std::abs(circle.getSpeedY()));
                            cout << "Odbicie od prawego dolnego rogu prostokąta" << endl;
                        }






                        if (hitRectangle.getLife() == 3)
                        {
                            hitRectangle.setFillColor(sf::Color(255, 255, 0));
                            hitRectangle.setLife(2);

                            if (ostatnie_odbicie == true)
                                licznik1++;
                            else if (ostatnie_odbicie == false)
                                licznik2++;
                        }



                        else if (hitRectangle.getLife() == 2)
                        {
                            hitRectangle.setFillColor(sf::Color(0, 255, 0));
                            hitRectangle.setLife(1);

                            if (ostatnie_odbicie == true)
                                licznik1++;
                            else if (ostatnie_odbicie == false)
                                licznik2++;
                        }



                        else if (hitRectangle.getLife() == 1)
                        {
                            if (ponkanoid_choosen == true)
                            {
                                std::srand(static_cast<unsigned>(std::time(nullptr)));
                                int l = std::rand() % 14;
                                cout << l << endl;
                                if (l == 13)
                                {
                                    hitRectangle.setLife(0);
                                    hitRectangle.setFillColor(sf::Color(49, 214, 214));
                                }
                                else
                                {
                                    hitRectangle.destroy();
                                    hitRectangle.setFillColor(sf::Color::Black);
                                }
                            }
                            if (arkanoid_choosen == true)
                            {
                                hitRectangle.destroy();
                                hitRectangle.setFillColor(sf::Color::Black);
                            }

                            if (ostatnie_odbicie == true)
                                licznik1 = licznik1 + 2;
                            else if (ostatnie_odbicie == false)
                                licznik2 = licznik2 + 2;
                        }



                        else if (hitRectangle.getLife() == 0)
                        {
                            hitRectangle.destroy();
                            hitRectangle.setFillColor(sf::Color::Black);

                            if (ostatnie_odbicie == true)
                                licznik1 = licznik1 + 20;
                            else if (ostatnie_odbicie == false)
                                licznik2 = licznik2 + 20;


                        }
                    }
                }
            }
        }

        if (arkanoid_choosen || ponkanoid_choosen)
        {
            bool allDestroyed = true;
            for (const auto& column : hitRectangles)
            {
                for (const auto& rectangle : column)
                {
                    if (!rectangle.isDestroyed())
                    {
                        allDestroyed = false;
                        break;
                    }
                }
                if (!allDestroyed)
                {
                    result = false;
                    break;
                }
            }

            if (allDestroyed)
            {
                result = true;
                window2.close();
            }
        }



        sf::Event event;
        while (window2.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window2.close();
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Left)
                {
                    main_rectangle1.is_selected = true;
                }
                else if (event.key.code == sf::Keyboard::Right)
                {
                    main_rectangle1.is_selected = true;
                }
                else if (event.key.code == sf::Keyboard::A)
                {
                    main_rectangle2.is_selected = true;
                }
                else if (event.key.code == sf::Keyboard::D)
                {
                    main_rectangle2.is_selected = true;
                }
                else if (event.key.code == sf::Keyboard::Space)
                {
                    shouldMoveCircle = true;
                    isRunning = true;

                    if (arkanoid_choosen == true)
                        circle.setSpeed(200, 200);
                }
            }
        }

        main_rectangle1.animate1(elapsed);
        main_rectangle2.animate2(elapsed);

        text5.setString(std::to_string(licznik1));
        text6.setString(std::to_string(licznik2));

        window2.clear(sf::Color::Black);
        window2.draw(green_rectangle);
        window2.draw(black_rectangle1);
        window2.draw(black_rectangle2);
        window2.draw(grey_rectangle1);
        window2.draw(main_rectangle1);

        if(ponkanoid_choosen == true || pong_choosen == true)
        {
            window2.draw(grey_rectangle2);
            window2.draw(main_rectangle2);
        }

        window2.draw(text1);
        window2.draw(text2);

        if(ponkanoid_choosen == true)
        {
            window2.draw(text3);
            window2.draw(text4);
            window2.draw(text5);
            window2.draw(text6);
        }

        if (arkanoid_choosen == true)
        {
            window2.draw(timeText);
        }


        if(ponkanoid_choosen == true || arkanoid_choosen == true)
        {
            for (int i = 0; i < numColumns; ++i)
            {
                for (int j = 0; j < numRectangles; ++j)
                {
                    window2.draw(hitRectangles[i][j]);
                }
            }
        }


        window2.draw(circle);
        window2.display();
    }



    gameend.play();










    sf::RenderWindow window3(sf::VideoMode(400, 300), "KONIEC GRY");
    window.setFramerateLimit(60);

    sf::Text txt1;
    txt1.setFont(font);
    txt1.setString("Koniec gry");
    txt1.setCharacterSize(24);            // PONG ARK POARK

    sf::Text txt2;
    txt2.setFont(font);
    txt2.setString("Wygral gracz nr: ");    // PONG POARK
    txt2.setCharacterSize(24);

    sf::Text txt3;
    txt3.setFont(font);
    txt3.setString("0");                    // PONG ARK POARK
    txt3.setCharacterSize(24);

    sf::Text txt4;
    txt4.setFont(font);
    txt4.setString("Twoj wynik to: ");      // ARK
    txt4.setCharacterSize(24);

    sf::Text txt5;
    txt5.setFont(font);
    txt5.setString(".");        // POARK
    txt5.setCharacterSize(24);

    sf::Text txt6;
    txt6.setFont(font);
    txt6.setString("Wyjscie");            // PONG ARK POARK
    txt6.setCharacterSize(24);

    sf::Text txt7;
    txt7.setFont(font);
    txt7.setString(".");            // ARK
    txt7.setCharacterSize(24);

    sf::RectangleShape end_rectangle1(sf::Vector2f(400, 300));
    end_rectangle1.setPosition(0.0, 0.0);
    end_rectangle1.setFillColor(sf::Color(250, 143, 5));

    sf::RectangleShape end_rectangle2(sf::Vector2f(380, 280));
    end_rectangle2.setPosition(10.0, 10.0);
    end_rectangle2.setFillColor(sf::Color(0, 0, 0));


    while (window3.isOpen())
    {
        sf::Event event;
        while (window3.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window3.close();
                return 0;
            }
            if (event.type == sf::Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window3);

                    if (txt6.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                    {
                        menuoption.play();
                        std::cout << "Wyjscie" << std::endl;
                        window3.close();
                        return 0;
                    }
                }
            }
        }



        window3.clear();
        window3.draw(end_rectangle1);
        window3.draw(end_rectangle2);


        if (pong_choosen)
        {
            txt1.setPosition(150, 70);
            txt2.setPosition(110, 120);
            txt3.setPosition(300, 120);
            txt6.setPosition(170, 170);

            string i = "0";
            if (who_won)
                i = "1";
            else
                i = "2";

            txt3.setString(i);

            window3.draw(txt1);
            window3.draw(txt2);
            window3.draw(txt3);
            window3.draw(txt6);
        }

        if (arkanoid_choosen)
        {
            txt3.setString(czas);

            string i;
            if (result)
            {
                i = "Wygrales!";

                txt1.setPosition(150, 60);
                txt3.setPosition(90, 160);
                txt6.setPosition(170, 210);
                txt7.setPosition(150, 110);
                window3.draw(txt3);
            }

            else
            {
                i = "Przegrales :(";
                txt1.setPosition(150, 70);
                txt6.setPosition(170, 170);
                txt7.setPosition(140, 120);
            }

            txt7.setString(i);

            window3.draw(txt1);
            window3.draw(txt6);
            window3.draw(txt7);
        }

        if (ponkanoid_choosen)
        {
            txt1.setPosition(150, 70);
            txt2.setPosition(105, 120);
            txt3.setPosition(295, 120);
            txt6.setPosition(170, 220);
            txt7.setPosition(140, 170);

            string i = "0";
            if (who_won)
                i = "1";
            else
                i = "2";

            txt3.setString(i);
            txt7.setString(wynik);

            window3.draw(txt1);
            window3.draw(txt2);
            window3.draw(txt3);
            window3.draw(txt6);
            if (result)
            window3.draw(txt7);
        }

        window3.display();
    }
}









