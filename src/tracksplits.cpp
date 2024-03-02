#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include<fstream>
#include<map>

using namespace std;

class Athletics;

class SEC {
    public:
        string name;
        vector <float> trackcolor; // track color 
        vector <float> lanecolor; // lane color
        vector <float> logocolor; // logo color
};

class Athlete {
    public:
        vector <float> splits;
        float time;
        vector <float> normalizedtime;
        vector <float> normalized_y;
        string year;
        vector <int> color = {rand() % 255, rand() % 255, rand() % 255};
        string name;
        int lane;
        int laneassignment(Athletics& athletics);
        friend class Athletics;
};

class Athletics {
    public:
        map <int, map <float, Athlete*> *> normalizedsplits;
        map <float, Athlete*>::iterator mit;
        map <float, Athlete*>::reverse_iterator rmit;
        map <float, Athlete*>::iterator mit2;
        map <float, Athlete*>::reverse_iterator rmit2;
        map <float, Athlete*>::iterator mit3;
        map <float, Athlete*>::reverse_iterator rmit3;
        map <int, map <float, Athlete*> *>::iterator nmit;
        map <int, map <float, Athlete*> *>::reverse_iterator rnmit;
        void readData(Athletics& athletics);
        int lanes;
        vector <int> availablelanes;
        vector < vector <Athlete*> > athlete_storage;
        void plotTrack();
        void plotAthletes();
        map <string, SEC*> schools;
        SEC *selectedschool; 
        void formSEC();
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


void Athletics::plotTrack() {
    printf("newgraph\n");
    printf("xaxis\n");
    printf("min 0 max 100 size 5.5 \n");
    printf("no_auto_hash_labels mhash 0 hash %f\n", 100.0/lanes);
    printf("yaxis\n");
    printf("min 0 max 1200 size 10.75\n"); // 120 -> 240
    printf("nodraw\n");
    printf("newcurve marktype box marksize 100 1200 cfill %f %f %f pts 50 600\n", selectedschool->trackcolor[0]/255.0, selectedschool->trackcolor[1]/255.0, selectedschool->trackcolor[2]/255.0);  
    // Let's draw the lanes vertically and white
    for (int i = 1; i < lanes; i++) {
        printf("newline pts %f %f %f %f color 1 1 1 linethickness 2\n", 100.0/lanes*i, 0.0, 100.0/lanes*i, 1200.0);
    }
    // Horizontal Finish Line
    printf("newline pts 0 1100 100 1100 color %f %f %f linethickness 2\n", selectedschool->lanecolor[0]/255.0, selectedschool->lanecolor[1]/255.0, selectedschool->lanecolor[2]/255.0);
    // Horizontal Start Line 
    printf("newline pts 0 100 100 100 color %f %f %f linethickness 2\n", selectedschool->lanecolor[0]/255.0, selectedschool->lanecolor[1]/255.0, selectedschool->lanecolor[2]/255.0);

    // Number the lanes below the start line 
    for (int i = 1; i <= lanes; i++) {
       printf("newstring hjc vjc lcolor %f %f %f font Times-Bold fontsize 16 x %f y 50 : %d\n", selectedschool->lanecolor[0]/255.0, selectedschool->lanecolor[1]/255.0, selectedschool->lanecolor[2]/255.0, (100.0/lanes*i)-((100.0/lanes)/2), i);
    }
    // Label start and finish line 
    printf("newstring hjl vjb lcolor %f %f %f font Times-Bold fontsize 10 x 1 y 110 : Start\n", selectedschool->lanecolor[0]/255.0, selectedschool->lanecolor[1]/255.0, selectedschool->lanecolor[2]/255.0);
    printf("newstring hjr vjb lcolor %f %f %f font Times-Bold fontsize 10 x 99 y 1110 : Finish\n", selectedschool->lanecolor[0]/255.0, selectedschool->lanecolor[1]/255.0, selectedschool->lanecolor[2]/255.0);
    // Logo on center lane
    printf("newstring hjc vjc lcolor %f %f %f font Times-Bold fontsize 28 rotate 90 x %f y 600 : %s\n",selectedschool->logocolor[0]/255.0, selectedschool->logocolor[1]/255.0, selectedschool->logocolor[2]/255.0 ,(100.0/lanes*(lanes/2.0)), selectedschool->name.c_str());
    // Dashed 10m horiontal marks 
    for (int i = 2; i <=10; i++) {
        printf("newline pts 0 %f 100 %f color %f %f %f linethickness 1 linetype dashed\n", 100.0*i, 100.0*i, 240.0/255.0, 220.0/255.0, 70.0/255.0);
        printf("newstring hjl vjb lcolor %f %f %f font Times-Bold fontsize 10 x 1 y %f : %dm\n",240.0/255.0, 220.0/255.0, 70.0/255.0 ,100.0*i+1, (i-1)*10);
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
            float distance;
            if (i !=0 )  {
                float timepermeter = mit->first/(100*i); // time per meter
                distance = (fastestsplit / timepermeter) + 100.0; // distance
            } else {
                distance = 100.0;
            }
          //  normalized->insert(pair<float, Athlete*>(fastestsplit/mit->first, mit->second)); // insert individual's normalized split into normalized map
              normalized->insert(pair<float, Athlete*>(distance, mit->second)); // insert individual's 
          //  mit->second->normalizedtime.push_back(fastestsplit/mit->first); // set normalized time for individual
         //   mit->second->normalized_y.push_back( (i==0) ? 100.0 : 100.0*i + mit->second->normalizedtime[mit->second->normalizedtime.size()-1]*100); // set normalized y coordinate for individual
              mit->second->normalized_y.push_back(distance); // set normalized time for individual
        }
        normalizedsplits[i] = normalized; // insert normalized map for given split into normalized splits map
    }
/*
 *  NOTE:
        normalizedsplits < split location, < normalized split, Athlete *> > 
        Now just go off of normalized splits to plot athletes on the track
*/
    athletes.clear();
    int i = 0;
    for (nmit = normalizedsplits.begin(); nmit != normalizedsplits.end(); nmit++) {
        cout << "Normalized " << nmit->first << "m split" << endl;
        for (rmit = nmit->second->rbegin(); rmit != nmit->second->rend(); rmit++) {
            cout << "Distance: " << rmit->first << " Lane: " << rmit->second->lane << " "  << rmit->second->name << " Year: " << rmit->second->year << endl;
            // store athlete pointer in vector of athletes for each split
            athletes.push_back(rmit->second);
        }
        athletics.athlete_storage.push_back(athletes);
        athletes.clear();
        i++;
    }
}

