#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>

using namespace sf;
using namespace std;

// 기본 Screen 클래스 (가장 상위)
class Screen {
public:
    Screen() : Yellow(252, 171, 64) {
        font.loadFromFile("Pretendard-Bold.otf");
    }

    virtual void click(RenderWindow& window, int& currentScreen) = 0;
    virtual void render(RenderWindow& window) = 0;
    virtual ~Screen() = default;

protected:
    Font font;
    Color Yellow;
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

        // 이미지 위치
        sarr[0].setPosition(850, 310);
        sarr[1].setPosition(860, 400);
        sarr[2].setPosition(860, 470);
        sarr[3].setPosition(850, 540);
        sarr[4].setPosition(850, 600);
        sarr[5].setPosition(860, 680);

        for (int i = 0; i < 6; i++) {
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

        for (int i = 0; i < 7; i++) {
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
        window.draw(nextBtn);
        for (int i = 0; i < 6; i++)
            window.draw(sarr[i]);
        for (int i = 0; i < 7; i++)
            window.draw(txtarr[i]);
        window.display();
    }

private:
    Text nextBtn, txtarr[7];
    Sprite sarr[6];
    Texture imgarr[6];
};

// 3. 만들어야 할 순서를 보여주는 클래스
class Order : public Screen {
public:
    Order() {
        orderTxt.setFont(font);
        orderTxt.setString(L"< 당신이 만들어야 할 포춘쿠키 순서 >");
        orderTxt.setCharacterSize(50);
        orderTxt.setFillColor(Yellow);
        orderTxt.setPosition(350, 159);

        timeTxt.setFont(font);
        timeTxt.setString(L"15초 안에 순서를 외워주세요!");
        timeTxt.setCharacterSize(30);
        timeTxt.setFillColor(Yellow);
        timeTxt.setPosition(550, 240);

        // 몇 초 남았는지 알려주는 텍스트
        timer.setFont(font);
        timer.setCharacterSize(30);
        timer.setFillColor(Yellow);
        timer.setPosition(1150, 50);

        // 이미지 경로를 벡터에 저장
        image = { "flour.png", "sugar.png", "milk.png", "egg.png", "oil.png", "butter.png" };

        // 랜덤하게 섞기
        random_device rd;
        mt19937 g(rd());
        shuffle(image.begin(), image.end(), g);

        int startX = 300; // 시작 X 위치
        int startY = 470; // 시작 Y 위치
        int spacing = 150; // 간격

        // 섞인 이미지 경로에 대해 Texture와 Sprite 생성
        for (size_t i = 0; i < image.size(); ++i) {
            Texture* texture = new Texture();
            if (texture->loadFromFile(image[i])) {
                Sprite sprite(*texture);
                sprite.setPosition(startX + (i * spacing), startY); // 가로로 위치 조정
                imgList.push_back(sprite);
                tList.push_back(texture); // Texture 리스트에 추가
            }
        }
    }

    ~Order() {
        // 메모리 해제
        for (auto texture : tList) {
            delete texture;
        }
    }

    void click(RenderWindow& window, int& currentScreen) override {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }

        // 타이머 초기화 (게임 시작 시점에서만 호출)
        static bool timerStarted = false;
        if (!timerStarted) {
            clock.restart(); // 타이머를 새로 시작
            timerStarted = true;
        }

        // 매 프레임마다 경과 시간 확인
        float elapsedTime = clock.getElapsedTime().asSeconds();
        if (elapsedTime > 15) {
            currentScreen = 3; // 다음 화면으로 이동
        }
    }

    void render(RenderWindow& window) override {
        window.draw(orderTxt);
        window.draw(timeTxt);

        // 매 프레임마다 경과 시간 갱신
        float elapsedTime = clock.getElapsedTime().asSeconds();
        int remainingTime = max(0, 15 - static_cast<int>(elapsedTime));

        // 타이머 계산 및 표시
        timer.setString(L"남은 시간: " + to_string(remainingTime) + L"초");
        window.draw(timer);

        // 이미지 렌더링
        for (const auto& sprite : imgList) {
            window.draw(sprite);
        }

        window.display();
    }

private:
    Text orderTxt, timeTxt, timer;
    vector<std::string> image;     // 이미지 경로를 저장할 벡터
    vector<Sprite> imgList;        // 스프라이트 벡터
    vector<Texture*> tList;        // Texture 포인터 벡터
    Clock clock;                   // 시간 측정을 위한 SFML Clock
};

// 4. 순서 기억 완료 문구 띄우는 클래스
class Memory : public Screen {
public:
    Memory() {
        mText.setFont(font);
        mText.setString(L"포춘쿠키 순서를 기억하셨나요?\n순서대로 쿠키를 움직여 포춘쿠키를 완성시켜주세요!");
        mText.setCharacterSize(50);
        mText.setFillColor(Yellow);
        mText.setPosition(250, 470);

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
                    Vector2i mousePos = Mouse::getPosition(window);
                    if (nextBtn.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        currentScreen = 1; // 화면 전환
                    }
                }
            }
        }
    }

    void render(RenderWindow& window) override {
        window.draw(startSprite);
        window.draw(mText);
        window.draw(nextBtn);
        window.display();
    }

private:
    Texture img;
    Sprite startSprite;
    Text mText, nextBtn;
};


// 메인 클래스
class Game {
public:
    Game() : window(VideoMode(1440, 1024), "Fortune Cookie"), currentScreen(0), Green(0, 145, 50) {
        screens[0] = new Start();
        screens[1] = new IngredientIntro();
        screens[2] = new Order();
        screens[3] = new Memory();
    }

    ~Game() {
        for (auto screen : screens) {
            delete screen;
        }
    }

    void run() {
        while (window.isOpen()) {
            window.clear(Green);
            screens[currentScreen]->click(window, currentScreen);
            screens[currentScreen]->render(window);
        }
    }

private:
    RenderWindow window;
    Color Green;
    int currentScreen;
    Screen* screens[4];
};

int main() {
    Game game;
    game.run();
    return 0;
}
