/**
 * @file Human.h
 * @brief Apibrėžia abstrakčią Human klasę.
 *
 * Šiame faile pateikiama bazinė abstrakti klasė, kuri saugo
 * žmogaus vardą ir pavardę bei nurodo bendrą sąsają klasėms,
 * paveldinčioms iš jos.
 */
#pragma once
#include <string>
#include <iostream>

/**
 * @class Human
 * @brief Abstrakti bazinė klasė žmogaus duomenims apibrėžti.
 *
 * Saugo vardą ir pavardę ir reikalauja, kad paveldinčios klasės
 * įgyvendintų getter ir setter metodus. Naudojama kaip pagrindas
 * Student klasei.
 */
class Human
{
protected:
    std::string firstName_;
    std::string lastName_;

public:
    /**
     * @brief Sukuria tuščią Human objektą.
     */
    Human() = default;

    /**
     * @brief Sukuria Human objektą su nurodytu vardu ir pavarde.
     * @param firstN Žmogaus vardas.
     * @param lastN Žmogaus pavardė.
     */
    Human(std::string firstN, std::string lastN) : firstName_(std::move(firstN)), lastName_(std::move(lastN)) {}

    /**
     * @brief Grąžina žmogaus vardą.
     * @return Nuoroda į vardo reikšmę.
     */
    virtual const std::string &firstName() const = 0;

    /**
     * @brief Grąžina žmogaus pavardę.
     * @return Nuoroda į pavardės reikšmę.
     */
    virtual const std::string &lastName() const = 0;

    /**
     * @brief Nustato žmogaus vardą.
     */
    virtual void setFirstName(std::string) = 0;

    /**
     * @brief Nustato žmogaus pavardę.
     */
    virtual void setLastName(std::string) = 0;

    /**
     * @brief Virtualus destruktorius bazinei klasei.
     */
    virtual ~Human()
    {
        // std::cout << "Human destructor called\n";
    }
};