void Athletics::plotAthletes() {
    // Plot the athletes on the track using the lanes on the track
   // vector <float> color;
    ifstream file;
    ofstream fileout;
  //  color.push_back(0);
  //  color.push_back(0.5);
  //  color.push_back(0);
    cout << endl;
    cout << "Plotting athletes on the track" << endl;
    cout << "Split groups: " << athlete_storage.size() << endl;
    cout << "Num Athletes: " << athlete_storage[0].size() << endl;
    
    for (int i = 0; i < athlete_storage.size(); i++) { // iterate through split groups
        printf("%s m split\n", to_string(i).c_str());
        for (int j = 0; j < athlete_storage[i].size(); j++) { // iterate through athletes in split group
         //   cout << athlete_storage[i][j]->name << " " << athlete_storage[i][j]->year << " " << athlete_storage[i][j]->lane << " " << athlete_storage[i][j]->normalizedtime[i] << endl;
            cout << "Normalized y: " << athlete_storage[i][j]->normalized_y[i] << endl;
            // Need to go through athlete_storage and convert normalized times to y coordinates. The put all y coordinates in a vector; plot vector on lane
                freopen(("jgr/" + to_string(i) + "m_split_" + to_string(j) + "place" + ".jgr").c_str(), "w", stdout);
                plotTrack(); // plot up to current lane for each lane in split group
                freopen("/dev/tty", "a", stdout); // reset stdout to terminal
            fileout.open("jgr/" + to_string(i) + "m_split_" + to_string(j) + "place" + ".jgr", ios::app);
            for (int k = 0; k <= j; k++) { // iterate through athletes up to current athlete place
                float x = 100.0/lanes*athlete_storage[i][k]->lane - ((100.0/lanes)/2);
                float y;
                y = athlete_storage[i][k]->normalized_y[i];
                char buffer2[45];
                snprintf(buffer2, 45, "Place: %d %s Lane: %d", k+1, athlete_storage[i][k]->name.c_str(), athlete_storage[i][k]->lane);
                buffer2[sizeof(buffer2)-1] = '\0';
                char buffer[200];
                snprintf(buffer,200, "newcurve marktype box linetype dashed glines 7 2 color %f %f %f marksize .75 3.75 label : %s\n", \
                        athlete_storage[i][k]->color[0]/255.0, athlete_storage[i][k]->color[1]/255.0,athlete_storage[i][k]->color[2]/255.0 ,buffer2);
                buffer[sizeof(buffer)-1] = '\0';
                fileout << buffer;
                string pts = "pts"; 
                for (int l = 0; l <= i; l++) {
                    float x = 100.0/lanes*athlete_storage[i][k]->lane - ((100.0/lanes)/2);
                    float y = athlete_storage[i][k]->normalized_y[l]; 
                    pts += " " + to_string(x) + " " + to_string(y);
                }
                cout << "pts: " << pts << endl;
                fileout << pts << "\n";
            }
            fileout.close();
        }
    }
}

void Athletics::formSEC () {
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
    SouthCarolina->trackcolor = {0, 100, 61, 43};
    SouthCarolina->lanecolor = {255, 255, 255};
    SouthCarolina->logocolor = {0, 0, 0};
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
    a.lanes = atoi(argv[1]);
    for (int i = 1; i <= a.lanes; i++) {
        a.availablelanes.push_back(i);
    }
    a.formSEC();
    a.selectedschool =  a.schools[argv[2]];
    cout << "Selected School: " << a.selectedschool->name << endl;
//    color.push_back(stof(argv[2])/255.0);
//    color.push_back(stof(argv[3])/255.0);
//    color.push_back(stof(argv[4])/255.0);

    a.readData(a);
    a.plotAthletes();

}
