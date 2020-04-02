#ifndef _FamilyTree_
#define _FamilyTree_

#include <iostream>
#include <string>


//using namespace std;
namespace family{
    class Tree{
        string _name;
        //bool _sex;
        Tree *_father, *_mother;
    public:
        Tree(string name): _name(name), _father(nullptr), _mother(nullptr) {};
        Tree &addFather(string son, string father);   // Tells the tree that the father of Yosef is Yaakov.
	    Tree &addMother(string son, string mother);  // Tells the tree that the mother of Yosef is Rachel.
        void display(size_t tabs = 0);
        string relation(string ancestor);
        string find(string description);
        bool remove(string ancestor);
        ~Tree(){
            if(_father != nullptr)
                delete _father;
            if(_mother != nullptr)
                delete _mother;
        };
    };

};

#endif