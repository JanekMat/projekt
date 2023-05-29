

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>

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
            setColorByLife();
        }
    }
};

class CustomCircleShape : public sf::CircleShape
{
private:
    int speed_x = 100;
    int speed_y = -100;

public:
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



int main()
{
    sf::RenderWindow window(sf::VideoMode(930, 900), "My window");

    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        return -1;
    }

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

    //    sf::Text text3;
    //    text3.setFont(font);
    //    text3.setString("Press 'R' to");
    //    text3.setCharacterSize(24);
    //    text3.setFillColor(sf::Color::White);
    //    text3.setPosition(760, 100);

    //    sf::Text text4;
    //    text4.setFont(font);
    //    text4.setString("restart the game");
    //    text4.setCharacterSize(24);
    //    text4.setFillColor(sf::Color::White);
    //    text4.setPosition(728, 130);

    CustomCircleShape circle(10.0);
    circle.setPosition(350.0, 780.0);
    circle.setFillColor(sf::Color(150, 10, 10));

    CustomRectangleShape main_rectangle1(sf::Vector2f(80, 8));
    main_rectangle1.setPosition(320.0, 800.0);
    main_rectangle1.setFillColor(sf::Color(100, 50, 250));

    CustomRectangleShape main_rectangle2(sf::Vector2f(80, 8));
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

    const int numRectangles = 6;
    const int numColumns = 7;
    const float rectangleWidth = 80.0f;
    const float rectangleHeight = 30.0f;
    const float startX = 65.0f;
    const float startY = 350.0f;
    const float paddingX = 4.0f;
    const float paddingY = 4.0f;

    std::vector<std::vector<HitRectangleShape>> hitRectangles(numColumns, std::vector<HitRectangleShape>(numRectangles, HitRectangleShape(sf::Vector2f(rectangleWidth, rectangleHeight))));

    srand(time(0));

    for (int i = 0; i < numColumns; ++i)
    {
        for (int j = 0; j < numRectangles; ++j)
        {
            HitRectangleShape& hitRectangle = hitRectangles[i][j];
            hitRectangle.setSize(sf::Vector2f(rectangleWidth, rectangleHeight));
            hitRectangle.setPosition(startX + i * (rectangleWidth + paddingX), startY + j * (rectangleHeight + paddingY));

            int randomLife = rand() % 3 + 1;
            hitRectangle.setLife(randomLife);
        }
    }

    sf::Clock clock;
    bool shouldMoveCircle = false;

    while (window.isOpen())
    {
        sf::Time elapsed = clock.restart();

        if (shouldMoveCircle)
        {
            sf::Vector2f currentPosition = circle.getPosition();
            sf::Vector2f velocity = sf::Vector2f(circle.getSpeedX(), circle.getSpeedY());
            sf::Vector2f newPosition = currentPosition + velocity * elapsed.asSeconds();
            circle.setPosition(newPosition);

            if (currentPosition.x < 10 && circle.getSpeedX() < 0)
            {
                circle.setSpeed(abs(circle.getSpeedX()), circle.getSpeedY());
            }
            else if (currentPosition.x + circle.getGlobalBounds().width > 710 && circle.getSpeedX() > 0)
            {
                circle.setSpeed(-abs(circle.getSpeedX()), circle.getSpeedY());
            }

            if (currentPosition.y < 0 && circle.getSpeedY() < 0)
            {
                circle.setSpeed(0, 0);
            }
            else if (currentPosition.y + circle.getGlobalBounds().height > 910 && circle.getSpeedY() > 0)
            {
                circle.setSpeed(0, 0);
            }

            if (checkCollision(circle, main_rectangle1))
            {
                circle.setSpeed(circle.getSpeedX(), -circle.getSpeedY());
            }
            else if (checkCollision(circle, main_rectangle2))
            {
                circle.setSpeed(circle.getSpeedX(), -circle.getSpeedY());
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
                        if (circleBounds.left + circleBounds.width >= rectangleBounds.left && circleBounds.left < rectangleBounds.left)
                        {
                            circle.setSpeed(-circle.getSpeedX(), circle.getSpeedY());
                        }

                        // Kolizja z prawą ścianką prostokąta
                        if (circleBounds.left <= rectangleBounds.left + rectangleBounds.width && circleBounds.left + circleBounds.width > rectangleBounds.left + rectangleBounds.width)
                        {
                            circle.setSpeed(-circle.getSpeedX(), circle.getSpeedY());
                        }

                        // Kolizja z górną krawędzią prostokąta
                        if (circleBounds.top + circleBounds.height >= rectangleBounds.top && circleBounds.top < rectangleBounds.top)
                        {
                            circle.setSpeed(circle.getSpeedX(), -circle.getSpeedY());
                        }

                        // Kolizja z dolną krawędzią prostokąta
                        if (circleBounds.top <= rectangleBounds.top + rectangleBounds.height && circleBounds.top + circleBounds.height > rectangleBounds.top + rectangleBounds.height)
                        {
                            circle.setSpeed(circle.getSpeedX(), -circle.getSpeedY());
                        }




                        if (hitRectangle.getLife() == 3)
                        {
                            hitRectangle.setFillColor(sf::Color(255, 255, 0));
                            hitRectangle.setLife(2);
                        }
                        else if (hitRectangle.getLife() == 2)
                        {
                            hitRectangle.setFillColor(sf::Color(0, 255, 0));
                            hitRectangle.setLife(1);
                        }
                        else if (hitRectangle.getLife() == 1)
                        {
                            hitRectangle.destroy();
                            hitRectangle.setFillColor(sf::Color::Black);
                        }
                    }
                }
            }
        }

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
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
                }
                else if (event.key.code == sf::Keyboard::R)
                {
//                    main_rectangle1.setPosition(320.0, 800.0);
//                    main_rectangle2.setPosition(320.0, 100.0);
//                    circle.setPosition(350.0, 780.0);
//                    circle.setSpeed(100, -100);
//                    shouldMoveCircle = false;
//                    for (int i = 0; i < numColumns; ++i)
//                    {
//                        for (int j = 0; j < numRectangles; ++j)
//                        {
//                            HitRectangleShape& hitRectangle = hitRectangles[i][j];
//                            int randomLife = rand() % 3 + 1;
//                            hitRectangle.setLife(randomLife);


//                        }
//                    }
                    return 0;
                }
            }
        }

        main_rectangle1.animate1(elapsed);
        main_rectangle2.animate2(elapsed);

        window.clear(sf::Color::Black);
        window.draw(green_rectangle);
        window.draw(black_rectangle1);
        window.draw(black_rectangle2);
        window.draw(main_rectangle1);
        window.draw(main_rectangle2);

        window.draw(text1);
        window.draw(text2);
//        window.draw(text3);
//        window.draw(text4);

        for (int i = 0; i < numColumns; ++i)
        {
            for (int j = 0; j < numRectangles; ++j)
            {
                window.draw(hitRectangles[i][j]);
            }
        }
        window.draw(circle);
        window.display();

    }
    return 0;
}



