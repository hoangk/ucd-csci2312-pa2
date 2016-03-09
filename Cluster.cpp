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
    LNode::LNode(const Point &point, LNodePtr n) {
        this->p = point;
        this->next = n;

    }
    Cluster::Cluster() {
        __size = 0;
        __points = nullptr;
    }

// copy constructor
    Cluster::Cluster(const Cluster &cluster) {
        __size = cluster.__size;
        LNodePtr pointer = __points;
        LNodePtr clusterpointer = cluster.__points;
        while (clusterpointer->next != nullptr) {
            pointer->p = clusterpointer->p;       //
            pointer = pointer->next;          //update left side
            clusterpointer = clusterpointer->next; // update right side
        }

    }

    Cluster &Cluster::operator=(const Cluster &cluster) {
        __size = cluster.__size;
        LNodePtr pointer = __points;
        LNodePtr clusterpointer = cluster.__points;
        while (clusterpointer->next != nullptr) {
            pointer->p = clusterpointer->p;       //
            pointer = pointer->next;          //update left side
            clusterpointer = clusterpointer->next; // update right side
        }
        return *this;
    }


    Cluster::~Cluster() {
        LNodePtr tempPointer = __points;
        while (__points != nullptr) {
            // delete __points->p;
            delete __points;
            __points = tempPointer->next;
            tempPointer = __points;
        }
    }

    int Cluster::getSize() const {
        return __size;
    }

    void Cluster::add(const Point &point) {
        if (__points == nullptr) {
            LNodePtr pointer = __points;
            pointer->p = point;
        }
        else {
            LNodePtr currentPointer = __points;
            if (currentPointer->p > point) {
                LNodePtr nextPointer = currentPointer;
                currentPointer = __points;
            }
        }
        __size++;
    }

    const Point &Cluster::remove(const Point &point) {
        LNodePtr previousPointer = __points;
        LNodePtr currentPointer = __points;
        while (currentPointer->next != nullptr) {
            if (currentPointer->p == point) {
                LNodePtr tempPointer;
                tempPointer = currentPointer;
                previousPointer->next = currentPointer->next;
                delete tempPointer;
                __size--;
            }
            previousPointer = currentPointer;
            currentPointer = currentPointer->next;
        }
    }

    bool Cluster::contains(const Point &point) {
        LNodePtr currentPointer = __points;
        while (currentPointer->next != nullptr) {
            if (currentPointer->p == point) {
                return true;
            }
            currentPointer = currentPointer->next;
        }

        return false;
    }

    const Point &Cluster::operator[](unsigned int index) const {
        LNodePtr currentPtr = __points;
        int i = 0;
        while (i < index) {
            return currentPtr->p;
            i++;
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
        LNodePtr currentPtr = cluster.__points;
        while (currentPtr->next != nullptr) {
            if (this->contains(currentPtr->p)) {
                currentPtr = currentPtr->next;
            }
            else {
                this->add(currentPtr->p);
                currentPtr = currentPtr->next;
            }
        }
        return *this;
    }

    Cluster &Cluster::operator-=(const Cluster &cluster) {
        LNodePtr currentPtr = cluster.__points;
        while (currentPtr->next != nullptr) {
            if (this->contains(currentPtr->p)) {
                this->remove(currentPtr->p);
            }
            currentPtr = currentPtr->next;
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
        if (cluster.__size != cluster1.__size)
            return false;
        else {
            LNodePtr currentPtr1 = cluster.__points;
            LNodePtr currentPtr2 = cluster1.__points;
            while (currentPtr1->next != nullptr) {
                if (currentPtr1->p != currentPtr2->p) {
                    return false;
                }
                currentPtr1 = currentPtr1->next;
                currentPtr2 = currentPtr2->next;
            }
        }
        return true;
    }

    const Cluster operator+(const Cluster &cluster, const Point &point) {
        LNodePtr currentPtr = cluster.__points;
        if (currentPtr == nullptr) {
            currentPtr = cluster.__points;
            currentPtr->p = point;
        }
        else {
            while (currentPtr->next != nullptr) {
                currentPtr = currentPtr->next;
            }
            LNodePtr newPointer = new LNode(point, nullptr);
            newPointer->p = point;
            newPointer->next = nullptr;
            currentPtr->next = newPointer;
        }
        return cluster;
    }

    const Cluster operator-(const Cluster &cluster, const Point &point) {
        LNodePtr currentPtr = cluster.__points;
        LNodePtr previousPtr = nullptr;
        while (currentPtr->next != nullptr) {
            if (currentPtr->p == point) {
                LNodePtr tempPointer;
                tempPointer = currentPtr;
                previousPtr->next = currentPtr->next;
                delete tempPointer;
            }
            previousPtr = currentPtr;
            currentPtr = currentPtr->next;
        }
        return cluster;
    }

    const Cluster operator+(const Cluster &cluster, const Cluster &cluster1) {
        LNodePtr currentPtr1 = cluster.__points;
        LNodePtr currentPtr2 = cluster1.__points;
        while (currentPtr1->next != nullptr) {
            if (currentPtr1->p == currentPtr2->p) {

            }
        }
//        bool Cluster::contains(const Point &point) {
//            LNodePtr currentPointer = __points;
//            while (currentPointer->next != nullptr) {
//                if (currentPointer->p == point) {
//                    return true;
//                }
//                currentPointer = currentPointer->next;
//            }
//
//            return false;
//        }
        return cluster;
    }
// n2bdone
    const Cluster operator-(const Cluster &cluster, const Cluster &cluster1) {
        return Cluster();
    }


}