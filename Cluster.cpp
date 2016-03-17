//
// Created by Khoa on 2/25/16.
//

#include "Cluster.h"
#include "Point.h"

namespace Clustering {



//void Cluster::__del() {
//
//}
//
//void Cluster::__cpy(LNodePtr pts) {
//
//}
//
//bool Cluster::__in(const Point &p) const {
//    return false;
//}
    LNode::LNode(const Point &point, LNodePtr n) :
            p(point),
            next(n)
    {}

    Cluster::Cluster() {
        __size = 0;
        __points = nullptr;
    }

// copy constructor
    Cluster::Cluster(const Cluster &cluster): Cluster() {
      // Cluster();
        for(int i = 0; i < cluster.__size; i++){
            add(cluster[i]);
        }

    }

    Cluster &Cluster::operator=(const Cluster &cluster) {

        if (__size > 0)
        {
            LNodePtr tempPtr;
            LNodePtr cursor = __points;

            while (cursor != NULL)
            {
                tempPtr = cursor;
                cursor = cursor->next;
                delete tempPtr;
            }
            __size = 0;
        }

        for (int n = 0; n < cluster.getSize(); ++n)
        {
            add(cluster[n]);
        }
        return *this;
    }


    Cluster::~Cluster() {
        LNodePtr tempPointer = __points;
        while (__points != nullptr) {
            delete __points;
            __points = tempPointer->next;
            tempPointer = __points;
        }
    }

    int Cluster::getSize() const {
        return __size;
    }

    void Cluster::add(const Point &point) {
        if (__size == 0)
        {
            __size++;
            LNodePtr newNode = new LNode(point ,nullptr);
            __points = newNode;
        }

        else
        {
            if (contains(point))
                return;
            LNodePtr next;
            LNodePtr previous;

            next = __points;
            previous = nullptr;

            while (next != nullptr)
            {
                if (point < next -> p)
                {
                    if (previous == nullptr)
                    {
                        __points = new LNode(point, next);
                        __size++;
                        return;
                    }
                    else
                    {
                        previous -> next = new LNode(point, next);
                        ++__size;
                        return;
                    }
                }
                previous = next;
                next = next->next;

            }

            LNodePtr newPtr =new LNode(point, nullptr);
            previous->next = newPtr;
            __size++;
        }

    }

    const Point &Cluster::remove(const Point &point) {
        if (contains(point)) {
            LNodePtr next;
            LNodePtr previous = nullptr;
            next = __points;
            while (next != nullptr)

                if (next->p == point) {
                    if (previous == nullptr) {
                        __points = next->next;
                        delete next;
                        __size--;
                        break;
                    }
                }
        }
    return point;
    }


    bool Cluster::contains(const Point &point) {

        LNodePtr next = __points;

        while (next != nullptr)
        {

            if (next->p.getId() == point.getId())

                return true;

            else
                next = next->next;
        }

        return false;
    }

    const Point &Cluster::operator[](unsigned int index) const {
        LNodePtr currentPtr = __points;

        for (int i = 0; i < index; i++) {
            currentPtr = currentPtr->next;
        }
        return currentPtr->p;
    }

    Cluster &Cluster::operator+=(const Point &point) {
        this->add(point);
        return *this;
    }

    Cluster &Cluster::operator-=(const Point &point) {
        this->remove(point);
        return *this;
    }

    Cluster &Cluster::operator+=(const Cluster &cluster) {
        for(int i = 0; i < cluster.__size; i++){
            add(cluster[i]);
        }
        return *this;
    }

    Cluster &Cluster::operator-=(const Cluster &cluster) {
        for(int i = 0; i < cluster.__size; i++){
            remove(cluster[i]);
        }
        return *this;
    }

    std::ostream &operator<<(std::ostream &ostream, const Cluster &cluster) {
        LNodePtr currentPtr = cluster.__points;
        if (currentPtr == nullptr) {
            ostream << "Empty cluster" << std::endl;
            return ostream;
        }
        while (currentPtr != nullptr) {
            if (currentPtr->next == nullptr)
                ostream << currentPtr->p;
            else ostream << currentPtr->p << " ";
            currentPtr = currentPtr->next;
        }
        ostream << std::endl;
        return ostream;
    }

    std::istream &operator>>(std::istream &istream, Cluster &cluster) {

        return istream;
    }

    bool operator==(const Cluster &cluster, const Cluster &cluster1) {
        if (cluster.getSize() != cluster1.getSize())
            return false;
        else {
            for(int i = 0; i < cluster.getSize(); i++){
                if(cluster[i] !=cluster1[i]){
                    return false;
                }
            }
        }
        return true;
    }
    bool operator !=(const Cluster &cluster, const Cluster &cluster1 ) {
        if (cluster == cluster1)
            return false;
        return true;
    }

    const Cluster operator+(const Cluster &cluster, const Point &point) {
        Cluster cluster1(cluster);
        cluster1 += point;
        return cluster1;
    }

    const Cluster operator-(const Cluster &cluster, const Point &point) {
        Cluster cluster1(cluster);
        cluster1 -= point;
        return cluster1;
    }

    const Cluster operator+(const Cluster &cluster, const Cluster &cluster1) {
        Cluster unionCluster(cluster);
        unionCluster += cluster1;
        return unionCluster;
    }

    const Cluster operator-(const Cluster &cluster, const Cluster &cluster1) {
            Cluster differenceCluster(cluster);
            differenceCluster -= cluster1;
        return differenceCluster;
    }


}
