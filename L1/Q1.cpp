// https://github.com/Yukash09/CS2810_OOAIA
#include "IITM.hpp"
int main(){
    srand(time(0)) ;
    int N , M ;
    std::vector<BTech> BTechList ;
    std::vector<DD> DDList ;
    std::vector<Faculty> facultyList ;
    int numHostels = 7 ;
    std::vector<std::string> Hostels = {"Mandakini" , "Cauvery" , "Krishna" , "Narmada" , "Tapti" , "Brahmaputra" , "Thamirabarani"} ;
    for(int i = 0 ; i < M ; ++i){
        int namelen = rand()%15 ;
        std::string name = "" ;
        for(int i = 0 ; i < namelen ; i++){
            int charnum = rand()%26 ;
            name += ('a' + charnum) ;
        }        
        bool isPermanent = (rand()%2 == 0 ? false : true) ;
        Faculty f1 ;
        f1.Name(name) ;
        f1.isPermanent(isPermanent) ;
        facultyList.push_back(f1) ;
    }

    for(int i = 0 ; i < N ; ++i){
        int namelen = rand()%15 ;
        std::string name = "" ;
        RollNumber r  ;
        for(int i = 0 ; i < namelen ; i++){
            int charnum = rand()%26 ;
            name += ('a' + charnum) ;
        }
        r.setroll(name) ;
        Faculty facad = facultyList[rand()%M];
        std::string hostel = Hostels[rand()%numHostels] ;
        float cgpa = ((float)rand()/RAND_MAX)*10 ;
        bool isBTech = (rand()%2 == 0 ? false : true) ;
        if(isBTech){
            BTech b1(r , hostel , facad , cgpa , name , isBTech) ;
            BTechList.push_back(b1) ;
        }
        else{
            DD d1(r , hostel , facad , cgpa , name , isBTech);
            DDList.push_back(d1) ;
        }
    }

    IITM CS(BTechList , DDList , facultyList) ;

    for(int i = 0 ; i < DDList.size() ; ++i){
        int rndm = rand()%M ;
        if(facultyList[rndm].numTAs() < 5){
            DDList[i].setTASupervisor(facultyList[rndm]) ;
            facultyList[rndm].addTA(&DDList[i]);            
        }

    }

    std::multimap<float,BTech, std::greater<float>> ByCGPA = CS.getCGPAmap()  ;
    int ptr = 0 ;
    for(auto i : ByCGPA){
        if(ptr >= M){
            break ;
        }
        else{
            if(facultyList[ptr].numBTechProjectees() < 2 && facultyList[ptr].isPermanent()){
                i.second.setBTPGuide(facultyList[ptr]) ;
                facultyList[ptr].addBTechProjectee(&i.second) ;
            }
            else{
                ptr++ ;
            }
        }
    }
    std::multimap<std::string , DD> ByHostelDD = CS.getHostelDDmap() ;
    ptr = 0 ;
    for(auto i : ByHostelDD){
        if(ptr >= M){
            break ;
        }
        else{
            if(facultyList[ptr].numDDProjectees() < 2 && facultyList[ptr].isPermanent()){
                i.second.setDDPGuide(facultyList[ptr]);
                facultyList[ptr].addDDProjectee(&i.second);
            }
            else{
                ptr++;
            }
        }
    }

}