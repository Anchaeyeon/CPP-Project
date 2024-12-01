#include <SFML/Graphics.hpp>
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
            if (event.type == Event::Closed) {
                window.close();
            }
            else if (event.type == Event::MouseButtonPressed) {
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
            if (event.type == Event::Closed) {
                window.close();
            }
            else if (event.type == Event::MouseButtonPressed) {
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

        nextTxt.setFont(font);
        nextTxt.setString(L"�� �ܿ� �� next�� �����ּ���!");
        nextTxt.setCharacterSize(30);
        nextTxt.setFillColor(Yellow);
        nextTxt.setPosition(550, 240);

        nextBtn.setFont(font);
        nextBtn.setString("next >");
        nextBtn.setCharacterSize(43);
        nextBtn.setFillColor(Yellow);
        nextBtn.setPosition(1273, 870);

        // �̹��� ��θ� ���Ϳ� ����
        image = { "flour.png", "sugar.png", "milk.png", "egg.png", "oil.png", "butter.png" };

        // �����ϰ� ����
        random_device rd;
        mt19937 g(rd());
        shuffle(image.begin(), image.end(), g);

        int startX = 300; // ���� X ��ġ
        int startY = 470; // ���� Y ��ġ
        int spacing = 150; // ����

        // ���� �̹��� ��ο� ���� Texture�� Sprite ����
        for (size_t i = 0; i < image.size(); ++i) {
            Texture* texture = new Texture();
            if (texture->loadFromFile(image[i])) {
                Sprite sprite(*texture);
                sprite.setPosition(startX + (i * spacing), startY); // ���η� ��ġ ����
                imgList.push_back(sprite);
                tList.push_back(texture); // Texture ����Ʈ�� �߰�
            }
        }
    }

    // ���� �̹��� ������ ��ȯ
    vector<string> getImageOrder() const {
        return image; // ���� �̹��� ������ ��ȯ
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
            if (event.type == Event::Closed) {
                window.close();
            }
            else if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    Vector2i mousePos = Mouse::getPosition(window);
                    if (nextBtn.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        currentScreen = 3; // ȭ�� ��ȯ
                    }
                }
            }
        }
    }

    void render(RenderWindow& window) override {
        window.draw(orderTxt);
        window.draw(nextTxt);
        window.draw(nextBtn);

        // �̹��� ������
        for (const auto& sprite : imgList) {
            window.draw(sprite);
        }

        window.display();
    }

private:
    Text orderTxt, nextTxt, nextBtn;
    vector<std::string> image;     // �̹��� ��θ� ������ ����
    vector<Sprite> imgList;        // ��������Ʈ ����
    vector<Texture*> tList;        // Texture ������ ����
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
            if (event.type == Event::Closed) {
                window.close();
            }
            else if (event.type == Event::MouseButtonPressed) {
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
    MakeInOrder(const vector<string>& order) {
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

        correctOrder = order; // Order Ŭ�������� ���� �ùٸ� �̹��� ����

        int startX = 300; // ���� X ��ġ
        int startY = 470; // ���� Y ��ġ
        int spacing = 150; // ����

        // ���� �̹��� ��ο� ���� Texture�� Sprite ����
        for (size_t i = 0; i < correctOrder.size(); ++i) {
            Texture* texture = new Texture();
            if (texture->loadFromFile(correctOrder[i])) {
                Sprite sprite(*texture);
                sprite.setPosition(startX + (i * spacing), startY);
                imgList.push_back(sprite);
                tList.push_back(texture); // Texture ����Ʈ�� �߰�
            }
        }
    }

    ~MakeInOrder() {
        // �޸� ����
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
                        // Ŭ���� �̹����� �ε����� clickedOrder�� �߰�
                        clickedOrder.push_back(i);

                        // �ߺ��� Ŭ�� ����
                        imgList.erase(imgList.begin() + i);
                        tList.erase(tList.begin() + i);
                        break;
                    }
                }

                // Ŭ�� ������ ��� ���߾��� ��� üũ
                if (clickedOrder.size() == correctOrder.size()) {
                    bool isCorrect = true;
                    for (size_t j = 0; j < correctOrder.size(); ++j) {
                        // Ŭ���� �̹����� �ε����� �̿��Ͽ� correctOrder���� �ش� �̹��� ��� ��������
                        std::string clickedImagePath = correctOrder[clickedOrder[j]];

                        // Ŭ���� �̹��� ��ο� �ùٸ� ������ �̹��� ��� ��
                        if (clickedImagePath != correctOrder[j]) {
                            isCorrect = false;
                            break;
                        }
                    }

                    if (isCorrect) {
                        currentScreen = 5; // ���� ȭ������ �̵�
                    }
                    else {
                        currentScreen = 6; // ���� ȭ������ �̵�
                    }
                }
            }

        }

        // Ÿ�̸� �ʱ�ȭ: ������ ���۵� ���� ȣ��
        static bool timerStarted = false;
        if (!timerStarted) {
            clock.restart(); // Ÿ�̸Ӹ� ���� ����
            timerStarted = true;
        }

        // Ÿ�̸� �ʰ� ó��
        float elapsedTime = clock.getElapsedTime().asSeconds();
        if (elapsedTime >= 30) {
            currentScreen = 6; // ���� ȭ������ �̵�
        }
    }

    void render(RenderWindow& window) override {
        window.draw(timeTxt);

        // ���� �ð� ��� �� ǥ��
        float elapsedTime = clock.getElapsedTime().asSeconds();
        int remainingTime = max(0, 30 - static_cast<int>(elapsedTime));
        timer.setString(L"���� �ð�: " + std::to_wstring(remainingTime) + L"��");
        window.draw(timer);

        // ���� ��ġ�� ��ġ�� �̹��� �׸���
        for (const auto& sprite : imgList) {
            window.draw(sprite);
        }

        window.display();
    }

private:
    vector<string> correctOrder; // �ùٸ� �̹��� ����
    vector<int> clickedOrder;    // ����ڰ� Ŭ���� ����
    vector<Sprite> imgList;      // �̹��� ��������Ʈ ����Ʈ
    vector<Texture*> tList;      // Texture ������ ����Ʈ
    Clock clock;                 // Ÿ�̸�
    Text timeTxt, timer;         // �ؽ�Ʈ ��ü
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

        crackStage = 0; // �ʱ� �ܰ�
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
        // �⺻ �̹��� �׸���
        window.draw(baseSprite);

        // ���� �� �̹��� �ܰ躰�� �׸���
        for (int i = 0; i < crackStage; i++) {
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
    Texture crackedImgs[3];
    Sprite baseSprite;
    Sprite crackSprites[3];
    Vector2f crackedPositions[3];
    int crackStage;
    
    Text successText, clickText, checkText; // �߰� �ؽ�Ʈ
    bool checkVisible; // ���ο� ���� ǥ�� ����
};


// 7. ������Ű ����� ���� Ŭ����
class Fail : public Screen {
public:
    Fail() {
        // �̹���
        img.loadFromFile("fail_fortune.png");
        failSprite.setTexture(img);
        failSprite.setPosition(434, 200);

        // "Fortune Cookie" �ؽ�Ʈ
        failText.setFont(font);
        failText.setString(L"������Ű ����� ���� ��.��");
        failText.setCharacterSize(50);
        failText.setFillColor(Yellow);
        failText.setPosition(484, 179);

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
            if (event.type == Event::Closed) {
                window.close();
            }
            else if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    Vector2i mousePos = Mouse::getPosition(window);
                    if (nextBtn.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        currentScreen = 5; // ȭ�� ��ȯ
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

// ���� Ŭ����
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