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

        nextTxt.setFont(font);
        nextTxt.setString(L"다 외운 후 next를 눌러주세요!");
        nextTxt.setCharacterSize(30);
        nextTxt.setFillColor(Yellow);
        nextTxt.setPosition(550, 240);

        nextBtn.setFont(font);
        nextBtn.setString("next >");
        nextBtn.setCharacterSize(43);
        nextBtn.setFillColor(Yellow);
        nextBtn.setPosition(1273, 870);

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

    // 섞인 이미지 순서를 반환
    vector<string> getImageOrder() const {
        return image; // 섞인 이미지 순서를 반환
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
            else if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    Vector2i mousePos = Mouse::getPosition(window);
                    if (nextBtn.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        currentScreen = 3; // 화면 전환
                    }
                }
            }
        }
    }

    void render(RenderWindow& window) override {
        window.draw(orderTxt);
        window.draw(nextTxt);
        window.draw(nextBtn);

        // 이미지 렌더링
        for (const auto& sprite : imgList) {
            window.draw(sprite);
        }

        window.display();
    }

private:
    Text orderTxt, nextTxt, nextBtn;
    vector<std::string> image;     // 이미지 경로를 저장할 벡터
    vector<Sprite> imgList;        // 스프라이트 벡터
    vector<Texture*> tList;        // Texture 포인터 벡터
};


// 4. 순서 기억 완료 문구 띄우는 클래스
class Memory : public Screen {
public:
    Memory() {
        mText.setFont(font);
        mText.setString(L"                포춘쿠키 순서를 기억하셨나요?\n순서대로 재료를 클릭해 포춘쿠키를 완성시켜주세요!");
        mText.setCharacterSize(50);
        mText.setFillColor(Yellow);
        mText.setPosition(230, 400);

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
                        currentScreen = 4; // 화면 전환
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

// 5. 순서대로 포춘쿠키 만들기 클래스
class MakeInOrder : public Screen {
public:
    MakeInOrder(const vector<string>& order) {
        // 타이머 텍스트 설정
        timeTxt.setFont(font);
        timeTxt.setString(L"30초 안에 앞에서 기억한 재료 순서대로 클릭해주세요.");
        timeTxt.setCharacterSize(50);
        timeTxt.setFillColor(Yellow);
        timeTxt.setPosition(195, 250);

        // 타이머 텍스트 설정
        timer.setFont(font);
        timer.setCharacterSize(30);
        timer.setFillColor(Yellow);
        timer.setPosition(1200, 20);

        correctOrder = order; // Order 클래스에서 받은 올바른 이미지 순서

        int startX = 300; // 시작 X 위치
        int startY = 470; // 시작 Y 위치
        int spacing = 150; // 간격

        // 섞인 이미지 경로에 대해 Texture와 Sprite 생성
        for (size_t i = 0; i < correctOrder.size(); ++i) {
            Texture* texture = new Texture();
            if (texture->loadFromFile(correctOrder[i])) {
                Sprite sprite(*texture);
                sprite.setPosition(startX + (i * spacing), startY);
                imgList.push_back(sprite);
                tList.push_back(texture); // Texture 리스트에 추가
            }
        }
    }

    ~MakeInOrder() {
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

            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                Vector2i mousePos = Mouse::getPosition(window);
                for (size_t i = 0; i < imgList.size(); ++i) {
                    if (imgList[i].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        // 클릭한 이미지의 인덱스를 clickedOrder에 추가
                        clickedOrder.push_back(i);

                        // 중복된 클릭 방지
                        imgList.erase(imgList.begin() + i);
                        tList.erase(tList.begin() + i);
                        break;
                    }
                }

                // 클릭 순서가 모두 맞추어진 경우 체크
                if (clickedOrder.size() == correctOrder.size()) {
                    bool isCorrect = true;
                    for (size_t j = 0; j < correctOrder.size(); ++j) {
                        // 클릭한 이미지의 인덱스를 이용하여 correctOrder에서 해당 이미지 경로 가져오기
                        std::string clickedImagePath = correctOrder[clickedOrder[j]];

                        // 클릭한 이미지 경로와 올바른 순서의 이미지 경로 비교
                        if (clickedImagePath != correctOrder[j]) {
                            isCorrect = false;
                            break;
                        }
                    }

                    if (isCorrect) {
                        currentScreen = 5; // 성공 화면으로 이동
                    }
                    else {
                        currentScreen = 6; // 실패 화면으로 이동
                    }
                }
            }

        }

        // 타이머 초기화: 게임이 시작될 때만 호출
        static bool timerStarted = false;
        if (!timerStarted) {
            clock.restart(); // 타이머를 새로 시작
            timerStarted = true;
        }

        // 타이머 초과 처리
        float elapsedTime = clock.getElapsedTime().asSeconds();
        if (elapsedTime >= 30) {
            currentScreen = 6; // 실패 화면으로 이동
        }
    }

