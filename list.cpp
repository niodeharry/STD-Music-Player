#include "list.h"

void createList(List &L) {
    first(L) = Nil;
    last(L) = Nil;
}

address alokasi(infotype X) {
    address P = new ElmList;
    info(P) = X;
    next(P) = Nil;
    prev(P) = Nil;
    P->firstedge = Nil;
    return P;
}

void insertLast(List &L, address P) {
    if (first(L) == Nil) {
        first(L) = P;
        last(L) = P;
    } else {
        next(last(L)) = P;
        prev(P) = last(L);
        last(L) = P;
    }

    connectGraph(L, P);
}

void printInfo(List L) {
    if (first(L) == Nil) {
        cout << "[List Kosong]" << endl;
        return;
    }

    address P = first(L);
    cout << "\n=== LIBRARY LAGU (DOUBLY LINKED LIST) ===" << endl;
    while (P != Nil) {
        cout << "ID: " << info(P).id << " | " 
             << info(P).judul << " - " << info(P).artis 
             << " (" << info(P).genre << ")";

        cout << "\n   [Rekomendasi]: ";
        addressEdge E = P->firstedge;
        if (E == Nil) cout << "-";
        
        while (E != Nil) {
            cout << "[" << info(E->nodeTuju).judul << "] ";
            E = E->next;
        }
        
        cout << "\n----------------------------------------" << endl;
        P = next(P);
    }
}

void addEdge(address PAsal, address PTuju) {
    addressEdge newEdge = new ElmEdge;
    newEdge->nodeTuju = PTuju;
    newEdge->next = Nil;

    newEdge->next = PAsal->firstedge;
    PAsal->firstedge = newEdge;
}

void connectGraph(List L, address PBaru) {
    address P = first(L);
    while (P != Nil) {
        if (P != PBaru) {
            bool samaArtis = (info(P).artis == info(PBaru).artis);
            bool samaGenre = (info(P).genre == info(PBaru).genre);

            if (samaArtis || samaGenre) {
                addEdge(PBaru, P);
                addEdge(P, PBaru);
            }
        }
        P = next(P);
    }
}