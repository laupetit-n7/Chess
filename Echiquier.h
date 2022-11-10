#ifndef DEF_ECHIQUIER
#define DEF_ECHIQUIER
#include <string>
#include <vector>
#include <map>
#include "Piece.h"

class Echiquier
{
    public:
    Echiquier();
    Echiquier(Piece plateau[64], int map[64]);
    void setEchiquier(Piece plateau[64], int map[64]);
    Piece* getPlateau();
    int* getMap();
    int getTrait();
    bool estVide(int caseE);
    bool isIn(int caseE);
    bool pieceAdverse(int caseE, int couleur);
    void faire_coup(int case_depart, int case_arrivee);
    void toString();
    void changeTrait();

    static const std::map<std::string, int> m_coordonnees;
    static const int m_tab120[120];
    static const int m_tab64[64];
    static const int blanc;
    static const int noir;
    static const int axeH[2];
    static const int axeV[2];
    static const int axeD[4];
    int m_trait;
    int m_map[64];
    Piece m_plateau[64];
    
    
};
#endif