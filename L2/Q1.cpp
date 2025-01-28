#include <bits/stdc++.h>
class Book{

public:
    std::string title ;
    std::string author ;

    Book(std::string title , std::string author , std::string isbn , int cA  , int tC){
        this->title = title ;
        this->author = author ;
        this->isbn = isbn ;
        this->copiesAvailable = cA ;
        this->totalCopies = tC ;
    }

    Book(){
        this->title = "UnknownTitle" ;
        this->author = "UnknownAuthor" ;
        this->isbn = "ISBN" ;
        this->copiesAvailable = 0 ;
        this->totalCopies = 5 ;        
    }

    Book(Book* copyBook , std::string newisbn){
        this->title = copyBook->title ;
        this->author = copyBook->author ;
        this->isbn = newisbn ;
        this->copiesAvailable = copyBook->copiesAvailable ;
        this->totalCopies = copyBook->totalCopies ;        
    }

    std::string getisbn(){
        return this->isbn ;
    }

    int cA(){
        return this->copiesAvailable ;
    }

    int tC(){
        return this->totalCopies ;
    }

    void updateCopies(int n){
        if(n > 0){
            this->copiesAvailable += n ;
            this->totalCopies += n ;
        }
        else{
            if(this->copiesAvailable + n < 0){
                std::cout << "Invalid request! Count becomes negative" << "\n";
            }
            else{
                this->copiesAvailable += n ;
                this->totalCopies += n ;
            }
        }
    }

    bool borrowBook(){
        if(this->copiesAvailable > 0){
            this->copiesAvailable -= 1;
            return true ;
        }
        else{
            std::cout << "Invalid request! Copy of book not available" << "\n";
            return false ;
        }
    }

    bool returnBook(){
        if(this->copiesAvailable < this->totalCopies){
            this->copiesAvailable += 1;
            return true ;
        }
        else{
            std::cout << "Invalid request! Copy of book exceeds total copies" << "\n";
            return false ;
        }        
    }

    void printDetails(){
        std::cout << this->title << " " << this->author << "\n";
    }

private:
    std::string isbn ;
    int copiesAvailable ;
    int totalCopies ;
};

class Member{

public:
    std::string name ;

    Member(std::string name , std::string memberID , int borrowLimit){
        this->name = name ;
        this->memberID = memberID ;
        this->borrowLimit = borrowLimit ;
    }

    Member(std::string name , std::string memberID){
        this->name = name ;
        this->memberID = memberID ;
    }

    bool borrowBook(std::string isbn){
        if(this->borrowedCurr >= this->borrowLimit){
            std::cout << "Invalid request! Borrow limit exceeded" << "\n";
            return false ;
        }
        else{
            // need to update this from book side
            this->borrowedBooks[isbn] += 1 ;
            this->borrowedCurr++ ;
            return true ;
        }
    }
            // need to update this from book side
    bool returnBook(std::string isbn){
        if(this->borrowedBooks[isbn] <= 0){
            std::cout << "Invalid request! Book not borrowed" << "\n";
            return false ;
        }
        else{
            // need to update this from book side
            this->borrowedBooks[isbn] -= 1 ;
            this->borrowedCurr-- ;
            return true ;
        }
    }

    std::string getmemberID(){
        return this->memberID ;
    }

    void printDetails(){
        for(auto i : this->borrowedBooks){
            if(i.second != 0){
                std::cout << this->memberID << " " << this->name << " " << i.first << " " << i.second << "\n" ;
            }
        }
    }

private:
    std::string memberID ;
    int borrowLimit = 3;
    int borrowedCurr = 0 ;
    std::map<std::string , int> borrowedBooks ;
} ;

class Library{

public:
    bool addBook(Book* book){
        for(int i = 0 ; i < (int)this->books.size() ; ++i){
            if(book->getisbn() == this->books[i]->getisbn()){
                std::cout << "Invalid request! Book with same isbn already exists" << "\n";
                return false ;
            }
        }
        this->books.push_back(book);
        return true ;
    }

    bool registerMember(Member* member){
        for(int i = 0 ; i < (int)this->members.size() ; ++i){
            if(member->getmemberID() == this->members[i]->getmemberID()){
                std::cout << "Invalid request! Member with same id already exists" << "\n";
                return false ;
            }
        }
        this->members.push_back(member) ;
        return true ;
    }

    bool borrowBook(std::string memberID , std::string isbn){
        int bookindex = 0 ;
        for(int i = 0 ; i < (int)this->books.size() ; ++i){
            if(isbn == this->books[i]->getisbn()){
                break ;
            }
            bookindex++ ;
        }
        int memindex = 0 ;
        for(int i = 0 ; i < (int)this->books.size() ; ++i){
            if(memberID == this->members[i]->getmemberID()){
                break ;
            }
            memindex++ ;
        }        
        bool avail = this->books[bookindex]->borrowBook() ;
        if(avail){
            bool limit = this->members[memindex]->borrowBook(isbn) ;
            if(limit){
                return true ;
            }
            else{
                this->books[bookindex]->returnBook() ;
                return false ;
            }
        }
        else{
            return false ;
        }
    }

