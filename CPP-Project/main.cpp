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
        timeTxt.setString(L"15초 동안 순서를 외워주세요!");
        timeTxt.setCharacterSize(30);
        timeTxt.setFillColor(Yellow);
        timeTxt.setPosition(550, 240);

        // 타이머 텍스트 설정
        timer.setFont(font);
        timer.setCharacterSize(30);
        timer.setFillColor(Yellow);
        timer.setPosition(1200, 20);

        // 이미지 경로를 벡터에 저장
        image = { "flour.png", "sugar.png", "milk.png", "egg.png", "oil.png", "butter.png" };

        // 섞은 이미지 경로를 저장
        random_device rd;
        mt19937 g(rd());
        shuffledImage = image;
        shuffle(shuffledImage.begin(), shuffledImage.end(), g);

        std::cout << "Correct order of images2: ";
        for (const auto& image : shuffledImage) {
            std::cout << image << " ";
        }
        std::cout << std::endl;

        int startX = 300; // 시작 X 위치
        int startY = 470; // 시작 Y 위치
        int spacing = 150; // 간격

        // 이미지 경로에 대해 Texture와 Sprite 생성
        for (size_t i = 0; i < shuffledImage.size(); ++i) {
            Texture* texture = new Texture();
            if (texture->loadFromFile(shuffledImage[i])) {
                Sprite sprite(*texture);
                sprite.setPosition(startX + (i * spacing), startY); // 가로로 위치 조정
                imgList.push_back(sprite);
                tList.push_back(texture); // Texture 리스트에 추가
            }
        }
        
    }

    // 올바른 이미지 순서를 반환
    vector<string> getShuffledOrder() const {
        return shuffledImage; // 섞인 순서를 반환
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
        // 타이머 초기화: 게임이 시작될 때만 호출
        static bool timerStarted = false;
        if (!timerStarted) {
            clock.restart(); // 타이머를 새로 시작
            timerStarted = true;
        }

        // 타이머 초과 처리
        float elapsedTime = clock.getElapsedTime().asSeconds();
        if (elapsedTime > 15) {
            currentScreen = 3;
        }
    }

    void render(RenderWindow& window) override {
        // 남은 시간 계산 및 표시
        float elapsedTime = clock.getElapsedTime().asSeconds();
        int remainingTime = max(0, 15 - static_cast<int>(elapsedTime));
        timer.setString(L"남은 시간: " + to_wstring(remainingTime) + L"초");
        window.draw(timer);
        window.draw(orderTxt);
        window.draw(timeTxt);

        // 이미지 렌더링
        for (const auto& sprite : imgList) {
            window.draw(sprite);
        }

        window.display();
    }

private:
    Text orderTxt, timeTxt, timer;
    vector<string> image;               // 원본 이미지 경로
    vector<string> shuffledImage;       // 섞은 이미지 경로
    vector<Sprite> imgList;        // 스프라이트 벡터
    vector<Texture*> tList;        // Texture 포인터 벡터
    Clock clock;                 // 타이머
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
        correctOrder = order; // Order 클래스에서 받은 올바른 이미지 순서

        std::cout << "Correct order of images: ";
        for (const auto& image : correctOrder) {
            std::cout << image << " ";
        }
        std::cout << std::endl;

        // 이미지 랜덤 섞기
        shuffledOrder = correctOrder; // 원본 순서를 그대로 섞기 전의 순서로 저장
        random_device rd;
        mt19937 g(rd());
        shuffle(shuffledOrder.begin(), shuffledOrder.end(), g); 

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

        int startX = 300; // 시작 X 위치
        int startY = 470; // 시작 Y 위치
        int spacing = 150; // 간격

        // 섞인 이미지 경로에 대해 Texture와 Sprite 생성
        for (size_t i = 0; i < shuffledOrder.size(); ++i) {
            Texture* texture = new Texture();
            if (texture->loadFromFile(shuffledOrder[i])) {
                Sprite sprite(*texture);
                sprite.setPosition(startX + (i * spacing), startY);
                imgList.push_back(sprite);
                tList.push_back(texture); // Texture 리스트에 추가
            }
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
                        // 클릭한 이미지의 경로를 clickedOrder에 추가
                        clickedOrder.push_back(shuffledOrder[i]);

                        // 디버그 출력: 클릭한 이미지 확인
                        std::cout << "Clicked image: " << shuffledOrder[i] << std::endl;

                        break; // 클릭한 이미지만 처리하고 반복문 종료
                    }
                }

                // 클릭 순서가 모두 맞추어진 경우 체크
                if (clickedOrder.size() == shuffledOrder.size()) {
                    if (clickedOrder == correctOrder) {
                        currentScreen = 5; // 성공 화면으로 이동
                    }
                    else {
                        currentScreen = 6; // 순서가 맞지 않은 실패 화면으로 이동
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
            currentScreen = 7; // 시간이 모두 지나 실패한 화면으로 이동
        }
    }


    void render(RenderWindow& window) override {
        window.draw(timeTxt);

        // 남은 시간 계산 및 표시
        float elapsedTime = clock.getElapsedTime().asSeconds();
        int remainingTime = max(0, 30 - static_cast<int>(elapsedTime));
        timer.setString(L"남은 시간: " + std::to_wstring(remainingTime) + L"초");
        window.draw(timer);

        // 랜덤 위치에 배치된 이미지 그리기 (클릭된 이미지는 제외)
        for (size_t i = 0; i < imgList.size(); ++i) {
            // 클릭된 이미지인지 확인
            if (find(clickedOrder.begin(), clickedOrder.end(), shuffledOrder[i]) == clickedOrder.end()) {
                window.draw(imgList[i]);
            }
        }

        window.display();
    }

