#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>

using namespace sf;
using namespace std;

// �⺻ Screen Ŭ���� (���� ����)
class Screen {
public:
    Screen() : Yellow(252, 171, 64) {
        font.loadFromFile("Pretendard-Bold.otf");
    }

    // â �ݱ� �̺�Ʈ�� ó��
    void CloseEvent(Event& event, RenderWindow& window) {
        if (event.type == Event::Closed) {
            window.close();
        }
    }

    virtual void click(RenderWindow& window, int& currentScreen) = 0;
    virtual void render(RenderWindow& window) = 0;
    virtual ~Screen() = default;

protected:
    Font font;
    Color Yellow;
};

// 1. ���� Ŭ����
class Start : public Screen {
public:
    Start() {
        // �̹���
        img.loadFromFile("start_cookie.png");
        startSprite.setTexture(img);
        startSprite.setPosition(649, 279);

        // "Fortune Cookie" �ؽ�Ʈ
        titleText.setFont(font);
        titleText.setString("Fortune Cookie");
        titleText.setCharacterSize(100);
        titleText.setFillColor(Yellow);
        titleText.setPosition(360, 452);

        // "�����ϱ�" �ؽ�Ʈ
        startBtn.setFont(font);
        startBtn.setString(L"�����ϱ�");
        startBtn.setCharacterSize(43);
        startBtn.setFillColor(Yellow);
        startBtn.setPosition(645, 602);
    }

