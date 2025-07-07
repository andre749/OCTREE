#include <iostream>
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
    Octree<int>::Point3D p1(0.2,0.76,-0.5),p2(1,0,0);
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
    ent=1;
    int total_nodes = 0;
  //  a.traverse([&](const Octree<int>::Node*) {total_nodes++;});
    //cout << "Total de nodos: " << total_nodes << '\n';

    auto funct= [](const Octree<int>::Node* node) {
        const auto& c = node->boundary.center;
        cout << "Nodo centro: (" << c.x << ", " << c.y << ", " << c.z << ")\n";

        if (node->isLeaf and node->points.size()) {
            for (const auto& pr : node->points) {
                const auto& p = pr.first;
                cout << "  Punto: (" << p.x << ", " << p.y << ", " << p.z << ") -> Valores: ";
                for (const auto& val : pr.second) {
                    cout << val << ' ';
                }
                cout << '\n';
            }
        } else {
            cout << "  (sin puntos)\n";
        }
    };
    a.traverse(funct);
    a.insert(p2,ent);
    cout<<endl<<endl;
    a.traverse(funct);



//    a.remove(p);
//    cout<<a.find(p);
//    cout<<a.find(p2);
//    cout<<a.find(p1);


//    array<Octree<int>::Node*,2> a;
//    a= {
//            new Octree<int>::Node{bb},
//             new  Octree<int>::Node{bb}
//    };
//
//    cout<<a[0]->boundary.center.y;






}
