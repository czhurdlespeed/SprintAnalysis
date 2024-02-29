#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include<fstream>
#include<map>

using namespace std;

class Athletics;

class Athlete {
    public:
        vector <float> splits;
        float time;
        string year;
        string name;
        int lane;
        int laneassignment(Athletics& athletics);
        friend class Athletics;
};

class Athletics {
    public:
        map <int, map <float, Athlete*> *> normalizedsplits;
        map <float, Athlete*>::iterator mit;
        map <float, Athlete*>::iterator mit2;
        map <float, Athlete*>::iterator mit3;
        map <int, map <float, Athlete*> *>::iterator nmit;
        void readData(Athletics& athletics);
        int lanes;
        vector <int> availablelanes;
        void plotTrack(vector <float> color);
        void plotAthletes();
        
};

int Athlete::laneassignment(Athletics& athletics) {
    // random number between 1 and lanes
    int random = rand() % athletics.availablelanes.size() + 1;
    while(athletics.availablelanes[random] == -1) {
        random = rand() % athletics.availablelanes.size() + 1;
    }
    athletics.availablelanes[random] = -1;
    return random;
}


void Athletics::plotTrack(vector <float> color) {
    printf("newgraph\n");
    printf("xaxis\n");
    printf("min 0 max 100 size 7 \n");
    printf("no_auto_hash_labels mhash 0 hash %f\n", 100.0/lanes);
    printf("yaxis\n");
    printf("min 0 max 120 size 11\n");
    printf("nodraw\n");
    printf("newcurve marktype box marksize 100 120 cfill %f %f %f pts 50 60\n", color[0], color[1], color[2]);  
    // Let's draw the lanes vertically and white
    for (int i = 1; i < lanes; i++) {
        printf("newline pts %f %f %f %f color 1 1 1 linethickness 2\n", 100.0/lanes*i, 0.0, 100.0/lanes*i, 110.0);
    }
    // Horizontal Finish Line
    printf("newline pts 0 110 100 110 color 1 1 1 linethickness 2\n");
    // Horizontal Start Line 
    printf("newline pts 0 10 100 10 color 1 1 1 linethickness 2\n");

    // Number the lanes below the start line 
    for (int i = 1; i <= lanes; i++) {
       printf("newstring hjc vjc lcolor 1 1 1 font Times-Bold fontsize 16 x %f y 5 : %d\n", (100.0/lanes*i)-((100.0/lanes)/2), i);
    }
    // Label start and finish line 
    printf("newstring hjl vjb lcolor 1 1 1 font Times-Bold fontsize 10 x 1 y 11 : Start\n");
    printf("newstring hjr vjb lcolor 1 1 1 font Times-Bold fontsize 10 x 99 y 111 : Finish\n");
    // Logo on center lane
    printf("newstring hjc vjc lcolor 1 1 1 font Times-Bold fontsize 28 rotate 90 x %f y 55 : Tennessee\n", (100.0/lanes*(lanes/2.0)));
    // Dashed 10m horiontal marks 
    for (int i = 2; i <=10; i++) {
        printf("newline pts 0 %f 100 %f color 0 0 0 linethickness 1 linetype dashed\n", 10.0*i, 10.0*i);
        printf("newstring hjl vjb lcolor 0 0 0 font Times-Bold fontsize 10 x 1 y %f : %dm\n", 10.0*i+1, (i-1)*10);
    }
}

