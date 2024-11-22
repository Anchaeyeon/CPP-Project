#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    // 창 생성
    sf::RenderWindow window(sf::VideoMode(1440, 1024), "Fortune Cookie");

    sf::Color Green(0, 145, 50);
    sf::Color Yellow(252, 171, 64);

    sf::Texture img;
    img.loadFromFile("start_cookie.png");

    // 스프라이트 생성
    sf::Sprite sprite(img);
    sprite.setPosition(649, 279);

    // 폰트
    sf::Font font;
    font.loadFromFile("Pretendard-Bold.otf");

    // 텍스트
    sf::Text text_f;
    text_f.setFont(font); // 폰트 설정
    text_f.setString("Fortune Cookie");
    text_f.setCharacterSize(100); // 글씨 크기
    text_f.setFillColor(Yellow);
    text_f.setPosition(360, 452); // 위치

    sf::Text text_start;
    text_start.setFont(font); // 폰트 설정
    text_start.setString(L"시작하기");
    text_start.setCharacterSize(43); // 글씨 크기
    text_start.setFillColor(Yellow);
    text_start.setPosition(645, 602); // 위치

    // 메인 루프
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // 창 닫기
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(Green);
        window.draw(sprite);
        window.draw(text_f);
        window.draw(text_start);

        // 화면 출력
        window.display();
    }

    return 0;
}