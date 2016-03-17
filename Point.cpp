//
// Created by Khoa on 2/11/16.
//

#include "Point.h"
#include <math.h>

namespace Clustering {

    unsigned int Point::__idGen = 0;


    Point::Point() {
         __dim = 0;
        __values = new double [__dim];
    }
    Point::Point(int initDim) {
        if (initDim != 0) {
            __dim = initDim;
            __values = new double[__dim];
            for(int i=0; i<__dim;i++ ) {
                __values [i] = 0;
            }

            __id = __idGen ++;
        }
    }

    Point::Point(int i, double *pDouble) {
        if (i != 0) {
            __dim = i;
            pDouble = new double[__dim];
            __id = __idGen++;

        }
    }

    Point::Point(const Point &point) {
        __dim = point.__dim;
        __values = new double[__dim];
        __id = point.__id;
        for (int i = 0; i < __dim; i++) {
            __values[i] = point.__values[i];
        }
    }

    Point &Point::operator=(const Point &point) {
        if (this != &point)
        {
            __dim = point.getDims();
            __id = point.__id;

        if (__values != nullptr)
            delete[] __values;

        __values = new double[point.__dim];
        for (int i = 0; i < point.__dim; i++) {
            __values[i] = point.__values[i];

          }
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
            std::cout << "Out of range " << std::endl;
        }
            this->__values[i] = d;
    }

    double Point::getValue(int i) const {
        if (i > __dim) {
            std::cout << "Out of range " << std::endl;
        }
//        else {
//        for ()
//        }
            return this->__values[i];
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
            return __values[index];
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
                else if(point.__values[i] > point1.__values[i])
                    return false;
            }
            return false;
    }

    bool operator>(const Point &point, const Point &point1) {
            for (int i = 0; i < point1.__dim; i++) {
                if (point.__values[i] > point1.__values[i])
                    return true;
                else if(point.__values[i] < point1.__values[i])
                    return false;
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
                ostream << point.__values[i];
                if (i != point.__dim - 1)
                    ostream << ", ";
            }
                ostream << std::endl;
            return ostream;
    }

    std::istream &operator>>(std::istream &istream, Point &point) {
        double *val = new double[point.__dim];
        char line[50];

        if(istream.good()) {
            for (int i = 0; i < point.__dim; i++) {
                istream.getline(line, 50, ', ');
                val[i] = atof(line);
            }
        }
        else
            std::cout << "The file is not open"<< std::endl;

        point.__values = val;
        return istream;
    }

};
