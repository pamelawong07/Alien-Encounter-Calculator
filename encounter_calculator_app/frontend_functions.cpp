#include "frontend_functions.h"
#include <qimage.h>

Frontend_functions::Frontend_functions(QObject *parent) : QObject(parent) {
    // splaydata = {"cba", "peepy"};
    // mindata = {"abc","peppy"};
    // splaytime = 0;
    // mintime = 3;
    // num_encounters = 100;
    total_encounters = 65115;

    textCounter = 0;
    splay_min = 0;
    curr_city = "gainesville";
    selected_state = "fl";
    this->init_cities();
    this->retrieveOptions(selected_state);
}

QStringList Frontend_functions::cities_select() const {
    return cities_select_list;
}

void Frontend_functions::init_cities(){
    //retrieve reported cities from csv
    ifstream cities_csv("../../copied_classes/ufo_clean.csv");
    string curr_city;
    string curr_state;
    string csv_line;
    if (!cities_csv.is_open()) {
        cout << "bad" << endl;
    }
    getline(cities_csv, csv_line);
    while (getline(cities_csv, csv_line)){
        stringstream s(csv_line);
        //cout << "a" << endl;
        getline(s, curr_city, ',');
        getline(s, curr_city, ',');
        getline(s, curr_state, ',');

        //remove quotations
        curr_city = curr_city.substr(1, curr_city.size()-2);
        curr_state = curr_state.substr(1, curr_state.size()-2);

        //scrub parentheses (and leading space) from city names if they exist
        int find_parentheses = curr_city.find('(');
        if (find_parentheses != string::npos){
            curr_city = curr_city.substr(0, find_parentheses-1);
        }

        if (state_cities.find(curr_state) != state_cities.end()){
            state_cities[curr_state].insert(curr_city);
        }
        else{
            state_cities[curr_state] = {curr_city};
        }
    }

    //for testing purposes
    // for (auto city : state_cities["tx"]){
    //     cout << "tx" << " " << city << endl;
    // }

    //getline(cities_csv, csv_line);
}

void Frontend_functions::getData(){
    vector<string> received_splaydata = {"abc","peppy"};    //will call backend functions
    vector<string> received_mindata = {"cba", "peepy"};     //instead of direct declaration when possible
    splaydata = received_splaydata;
    mindata = received_mindata;
    splaytime = 0;
    mintime = 3;
}

QString Frontend_functions::getText(){
    QString curr_text;
    string curr_city_cap = static_cast<char>(toupper(curr_city[0])) + curr_city.substr(1, curr_city.size()-1);
    if (textCounter == 0){
        float probability = 0.01;       //will get probability from backend function
        curr_text = QString::fromStdString("Your probability of encountering an alien in " + curr_city_cap + " is " + to_string(probability) + "%!");
        curr_text += QString::fromStdString("\n\nThere have been " + to_string(num_encounters) + " reported alien encounters in " + curr_city_cap + " out of " + to_string(total_encounters) +  " in the country.");
        curr_text += QString::fromStdString("\n\nClick the arrows below to read reported encounters, if any.");
    }
    else if (!splay_min)
        curr_text = QString::fromStdString(splaydata[textCounter-1]);
    else
        curr_text = QString::fromStdString(mindata[textCounter-1]);
    return curr_text;
}

QString Frontend_functions::getTime(){
    QString curr_text;
    if (!splay_min)
        curr_text = QString::fromStdString("TIME: " + to_string(splaytime) + " secs");
    else
        curr_text = QString::fromStdString("TIME: " + to_string(mintime) + " secs");
    return curr_text;
}

QString Frontend_functions::getState(){
    return QString::fromStdString(selected_state);
}

void Frontend_functions::toggleCounter(bool direction){
    if (direction == 0){    //left toggle
        if (textCounter > 0)
            textCounter--;
    }
    else{
        if (textCounter < splaydata.size())
            textCounter++;
    }
}

