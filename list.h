#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <string>

using namespace std;

// -- VERSI 1 --

// 1. DEFINISI INFOTYPE (DATA LAGU)
struct infotype{
    int id;
    string judul;
    string artis;
    string genre;
    int tahun;
};

// 2. DEFINISI POINTER & ELEMENT
struct ElmList;
struct ElmEdge;
struct ElmPlaylist;
struct ElmStack;

typedef ElmList* address;           // Pointer ke Elemen lagu (DLL)
typedef ElmEdge* addressEdge;       // Pointer ke Elemen relasi (graph)
typedef ElmPlaylist* addressP;      // Pointer playlist
typedef ElmStack* addressStack;     // Pointer stack

// Node untuk graph (daftar tetangga/kemiripan)
struct ElmEdge{
    address nodeTuju;
    addressEdge next;
};

// Node main (utama) untuk elemen list lagu
// Menggunakan Doubly Linked List (DLL)
struct ElmList{
    infotype info;       // Data lagu
    address next;        // Pointer next
    address prev;        // Pointer prev
    addressEdge firstedge; // Head of edge list (graph)
};

// Wrapper (definisi List)
struct List{
    address first;
    address last;
};

// 3. STRUKTUR DATA PLAYLIST (SINGLY LIST)
struct ElmPlaylist{
    address songRef;
    addressP next;
};

struct ListPlaylist{
    addressP first;
};

// 4. STRUKTUR DATA HISTORY (STACK)
struct ElmStack{
    address songRef;
    addressStack next;
};

struct Stack{
    addressStack top;
};

// 5. FUNGSI
// Primitive Library (DLL)
void createList(List &L);
address alokasi(infotype X);
void insertLast(List &L, address P);
void printInfo(List L);

// Fitur Search & Delete
address findSong(List L, string judul);
void searchSongs(List L, string judul);
void deleteSong(List &L, string judul);

// Helper untuk Graph Cleanup
void deleteAllEdges(address P);
void removeEdgesToSong(List &L, address target);

// Primitive Graph
void addEdge(address PAsal, address PTuju);
void connectGraph(List L, address PBaru);

// Primitive Playlist (Singly List)
void createPlaylist(ListPlaylist &LP);
void insertPlaylist(ListPlaylist &LP, address songRef);
void printPlaylist(ListPlaylist LP);

// Primitive Stack (History)
void createStack(Stack &S);
void push(Stack &S, address songRef);
address pop(Stack &S);
void printHistory(Stack S);

// Player
void playSong(address P, Stack &S);

#endif
