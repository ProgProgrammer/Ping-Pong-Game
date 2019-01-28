#pragma once
#include <SFML/Graphics.hpp>
#include "ServerPackage.h"
#include <sstream>
 
// TODO make ISetting buildable
/*
class ISetting
{
public:
    virtual ~ISetting() = default;
    virtual std::string getName() const = 0;
    virtual std::string getStrValue() const = 0;
    virtual void next() = 0;
    virtual void prev() = 0;
};

template<typename  T>
class Setting2<T> : public ISetting
{
    std::string name;
    T & ref;
    std::vector<T> possibleValues;
    unsigned currentPos = 0;

public:
    Setting2<T>(std::string name, T & ref, std::vector<T> possibleValues = {})
        : name(name), ref(ref), possibleValues(possibleValues)
    {
        if(!possibleValues.empty())
        {
            if(possibleValues[0] != ref)
            {
                std::stringstream ss;
                ss << "Init value for setting: '" << name << "'(" << ref << ")"
                    << " doesn't equle first possible value " << possibleValues[0];
                throw std::logic_error(ss.str());
            }
        }
    }
    std::string getName() const override { return name; }
    std::string getStrValue() const override { return std::to_string(ref); }
    void next() override
    {
        if(possibleValues.empty())
        {
            ++ref;
            return;
        }
        else if(currentPos < possibleValues.size())
        {
            currentPos++;
        }
        else // currentPos >= possibleValues.size()
        {
            currentPos = 0;
        }

        ref = possibleValues[currentPos];
    }
    void prev() override
    {
        if(possibleValues.empty())
        {
            --ref;
            return;
        }
        else if(currentPos <= 0)
        {
            currentPos = possibleValues.size() - 1;
        }
        else // currentPos > 0
        {
            currentPos--;
        }

        ref = possibleValues[currentPos];
    }
};
*/
class PauseMessage
{
    ServerPackage serverPackage {};
    sf::Text pauseMessage;

    sf::Font font;
    sf::Text hudText;
    int currentSetting = 0;

    struct Setting
    {

        std::string name;
        float* value;
    };

    float perlinFrequency = 7.0f;
    float perlinFrequencyBase = 4.0f;
    std::vector<Setting> settings {};

public:
    PauseMessage();
    void userEvent(sf::Event event);
    void setFont(const sf::Font& font);
    void setServerPackage(const ServerPackage & sp) { this->serverPackage = sp; }
    void draw(sf::RenderWindow& window);

private:
    void drawContolInfromation(sf::RenderWindow& window);
};
