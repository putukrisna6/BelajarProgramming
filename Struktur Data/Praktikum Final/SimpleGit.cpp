#include <iostream>
#include <cstdio>
#include <string>
#include <map>
#include <list>
#include <queue>

using namespace std;

enum StringValue {
    evCommit, \
    evReset, \
    evLog, \
    evCheckout, \
    evStatus, \
    evBranch, \
    evSync, \
    evNotDefined
};

static map<string, StringValue> s_map;

void Initialize() {
    s_map["commit"]  = evCommit;
    s_map["reset"]   = evReset;
    s_map["log"]     = evLog;
    s_map["checkout"]= evCheckout;
    s_map["status"]  = evStatus;
    s_map["branch"]  = evBranch;
    s_map["sync"]    = evSync;
}

typedef pair<string, int> pairs;

class git {
private:
deque<pairs> master, feature,\
             *pos, *branch;
string status;
int idm, idf;

public:
    git() {
        this->pos   = &master;
        this->branch= &feature;
        status = "";
        this->idm = this->idf = 0;
    }

    void decision(string q) {
        switch(s_map[q]) {
            case evCommit :
                if (q == "commit") commit();
                break;
            case evReset :
                reset();
                break;
            case evLog :
                log();
                break;
            case evCheckout :
                checkout();
                break;
            case evStatus :
                statusf();
                break;
            case evBranch :
                branchf();
                break;
            case evSync :
                sync();
                break;
            default :
                cout << "error gan\n";
                break;
        }
    }

    void commit() {
        string temp;
        cin >> temp;

        if (pos == &master) {
            pos->push_back(make_pair(temp, idm));
            idm++;
        }
        else {
            pos->push_back(make_pair(temp, idf));
            idf++;    
        }
        status = temp;

    }

    void reset() {
        int ID;
        cin >> ID;

        while(pos->back().second != ID) {
            pos->pop_back();
        }
        cout << "Anda berada di commit " << pos->back().first << endl;
        // status.first = pos->back().first;
        // status.second= pos->back().second;

        status = pos->back().first;
    }

    void log() {
        if(!pos->empty()) {
            for (int i = pos->size() - 1; i >= 0; i--) {
                deque<pairs> temp = *pos;
                cout << temp[i].second << endl;
                cout << temp[i].first << endl;
            }
        }
        else cout << endl;
    }

    void checkout() {
        int ID;
        cin >> ID;

        deque<pairs>::reverse_iterator it;

        int count = 0;
        for (it = pos->rbegin(); it != pos->rend(); it++) {
            if (it->second == ID) {
               
                status = it->first;

                cout << "Anda berada di commit " << it->first << endl;
                count = 1;
                break;
            }
        }
        if(!count) cout << "ID tidak ditemukan" << endl;
    }

    void statusf() {
        cout << "Anda berada di commit " << status << endl;
    }

    void branchf() {
        string query;
        cin >> query;

        if (query == "master") {
            pos     = &master;
            branch  = &feature;
            if (!pos->empty()) status  = pos->back().first;
        }
        else if (query == "feature") {
            pos     = &feature;
            branch  = &master;
            if (!pos->empty()) status  = pos->back().first;
        }
    }

    void sync() {
        // deque<pairs> del = *pos, keep = *branch;
        
        size_t l = min(pos->size(), branch->size()) - 1;
    
        if (pos == &master) {
            for(l; l>= 0; l--) {
                if(feature[l] == master[l]) {
                    while(feature[l].first != feature.back().first) {
                        feature.pop_back();
                    // feature.pop_back();
                    }
                    return;
                }  
            }
        }
        else {
            for(l; l>= 0; l--) {
                if(feature[l] == master[l]) {
                    while(master[l].first != master.back().first) {
                        master.pop_back();
                    // feature.pop_back();
                    }
                    return;
                }  
            }
        }
    }
};

int main() {
    Initialize();
    git simple;
    string input = "";
    while (input != "quit") {
        cin >> input;
        simple.decision(input);
    }
    return 0;
}
