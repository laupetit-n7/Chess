#include "Game.h"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[]){
    cout << "Jeux d'echecs\n";
    Game g = Game();
    Echiquier ech = g.getEchiquier();
    ech.toString();
    string case_depart;
    string case_arrivee;
    cout << "\nWhat is your move\n?";
    cin >> case_depart >> case_arrivee;
    while (g.jouer_coup(case_depart, case_arrivee)){ //&& !g.estEchecEtMat(1) && !g.estEchecEtMat(-1)){
        if(g.estEchec(1)){
            cout << "\nCheck!!!\n";
        }
        g.getEchiquier().toString();
        cout << "What is your move?";
        cin >> case_depart >> case_arrivee;
    }
    cout << "Fin du game";
}