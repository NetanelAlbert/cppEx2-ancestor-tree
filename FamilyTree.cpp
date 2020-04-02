
#include "FamilyTree.hpp"
#include <iostream>

using namespace std;
using namespace family;

Tree &Tree::addFather(string son, string father){
    if(son == _name){
        if(_father == nullptr)
            _father = new Tree(father);
        else
            throw runtime_error(son+" already has a father");
    }
    if(_father != nullptr){
        try{
            _father->addFather(son, father);
        } catch (out_of_range &er){}
    }
    if(_mother != nullptr){
        try{
            _mother->addFather(son, father);
        } catch (out_of_range &er){}
    }
    throw out_of_range(son+" dosn't exist");
}

Tree &Tree::addMother(string son, string mother){
    if(son == _name){
        if(_mother == nullptr)
            _mother = new Tree(mother);
        else
            throw runtime_error(son+" already has a mother");
    }
    if(_father != nullptr){
        try{
            _father->addMother(son, mother);
        } catch (out_of_range &er){}
    }
    if(_mother != nullptr){
        try{
            _mother->addMother(son, mother);
        } catch (out_of_range &er){}
    }
    throw out_of_range(son+" dosn't exist");
}

string Tree::relation(string ancestor){
    if(ancestor == _name){
        return "me";
    }
    if(_father != nullptr){
        try{
            string &ans = _father->relation(ancestor);
            if(ans == "me")
                return "father";
            if(ans == "father" || ans == "mother")
                return "grand"+ans;
            return "great-"+ans;
        } catch (out_of_range &er){}
    }
    if(_mother != nullptr){
        try{
            string &ans = _mother->relation(ancestor);
            if(ans == "me")
                return "mother";
            if(ans == "father" || ans == "mother")
                return "grand"+ans;
            return "great-"+ans;
        } catch (out_of_range &er){}
    }
    throw out_of_range(ancestor+" dosn't exist");
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
        string tmp = description.substr(5); //remove "great"/"grand"
        if(tmp.at(0) == '-')
            tmp.erase(0,1); //remove the '-' after "great" 

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

void Tree::display(size_t tabs = 0){
    if(tabs == 0)
        cout << "Display "<<_name<<" tree. Father = up, mother = down.\n" << endl;
    
    if(_father != nullptr)
        _father->display(tabs+1);
    else
        cout << '\n';
    for (size_t i = 0; i < tabs; i++)
        cout << '\t';
    cout << _name << '\n' << endl;
    if(_mother != nullptr)
        _mother->display(tabs+1);
    else
        cout << '\n';
}