    void click(RenderWindow& window, int& currentScreen) override {
        Event event;
        while (window.pollEvent(event)) {
            // ���� Ŭ�������� ��ӹ޾� â �ݱ� ó��
            CloseEvent(event, window);

            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    Vector2i mousePos = Mouse::getPosition(window);
                    if (startBtn.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        currentScreen = 1; // ȭ�� ��ȯ
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

// 2. ��� �Ұ� Ŭ����
class IngredientIntro : public Screen {
public:
    IngredientIntro() {
        // �̹��� �ε�
        imgarr[0].loadFromFile("flour.png");
        imgarr[1].loadFromFile("milk.png");
        imgarr[2].loadFromFile("egg.png");
        imgarr[3].loadFromFile("butter.png");
        imgarr[4].loadFromFile("sugar.png");
        imgarr[5].loadFromFile("oil.png");

        // �̹��� ��ġ
        sarr[0].setPosition(850, 310);
        sarr[1].setPosition(860, 400);
        sarr[2].setPosition(860, 470);
        sarr[3].setPosition(850, 540);
        sarr[4].setPosition(850, 600);
        sarr[5].setPosition(860, 680);

        for (int i = 0; i < 6; i++) {
            sarr[i].setTexture(imgarr[i]);
        }

        // �ؽ�Ʈ
        txtarr[0].setString(L"< ��� �Ұ� Time >");
        txtarr[0].setPosition(519, 173);

        txtarr[1].setString(L"�ڷº�");
        txtarr[1].setPosition(520, 324);

        txtarr[2].setString(L"����");
        txtarr[2].setPosition(520, 396);

        txtarr[3].setString(L"���");
        txtarr[3].setPosition(520, 468);

        txtarr[4].setString(L"����");
        txtarr[4].setPosition(520, 540);

        txtarr[5].setString(L"�����Ŀ��");
        txtarr[5].setPosition(520, 612);

        txtarr[6].setString(L"�ٴҶ����");
        txtarr[6].setPosition(520, 684);

        for (int i = 0; i < 7; i++) {
            txtarr[i].setFont(font);
            txtarr[i].setCharacterSize(50);
            txtarr[i].setFillColor(Yellow);
        }

        // �������� �Ѿ�� ��ư
        nextBtn.setFont(font);
        nextBtn.setString("next >");
        nextBtn.setCharacterSize(43);
        nextBtn.setFillColor(Yellow);
        nextBtn.setPosition(1273, 870);
    }

    void click(RenderWindow& window, int& currentScreen) override {
        Event event;
        while (window.pollEvent(event)) {
            CloseEvent(event, window);
            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    sf::Vector2i mousePos = Mouse::getPosition(window);
                    if (nextBtn.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        currentScreen = 2; // ȭ�� ��ȯ
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

// 3. ������ �� ������ �����ִ� Ŭ����
class Order : public Screen {
public:
    Order() {
        orderTxt.setFont(font);
        orderTxt.setString(L"< ����� ������ �� ������Ű ���� >");
        orderTxt.setCharacterSize(50);
        orderTxt.setFillColor(Yellow);
        orderTxt.setPosition(350, 159);

        timeTxt.setFont(font);
        timeTxt.setString(L"15�� ���� ������ �ܿ��ּ���!");
        timeTxt.setCharacterSize(30);
        timeTxt.setFillColor(Yellow);
        timeTxt.setPosition(550, 240);

        // Ÿ�̸� �ؽ�Ʈ ����
        timer.setFont(font);
        timer.setCharacterSize(30);
        timer.setFillColor(Yellow);
        timer.setPosition(1200, 20);

        // �̹��� ��θ� ���Ϳ� ����
        image = { "flour.png", "sugar.png", "milk.png", "egg.png", "oil.png", "butter.png" };

        // ���� �̹��� ����
        random_device rd;
        mt19937 g(rd());
        shuffleImage = image;
        shuffle(shuffleImage.begin(), shuffleImage.end(), g);

        std::cout << "���� �̹���: ";
        for (const auto& image : shuffleImage) {
            std::cout << image << " ";
        }
        std::cout << std::endl;

        int startX = 300; // ���� X ��ġ
        int startY = 470; // ���� Y ��ġ
        int spacing = 150; // ����

        // �̹��� ��ο� ���� Texture�� Sprite ����
        for (size_t i = 0; i < shuffleImage.size(); ++i) {
            Texture* texture = new Texture();
            if (texture->loadFromFile(shuffleImage[i])) {
                Sprite sprite(*texture);
                sprite.setPosition(startX + (i * spacing), startY); // ���η� ��ġ ����
                imgList.push_back(sprite);
                tList.push_back(texture); // Texture ����Ʈ�� �߰�
            }
        }

    }

    // �ùٸ� �̹��� ���� ����
    vector<string> getShuffledOrder() const {
        return shuffleImage; // ���� ���� ����
    }

    ~Order() {
        // �޸� ����
        for (auto texture : tList) {
            delete texture;
        }
    }

    void click(RenderWindow& window, int& currentScreen) override {
        Event event;
        while (window.pollEvent(event)) {
            CloseEvent(event, window);
        }
        // Ÿ�̸� �ʱ�ȭ
        static bool timerStart = false;
        if (!timerStart) {
            clock.restart(); // Ÿ�̸� ���� ����
            timerStart = true;
        }

        // Ÿ�̸� �ʰ� ó��
        float timeOver = clock.getElapsedTime().asSeconds();
        if (timeOver > 15) {
            currentScreen = 3;
        }
    }

    void render(RenderWindow& window) override {
        // ���� �ð� ��� & ǥ��
        float rTime = clock.getElapsedTime().asSeconds();
        int remainingTime = max(0, 15 - static_cast<int>(rTime));
        timer.setString(L"���� �ð�: " + to_wstring(remainingTime) + L"��");
        window.draw(timer);

        window.draw(orderTxt);
        window.draw(timeTxt);

        // �̹��� ������
        for (const auto& sprite : imgList) {
            window.draw(sprite);
        }

        window.display();
    }

private:
    Text orderTxt, timeTxt, timer;
    vector<string> image;               // ���� �̹��� ���
    vector<string> shuffleImage;       // ���� �̹��� ���
    vector<Sprite> imgList;        // ��������Ʈ ����
    vector<Texture*> tList;        // Texture ������ ����
    Clock clock;                 // Ÿ�̸�
};

// 4. ���� ��� �Ϸ� ���� ���� Ŭ����
class Memory : public Screen {
public:
    Memory() {
        mText.setFont(font);
        mText.setString(L"                ������Ű ������ ����ϼ̳���?\n������� ��Ḧ Ŭ���� ������Ű�� �ϼ������ּ���!");
        mText.setCharacterSize(50);
        mText.setFillColor(Yellow);
        mText.setPosition(230, 400);

        // �������� �Ѿ�� ��ư
        nextBtn.setFont(font);
        nextBtn.setString("next >");
        nextBtn.setCharacterSize(43);
        nextBtn.setFillColor(Yellow);
        nextBtn.setPosition(1273, 870);
    }

    void click(RenderWindow& window, int& currentScreen) override {
        Event event;
        while (window.pollEvent(event)) {
            CloseEvent(event, window);
            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    Vector2i mousePos = Mouse::getPosition(window);
                    if (nextBtn.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        currentScreen = 4; // ȭ�� ��ȯ
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

// 5. ������� ������Ű ����� Ŭ����
class MakeInOrder : public Screen {
public:
    MakeInOrder(const vector<string>& orderImg) {
        correctOrder = orderImg; // Order Ŭ�������� ���� �ùٸ� �̹��� ����

        std::cout << "�޾ƿ� �̹���: ";
        for (const auto& image : correctOrder) {
            std::cout << image << " ";
        }
        std::cout << std::endl;

        // �̹��� ���� ����
        shuffleOrder = correctOrder; // ���� ������ �״�� ���� ���� ������ ����
        random_device rd;
        mt19937 g(rd());
        shuffle(shuffleOrder.begin(), shuffleOrder.end(), g);

        // Ÿ�̸� �ؽ�Ʈ ����
        timeTxt.setFont(font);
        timeTxt.setString(L"30�� �ȿ� �տ��� ����� ��� ������� Ŭ�����ּ���.");
        timeTxt.setCharacterSize(50);
        timeTxt.setFillColor(Yellow);
        timeTxt.setPosition(195, 250);

        // Ÿ�̸� �ؽ�Ʈ ����
        timer.setFont(font);
        timer.setCharacterSize(30);
        timer.setFillColor(Yellow);
        timer.setPosition(1200, 20);

        int startX = 300; // ���� X ��ġ
        int startY = 470; // ���� Y ��ġ
        int spacing = 150; // ����

        // ���� �̹��� ��ο� ���� Texture�� Sprite ����
        for (size_t i = 0; i < shuffleOrder.size(); ++i) {
            Texture* texture = new Texture();
            if (texture->loadFromFile(shuffleOrder[i])) {
                Sprite sprite(*texture);
                sprite.setPosition(startX + (i * spacing), startY);
                imgList.push_back(sprite);
                tList.push_back(texture); // Texture ����Ʈ�� �߰�
            }
        }
        // ���� ���� �ε�
        winSound.setBuffer(winBuffer);
        loseSound.setBuffer(loseBuffer);

        // ���� ���� �ʱ�ȭ
        win = false;
        lose = false;
    }

    void click(RenderWindow& window, int& currentScreen) override {
        Event event;
        while (window.pollEvent(event)) {
            CloseEvent(event, window);

            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                Vector2i mousePos = Mouse::getPosition(window);
                for (size_t i = 0; i < imgList.size(); ++i) {
                    if (imgList[i].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        clickOrder.push_back(shuffleOrder[i]);

                        std::cout << "Clicked image: " << shuffleOrder[i] << std::endl;

                        break; // Ŭ���� �̹����� ó���ϰ� �ݺ��� ����
                    }
                }

                if (clickOrder.size() == shuffleOrder.size()) {
                    if (clickOrder == correctOrder) {
                        if (!win) {
                            winSound.play(); // ���� �� win.ogg ���
                            win = true; // ���¸� true�� ����
                        }
                        currentScreen = 5; // ���� ȭ������ �̵�
                    }
                    else {
                        if (!lose) {
                            loseSound.play(); // ���� �� lose.ogg ���
                            lose = true; // ���¸� true�� ����
                        }
                        currentScreen = 6; // ������ �߸� Ŭ���� ���� ȭ������ �̵�
                    }
                }
            }
        }

        static bool timerStart = false;
        if (!timerStart) {
            clock.restart(); // Ÿ�̸Ӹ� ���� ����
            timerStart = true;
        }

        float timeOver = clock.getElapsedTime().asSeconds();
        if (timeOver >= 30) {
            if (!lose) {
                loseSound.play(); // �ð� �ʰ� �� lose.ogg ���
                lose = true; // ���¸� true�� ����
            }
            currentScreen = 7; // �ð��� ��� ���� ������ ȭ������ �̵�
        }
    }

    void render(RenderWindow& window) override {
        window.draw(timeTxt);

        // ���� �ð� ��� �� ǥ��
        float rTime = clock.getElapsedTime().asSeconds();
        int remainingTime = max(0, 30 - static_cast<int>(rTime));
        timer.setString(L"���� �ð�: " + std::to_wstring(remainingTime) + L"��");
        window.draw(timer);

        // ���� ��ġ�� ��ġ�� �̹��� �׸��� (Ŭ���� �̹����� ����)
        for (size_t i = 0; i < imgList.size(); ++i) {
            // Ŭ���� �̹������� Ȯ��
            if (find(clickOrder.begin(), clickOrder.end(), shuffleOrder[i]) == clickOrder.end()) {
                window.draw(imgList[i]);
            }
        }

        window.display();
    }

private:
    vector<string> correctOrder; // �ùٸ� �̹��� ����
    vector<string> shuffleOrder; // �������� ���� �̹��� ����
    vector<string> clickOrder;   // ����ڰ� Ŭ���� ����
    vector<Sprite> imgList;      // �̹��� ��������Ʈ ����Ʈ
    vector<Texture*> tList;      // Texture ������ ����Ʈ
    Clock clock;                 // Ÿ�̸�
    Text timeTxt, timer;         // �ؽ�Ʈ ��ü

    // ���� ���� ����
    SoundBuffer winBuffer;       // ���� �� ����� ���� ����
    SoundBuffer loseBuffer;      // ���� �� ����� ���� ����
    Sound winSound;              // �������� �� ����� ����
    Sound loseSound;             // �������� �� ����� ����

    bool win; // ���� ������ ����� ����
    bool lose; // ���� ������ ����� ����
};

// 6. ������Ű ����� ���� Ŭ����
class Success : public Screen {
public:
    Success() {
        // �⺻ �̹��� �ε�
        baseImg.loadFromFile("success_fortune.png");
        baseSprite.setTexture(baseImg);
        baseSprite.setPosition(434, 200);

        // ���� �� �̹��� �ε� �� �ʱ�ȭ
        crackImg[0].loadFromFile("crack1.png");
        crackImg[1].loadFromFile("crack2.png");
        crackImg[2].loadFromFile("crack3.png");

        crackPos[0] = Vector2f(690, 570);
        crackPos[1] = Vector2f(760, 560);
        crackPos[2] = Vector2f(800, 560);

        for (int i = 0; i < 3; i++) {
            crackSprites[i].setTexture(crackImg[i]);
            crackSprites[i].setPosition(crackPos[i]);
        }

        successText.setFont(font);
        successText.setString(L"������Ű ����� ����!");
        successText.setCharacterSize(50);
        successText.setFillColor(Yellow);
        successText.setPosition(484, 179);

        clickText.setFont(font);
        clickText.setString(L"������Ű�� Ŭ�����ּ���");
        clickText.setCharacterSize(30);
        clickText.setFillColor(Yellow);
        clickText.setPosition(550, 250);

        checkText.setFont(font);
        checkText.setString(L"���� ���� fortune�� Ȯ���� �� �ð�!");
        checkText.setCharacterSize(50);
        checkText.setFillColor(Yellow);
        checkText.setPosition(340, 179);
        checkVisible = false; // �ʱ⿡�� ���� ����

        crack = 0; // �ʱ� �ܰ�
        basePos = baseSprite.getPosition(); // ���� ��ġ ����

        // �ִϸ��̼� ���� �ʱ�ȭ
        isShaking = false;
        shakeTime = 0.2f; // ��鸲 ���� �ð�
        shakeClock.restart(); // Ÿ�̸� �ʱ�ȭ
    }

    void click(RenderWindow& window, int& currentScreen) override {
        Event event;
        while (window.pollEvent(event)) {
            CloseEvent(event, window);

            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                Vector2i pixelPos = Mouse::getPosition(window);
                Vector2f mousePos = window.mapPixelToCoords(pixelPos);

                if (baseSprite.getGlobalBounds().contains(mousePos)) {
                    if (crack < 3) {
                        checkVisible = true;
                        crack++;
                        isShaking = true; // Ŭ�� �� ��鸲 Ȱ��ȭ
                        shakeClock.restart(); // Ÿ�̸� �����
                    }
                    else if (crack == 3) {
                        currentScreen = 8;
                    }
                }
            }
        }
    }

    void render(RenderWindow& window) override {
        // ��鸲 �ִϸ��̼� ó��
        if (isShaking) {
            float elapsedTime = shakeClock.getElapsedTime().asSeconds();
            if (elapsedTime < shakeTime) {
                // ��鸲 ȿ�� ����
                float offset = (elapsedTime / shakeTime) * 10; // �ִ� �̵��� 10
                baseSprite.setPosition(basePos.x + offset, basePos.y);
            }
            else {
                // ��鸲�� ������ ���� ��ġ�� ����
                baseSprite.setPosition(basePos);
                isShaking = false; // ��鸲 ��Ȱ��ȭ
            }
        }

        // �⺻ �̹��� �׸���
        window.draw(baseSprite);

        // ���� �� �̹��� �ܰ躰�� �׸���
        for (int i = 0; i < crack; i++) {
            window.draw(crackSprites[i]);
        }

        // �ؽ�Ʈ ������
        if (checkVisible) {
            window.draw(checkText); // ���ο� ���� ǥ��
        }
        else {
            window.draw(successText); // ���� ���� ǥ��
        }
        window.draw(clickText); // Ŭ�� �ȳ� ����

        window.display();
    }

private:
    Texture baseImg;
    Texture crackImg[3];
    Sprite baseSprite;
    Sprite crackSprites[3];
    Vector2f crackPos[3];
    int crack;

    Vector2f basePos; // ���� ��ġ ����
    Text successText, clickText, checkText;
    bool checkVisible; // ���ο� ���� ǥ�� ����
    bool isShaking; // ��鸲 ���� ����
    Clock shakeClock; // ��鸲 Ÿ�̸�
    float shakeTime; // ��鸲 ���� �ð�
};

class FailScreen : public Screen {
public:
    FailScreen(const std::wstring& message) {
        // ���� �̹���
        img.loadFromFile("fail_fortune.png");
        failSprite.setTexture(img);
        failSprite.setPosition(434, 200);

        // ���� �ؽ�Ʈ
        failText1.setFont(font);
        failText1.setString(L"������Ű ����� ���� ��.��");
        failText1.setCharacterSize(50);
        failText1.setFillColor(Yellow);
        failText1.setPosition(484, 179);

        failText2.setFont(font);
        failText2.setString(message);
        failText2.setCharacterSize(30);
        failText2.setFillColor(Yellow);
        failText2.setPosition(600, 250);

        exitButton.setFont(font);
        exitButton.setString(L"�����ϱ�");
        exitButton.setCharacterSize(30);
        exitButton.setFillColor(Yellow);
        exitButton.setPosition(1273, 870);
    }

    void click(RenderWindow& window, int& currentScreen) override {
        Event event;
        while (window.pollEvent(event)) {
            CloseEvent(event, window);
            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                Vector2i mousePos = Mouse::getPosition(window);
                if (exitButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    window.close(); // â �ݱ�
                }
            }
        }
    }

    void render(RenderWindow& window) override {
        window.draw(failSprite);
        window.draw(failText1);
        window.draw(failText2);
        window.draw(exitButton);
        window.display();
    }

protected:
    Texture img;
    Sprite failSprite;
    Text failText1, failText2;
    Text exitButton;
};

// 7. ������ ���� �ʾ��� ���� ���� Ŭ����
class OrderFail : public FailScreen {
public:
    OrderFail() : FailScreen(L"������ ���� �ʾҾ��") {}
};

// 8. 30�ʰ� �� ������ ���� ���� Ŭ����
class TimeOverFail : public FailScreen {
public:
    TimeOverFail() : FailScreen(L"30�ʰ� �� �������") {}
};


// 9. ������ ��� �˷��ִ� Ŭ����
class Fortune : public Screen {
public:
    Fortune() {
        // �̹��� �ε�
        imgarr[0].loadFromFile("fortune_left.png");
        imgarr[1].loadFromFile("fortune_right.png");
        imgarr[2].loadFromFile("paper.png");

        // �̹��� ��ġ ����
        sarr[0].setPosition(110, 395);
        sarr[1].setPosition(1098, 320);
        sarr[2].setPosition(340, 445);

        for (int i = 0; i < 3; i++) {
            sarr[i].setTexture(imgarr[i]);
        }

        fText.setFont(font);
        fText.setString(L"���� ���� fortune��?");
        fText.setCharacterSize(50);
        fText.setFillColor(Yellow);
        fText.setPosition(484, 179);

        // ���� �ʱ�ȭ
        srand(static_cast<unsigned int>(time(0)));

        lifeQuotes = { "1.png", "2.png", "3.png", "4.png", "4.png", "6.png", "7.png", "8.png", "9.png", "10.png", "11.png", "12.png", "13.png", "14.png", "15.png", "16.png", "17.png", "18.png", "19.png" };

        // �������� �̹��� ����
        int randomImg = rand() % lifeQuotes.size();
        if (fTexture.loadFromFile(lifeQuotes[randomImg])) {
            fSprite.setTexture(fTexture);
        }

        exitButton.setFont(font);
        exitButton.setString(L"�����ϱ�");
        exitButton.setCharacterSize(30);
        exitButton.setFillColor(Yellow);
        exitButton.setPosition(1273, 870);
    }

    void click(RenderWindow& window, int& currentScreen) override {
        Event event;
        while (window.pollEvent(event)) {
            CloseEvent(event, window);
        }
        if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
            Vector2i mousePos = Mouse::getPosition(window);
            if (exitButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                window.close(); // â �ݱ�
            }
        }
    }

    void render(RenderWindow& window) override {
        // �̹����� �߰��� ��ġ�ϰ�
        float centerX = (window.getSize().x - fSprite.getGlobalBounds().width) / 2;
        float centerY = (window.getSize().y - fSprite.getGlobalBounds().height) / 2;
        fSprite.setPosition(centerX, centerY);
        window.draw(fText);
        for (int i = 0; i < 3; i++) {
            window.draw(sarr[i]);
        }
        window.draw(fSprite);  // �������� ���õ� �̹��� �׸���

        // ���� ��ư
        window.draw(exitButton);

        window.display();
    }

private:
    Texture imgarr[6];
    Sprite sarr[6];
    Text fText;
    vector<string> lifeQuotes;
    Texture fTexture;
    Sprite fSprite;
    Text exitButton;
};

// ���� Ŭ����
class Game {
public:
    Game() : window(VideoMode(1440, 1024), "Fortune Cookie"), currentScreen(0), Green(0, 145, 50) {
        screens[0] = new Start();
        screens[1] = new IngredientIntro();
        screens[2] = new Order();
        screens[3] = new Memory();
        Order* orderScreen = static_cast<Order*>(screens[2]);
        vector<string> correctOrder = orderScreen->getShuffledOrder(); // ���� ���� ��������
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