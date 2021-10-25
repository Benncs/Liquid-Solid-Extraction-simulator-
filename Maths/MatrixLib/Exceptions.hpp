//
// Created by Benjamin on 06/08/2021.
//

#ifndef MATH_EXCEPTIONS_HPP
#define MATH_EXCEPTIONS_HPP

#include <exception>
#include <string>
#include <utility>

class Exceptions : public std::exception {
public:
    explicit Exceptions(int numero=0, std::string  phrase="", int niveau=0) noexcept
            :m_numero(numero),m_phrase(std::move(phrase)),m_niveau(niveau)
    {}

    [[nodiscard]] const char* what() const noexcept override
    {
        return m_phrase.c_str();
    }

    [[nodiscard]] int getNiveau() const noexcept
    {
        return m_niveau;
    }

    ~Exceptions() noexcept override
    = default;

private:
    int m_numero;               //Numéro de l'erreur
    std::string m_phrase;            //Description de l'erreur
    int m_niveau;               //Niveau de l'erreur
};


#endif //MATH_EXCEPTIONS_HPP
