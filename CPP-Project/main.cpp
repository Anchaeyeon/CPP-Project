#include <SFML/Graphics.hpp>
#include <iostream>

// 기본 Screen 클래스 (가장 상위)
class Screen {
public:
    Screen() : Green(0, 145, 50), Yellow(252, 171, 64) {
        font.loadFromFile("Pretendard-Bold.otf");
    }

    virtual void click(sf::RenderWindow& window, int& currentScreen) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
    virtual ~Screen() = default;

protected:
    sf::Font font;
    sf::Color Green, Yellow;
};

// 시작 클래스
class Start : public Screen {
public:
    Start() {
        // 이미지
        img.loadFromFile("start_cookie.png");
        startSprite.setTexture(img);
        startSprite.setPosition(649, 279);

        // "Fortune Cookie" 텍스트
        titleText.setFont(font);
        titleText.setString("Fortune Cookie");
        titleText.setCharacterSize(100);
        titleText.setFillColor(Yellow);
        titleText.setPosition(360, 452);

        // "시작하기" 텍스트
        startBtn.setFont(font);
        startBtn.setString(L"시작하기");
        startBtn.setCharacterSize(43);
        startBtn.setFillColor(Yellow);
        startBtn.setPosition(645, 602);
    }

    void click(sf::RenderWindow& window, int& currentScreen) override {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    if (startBtn.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        currentScreen = 1; // 화면 전환
                    }
                }
            }
        }
    }

    void render(sf::RenderWindow& window) override {
        window.clear(Green);
        window.draw(startSprite);
        window.draw(titleText);
        window.draw(startBtn);
        window.display();
    }

private:
    sf::Texture img;
    sf::Sprite startSprite;
    sf::Text titleText, startBtn;
};

// 재료 소개 클래스
class IngredientIntro : public Screen {
public:
    IngredientIntro() {
        // 이미지
        flourImg.loadFromFile("flour.png");
        flourSprite.setTexture(flourImg);
        flourSprite.setPosition(850, 310);

        milkImg.loadFromFile("milk.png");
        milkSprite.setTexture(milkImg);
        milkSprite.setPosition(860, 400);

        eggImg.loadFromFile("egg.png");
        eggSprite.setTexture(eggImg);
        eggSprite.setPosition(860, 470);

        butterImg.loadFromFile("butter.png");
        butterSprite.setTexture(butterImg);
        butterSprite.setPosition(850, 500);

        sugarImg.loadFromFile("sugar.png");
        sugarSprite.setTexture(sugarImg);
        sugarSprite.setPosition(850, 600);

        oilImg.loadFromFile("oil.png");
        oilSprite.setTexture(oilImg);
        oilSprite.setPosition(860, 680);

        chocoImg.loadFromFile("choco.png");
        chocoSprite.setTexture(chocoImg);
        chocoSprite.setPosition(870, 750);

        // "< 재료 소개 Time >" 텍스트
        IngredientText.setFont(font);
        IngredientText.setString(L"< 재료 소개 Time >");
        IngredientText.setCharacterSize(50);
        IngredientText.setFillColor(Yellow);
        IngredientText.setPosition(519, 173);

        // 박력분
        flour.setFont(font);
        flour.setString(L"박력분");
        flour.setCharacterSize(50);
        flour.setFillColor(Yellow);
        flour.setPosition(542, 324);

        // 우유
        milk.setFont(font);
        milk.setString(L"우유");
        milk.setCharacterSize(50);
        milk.setFillColor(Yellow);
        milk.setPosition(542, 396);

        // 계란
        egg.setFont(font);
        egg.setString(L"계란");
        egg.setCharacterSize(50);
        egg.setFillColor(Yellow);
        egg.setPosition(542, 468);

        // 버터
        butter.setFont(font);
        butter.setString(L"버터");
        butter.setCharacterSize(50);
        butter.setFillColor(Yellow);
        butter.setPosition(542, 540);

        // 슈가파우더
        sugar.setFont(font);
        sugar.setString(L"슈가파우더");
        sugar.setCharacterSize(50);
        sugar.setFillColor(Yellow);
        sugar.setPosition(542, 612);

        // 바닐라오일
        oil.setFont(font);
        oil.setString(L"바닐라오일");
        oil.setCharacterSize(50);
        oil.setFillColor(Yellow);
        oil.setPosition(542, 684);

        // 초콜릿
        choco.setFont(font);
        choco.setString(L"초콜릿");
        choco.setCharacterSize(50);
        choco.setFillColor(Yellow);
        choco.setPosition(542, 750);

        // 다음으로 넘어가는 버튼
        nextBtn.setFont(font);
        nextBtn.setString("next >");
        nextBtn.setCharacterSize(43);
        nextBtn.setFillColor(Yellow);
        nextBtn.setPosition(1273, 870);
    }

    void click(sf::RenderWindow& window, int& currentScreen) override {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    if (nextBtn.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        currentScreen = 2; // 화면 전환
                    }
                }
            }
        }
    }

    void render(sf::RenderWindow& window) override {
        window.clear(Green);
        window.draw(IngredientText);
        window.draw(nextBtn);

        window.draw(flour);
        window.draw(milk);
        window.draw(egg);
        window.draw(butter);
        window.draw(sugar);
        window.draw(oil);
        window.draw(choco);

        window.draw(flourSprite);
        window.draw(milkSprite);
        window.draw(eggSprite);
        window.draw(butterSprite);
        window.draw(sugarSprite);
        window.draw(oilSprite);
        window.draw(chocoSprite);

        window.display();
    }

private:
    sf::Text IngredientText, nextBtn;
    sf::Text flour, milk, egg, butter, sugar, oil, choco;
    sf::Texture flourImg, milkImg, eggImg, butterImg, sugarImg, oilImg, chocoImg;
    sf::Sprite flourSprite, milkSprite, eggSprite, butterSprite, sugarSprite, oilSprite, chocoSprite;
};

// 만들어야 할 순서를 보여주는 클래스
class Order : public Screen {
public:
    Order() {
        // 순서 소개 텍스트
        orderList.setFont(font);
        orderList.setString(L"< 당신이 만들어야 할 포춘쿠키 순서 >");
        orderList.setCharacterSize(50);
        orderList.setFillColor(Yellow);
        orderList.setPosition(350, 159);
    }

    void click(sf::RenderWindow& window, int& currentScreen) override {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
    }

    void render(sf::RenderWindow& window) override {
        window.clear(Green);
        window.draw(orderList);
        window.display();
    }

private:
    sf::Text orderList;
};

// 메인 클래스
class Game {
public:
    Game() : window(sf::VideoMode(1440, 1024), "Fortune Cookie"), currentScreen(0) {
        screens[0] = new Start();
        screens[1] = new IngredientIntro();
        screens[2] = new Order();
    }

    ~Game() {
        for (auto screen : screens) {
            delete screen;
        }
    }

    void run() {
        while (window.isOpen()) {
            screens[currentScreen]->click(window, currentScreen);
            screens[currentScreen]->render(window);
        }
    }

private:
    sf::RenderWindow window;
    int currentScreen;
    Screen* screens[3];
};

int main() {
    Game game;
    game.run();
    return 0;
}
