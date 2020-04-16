#ifndef _FamilyTree_
#define _FamilyTree_

#include <iostream>
#include <string>
#include <iostream>
using namespace std;

using namespace std;
namespace family{
    enum Type{
        root_type, father_type, mother_type
    };

    class Tree{
        const string _name;
        const Type _type;
        Tree *_father, *_mother;

        Tree *findNode(const string &);
    public:
        Tree(string name, Type type = root_type): 
            _name(name), 
            _father(nullptr), 
            _mother(nullptr), 
            _type(type) { };
        Tree &addFather(const string &,const string &);   // Tells the tree that the father of 'son' is 'father'.
	    Tree &addMother(const string &,const string &);  // Tells the tree that the mother of 'son' is 'mother'.
        void display(size_t tabs = 0) const;
        string relation(const string &) const;
        string find(const string &) const;
        bool remove(const string &);
        ~Tree(){
            if(_father != nullptr)
                delete _father;
            if(_mother != nullptr)
                delete _mother;
        };
    };
};

#endif