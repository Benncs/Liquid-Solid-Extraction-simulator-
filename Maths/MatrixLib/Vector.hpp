//
// Created by CASALE Benjamin on 05/04/2021.
//

#ifndef MATRIX_VECTOR_HPP
#define MATRIX_VECTOR_HPP

class complexe;

#include <vector>
#include <cmath>

/************************************
 * Basic class to impletement vectors
 * Based on std::vector
 * Compatible with Matrix class
 * @tparam T
 **********************************/

namespace LinearAlgebra {
    template<class T>
    class Vector {
    public:
        //Constructors-Destructor
        Vector();

        explicit Vector(const std::vector<T> &Input);

        explicit Vector(const int &NumDim);

        ~Vector() = default;

        //Methods

        //Getters
        [[nodiscard]] inline unsigned int GetDim() const;

        inline T GetElement(unsigned int Index) const;

        //Setters
        inline void SetElement(unsigned int Index, T Value);

        //Others
        T Norm() const;

        [[nodiscard]] bool IsNull() const;

        Vector<T> Normalize();

        void Clear();

        void NormalizeIt();

        //Overload
        static T dot(const Vector<T> &A, const Vector<T> &B);

        static Vector<T> cross(const Vector<T> &A, const Vector<T> &B);

        bool operator==(const Vector &rhs) const;

        bool operator!=(const Vector &rhs) const;


        Vector<T> operator+(const Vector<T> &RHS) const;

        Vector<T> operator-(const Vector<T> &RHS) const;

        Vector<T> operator*(const T &RHS) const;

        Vector<T> &operator=(const Vector<T>& RHS);

        template<class U>
        friend Vector<U> operator*(const U &LHS, const Vector<U> &RHS);


    private:
        std::vector<T> m_Vector_Data;
        unsigned int m_Dim =0;
        inline bool CloseEnough(T f1, T f2)const { return fabs(f1 - f2) < 1e-9; }
    };

    template<class T>
    Vector<T>::Vector() {
        /*Empty vectors constructor*/
        m_Dim = 0;
        m_Vector_Data = std::vector<T>();
    }

    template<class T>
    Vector<T>::Vector(const std::vector<T> &Input) {
        /*Vectors with Data constructor*/
        m_Dim = Input.size();
        m_Vector_Data = Input;
    }

    template<class T>
    inline unsigned int Vector<T>::GetDim() const { return m_Dim; }

    template<class T>
    inline T Vector<T>::GetElement(unsigned int Index) const { return m_Vector_Data[Index]; }

    template<class T>
    Vector<T> Vector<T>::operator+(const Vector<T> &RHS) const {
        if (m_Dim != RHS.m_Dim) throw std::invalid_argument("Dimensions don't match");

        std::vector<T> VRes;
        for (unsigned int i = 0; i < m_Dim; ++i) {
            VRes.emplace_back(m_Vector_Data.at(i) + RHS.m_Vector_Data.at(i));
        }

        Vector<T> Res(VRes);
        return Res;
    }

    template<class T>
    Vector<T> Vector<T>::operator-(const Vector<T> &RHS) const {
        if (m_Dim != RHS.m_Dim) throw std::invalid_argument("Dimensions don't match");

        std::vector<T> VRes;
        for (unsigned int i = 0; i < m_Dim; ++i) {
            VRes.emplace_back(m_Vector_Data.at(i) - RHS.m_Vector_Data.at(i));
        }

        Vector<T> Res(VRes);
        return Res;
    }

    template<class T>
    Vector<T> Vector<T>::operator*(const T &RHS) const {
        std::vector<T> VRes;
        for (unsigned int i = 0; i < m_Dim; ++i) {
            VRes.emplace_back(m_Vector_Data.at(i) * RHS);
        }
        Vector<T> Res(VRes);
        return Res;
    }

    template<class U>
    Vector<U> operator*(const U &LHS, const Vector<U> &RHS) {
        std::vector<U> VRes;
        for (unsigned int i = 0; i < RHS.m_Dim; ++i) {
            VRes.emplace_back(LHS * RHS.m_Vector_Data.at(i));
        }

        Vector<U> Res(VRes);
        return Res;
    }

