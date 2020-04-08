#ifndef _FamilyTree_
#define _FamilyTree_

#include <iostream>
#include <string>


using namespace std;
namespace family{
    enum Type{
        root_type, father_type, mother_type
    };

    class Tree{
        string _name;
        Type _type;
        Tree *_father, *_mother;
    public:
        Tree(string name, Type type = root_type): 
            _name(name), 
            _father(nullptr), 
            _mother(nullptr), 
            _type(type) { };
        Tree &addFather(string , string father);   // Tells the tree that the father of 'son' is 'father'.
	    Tree &addMother(string son, string mother);  // Tells the tree that the mother of 'son' is 'mother'.
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