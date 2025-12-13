#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <string>

#define Nil NULL
#define info(P) (P)->info
#define next(P) (P)->next
#define prev(P) (P)->prev
#define first(L) ((L).first)
#define last(L) ((L).last)

using namespace std;


// 1. DEFINISI INFOTYPE (DATA LAGU)
struct infotype{
    int id;
    string judul;
    string artis;
    string genre;
    int tahun;
};


// 2. DEFINISI POINTER & ELEMENT
typedef struct ElmList *address; // Pointer ke Elemen lagu
typedef struct ElmEdge *addressEdge; // Pointer ke Elemen relasi (graph)

// Node untuk graph (daftar tetangga/kemiripan)
struct ElmEdge{
    address nodeTuju;
    addressEdge next;
};


// Node main (utama) untuk elemen list lagu
// Menggunakan Doubly Linked List (DLL)
struct ElmList{
    infotype info; // Data lagu
    address next; // Pointer next
    address prev; // Pointer prev

    addressEdge firstedge; // Nanti dipake untuk graph (head of edge list)
};

// Wrapper (definisi List)
struct List{
    address first;
    address last;
};

// 3. PRIMITIF LIST
void createList(List &L);
address alokasi(infotype X);
void insertLast(List &L, address P);
void printInfo(List L);

void addEdge(address PAsal, address PTuju);
void connectGraph(List L, address PBaru);

#endif