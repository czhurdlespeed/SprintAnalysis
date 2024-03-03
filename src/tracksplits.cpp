/* 
 * Jon Calvin Wetzel
 * COSC594: jgraph lab 
 * March 3, 2024
 * Description:
*/
#include<iostream> // including libraries
#include<vector>
#include<string>
#include<sstream>
#include<fstream>
#include<map>

using namespace std;

class Athletics;

class SEC { // forms SEC conference with color 
    public:
        // Variables
        string name;

        // Data structures
        vector <float> trackcolor; // track color 
        vector <float> lanecolor; // lane color
        vector <float> logocolor; // logo color
};

class Athlete { // athlete class
    public:
        // Variables 
        string name; // athlete's name
        int lane; // athlete's lane
        
        // Data structures 
        vector <float> splits; // reaction time, 10m, 20m, 30m, 40m, 50m, 60m, 70m, 80m, 90m, 100m
        vector <float> distance_y; // distance traveled down track
        string year; // year time was run
        vector <int> color = {rand() % 255, rand() % 255, rand() % 255}; // random color for athlete's plot
        
        // Methods
        int laneassignment(Athletics& athletics); // assign a lane to the athlete based on available lanes in Athletics
};

class Athletics {
    public:
        // Variables
        int lanes; // number of lanes on the track
        SEC *selectedschool; // selected school 
        
        // Data structures
        map <int, map <float, Athlete*> *> racesplits; // map of pointers to split maps
        map <int, map <float, Athlete*> *>::iterator nmit; // iterator for racesplits map
        map <float, Athlete*>::iterator mit; // iterator for single split map e.g. 10m split map
        map <float, Athlete*>::reverse_iterator rmit; // reverse iterator for single split map e.g. 10m split map
        map <string, SEC*> schools; // map of SEC schools
        vector <int> availablelanes; // available lanes on the track
        vector < vector <Athlete*> > athlete_storage; // vector of athletes for each split; vectors align with order of the split maps
        
        // Methods
        void readData(Athletics& athletics); // read csv data, create athletes, and create split maps
        void plotTrack(); // plot the track of desired SEC school
        void plotAthletes(); // plot each athlete's race on the track
        void formSEC(); // form SEC schools and colors
};

int Athlete::laneassignment(Athletics& athletics) { // assign lanes randomly to athletes based on remaining lanes
    // random number between 1 and lanes
    int random;
    random = rand() % athletics.availablelanes.size() + 1; // random lane
    while(athletics.availablelanes[random] == -1) { // if lane is taken, get another random lane
        random = rand() % athletics.availablelanes.size() + 1;
    }
    athletics.availablelanes[random] = -1; // lane now taken
    return random;
}


void Athletics::plotTrack() { // plot the track of the selected school with school colors and logo
    // Variables 
    int i;
    printf("newgraph\n");
    printf("xaxis\n");
    printf("min 0 max 100 size 5.5 \n");
    printf("no_auto_hash_labels mhash 0 hash %f\n", 100.0/lanes);
    printf("yaxis\n");
    printf("min 0 max 1200 size 10.75\n"); // 120 -> 240
    printf("nodraw\n");
    printf("newcurve marktype box marksize 100 1200 cfill %f %f %f pts 50 600\n", \
            selectedschool->trackcolor[0]/255.0, selectedschool->trackcolor[1]/255.0, selectedschool->trackcolor[2]/255.0);  
    // Draw the lanes vertically
    for (i = 1; i < lanes; i++) {
        printf("newline pts %f %f %f %f color 1 1 1 linethickness 2\n", \
                100.0/lanes*i, 0.0, 100.0/lanes*i, 1200.0);
    }
    // Horizontal Finish Line
    printf("newline pts 0 1100 100 1100 color %f %f %f linethickness 2\n", \
            selectedschool->lanecolor[0]/255.0, selectedschool->lanecolor[1]/255.0, selectedschool->lanecolor[2]/255.0);
    // Horizontal Start Line 
    printf("newline pts 0 100 100 100 color %f %f %f linethickness 2\n", \
            selectedschool->lanecolor[0]/255.0, selectedschool->lanecolor[1]/255.0, selectedschool->lanecolor[2]/255.0);

    // Number the lanes below the start line 
    for (i = 1; i <= lanes; i++) {
       printf("newstring hjc vjc lcolor %f %f %f font Times-Bold fontsize 16 x %f y 50 : %d\n", \
               selectedschool->lanecolor[0]/255.0, selectedschool->lanecolor[1]/255.0, selectedschool->lanecolor[2]/255.0, (100.0/lanes*i)-((100.0/lanes)/2), i);
    }
    // Label start and finish line 
    printf("newstring hjl vjb lcolor %f %f %f font Times-Bold fontsize 10 x 1 y 110 : Start\n", \
            selectedschool->lanecolor[0]/255.0, selectedschool->lanecolor[1]/255.0, selectedschool->lanecolor[2]/255.0);
    printf("newstring hjr vjb lcolor %f %f %f font Times-Bold fontsize 10 x 99 y 1110 : Finish\n", \
            selectedschool->lanecolor[0]/255.0, selectedschool->lanecolor[1]/255.0, selectedschool->lanecolor[2]/255.0);
    // Logo on center lane
    printf("newstring hjc vjc lcolor %f %f %f font Times-Bold fontsize 28 rotate 90 x %f y 600 : %s\n", \
            selectedschool->logocolor[0]/255.0, selectedschool->logocolor[1]/255.0, selectedschool->logocolor[2]/255.0 ,(100.0/lanes*(lanes/2.0)), selectedschool->name.c_str());
    // Dashed 10m horiontal marks 
    for (i = 2; i <=10; i++) {
        printf("newline pts 0 %f 100 %f color %f %f %f linethickness 1 linetype dashed\n", \
                100.0*i, 100.0*i, 240.0/255.0, 220.0/255.0, 70.0/255.0);
        printf("newstring hjl vjb lcolor %f %f %f font Times-Bold fontsize 10 x 1 y %f : %dm\n", \
                240.0/255.0, 220.0/255.0, 70.0/255.0 ,100.0*i+1, (i-1)*10);
    }
}

