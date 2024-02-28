#include<iostream>
#include<vector>
#include<string>
#include<sstream>

using namespace std;


void plotTrack(int lanes, vector <float> color) {
    printf("newgraph\n");
    printf("xaxis\n");
    printf("min 0 max 100 size 7 \n");
    printf("no_auto_hash_labels mhash 0 hash %f\n", 100.0/lanes);
    printf("yaxis\n");
    printf("min 0 max 110 size 11\n");
    printf("nodraw\n");
    printf("newcurve marktype box marksize 100 110 cfill %f %f %f pts 50 55\n", color[0], color[1], color[2]);  

}




int main(int argc, char** argv) {
    if (argc < 3) {
        printf("Usage: %s <lanes> <color>\n", argv[0]);
        return 1;
    }
    int lanes = atoi(argv[1]);
    vector <float> color;
    color.push_back(stof(argv[2])/255.0);
    color.push_back(stof(argv[3])/255.0);
    color.push_back(stof(argv[4])/255.0);
/*    for (int i = 0; i < color.size(); i++) {
        cout << color[i] << endl;
    }
*/  
    plotTrack(lanes, color);



}
