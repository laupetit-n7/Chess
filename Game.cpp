#include "Game.h"
#include <bits/stdc++.h>
using namespace std;

const vector<int> Game::pion_depart = {-55,-54,-53,-52,-51,-50,-49,-48,8,9,10,11,12,13};

Game::Game(){
    Echiquier m_Echiquier = Echiquier();
    m_dernier_coup[0]=-1;
    m_dernier_coup[1]=-1;
    loc_Roi_blanc = 60;
    loc_Roi_noir = 4;
}

bool Game::jouer_coup(string case_depart, string case_arrivee){
    int i = Echiquier::m_coordonnees.at(case_depart);
    int j = Echiquier::m_coordonnees.at(case_arrivee);
    return jouer_coup(i,j);
}

bool Game::jouer_coup(int case_depart, int case_arrivee){
    if( case_arrivee < 0 || case_arrivee > 63 || case_depart<0 || case_depart>63){
        return false; 
    }
    Piece* plateau = m_Echiquier.getPlateau();
    int* map = m_Echiquier.getMap();
    Echiquier tmp_ech = Echiquier(plateau, map);
    Piece p = plateau[case_depart];
    int couleur = p.getCouleur();
    int trait = m_Echiquier.getTrait();
    if (couleur!=trait){
        return false;
    }
    else {
        vector<int> coups = coup_potentiel(case_depart);
        for (vector<int>::iterator it = coups.begin() ; it != coups.end(); ++it){
        }
        if (binary_search(coups.begin(),coups.end(),case_arrivee)){
            //Roque
            if (p.getNom()=="Roi" && abs(case_arrivee-case_depart)==2 && RoquePossible(case_depart, case_arrivee)){
                // TODO m_Echiquier.faire_coup()
            }
            m_Echiquier.faire_coup(case_depart ,case_arrivee);
            if (!estEchec(couleur)){
                p.setaBouge();
                if (p.getN()==(int)('R') && couleur==m_Echiquier.blanc){
                    loc_Roi_blanc = case_arrivee;
                }
                else if (p.getN()==(int)('R') && couleur==m_Echiquier.noir){
                    loc_Roi_noir = case_arrivee;
                }
                m_dernier_coup[0] = case_depart;
                m_dernier_coup[1] = case_arrivee;
                m_Echiquier.changeTrait();
                return true;
            }
            else {
                m_Echiquier.faire_coup(case_arrivee, case_depart);
                return false;
            }
        }
        else {
            return false;
        }
    }
}



