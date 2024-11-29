#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>

using namespace sf;

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
        imgarr[6].loadFromFile("choco.png");

        // �̹��� ��ġ
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

        txtarr[7].setString(L"���ݸ�");
        txtarr[7].setPosition(520, 750);

        for (int i = 0; i < 8; i++) {
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

        // �̹��� ���
        std::vector<std::string> imagePaths = { "flour.png", "sugar.png", "milk.png", "egg.png", "oil.png", "butter.png" };

        int startX = 300; // ���� X ��ġ
        int startY = 470; // ���� Y ��ġ
        int spacing = 150; // ����

        // �� �̹��� ��ο� ���� ���� Texture�� ����
        for (size_t i = 0; i < imagePaths.size(); ++i) {
            Texture* texture = new Texture();
            if (texture->loadFromFile(imagePaths[i])) {
                Sprite sprite(*texture);
                sprite.setPosition(startX + (i * spacing), startY); // ���η� ��ġ ����
                imageList.push_back(sprite);
                textureList.push_back(texture); // Texture ����Ʈ�� �߰�
            }
        }
    }

    ~Order() {
        // �޸� ����
        for (auto texture : textureList) {
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
    }

    void render(RenderWindow& window) override {
        window.clear(Green);
        window.draw(orderList);

        // �̹��� ������
        for (const auto& sprite : imageList) {
            window.draw(sprite);
        }

        window.display();
    }

private:
    Text orderList;
    std::vector<Sprite> imageList;
    std::vector<Texture*> textureList; // Texture ������ ����
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
