
#include "FamilyTree.hpp"
//#include <iostream>

using namespace std;
using namespace family;

Tree &Tree::addFather(string son, string father){
    if(son == _name){
        if(_father == nullptr){
            _father = new Tree(father, 'm');
            return *this;
        }
        else
            throw runtime_error(son+" already has a father");
    }
    if(_father != nullptr){
        try{
            _father->addFather(son, father);
            return  *this;
        } catch (out_of_range &er){}
    }
    if(_mother != nullptr){
        _mother->addFather(son, father);
        return  *this;
    }
    throw out_of_range(son+" dosn't exist");
}

Tree &Tree::addMother(string son, string mother){
    if(son == _name){
        if(_mother == nullptr){
            _mother = new Tree(mother, 'f');
            return  *this;
        }
        else
            throw runtime_error(son+" already has a mother");
    }
    if(_father != nullptr){
        try{
            _father->addMother(son, mother);
            return  *this;
        } catch (out_of_range &er){}
    }
    if(_mother != nullptr){
        _mother->addMother(son, mother);
        return  *this;
    }
    throw out_of_range(son+" dosn't exist");
}

string Tree::relation(string ancestor){
    if(ancestor == _name){
        return "me";
    }
    string ans = "unrelated";
    if(_father != nullptr){
        ans = _father->relation(ancestor);
        if(ans != "unrelated"){
            if(ans == "me"){
                ans = "father";
            }else if(ans == "father" || ans == "mother"){
                ans = "grand"+ans;
            }else ans = "great-"+ans;
        }
    }
    if(ans == "unrelated" &&_mother != nullptr){
        ans = _mother->relation(ancestor);
        if(ans != "unrelated"){
            if(ans == "me"){
                ans = "mother";
            }else if(ans == "father" || ans == "mother"){
                ans = "grand"+ans;
            }else ans = "great-"+ans;
        }
    }
    return ans;
}

string Tree::find(string description){
    if(description.at(0) == 'f'){
        if(_father != nullptr)
            return _father->_name;
        else
            throw out_of_range("Requested relation dosn't exist");
    }
    if(description.at(0) == 'm'){
        if(_mother != nullptr)
            return _mother->_name;
        else
            throw out_of_range("Requested relation dosn't exist");
    }
    if(description.at(0) == 'g'){
        string tmp;
        try{
            tmp = description.substr(5); //remove "great"/"grand"
            if(tmp.at(0) == '-')
                tmp.erase(0,1); //remove the '-' after "great" 
        } catch(out_of_range& ex){ // throwed by string
            throw runtime_error("wrong expression");
        }

        if(_father != nullptr)
            try{
                return _father->find(tmp);
            } catch(out_of_range &ex){}
        if(_mother != nullptr)
            return _mother->find(tmp);

        throw out_of_range("Requested relation dosn't exist");
    }
    throw runtime_error("wrong expression");
}

bool Tree::remove(string ancestor){
    if(_father != nullptr && _father->_name == ancestor){
        delete _father;
        _father = nullptr;
        return true;
    }
    if(_mother != nullptr && _mother->_name == ancestor){
        delete _mother;
        _mother = nullptr;
        return true;
    }
    return (_father != nullptr && _father->remove(ancestor)) 
        || (_mother != nullptr && _mother->remove(ancestor));
}

void Tree::display(size_t tabs){
    if(tabs == 0)
        cout << "Display "<<_name<<" tree. Father = up, mother = down.\n" << endl;
    
    if(_father != nullptr)
        _father->display(tabs+1);
    
    for (size_t i = 0; i < tabs; i++)
        cout << '\t';
    if(_sex == 'm')
        cout << "/``";
    if(_sex == 'f')
        cout << "\\_";
    cout << _name << endl;
    if(_mother != nullptr)
        _mother->display(tabs+1);
    
}