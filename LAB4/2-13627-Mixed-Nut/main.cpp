#include "function.h"
#include <iomanip>
#include <iostream>
#include <string>
#include <cassert>

namespace oj {
    void Nut::setVolume(double v) {
        volume = v;
    }

    double Nut::getVolume() {
        return volume;
    }

    // AFTER Here
    CuboidNut::CuboidNut(double _l, double _w, double _h): length(_l), width(_w), height(_h) {
        if (length<0 || width<0 || height<0) setVolume(0);
        else setVolume(length*width*height);
    }
    CubeNut::CubeNut(double _w): CuboidNut(_w, _w, _w) {
    }
    SphereNut::SphereNut(double _r): radius(_r) {
        if (radius<0) setVolume(0);
        else setVolume(4./3*PI*radius*radius*radius);
    }
    ConeNut::ConeNut(double _r, double _h): radius(_r), height(_h) {
        if (radius<0 || height<0) setVolume(0);
        else setVolume(1./3*PI*radius*radius*height);
    }
    CylinderNut::CylinderNut(double _r, double _h): radius(_r), height(_h) {
        if (radius<0 || height<0) setVolume(0);
        else setVolume(PI*radius*radius*height);
    }
}

int main(void) {
    using namespace oj;
    using std::cin;
    using std::cout;
    using std::endl;
    using std::string;

    string shape;
    double totalVolume = 0.0;

    while (cin >> shape) {
        if (shape == "Cube") {
            double s;
            cin >> s;
            CubeNut cube(s);
            totalVolume += cube.getVolume();
        } else if (shape == "Cuboid") {
            double l, w, h;
            cin >> l >> w >> h;
            CuboidNut cuboid(l, w, h);
            totalVolume += cuboid.getVolume();
        } else if (shape == "Sphere") {
            double r;
            cin >> r;
            SphereNut sphere(r);
            totalVolume += sphere.getVolume();
        } else if (shape == "Cone") {
            double r, h;
            cin >> r >> h;
            ConeNut cone(r, h);
            totalVolume += cone.getVolume();
        } else if (shape == "Cylinder") {
            double r, h;
            cin >> r >> h;
            CylinderNut cylinder(r, h);
            totalVolume += cylinder.getVolume();
        } else {
            assert(false);
        }
    }

    cout << std::setprecision(4) << std::fixed;   // set precision to 4 decimal places
    cout << totalVolume << endl;

    return 0;
}