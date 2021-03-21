#include "sylee.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <iostream>
#include <list>

void set_text(int cursor, string str1, string str2, string str3);
void key_input(sf::Event event, int *mode);
void select_file(sf::Event event, int *mode, int *cursor,
                 list<string> filelist);
void get_file(list<string> filelist);

enum mode { OPEN, RUNNING, RESULT };

bool keycode[33] = {
    0,
};

sf::Texture texture;
sf::Sprite sprite;
sf::Text text1;
sf::Text text2;
sf::Text text3;
sf::Font font;

string str_full;
string str_fullfile;
string str_input;
string str_cur;
string str_next;
list<string> filelist;
list<string>::iterator itr;
list<string>::reverse_iterator ritr;

int line;
const char *name;

string temp;
int main() {
    sf::RenderWindow window(sf::VideoMode(880, 500),
                            "Project Keyboard Warrior");
    texture.loadFromFile("images/Keyboard.jpeg");

    int mode = OPEN;
    int cursor = 0;

    if (!font.loadFromFile("arial.ttf")) {
        printf("font error\n");
    }
    text1.setFont(font);
    text1.setCharacterSize(24);
    text1.setFillColor(sf::Color::Black);
    text2.setFont(font);
    text2.setCharacterSize(24);
    text2.setFillColor(sf::Color::Black);
    text3.setFont(font);
    text3.setCharacterSize(24);
    text3.setFillColor(sf::Color::Black);
    sprite.setPosition(0, 250);

    read_ls(filelist);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (mode == OPEN) {
                select_file(event, &mode, &cursor, filelist);
                string str1;
                string str2;
                string str3;
                if (cursor == 0) {
                    itr = filelist.begin();
                    str1 = *itr;
                    itr++;
                    str2 = *itr;
                    itr++;
                    str3 = *itr;
                    set_text(1, str1, str2, str3);
                } else if (filelist.size() > 2 &&
                           cursor == filelist.size() - 1) {
                    ritr = filelist.rbegin();
                    str3 = *ritr;
                    ritr++;
                    str2 = *ritr;
                    ritr++;
                    str1 = *ritr;
                    set_text(3, str1, str2, str3);
                } else {
                    itr = filelist.begin();
                    for (int i = 1; i < cursor; i++)
                        itr++;
                    str1 = *itr;
                    itr++;
                    str2 = *itr;
                    itr++;
                    str3 = *itr;
                    set_text(2, str1, str2, str3);
                }
            } else if (mode == RUNNING) {
                key_input(event, &mode);
                set_text(cursor, str_cur, str_input, str_next);
            } else if (mode == RESULT) {
                if (event.type == sf::Event::KeyReleased)
                    texture.loadFromFile("images/Keyboard.jpeg");
                set_text(cursor, "Press BackSpace to return.", "", "");
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::BackSpace) {
                        mode = OPEN;
                        cursor = 0;
                        texture.loadFromFile("images/BACKSPACE.jpeg");
                    }
                }
            }
        }
        sprite.setTexture(texture);
        window.clear(sf::Color::White);
        window.draw(sprite);
        window.draw(text1);
        window.draw(text2);
        window.draw(text3);
        window.display();
    }
    return 0;
}

void set_text(int cursor, string str1, string str2, string str3) {
    text1.setStyle(sf::Text::Regular);
    text1.setPosition(400, 50);
    text2.setStyle(sf::Text::Regular);
    text2.setPosition(400, 100);
    text3.setStyle(sf::Text::Regular);
    text3.setPosition(400, 150);
    if (cursor == 1)
        text1.setStyle(sf::Text::Underlined);
    else if (cursor == 2)
        text2.setStyle(sf::Text::Underlined);
    else if (cursor == 3)
        text3.setStyle(sf::Text::Underlined);
    else {
        text1.setPosition(100, 50);
        text2.setPosition(100, 100);
        text3.setPosition(100, 150);
    }
    text1.setString(str1);
    text2.setString(str2);
    text3.setString(str3);
}

