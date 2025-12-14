#include "list.h"

// -- VERSI 1 --

//1. Create List
void createList(List &L) {
    first(L) = Nil;
    last(L) = Nil;
}

//2. Alokasi
address alokasi(infotype X) {
    address P = new ElmList;
    info(P) = X;
    next(P) = Nil;
    prev(P) = Nil;
    P->firstedge = Nil; // State awal graph edge kosong
    return P;
}

//3. Insert Last (DLL)
void insertLast(List &L, address P) {
    if (first(L) == Nil) {
        // Saat list kosong
        first(L) = P;
        last(L) = P;
    } else {
        // Saat list tidak kosong
        next(last(L)) = P; // Connect next element terakhir ke P
        prev(P) = last(L); // Connect previous P ke elemen terakhir
        last(L) = P; // Update last jadi P
    }

    // Untuk menjalankan logika graph setiap insert
    connectGraph(L, P);
}

//4. Print Info
void printInfo(List L) {
    if (first(L) == Nil) {
        cout << "[List Kosong]" << endl;
        return;
    }

    address P = first(L);
    cout << "\n=== LIBRARY LAGU (DOUBLY LINKED LIST) ===" << endl;
    while (P != Nil) {
        // Cetak info lagu
        cout << "ID: " << info(P).id << " | " 
             << info(P).judul << " - " << info(P).artis 
             << " (" << info(P).genre << ")";

        // Cetak info graph untuk rekomendasi
        cout << "\n   [Rekomendasi]: ";
        addressEdge E = P->firstedge;
        if (E == Nil) cout << "-";
        
        while (E != Nil) {
            // Akses info lagu melalui pointer edge
            cout << "[" << info(E->nodeTuju).judul << "] ";
            E = E->next;
        }
        
        cout << "\n----------------------------------------" << endl;
        P = next(P);
    }
}

//5. Fitur Search
address findSong(List L, string judul) {
    address P = first(L);
    while (P != Nil) {
        if (info(P).judul == judul) {
            return P;
        }
        P = next(P);
    }
    return Nil;
}

//6. Fitur Delete (DLL)
void deleteSong(List &L, string judul) {
    address P = findSong(L, judul);
    
    if (P == Nil) {
        cout << "Lagu tidak ditemukan!" << endl;
        return;
    }

    // Hapus dari DLL
    if (P == first(L)) {
        // Hapus depan
        first(L) = next(P);
        if (first(L) != Nil) {
            prev(first(L)) = Nil;
        } else {
            last(L) = Nil;
        }
    } else if (P == last(L)) {
        // Hapus belakang
        last(L) = prev(P);
        next(last(L)) = Nil;
    } else {
        // Hapus tengah
        next(prev(P)) = next(P);
        prev(next(P)) = prev(P);
    }

    cout << "Lagu '" << info(P).judul << "' berhasil dihapus." << endl;
    delete P; // Free memory
    
    // note: biasanya recommended buat hapus pointer di Graph/Playlist biar ga dangling 
    // tapi buat tahap ini DLL delete dah cukup.
}

// -- Graph -- //

//7. Tambah Edge
void addEdge(address PAsal, address PTuju) {
    // Alokasi edge baru
    addressEdge newEdge = new ElmEdge;
    newEdge->nodeTuju = PTuju;
    newEdge->next = Nil;

    // Insert first ke list edge (O(1))
    newEdge->next = PAsal->firstedge;
    PAsal->firstedge = newEdge;
}

//6. Koneksi Graph
void connectGraph(List L, address PBaru) {
    address P = first(L);
    while (P != Nil) {
        // Dont check diri sendiri
        if (P != PBaru) {
            // Check kesamaan artis/genre
            bool samaArtis = (info(P).artis == info(PBaru).artis);
            bool samaGenre = (info(P).genre == info(PBaru).genre);

            // Buat relasi undirected (2 arah)
            if (samaArtis || samaGenre) {
                addEdge(PBaru, P);
                addEdge(P, PBaru);
            }
        }
        P = next(P);
    }
}

// IMPLEMENTASI STACK (HISTORY)
void createStack(Stack &S) {
    top(S) = Nil;
}

void push(Stack &S, address songRef) {
    addressStack P = new ElmStack;
    P->songRef = songRef;
    P->next = top(S);
    top(S) = P;
}

address pop(Stack &S) {
    if (top(S) == Nil) return Nil;
    
    addressStack P = top(S);
    address songRef = P->songRef;
    
    top(S) = P->next;
    delete P;
    return songRef;
}

void printHistory(Stack S) {
    addressStack P = top(S);
    cout << "\n=== HISTORY (STACK) ===" << endl;
    if (P == Nil) cout << "(Kosong)" << endl;
    while (P != Nil) {
        if (P->songRef != Nil) {
            cout << "[Played] " << info(P->songRef).judul << endl;
        }
        P = P->next;
    }
}

void playSong(address P, Stack &S) {
    if (P != Nil) {
        cout << "\n>>> NOW PLAYING: " << info(P).judul << " <<<" << endl;
        push(S, P); // Masuk Stack History
    }
}