#include <sstream>
#include "movie.h"
using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, int qty, std::string genre, std::string rating): 
Product(category, name, price, qty), genre_(genre), rating_(rating){
 
}

Movie::~Movie(){

}
      
set<std::string> Movie::keywords() const{
  set<string> keyword = parseStringToWords(getName());
  set<string> genre = parseStringToWords(genre_);
  for(set<string>::iterator it=genre.begin(); it != genre.end();++it){
    keyword.insert(*it);
  }
  return keyword;
}

//bool Movie::isMatch(std::vector<std::string>& searchTerms) const{}


string Movie::displayString() const{
  stringstream display;
  display << getName() << endl;
  display << "Genre: " << genre_ << " Rating: " << rating_ << endl;
  display << getPrice() << " " << getQty() << " left." << endl;
  return display.str();

}

void Movie::dump(std::ostream& os) const{
  os << category_ << endl;
  os  << getName() << endl;
  os  << getPrice() << endl;
  os << getQty() << endl;
  os  << genre_ << endl;
  os  << rating_ << endl;
}

