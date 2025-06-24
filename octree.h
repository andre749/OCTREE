// Created by andre on 6/23/2025.
//

#ifndef OCTREE_OCTREE_H
#define OCTREE_OCTREE_H

#include<vector>
#include <cstdlib>
#include <string>
#include <functional>
#include <queue>

using namespace std;
template<typename T>
class Octree {
public:
    struct Point3D {
        double x, y, z;
        Point3D(int x,int y, int z):x(x),y(y),z(z){}
        Point3D operator+(Point3D& o){return{x+o.x,y+o.y,z+o.z};}
        Point3D operator-(Point3D& o){return{x-o.x,y-o.y,z-o.z};}

    };
    struct BoundingBox {
        Point3D center;
        double halfSize; // radio en cada eje
        bool contains(const Point3D& p) const {
            return (((center.x - halfSize) <= p.x && p.x <= (center.x + halfSize)) &&
            ((center.y - halfSize) <= p.y && p.y <= (center.y + halfSize)) &&
            ((center.z - halfSize) <= p.z && p.z <= (center.z + halfSize)));

        }

        BoundingBox(Point3D &center,double halfsize):center(center),halfSize(halfsize){}
    };
    // Nodo interno
    struct Node {
        BoundingBox boundary;
        vector<pair<Point3D,vector<T>>> points;
        Node children[8];
        bool isLeaf = true;
        Node(BoundingBox& b):boundary(b),isLeaf(true){}
    };
    Node* root;
    std::size_t density;
    int maxDepth;
    Octree(const BoundingBox& boundary,size_t capacity = 8,int maxDepth = 8):density(capacity),maxDepth(maxDepth){
        root=new Node{boundary};
    }
    ~Octree();

    // Operaciones públicas
    bool insert(const Point3D& p, const T& value){
        if(!root->boundary.contains(p)) return false;
        return insert(root,p,value,0);
    }
    bool remove(const Point3D& p, const T* value = nullptr){

    }
    vector<T> find(const Point3D& p){

    }

    void clear();

    size_t size() {
        return{};
    }
    int depth() {
        return{};
    }
    int max_depth(){
        maxDepth;
    }
    string toString(int indent = 0){
        return{};
    }
    void traverse(const std::function<void(const Octree&)>& fn){

    }

private:

    bool insert(Node* node, const Point3D& p, const T& value, int depth){
        if(depth>=maxDepth) return false;
        if(node->isLeaf) {
            for(int i=0;i<node->points.size();i++){
                if(node->points[i].first==p){
                    node->points[i].second.push_back(value);
                    return true;
                }
            }
            node->points.push_back({p, value});
            if(node->points.size()>density) subdivide(node);
            return true;
        }
        int index= nearest_child(p,node->children);
        return insert(node->children[index],p,value,depth+1);

    }
    bool remove(Node* node, const Point3D& p, const T* value, int depth);

    void subdivide(Node* node){
        node->isLeaf=false;
        Point3D center=node->boundary.center;
        double hf=node->boundary.halfSize/2;
        node->children= {
                {BoundingBox(center + Point3D{hf, hf, hf},  hf)},
                {BoundingBox(center + Point3D{-hf, hf, hf}, hf)},
                {BoundingBox(center + Point3D{hf, -hf, hf}, hf)},
                {BoundingBox(center + Point3D{hf, hf, -hf}, hf)},
                {BoundingBox(center - Point3D{hf, hf, hf},  hf)},
                {BoundingBox(center - Point3D{-hf, hf, hf}, hf)},
                {BoundingBox(center - Point3D{hf, -hf, hf}, hf)},
                {BoundingBox(center - Point3D{hf, hf, -hf}, hf)}
        };
        for( int i=i<node->points.size()-1;i>=0;i--){
            pair<Point3D,vector<T>> pair=node->points[i];
            insert(node,pair.first,pair.second);
            node->points.pop_back();
        }

    }
    int nearest_child(const Point3D& p,Node array[8]){
        int index,  currentDis,minDis=abs(array[0].boundary.center.x-p.x)+
                                      abs(array[0].boundary.center.y-p.y)+
                                      abs(array[0].boundary.center.z-p.z);;;
        for( int i=1;i< 8;i++){
            currentDis=abs(array[i].boundary.center.x-p.x)+
                    abs(array[i].boundary.center.y-p.y)+
                    abs(array[i].boundary.center.z-p.z);
            if(currentDis<minDis){
                minDis=currentDis;
                index=i;
            }
        }
        return index;

    }
    void clear(Node* node){

    }
};


#endif //OCTREE_OCTREE_H
