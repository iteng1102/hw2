#include <sstream>
#include "book.h"
using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty, std::string author, std::string isbn): 
Product(category, name, price, qty), author_(author), isbn_(isbn){

}

Book::~Book(){

}
      
set<std::string> Book::keywords() const{
  set<string> keyword = parseStringToWords(getName());
  keyword.insert(isbn_);
  set<string> author = parseStringToWords(author_); 
  for(set<string>::iterator it=author.begin(); it != author.end();++it){
    keyword.insert(*it);
  }
  //parse all the words before adding them to keyword 
  return keyword;
}

//bool Book::isMatch(std::vector<std::string>& searchTerms) const{}


string Book::displayString() const{
  stringstream display;
  display << getName() << endl;
  display << "Author: " << author_ << " ISBN: " << isbn_  << endl;
  display << getPrice() << " " << getQty() << " left." << endl;
  return display.str();
}

void Book::dump(std::ostream& os) const{
  os << category_ << endl; //adds all data to ostream 
  os  << getName() << endl;
  os  << getPrice() << endl;
  os  << getQty() << endl;
  os  << isbn_ << endl;
  os  << author_ << endl;
}