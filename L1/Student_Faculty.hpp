#include "RollNumber.hpp"
class Student ;
class Faculty{
public:
    // Faculty(std::string name){
    //     this->name = name ;
    // }
    void isPermanent(bool flag){
        std::cout << "Setting Permanent/Adjunct" << std::endl ;
        this->isAdjunct = !flag ;
    }
    bool isPermanent(){
        std::cout << this->name << " is " << (this->isAdjunct ? "Adjunct " : "Permanent ") << "Faculty "  << std::endl ;
        return !this->isAdjunct ;
    }
    void Name(std::string name){
        std::cout << "Setting Name for Faculty" << std::endl ;
        this->name = name ;
    }
    std::string getName(){
        return this->name;
    }
    void addBTechProjectee(Student*  student){
        std::cout << "Added a BTech Projectee for faculty " << this->name << std::endl ;
        numBTech.push_back(student);
    }
    void addDDProjectee(Student* student){
        std::cout << "Added a DD Projectee for faculty " << this->name << std::endl ;
        numDD.push_back(student) ;
    }
    void addTA(Student* student){
        std::cout << "Added a TA for faculty " << this->name << std::endl ;
        numTA.push_back(student);
    }
    int numBTechProjectees(){
        return this->numBTech.size() ;
    }
    int numDDProjectees(){
        return this->numDD.size() ;
    }
    int numTAs(){
        return this->numTA.size() ;
    }
    std::vector<Student*> getBTech(){
        return this->numBTech ;
    }
    std::vector<Student*> getDD(){
        return this->numDD ;
    }
    bool operator==(Faculty other){
        if(other.name == this->name){
            return true ;
        }
        return false ;
    }

private:
    std::string name ;
    std::vector<Student*> numBTech ;
    std::vector<Student*> numDD ;
    std::vector<Student*> numTA ;
    bool isAdjunct = false ;
};

class Student{

public:
    std::string name ;

    void init(RollNumber r , std::string hostel , Faculty& facad , float cgpa , std::string name , bool isBTech){
        std::cout <<"Initialisation for Student" << std::endl ;
        this->roll = r ;
        this->hostel = hostel ;
        this->facad = facad ;
        this->cgpa = cgpa ;
        this->isBTech = isBTech ;
    }

    std::string getRoll(){
        std::cout << "Roll number of " << this->name << " is " << this->roll.str << std::endl ;
        return this->roll.str ;
    }

    std::string getHostel(){
        std::cout << "Hostel of " << this->name << " is " << this->hostel << std::endl ;
        return this->hostel ;
    }

    Faculty getFacad(){
        std::cout << "Facad of " << this->name << " is " << this->facad.getName() << std::endl ;
        return this->facad ;
    }
    
    bool needGuide(){
        return !hasGuide ;
    }

    void changeHostel(std::string hostel){
        this->hostel = hostel ;
    }

    float getCGPA(){
        std::cout << "CGPA of " << this->name << " is " << this->cgpa << std::endl ;
        return this->cgpa ;
    }

    bool is_BTech(){
        return this->isBTech ;
    }

protected:
    bool isBTech = false ;
    RollNumber roll ;
    std::string hostel ;
    Faculty facad ;
    float cgpa ;
    bool hasGuide = false ;
};

class BTech : public Student{

public:
    BTech(RollNumber r , std::string hostel , Faculty& facad , float cgpa , std::string name , bool isBTech){
        this->init(r ,  hostel , facad ,  cgpa , name , isBTech) ;
    }
    void setBTPGuide(Faculty& facad){
        std::cout << "Setting BTP Guide for " << this->name << std::endl ;
        this->BTPGuide = facad ;
        this->hasGuide = true ;
    }
    Faculty getBTPGuide(){
        return this->BTPGuide ;
    }

private:
    Faculty BTPGuide ;

};

class DD : public Student{

public:
    DD(RollNumber r , std::string hostel , Faculty& facad , float cgpa , std::string name , bool isBTech){
        this->init(r ,  hostel , facad ,  cgpa , name , isBTech) ;
    }
    void setDDPGuide(Faculty& facad){
        std::cout << "Setting DDP Guide for " << this->name << std::endl ;
        this->DDPGuide = facad ;
        this->hasGuide = true ;
    }
    Faculty getDDPGuide(){
        return this->DDPGuide ;
    }
    void setTASupervisor(Faculty& facad){
        std::cout << "Setting TA Supervisor for " << this->name << std::endl ;
        this->Supervisor = facad ;
    }
    Faculty getTASupervisor(){
        return this->Supervisor ;
    }

private:
    Faculty DDPGuide ;
    Faculty Supervisor ;    
};
