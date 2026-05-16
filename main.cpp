#include <SFML/Graphics.hpp>
#include <sstream>
#include <string>

#include "array_sequence.hpp"
#include "bit_sequence.hpp"
#include "immutable_array_sequence.hpp"
#include "immutable_bit_sequence.hpp"
#include "immutable_list_sequence.hpp"
#include "list_sequence.hpp"

enum Screen
{
    TYPE_SCREEN,
    MODE_SCREEN,
    MENU_SCREEN,
    INPUT_SCREEN,
    RESULT_SCREEN
};
enum InputMode
{
    CREATE_COUNT,
    CREATE_ELEMENT,
    APPEND,
    PREPEND,
    INSERT_INDEX,
    INSERT_VALUE
};

class Button
{
   private:
    sf::RectangleShape shape;
    sf::Text text;

   public:
    Button(float x, float y, float w, float h, const std::string& str, sf::Font& font) : text(font)
    {
        shape.setPosition({x, y});
        shape.setSize({w, h});
        shape.setFillColor(sf::Color::White);
        shape.setOutlineThickness(2);
        shape.setOutlineColor(sf::Color(101, 67, 33));
        text.setString(str);
        text.setCharacterSize(22);
        text.setFillColor(sf::Color::Black);
        sf::FloatRect b = text.getLocalBounds();
        text.setPosition({x + w / 2 - b.size.x / 2, y + h / 2 - b.size.y / 2 - 5});
    }

    void setText(const std::string& str)
    {
        text.setString(str);
        sf::FloatRect b = text.getLocalBounds();
        text.setPosition({shape.getPosition().x + shape.getSize().x / 2 - b.size.x / 2,
                          shape.getPosition().y + shape.getSize().y / 2 - b.size.y / 2 - 5});
    }

    bool clicked(sf::Vector2f m)
    {
        return shape.getGlobalBounds().contains(m);
    }
    void draw(sf::RenderWindow& w)
    {
        w.draw(shape);
        w.draw(text);
    }
};

std::string seqToStr(Sequence<int>& s, bool list)
{
    if (s.GetLength() == 0) return "empty";
    std::ostringstream ss;
    for (size_t i = 0; i < s.GetLength(); i++)
    {
        ss << s.Get(i);
        if (i + 1 < s.GetLength()) ss << (list ? " -> " : ", ");
    }
    return ss.str();
}

std::string bitToStr(Sequence<Bit<unsigned char>>& s)
{
    if (s.GetLength() == 0) return "empty";
    std::ostringstream ss;
    for (size_t i = 0; i < s.GetLength(); i++)
    {
        ss << static_cast<bool>(s.Get(i));
        if (i + 1 < s.GetLength()) ss << ", ";
    }
    return ss.str();
}

