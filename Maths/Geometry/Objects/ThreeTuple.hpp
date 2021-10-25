//
// Created by CASALE Benjamin on 06/10/2021.
//

#ifndef GEOMETRY_THREETUPLE_HPP
#define GEOMETRY_THREETUPLE_HPP


namespace Geometry {

    template<typename T>
    class Tuple3 {
    public:
        Tuple3<T>();

        Tuple3<T>(const Tuple3<T> &ToCopy);

        Tuple3<T>(const T &F, const T &S, const T &Th);

        inline T First() const { return first; };

        inline T Second() const { return second; };

        inline T Third() const { return third; };


        template<class U>
        friend std::ostream &operator<<(std::ostream &os, const Tuple3<U> &tuple);

    private:
        T first, second, third;
    };

    template<typename T>
    Tuple3<T>::Tuple3(const T &F, const T &S, const T &Th) :first(F), second(S), third(Th) {

    }

    template<typename T>
    Tuple3<T>::Tuple3(const Tuple3<T> &ToCopy) {
        this->first = ToCopy.First();
        this->second = ToCopy.Second();
        this->third = ToCopy.Third();
    }

    template<typename T>
    Tuple3<T>::Tuple3() {
        first = 0;
        second = 0;
        third = 0;
    }

    template<class U>
    std::ostream &operator<<(std::ostream &os, const Tuple3<U> &tuple) {
        os << "3-Tuples" << std::endl << "  First: " << tuple.first << std::endl << "  Second: " << tuple.second
           << std::endl << "  Third: " << tuple.third;
        return os;
    }
}
#endif //GEOMETRY_THREETUPLE_HPP
