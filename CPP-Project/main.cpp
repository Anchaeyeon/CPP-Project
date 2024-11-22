#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    // â ����
    sf::RenderWindow window(sf::VideoMode(1440, 1024), "Fortune Cookie");

    sf::Color Green(0, 145, 50);
    sf::Color Yellow(252, 171, 64);

    sf::Texture img;
    img.loadFromFile("start_cookie.png");

    // ��������Ʈ ����
    sf::Sprite sprite(img);
    sprite.setPosition(649, 279);

    // ��Ʈ
    sf::Font font;
    font.loadFromFile("Pretendard-Bold.otf");

    // �ؽ�Ʈ
    sf::Text text_f;
    text_f.setFont(font); // ��Ʈ ����
    text_f.setString("Fortune Cookie");
    text_f.setCharacterSize(100); // �۾� ũ��
    text_f.setFillColor(Yellow);
    text_f.setPosition(360, 452); // ��ġ

    sf::Text text_start;
    text_start.setFont(font); // ��Ʈ ����
    text_start.setString(L"�����ϱ�");
    text_start.setCharacterSize(43); // �۾� ũ��
    text_start.setFillColor(Yellow);
    text_start.setPosition(645, 602); // ��ġ

    // ���� ����
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // â �ݱ�
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(Green);
        window.draw(sprite);
        window.draw(text_f);
        window.draw(text_start);

        // ȭ�� ���
        window.display();
    }

    return 0;
}