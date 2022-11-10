#ifndef DEF_GAME
#define DEF_GAME

#include <string>
#include <vector>
#include "Echiquier.h"

class Game
{
    public:
    Game();
    Echiquier m_Echiquier;
    std::vector<int> coup_potentiel(int case_depart);
    bool jouer_coup(std::string case_depart, std::string case_arrivee);
    bool jouer_coup(int case_depart, int case_arrivee);
    bool estEchec(int couleur, int loc);
    bool estEchec(int couleur);
    bool estEchecEtMat(int couleur);
    int getLocRoi(int couleur);
    void faire_coup(int case_depart, int case_arrivee);
    bool RoquePossible(int case_depart, int case_arrivee);
    Echiquier getEchiquier();

    int m_dernier_coup[2];
    int loc_Roi_blanc;
    int loc_Roi_noir;
    static const std::vector<int> pion_depart;
};
#endif