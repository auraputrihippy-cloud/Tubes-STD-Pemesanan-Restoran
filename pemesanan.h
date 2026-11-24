#ifndef PEMESANAN_H_INCLUDED
#define PEMESANAN_H_INCLUDED

#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

// --- STRUKTUR DATA (MLL 1-to-N berbasis Doubly Linked List) ---

typedef struct elemenPesanan *adrPesanan;
typedef struct elemenItem *adrItem;

struct Pesanan {
    string kodePesanan;
    string namaPelanggan;
    int nomorMeja;
    string status;
};

struct ItemMenu {
    string namaMenu;
    string kategori;
    int hargaSatuan;
    int jumlahPorsi;
};

struct elemenPesanan {
    Pesanan info;
    adrPesanan next;
    adrPesanan prev;
    adrItem firstItem;
};

struct elemenItem {
    ItemMenu info;
    adrItem next;
    adrItem prev;
};

struct ListPesanan {
    adrPesanan first;
    adrPesanan last;
};

// --- FUNGSI & PROSEDUR ---

// Basic
void createListPesanan(ListPesanan &L);
bool isEmptyPesanan(ListPesanan L);
bool isEmptyItem(adrPesanan p);
adrPesanan createElementPesanan(string kode, string namaPelanggan, int nomorMeja, string status);
adrItem createElementItem(string namaMenu, string kategori, int hargaSatuan, int jumlahPorsi);

// Add
void addPesanan(ListPesanan &L, adrPesanan p);
void addItemMenu(adrPesanan p, adrItem pItem);

// Search
adrPesanan searchPesanan(ListPesanan L, string kodePesanan);
adrItem searchItemMenu(adrPesanan p, string namaMenu);
bool searchMenuDiSemuaPesanan(ListPesanan L, string namaMenu);

// Update
void updatePesanan(adrPesanan p, string namaBaru, int mejaBaru, string statusBaru);
void updateItemMenu(adrItem pItem, string namaBaru, string kategoriBaru, int hargaBaru, int jumlahBaru);

// Delete
void deletePesanan(ListPesanan &L, string kodePesanan);
void deleteItemMenu(adrPesanan p, string namaMenu);
void clearAllPesanan(ListPesanan &L);

// Helper Hitungan
int countPesanan(ListPesanan L);
int countTotalPorsi(adrPesanan p);
int countPorsiByCategory(adrPesanan p, string kategori);
int calculateTotalBayar(adrPesanan p);

// Sorting
void selectionSortPesanan(adrPesanan* arrayPesanan, int n, int mode);

// Display & Utilitas
void displayTable(ListPesanan L, int mode);
void showPesananDetails(adrPesanan p);
void clearScreen();
void pauseScreen();

#endif // PEMESANAN_H_INCLUDED
