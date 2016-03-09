//
// Created by Khoa on 2/11/16.
//

#include "Point.h"
#include <math.h>
#include <MacTypes.h>

namespace Clustering {


    Point::Point(){
        __dim = 0;
        __values = 0;
    }

    Point::Point(int initDim) {
        if (initDim != 0) {
            __dim = initDim;
            __values = new double[__dim];

        }

    }


    Point::Point(int i, double *pDouble) {
        if (i != 0) {
            __dim = i;
            pDouble = new double[__dim];
        }


    }

    Point::Point(const Point &point) {
        __dim = point.__dim;
        __values = new double[__dim];
        for (int i = 0; i < __dim; i++) {
            __values[i] = point.__values[i];
        }
    }

    Point &Point::operator=(const Point &point) {
        __dim = point.__dim;
        __values = new double[__dim];
        for (int i = 0; i < __dim; i++) {
            __values[i] = point.__values[i];

        }
        return *this;
    }

    Point::~Point() {
        delete[] __values;
    }

    int Point::getId() const {
        return __id;
    }

    int Point::getDims() const {
        return __dim;
    }

    void Point::setValue(int i, double d) {
        if (i > __dim) {
            std::cout << "out of range " << std::endl;
        }
        this-> __values[i-1] = d;
    }

    double Point::getValue(int i) const {
        if (i > __dim) {
            std::cout << "out of range " << std::endl;
        }
        return this->__values[i-1];;
    }

    double Point::distanceTo(const Point &point) const {
        double dis = 0;
        if (point.__dim == __dim) {
            double sum = 0.0;
            for (int i = 0; i < __dim; i++) {
                sum += ((point.__values[i] - __values[i]) * (point.__values[i] - __values[i]));
            }
            dis = sqrt(sum);
        }
        return dis;

    }
    Point &Point::operator*=(double d) {
        for (int i = 0; i < __dim; i++) {
            __values[i] *= d;
        }
        return *this;
    }

    Point &Point::operator/=(double d) {
        for (int i = 0; i < __dim; i++) {
            __values[i] /= d;
        }
        return *this;
    }

    const Point Point::operator*(double d) const {
        Point tempValues(__dim);
        for (int i = 0; i < __dim; i++) {
            tempValues.__values[i] = __values[i] * d;
        }
        return tempValues;
    }

    const Point Point::operator/(double d) const {
        Point tempValues2(__dim);
        for (int i = 0; i < __dim; i++) {
            tempValues2.__values[i] = __values[i] / d;
        }
        return tempValues2;
    }

    double &Point::operator[](int index) {
        return __values[index - 1];
    }

    Point &operator+=(Point &point, const Point &point1) {
        for (int i = 0; i < point.__dim; i++) {
            point.__values[i] += point1.__values[i];
        }
        return point;
    }


    Point &operator-=(Point &point, const Point &point1) {
        for (int i = 0; i < point.__dim; i++) {
            point.__values[i] -= point1.__values[i];
        }
        return point;
    }

    const Point operator+(const Point &point, const Point &point1) {
        Point tempPoint(point.__dim);
        for (int i = 0; i < point.__dim; i++) {
            tempPoint.__values[i] = point.__values[i] + point1.__values[i];
        }
        return tempPoint;
    }

    const Point operator-(const Point &point, const Point &point1) {
        Point tempPoint(point.__dim);
        for (int i = 0; i < point.__dim; i++) {
            tempPoint.__values[i] = point.__values[i] - point1.__values[i];
        }
        return tempPoint;
    }

    bool operator==(const Point &point, const Point &point1) {
        if (point.__dim == point1.__dim) {
            for (int i = 0; i < point.__dim; i++) {
                if (point.__values[i] != point1.__values[i])
                    return false;
            }
        }
        return true;
    }

    bool operator!=(const Point &point, const Point &point1) {
        if (point == point1)
            return false;
        return true;
    }

    bool operator<(const Point &point, const Point &point1) {
        for (int i = 0; i < point1.__dim; i++) {
            if (point.__values[i] < point1.__values[i])
                return true;
        }
        return false;
    }

    bool operator>(const Point &point, const Point &point1) {
        for (int i = 0; i < point1.__dim; i++) {
            if (point.__values[i] > point1.__values[i])
                return true;
        }
        return false;
    }

    bool operator<=(const Point &point, const Point &point1) {
        if (point > point1)
            return false;
        return true;
    }

    bool operator>=(const Point &point, const Point &point1) {
        if (point < point1)
            return false;
        return true;
    }

    std::ostream &operator<<(std::ostream &ostream, const Point &point) {
        for (int i = 0; i < point.__dim; i++) {
            ostream << point.__values;
            if (i < point.__dim - 1)
                ostream << ", ";
            ostream << std::endl;
        }
        return ostream;
    }

    std::istream &operator>>(std::istream &istream, Point &point) {
        for (int i = 0; i < point.__dim; i++) {
            istream >> point.__values[i];
        }
        return istream;
    }
};
