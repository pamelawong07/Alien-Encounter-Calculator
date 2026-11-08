// not actual main.cpp implemention, just the haversine helper function 
#include <cmath>
//other includes here


//haversine distance between two points **IN MILES NOT KM
double haversine(double lat1, double long1, double lat2, double long2){
    const double R = 3958.8;
    const double rad = 3.14159265358979323846 / 180.0; //pi to 20 digits :sob:
    double distancelat = (lat2 - lat1) * rad;
    double distancelong = (long2 - long1) * rad;
    double a = std::sin(distancelat/2) * std::sin(distancelat/2) + std::cos (lat1 * rad) * std::cos(lat2 * rad) * std::sin(distancelong/2) * std::sin(distancelong/2); //the haversine formula
    double miles = 2*R*std::asin(std::sqrt(a));
    return std::round(miles * 100.0) / 100.0; //round it to the nearest 0.01 miles
}

int main(){
    //implement stuff here
    // set gainesville as origin
    // read csv
    // build minheap and splay tree
    // connect to ui(?)
    return 0;
}