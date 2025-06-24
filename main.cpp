#include <iostream>
#include "octree. cpp"
using namespace std;


int main() {
    Octree<int>::Point3D p(0,0,0);
    Octree<int>::BoundingBox bb(p,1);
    Octree<int>::Node n(bb);
    Octree<int> a(n,100,100);



}
