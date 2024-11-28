#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

// 기본 Screen 클래스 (가장 상위)
class Screen {
public:
    Screen() : Green(0, 145, 50), Yellow(252, 171, 64) {
        font.loadFromFile("Pretendard-Bold.otf");
    }

    virtual void click(RenderWindow& window, int& currentScreen) = 0;
    virtual void render(RenderWindow& window) = 0;
    virtual ~Screen() = default;

protected:
    Font font;
    Color Green, Yellow;
};

// 1. 시작 클래스
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

    void click(RenderWindow& window, int& currentScreen) override {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            else if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    Vector2i mousePos = Mouse::getPosition(window);
                    if (startBtn.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        currentScreen = 1; // 화면 전환
                    }
                }
            }
        }
    }

    void render(RenderWindow& window) override {
        window.clear(Green);
        window.draw(startSprite);
        window.draw(titleText);
        window.draw(startBtn);
        window.display();
    }

private:
    Texture img;
    Sprite startSprite;
    Text titleText, startBtn;
};

// 2. 재료 소개 클래스
class IngredientIntro : public Screen {
public:
    IngredientIntro() {
        // 이미지 로드
        imgarr[0].loadFromFile("flour.png");
        imgarr[1].loadFromFile("milk.png");
        imgarr[2].loadFromFile("egg.png");
        imgarr[3].loadFromFile("butter.png");
        imgarr[4].loadFromFile("sugar.png");
        imgarr[5].loadFromFile("oil.png");
        imgarr[6].loadFromFile("choco.png");

        // 이미지 위치
        sarr[0].setPosition(850, 310);
        sarr[1].setPosition(860, 400);
        sarr[2].setPosition(860, 470);
        sarr[3].setPosition(850, 500);
        sarr[4].setPosition(850, 600);
        sarr[5].setPosition(860, 680);
        sarr[6].setPosition(870, 750);

        for (int i = 0; i < 7; i++) {
            sarr[i].setTexture(imgarr[i]);
        }

        // 텍스트
        txtarr[0].setString(L"< 재료 소개 Time >");
        txtarr[0].setPosition(519, 173);

        txtarr[1].setString(L"박력분");
        txtarr[1].setPosition(520, 324);

        txtarr[2].setString(L"우유");
        txtarr[2].setPosition(520, 396);

        txtarr[3].setString(L"계란");
        txtarr[3].setPosition(520, 468);

        txtarr[4].setString(L"버터");
        txtarr[4].setPosition(520, 540);

        txtarr[5].setString(L"슈가파우더");
        txtarr[5].setPosition(520, 612);

        txtarr[6].setString(L"바닐라오일");
        txtarr[6].setPosition(520, 684);

        txtarr[7].setString(L"초콜릿");
        txtarr[7].setPosition(520, 750);

        for (int i = 0; i < 8; i++) {
            txtarr[i].setFont(font);
            txtarr[i].setCharacterSize(50);
            txtarr[i].setFillColor(Yellow);
        }

        // 다음으로 넘어가는 버튼
        nextBtn.setFont(font);
        nextBtn.setString("next >");
        nextBtn.setCharacterSize(43);
        nextBtn.setFillColor(Yellow);
        nextBtn.setPosition(1273, 870);
    }

    void click(RenderWindow& window, int& currentScreen) override {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            else if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    sf::Vector2i mousePos = Mouse::getPosition(window);
                    if (nextBtn.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        currentScreen = 2; // 화면 전환
                    }
                }
            }
        }
    }

    void render(RenderWindow& window) override {
        window.clear(Green);
        window.draw(nextBtn);

        for (int i = 0; i < 7; i++)
            window.draw(sarr[i]);

        for (int i = 0; i < 8; i++)
            window.draw(txtarr[i]);

        window.display();
    }

private:
    Text IngredientText, nextBtn;
    Text txtarr[8];
    Sprite sarr[7];
    Texture imgarr[7];
};

// 3. 만들어야 할 순서를 보여주는 클래스
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

    void click(RenderWindow& window, int& currentScreen) override {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }
    }

    void render(RenderWindow& window) override {
        window.clear(Green);
        window.draw(orderList);
        window.display();
    }

private:
    Text orderList;
};

// 메인 클래스
class Game {
public:
    Game() : window(VideoMode(1440, 1024), "Fortune Cookie"), currentScreen(0) {
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
    RenderWindow window;
    int currentScreen;
    Screen* screens[3];
};

int main() {
    Game game;
    game.run();
    return 0;
}
