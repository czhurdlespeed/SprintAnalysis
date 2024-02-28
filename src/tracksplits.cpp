#include<iostream>
#include<vector>
#include<string>
#include<sstream>

using namespace std;


void plotTrack(int lanes, vector <float> color) {
    printf("newgraph\n");
    printf("xaxis\n");
    printf("min 0.2 max 2.8 size 5 \n");
    printf("no_auto_hash_labels mhash 0 hash 1 shash 1\n");
    printf("yaxis\n");
    printf("min 0 max 10 size 6\n");
    printf("nodraw\n");
    printf("newcurve marktype box marksize 2.6 10 cfill %f %f %f pts 1.5 5\n", color[0], color[1], color[2]);  

}




int main(int argc, char** argv) {
    if (argc < 3) {
        printf("Usage: %s <lanes> <color>\n", argv[0]);
        return 1;
    }
    int lanes = atoi(argv[1]);
    vector <float> color;
    color.push_back(stof(argv[2]));
    color.push_back(stof(argv[3]));
    color.push_back(stof(argv[4]));
/*    for (int i = 0; i < color.size(); i++) {
        cout << color[i] << endl;
    }
*/  
    plotTrack(lanes, color);



}
