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
