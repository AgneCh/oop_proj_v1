/**
 * @file Student.h
 * @brief Apibrėžia Student klasę.
 *
 * Šiame faile pateikiama Student klasės deklaracija,
 * kuri paveldi duomenis iš Human klasės ir saugo informaciją
 * apie namų darbų ir egzamino balus bei galutinį balą.
 */
#pragma once
#include "Human.h"
#include <iostream>
#include <string>
#include <vector>
#include <list>

/**
 * @class Student
 * @brief Klasė skirta studento duomenims saugoti ir valdyti.
 *
 * Ši klasė paveldi bazinius duomenis iš Human klasės (vardą, pavardę)
 * ir papildomai saugo namų darbų pažymius, egzamino rezultatą bei
 * galutinius balus (vidurkį ir medianą).
 */
class Student : public Human
{
private:
    std::vector<int> grades_;
    int exam_{0};
    double finalGradeMean_{0.0};
    double finalGradeMedian_{0.0};

    /**
     * @brief Nuskaito Student duomenis iš įvesties srauto.
     *
     * Leidžia užpildyti Student objektą skaitant duomenis
     * iš std::cin arba kito įvesties srauto.
     *
     * @param in Įvesties srautas.
     * @param s Student objektas, į kurį įrašomi duomenys.
     * @return Tas pats įvesties srautas po nuskaitymo.
     */
    friend std::istream &operator>>(std::istream &in, Student &s);

    /**
     * @brief Išveda Student duomenis į išvesties srautą.
     *
     * Leidžia atspausdinti studento informaciją naudojant
     * std::cout arba kitą išvesties srautą.
     *
     * @param out Išvesties srautas.
     * @param s Student objektas, kurio duomenys išvedami.
     * @return Tas pats išvesties srautas po išvedimo.
     */
    friend std::ostream &operator<<(std::ostream &out, const Student &s);

public:
    // Constructors
    /**
     * @brief Sukuria tuščią Student objektą.
     *
     * Inicializuoja Student objektą be jokių pradinių duomenų.
     */
    Student() = default;

    /**
     * @brief Sukuria Student objektą su nurodytu vardu ir pavarde.
     * @param firstN Student vardas.
     * @param lastN Student pavardė.
     */
    Student(std::string firstN, std::string lastN) : Human(std::move(firstN), std::move(lastN)) {}

    // Copy constructor
    /**
     * @brief Sukuria naują Student objektą kopijuojant kitą Student.
     * @param other Objektas iš kurio kopijuojami duomenys.
     */
    Student(const Student &other) : Human(other.firstName_, other.lastName_),
                                    grades_(other.grades_),
                                    exam_(other.exam_),
                                    finalGradeMean_(other.finalGradeMean_),
                                    finalGradeMedian_(other.finalGradeMedian_)
    {
        // std::cout << "Copy constructor is called\n";
    }

    // Copy assigment operator
    /**
     * @brief Priskiria kitą Student objektą šiam objektui.
     *
     * Patikrina ar nepriskiriama sau pačiam ir
     * attnaujina dabartinio objekto laukus pagal other objekto reikšmes.
     *
     * @param other Student objektas, iš kurio kopijuojami duomenys.
     * @return Nuoroda į dabartinį objektą po priskyrimo.
     */
    Student &operator=(const Student &other)
    {
        if (this != &other)
        {
            firstName_ = other.firstName_;
            lastName_ = other.lastName_;
            grades_ = other.grades_;
            exam_ = other.exam_;
            finalGradeMean_ = other.finalGradeMean_;
            finalGradeMedian_ = other.finalGradeMedian_;
        }
        // std::cout << "Copy assigment operator is called\n";
        return *this;
    }

    // Getters
    /**
     * @brief Grąžina studento vardą.
     * @return Student vardas.
     */
    const std::string &firstName() const override { return firstName_; }

    /**
     * @brief Grąžina studento pavardę.
     * @return Student pavardė.
     */
    const std::string &lastName() const override { return lastName_; }

    /**
     * @brief Grąžina visus namų darbų balus.
     * @return Vektorių su studento namų darbų balais.
     */
    const std::vector<int> &grades() const { return grades_; }

    /**
     * @brief Grąžina egzamino rezultatą.
     * @return Egzamino balas.
     */
    int exam() const { return exam_; }

    /**
     * @brief Grąžina galutinį balą, apskaičiuotą pagal vidurkį.
     * @return Galutinio balo reikšmė (vidurkis).
     */
    double finalMean() const { return finalGradeMean_; }

    /**
     * @brief Grąžina galutinį balą, apskaičiuotą pagal medianą.
     * @return Galutinio balo reikšmė (mediana).
     */
    double finalMedian() const { return finalGradeMedian_; }

    // Setters
    /**
     * @brief Nustato studento vardą.
     * @param v Naujas vardas.
     */
    void setFirstName(std::string v) override { firstName_ = std::move(v); }

    /**
     * @brief Nustato studento pavardę.
     * @param v Nauja pavardė.
     */
    void setLastName(std::string v) override { lastName_ = std::move(v); }

    /**
     * @brief Prideda naują balą prie studento namų darbų balų sąrašo.
     * @param g Balo reikšmė.
     */
    void addGrade(int g) { grades_.push_back(g); }

    /**
     * @brief Nustato egzamino rezultatą.
     * @param e Egzamino balas.
     */
    void setExam(int e) { exam_ = e; }

    /**
     * @brief Nustato galutinį balą, apskaičiuotą pagal vidurkį.
     * @param v Galutinio balo reikšmė.
     */
    void setFinalMean(double v) { finalGradeMean_ = v; }

    /**
     * @brief Nustato galutinį balą, apskaičiuotą pagal medianą.
     * @param v Galutinio balo reikšmė.
     */
    void setFinalMedian(double v) { finalGradeMedian_ = v; }

    /**
     * @brief Pašalina vardo, pavardės ir pažymių reikšmes iš objekto prieš jo sunaikinimą.
     */
    ~Student()
    {
        firstName_.clear();
        lastName_.clear();
        grades_.clear();
        // std::cout << "Student object destroyed \n";
    }
};

#ifdef USE_LIST
using StudentContainer = std::list<Student>;
inline const char *getContainerName()
{
    return "std::list<Student>";
}
#else
using StudentContainer = std::vector<Student>;
inline const char *getContainerName()
{
    return "std::vector<Student>";
}
#endif