#include <sstream>
#include "clothing.h"
using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, std::string brand, std::string size): 
Product(category, name, price, qty), brand_(brand), size_(size){
 
}

Clothing::~Clothing(){

}
      
set<std::string> Clothing::keywords() const{
  set<string> keyword = parseStringToWords(getName());
  set<string> size = parseStringToWords(size_);
  for(set<string>::iterator it=size.begin(); it != size.end();++it){
    keyword.insert(*it);
  }
  set<string> brandKey = parseStringToWords(brand_);
  for (set<string>::iterator it = brandKey.begin(); it!=brandKey.end(); ++it){
    keyword.insert(*it);
  }
  return keyword;
}

//bool Clothing::isMatch(std::vector<std::string>& searchTerms) const{}


string Clothing::displayString() const{
  stringstream display;
  display << getName() << endl;
  display << "Size: " << size_ << " Brand: " << brand_  << endl;
  display << getPrice() << " " << getQty() << " left." << endl;
  return display.str();
}

void Clothing::dump(std::ostream& os) const{
  os <<category_ << endl;
  os << getName() << endl;
  os << getPrice() << endl;
  os << getQty() << endl;
  os << size_ << endl;
  os << brand_ << endl;

}