    void render(RenderWindow& window) override {
        window.draw(timeTxt);

        // 남은 시간 계산 및 표시
        float elapsedTime = clock.getElapsedTime().asSeconds();
        int remainingTime = max(0, 30 - static_cast<int>(elapsedTime));
        timer.setString(L"남은 시간: " + std::to_wstring(remainingTime) + L"초");
        window.draw(timer);

        // 랜덤 위치에 배치된 이미지 그리기
        for (const auto& sprite : imgList) {
            window.draw(sprite);
        }

        window.display();
    }

private:
    vector<string> correctOrder; // 올바른 이미지 순서
    vector<int> clickedOrder;    // 사용자가 클릭한 순서
    vector<Sprite> imgList;      // 이미지 스프라이트 리스트
    vector<Texture*> tList;      // Texture 포인터 리스트
    Clock clock;                 // 타이머
    Text timeTxt, timer;         // 텍스트 객체
};

// 6. 포춘쿠키 만들기 성공 클래스
class Success : public Screen {
public:
    Success() {
        // 기본 이미지 로드
        baseImg.loadFromFile("success_fortune.png");
        baseSprite.setTexture(baseImg);
        baseSprite.setPosition(434, 200);

        // 금이 간 이미지 로드 및 초기화
        crackedImgs[0].loadFromFile("crack1.png");
        crackedImgs[1].loadFromFile("crack2.png");
        crackedImgs[2].loadFromFile("crack3.png");

        crackedPositions[0] = Vector2f(690, 570);
        crackedPositions[1] = Vector2f(760, 560);
        crackedPositions[2] = Vector2f(800, 560);

        for (int i = 0; i < 3; i++) {
            crackSprites[i].setTexture(crackedImgs[i]);
            crackSprites[i].setPosition(crackedPositions[i]);
        }

        successText.setFont(font);
        successText.setString(L"포춘쿠키 만들기 성공!");
        successText.setCharacterSize(50);
        successText.setFillColor(Yellow);
        successText.setPosition(484, 179);

        clickText.setFont(font);
        clickText.setString(L"포춘쿠키를 클릭해주세요");
        clickText.setCharacterSize(30);
        clickText.setFillColor(Yellow);
        clickText.setPosition(550, 250);

        checkText.setFont(font);
        checkText.setString(L"드디어 나의 fortune을 확인해 볼 시간!");
        checkText.setCharacterSize(50);
        checkText.setFillColor(Yellow);
        checkText.setPosition(340, 179);
        checkVisible = false; // 초기에는 숨김 상태

        crackStage = 0; // 초기 단계
    }

    void click(RenderWindow& window, int& currentScreen) override {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }

            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                Vector2i pixelPos = Mouse::getPosition(window);
                Vector2f mousePos = window.mapPixelToCoords(pixelPos);

                if (baseSprite.getGlobalBounds().contains(mousePos)) {
                    if (crackStage < 3) {
                        checkVisible = true;
                        crackStage++;
                    }
                    else if (crackStage == 3) {
                        currentScreen = 1;
                    }
                }
            }
        }
    }

    void render(RenderWindow& window) override {
        // 기본 이미지 그리기
        window.draw(baseSprite);

        // 금이 간 이미지 단계별로 그리기
        for (int i = 0; i < crackStage; i++) {
            window.draw(crackSprites[i]);
        }

        // 텍스트 렌더링
        if (checkVisible) {
            window.draw(checkText); // 새로운 문구 표시
        }
        else {
            window.draw(successText); // 기존 문구 표시
        }
        window.draw(clickText); // 클릭 안내 문구

        window.display();
    }

private:
    Texture baseImg;
    Texture crackedImgs[3];
    Sprite baseSprite;
    Sprite crackSprites[3];
    Vector2f crackedPositions[3];
    int crackStage;
    
    Text successText, clickText, checkText; // 추가 텍스트
    bool checkVisible; // 새로운 문구 표시 여부
};


// 7. 포춘쿠키 만들기 실패 클래스
class Fail : public Screen {
public:
    Fail() {
        // 이미지
        img.loadFromFile("fail_fortune.png");
        failSprite.setTexture(img);
        failSprite.setPosition(434, 200);

        // "Fortune Cookie" 텍스트
        failText.setFont(font);
        failText.setString(L"포춘쿠키 만들기 실패 ㅠ.ㅠ");
        failText.setCharacterSize(50);
        failText.setFillColor(Yellow);
        failText.setPosition(484, 179);

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
                        currentScreen = 5; // 화면 전환
                    }
                }
            }
        }
    }

    void render(RenderWindow& window) override {
        window.draw(failSprite);
        window.draw(failText);
        window.draw(nextBtn);
        window.display();
    }

private:
    Texture img;
    Sprite failSprite;
    Text failText, nextBtn;
};

// 메인 클래스
class Game {
public:
    Game() : window(VideoMode(1440, 1024), "Fortune Cookie"), currentScreen(0), Green(0, 145, 50) {
        screens[0] = new Start();
        screens[1] = new IngredientIntro();
        screens[2] = new Order();
        screens[3] = new Memory();
        vector<string> correctOrder = orderScreen.getImageOrder();
        screens[4] = new MakeInOrder(correctOrder);
        screens[5] = new Success();
        screens[6] = new Fail();
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
    Screen* screens[7];
    Order orderScreen;
};

int main() {
    Game game;
    game.run();
    return 0;
}