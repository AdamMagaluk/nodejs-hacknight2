/* 
 * File:   Dog.h
 * Author: adam
 *
 * Created on September 25, 2012, 7:34 PM
 */

#ifndef DOG_H
#define	DOG_H

#include <string>


class Animal {
public:
    Animal(std::string name) : m_name(name){}
    Animal(const Animal& orig){
        m_name = orig.m_name;
    }
    virtual ~Animal(){}
    
    std::string Name() const{return m_name;}
    
private:
    std::string m_name;
};


class Dog : public Animal{
public:
    Dog(std::string name);
    Dog(const Dog& orig);
    virtual ~Dog();
    
    void move();
private:
};

#endif	/* DOG_H */