void Athletics::readData(Athletics& athletics) {
    ifstream file;
    vector <Athlete*> athletes;
    file.open("Data.csv");
    map <float, Athlete*> reaction; // map of reaction times to athletes
    map <float, Athlete*> split10m; // map of 10m splits to athletes
    map <float, Athlete*> split20m; // map of 20m splits to athletes
    map <float, Athlete*> split30m; // map of 30m splits to athletes
    map <float, Athlete*> split40m; // map of 40m splits to athletes
    map <float, Athlete*> split50m; // map of 50m splits to athletes
    map <float, Athlete*> split60m; // map of 60m splits to athletes
    map <float, Athlete*> split70m; // map of 70m splits to athletes
    map <float, Athlete*> split80m; // map of 80m splits to athletes
    map <float, Athlete*> split90m; // map of 90m splits to athletes
    map <float, Athlete*> split100m; // map of 100m splits to athletes
    string line;
    getline(file, line); // skip header
    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        Athlete *a = new Athlete(); // create new athlete 
        a->lane = a->laneassignment(athletics); // assign a lane to the athlete
        for (int i=0; i<13; i++) {
            getline(ss, token, ',');
            cout << token << endl;
            if (i==0) {
                a->name = token;
            } else if (i==1) {
                a->year = token;
            } else { // splits[0] == reaction time
                a->splits.push_back(stof(token));
            }
            token.clear();
            // cases for each split
            switch (i) {
                case 2:
                    reaction[a->splits[0]] = a;
                    break;
                case 3:
                    split10m[a->splits[1]] = a;
                    break;
                case 4:
                    split20m[a->splits[2]] = a;
                    break;
                case 5:
                    split30m[a->splits[3]] = a;
                    break;
                case 6:
                    split40m[a->splits[4]] = a;
                    break;
                case 7:
                    split50m[a->splits[5]] = a;
                    break;
                case 8:
                    split60m[a->splits[6]] = a;
                    break;
                case 9:
                    split70m[a->splits[7]] = a;
                    break;
                case 10:
                    split80m[a->splits[8]] = a;
                    break;
                case 11:
                    split90m[a->splits[9]] = a;
                    break;
                case 12:
                    split100m[a->splits[10]] = a;
                    break;
            }
        }
        ss.clear();
        athletes.push_back(a);
    }


    file.close();
    for (int i=0; i < athletes.size(); i++) {
        printf("%s %s\n", athletes[i]->name.c_str(), athletes[i]->year.c_str());
        for (int j=0; j < athletes[i]->splits.size(); j++) {
            printf("%f ", athletes[i]->splits[j]);
        }
        printf("\n");
    }
    float fastestsplit;
    cout << "Fastest reaction time: " << reaction.begin()->first << " by " << reaction.begin()->second->name << endl;
    cout << "Fastest 10m split: " << split10m.begin()->first << " by " << split10m.begin()->second->name << endl;
    cout << "Fastest 20m split: " << split20m.begin()->first << " by " << split20m.begin()->second->name << endl;
    cout << "Fastest 30m split: " << split30m.begin()->first << " by " << split30m.begin()->second->name << endl;
    cout << "Fastest 40m split: " << split40m.begin()->first << " by " << split40m.begin()->second->name << endl;
    cout << "Fastest 50m split: " << split50m.begin()->first << " by " << split50m.begin()->second->name << endl;
    cout << "Fastest 60m split: " << split60m.begin()->first << " by " << split60m.begin()->second->name << endl;
    cout << "Fastest 70m split: " << split70m.begin()->first << " by " << split70m.begin()->second->name << endl;
    cout << "Fastest 80m split: " << split80m.begin()->first << " by " << split80m.begin()->second->name << endl;
    cout << "Fastest 90m split: " << split90m.begin()->first << " by " << split90m.begin()->second->name << endl;
    cout << "Fastest 100m split: " << split100m.begin()->first << " by " << split100m.begin()->second->name << endl;
    // normalize the splits to the fastest split 
    vector < map <float, Athlete*> * > accesstable;
    accesstable.push_back(&reaction);
    accesstable.push_back(&split10m);
    accesstable.push_back(&split20m);
    accesstable.push_back(&split30m);
    accesstable.push_back(&split40m);
    accesstable.push_back(&split50m);
    accesstable.push_back(&split60m);
    accesstable.push_back(&split70m);
    accesstable.push_back(&split80m);
    accesstable.push_back(&split90m);
    accesstable.push_back(&split100m);
   // map <float, Athlete*>::iterator mit;
  //  map <int, map <float, Athlete*> *> normalizedsplits;
  //  map <int, map <float, Athlete*> *>::iterator nmit;
    for (int i = 0; i < accesstable.size(); i++) { // access table to split maps to normalize
        map <float, Athlete*> * split = accesstable[i]; // maps to normalize
        map <float, Athlete*> * normalized = new map <float, Athlete*>(); // normalized map
        float fastestsplit = split->begin()->first; // fastest split from split map
        for (mit = split->begin(); mit != split->end(); mit++) { // iterate through split map
            normalized->insert(pair<float, Athlete*>(fastestsplit/mit->first, mit->second)); // insert individual's normalized split into normalized map
        }
        normalizedsplits[i] = normalized; // insert normalized map for given split into normalized splits map
    }
