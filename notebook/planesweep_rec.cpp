//
//  main.cpp
//  planesweep_rec
//
//  Created by Yufei Zheng on 10/05/2018.
//  Copyright © 2018 Yufei Zheng. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <math.h>

#define MAX_SIZE 100

using namespace std;

struct Rectangle
{
    int x, y, w, h, neighbors = 0;
};

struct Event
{
    int x, y, h, index;
    char lr; //'l' for left endpoint, 'r' for right endpoint
    
    bool operator < (const Event& _e) const
    {
        if (x != _e.x)
            return (x < _e.x);   // events on left have higher priority
        if (lr != _e.lr)
            return (lr == 'l'); // for events with same x's, left endpoints have higher priority
        if (y != _e.y)
            return (y < _e.y);   // for events of the same type, with the same s'x, lower endpoints win
        return h < _e.h;
    }
};

struct StatusNode
{
    int y, h, idx;
    
    bool operator < (const StatusNode& _sn) const
    {
        if (y != _sn.y)
            return (y < _sn.y);
        return (h < _sn.h);
    }
};

int main(int argc, const char * argv[]) {
    
    vector<Rectangle> rectangles;
    Rectangle r;
    
    //-------- read point set from file -------
    ifstream myfile ("rectangles.txt");
    if (myfile.is_open())
    {
        // cout << "open" << endl;
        while (myfile >> r.x >> r.y >> r.w >> r.h)
        {
            rectangles.push_back(r);
        }
        myfile.close();
    }
    else
        cout << "can't open file!" << endl;
    
    
    //------------event queue------------------
    vector<Event> events;
    for (int i=0; i<rectangles.size(); i++) {
        Event e1, e2;
        e1.x = rectangles[i].x;
        e1.y = rectangles[i].y;
        e1.h = rectangles[i].h;
        e1.index = i;
        e1.lr = 'l';
        e2.x = rectangles[i].x + rectangles[i].w;
        e2.y = rectangles[i].y;
        e2.h = rectangles[i].h;
        e2.index = i;
        e2.lr = 'r';
        events.push_back(e1);
        events.push_back(e2);
    }
    sort(events.begin(), events.end());
    
    
    //-----------plane sweep status------------
    set<StatusNode> status; //BBST for representing sweep line status
    StatusNode node;
    
    for (int i=0; i<events.size(); i++) {
        node.y = events[i].y;
        node.h = events[i].h;
        node.idx = events[i].index;
        if (events[i].lr == 'l') {  // handle left endpoints
            set<StatusNode>::const_iterator iter = status.lower_bound(node);
            if (iter != status.begin())
                iter--; // see def. of lower_bound, it only returns the upper neighbor
            for (; iter != status.end(); iter++) {
                if ((((*iter).y <= node.y) && ((*iter).y + (*iter).h >= node.y)) || (((*iter).y >= node.y) && (node.y + node.h >= (*iter).y))) {
                    rectangles[(*iter).idx].neighbors++;
                    rectangles[node.idx].neighbors++;
                }
            }
            status.insert(node);
        } else {                    // handle right endpoint
            status.erase(node);
        }
    }
    
    cout << "Rectangles:" << endl;
    for (vector<Rectangle>::const_iterator iter=rectangles.begin(); iter != rectangles.end(); iter++) {
        cout << "Rectangle " << iter-rectangles.begin() << ':' << endl;
        cout << (*iter).neighbors << endl;
        cout << endl;
    }
    
    return 0;
}
