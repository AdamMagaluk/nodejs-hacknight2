/* 
 * File:   Dog.cpp
 * Author: adam
 * 
 * Created on September 25, 2012, 7:34 PM
 */
#include <iostream>s
#include "Dog.h"

Dog::Dog(std::string name) : Animal(name) {
    std::cout << "Dog (" << Name() << ") is born." << std::endl; 
}

Dog::Dog(const Dog& orig) : Animal(orig) {
}

Dog::~Dog() {
    std::cout << "Dog (" << Name() << ") died." << std::endl; 
}

void Dog::move(){
    std::cout << "Dog (" << Name() << ") is moving." << std::endl; 
}