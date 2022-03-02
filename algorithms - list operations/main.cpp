//
//  main.cpp
//  algorithms - list operations
//
//  Created by Marcin Ostolski on 22/02/2022.
//

#include <iostream>
#include <stdlib.h>

using namespace std;

typedef int item_t;

typedef struct node
{
    item_t item;
    node* next_ptr;
} node_t;

typedef node_t *list_ptr_t;

// Wersja z przekazywaniem parametrów przez referencję
void create(list_ptr_t &list_ptr)
{
    if (list_ptr != NULL) {
        cout << "Lista juz istnieje. Nalezy ja najpierw skasowac.\n";
        return;
    }
    node_t *new_list_ptr = new node_t;
    new_list_ptr -> item = 0;
    new_list_ptr -> next_ptr = NULL;
    cout << "Lista zostala utworzona (tylko glowa).\n";
    list_ptr = new_list_ptr;
}

// Wersja z przekazywaniem parametrów przez wskaniki (wskanik do
// wskanika)
void create2(node_t **list_ptr)
{
    
}

// wstawienie x za elementem wskazywanym przez p
void insert(node_t *p, item_t x)
{
    node_t *old_list_ptr = p -> next_ptr;
    node_t *new_list_ptr = new node_t;
    new_list_ptr -> item = x;
    new_list_ptr -> next_ptr = old_list_ptr;
    
    p -> next_ptr = new_list_ptr;
}

// wypisuje liste zaczynajšc od elementu wskazywanego przez głowę
void print(node_t *list_ptr)
{
    if (list_ptr == NULL) {
        cout << "Błąd - przekazano wskaźnik pusty.\n";
        return;
    }
    node_t* p = list_ptr->next_ptr;
    cout << "Elementy listy: ";
    while (p != NULL ){
        cout << p -> item << " ";
        p = p -> next_ptr;
    }
    
    cout << endl;
    
}

// sprawdza czy x jest na liscie (funkcja iteracyjna)
bool found_iter(node_t *list_ptr, int x)
{
    if (list_ptr == NULL) {
        return false;
    }
    node_t *p = list_ptr -> next_ptr;
    if (p == NULL) {
        return false;
    }
    while (p != NULL) {
        if (p -> item == x) return true;
        p = p -> next_ptr;
    }
    return false;
    
}

void delete_next(node_t *p)
{
   
    if (p == NULL || p -> next_ptr == NULL) {
        cout << "Lista nie istnieje lub nie ma elementow.\n";
        return;
    }
    node_t *delete_element = p -> next_ptr;
    p -> next_ptr = (p -> next_ptr) -> next_ptr;
    int x = delete_element->item;
    delete delete_element ;
    cout << "Element " << x << " zostal bezpiecznie usuniety.\n";
    
    
}

void delete_list(list_ptr_t &list_ptr)
{
    if (list_ptr == NULL) {
        cout << "Blad: przekazano wskaznik pusty.\n";
        return;
    }
    node_t *p = list_ptr->next_ptr;
    while (p!=NULL){
        node_t *q;
        q = p-> next_ptr;
        delete p ;
        p = q;
    }
    delete list_ptr;
    list_ptr = NULL;
    
}

// usun wybrany element
void delete_x(node_t *list_ptr, node_t *d)
{
    node_t *p = list_ptr;
    if (list_ptr == d)
    {
        p=list_ptr->next_ptr;
        list_ptr=p;
        delete p;
    }
    else
    {
        p = list_ptr;
        while (p->next_ptr != d) p=p->next_ptr;
        p->next_ptr = d->next_ptr;
        delete d;
        
    }
    
}

//odwroc elementy na liscie
void reverse(list_ptr_t &list_ptr)
{
    node_t *p, *d;
    if (list_ptr)
    {
        d = list_ptr -> next_ptr;
        while (d -> next_ptr)
        {
            p = d -> next_ptr;
            d -> next_ptr = p -> next_ptr;
            p -> next_ptr = list_ptr -> next_ptr;
            list_ptr -> next_ptr = p;
        }
    }
}


int main()
{
    list_ptr_t list_ptr = NULL;
    item_t x;
    node_t *d;  // do wskazywania elementow
    int wybor;
    do {
        cout << "[0] Koniec\n";
        cout << "[1] Utworz liste\n";
        cout << "[2] Wstaw x\n";
        cout << "[3] Wypisz liste\n";
        cout << "[4] Sprawdz czy x jest na liscie\n";
        cout << "[5] Usun element za wskazanym\n";
        cout << "[6] Usun wskazany element z listy\n";
        cout << "[7] Odworc elementy na liscie\n";
        cout << "[8] Skasuj cala liste\n";
        cout << "\n";
        cin >> wybor;
        switch (wybor) {
            case 1:
                if (list_ptr != NULL) {
                    cout << "Lista juz istnieje. Nalezy ja najpierw skasowac.\n";
                    break;
                }
                create(list_ptr);
                break;
            case 2:
                cout << "Podaj x: ";
                cin >> x;
                insert(list_ptr, x);
                cout << "Wstawiono: " << x << "\n";
                break;
            case 3:
                //cout << "Oto lista:\n";
                print(list_ptr);
                break;
            case 4:
                cout << "Podaj x: ";
                cin >> x;
                if (found_iter(list_ptr, x))
                    cout << "Element " << x << " zostal znaleziony\n";
                else
                    cout << "Elementu " << x << " nie ma na liscie.\n";
                break;
                
            case 5:
                
                delete_next(list_ptr->next_ptr->next_ptr); //usuniemy element 2
                break;
            case 6:
                d=list_ptr; //do przechodzenia po liscie
                
                if (list_ptr == NULL || list_ptr -> next_ptr == NULL)
                {
                    cout << "Lista nie istnieje lub nie ma elementow.\n";
                    break;
                }
                
                cout << "Podaj x: ";
                cin >> x;
                while(d->item!=x && d->next_ptr!=NULL) d=d->next_ptr;
                if (d->item!=x)
                {
                    cout<<"Element o podanej wartosci nie wystepuje w liscie!";
                    break;
                }
                
                delete_x(list_ptr, d);
                break;
            case 7:
                if (list_ptr == NULL || list_ptr -> next_ptr == NULL)
                {
                    cout << "Lista nie istnieje lub nie ma elementow.\n";
                    break;
                }
                reverse(list_ptr);
                break;
            case 8:
                if (list_ptr == NULL) {
                    cout << "Listy nie ma. Nie ma co kasowac.\n";
                    break;
                }
                delete_list(list_ptr);
                cout << "Lista skasowana.\n";
                break;
            case 9:;
                break;
        }
        cout << "\n\n";
        
    } while (wybor);
    
    // system("PAUSE");
    
    return 0;
}

