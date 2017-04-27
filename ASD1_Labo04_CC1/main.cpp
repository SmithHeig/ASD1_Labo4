// PROGRAMME DE TEST CC1

#include "liste.cpp"
#include <random>

int main() {

    const int N = 10;

    cout << "Creation d'une liste de " << N << " entiers aléatoires \n";
    LinkedList<int> liste;
    for (unsigned i = 0; i < N; ++i) {
        liste.push_front(rand()%100);
    }
    cout << "\n" << liste;

    cout << "\nModification de l'élément en tête à 42 \n";
    liste.front() = 42;
    cout << "\n" << liste;

    cout << "\nModification de l'élément en position " << N/2 << " à 24 \n";
    liste.at(N/2) = 24;
    cout << "\n" << liste;

    cout << "\nSuppression de l'élément en position " << 2*N/3 << "\n";
    liste.erase(2*N/3);
    cout << "\n" << liste;

    cout << "\nInsertion de l'élément 421 en position 0\n";
    liste.insert(421, 0);
    cout << "\n" << liste;

    cout << "\nInsertion de l'élément 422 en position " << N/3 << "\n";
    liste.insert(422, N/3);
    cout << "\n" << liste;

    cout << "\nInsertion de l'élément 423 en dernière position\n";
    liste.insert(423, liste.size());
    cout << "\n" << liste;

    cout << "\nDestruction de la liste \n";
}