int main()
{
    sf::RenderWindow window(sf::VideoMode({900, 650}), "LABA 2");
    sf::Font font;
    if (!font.openFromFile("arial.ttf")) return 1;

    Screen screen = TYPE_SCREEN;
    size_t containerType = 0;
    bool immutable = false;
    InputMode inputMode = CREATE_COUNT;
    std::string input, result;
    Sequence<int>* seq = nullptr;
    Sequence<Bit<unsigned char>>* bitSeq = nullptr;
    size_t createCount = 0, createIndex = 0, insertIndex = 0;

    sf::Text title(font);
    title.setCharacterSize(30);
    title.setFillColor(sf::Color(101, 67, 33));

    Button btn1(250, 120, 400, 55, "", font), btn2(250, 185, 400, 55, "", font),
        btn3(250, 250, 400, 55, "", font), btn4(250, 315, 400, 55, "", font),
        btn5(250, 380, 400, 55, "", font), backBtn(320, 520, 260, 50, "BACK", font);

    sf::Text output(font);
    output.setCharacterSize(24);
    output.setFillColor(sf::Color::Black);
    output.setPosition({60, 200});

    sf::Text inputText(font);
    inputText.setCharacterSize(28);
    inputText.setFillColor(sf::Color::Black);
    inputText.setPosition({250, 280});

    sf::Text hint(font);
    hint.setCharacterSize(20);
    hint.setFillColor(sf::Color(120, 70, 70));
    hint.setPosition({180, 360});

    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()) window.close();

            if (screen == INPUT_SCREEN && event->is<sf::Event::TextEntered>())
            {
                auto* t = event->getIf<sf::Event::TextEntered>();
                if (t->unicode == '\b' && !input.empty())
                    input.pop_back();
                else if (t->unicode == '\r' && !input.empty())
                {
                    try
                    {
                        int val = std::stoi(input);
                        input.clear();
                        bool isBit = (containerType == 3);

                        if (isBit && inputMode != CREATE_COUNT && inputMode != INSERT_INDEX &&
                            (val < 0 || val > 1))
                        {
                            result = "Error: bit must be 0 or 1";
                            screen = RESULT_SCREEN;
                            continue;
                        }

                        if (inputMode == CREATE_COUNT)
                        {
                            if (val < 0 || val > 100)
                            {
                                result = "Error: 0-100";
                                screen = RESULT_SCREEN;
                            }
                            else
                            {
                                createCount = val;
                                createIndex = 0;
                                delete seq;
                                delete bitSeq;
                                seq = nullptr;
                                bitSeq = nullptr;
                                if (containerType == 1)
                                    seq = immutable
                                              ? (Sequence<int>*)new ImmutableArraySequence<int>()
                                              : new ArraySequence<int>();
                                else if (containerType == 2)
                                    seq = immutable
                                              ? (Sequence<int>*)new ImmutableListSequence<int>()
                                              : new ListSequence<int>();
                                else if (containerType == 3)
                                    bitSeq =
                                        immutable
                                            ? (Sequence<
                                                  Bit<unsigned char>>*)new ImmutableBitSequence<>()
                                            : new BitSequence<>();
                                if (createCount == 0)
                                {
                                    result = "Empty created";
                                    screen = RESULT_SCREEN;
                                }
                                else
                                    inputMode = CREATE_ELEMENT;
                            }
                        }
                        else if (inputMode == CREATE_ELEMENT)
                        {
                            if (isBit)
                            {
                                Bit<unsigned char> b(val);
                                if (immutable)
                                {
                                    auto n = bitSeq->Append(b);
                                    delete bitSeq;
                                    bitSeq = n;
                                }
                                else
                                    bitSeq->Append(b);
                            }
                            else
                            {
                                if (immutable)
                                {
                                    auto n = seq->Append(val);
                                    delete seq;
                                    seq = n;
                                }
                                else
                                    seq->Append(val);
                            }
                            if (++createIndex >= createCount)
                            {
                                result = "Created: " + (isBit ? bitToStr(*bitSeq)
                                                              : seqToStr(*seq, containerType == 2));
                                screen = RESULT_SCREEN;
                            }
                        }
                        else if (inputMode == APPEND)
                        {
                            if (isBit)
                            {
                                Bit<unsigned char> b(val);
                                if (immutable)
                                {
                                    auto n = bitSeq->Append(b);
                                    delete bitSeq;
                                    bitSeq = n;
                                }
                                else
                                    bitSeq->Append(b);
                                result =
                                    "Appended: " + std::to_string(val) + "\n" + bitToStr(*bitSeq);
                            }
                            else
                            {
                                if (immutable)
                                {
                                    auto n = seq->Append(val);
                                    delete seq;
                                    seq = n;
                                }
                                else
                                    seq->Append(val);
                                result = "Appended: " + std::to_string(val) + "\n" +
                                         seqToStr(*seq, containerType == 2);
                            }
                            screen = RESULT_SCREEN;
                        }
                        else if (inputMode == PREPEND)
                        {
                            if (isBit)
                            {
                                Bit<unsigned char> b(val);
                                if (immutable)
                                {
                                    auto n = bitSeq->Prepend(b);
                                    delete bitSeq;
                                    bitSeq = n;
                                }
                                else
                                    bitSeq->Prepend(b);
                                result =
                                    "Prepended: " + std::to_string(val) + "\n" + bitToStr(*bitSeq);
                            }
                            else
                            {
                                if (immutable)
                                {
                                    auto n = seq->Prepend(val);
                                    delete seq;
                                    seq = n;
                                }
                                else
                                    seq->Prepend(val);
                                result = "Prepended: " + std::to_string(val) + "\n" +
                                         seqToStr(*seq, containerType == 2);
                            }
                            screen = RESULT_SCREEN;
                        }
                        else if (inputMode == INSERT_INDEX)
                        {
                            size_t len = isBit ? (bitSeq ? bitSeq->GetLength() : 0)
                                               : (seq ? seq->GetLength() : 0);
                            if (val < 0 || val > (int)len)
                            {
                                result = "Error: bad index";
                                screen = RESULT_SCREEN;
                            }
                            else
                            {
                                insertIndex = val;
                                inputMode = INSERT_VALUE;
                            }
                        }
                        else if (inputMode == INSERT_VALUE)
                        {
                            if (isBit)
                            {
                                Bit<unsigned char> b(val);
                                if (immutable)
                                {
                                    auto n = bitSeq->InsertAt(b, insertIndex);
                                    delete bitSeq;
                                    bitSeq = n;
                                }
                                else
                                    bitSeq->InsertAt(b, insertIndex);
                                result = "Inserted at " + std::to_string(insertIndex) + "\n" +
                                         bitToStr(*bitSeq);
                            }
                            else
                            {
                                if (immutable)
                                {
                                    auto n = seq->InsertAt(val, insertIndex);
                                    delete seq;
                                    seq = n;
                                }
                                else
                                    seq->InsertAt(val, insertIndex);
                                result = "Inserted " + std::to_string(val) + " at " +
                                         std::to_string(insertIndex) + "\n" +
                                         seqToStr(*seq, containerType == 2);
                            }
                            screen = RESULT_SCREEN;
                        }
                    }
                    catch (const std::exception&)
                    {
                        result = "Error: invalid input";
                        screen = RESULT_SCREEN;
                    }
                }
                else if ((t->unicode >= '0' && t->unicode <= '9') || t->unicode == '-')
                    input += static_cast<char>(t->unicode);
            }

            if (auto* m = event->getIf<sf::Event::MouseButtonPressed>())
            {
                sf::Vector2f p = window.mapPixelToCoords(m->position);
                if (screen == TYPE_SCREEN)
                {
                    if (btn1.clicked(p))
                    {
                        containerType = 1;
                        screen = MODE_SCREEN;
                    }
                    if (btn2.clicked(p))
                    {
                        containerType = 2;
                        screen = MODE_SCREEN;
                    }
                    if (btn3.clicked(p))
                    {
                        containerType = 3;
                        screen = MODE_SCREEN;
                    }
                }
                else if (screen == MODE_SCREEN)
                {
                    if (btn1.clicked(p))
                    {
                        immutable = false;
                        screen = MENU_SCREEN;
                    }
                    if (btn2.clicked(p))
                    {
                        immutable = true;
                        screen = MENU_SCREEN;
                    }
                    if (backBtn.clicked(p)) screen = TYPE_SCREEN;
                }
                else if (screen == MENU_SCREEN)
                {
                    bool has = (containerType == 3) ? (bitSeq != nullptr) : (seq != nullptr);
                    if (btn1.clicked(p))
                    {
                        inputMode = CREATE_COUNT;
                        input.clear();
                        screen = INPUT_SCREEN;
                    }
                    if (btn2.clicked(p) && has)
                    {
                        inputMode = APPEND;
                        input.clear();
                        screen = INPUT_SCREEN;
                    }
                    if (btn3.clicked(p) && has)
                    {
                        inputMode = PREPEND;
                        input.clear();
                        screen = INPUT_SCREEN;
                    }
                    if (btn4.clicked(p) && has)
                    {
                        inputMode = INSERT_INDEX;
                        input.clear();
                        screen = INPUT_SCREEN;
                    }
                    if (btn5.clicked(p) && has)
                    {
                        if (containerType == 3)
                            result = "BitSeq:\n" + bitToStr(*bitSeq) +
                                     "\n\nLen: " + std::to_string(bitSeq->GetLength());
                        else
                            result = "Container:\n" + seqToStr(*seq, containerType == 2) +
                                     "\n\nLen: " + std::to_string(seq->GetLength()) +
                                     "\nFirst: " + std::to_string(seq->GetFirst()) +
                                     "\nLast: " + std::to_string(seq->GetLast());
                        screen = RESULT_SCREEN;
                    }
                    if (backBtn.clicked(p)) screen = MODE_SCREEN;
                }
                else if (screen == RESULT_SCREEN)
                {
                    if (backBtn.clicked(p)) screen = MENU_SCREEN;
                }
            }
        }

        window.clear(sf::Color(255, 228, 225));
        sf::FloatRect tb = title.getLocalBounds();
        title.setPosition({450 - tb.size.x / 2, 40});

        if (screen == TYPE_SCREEN)
        {
            title.setString("CHOOSE TYPE");
            btn1.setText("Array");
            btn2.setText("List");
            btn3.setText("Bit Sequence");
            btn1.draw(window);
            btn2.draw(window);
            btn3.draw(window);
        }
        else if (screen == MODE_SCREEN)
        {
            title.setString("CHOOSE MODE");
            btn1.setText("Mutable");
            btn2.setText("Immutable");
            btn1.draw(window);
            btn2.draw(window);
            backBtn.draw(window);
        }
        else if (screen == MENU_SCREEN)
        {
            title.setString("OPERATIONS");
            btn1.setText("Create");
            btn2.setText("Append");
            btn3.setText("Prepend");
            btn4.setText("Insert At");
            btn5.setText("Print");
            btn1.draw(window);
            btn2.draw(window);
            btn3.draw(window);
            btn4.draw(window);
            btn5.draw(window);
            backBtn.draw(window);
        }
        else if (screen == INPUT_SCREEN)
        {
            title.setString("INPUT");
            if (inputMode == CREATE_COUNT)
                hint.setString("Count (0-100):");
            else if (inputMode == CREATE_ELEMENT)
                hint.setString("Elem " + std::to_string(createIndex + 1) + "/" +
                               std::to_string(createCount));
            else if (inputMode == APPEND)
                hint.setString(containerType == 3 ? "Bit (0/1):" : "Value:");
            else if (inputMode == PREPEND)
                hint.setString(containerType == 3 ? "Bit (0/1):" : "Value:");
            else if (inputMode == INSERT_INDEX)
            {
                size_t len = (containerType == 3) ? (bitSeq ? bitSeq->GetLength() : 0)
                                                  : (seq ? seq->GetLength() : 0);
                hint.setString("Index (0-" + std::to_string(len) + "):");
            }
            else if (inputMode == INSERT_VALUE)
                hint.setString("Value at " + std::to_string(insertIndex) + ":");
            inputText.setString("> " + input + "_");
            window.draw(inputText);
            window.draw(hint);
        }
        else if (screen == RESULT_SCREEN)
        {
            title.setString("RESULT");
            output.setString(result);
            window.draw(output);
            backBtn.draw(window);
        }

        window.draw(title);
        window.display();
    }

    delete seq;
    delete bitSeq;
    return 0;
}