    bool returnBook(std::string memberID , std::string isbn){
        int bookindex = 0 ;
        for(int i = 0 ; i < (int)this->books.size() ; ++i){
            if(isbn == this->books[i]->getisbn()){
                break ;
            }
            bookindex++ ;
        }
        int memindex = 0 ;
        for(int i = 0 ; i < (int)this->books.size() ; ++i){
            if(memberID == this->members[i]->getmemberID()){
                break ;
            }
            memindex++ ;
        } 
        bool isposs = this->books[bookindex]->returnBook() ;
        if(isposs){
            bool canreturn = this->members[memindex]->returnBook(isbn) ;
            if(canreturn){
                return true ;
            }
            else{
                this->books[bookindex]->borrowBook() ;
            }
        }
        return false ;
    }

    Book* getBook(std::string isbn){
        for(int i = 0 ; i < (int)this->books.size() ; ++i){
            if(isbn == this->books[i]->getisbn()){
                return this->books[i] ;
            }
        }   
        return this->books[0] ;    
    }

    Member* getMem(std::string memID){
        for(int i = 0 ; i < (int)this->members.size() ; ++i){
            if(memID == this->members[i]->getmemberID()){
                return this->members[i] ;
            }
        }  
        return this->members[0] ;           
    }

    void printLibraryDetails(){
        for(int i = 0 ; i < (int)this->books.size() ; ++i){
            std::cout << this->books[i]->title << " " << this->books[i]->author << " " << this->books[i]->cA() << "\n";
        }
        for(int i = 0 ; i < (int)this->members.size() ; ++i){
            std::cout << this->members[i]->getmemberID() << " " << this->members[i]->name << "\n";
        }
    }


private:
    std::vector<Book*> books ;
    std::vector<Member*> members;
};

int main(){
    std::vector<std::string> operations = {"Book" , "UpdateCopiesCount" , "Member" , "Borrow" , "Return" , "PrintBook" , "PrintMember" , "PrintLibrary" , "Done"};
    Library IITM ;
    while(true){
        std::string s ; 
        std::cin >> s ;
        if(s == operations[0]){
            std::string typ ; std::cin >> typ ;
            if(typ == "ExisitingBook" || typ == "ExistingBook"){
                std::string oldisbn , newisbn ;
                std::cin >> oldisbn >> newisbn ;
                Book* oldbook = IITM.getBook(oldisbn) ;
                Book* newbook = new Book(oldbook , newisbn) ;
                bool flag = IITM.addBook(newbook) ;
                if(!flag){
                    delete newbook ;
                }
            }
            else if(typ == "None"){
                Book* newbk = new Book ;
                bool flag = IITM.addBook(newbk) ;
                if(!flag){
                    delete newbk ;
                }
            }
            else{
                std::string author , isbn ; int cA ; int tC ;
                std::cin >> author >> isbn >> cA >> tC ;
                Book* newb = new Book(typ , author , isbn , cA , tC);
                bool flag = IITM.addBook(newb) ;
                if(!flag){
                    delete newb ;
                }
            }
        }
        if(s == operations[1]){
            std::string isbn ;
            int newcount ;
            std::cin >> isbn >> newcount ;
            Book* book = IITM.getBook(isbn) ;
            book->updateCopies(newcount) ;
        }
        if(s == operations[2]){
            std::string typ ; 
            std::cin >> typ ;
            if(typ == "NoBorrowLimit"){
                std::string memberID , name ;
                std::cin >> memberID >> name ;
                Member* newmem = new Member(name , memberID) ;
                bool flag = IITM.registerMember(newmem);
                if(!flag){
                    delete newmem ;
                }
            }
            else{
                std::string name ; int blimit ;
                std::cin >> name >> blimit ;
                Member* newm = new Member(name , typ , blimit);
                bool flag = IITM.registerMember(newm) ;
                if(!flag){
                    delete newm ;
                }
            }
        }
        if(s == operations[3]){
            std::string memID , isbn  ;
            std::cin >> memID >> isbn ;
            IITM.borrowBook(memID , isbn) ;
        }
        if(s == operations[4]){
            std::string memID , isbn ;
            std::cin >> memID >> isbn ;
            IITM.returnBook(memID , isbn) ;            
        }
        if(s == operations[5]){
            std::string isbn ; 
            std::cin >> isbn ;
            Book* book = IITM.getBook(isbn) ;
            book->printDetails() ;
        }
        if(s == operations[6]){
            std::string memID ; 
            std::cin >> memID ;
            Member* mem = IITM.getMem(memID) ;
            mem->printDetails() ;
        }
        if(s == operations[7]){
            IITM.printLibraryDetails() ;
        }
        if(s == operations[8]){
            return  0 ;
        }
        std::getline(std::cin , s) ;
    }
}
