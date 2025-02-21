#include "mydatastore.h"
#include "util.h"
#include <map>
using namespace std; 

MyDataStore::~MyDataStore()
{
    for (set<Product*>::iterator it = allProduct.begin(); it!=allProduct.end(); ++it){
      delete *it; //deletes the allproduct set
    }
    allProduct.clear();
    for (User* user: userList){ //deletes pointers from the userList set 
      delete user;
    }
    userList.clear();
}

        /**
        * Adds a product to the data store
        */
void MyDataStore::addProduct(Product* p)
{
    if (!p){
      return;
    }
    allProduct.insert(p); //adds product to allProduct vector 
    const set<string> keyterms = p->keywords();
    for(const string keyword: keyterms){
      keyProduct[keyword].insert(p); //adds all the products with the same keyword to map
      //cout << "keyproduct added " << p->getName() <<endl;
    }
}

        /**
        * Adds a user to the data store
        */
void MyDataStore::addUser(User* u)
{
    if (u == nullptr){
      return;
    }
    userList.push_back(u); //adds user to list
    shoppingCart[u->getName()]; //adds user as keyword to shopping cart 
}


std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type)
{
    set<string> term(terms.begin(), terms.end());
    set<Product*> result;
    set<string> intersection;
    bool firstterm = true; 
    /*for (map<string, set<Product*>>::iterator it1 = keyProduct.begin(); it1!=keyProduct.end(); ++it1){
      cout << "keywords inside " << it1->first << endl;
      for (Product* p:it1->second){
        cout << "product inside" << p->getName() <<endl;
      }
    }*/
    for (set<string>::iterator it = term.begin(); it!=term.end(); ++it){ //goes through each term 
      map<string, set<Product*>>::iterator it1 = keyProduct.find(*it); //finds if term is a keyword 
      //cout <<"term is " << *it <<endl;
      if (it1==keyProduct.end()){
        continue; //continue to next term if not keyword 
      }
      if (firstterm==true){ //if first term found, add 
        result = keyProduct[*it];
        firstterm = false;
        //cout << "first term added" << endl;
      }
      else{
        if (type == 0){ //if search is and, use intersection between first term and second terms 
          result = setIntersection(it1->second, result);
        }
        else {
          result = setUnion(result, it1->second); //use union otherwise
        }
      }
    }
    vector<Product*> searchVector(result.begin(), result.end()); //changes set to vector for hit 
    return searchVector;
}

        
void MyDataStore::dump(std::ostream& ofile){
    ofile << "<products>" << endl;
    for (Product* product: allProduct){
      product->dump(ofile); //goes through each product's dump
    }
    ofile << "</products>" << endl;
    ofile << "<users>" << endl;
    for (User* user: userList){
      user->dump(ofile); //goes through each user's dump 
    }
    ofile << "</users>" << endl;
}

void MyDataStore::viewCart(std::string username){
    vector<Product*> cart;
    map<string, vector<Product*>>::iterator it = shoppingCart.find(username);
    if (it!=shoppingCart.end()){
      cart = it->second; //adds all the products from the user to a cart 
    }
    else{
        cout << "Invalid username" << endl;
    }
    for (int i = 0; i<cart.size(); i++){
      cout << "Item " << i+1 << " " << endl;
      cout << cart[i]->displayString() << endl; //print out all items from cart 
    }
}

void MyDataStore::addCart(std::string username, std::vector<Product*> list, int hitIndex){
    map<string, vector<Product*>>::iterator it = shoppingCart.find(username);
    if (it == shoppingCart.end()||hitIndex>list.size()||hitIndex<0){
      cout << "Invalid request" << endl;
      return;
    }
    else{
      it->second.push_back(list[hitIndex-1]); //adds product to user's vector list 
    }
}

void MyDataStore::buyCart(std::string username){
    vector<Product*> remainCart = shoppingCart[username]; //sets the remain cart to user's cart 
    vector<Product*> newCart;
    User* currentUser = nullptr;
    for (User* user:userList){ //goes through each user and if it's the one we want, change it to the current user 
      if (user->getName()==username){
        currentUser = user;
        break;
      }
    }

    if (currentUser==nullptr){
      cout << "Invalid username" << endl;
      return;
    }

    for (int i = 0; i< remainCart.size(); i++){
      if (remainCart[i]->getQty()>0 && remainCart[i]->getPrice()<=currentUser->getBalance()){
        remainCart[i]->subtractQty(1); //subtracts quantity from cart 
        currentUser->deductAmount(remainCart[i]->getPrice()); //subtracts price from balance 
      }
      else{
        newCart.push_back(remainCart[i]); //push the ones untouched into remaining cart 
      }
    }
    shoppingCart[username] = newCart; //adds new cart to the user's current cart after check out 
}