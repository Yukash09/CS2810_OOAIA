#include <bits/stdc++.h>

class RollNumber{
public:
    std::string str ;
    void setroll(std::string str){
        this->str = str ;
    }
    
};

class Faculty{

public:
    void Name(std::string name){
        this->name = name ;
    }
    void addBTechProjectee(){
        numBTech += 1;
    }
    void addDDProjectee(){
        numDD += 1 ;
    }
    void addTA(){
        numTA += 1 ;
    }
    int numBTechProjectees(){
        return this->numBTech ;
    }
    int numDDProjectees(){
        return this->numDD ;
    }
    int numTAs(){
        return this->numTA ;
    }

private:
    std::string name ;
    int numBTech = 0 ;
    int numDD = 0 ;
    int numTA = 0 ;
};

class Student{

public:
    Student(RollNumber r , std::string hostel , Faculty facad , float cgpa , bool isBTech){
        this->roll = r ;
        this->hostel = hostel ;
        this->facad = facad ;
        this->cgpa = cgpa ;
        this->isBTech = isBTech ;
    }

    std::string getRoll(){
        return this->roll.str ;
    }

    std::string getHostel(){
        return this->hostel ;
    }

    Faculty getFacad(){
        return this->facad ;
    }

    void changeHostel(std::string hostel){
        this->hostel = hostel ;
    }

private:
    RollNumber roll ;
    std::string hostel ;
    Faculty facad ;
    float cgpa ;
    bool isBTech ;

};


class BTech : public Student{

public:
    void setBTPGuide(Faculty& facad){
        this->BTPGuide = facad ;
    }
    Faculty getBTPGuide(){
        return this->BTPGuide ;
    }

private:
    Faculty BTPGuide ;
};

class DD : public Student{

public:
    void setDDPGuide(Faculty& facad){
        this->DDPGuide = facad ;
    }
    Faculty getDDPGuide(){
        return this->DDPGuide ;
    }
    void setTASupervisor(Faculty& facad){
        this->Supervisor = facad ;
    }
    Faculty getTASupervisor(){
        return this->Supervisor ;
    }

private:
    Faculty DDPGuide ;
    Faculty Supervisor ;
};

class IITM{

public:
    IITM(std::vector<Student>& students , std::vector<Faculty>& faculties){
        this->studentsList = students ;
        this->facultyList = faculties ;
    }
    bool checkConstraints(Faculty& facad){
        int maxTAs = 5 ;
        int maxDD = 2 ;
        int maxBTech = 2 ;
        int numTA = facad.numTAs() ;
        int numBTech = facad.numBTechProjectees() ;
        int numDD = facad.numDDProjectees() ;
        if(numDD > maxDD || numTA > maxTAs || numBTech > maxBTech){
            return false ;
        }
        return true ;
    }
    void printStudentsByRoll(){
        for(auto i : ByRoll){

        }
    }


private:
    std::vector<Student> studentsList ;
    std::vector<Faculty> facultyList ;
    std::multimap<std::string,Student> ByHostel ;
    std::map<std::string,Student> ByRoll ;
    void createRollMap(){
        for(int i = 0 ; i < this->studentsList.size() ; ++i){
            ByRoll[this->studentsList[i].getRoll()] = this->studentsList[i] ;
        }
    }
};

int main(){

}