vector<int> Game::coup_potentiel(int case_depart){
    vector<int> coups;
    Piece* plateau = m_Echiquier.getPlateau();
    int case_courante = m_Echiquier.m_tab64[case_depart];
    int case_64_120 = m_Echiquier.m_tab64[case_depart];
    if (case_depart>=0 && case_depart<=63 && !m_Echiquier.estVide(case_64_120)){
        Piece p = plateau[case_depart];
        int* direction = p.getDirection();
        int taille = p.getTaille();
        int couleur = p.getCouleur();
        switch(p.getN()){
            case ((int)('P')) :
            {
                int pionAvance = case_64_120+10*couleur;
                int pionAvance2 = case_64_120 + 10*2*couleur;
                int pionMangeG = case_64_120 + 11*couleur;
                int pionMangeD = case_64_120 + 9*couleur;
                if (m_Echiquier.isIn(pionAvance) && m_Echiquier.estVide(pionAvance)){
                    coups.push_back(m_Echiquier.m_tab120[pionAvance]);
                }
                if (m_Echiquier.estVide(pionAvance2) && binary_search(pion_depart.begin(),pion_depart.end(),case_depart*couleur)){
                    coups.push_back(m_Echiquier.m_tab120[pionAvance2]);
                }
                if (m_Echiquier.isIn(pionMangeG) && m_Echiquier.pieceAdverse(pionMangeG, couleur)){
                    coups.push_back(m_Echiquier.m_tab120[pionMangeG]);
                }
                if (m_Echiquier.isIn(pionMangeD) && m_Echiquier.pieceAdverse(pionMangeD, couleur)){
                    coups.push_back(m_Echiquier.m_tab120[pionMangeD]);
                }
                if (plateau[m_dernier_coup[1]].getN() == (int)('P') && abs(m_dernier_coup[1] - m_dernier_coup[0])==16 && abs(m_dernier_coup[1]-case_depart)==1){
                    coups.push_back(m_dernier_coup[1]+couleur*8);
                }
                break;
            }
            case ((int)('R')) : 
            {
                for (int ind_Direction=0;ind_Direction<taille;ind_Direction++){
                    case_courante = case_64_120 + direction[ind_Direction];
                    if (m_Echiquier.isIn(case_courante) && (plateau[m_Echiquier.m_tab120[case_courante]].getN()==-1 or plateau[m_Echiquier.m_tab120[case_courante]].getCouleur()!=couleur)){
                        coups.push_back(m_Echiquier.m_tab120[case_courante]);
                    }
                }
                if (!p.getMoved()){
                    if (plateau[case_depart-4].getN()==(int)('T') && !plateau[case_depart-4].getMoved() && m_Echiquier.estVide(case_64_120-1) && m_Echiquier.estVide(case_64_120-2)){
                        coups.push_back(case_depart-2);
                    }
                    if (plateau[case_depart+3].getN()==(int)('T') && !plateau[case_depart+3].getMoved()&&  m_Echiquier.estVide(case_64_120+1) && m_Echiquier.estVide(case_64_120+2)){
                        coups.push_back(case_depart+2);
                    }
                }
                break;
            }
            case ((int)('C')) :
            {
                for (int ind_Direction=0;ind_Direction<taille;ind_Direction++){
                    case_courante = case_64_120 + direction[ind_Direction];
                    if (m_Echiquier.isIn(case_courante) && (plateau[case_courante].getN()==-1 or plateau[case_courante].getCouleur()!=couleur)){
                        coups.push_back(m_Echiquier.m_tab120[case_courante]);
                    }
                }
                break;
            }
            default :
            {
                for (int ind_Direction=0;ind_Direction<taille;ind_Direction++){
                    case_courante = case_64_120 + direction[ind_Direction];
                    while (m_Echiquier.isIn(case_courante) && m_Echiquier.estVide(case_courante)){
                        coups.push_back(m_Echiquier.m_tab120[case_courante]);
                        case_courante = case_courante + direction[ind_Direction];
                    }
                    if (m_Echiquier.pieceAdverse(m_Echiquier.m_tab120[case_courante], couleur)){
                        coups.push_back(m_Echiquier.m_tab120[case_courante]);
                    }
                }
                break;
            }
            
        }
    }
    sort(coups.begin(),coups.end());
    return coups;
};

bool Game::estEchec(int couleur, int loc){
    int old_pos_roi = getLocRoi(couleur);
    m_Echiquier.faire_coup(old_pos_roi, loc);
    bool res = estEchec(couleur);
    m_Echiquier.faire_coup(loc, old_pos_roi);
    return res;
}

bool Game::estEchec(int couleur){
    bool res = false;
    int *map = m_Echiquier.getMap();
    Piece* plateau = m_Echiquier.getPlateau();
    int loc;
    if (couleur == Echiquier::blanc){
        loc = loc_Roi_blanc;
    }
    else if(couleur == Echiquier::noir){
        loc = loc_Roi_noir;
    }
    for (int i=0;i<64;i++){
        if (plateau[i].getN()!=-1 && plateau[i].getCouleur()!=couleur){
            vector<int> deplacement = coup_potentiel(i);
            if (binary_search(deplacement.begin(),deplacement.end(), loc)){  
                return true;
            }
        }
    }
    return false;
};

bool Game::estEchecEtMat(int couleur){
    int *map = m_Echiquier.getMap();
    Piece* plateau = m_Echiquier.getPlateau();
    if (!estEchec(couleur)){
        return false;
    }
    else {
        int i=0;
        while (i<64){
            if (plateau[i].getCouleur()==couleur){
                Piece p = plateau[i];
                vector <int> coups = coup_potentiel(i);
                for(vector<int>::iterator it=coups.begin(); it!=coups.end();++it){
                    m_Echiquier.faire_coup(i, *it);
                    if (!estEchec(couleur)){
                        m_Echiquier.faire_coup(*it,i);
                        return false;
                    }
                    m_Echiquier.faire_coup(*it,i);
                }
            }
            i++;
        }
        return true;
    }
}

bool Game::RoquePossible(int case_depart, int case_arrivee){
    Piece* plateau = m_Echiquier.getPlateau();
    Piece p = plateau[case_depart];
    for (int i=case_depart;i<=case_arrivee; i+= (case_arrivee-case_depart)/2){
        if (!estEchec(p.getCouleur(), i)){
            return false;
        }
    }
    return true;
}

int Game::getLocRoi(int couleur){
    if (couleur==m_Echiquier.blanc){
        return loc_Roi_blanc;
    }
    else if (couleur==m_Echiquier.noir){
        return loc_Roi_noir;
    }
    else {
        return -1;
    }
}

Echiquier Game::getEchiquier(){
    return m_Echiquier;
}