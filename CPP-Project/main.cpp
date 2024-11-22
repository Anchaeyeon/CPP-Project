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
    sf::Text title_text;
    title_text.setFont(font); // ��Ʈ ����
    title_text.setString("Fortune Cookie");
    title_text.setCharacterSize(100); // �۾� ũ��
    title_text.setFillColor(Yellow);
    title_text.setPosition(360, 452); // ��ġ

    sf::Text start_btn;
    start_btn.setFont(font); // ��Ʈ ����
    start_btn.setString(L"�����ϱ�");
    start_btn.setCharacterSize(43); // �۾� ũ��
    start_btn.setFillColor(Yellow);
    start_btn.setPosition(645, 602); // ��ġ

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
        window.draw(title_text);
        window.draw(start_btn);

        // ȭ�� ���
        window.display();
    }

    return 0;
}