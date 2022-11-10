#include "Echiquier.h"
#include <string>

using namespace std;

Piece::Piece():m_nom("Vide"),m_n(-1), m_couleur(0){}
Piece::Piece(string nom, int couleur): m_nom(nom), m_couleur(couleur), m_n((int)nom[0]), m_aBouge(false){
    switch((int)m_nom[0]){
            case ((int)('P')) :
                break;
            case ((int)('T')) :
            {
                m_direction[0] = -10;
                m_direction[1] = 10;
                m_direction[2] = -1;
                m_direction[3] = 1;
                m_taille_dir = 4;
                break;
            }
            case ((int)('C')) :
            {
                int direction[8] = {-21, 21, -19, 19, 8, -8, 12, -12};
                for(int i=0;i<8;i++){
                    m_direction[i] = direction[i];
                }
                m_taille_dir = 8;
                break;
            }
            case ((int)('F')) :
            {
                int direction[4] = {-9,9,11,-11};
                for(int i=0;i<4;i++){
                    m_direction[i] = direction[i];
                }
                m_taille_dir = 4;
                break; 
            }
            case((int)('D')) :
            {
                int direction[8] = {-9, 9, -11, 11, -10, 10, -1, 1};
                for(int i=0;i<8;i++){
                    m_direction[i] = direction[i];
                }
                m_taille_dir = 8;
                break;
            }
            case ((int)('R')) : 
            {
                int direction[8] = {-9, 9, -11, 11, -10, 10, -1, 1};
                for(int i=0;i<8;i++){
                    m_direction[i] = direction[i];
                }
                m_taille_dir = 8;
                break;
            }
        }
}
string Piece::getNom(){
    return m_nom;
}
int Piece::getCouleur(){
    return m_couleur;
}
int Piece::getN(){
    return m_n;
}
bool Piece::getMoved() {
    return m_aBouge;
}

int* Piece::getDirection() {
    return m_direction;
}

int Piece::getTaille() {
    return m_taille_dir;
}

void Piece::setaBouge(){
    m_aBouge = true;
}
