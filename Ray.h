#ifndef  RAY_H
#define RAY_H
#include "Vector.h"
#include <istream>
class Ray {
    private:
        Vector origin;
        Vector direction;
    public:
        Ray() {}
        Ray(const Vector& _origin, const Vector& _direction): origin(_origin), direction(_direction) {}
        const Vector& getOrigin() const{
            return origin;
        };
        const Vector& getDirection() const{
            return direction;
        };
        void printing(std::ostream& out) const {
            out << direction.getX() << " " << direction.getY() << " " << direction.getZ() << " \n";

        }
};
#endif