void Athletics::readData(Athletics& athletics) {
    // Variables 
    ifstream file;
    float fastestsplit;
    string token;
    string line;
    stringstream ss;
    int lanesremaining = athletics.lanes;
    int i;
    float distance;
    // Data structures
    vector < map <float, Athlete*> * > accesstable; // vector of pointers to split maps
    vector <Athlete*> athletes; // vector of athlete pointers
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
    
    file.open("Data.csv"); // open csv file
    getline(file, line); // skip header
    while (getline(file, line) && (lanesremaining > 0)) {
        ss << line;
        Athlete *a = new Athlete(); // create new athlete 
        a->lane = a->laneassignment(athletics); // assign a lane to the athlete
        for (i=0; i<13; i++) { // 13 fields in csv file
            getline(ss, token, ','); // split line by comma (csv file)
            if (i==0) { // first field is name
                a->name = token;
            } else if (i==1) { // second field is year
                a->year = token;
            } else { // remaining fields are splits 
                a->splits.push_back(stof(token));
            }
            token.clear();
            // place each split in corresponding split map
            switch (i) { // switch statement to place splits in corresponding split map
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
        // athletes.push_back(a); // store athlete in vector of athletes
        lanesremaining--; // decrement lanes remaining
    }
    file.close();
       /* for (int i=0; i < athletes.size(); i++) {
            printf("%s %s\n", athletes[i]->name.c_str(), athletes[i]->year.c_str());
            for (int j=0; j < athletes[i]->splits.size(); j++) {
                printf("%f ", athletes[i]->splits[j]);
            }
            printf("\n");
        }
        */
         /*   cout << "Fastest reaction time: " << reaction.begin()->first << " by " << reaction.begin()->second->name << endl;
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
         */
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
    for (int i = 0; i < accesstable.size(); i++) { // access table of split maps
        map <float, Athlete*> * split = accesstable[i]; // pointer split map accessed
        map <float, Athlete*> * Athletedistance = new map <float, Athlete*>(); // keep split map order but convert from time to distance
        float fastestsplit = split->begin()->first; // fastest time for given split map i.e. fastest time for 10m split group
        for (mit = split->begin(); mit != split->end(); mit++) { // iterate through split map
            if (i !=0 )  { // if not reaction time
                float timepermeter = mit->first/(100*i); // time per meter
                distance = (fastestsplit / timepermeter) + 100.0; // distance
                mit->second->distance_y.push_back(distance); // set distance traveled for athlete
            } else { // if reaction time
                distance = 1-mit->first; // want fastest reaction time to be at end of reaction time map (traversed in reverse)
                mit->second->distance_y.push_back(100.0); // reaction time so distances are all at start line
            }
              Athletedistance->insert(pair<float, Athlete*>(distance, mit->second)); // insert individual's distance into the distance split map 
        }
        racesplits[i] = Athletedistance; // store distance split map in racesplits map 
    }
    athletes.clear();
    for (nmit = racesplits.begin(); nmit != racesplits.end(); nmit++) { // traverse racesplits map
        for (rmit = nmit->second->rbegin(); rmit != nmit->second->rend(); rmit++) { // traverse distance split map in reverse (want largest distance first)
            // store athlete pointers in vector of athletes for each split
            athletes.push_back(rmit->second);
        }
        athletics.athlete_storage.push_back(athletes); // athletes are in correct order for given split group; place split group in athlete_storage
        athletes.clear();
    }
}

void Athletics::plotAthletes() { // plot each athlete on track for each split in oder of place at given split e.g. 2nd place 10m split, 3rd place 20m split, etc.
    // Variables
    ifstream file;
    ofstream fileout;
    int i, j, k;
    float hash, x, y;
    string year, pts;
    hash = 100.0/lanes;

    for (i = 0; i < athlete_storage.size(); i++) { // iterate through split groups
        for (j = 0; j < athlete_storage[i].size(); j++) { // iterate through athletes in split group
            freopen(("jgr/" + to_string(i) + "0m_split_" + to_string((j+1)) + "place" + ".jgr").c_str(), "w", stdout); // redirect stdout to file
            plotTrack(); // plot up to current lane for each lane in split group
            freopen("/dev/tty", "a", stdout); // reset stdout to terminal
            fileout.open("jgr/" + to_string(i) + "0m_split_" + to_string((j+1)) + "place" + ".jgr", ios::app); // open file for appending
            fileout << "newgraph\n";
            fileout << "xaxis\n";
            fileout << "min 0 max 100 size 5.5 \n";
            fileout << "no_auto_hash_labels mhash 0 hash " << hash << "\n";
            fileout << "yaxis\n";
            fileout << "min 0 max 1200 size 10.75\n"; // 120 -> 240
            fileout << "nodraw\n";
            for (k = 0; k <= j; k++) { // iterate through athletes up to current athlete place
                x = 100.0/lanes*athlete_storage[i][k]->lane - ((100.0/lanes)/2); // place athlete in lane
                y = athlete_storage[i][k]->distance_y[i]; // place athlete at distance traveled
                year = " '" + athlete_storage[i][k]->year.substr(2, 2); // year athlete ran time 
                char legendlabel[40];
                if (k==0) {
                    snprintf(legendlabel, 40, "%2dst %-24s Lane: %-3d", k+1, (athlete_storage[i][k]->name + year).c_str(), athlete_storage[i][k]->lane);
                } 
                else if (k==1) {
                    snprintf(legendlabel, 40, "%2dnd %-24s Lane: %-3d", k+1, (athlete_storage[i][k]->name + year ).c_str(), athlete_storage[i][k]->lane);
                }
                else if (k==2) {
                    snprintf(legendlabel, 40, "%2drd %-24s Lane: %-3d", k+1, (athlete_storage[i][k]->name + year).c_str(), athlete_storage[i][k]->lane);
                }
                else {
                    snprintf(legendlabel, 40, "%2dth %-24s Lane: %-3d", k+1, (athlete_storage[i][k]->name + year).c_str(), athlete_storage[i][k]->lane);
                }
                legendlabel[sizeof(legendlabel)-1] = '\0'; // null terminate buffer
                char athleteline[200];
                snprintf(athleteline,200, "newcurve marktype box linetype dashed glines 7 2 color %f %f %f marksize 1 5 label : %s\n", \
                        athlete_storage[i][k]->color[0]/255.0, athlete_storage[i][k]->color[1]/255.0,athlete_storage[i][k]->color[2]/255.0, legendlabel);
                athleteline[sizeof(athleteline)-1] = '\0';
                fileout << athleteline;
                pts.clear();
                pts = "pts"; 
                for (int l = 0; l <= i; l++) {
                    x = 100.0/lanes*athlete_storage[i][k]->lane - ((100.0/lanes)/2);
                    y = athlete_storage[i][k]->distance_y[l]; 
                    pts += " " + to_string(x) + " " + to_string(y);
                }
                fileout << pts << "\n";
            }
            fileout.close(); // close file
        }
    } 
}

void Athletics::formSEC () { // form SEC schools and colors
    // SEC schools and colors
    SEC *Tennessee = new SEC();
    Tennessee->trackcolor = {255, 130, 0};
    Tennessee->lanecolor = {255, 255, 255};
    Tennessee->logocolor = {88, 89, 91};
    Tennessee->name = "Tennessee";
    schools["Tennessee"] = Tennessee;
    SEC *Florida = new SEC();
    Florida->trackcolor = {0, 33, 165};
    Florida->lanecolor = {255, 255, 255};
    Florida->logocolor = {250, 70, 22};
    Florida->name = "Florida";
    schools["Florida"] = Florida;
    SEC *Alabama = new SEC();
    Alabama->trackcolor = {158, 27, 50};
    Alabama->lanecolor = {130, 138, 143};
    Alabama->logocolor = {255, 255, 255};
    Alabama->name = "Alabama";
    schools["Alabama"] = Alabama;
    SEC *Auburn = new SEC();
    Auburn->trackcolor = {12, 35, 64};
    Auburn->lanecolor = {255, 255, 255};
    Auburn->logocolor = {232, 119, 34};
    Auburn->name = "Auburn";
    schools["Auburn"] = Auburn;
    SEC *Arkansas = new SEC();
    Arkansas->trackcolor = {157, 34, 53};
    Arkansas->lanecolor = {255, 255, 255};
    Arkansas->logocolor = {255, 255, 255};
    Arkansas->name = "Arkansas";
    schools["Arkansas"] = Arkansas;
    SEC *Georgia = new SEC();
    Georgia->trackcolor = {186, 12, 47};
    Georgia->lanecolor = {0, 0, 0};
    Georgia->logocolor = {255, 255, 255};
    Georgia->name = "Georgia";
    schools["Georgia"] = Georgia;
    SEC *Kentucky = new SEC();
    Kentucky->trackcolor = {0, 51, 160};
    Kentucky->lanecolor = {0, 0, 0};
    Kentucky->logocolor = {255, 255, 255};
    Kentucky->name = "Kentucky";
    schools["Kentucky"] = Kentucky;
    SEC *LSU = new SEC();
    LSU->trackcolor = {70, 29 ,124};
    LSU->lanecolor = {255, 255, 255};
    LSU->logocolor = {253, 208, 35};
    LSU->name = "LSU";
    schools["LSU"] = LSU;
    SEC *OleMiss = new SEC();
    OleMiss->trackcolor = {204, 9, 47};
    OleMiss->lanecolor = {255, 255, 255};
    OleMiss->logocolor = {22, 43, 72};
    OleMiss->name = "Ole Miss";
    schools["Ole Miss"] = OleMiss;
    SEC *MSU = new SEC();
    MSU->trackcolor = {102, 0, 0};
    MSU->lanecolor = {255, 255, 255};
    MSU->logocolor = {255, 255, 255};
    MSU->name = "Mississippi State";
    schools["Mississippi State"] = MSU;
    SEC *Missouri = new SEC();
    Missouri->trackcolor = {0, 0, 0};
    Missouri->lanecolor = {255, 255, 255};
    Missouri->logocolor = {241, 184, 45};
    Missouri->name = "Missouri";
    schools["Missouri"] = Missouri;
    SEC *SouthCarolina = new SEC();
    SouthCarolina->trackcolor = {115, 0, 10};
    SouthCarolina->lanecolor = {0, 0, 0};
    SouthCarolina->logocolor = {255, 255, 255};
    SouthCarolina->name = "South Carolina";
    schools["South Carolina"] = SouthCarolina;
    SEC *TexasAM = new SEC();
    TexasAM->trackcolor = {80, 0, 0};
    TexasAM->lanecolor = {255, 255, 255};
    TexasAM->logocolor = {255, 255, 255};
    TexasAM->name = "Texas A&M";
    schools["Texas A&M"] = TexasAM;
    SEC *Vanderbilt = new SEC();
    Vanderbilt->trackcolor = {0, 0, 0};
    Vanderbilt->lanecolor = {255, 255, 255};
    Vanderbilt->logocolor = {134, 109, 75};
    Vanderbilt->name = "Vanderbilt";
    schools["Vanderbilt"] = Vanderbilt;
}

int main(int argc, char** argv) {
    if (argc < 3) {
        printf("Usage: %s <lanes> <SEC School Name>\n", argv[0]);
        return 1;
    }
    Athletics a;
    a.lanes = atoi(argv[1]); // number of lanes
    for (int i = 1; i <= a.lanes; i++) { // available lanes
        a.availablelanes.push_back(i);
    }
    a.formSEC(); // form SEC schools and colors
    a.selectedschool =  a.schools[argv[2]]; // user selected school
    a.readData(a); // read data and create athletes
    a.plotAthletes(); // plot athletes
}
