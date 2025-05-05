#include <iostream>
#include "libconfc.h"

int main(int argc, char **argv)
{
    if(argc < 2) {
	    cout << "Error: config file not specified\nUsage: " << argv[0] << " initial.conf\n";
	    return 1;
    }

    confc cfg;
    string arg1 = argv[1];
    if(!cfg.load(arg1)) {
    	cout << "Error loading config file\n";
	    return 1;
    }

    cout << "\nTest 1: print initial config\n";
    cfg.print();
    
    cout << "\nTest 2: print only 'ip' and 'mac' key-value:\n";
    string val = cfg.getval("ip");
    if(val != "") cout << "ip =" << val << "\n";
    val = cfg.getval("mac");
    if(val != "") cout << "mac =" << val << "\n";;
    
    cout << "\nTest 3: remove key 'gateway' and print full config\n";
    cfg.remove("gateway");
    cfg.print();
    
    cout << "\nTest 4: remove last key and print full config\n";
    cfg.remove("hostname");
    cfg.print();
    
    cout << "\nTest 5: remove first key and print full config\n";
    cfg.remove("interface");
    cfg.print();

    cout << "\nTest 6: check if key 'interface' exists\n";
    val = cfg.getval("interface");
    val == "" ? cout << "'interface' does not exist\n" : cout << "'interface' does exist. val = "<< val << "\n";
	
    cout << "\nTest 7: check if key 'mac' exists\n";
    val = cfg.getval("mac");
    val == "" ? cout << "'mac' does not exist\n" : cout << "'mac' does exist. val = " << val << "\n";

    cout << "\nTest 8: check if key 'mac' = 'f0:19:54:27:7d:ab'\n";
    int chk = cfg.checkval("mac", "f0:79:59:67:7d:ad");
    cout << (chk ? "true" : "false") << "\n";

    cout << "\nTest 9: check if key 'mac' = 'a3:b1:cd:d7:e9:f5'\n";
    chk = cfg.checkval("mac", "a3:b1:cd:d7:e9:f5");
    cout << (chk ? "true" : "false") << "\n";

    cout << "\nTest 10: add new key 'domain1' to the bottom of config\n";
    cfg.setval("domain1", "last.org");
    cfg.print();

    cout << "\nTest 11: add new key 'domain0' to the top of config\n";
    cfg.add1st("domain0", "first.org");
    cfg.print();

    cout << "\nTest 12: update 'IP' value\n";
    cfg.setval("ip", "1.1.1.1");
    cfg.print();

    cout << "\nTest 13: save modified config to 'modded.conf'\n";
    int ret = cfg.save("modded.conf");
    if(!ret) {
    	cout << "Error: could not write file\n";
	    return 1;
    } else if(ret == -1) {
        cout << "Error: file already exists\n";
        return 1;
    }
    cout << "Done!\n";
}
