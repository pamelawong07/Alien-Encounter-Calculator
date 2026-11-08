#ifndef FRONTEND_FUNCTIONS_H
#define FRONTEND_FUNCTIONS_H

#include <QObject>
#include <QtQml>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include "copied_classes/encounter.h"
using namespace std;

class Frontend_functions : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList cities_select READ cities_select NOTIFY toggle_city_select)
    QML_ELEMENT
    int textCounter;
    bool splay_min;     //0: splay 1: minheap
    vector<string> splaydata;
    vector<string> mindata;
    float mintime;
    float splaytime;
    string curr_city;
    string selected_state;
    int num_encounters;
    int total_encounters;
    unordered_map<string, set<string>> state_cities;
    QStringList cities_select_list;

public:
    //constructor
    explicit Frontend_functions(QObject *parent = nullptr);
    QStringList cities_select() const;
    void init_cities();
    //updates splaydata and mindata whenever "calculate probability" is run
    Q_INVOKABLE void getData();
    //gets current text (report) to be shown in box
    Q_INVOKABLE QString getText();
    //gets time to display
    Q_INVOKABLE QString getTime();
    Q_INVOKABLE QString getState();
    Q_INVOKABLE void toggleCounter(bool direction);
    Q_INVOKABLE void toggleSplay();
    Q_INVOKABLE void toggleMin();
    Q_INVOKABLE void processClick(int x, int y);
    Q_INVOKABLE void setCurr_city(QString city);
    Q_INVOKABLE void submitReport(QString city, QString desc);
    void retrieveOptions(string state);

signals:
    //void buttonClicked();
    void toggle_city_select();
};

#define alabama_c "#d9833f"
#define alaska_c  "#a3c0d9"
#define arizona_c  "#cf7f34"
#define arkansas_c  "#ac73d1"
#define california_c  "#e7e349"
#define colorado_c  "#81db99"
#define connecticut_c  "#81dbc9"
#define delaware_c  "#ec3921"
#define florida_c  "#5e6de9"
#define georgia_c  "#e484ce"
#define hawaii_c  "#6bdb2f"
#define idaho_c  "#ae66e9"
#define illinois_c  "#e9bf66"
#define indiana_c  "#24caa4"
#define iowa_c  "#da71dd"
#define kansas_c  "#717ddd"
#define kentucky_c  "#f06222"
#define louisiana_c  "#77a971"
#define maine_c  "#a88cf3"
#define maryland_c  "#f3f222"
#define massachusetts_c  "#f0ad94"
#define michigan_c  "#252add"
#define minnesota_c  "#48e2a0"
#define mississippi_c  "#c83175"
#define missouri_c  "#1c7dd6"
#define montana_c  "#6da8dd"
#define nebraska_c  "#8d4c53"
#define nevada_c  "#2d8d41"
#define newhampshire_c  "#2d398d"
#define newjersey_c  "#b60960"
#define newmexico_c  "#24d7e0"
#define newyork_c  "#be2e0b"
#define northcarolina_c  "#c8f38c"
#define northdakota_c  "#82b35a"
#define ohio_c  "#c8f570"
#define oklahoma_c  "#d1392b"
#define oregon_c  "#f3c027"
#define pennsylvania_c  "#f39cd1"
#define rhodeisland_c  "#e07538"
#define southcarolina_c  "#9d6f8b"
#define southdakota_c  "#8d110b"
#define tennessee_c  "#db5e58"
#define texas_c  "#091de7"
#define utah_c  "#9059bc"
#define vermont_c  "#b905e2"
#define virginia_c  "#a25ab3"
#define washington_c  "#466df3"
#define westvirginia_c  "#44a00d"
#define wisconsin_c  "#e45eb2"
#define wyoming_c  "#87addb"


#endif // FRONTEND_FUNCTIONS_H
