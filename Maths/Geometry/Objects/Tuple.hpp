//
// Created by CASALE Benjamin on 06/10/2021.
//

#ifndef GEOMETRY_TUPLE_HPP
#define GEOMETRY_TUPLE_HPP

#include <ostream>
namespace Geometry {
    template<typename T>
    class Tuple {
        /**
         * Class that reprenst a pair of element of a template type that can't be modified.
         * Element must be of the same type
         */
    public:
        /**
         * Default constructor, create an empty tuple
         */
        Tuple<T>();

        /**
         * Copy constructor
         * @param ToCopy Tuple to copy
         */
        Tuple<T>(const Tuple<T> &ToCopy);

        /**
         * Constructor with two element given
         * @param F First element
         * @param S Second element
         */
        Tuple<T>(const T &F, const T &S);

        /**
         * First element's getter
         * @return Tuple's first element
         */
        [[nodiscard]] inline T First() const { return first; };

        /**
         * Second element's getter
         * @return Tuple's second  element
         */
        [[nodiscard]] inline T Second() const { return second; };

        /**
         * Overload of << in order to use std::cout
         * @tparam U Type of element inside the tuple
         * @param os stream
         * @param tuple Tuple to show
         * @return stream with tuple's information
         */
        template<class U>
        friend std::ostream &operator<<(std::ostream &os, const Tuple<U> &tuple);

        /**
         * Assigmenet overload
         * @param RHS Tuple to assign
         * @return Assigned tuple
         */
        Tuple<T> &operator=(const Tuple<T> &RHS);;

    private:
        T first, second;
    };

    /*
     * Methods are basics, assig 2 element and read them if need.
     * */

    template<typename T>
    Tuple<T>::Tuple(const Tuple<T> &ToCopy) {
        this->first = ToCopy.First();
        this->second = ToCopy.Second();
    }

    template<typename T>
    Tuple<T>::Tuple(const T &F, const T &S) : first(F), second(S) {

    }

    template<typename T>
    Tuple<T>::Tuple() {
        first = static_cast<T>(0);
        second = static_cast<T>(0);
    }

    template<typename T>
    Tuple<T> &Tuple<T>::operator=(const Tuple<T> &RHS) {
        first = RHS.First();
        second = RHS.Second();
        return *this;
    }

    template<typename T>
    std::ostream &operator<<(std::ostream &os, const Tuple<T> &tuple) {
        os << "Tuple" << std::endl << "  First: " << tuple.first << std::endl << "  Second: " << tuple.second;
        return os;
    }
}
#endif //GEOMETRY_TUPLE_HPP
