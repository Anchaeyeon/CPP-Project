#include <SFML/Graphics.hpp>
#include <iostream>

// �⺻ Screen Ŭ���� (���� ����)
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

// ���� Ŭ����
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
                        currentScreen = 1; // ȭ�� ��ȯ
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

// ��� �Ұ� Ŭ����
class IngredientIntro : public Screen {
public:
    IngredientIntro() {
        // �̹���
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

        // "< ��� �Ұ� Time >" �ؽ�Ʈ
        IngredientText.setFont(font);
        IngredientText.setString(L"< ��� �Ұ� Time >");
        IngredientText.setCharacterSize(50);
        IngredientText.setFillColor(Yellow);
        IngredientText.setPosition(519, 173);

        // �ڷº�
        flour.setFont(font);
        flour.setString(L"�ڷº�");
        flour.setCharacterSize(50);
        flour.setFillColor(Yellow);
        flour.setPosition(542, 324);

        // ����
        milk.setFont(font);
        milk.setString(L"����");
        milk.setCharacterSize(50);
        milk.setFillColor(Yellow);
        milk.setPosition(542, 396);

        // ���
        egg.setFont(font);
        egg.setString(L"���");
        egg.setCharacterSize(50);
        egg.setFillColor(Yellow);
        egg.setPosition(542, 468);

        // ����
        butter.setFont(font);
        butter.setString(L"����");
        butter.setCharacterSize(50);
        butter.setFillColor(Yellow);
        butter.setPosition(542, 540);

        // �����Ŀ��
        sugar.setFont(font);
        sugar.setString(L"�����Ŀ��");
        sugar.setCharacterSize(50);
        sugar.setFillColor(Yellow);
        sugar.setPosition(542, 612);

        // �ٴҶ����
        oil.setFont(font);
        oil.setString(L"�ٴҶ����");
        oil.setCharacterSize(50);
        oil.setFillColor(Yellow);
        oil.setPosition(542, 684);

        // ���ݸ�
        choco.setFont(font);
        choco.setString(L"���ݸ�");
        choco.setCharacterSize(50);
        choco.setFillColor(Yellow);
        choco.setPosition(542, 750);

        // �������� �Ѿ�� ��ư
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
                        currentScreen = 2; // ȭ�� ��ȯ
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

// ������ �� ������ �����ִ� Ŭ����
class Order : public Screen {
public:
    Order() {
        // ���� �Ұ� �ؽ�Ʈ
        orderList.setFont(font);
        orderList.setString(L"< ����� ������ �� ������Ű ���� >");
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

// ���� Ŭ����
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
