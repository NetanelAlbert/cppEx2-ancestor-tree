/**
 * Created by Netanel Albert
 * Date: 2020-4 
 */

#include "doctest.h"
#include "FamilyTree.hpp"

using namespace family;

Tree *test_tree(){ // helper function for other tests
    Tree *T  = new Tree("Yosef"); // Yosef is the "root" of the tree (the youngest person).
	CHECK_NOTHROW(T->addFather("Yosef", "Yaakov"));   // Tells the tree that the father of Yosef is Yaakov.
	CHECK_NOTHROW(T->addMother("Yosef", "Rachel"));   // Tells the tree that the mother of Yosef is Rachel.
	CHECK_NOTHROW(T->addFather("Yaakov", "Isaac"));
	CHECK_NOTHROW(T->addMother("Yaakov", "Rivka"));
	CHECK_NOTHROW(T->addFather("Rivka", "Betuel"));
	CHECK_NOTHROW(T->addFather("Isaac", "Avraham"));
	CHECK_NOTHROW(T->addMother("Isaac", "Sara"));
	CHECK_NOTHROW(T->addFather("Avraham", "Terah"));
    
    CHECK_NOTHROW(T->addFather("Rachel", "Lavan"));
    CHECK_NOTHROW(T->addFather("Sara", "Haran"));
    CHECK_NOTHROW(T->addFather("Betuel", "Nahor"));
    CHECK_NOTHROW(T->addMother("Betuel", "Milca")); 

     return T;
}

TEST_CASE("add father") {
   Tree t("Nati");
   CHECK_NOTHROW(t.addFather("Nati", "Nadav"));
   CHECK_NOTHROW(t.addFather("Nadav", "Haim"));
   CHECK(t.find("father") == "Nadav");
   CHECK(t.find("grandfather") == "Haim");

   CHECK_THROWS(t.addFather("Nadav", "Avi")); // Nadav alredy have a father
   CHECK_THROWS(t.addFather("Dani", "Avi")); // Dani not exist
}

TEST_CASE("add mother") {
   Tree t("Nati");
   CHECK_NOTHROW(t.addMother("Nati", "Orit"));
   CHECK_NOTHROW(t.addMother("Orit", "Aliza"));
   CHECK(t.find("mother") == "Orit");
   CHECK(t.find("grandmother") == "Aliza");

   CHECK_THROWS(t.addMother("Orit", "Ruti")); // Orit alredy have a mother
   CHECK_THROWS(t.addMother("Dani", "Ruti")); // Dani not exist

}

TEST_CASE("display") {
    Tree *T = test_tree();
    CHECK_NOTHROW(T->display()); 
    /*
    Need to print:

    Display Yosef tree. Father = up, mother = down.

				            /``Terah
			        /``Avraham
		    /``Isaac
			        \_Sara
	/``Yaakov
			        /``Betuel
		    \_Rivka
Yosef
	\_Rachel

    */

    delete T;
}

TEST_CASE("relation") {
    Tree *T = test_tree();
    CHECK(T->relation("Yosef") == "me");
    CHECK(T->relation("Yaakov") == "father");
    CHECK(T->relation("Isaac") == "grandfather");
    CHECK(T->relation("Avraham") == "great-grandfather");
    CHECK(T->relation("Terah") == "great-great-grandfather");
    CHECK(T->relation("Sara") == "great-grandmother");
    CHECK(T->relation("Rivka") == "grandmother");
    CHECK(T->relation("Betuel") == "great-grandfather");
    CHECK(T->relation("Rachel") == "mother");

    CHECK(T->relation("Lavan") == "grandfather");
    CHECK(T->relation("Haran") == "great-great-grandfather");
    CHECK(T->relation("Nahor") == "great-great-grandfather");
    CHECK(T->relation("Milca") == "great-great-grandmother"); 

    delete T;
}

TEST_CASE("find") {
    Tree *T = test_tree();

    CHECK(T->find("me") == "Yosef"); 
    CHECK(T->find("father") == "Yaakov"); 
    CHECK(T->find("mother") == "Rachel"); 

    string grandfather = T->find("grandfather");
    CHECK((grandfather == "Isaac" ||
           grandfather == "Lavan")); 

    CHECK(T->find("grandmother") == "Rivka");

    string great_grandfather = T->find("great-grandfather"); 
    CHECK((great_grandfather == "Avraham" ||
           great_grandfather == "Betuel")); 

    CHECK(T->find("great-grandmother") == "Sara"); 

    string great_great_grandfather = T->find("great-great-grandfather"); 
    CHECK((great_great_grandfather == "Terah" ||
           great_great_grandfather == "Haran" || 
           great_great_grandfather == "Nahor")); 

    CHECK(T->find("great-great-grandmother") == "Milca"); 
   
    CHECK_THROWS(T->find("brother")); // not define
    CHECK_THROWS(T->find("great-great-great-grandfather")); // not exist
    CHECK_THROWS(T->find("Sara")); // not a rilation
    delete T;
}



TEST_CASE("remove function") {
    Tree *T = test_tree();
    

    CHECK_THROWS(T->remove("Yosef")); // cant remove root
 
    CHECK_THROWS(T->remove("Dani")); // cant remove unexist 

    CHECK(T->remove("Rivka"));

    CHECK_THROWS(T->remove("Betuel")); // already removed (with Rivka)
    
    CHECK(T->relation("Rivka") == "unrelated");

    
    delete T;
}

TEST_CASE("") {
    Tree *T = test_tree();



    delete T;
}