#ifndef LIBCONFC_H
#define LIBCONFC_H

#include <string>

using namespace std;

class confc {
   private:
      struct conft {   
         string key;
         string value;
         struct conft *next;
      };
      conft *cfg;

   public:
      confc();
      int load(string file_name);
      int save(string file_name);
      int setval(string key, string value);
      int add1st(string key, string value);
      string getval(string key);
      void print();
      void remove(string key);
      int checkval(string key, string value);
      ~confc();      
};

#endif
