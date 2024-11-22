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
    sf::Text title_text;
    title_text.setFont(font); // 폰트 설정
    title_text.setString("Fortune Cookie");
    title_text.setCharacterSize(100); // 글씨 크기
    title_text.setFillColor(Yellow);
    title_text.setPosition(360, 452); // 위치

    sf::Text start_btn;
    start_btn.setFont(font); // 폰트 설정
    start_btn.setString(L"시작하기");
    start_btn.setCharacterSize(43); // 글씨 크기
    start_btn.setFillColor(Yellow);
    start_btn.setPosition(645, 602); // 위치

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
        window.draw(title_text);
        window.draw(start_btn);

        // 화면 출력
        window.display();
    }

    return 0;
}