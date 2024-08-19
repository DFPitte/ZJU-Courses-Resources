#include<bits/stdc++.h>

using namespace std;
const int MAX_PAGES = 20001;
int lastAccessTime[MAX_PAGES];
int accessCount[MAX_PAGES];
int k, queueSize, numReferences,pageID;
struct st {
    int id, time;
    bool operator < (const st& a) const {
        if (time != a.time)
            return time < a.time;
        else
            return id < a.id;
    }
};


set<st> cacheQueue, historyQueue;


void printQueue(const set<st>& queue) {
    if (queue.empty()) {
        cout<<"-"<<endl;
    } else {
        bool isFirst = true;
        for (auto& page : queue) {
            if (!isFirst) cout << ' ';
            isFirst = false;
            cout << page.id;
        }
        cout << endl;
    }
}

int main() {
    cin >> k >> queueSize >> numReferences;

    for (int i = 0; i < numReferences; ++i) {
        
        cin >> pageID;

        if (cacheQueue.find({pageID, lastAccessTime[pageID]}) != cacheQueue.end()) {
            cacheQueue.erase({pageID, lastAccessTime[pageID]});
            lastAccessTime[pageID] = i;
            cacheQueue.insert({pageID, lastAccessTime[pageID]});
        } else {
            if (historyQueue.find({pageID, lastAccessTime[pageID]}) != historyQueue.end()) {
                ++accessCount[pageID];
                historyQueue.erase({pageID, lastAccessTime[pageID]});
                lastAccessTime[pageID] = i;

                if (accessCount[pageID] == k) {
                    cacheQueue.insert({pageID, lastAccessTime[pageID]});
                    accessCount[pageID] = 0;
                    if (cacheQueue.size() > queueSize)
                        cacheQueue.erase(cacheQueue.begin());
                } else {
                    historyQueue.insert({pageID, lastAccessTime[pageID]});
                }
            } else {
                ++accessCount[pageID];
                lastAccessTime[pageID] = i;
                historyQueue.insert({pageID, lastAccessTime[pageID]});
                if (historyQueue.size() > queueSize) {
                    int removeID = historyQueue.begin()->id;
                    historyQueue.erase(historyQueue.begin());
                    accessCount[removeID] = 0;
                }
            }
        }
    }

    printQueue(historyQueue);
    printQueue(cacheQueue);

    return 0;
}
