#ifndef DEF_PIECE
#define DEF_PIECE
#include <string>

class Piece
{
    public:
    Piece();
    Piece(std::string nom, int couleur);
    std::string getNom();
    int getCouleur();
    int getN();
    bool getMoved();
    int* getDirection();
    int getTaille();
    void setaBouge();

    std::string m_nom;
    int m_n;
    int m_couleur;
    bool m_aBouge;
    int m_direction[8];
    int m_taille_dir;
};

#endif