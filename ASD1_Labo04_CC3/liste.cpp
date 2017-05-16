//
//  LinkedList.cpp
//
//  Labo James Smith Guillaume Schranz et Joel Schär
//
//  Copyright (c) 2016 Olivier Cuisenaire. All rights reserved.
//

#include <iostream>
#include <stdexcept>
#include <stdlib.h>     // srand, rand

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
    * @brief Maillon de la chaine.
    *
    * contient une valeur et le lien vers le maillon suivant.
    */
    struct Node {
        value_type data;
        Node* next;
        Node(const_reference data, Node* next = nullptr): data(data), next(next) {
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
   LinkedList(const LinkedList& other): 
      head(new Node{other.head->data, other.head->next}) ,
                  nbElements(other.nbElements){
      
      Node* prec     = head;
      Node* aCopier  = other.head;

      while (aCopier->next != nullptr) {
          aCopier = aCopier->next;
          Node* aAjouter = new Node(aCopier->data, nullptr);
          
          prec->next = aAjouter;
          prec = aAjouter;
      }  
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
        LinkedList tmp = other;
        swap(head, tmp.head);
        swap(nbElements, tmp.nbElements);
        
        return *this;
    }

public:
    /**
     *  @brief destructeur
     */
    ~LinkedList() {
        for(unsigned i = 0; i < nbElements;++i){
            Node* temp = head;
            head = head->next;
            delete temp;
        }
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
       try{
         head = new Node(value,head);
         ++nbElements;
       }
       catch(...){
          
       }
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
       if (!nbElements){
          throw std::runtime_error("empty_list");
       }
       else {
          return head->data;
       }
    }
    
    const_reference front() const {
         return head->data;
    }

public:
    /**
     *  @brief Suppression de l'élément en tête de LinkedList
     *
     *  @exception std::runtime_error si la liste est vide
     */
    void pop_front( ) {
      if(head == nullptr){
         throw runtime_error("empty_list"); 
      }
      else {
         Node* temp = head;
         head = head->next;
         delete temp;
         nbElements--;
       }
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
         return push_front(value);
      } 
      Node* current = head;
      if (pos > nbElements) {
         throw std::out_of_range("LinkedList::insert");
      }
      for(size_t i = 0; i < pos-1; ++i){
            current = current->next;
      }
      Node* temp = current;

      temp->next = new Node(value, temp->next);
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
      if (pos >= nbElements){
         throw std::out_of_range("LinkedList::at");
      }
      else {
         Node* temp = head;
         for(size_t i = 0; i < pos; ++i){
             temp = temp->next;
      }
      return temp->data; 
      }
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
        if(pos >= size()){
            throw(out_of_range("LinkedList::at"));
        }
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
         if(pos >= nbElements){
            throw std::out_of_range("LinkedList::erase");
         }
         else {
            if(pos == 0){
                Node* temp = head;
                head = head->next;
                delete temp;
            } 
            else {
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
        Node* temp = head;
        for(unsigned i = 0; i < nbElements; ++i){
            if(temp->data == value){
                return i;
            }
            temp = temp->next;
        }
        return -1;
    }

    /**
     *  @brief Tri des elements de la liste par tri fusion
     */
    Node*& merge(Node*& start, Node* mid, Node* end){

        cout << "before merge :" << (*this) << "  " << start->data << mid -> data << endl;

        Node** cur = &start;
        Node* curMid = mid;
        Node* curStart = start;
        Node* temp;

            while(curStart != mid && curMid != end) {

                if (curStart->data < curMid->data) {
                    *cur = curStart;
                    curStart = curStart->next;

                } else {
                    temp = curMid->next;
                    curMid->next = *cur;
                    *cur = curMid;
                    curMid = temp;
                }
                    cur = &((*cur)->next);
            }

            while(curStart != mid){
                *cur = curStart;
                curStart = curStart->next;
                cur = &(*cur)->next;
            }
            while(curMid != end){
                *cur = curMid;
                curMid = curMid->next;
                cur = &(*cur)->next;
            }

           *cur = end;

        cout << "after merge  :" << (*this) << endl;
        return *cur;

    }

    Node*& mergeSort(Node*& start, size_t n){
        Node** cur = &start;
        cout << "\n n1 : " << n << endl;

        for(size_t i=0; i<n; ++i){
            cout << (*cur)->data << " ";
            cur = &(*cur)->next;
        }

        if(n<=1)
            return start->next;


        Node* half = mergeSort(start, n/2);
        Node* full = mergeSort(half, (n+1)/2);


        cout << "\n n2 : " << n << endl;

        for(size_t i=0; i<n+(n/2); ++i){
            cout << (*cur)->data << " ";
            cur = &(*cur)->next;
        }
     /*   for(size_t i=0; i<n/2; ++i){
            half = half->next;
            full = full->next->next;
        }
        cout<<endl;*/

        //half = mergeSort(start, n/2);
        //full = mergeSort(half, (n+1)/2);



        return merge(start, half, full);;

    }

    void sort() {
        if(nbElements <= 1)
            return;
/*
        size_t mid = nbElements/2;

        Node* leftHead = head;
        Node* rightHead = head;
        for(size_t i = 0; i < mid; ++i){
            rightHead = rightHead->next;
        }



        Node* half = head;
        Node* full = head;
        while(full && full->next){
            half = half->next;
            full = full->next->next;
        }
*/
        mergeSort(head,nbElements);

/*
        LinkedList<T> leftListe;
        leftListe.head = this->head;


        LinkedList<T> rightListe;
        rightListe.head = half;
        for(size_t i = 0; i < nbElements - mid; ++i){
            rightListe.insert(this->at(i + mid), i);
        }

        cout << "half" << half->data << endl;
*/

        //cout << "\n\n" << *this << "        " << leftHead->data << "|" <<leftListe << "         "<< rightHead->data << "|" << rightListe <<"\n\n";



        //fusionner(leftHead, rightHead);

    } // end sort
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
