
#ifndef SEM2LAB2_PERSON_H
#define SEM2LAB2_PERSON_H

#include <string>
class Person {
public:
    int id;
    std::string firstName;
    std::string lastName;

    Person(int id = INT_MAX,std::string firstName = "" ,std::string lastName = "" ){
        this->id = id;
        this->firstName = firstName;
        this->lastName = lastName;
    }

    bool operator ==(Person other){
        return this->id == other.id;
    }

    bool  operator!=(Person other){
        return this->id != other.id;
    }

    std::string ToString(){
        return  firstName +" " + lastName + " " +  std::to_string(id);
    }
};
#endif //SEM2LAB2_PERSON_H
