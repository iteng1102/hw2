#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
  set<string> words;
  string trimmed = trim(rawWords); //first trim the word 
  trimmed = convToLower(trimmed); //make them all into lower case 
  stringstream ss(trimmed);
  string all;
  while (ss>>all){
    string temp;
    for (int i = 0; i< all.length(); i++){
      if (ispunct(all[i])){ //find punctuations 
        if (temp.length()>1){
          words.insert(temp); //if word length bigger than 1, add it to word 
          //cout << "inserted " << endl;
        }
        temp.clear();
        //cout << "Cleared " << endl;
      }
      else if (i == all.length()-1 && !ispunct(all[i])){
        temp.push_back(all[i]);
        if (temp.length()>1){ //checks if larger than 1
          words.insert(temp);
        }
      }
      else{
        temp.push_back(all[i]); //if nothing just push the word in 
        //cout << "pushed back " << all[i] << endl;
      }
    }
  }
  return words;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
