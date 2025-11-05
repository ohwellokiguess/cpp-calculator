#pragma once
#include <iostream>
#include <numeric>

class Rational {
public:
    //              Constructors

    // Num and Denom
    Rational(int numerator, int denominator) {
        if (denominator == 0){
            std::cerr << "Знаменатель не может быть равен нулю";
        } else {
            numerator_ = numerator;
            denominator_ = denominator;
            Reduction();
        }
    }

    // Only numerator
    Rational(int numerator) {
        numerator_ = numerator;
    }

    // Default
    Rational() {}

    // Copying
    Rational(const Rational& r) {
        numerator_ = r.numerator_;
        denominator_ = r.denominator_;
        Reduction();
    }
    //
    //              Methods

    // Inversion
    Rational Inv() const {
        return Rational(denominator_, numerator_);
    }

    int GetNumerator() const {
        return numerator_;
    }

    int GetDenominator() const {
        return denominator_;
    }

    void Reduction() {
        if (denominator_ < 0) {
            numerator_ = -numerator_;
            denominator_ = -denominator_;
        }
        const int divisor = std::gcd(numerator_, denominator_);
        numerator_ /= divisor;
        denominator_ /= divisor;
    }

    //
    //              Operator Overload

    //                  Arithmetic

    Rational operator+(const Rational& lhs) const {
        return {numerator_ * lhs.denominator_ + lhs.numerator_ * denominator_,
                denominator_ * lhs.denominator_};
    }

    Rational operator-(const Rational& lhs) const {
        return {numerator_ * lhs.denominator_ - lhs.numerator_ * denominator_,
                denominator_ * lhs.denominator_};;
    }

    Rational operator*(const Rational& lhs) const {
    return {numerator_ * lhs.numerator_,
            denominator_ * lhs. denominator_};
    }

    Rational operator/(const Rational& lhs) const {
        return {numerator_ * lhs.denominator_,
                denominator_ * lhs.numerator_};
    }
    //
    //                  Assignment

    Rational& operator=(const Rational& lhs) {
        numerator_ = lhs.numerator_;
        denominator_ = lhs.denominator_;
        return *this;
    }

    Rational operator+=(const Rational& lhs) {
        return *this = *this + lhs;
    }

    Rational operator-=(const Rational& lhs) {
        return *this = *this - lhs;
    }

    Rational operator*=(const Rational& lhs) {
        return *this = *this * lhs;
    }
    Rational operator/=(const Rational& lhs) {
        return *this = *this / lhs;
    }
    //
    //                  Unary

    Rational operator+() const {
        return {numerator_, denominator_};
    }

    Rational operator-() const {
        return {-numerator_, denominator_};
    }
    //
    //                  Comparison

    auto operator==(const Rational& lhs) const {
        return (numerator_ * lhs.denominator_) == (lhs.numerator_ * denominator_);
    }

    auto operator<=>(const Rational& lhs) const {
        return (numerator_ * lhs.denominator_) <=> (lhs.numerator_ * denominator_);
    }
    //

    friend std::ostream& operator<<(std::ostream& os, const Rational& r);
    friend std::istream& operator>>(std::istream& is, Rational& r);

private:

    int numerator_ = 0;
    int denominator_ = 1;
};

//                    IOS Overload

inline std::ostream& operator<<(std::ostream& os, const Rational& r) {
    if (r.denominator_ == 1) {
        os << r.numerator_;
        return os;
    } else {
        os << r.numerator_ << " / " << r.denominator_;
        return os;
    }
};

inline std::istream& operator>>(std::istream& is, Rational& r) {
    char del = '0';

    if (!(is >> r.numerator_)) {
        is.setstate(std::ios::failbit);
        return is;
    }

    if (!(is >> std::ws >> del)) {
        is.clear();
        return is;
    }

    if (del != '/') {
        is.unget();
        return is;
    }

    if (!(is >> r.denominator_) || (r.denominator_ == 0)) {
        is.setstate(std::ios::failbit);
        return is;
    }
    return is;
};
