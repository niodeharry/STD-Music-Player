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

struct infotype{
    int id;
    string judul;
    string artis;
    string genre;
    int tahun;
};

typedef struct ElmList *address;
typedef struct ElmEdge *addressEdge;

struct ElmEdge{
    address nodeTuju;
    addressEdge next;
};

struct ElmList{
    infotype info;
    address next;
    address prev;

    addressEdge firstedge;
};

struct List{
    address first;
    address last;
};

void createList(List &L);
address alokasi(infotype X);
void insertLast(List &L, address P);
void printInfo(List L);

void addEdge(address PAsal, address PTuju);
void connectGraph(List L, address PBaru);

#endif