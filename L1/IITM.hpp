#include "Student_Faculty.hpp"
class IITM{

public:
    IITM(std::vector<BTech>& BTechs , std::vector<DD>& DDs , std::vector<Faculty>& faculties){
        std::cout << "Constructor for IITM" << std::endl ;
        this->BTechList = BTechs ;
        this->DDList = DDs ;
        this->facultyList = faculties ;
    }
    bool checkConstraints(Faculty& facad){
        std::cout << "Checking constraints" << std::endl ;
        int maxTAs = 5 ;
        int maxDD = 2 ;
        int maxBTech = 2 ;
        int numTA = facad.numTAs() ;
        int numBTech = facad.numBTechProjectees() ;
        int numDD = facad.numDDProjectees() ;
        if(numDD >= maxDD || numTA >= maxTAs || numBTech >= maxBTech){
            return false ;
        }
        return true ;
    }
    void printStudentsByRoll(){
        std::cout << "Students by Roll Number" << std::endl ;
        for(auto i : ByRoll){
            std::cout << i.first << " " << i.second.name << std::endl ;
        }
    }
    void printStudentsByHostel(){
        std::cout << "Students by Hostel" << std::endl ;
        for(auto i : this->ByHostel){
            std::cout << i.first << " " << i.second.name << std::endl ;
        }
    }
    void printStudentsByGuide(){
        std::cout << "Students by Guide" << std::endl ;
        for(auto i : this->ByGuide){
            std::cout << i.first << " " << i.second.name  << std::endl ;
        }
    }
    void printStudentsUnassigned(){
        std::cout << "Unassigned Students" << std::endl ;
        for(int i = 0 ; i < this->BTechList.size() ; ++i){
            if(this->BTechList[i].needGuide()){
                std::cout << this->BTechList[i].name ;
            }
        }
        for(int i = 0 ; i < this->DDList.size() ; ++i){
            if(this->DDList[i].needGuide()){
                std::cout << this->DDList[i].name ;
            }
        }
    }
    Faculty maxProjectees(){
        Faculty maxx = this->facultyList[0] ;
        int maxnum = -1 ;
        for(int i = 0 ; i < this->facultyList.size() ; ++i){
            std::vector<Student*> BTechstudents = this->facultyList[i].getBTech();
            std::vector<Student*> DDstudents = this->facultyList[i].getDD() ;
            std::map<std::string,int> freq ;
            for(int j = 0 ; j < BTechstudents.size() ; j++){
                Student* student = BTechstudents[j] ;
                std::string hostel = student->getHostel();
                freq[hostel] += 1 ;
            }
            for(int j = 0 ; j < DDstudents.size() ; j++){
                Student* student = DDstudents[j] ;
                std::string hostel = student->getHostel();
                freq[hostel] += 1 ;
            }
            int cur = freq.size() ;
            if(cur > maxnum){
                maxx = this->facultyList[i] ;
                maxnum = cur ;
            }
        }
        std::cout << "Faculty with maximum students from different hostels " << maxx.getName() << std::endl ;
        return maxx ;
    }
    float percentageStudents(){
        int count = 0 ; 
        for(int i = 0 ; i < this->DDList.size() ; ++i){
            DD student = this->DDList[i] ;
            Faculty DDP = student.getDDPGuide() ;
            Faculty TA = student.getTASupervisor() ;
            if(TA == DDP){
                count++ ;
            }
        }
        float percentage = (float)(count)/DDList.size() ;
        std::cout << "Percentage of students with DDP Guide same as TA Supervisor " << percentage*100 << std::endl ;
        return percentage*100 ;
    }
    void printDDgnHostelFaculty(std::string hostel , Faculty facad){
        std::cout << "DD students with faculty " << facad.getName() << " in hostel " << hostel << std::endl ;
        for(int i = 0 ; i <  this->DDList.size() ; ++i){
            DD student = this->DDList[i] ;
            if(student.getHostel() == hostel){
                if(student.getDDPGuide() == facad || student.getTASupervisor() == facad){
                    std::cout << student.name << std::endl ;
                }
            }
        }
    }
    std::multimap<float,BTech,std::greater<float>> getCGPAmap(){
        return this->ByCGPA ;
    }

    std::multimap<std::string,Student> getHostelmap(){
        return this->ByHostel ;
    }
    std::multimap<std::string,DD> getHostelDDmap(){
        return this->ByHostelDD ;
    } 


private:
    std::vector<BTech> BTechList ;
    std::vector<DD> DDList ;
    std::vector<Faculty> facultyList ;
    std::multimap<std::string,Student> ByHostel ;
    std::map<std::string,Student> ByRoll ;
    std::multimap<std::string,Student> ByGuide ;
    std::multimap<float,BTech, std::greater<float>> ByCGPA ;
    std::multimap<std::string,DD> ByHostelDD ;

    void createMaps(){
        std::cout << "Creating Maps for Students" << std::endl ;
        for(int i = 0 ; i < this->BTechList.size() ; ++i){
            ByRoll[this->BTechList[i].getRoll()] = this->BTechList[i] ;
            ByHostel.insert({this->BTechList[i].getHostel(), this->BTechList[i]}) ;
            ByGuide.insert({this->BTechList[i].getFacad().getName() , this->BTechList[i]});
            ByCGPA.insert({this->BTechList[i].getCGPA() , this->BTechList[i]}) ;
        }
        for(int i = 0 ; i < this->DDList.size() ; ++i){
            ByRoll[this->DDList[i].getRoll()] = this->DDList[i] ;
            ByHostel.insert({this->DDList[i].getHostel(), this->DDList[i]}) ;
            ByGuide.insert({this->DDList[i].getFacad().getName() , this->DDList[i]});  
            ByHostelDD.insert({this->DDList[i].getHostel() , this->DDList[i]}) ;        
        }
    }

};
