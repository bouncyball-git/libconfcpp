#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "libconfc.h"

template <char C>
istream& expect(istream& in) {
    if ((in >> ws).peek() == C) {
        in.ignore();
    }
    else {
        in.setstate(ios_base::failbit);
    }
    return in;
}

confc::confc()
{
    cfg = new (std::nothrow) conft;
    if(!cfg) exit(1);
    cfg->key = "";
    cfg->value = "";
    cfg->next = NULL;
}

// initialize first element, update or add config element to the end of chain
int confc::setval(string key, string value)
{
    // case 1: set first key-value
    if(cfg->key == "")
    {
        cfg->key = key;
        cfg->value = value;
        return 1;
    }

    conft *c;
    for(c = cfg ; ; c = c->next)
    {
        // case 2: key matched, update value
        if(c->key == key)
        {
            c->value = value;
            return 1;
        }

	    // case 3: key not matched and this is last struct, add new struct to the end of the chain
        if(c->next == NULL)
        {
            c->next = new (std::nothrow) conft;
            if(!c->next) return 0;
            c = c->next;
            c->key = key;
            c->value = value;
            c->next = NULL;
            return 1;
        }
    }
}

// get value by key
string confc::getval(string key)
{
    conft *c;
    for(c = cfg; c != NULL; c = c->next)
    {
        if(c->key == key) {
            return c->value;
        }
    }
    return "";
}

// remove config element from chain
void confc::remove(string key)
{
    conft *c, *cp = cfg;
    for(c = cfg; c != NULL; c = c->next)
    {
        if(c->key == key) {
	        if(c == cfg) cfg = c->next;
	        cp->next = c->next;
    	    delete(c); c = NULL;
	        return;
        }
        cp = c;
    }
}

// load config from file
int confc::load(string file_name)
{
    string line, key, value;

    ifstream f(file_name);
    if(!f) return 0;

    int read_ok = 0;
    while(getline(f, line))
    {
        if (line.empty() || line[0] == '#') continue;
        std::istringstream in(line);
        if (!(in >> key >> expect<'='> >> value)) continue;
        if(!setval(key, value)) continue;
        read_ok = 1;
    }
    f.close();
    return read_ok ? 1 : 0;
}

// save config to file
int confc::save(string file_name)
{
    ifstream f(file_name);
    if(!f)
    {
        ofstream f(file_name);
        if(!f) return 0;

        conft *c;
        for(c = cfg; c != NULL; c = c->next)
        {
            f << c->key << " = " << c->value << "\n";
        }
        f.close();
        return 1;
    }
    return -1;
}

// debug: print all elements of config
void confc::print()
{
    conft * ct = cfg;
    do {
        cout << ct->key << "=" << ct->value << "\n";
        ct = ct->next;
    } while(ct != NULL);
}

// check if value matches or key exists
int confc::checkval(string key, string value)
{
    string val = getval(key);
    // if there is no such key
    if(val == "") return 0;
    // if value matches
    if(val == value) return 1;
    // otherwise
    return 0;
}

// adds config element to the beginning of chain
int confc::add1st(string key, string value)
{
    conft *c = new (std::nothrow) conft;
    if(!c) return 0;
    c->key = key;
    c->value = value;
    c->next = cfg;
    cfg = c;
    return 1;
}

// deletes whole config from memory
confc::~confc()
{
    conft *c = cfg, *ct;
    do {
        ct = c;
        c = c->next;
        ct->key = "";
        ct->value = "";
        delete(ct); ct = NULL;
    } while (c != NULL);
}
