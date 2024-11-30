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
        window.clear(Green);
        window.draw(nextBtn);

        for (int i = 0; i < 6; i++)
            window.draw(sarr[i]);

        for (int i = 0; i < 7; i++)
            window.draw(txtarr[i]);

        window.display();
    }

private:
    Text IngredientText, nextBtn;
    Text txtarr[7];
    Sprite sarr[6];
    Texture imgarr[6];
};

// 3. ������ �� ������ �����ִ� Ŭ����
class Order : public Screen {
public:
    Order() {
        // ���� �Ұ� �ؽ�Ʈ
        orderList.setFont(font);
        orderList.setString(L"< ����� ������ �� ������Ű ���� >");
        orderList.setCharacterSize(50);
        orderList.setFillColor(Yellow);
        orderList.setPosition(350, 159);

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

        // Ÿ�̸� ����
        clock.restart();
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
            else if (clock.getElapsedTime().asSeconds() > 30) { // 30�� ���
                currentScreen = 1; // ���� ȭ������ �̵�
            }
        }
    }

    void render(RenderWindow& window) override {
        window.clear(Green);
        window.draw(orderList);

        // �̹��� ������
        for (const auto& sprite : imgList) {
            window.draw(sprite);
        }

        window.display();
    }

private:
    Text orderList;
    std::vector<std::string> image;     // �̹��� ��θ� ������ ����
    std::vector<Sprite> imgList;        // ��������Ʈ ����
    std::vector<Texture*> tList;        // Texture ������ ����
    Clock clock;                        // �ð� ������ ���� SFML Clock
};


// ���� Ŭ����
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
