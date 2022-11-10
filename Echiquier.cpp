#include "Echiquier.h"
#include <iostream>

using namespace std;

Echiquier::Echiquier(){
    m_plateau[0] = Piece("Tour", noir);
    m_plateau[1] = Piece("Cavalier", noir);
    m_plateau[2] = Piece("Fou", noir);
    m_plateau[3] = Piece("Dame", noir);
    m_plateau[4] = Piece("Roi", noir);
    m_plateau[5] = Piece("Fou", noir);
    m_plateau[6] = Piece("Cavalier", noir);
    m_plateau[7] = Piece("Tour", noir);
    for (int i=8;i<16;i++){
        m_plateau[i]=Piece("Pion", noir);
    }
    for (int x=16;x<48;x++){
        m_plateau[x]=Piece();
    }
    for(int j=48;j<56;j++){
        m_plateau[j]=Piece("Pion", blanc);
    }
    m_plateau[56] = Piece("Tour", blanc);
    m_plateau[57] = Piece("Cavalier", blanc);
    m_plateau[58] = Piece("Fou", blanc);
    m_plateau[59] = Piece("Dame", blanc);
    m_plateau[60] = Piece("Roi", blanc);
    m_plateau[61] = Piece("Fou", blanc);
    m_plateau[62] = Piece("Cavalier", blanc);
    m_plateau[63] = Piece("Tour", blanc);

    m_trait = blanc;

    for(int i=0;i<15;i++){
        m_map[i]=1;
    }
    for(int i=15;i<48;i++){
        m_map[i]=0;
    }
    for(int i=48;i<64;i++){
        m_map[i]=1;
    }
}

Echiquier::Echiquier(Piece plateau[64], int map[64]){
    copy(plateau, plateau+64, m_plateau);
    copy(map, map+64, m_map);
}

Piece* Echiquier::getPlateau(){
    return m_plateau;
}

int* Echiquier::getMap() {
    return m_map;
}

int Echiquier::getTrait(){
    return m_trait;
}

bool Echiquier::estVide(int caseE_64){
    return m_plateau[Echiquier::m_tab120[caseE_64]].getN()==-1;
}

bool Echiquier::isIn(int caseE){
    return Echiquier::m_tab120[caseE]!=-1;
}

bool Echiquier::pieceAdverse(int caseE_64, int couleur){
    return (!estVide(caseE_64) && m_plateau[Echiquier::m_tab120[caseE_64]].getCouleur()!=couleur);
}

void Echiquier::faire_coup(int case_depart, int case_arrivee){
    Piece p = m_plateau[case_depart];
    m_plateau[case_depart] = Piece();
    m_map[case_depart]=0;
    m_plateau[case_arrivee] = p;
    m_map[case_arrivee]=1;
}

void Echiquier::changeTrait(){
    m_trait = m_trait*-1;
}

void Echiquier::toString(){
    for(int i=0;i<8;i++){
        for (int j=0;j<8;j++){
            cout << m_plateau[8*i+j].getNom()[0];
            cout << "  ";
        }
        cout << "\n";
    }
}

const int Echiquier::m_tab120[120] = {
-1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
-1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
-1,  0,  1,  2,  3,  4,  5,  6,  7, -1,
-1,  8,  9, 10, 11, 12, 13, 14, 15, -1,
-1, 16, 17, 18, 19, 20, 21, 22, 23, -1,
-1, 24, 25, 26, 27, 28, 29, 30, 31, -1,
-1, 32, 33, 34, 35, 36, 37, 38, 39, -1,
-1, 40, 41, 42, 43, 44, 45, 46, 47, -1,
-1, 48, 49, 50, 51, 52, 53, 54, 55, -1,
-1, 56, 57, 58, 59, 60, 61, 62, 63, -1,
-1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

const int Echiquier::m_tab64[64] = {
21, 22, 23, 24, 25, 26, 27, 28,
31, 32, 33, 34, 35, 36, 37, 38,
41, 42, 43, 44, 45, 46, 47, 48,
51, 52, 53, 54, 55, 56, 57, 58,
61, 62, 63, 64, 65, 66, 67, 68,
71, 72, 73, 74, 75, 76, 77, 78,
81, 82, 83, 84, 85, 86, 87, 88,
91, 92, 93, 94, 95, 96, 97, 98};

const map<string, int> Echiquier::m_coordonnees = {
{"a8",0,},{"b8",1,},{"c8",2,},{"d8",3,},{"e8",4,},{"f8",5,},{"g8",6,},{"h8",7,},
{"a7",8,},{"b7",9,},{"c7",10,},{"d7",11,},{"e7",12,},{"f7",13,},{"g7",14,},{"h7",15,},
{"a6",16,},{"b6",17,},{"c6",18,},{"d6",19,},{"e6",20,},{"f6",21,},{"g6",22,},{"h6",23,},
{"a5",24,},{"b5",25,},{"c5",26,},{"d5",27,},{"e5",28,},{"f5",29,},{"g5",30,},{"h5",31,},
{"a4",32,},{"b4",33,},{"c4",34,},{"d4",35,},{"e4",36,},{"f4",37,},{"g4",38,},{"h4",39,},
{"a3",40,},{"b3",41,},{"c3",42,},{"d3",43,},{"e3",44,},{"f3",45,},{"g3",46,},{"h3",47,},
{"a2",48,},{"b2",49,},{"c2",50,},{"d2",51,},{"e2",52,},{"f2",53,},{"g2",54,},{"h2",55,},
{"a1",56,},{"b1",57,},{"c1",58,},{"d1",59,},{"e1",60,},{"f1",61,},{"g1",62,},{"h1",63,}}; 

int m_map[64];

const int Echiquier::blanc=-1;
const int Echiquier::noir=1;
int m_trait;
Piece m_plateau[64];

