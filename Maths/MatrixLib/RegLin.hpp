//
// Created by CASALE Benjamin on 06/04/2021.
//

#ifndef MATRIX_REGLIN_HPP
#define MATRIX_REGLIN_HPP
#include "Matrix.hpp"
#include <fstream>
#include <iterator>

//TODO Clear
namespace LinearAlgebra {

    template<class T>
    double RSquare(const std::vector<T> &X, const std::vector<T> &Y, const Vector <T> R) {
        int Numerator = 0;
        int Denominator = 0;
        int Mean = 0;
        const size_t Size = Y.size();
        T Coeff = R.GetElement(1);
        T Intercept = R.GetElement(0);

        auto f = [Coeff,Intercept](T x){return Coeff*x+Intercept;};

        std::vector<T> Regfunc;
        for (auto &Value : X) Regfunc.emplace_back(f(Value));
        for (auto &Value : Regfunc) Mean += Value;
        Mean = Mean / Size;

        for (auto Value = 0; Value < Size; ++Value) Numerator += std::pow(Regfunc[Value] - Y[Value], 2);
        for (auto &Value : Regfunc) Denominator += std::pow(Value - Mean, 2);

        double Res = 1 - static_cast<double>(Numerator) / static_cast<double>(Denominator);
        return Res;
    }

    template<class T>
    SOLUTIONS LinReg(const Matrix <T> &MatInput, const Vector <T> &VecInput, Vector <T> &Res) {
        Matrix<T> X = MatInput;

        Matrix<T> XT = X.Transpose();
        Matrix<T> XTX = XT * X;
        if (XTX.Inverse() == SOLUTIONS::NO_INVERSE) {
            return SOLUTIONS::NO_INVERSE;
        }
        Matrix<T> XTXXT = XTX * XT;
        Res = XTXXT * VecInput;
        return SOLUTIONS::DONE;

    }

    template<class T>
    T LinReg(const std::string &File_Name, Vector <T> &Res) {
        std::ifstream FILE2(File_Name);

        std::string read;
        std::vector<T> x;
        std::vector<T> y;
        while (getline(FILE2, read)) {
            std::istringstream iss(read);
            std::vector<std::string> res(std::istream_iterator<std::string>{iss},
                                         std::istream_iterator<std::string>());
            // x.emplace_back(std::stod(res[0]));
            x.emplace_back(static_cast<T>(std::stold(res[0])));
            y.emplace_back(static_cast<T>(std::stold(res[1])));
        }
        FILE2.close();

        const size_t num = x.size();
        std::vector<T> Xdata;
        std::vector<T> Ydata;
        for (auto i = 0; i < num; ++i) {
            Xdata.emplace_back(1);
            Xdata.emplace_back(x[i]);
            Ydata.emplace_back(y[i]);
        }

        Matrix<T> X(num, 2, Xdata);
        Vector<T> Y(Ydata);
        LinReg(X, Y, Res);
        T Rsquare = RSquare(x, y, Res);
        return Rsquare;
    }
}


#endif //${Filename}
