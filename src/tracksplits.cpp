#include<iostream>
#include<vector>
#include<string>
#include<sstream>

using namespace std;


void plotTrack(int lanes, vector <int> color) {
    printf("newgraph\n");
    printf("xaxis\n");
    printf("min 0 max 10 size 7 \n");
    printf("no_auto_hash_labels mhash 0 hash 1\n");
    printf("yaxis\n");
    printf("min 0 max 6 size 4\n");
    printf("nodraw\n");
    printf("newcurve marktype box marksize 2.6 10 cfill %d %d %d pts 0 0 10 0 10 5 0 5\n", color[0], color[1], color[2]);  

}




int main(int argc, char** argv) {
    if (argc < 3) {
        printf("Usage: %s <lanes> <color>\n", argv[0]);
        return 1;
    }
    int lanes = atoi(argv[1]);
    vector <int> color;
    string s = argv[2];
    istringstream iss(s);
    while (getline(iss, s, ',')) {
        color.push_back(atoi(s.c_str()));
    }
    plotTrack(lanes, color);



}
