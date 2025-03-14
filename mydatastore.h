#include <string>
#include <set>
#include <vector>
#include <map>
#include "datastore.h"


class MyDataStore: public DataStore{
    public:
        ~MyDataStore();

        /**
        * Adds a product to the data store
        */
        void addProduct(Product* p);

        /**
        * Adds a user to the data store
        */
        void addUser(User* u);

        /**
        * Performs a search of products whose keywords match the given "terms"
        *  type 0 = AND search (intersection of results for each term) while
        *  type 1 = OR search (union of results for each term)
        */
        std::vector<Product*> search(std::vector<std::string>& terms, int type);

        /**
        * Reproduce the database file from the current Products and User values
        */
        void dump(std::ostream& ofile);

        //ADD username search_hit_number " << endl;
        void addCart(std::string username, std::vector<Product*> list, int hitIndex);

        //cout << "  VIEWCART username                  " << endl;
        void viewCart(std::string username);
        //cout << "  BUYCART username   
        void buyCart(std::string username);


    private:
        std::vector<User*> userList;
        std::set<Product*> allProduct;
        std::map<std::string, std::vector<Product*>> shoppingCart; 
        std::map<std::string, std::set<Product*>> keyProduct; 

};
