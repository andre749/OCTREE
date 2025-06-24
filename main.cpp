#include <iostream>
#include <mmcobj.h>
#include "octree. cpp"
using namespace std;
template<
        typename Container,
        // SFINAE: existan std::begin/ std::end
        typename = decltype(std::begin(std::declval<Container>())),
        typename = decltype(std::end  (std::declval<Container>()))
>
std::ostream& operator<<(std::ostream& os, const Container& c) {
    os << "{ ";
    auto it = std::begin(c);
    auto end = std::end(c);
    for (; it != end; ++it) {
        os << *it;
        if (std::next(it) != end)
            os << ", ";
    }
    os << " }";
    return os;
}


int main() {
    Octree<int>::Point3D p(0,0,0);
    Octree<int>::BoundingBox bb(p,1);
    Octree<int> a(bb,2,100);
    Octree<int>::Point3D p1(0.2,0.76,-0.5);
    int ent=2;
    cout<<a.insert(p,ent)<<"\n";
    ent=21;
    cout<<a.insert(p,ent)<<"\n";
    ent=2;
    cout<<a.insert(p,ent)<<"\n";
    ent=-1;
    cout<<a.insert(p,ent)<<"\n";
    ent=-58;
    cout<<a.insert(p1,ent)<<"\n";
    ent=3;
    cout<<a.insert(p1,ent)<<"\n";
    ent=7;
    cout<<a.insert(p1,ent)<<"\n";
    ent=10;
    cout<<a.insert(p1,ent)<<"\n";
    cout<<a.find(p);
    cout<<a.find(p1);





//    array<Octree<int>::Node*,2> a;
//    a= {
//            new Octree<int>::Node{bb},
//             new  Octree<int>::Node{bb}
//    };
//
//    cout<<a[0]->boundary.center.y;







}
