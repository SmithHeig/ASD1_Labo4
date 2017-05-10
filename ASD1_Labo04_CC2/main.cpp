// PROGRAMME DE TEST CC1

#include "liste.cpp"
#include <random>

int main() {

    const int N = 9;

    cout << "Creation d'une liste de " << N << " entiers aléatoires \n";
    LinkedList<int> liste;
    for (unsigned i = 0; i < N; ++i) {
        liste.push_front(rand()%100);
    }
    cout << "\n" << liste;

    cout << "\nModification de l'élément en tête à 42";
    liste.front() = 42;
    cout << "\n" << liste;

    cout << "\nModification de l'élément en position " << N/2 << " à 43";
    liste.at(N/2) = 43;
    cout << "\n" << liste;

    cout << "\nSuppression de l'élément en position " << N/3 << "\n";
    liste.erase(N/3);
    cout << "\n" << liste;

    cout << "\nSuppression de l'élément en dernière position \n";
    liste.erase(liste.size()-1);
    cout << "\n" << liste;

    cout << "\nInsertion de l'élément 44 en position 0\n";
    liste.insert(44, 0);
    cout << "\n" << liste;

    cout << "\nInsertion de l'élément 45 en position " << N/3 << "\n";
    liste.insert(45, N/3);
    cout << "\n" << liste;

    cout << "\nInsertion de l'élément 46 en dernière position\n";
    liste.insert(46, liste.size());
    cout << "\n" << liste;

    cout << "\n\nRecherche d'elements allant de 0 à 99 \n";
    for(int i = 0; i < 100; ++i) {
        if(liste.find(i)!=-1)
            cout << '(' << i << ')';
    }

    {
        cout << "\n\nCreation d'une copie constante de la liste\n";
        const LinkedList<int> copie = liste;
        cout << "\n" << copie.size() << ": ";
        for(size_t i = 0; i < copie.size(); ++i)
            cout << copie.at(i) << " ";
        cout << "\nDestruction de la copie constante\n";
    }

    {
        cout << "\n\nCreation d'une copie de la liste\n";
        LinkedList<int> copie = liste;
        cout << "\nCopie - " << copie;

        cout << "\nSuppression des " << N/2 << " premiers éléments\n";
        for(int i = 0; i < N/2; ++i)
            copie.pop_front();
        cout << "\nCopie - " << copie;

        cout << "\nRecopie de la liste original dans la copie\n";
        copie = liste;

        cout << "\nCopie - " << copie;
        cout << "\nDestruction de la copie\n";
    }

    try {
        cout << "\n\nInsertion hors de range";
        liste.insert(42,liste.size()+1);
        cout << "\nException non levée";
    }
    catch( std::out_of_range& e ) {
        cout << "\nstd::out_of_range capturée ";
    }
    catch( ... ) {
        cout << "\nPas la bonne exception";
    }

    try {
        cout << "\nSuppression hors de range";
        liste.erase(liste.size());
        cout << "\nException non levée";
    }
    catch( std::out_of_range& e ) {
        cout << "\nstd::out_of_range capturée ";
    }
    catch( ... ) {
        cout << "\nPas la bonne exception";
    }

    try {
        cout << "\nAccès hors de range";
        liste.at(liste.size()) = 42;
        cout << "\nException non levée";
    }
    catch( std::out_of_range& e ) {
        cout << "\nstd::out_of_range capturée ";
    }
    catch( ... ) {
        cout << "\nPas la bonne exception";
    }

    {
        cout << "\nCreation d'une liste vide";
        LinkedList<double> listeVide;
        try {
            cout << "\nAccès à l'élément de tête";
            listeVide.front() = 1;
            cout << "\nException non levée";
        }
        catch( std::runtime_error& e ) {
            cout << "\nstd::runtime_error capturée ";
        }
        catch( ... ) {
            cout << "\nPas la bonne exception";
        }

        try {
            cout << "\nSuppression d'un élément";
            listeVide.pop_front();
            cout << "\nException non levée";
        }
        catch( std::runtime_error& e ) {
            cout << "\nstd::runtime_error capturée ";
        }
        catch( ... ) {
            cout << "\nPas la bonne exception";
        }
    }

    cout << "\nDestruction de la liste \n";

}