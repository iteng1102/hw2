#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include "product.h"
#include "util.h"

class Movie: public Product{
    public:
      Movie(const std::string category, const std::string name, double price, int qty, std::string genre, std::string rating);
      ~Movie() override;
      /**
      * Returns the appropriate keywords that this product should be associated with
      */
      std::set<std::string> keywords() const override;

      /**
      * Allows for a more detailed search beyond simple keywords
      */
      //bool isMatch(std::vector<std::string>& searchTerms) const override;

      /**
      *  Returns a string to display the product info for hits of the search
      */
      std::string displayString() const override;

      /**
      * Outputs the product info in the database format
      */
      void dump(std::ostream& os) const override;


    private:
      std::string genre_;
      std::string rating_;
};

//words in the authors's name and ISBN number