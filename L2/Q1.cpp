#include <bits/stdc++.h>

class Book{

public:
    std::string title ;
    std::string author ;

    Book(std::string title="UnknownTitle" , std::string author="UnknownAuthor" , std::string isbn="ISBN" , int cA = 0 , int tC = 5){
        this->title = title ;
        this->author = author ;
        this->isbn = isbn ;
        this->copiesAvailable = cA ;
        this->totalCopies = tC ;
    }

    Book(Book& copyBook , std::string newisbn){
        this->title = copyBook.title ;
        this->author = copyBook.author ;
        this->isbn = newisbn ;
        this->copiesAvailable = copyBook.copiesAvailable ;
        this->totalCopies = copyBook.totalCopies ;        
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
                std::cout << "Invalid request! Count becomes negative" << std::endl ;
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
            std::cout << "Invalid request! Copy of book not available" << std::endl ;
            return false ;
        }
    }

    bool returnBook(){
        if(this->copiesAvailable < this->totalCopies){
            this->copiesAvailable += 1;
            return true ;
        }
        else{
            std::cout << "Invalid request! Copy of book exceeds total copies" << std::endl ;
            return false ;
        }        
    }

    void printDetails(){
        std::cout << this->title << " " << this->author << std::endl ;
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
            std::cout << "Invalid request! Borrow limit exceeded" << std::endl ;
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
            std::cout << "Invalid request! Book not Borrowed" << std::endl ;
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
            std::cout << this->memberID << " " << this->name << " " << i.first << " " << i.second ;
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
        for(int i = 0 ; i < this->books.size() ; ++i){
            if(book->getisbn() == this->books[i]->getisbn()){
                std::cout << "Invalid request! Book with same isbn already exists" << std::endl ;
                return false ;
            }
        }
        this->books.push_back(book);
        return true ;
    }

    bool registerMember(Member* member){
        for(int i = 0 ; i < this->members.size() ; ++i){
            if(member->getmemberID() == this->members[i]->getmemberID()){
                std::cout << "Invalid request! Member with same id already exists" << std::endl ;
                return false ;
            }
        }
        this->members.push_back(member) ;
        return true ;
    }

    bool borrowBook(std::string memberID , std::string isbn){
        int bookindex = 0 ;
        for(int i = 0 ; i < this->books.size() ; ++i){
            if(isbn == this->books[i]->getisbn()){
                break ;
            }
            bookindex++ ;
        }
        int memindex = 0 ;
        for(int i = 0 ; i < this->books.size() ; ++i){
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
        for(int i = 0 ; i < this->books.size() ; ++i){
            if(isbn == this->books[i]->getisbn()){
                break ;
            }
            bookindex++ ;
        }
        int memindex = 0 ;
        for(int i = 0 ; i < this->books.size() ; ++i){
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
        else{
            return false ;
        }   
    }

    Book* getBook(std::string isbn){
        for(int i = 0 ; i < this->books.size() ; ++i){
            if(isbn == this->books[i]->getisbn()){
                return this->books[i] ;
            }
        }       
    }

    void printLibraryDetails(){
        for(int i = 0 ; i < this->books.size() ; ++i){
            std::cout << this->books[i]->title << " " << this->books[i]->author << " " << this->books[i]->cA() << std::endl ;
        }
        for(int i = 0 ; i < this->members.size() ; ++i){
            std::cout << this->members[i]->getmemberID() << " " << this->members[i]->name << std::endl ;
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
        std::string s ; std::cin >> s ;
        if(s == operations[0]){
            std::string typ ; std::cin >> typ ;
            if(typ == "ExistingBook"){
                std::string oldisbn , newisbn ;
                std::cin >> oldisbn >> newisbn ;
                Book* oldbook = IITM.getBook(oldisbn) ;
                Book newbook(*oldbook , newisbn) ;
                IITM.addBook(&newbook) ;
            }
            else if(typ == "None"){
                Book newbook ;
                IITM.addBook(&newbook) ;
            }
            else{
                std::string author , isbn ; int cA ; int tC ;
                std::cin >> author >> isbn >> cA >> tC ;
                Book newbook(typ , author , isbn , cA , tC);
                IITM.addBook(&newbook) ;
            }
        }
    }
}