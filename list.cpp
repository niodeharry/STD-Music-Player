#include "list.h"

// -- VERSI 1 --

//1. Create List
void createList(List &L) {
    L.first = nullptr;
    L.last = nullptr;
}

//2. Alokasi
address alokasi(infotype X) {
    address P = new ElmList;
    P->info = X;
    P->next = nullptr;
    P->prev = nullptr;
    P->firstedge = nullptr; // State awal graph edge kosong
    return P;
}

//3. Insert Last (DLL)
void insertLast(List &L, address P) {
    if (L.first == nullptr) {
        // Saat list kosong
        L.first = P;
        L.last = P;
    } else {
        // Saat list tidak kosong
        L.last->next = P; // Connect next element terakhir ke P
        P->prev = L.last; // Connect previous P ke elemen terakhir
        L.last = P; // Update last jadi P
    }

    // Untuk menjalankan logika graph setiap insert
    connectGraph(L, P);
}

//4. Print Info
void printInfo(List L) {
    if (L.first == nullptr) {
        cout << "[List Kosong]" << endl;
        return;
    }

    address P = L.first;
    cout << "\n=== LIBRARY LAGU (DOUBLY LINKED LIST) ===" << endl;
    while (P != nullptr) {
        // Cetak info lagu
        cout << "ID: " << P->info.id << " | "
             << P->info.judul << " - " << P->info.artis
             << " (" << P->info.genre << ")";

        // Cetak info graph untuk rekomendasi
        cout << "\n   [Rekomendasi]: ";
        addressEdge E = P->firstedge;
        if (E == nullptr) cout << "-";
        
        while (E != nullptr) {
            // Akses info lagu melalui pointer edge
            cout << "[" << E->nodeTuju->info.judul << "] ";
            E = E->next;
        }
        
        cout << "\n----------------------------------------" << endl;
        P = P->next;
    }
}

//5. Fitur Search
address findSong(List L, string judul) {
    address P = L.first;
    while (P != nullptr) {
        if (P->info.judul == judul) {
            return P;
        }
        P = P->next;
    }
    return nullptr;
}

void deleteAllEdges(address P) {
    addressEdge E = P->firstedge;
    while (E != nullptr) {
        addressEdge temp = E;
        E = E->next;
        delete temp;
    }
    P->firstedge = nullptr;
}

void removeEdgesToSong(List &L, address target) {
    address P = L.first;
    while (P != nullptr) {
        addressEdge prev = nullptr;
        addressEdge E = P->firstedge;

        while (E != nullptr) {
            if (E->nodeTuju == target) {
                if (prev == nullptr) {
                    P->firstedge = E->next;
                } else {
                    prev->next = E->next;
                }
                addressEdge temp = E;
                E = E->next;
                delete temp;
            } else {
                prev = E;
                E = E->next;
            }
        }
        P = P->next;
    }
}


//6. Fitur Delete (DLL)
void deleteSong(List &L, string judul) {
    address P = findSong(L, judul);
    
    if (P == nullptr) {
        cout << "Lagu tidak ditemukan!" << endl;
        return;
    }

    removeEdgesToSong(L, P);
    deleteAllEdges(P);

    // Hapus dari DLL
    if (P == L.first) {
        // Hapus depan
        L.first = P->next;
        if (L.first != nullptr) {
            L.first->prev = nullptr;
        } else {
            L.last = nullptr;
        }
    } else if (P == L.last) {
        // Hapus belakang
        L.last = P->prev;
        L.last->next = nullptr;
    } else {
        // Hapus tengah
        P->prev->next = P->next;
        P->next->prev = P->prev;
    }

    cout << "Lagu '" << P->info.judul << "' berhasil dihapus." << endl;
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
    newEdge->next = nullptr;

    // Insert first ke list edge (O(1))
    newEdge->next = PAsal->firstedge;
    PAsal->firstedge = newEdge;
}

//6. Koneksi Graph
void connectGraph(List L, address PBaru) {
    address P = L.first;
    while (P != nullptr) {
        // Dont check diri sendiri
        if (P != PBaru) {
            // Check kesamaan artis/genre
            bool samaArtis = (P->info.artis == PBaru->info.artis);
            bool samaGenre = (P->info.genre == PBaru->info.genre);

            // Buat relasi undirected (2 arah)
            if (samaArtis || samaGenre) {
                addEdge(PBaru, P);
                addEdge(P, PBaru);
            }
        }
        P = P->next;
    }
}

// IMPLEMENTASI STACK (HISTORY)
void createStack(Stack &S) {
    S.top = nullptr;
}

void push(Stack &S, address songRef) {
    addressStack P = new ElmStack;
    P->songRef = songRef;
    P->next = S.top;
    S.top = P;
}

address pop(Stack &S) {
    if (S.top == nullptr) return nullptr;
    
    addressStack P = S.top;
    address songRef = P->songRef;
    
    S.top = P->next;
    delete P;
    return songRef;
}

void printHistory(Stack S) {
    addressStack P = S.top;
    cout << "\n=== HISTORY (STACK) ===" << endl;
    if (P == nullptr) cout << "(Kosong)" << endl;
    while (P != nullptr) {
        if (P->songRef != nullptr) {
            cout << "[Played] " << P->songRef->info.judul << endl;
        }
        P = P->next;
    }
}

void playSong(address P, Stack &S) {
    if (P != nullptr) {
        cout << "\n>>> NOW PLAYING: " << P->info.judul << " <<<" << endl;
        push(S, P); // Masuk Stack History
    }
}

// ================= PLAYLIST (SINGLY LINKED LIST) =================

// Create Playlist
void createPlaylist(ListPlaylist &LP) {
    LP.first = nullptr;
}

// Insert ke Playlist
void insertPlaylist(ListPlaylist &LP, address songRef) {
    if (songRef == nullptr) return;

    addressP P = new ElmPlaylist;
    P->songRef = songRef;
    P->next = nullptr;

    if (LP.first == nullptr) {
        LP.first = P;
    } else {
        addressP Q = LP.first;
        while (Q->next != nullptr) {
            Q = Q->next;
        }
        Q->next = P;
    }

    cout << "Lagu masuk ke playlist: " << songRef->info.judul << endl;
}

// Print Playlist
void printPlaylist(ListPlaylist LP) {
    cout << "\n=== PLAYLIST ===" << endl;
    if (LP.first == nullptr) {
        cout << "(Kosong)" << endl;
        return;
    }

    addressP P = LP.first;
    int i = 1;
    while (P != nullptr) {
        if (P->songRef != nullptr) {
            cout << i++ << ". "
                 << P->songRef->info.judul
                 << " - " << P->songRef->info.artis << endl;
        }
        P = P->next;
    }
}