void key_input(sf::Event event, int *mode) {
    if (event.type == sf::Event::KeyPressed) {
        if (str_input.length() == str_cur.length() - 1 &&
            event.key.code != sf::Keyboard::BackSpace) {
            if (event.key.code == sf::Keyboard::Enter) {
                texture.loadFromFile("images/Enter.jpeg");
                str_full.append(str_input);
                str_fullfile.append(str_cur);
                str_fullfile.pop_back();
                if (str_next.empty()) {
                    *mode = RESULT;
                    strsnd(str_full, str_fullfile);
                    return;
                } else {
                    str_input.clear();
                    str_cur.clear();
                    str_next.clear();
                    readfile(name, str_cur, str_next, line++);
                    strsnd(str_full, str_fullfile);
                }
            }
        } else if (event.key.code == sf::Keyboard::A) {
            if (keycode[0] == 0)
                str_input.push_back('a');
            keycode[0] == 1;
            texture.loadFromFile("images/A.jpeg");
        } else if (event.key.code == sf::Keyboard::B) {
            if (keycode[1] == 0)
                str_input.push_back('b');
            keycode[1] == 1;
            texture.loadFromFile("images/B.jpeg");
        } else if (event.key.code == sf::Keyboard::C) {
            if (keycode[2] == 0)
                str_input.push_back('c');
            keycode[2] == 1;
            texture.loadFromFile("images/C.jpeg");
        } else if (event.key.code == sf::Keyboard::D) {
            if (keycode[3] == 0)
                str_input.push_back('d');
            keycode[3] == 1;
            texture.loadFromFile("images/D.jpeg");
        } else if (event.key.code == sf::Keyboard::E) {
            if (keycode[4] == 0)
                str_input.push_back('e');
            keycode[4] == 1;
            texture.loadFromFile("images/E.jpeg");
        } else if (event.key.code == sf::Keyboard::F) {
            if (keycode[5] == 0)
                str_input.push_back('f');
            keycode[5] == 1;
            texture.loadFromFile("images/F.jpeg");
        } else if (event.key.code == sf::Keyboard::G) {
            if (keycode[6] == 0)
                str_input.push_back('g');
            keycode[6] == 1;
            texture.loadFromFile("images/G.jpeg");
        } else if (event.key.code == sf::Keyboard::H) {
            if (keycode[7] == 0)
                str_input.push_back('h');
            keycode[7] == 1;
            texture.loadFromFile("images/H.jpeg");
        } else if (event.key.code == sf::Keyboard::I) {
            if (keycode[8] == 0)
                str_input.push_back('i');
            keycode[8] == 1;
            texture.loadFromFile("images/I.jpeg");
        } else if (event.key.code == sf::Keyboard::J) {
            if (keycode[9] == 0)
                str_input.push_back('j');
            keycode[9] == 1;
            texture.loadFromFile("images/J.jpeg");
        } else if (event.key.code == sf::Keyboard::K) {
            if (keycode[10] == 0)
                str_input.push_back('k');
            keycode[10] == 1;
            texture.loadFromFile("images/K.jpeg");
        } else if (event.key.code == sf::Keyboard::L) {
            if (keycode[11] == 0)
                str_input.push_back('l');
            keycode[11] == 1;
            texture.loadFromFile("images/L.jpeg");
        } else if (event.key.code == sf::Keyboard::M) {
            if (keycode[12] == 0)
                str_input.push_back('m');
            keycode[12] == 1;
            texture.loadFromFile("images/M.jpeg");
        } else if (event.key.code == sf::Keyboard::N) {
            if (keycode[13] == 0)
                str_input.push_back('n');
            keycode[13] == 1;
            texture.loadFromFile("images/N.jpeg");
        } else if (event.key.code == sf::Keyboard::O) {
            if (keycode[14] == 0)
                str_input.push_back('o');
            keycode[14] == 1;
            texture.loadFromFile("images/O.jpeg");
        } else if (event.key.code == sf::Keyboard::P) {
            if (keycode[15] == 0)
                str_input.push_back('p');
            keycode[15] == 1;
            texture.loadFromFile("images/P.jpeg");
        } else if (event.key.code == sf::Keyboard::Q) {
            if (keycode[16] == 0)
                str_input.push_back('q');
            keycode[16] == 1;
            texture.loadFromFile("images/Q.jpeg");
        } else if (event.key.code == sf::Keyboard::R) {
            if (keycode[17] == 0)
                str_input.push_back('r');
            keycode[17] == 1;
            texture.loadFromFile("images/R.jpeg");
        } else if (event.key.code == sf::Keyboard::S) {
            if (keycode[18] == 0)
                str_input.push_back('s');
            keycode[18] == 1;
            texture.loadFromFile("images/S.jpeg");
        } else if (event.key.code == sf::Keyboard::T) {
            if (keycode[19] == 0)
                str_input.push_back('t');
            keycode[19] == 1;
            texture.loadFromFile("images/T.jpeg");
        } else if (event.key.code == sf::Keyboard::U) {
            if (keycode[20] == 0)
                str_input.push_back('u');
            keycode[20] == 1;
            texture.loadFromFile("images/U.jpeg");
        } else if (event.key.code == sf::Keyboard::V) {
            if (keycode[21] == 0)
                str_input.push_back('v');
            keycode[21] == 1;
            texture.loadFromFile("images/V.jpeg");
        } else if (event.key.code == sf::Keyboard::W) {
            if (keycode[22] == 0)
                str_input.push_back('w');
            keycode[22] == 1;
            texture.loadFromFile("images/W.jpeg");
        } else if (event.key.code == sf::Keyboard::X) {
            if (keycode[23] == 0)
                str_input.push_back('x');
            keycode[23] == 1;
            texture.loadFromFile("images/X.jpeg");
        } else if (event.key.code == sf::Keyboard::Y) {
            if (keycode[24] == 0)
                str_input.push_back('y');
            keycode[24] == 1;
            texture.loadFromFile("images/Y.jpeg");
        } else if (event.key.code == sf::Keyboard::Z) {
            if (keycode[25] == 0)
                str_input.push_back('z');
            keycode[25] == 1;
            texture.loadFromFile("images/Z.jpeg");
        } else if (event.key.code == sf::Keyboard::Space) {
            if (keycode[26] == 0)
                str_input.push_back(' ');
            keycode[26] == 1;
            texture.loadFromFile("images/SPACE.jpeg");
        } else if (event.key.code == sf::Keyboard::BackSpace) {
            if (keycode[27] == 0) {
                if (!str_input.empty())
                    str_input.pop_back();
            }
            keycode[27] = 1;
            texture.loadFromFile("images/BACKSPACE.jpeg");
        } else if (event.key.code == sf::Keyboard::Period) {
            if (keycode[28] == 0)
                str_input.push_back('.');
            keycode[28] == 1;
            texture.loadFromFile("images/PERIOD.jpeg");
        } else if (event.key.code == sf::Keyboard::Comma) {
            if (keycode[29] == 0)
                str_input.push_back(',');
            keycode[29] == 1;
            texture.loadFromFile("images/COMMA.jpeg");
        }
    } else if (event.type == sf::Event::KeyReleased) {
        if (event.key.code == sf::Keyboard::A) {
            keycode[0] = 0;
        } else if (event.key.code == sf::Keyboard::B) {
            keycode[1] = 0;
        } else if (event.key.code == sf::Keyboard::C) {
            keycode[2] = 0;
        } else if (event.key.code == sf::Keyboard::D) {
            keycode[3] = 0;
        } else if (event.key.code == sf::Keyboard::E) {
            keycode[4] = 0;
        } else if (event.key.code == sf::Keyboard::F) {
            keycode[5] = 0;
        } else if (event.key.code == sf::Keyboard::G) {
            keycode[6] = 0;
        } else if (event.key.code == sf::Keyboard::H) {
            keycode[7] = 0;
        } else if (event.key.code == sf::Keyboard::I) {
            keycode[8] = 0;
        } else if (event.key.code == sf::Keyboard::J) {
            keycode[9] = 0;
        } else if (event.key.code == sf::Keyboard::K) {
            keycode[10] = 0;
        } else if (event.key.code == sf::Keyboard::L) {
            keycode[11] = 0;
        } else if (event.key.code == sf::Keyboard::M) {
            keycode[12] = 0;
        } else if (event.key.code == sf::Keyboard::N) {
            keycode[13] = 0;
        } else if (event.key.code == sf::Keyboard::O) {
            keycode[14] = 0;
        } else if (event.key.code == sf::Keyboard::P) {
            keycode[15] = 0;
        } else if (event.key.code == sf::Keyboard::Q) {
            keycode[16] = 0;
        } else if (event.key.code == sf::Keyboard::R) {
            keycode[17] = 0;
        } else if (event.key.code == sf::Keyboard::S) {
            keycode[18] = 0;
        } else if (event.key.code == sf::Keyboard::T) {
            keycode[19] = 0;
        } else if (event.key.code == sf::Keyboard::U) {
            keycode[20] = 0;
        } else if (event.key.code == sf::Keyboard::V) {
            keycode[21] = 0;
        } else if (event.key.code == sf::Keyboard::W) {
            keycode[22] = 0;
        } else if (event.key.code == sf::Keyboard::X) {
            keycode[23] = 0;
        } else if (event.key.code == sf::Keyboard::Y) {
            keycode[24] = 0;
        } else if (event.key.code == sf::Keyboard::Z) {
            keycode[25] = 0;
        } else if (event.key.code == sf::Keyboard::Space) {
            keycode[26] = 0;
        } else if (event.key.code == sf::Keyboard::BackSpace) {
            keycode[27] = 0;
        } else if (event.key.code == sf::Keyboard::Period) {
            keycode[28] = 0;
        } else if (event.key.code == sf::Keyboard::Comma) {
            keycode[29] = 0;
        }
        texture.loadFromFile("images/Keyboard.jpeg");
    }
}