/*
 *  NOTE:
        normalizedsplits < split location, < normalized split, Athlete *> > 
        Now just go off of normalized splits to plot athletes on the track
*/
    for (nmit = normalizedsplits.begin(); nmit != normalizedsplits.end(); nmit++) {
        cout << "Normalized " << nmit->first << "m split" << endl;
        for (mit = nmit->second->begin(); mit != nmit->second->end(); mit++) {
            cout << mit->first << " Lane: " << mit->second->lane << " "  << mit->second->name << " Year: " << mit->second->year << endl;
        }
    }
}

void Athletics::plotAthletes() {
    // Plot the athletes on the track using the lanes on the track
    vector <float> color;
    color.push_back(0);
    color.push_back(0.5);
    color.push_back(0);
    ofstream file;
    cout << endl;
    cout << "Plotting athletes on the track" << endl;
    for (nmit = normalizedsplits.begin(); nmit != normalizedsplits.end(); nmit++) { // iterate through split groups
        cout << "Normalized " << nmit->first << "m split" << endl;
        int i = 0;
        for (mit = nmit->second->begin(); mit != nmit->second->end(); mit++) {
            mit3 = mit;
            i++;
           // cout << "i: " << i << endl;
            if (nmit != normalizedsplits.begin()) { // not 0m split (reaction time)
                freopen(("jgr/" + to_string(nmit->first) + "m_split_" + to_string(i) + "place" + ".jgr").c_str(), "w", stdout);
                plotTrack(color); // plot up to current lane for each lane in split group
                freopen("/dev/tty", "a", stdout); // reset stdout to terminal
            }
            int j = 0;
            for (mit2 = nmit->second->begin(); mit2 != nmit->second->end(); mit2++) { // iterate through athletes in split group
                j++;
               // cout << "j: " << j << endl;
                //cout << mit->first << " Lane: " << mit->second->lane << " "  << mit->second->name << " Year: " << mit->second->year << endl;
                // append stdout to a file
                if (nmit == normalizedsplits.begin()) { // 0m split (reaction time)...want to plot each reaction time sequentially
                    freopen(("jgr/" + to_string(nmit->first) + "m_split_"  +  to_string(i) + "place"  + ".jgr").c_str(), "w", stdout);
                    plotTrack(color); // plot up to current lane for each lane in split group
                    freopen("/dev/tty", "a", stdout); // reset stdout to terminal
                }
                // format string using sprintf   
                char buffer[150];
                // mit->first is the first normalized split for the current split group
                // nmit->first is the current split group e.g. 0m 10m 20m
                // mit->second->name is the name of the athlete
                // j is the current lane
                file.open("jgr/" + to_string(nmit->first) + "m_split_" +  to_string(j) + "place"  + ".jgr", std::ios::app); // create new file for each lane in each split group
                snprintf(buffer, 150, "newline marktype box linetype dashed color 0 1 0 pts %f %f label : %s\n", (100.0/lanes*(mit->second->lane))-((100.0/lanes)/2), 10.0*(nmit->first)*mit->first + 10, mit->second->name.c_str());
                file << buffer;
                file.close();
            } // j for loop
        } // lanes for loop
       // break;
    } // split groups for loop
}


int main(int argc, char** argv) {
    if (argc < 3) {
        printf("Usage: %s <lanes> <color>\n", argv[0]);
        return 1;
    }
    vector <float> color;
    color.push_back(stof(argv[2])/255.0);
    color.push_back(stof(argv[3])/255.0);
    color.push_back(stof(argv[4])/255.0);
    Athletics a;
    a.lanes = atoi(argv[1]);
    for (int i = 1; i <= a.lanes; i++) {
        a.availablelanes.push_back(i);
    }
    a.readData(a);
    a.plotAthletes();

}