void Frontend_functions::toggleSplay(){
    splay_min = 0;
}

void Frontend_functions::toggleMin(){
    splay_min = 1;
}

void Frontend_functions::processClick(int x, int y){
    static QImage map(":/img/images/United-States-Country-colored.png");
    string col = (map.pixelColor(x, y).name()).toStdString();;
    if (col == florida_c)
        selected_state = "fl";
    else if (col == alabama_c)
        selected_state = "al";
    else if (col == alaska_c)
        selected_state = "ak";
    else if (col == arizona_c)
        selected_state = "az";
    else if (col == arkansas_c)
        selected_state = "ar";
    else if (col == california_c)
        selected_state = "ca";
    else if (col == colorado_c)
        selected_state = "co";
    else if (col == connecticut_c)
        selected_state = "ct";
    else if (col == delaware_c)
        selected_state = "de";
    else if (col == georgia_c)
        selected_state = "ga";
    else if (col == hawaii_c)
        selected_state = "hi";
    else if (col == idaho_c)
        selected_state = "id";
    else if (col == illinois_c)
        selected_state = "il";
    else if (col == indiana_c)
        selected_state = "in";
    else if (col == iowa_c)
        selected_state = "ia";
    else if (col == kansas_c)
        selected_state = "ks";
    else if (col == kentucky_c)
        selected_state = "ky";
    else if (col == louisiana_c)
        selected_state = "la";
    else if (col == maine_c)
        selected_state = "me";
    else if (col == maryland_c)
        selected_state = "md";
    else if (col == massachusetts_c)
        selected_state = "ma";
    else if (col == michigan_c)
        selected_state = "mi";
    else if (col == minnesota_c)
        selected_state = "mn";
    else if (col == mississippi_c)
        selected_state = "ms";
    else if (col == missouri_c)
        selected_state = "mo";
    else if (col == montana_c)
        selected_state = "mt";
    else if (col == nebraska_c)
        selected_state = "ne";
    else if (col == nevada_c)
        selected_state = "nv";
    else if (col == newhampshire_c)
        selected_state = "nh";
    else if (col == newjersey_c)
        selected_state = "nj";
    else if (col == newmexico_c)
        selected_state = "nm";
    else if (col == newyork_c)
        selected_state = "ny";
    else if (col == northcarolina_c)
        selected_state = "nc";
    else if (col == northdakota_c)
        selected_state = "nd";
    else if (col == ohio_c)
        selected_state = "oh";
    else if (col == oklahoma_c)
        selected_state = "ok";
    else if (col == oregon_c)
        selected_state = "or";
    else if (col == pennsylvania_c)
        selected_state = "pa";
    else if (col == rhodeisland_c)
        selected_state = "ri";
    else if (col == southcarolina_c)
        selected_state = "sc";
    else if (col == southdakota_c)
        selected_state = "sd";
    else if (col == tennessee_c)
        selected_state = "tn";
    else if (col == texas_c)
        selected_state = "tx";
    else if (col == utah_c)
        selected_state = "ut";
    else if (col == vermont_c)
        selected_state = "vt";
    else if (col == virginia_c)
        selected_state = "va";
    else if (col == washington_c)
        selected_state = "wa";
    else if (col == westvirginia_c)
        selected_state = "wv";
    else if (col == wisconsin_c)
        selected_state = "wi";
    else if (col == wyoming_c)
        selected_state = "wy";
    //cout << selected_state << endl;
    retrieveOptions(selected_state);
}

void Frontend_functions::setCurr_city(QString city){
    curr_city = city.toStdString();
}

void Frontend_functions::retrieveOptions(string state){
    cities_select_list.clear();
    for (const string& city : state_cities[state]){
        cities_select_list.append(QString::fromStdString(city));
        //cout << city << endl;
    }
    emit toggle_city_select();
}

void Frontend_functions::submitReport(QString city, QString desc){

}