void select_file(sf::Event event, int *mode, int *cursor,
                 list<string> filelist) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Enter) {
            if (keycode[30] == 0) {
                *mode = RUNNING;
                line = 0;
                itr = filelist.begin();
                for (int i = 0; i < *cursor; i++)
                    itr++;
                temp = "./Practices/";
                temp.append(*itr);
                name = (temp).c_str();
                *cursor = -1;
                str_full.clear();
                str_fullfile.clear();
                str_input.clear();
                str_cur.clear();
                str_next.clear();
                readfile(name, str_cur, str_next, line++);
            }
            keycode[30] = 1;
            texture.loadFromFile("images/Enter.jpeg");
        } else if (event.key.code == sf::Keyboard::Up) {
            if (keycode[31] == 0)
                if (*cursor > 0)
                    *cursor = *cursor - 1;
            keycode[31] = 1;
            texture.loadFromFile("images/UP.jpeg");
        } else if (event.key.code == sf::Keyboard::Down) {
            if (keycode[32] == 0)
                if (*cursor < filelist.size() - 1)
                    *cursor = *cursor + 1;
            keycode[32] = 1;
            texture.loadFromFile("images/DOWN.jpeg");
        }
    }
    if (event.type == sf::Event::KeyReleased) {
        texture.loadFromFile("images/Keyboard.jpeg");
        if (event.key.code == sf::Keyboard::Enter) {
            keycode[30] = 0;
        } else if (event.key.code == sf::Keyboard::Up) {
            keycode[31] = 0;
        } else if (event.key.code == sf::Keyboard::Down) {
            keycode[32] = 0;
        }
    }
}
