//coucou
//
//  LinkedList.cpp
//
//  Copyright (c) 2016 Olivier Cuisenaire. All rights reserved.
//

#include <iostream>
#include <stdexcept>
using namespace std;

/// Forward declaration classe
template < typename T > class LinkedList;

/// Forward declaration fonction d'affichage
template <typename T>
ostream& operator << (ostream& os, const LinkedList<T>& liste);

/// Classe de liste chainee
template < typename T > class LinkedList {

    friend ostream& operator << <T>(ostream& os, const LinkedList<T>& liste);

public:
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;

private:
    /**
    *  @brief Maillon de la chaine.
    *
    * contient une valeur et le lien vers le maillon suivant.
    */
    struct Node {
        value_type data;
        Node* next;
        Node(const_reference data, Node* next = nullptr)
                : data(data), next(next) {
            cout << "(C" << data << ") ";
        }
        Node(Node&) = delete;
        Node(Node&&) = delete;
        ~Node()
        {
            cout << "(D" << data << ") ";
        }
    };

private:
    /**
     *  @brief  Tete de la LinkedList
     */
    Node* head;

private:
    /**
     *  @brief Nombre d'éléments
     */
    size_t nbElements;

public:
    /**
     *  @brief Constructeur par défaut. Construit une LinkedList vide
     *
     */
    LinkedList() /* ... */
    {
        head = nullptr;
        nbElements = 0;
    }

public:
    /**
     *  @brief Constructeur de copie
     *
     *  @param other la LinkedList à copier
     */
    LinkedList( LinkedList& other ) /* ... */ {
        (*this) = other;
    }

public:
    /**
     *  @brief Opérateur d'affectation par copie
     *
     *  @param other la LinkedList à copier
     *
     *  @return la LinkedList courante *this (par référence)
     *
     *  @remark l'opérateur doit être une no-op si other
     *  est la LinkedList courante.
     *
     *  @remark le contenu précédent de la LinkedList courante est
     *  effacé.
     */
    LinkedList& operator = ( const LinkedList& other ) {
        head = other.head;
        nbElements = other.nbElements;
        return *this;
        /** Doit on supprimé les éléments du tableau qui se fait ecrasé ?*/
    }

public:
    /**
     *  @brief destructeur
     */
    ~LinkedList() {
        for(unsigned i = 0; i < nbElements - 1; ++i){
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        delete head; // supprimer le dernier élément
        nbElements = 0; //Useless ?
    }

public:
    /**
     *  @brief nombre d'éléments stockés dans la liste
     *
     *  @return nombre d'éléments.
     */
    size_t size() const noexcept {
        return nbElements;
    }

public:
    /**
     *  @brief insertion d'une valeur dans un maillon en tête de liste
     *
     *  @param value la valeur à insérer
     *
     *  @exception std::bad_alloc si pas assez de mémoire, où toute autre exception lancée par la constructeur de copie de value_type
     */
    void push_front( const_reference value) {
        head = new Node(value,head);
        ++nbElements;
    }

public:
    /**
     *  @brief accès (lecture/écriture) à la valeur en tête de LinkedList
     *
     *  @return référence à cette valeur
     *
     *  @exception std::runtime_error si la liste est vide
     */
    reference front() {
        /* Doit géré les execptions encore */
        return (*head).data;
    }

    const_reference front() const {
        const unsigned front_data = (*head).data;
        return front_data;
    }

public:
    /**
     *  @brief Suppression de l'élément en tête de LinkedList
     *
     *  @exception std::runtime_error si la liste est vide
     */
    void pop_front( ) {
        Node* temp = head;
        head = head->next;
        delete temp;
        nbElements--;
    }

public:
    /**
     *  @brief Insertion en position quelconque
     *
     *  @param value la valeur à insérer
     *  @param pos   la position où insérer, 0 est la position en tete
     *
     *  @exception std::out_of_range("LinkedList::insert") si pos non valide
     *
     *  @exception std::bad_alloc si pas assez de mémoire, où toute autre exception lancée par la constructeur de copie de value_type
     */
    void insert( const_reference value, size_t pos ) {
        if(pos == 0){
            this->push_front(value);
        } else {
            if(pos == this->size()){
                --pos;
            }
            Node* temp = head;
            for(unsigned i = 0; i < pos -1; ++i){
                temp = temp->next;
            }
            Node* n = new Node(value, temp->next);
            temp->next = n;
        }
        ++nbElements;
    }

public:
    /**
     *  @brief Acces à l'element en position quelconque
     *
     *  @param pos la position, 0 est la position en tete
     *
     *  @exception std::out_of_range("LinkedList::at") si pos non valide
     *
     *  @return une reference a l'element correspondant dans la liste
     */
    reference at(size_t pos) {
        Node* temp = head;
        for(size_t i = 0; i < pos; ++i){
            temp = temp->next;
        }
        return (*temp).data;
    }

    /**
     *  @brief Acces à l'element en position quelconque
     *
     *  @param pos la position, 0 est la position en tete
     *
     *  @exception std::out_of_range("LinkedList::at") si pos non valide
     *
     *  @return une const_reference a l'element correspondant dans la liste
     */
    const_reference at(size_t pos) const {
        Node* temp = head;
        /* element avant l'élément à insérer */
        for(unsigned i = 0; i < pos; ++i){
            temp = temp->next;
        }
        return (*temp).data;
    }

public:
    /**
     *  @brief Suppression en position quelconque
     *
     *  @param pos la position, 0 est la position en tete
     *
     *  @exception std::out_of_range("LinkedList::erase") si pos non valide
     */
    void erase( size_t pos ) {
        if(pos == 0){
            Node* temp = head;
            head = head->next;
            delete temp;
        } else {
            Node* temp = head;
            for(unsigned i = 0; i < pos - 1; ++i){
                temp = temp->next;
            }
            Node* toDelete = temp->next;
            temp->next = temp->next->next;
            delete toDelete;
        }
        --nbElements;
    }

public:
    /**
     *  @brief Recherche du premier élément correspondant
        à une valeur donnée dans la liste
     *
     *  @param value la valeur à chercher
     *
     *  @return la position dans la liste. -1 si la valeur
        n'est pas trouvée
     */
    size_t find( const_reference value ) const noexcept {
        /* ... */
    }

    /**
     *  @brief Tri des elements de la liste par tri fusion
     */
    void sort() {
        /* ... */
    }

};

template <typename T>
ostream& operator << (ostream& os, const LinkedList<T>& liste) {
    os << liste.size() << ": ";
    auto n = liste.head;
    while (n) {
        os << n->data << " ";
        n = n->next;
    }
    return os;
}