    template<class T>
    T Vector<T>::dot(const Vector<T> &A, const Vector<T> &B) {

        /*Dot productor for vectors of the same dimensions*/
        if (A.m_Dim != B.m_Dim) throw std::invalid_argument("Dimensions don't match");
        T CumSum = static_cast<T>(0.0);
        for (unsigned int i = 0; i < A.m_Dim; ++i) {
            CumSum += A.m_Vector_Data.at(i) * B.m_Vector_Data.at(i);
        }

        return CumSum;
    }

    template<class T>
    Vector<T> Vector<T>::cross(const Vector<T> &A, const Vector<T> &B) {

        //Cross Product
        if (A.m_Dim != B.m_Dim) throw std::invalid_argument("Dimensions don't match");

        if (A.m_Dim != 3) throw std::invalid_argument("Cross product only on 3 dim vectors");
        std::vector<T> VRes;
        //Basically the croos product formula
        VRes.emplace_back(
                A.m_Vector_Data.at(1) * B.m_Vector_Data.at(2) - (A.m_Vector_Data.at(2) * B.m_Vector_Data.at(1)));
        VRes.emplace_back(
                A.m_Vector_Data.at(0) * B.m_Vector_Data.at(2) - (A.m_Vector_Data.at(2) * B.m_Vector_Data.at(0)));
        VRes.emplace_back(
                A.m_Vector_Data.at(0) * B.m_Vector_Data.at(1) - (A.m_Vector_Data.at(1) * B.m_Vector_Data.at(0)));
        Vector<T> Res(VRes);
        return Res;

    }



    template<class T>
    T Vector<T>::Norm() const {
        /*Norm2 calculation */
        T CumSum = static_cast<T>(0.0);
        for (unsigned int i = 0; i < m_Dim; ++i) {
            CumSum += (m_Vector_Data.at(i) * m_Vector_Data.at(i));
        }
        return std::sqrt(CumSum);
    }

    template<class T>
    inline void Vector<T>::SetElement(unsigned int Index, T Value) { m_Vector_Data[Index] = Value; }

    template<class T>
    Vector<T> Vector<T>::Normalize() {
        /* Basically divising every element by the vector's norm*/
        T VNorm = this->Norm();
        //if (VNorm == 0) return 0;
        if(VNorm ==0) return Vector<T>(this->m_Dim);
        else {
            Vector<T> Res(m_Vector_Data);
            return Res * static_cast<T>(1.0 / VNorm);
        }

    }

    template<class T>
    void Vector<T>::NormalizeIt() {

        /*It modifies the vectors, in place methods
         * Basically dividing every element by the vector's norm*/
        T VNorm = this->Norm();

        for (unsigned int i = 0; i < m_Dim; ++i) {
            T temp = (VNorm!=0)? m_Vector_Data.at(i) * static_cast<T>(1.0 / VNorm): 0;
            m_Vector_Data.at(i) = temp;
        }
    }

    template<class T>
    Vector<T>::Vector(const int &NumDim) {

        /*Constructor for a Vector with a fixed size*/
        m_Dim = NumDim;
        m_Vector_Data = std::vector<T>(m_Dim, static_cast<T>(0.0));
    }

    template<class T>
    void Vector<T>::Clear() {
        this->m_Dim=0;
        this->m_Vector_Data.clear();
    }

    template<class T>
    bool Vector<T>::IsNull() const {
        for(auto element : m_Vector_Data) {
            if(std::abs(element)<1e-9) return true;
        }
        return false;
    }

    template<class T>
    Vector<T> &Vector<T>::operator=(const Vector<T>& RHS) {
            m_Dim=RHS.m_Dim;
            m_Vector_Data.clear();
            for(unsigned i =0;i<m_Dim;++i) m_Vector_Data.template emplace_back(RHS.GetElement(i));
            return *this;
    }

    template<class T>
    bool Vector<T>::operator==(const Vector &rhs) const {
        if(m_Dim!=rhs.m_Dim) return false;
        else {
            for (auto i = 0; i < m_Dim; ++i) {
                if(!CloseEnough(m_Vector_Data[i],rhs.m_Vector_Data[i])) return false;
            }
            return true;
        }

    }

    template<class T>
    bool Vector<T>::operator!=(const Vector &rhs) const {
        return !(rhs == *this);
    }

}
#endif //MATRIX_VECTOR_HPP