private:
    vector<string> correctOrder; // 올바른 이미지 순서
    vector<string> shuffledOrder; // 랜덤으로 섞인 이미지 순서
    vector<string> clickedOrder; // 사용자가 클릭한 순서
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
                        currentScreen = 8;
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


// 7. 포춘쿠키 만들기 실패 클래스 (순서가 맞지 않았을 때)
class OrderFail : public Screen {
public:
    OrderFail() {
        // 이미지
        img.loadFromFile("fail_fortune.png");
        failSprite.setTexture(img);
        failSprite.setPosition(434, 200);

        failText1.setFont(font);
        failText1.setString(L"포춘쿠키 만들기 실패 ㅠ.ㅠ");
        failText1.setCharacterSize(50);
        failText1.setFillColor(Yellow);
        failText1.setPosition(484, 179);

        failText2.setFont(font);
        failText2.setString(L"순서가 맞지 않았어요");
        failText2.setCharacterSize(30);
        failText2.setFillColor(Yellow);
        failText2.setPosition(600, 250);
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
        window.draw(failSprite);
        window.draw(failText1);
        window.draw(failText2);
        window.display();
    }

private:
    Texture img;
    Sprite failSprite;
    Text failText1, failText2;
};

// 8. 포춘쿠키 만들기 실패 클래스 (시간이 다 지났을 때)
class TimeOverFail : public Screen {
public:
    TimeOverFail() {
        // 이미지
        img.loadFromFile("fail_fortune.png");
        failSprite.setTexture(img);
        failSprite.setPosition(434, 200);

        failText1.setFont(font);
        failText1.setString(L"포춘쿠키 만들기 실패 ㅠ.ㅠ");
        failText1.setCharacterSize(50);
        failText1.setFillColor(Yellow);
        failText1.setPosition(484, 179);

        failText2.setFont(font);
        failText2.setString(L"30초가 다 지났어요");
        failText2.setCharacterSize(30);
        failText2.setFillColor(Yellow);
        failText2.setPosition(600, 250);
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
        window.draw(failSprite);
        window.draw(failText1);
        window.draw(failText2);
        window.display();
    }

private:
    Texture img;
    Sprite failSprite;
    Text failText1, failText2;
};

// 9. 오늘의 운세를 알려주는 클래스
class Fortune : public Screen {
public:
    Fortune() {
        // 이미지 로드
        imgarr[0].loadFromFile("fortune_left.png");
        imgarr[1].loadFromFile("fortune_right.png");
        imgarr[2].loadFromFile("paper.png");

        // 이미지 위치 설정
        sarr[0].setPosition(110, 395);
        sarr[1].setPosition(1098, 320);
        sarr[2].setPosition(340, 445);

        for (int i = 0; i < 3; i++) {
            sarr[i].setTexture(imgarr[i]);
        }

        fText.setFont(font);
        fText.setString(L"오늘 나의 fortune은?");
        fText.setCharacterSize(50);
        fText.setFillColor(Color::Yellow);
        fText.setPosition(484, 179);

        // 랜덤 초기화
        srand(static_cast<unsigned int>(time(0)));

        lifeQuotes = { "1.png", "2.png", "3.png", "4.png", "4.png", "6.png", "7.png", "8.png", "9.png", "10.png", "11.png", "12.png", "13.png", "14.png", "15.png", "16.png", "17.png", "18.png", "19.png" };

        // 랜덤으로 이미지 선택
        int randomIndex = rand() % lifeQuotes.size();
        if (fortuneTexture.loadFromFile(lifeQuotes[randomIndex])) {
            fortuneSprite.setTexture(fortuneTexture);
        }
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
        // 이미지의 중심을 화면의 중심에 위치시키기 위해 좌표 계산
        float centerX = (window.getSize().x - fortuneSprite.getGlobalBounds().width) / 2;
        float centerY = (window.getSize().y - fortuneSprite.getGlobalBounds().height) / 2;
        fortuneSprite.setPosition(centerX, centerY);
        window.draw(fText);
        for (int i = 0; i < 3; i++) {
            window.draw(sarr[i]);
        }
        window.draw(fortuneSprite);  // 랜덤으로 선택된 이미지 그리기
        window.display();
    }

private:
    Texture imgarr[6];
    Sprite sarr[6];
    Text fText;
    vector<string> lifeQuotes;
    Texture fortuneTexture;
    Sprite fortuneSprite;
};


// 메인 클래스
class Game {
public:
    Game() : window(VideoMode(1440, 1024), "Fortune Cookie"), currentScreen(0), Green(0, 145, 50) {
        screens[0] = new Start();
        screens[1] = new IngredientIntro();
        screens[2] = new Order();
        screens[3] = new Memory();
        Order* orderScreen = static_cast<Order*>(screens[2]);
        vector<string> correctOrder = orderScreen->getShuffledOrder(); // 원래 순서 가져오기
        screens[4] = new MakeInOrder(correctOrder);
        screens[5] = new Success();
        screens[6] = new OrderFail();
        screens[7] = new TimeOverFail();
        screens[8] = new Fortune();
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
    Screen* screens[9];
    Order orderScreen;
};

int main() {
    Game game;
    game.run();
    return 0;
}