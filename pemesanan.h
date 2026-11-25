#ifndef PEMESANAN_H
#define PEMESANAN_H

#include <iostream>
#include <string>

using namespace std;

// ============================================================================
// DEFINISI TIPE DATA & STRUKTUR ADT (MLL-02 & BST)
// ============================================================================

// Info Parent: Order
struct infotypeOrder {
    int nomorOrder;        // Key unik transaksi (juga menjadi key BST)
    string idPelanggan;
    string waktuPesan;     // Format "HH:MM" (contoh: "12:30")
    string statusPesanan;  // "Diproses", "Selesai", "Dibayar", "Dibatalkan"
};

// Info Child: Menu
struct infotypeMenu {
    string idMenu;         // Key unik menu (contoh: "MN01")
    string namaMenu;
    string kategori;       // "Makanan", "Minuman", "Snack", "Dessert"
    int hargaSatuan;
};

// Info Relasi: Item Pesanan
struct infotypeRelasi {
    int nomorOrder;
    int jumlahPorsi;
    int hargaSaatPesan;
    string catatan;        // Catatan pesanan (contoh: "Kurangi gula", "Normal")
};

// Forward declaration pointer elemen
typedef struct elmOrder *adrOrder;
typedef struct elmMenu *adrMenu;
typedef struct elmRelasi *adrRelasi;
typedef struct NodeBST *adrBST;

// Elemen & List Parent (Doubly Linked List standar: first & last)
struct elmOrder {
    infotypeOrder info;
    adrOrder next;
    adrOrder prev;
};

struct ListOrder {
    adrOrder first;
    adrOrder last;
};

// Elemen & List Child (Doubly Linked List standar: first & last)
struct elmMenu {
    infotypeMenu info;
    adrMenu next;
    adrMenu prev;
};

struct ListMenu {
    adrMenu first;
    adrMenu last;
};

// Elemen & List Relasi MLL-02 (Singly Linked List standar: first saja)
struct elmRelasi {
    infotypeRelasi info;
    adrOrder parent;
    adrMenu child;
    adrRelasi next;
};

struct ListRelasi {
    adrRelasi first;
};

// Node Binary Search Tree (Key: info.nomorOrder)
struct NodeBST {
    infotypeOrder info;
    adrBST left;
    adrBST right;
};

// ============================================================================
// 1. INISIALISASI, PENGECEKAN KOSONG & ALOKASI MLL-02
// ============================================================================

// I.S. ListOrder LO sembarang.
// F.S. Terbentuk ListOrder kosong (LO.first == NULL dan LO.last == NULL).
void createListOrder(ListOrder &LO);

// I.S. ListMenu LM sembarang.
// F.S. Terbentuk ListMenu kosong (LM.first == NULL dan LM.last == NULL).
void createListMenu(ListMenu &LM);

// I.S. ListRelasi LR sembarang.
// F.S. Terbentuk ListRelasi kosong (LR.first == NULL).
void createListRelasi(ListRelasi &LR);

// I.S. ListOrder LO terdefinisi.
// F.S. Mengembalikan true jika LO kosong, false jika tidak.
bool isEmptyOrder(ListOrder LO);

// I.S. ListMenu LM terdefinisi.
// F.S. Mengembalikan true jika LM kosong, false jika tidak.
bool isEmptyMenu(ListMenu LM);

// I.S. ListRelasi LR terdefinisi.
// F.S. Mengembalikan true jika LR kosong, false jika tidak.
bool isEmptyRelasi(ListRelasi LR);

// I.S. data bertipe infotypeOrder terdefinisi.
// F.S. Mengembalikan alamat elemen Order baru dengan info = data, next = NULL, prev = NULL.
adrOrder allocateOrder(infotypeOrder data);

// I.S. data bertipe infotypeMenu terdefinisi.
// F.S. Mengembalikan alamat elemen Menu baru dengan info = data, next = NULL, prev = NULL.
adrMenu allocateMenu(infotypeMenu data);

// I.S. Pointer parent P, pointer child C, dan data relasi terdefinisi.
// F.S. Mengembalikan alamat elemen Relasi baru yang menghubungkan P dan C dengan next = NULL.
adrRelasi allocateRelasi(adrOrder P, adrMenu C, infotypeRelasi data);

// ============================================================================
// 2. FUNGSIONALITAS UMUM MLL-02 (INSERT, SEARCH, DELETE, SHOW, COUNT)
// ============================================================================

// --- Insert (Parent: Insert Last, Child: Insert First, Relasi: Insert First) ---

// I.S. ListOrder LO mungkin kosong, P adalah alamat elemen Order yang valid.
// F.S. P disisipkan sebagai elemen terakhir pada ListOrder LO.
void insertLastOrder(ListOrder &LO, adrOrder P);

// I.S. ListMenu LM mungkin kosong, C adalah alamat elemen Menu yang valid.
// F.S. C disisipkan sebagai elemen pertama pada ListMenu LM.
void insertFirstMenu(ListMenu &LM, adrMenu C);

// I.S. ListRelasi LR mungkin kosong, R adalah alamat elemen Relasi yang valid.
// F.S. R disisipkan sebagai elemen pertama pada ListRelasi LR.
void insertFirstRelasi(ListRelasi &LR, adrRelasi R);

// --- Search & Cek Relasi ---

// I.S. ListOrder LO dan nomorOrder terdefinisi.
// F.S. Mengembalikan alamat elemen Order yang memiliki nomorOrder sesuai, atau NULL jika tidak ditemukan.
adrOrder findOrder(ListOrder LO, int nomorOrder);

// I.S. ListMenu LM dan idMenu terdefinisi.
// F.S. Mengembalikan alamat elemen Menu yang memiliki idMenu sesuai, atau NULL jika tidak ditemukan.
adrMenu findMenu(ListMenu LM, string idMenu);

// I.S. ListRelasi LR, nomorOrder, dan idMenu terdefinisi.
// F.S. Mengembalikan alamat elemen Relasi yang menghubungkan nomorOrder dan idMenu, atau NULL jika tidak ada.
adrRelasi findRelasi(ListRelasi LR, int nomorOrder, string idMenu);

// I.S. ListRelasi LR, nomorOrder, dan idMenu terdefinisi.
// F.S. Mengembalikan true jika Order dan Menu saling berelasi, false jika tidak.
bool isRelated(ListRelasi LR, int nomorOrder, string idMenu);

// --- Delete Primitif & Cascade Delete ---

// I.S. ListOrder LO tidak kosong.
// F.S. Elemen pertama LO dilepas dan alamatnya disimpan pada P.
void deleteFirstOrder(ListOrder &LO, adrOrder &P);

// I.S. ListOrder LO tidak kosong.
// F.S. Elemen terakhir LO dilepas dan alamatnya disimpan pada P.
void deleteLastOrder(ListOrder &LO, adrOrder &P);

// I.S. ListOrder LO tidak kosong dan prec adalah alamat elemen valid yang memiliki suksesor.
// F.S. Elemen setelah prec dilepas dari LO dan alamatnya disimpan pada P.
void deleteAfterOrder(ListOrder &LO, adrOrder prec, adrOrder &P);

// I.S. ListMenu LM tidak kosong.
// F.S. Elemen pertama LM dilepas dan alamatnya disimpan pada C.
void deleteFirstMenu(ListMenu &LM, adrMenu &C);

// I.S. ListMenu LM tidak kosong.
// F.S. Elemen terakhir LM dilepas dan alamatnya disimpan pada C.
void deleteLastMenu(ListMenu &LM, adrMenu &C);

// I.S. ListMenu LM tidak kosong dan prec adalah alamat elemen valid yang memiliki suksesor.
// F.S. Elemen setelah prec dilepas dari LM dan alamatnya disimpan pada C.
void deleteAfterMenu(ListMenu &LM, adrMenu prec, adrMenu &C);

// I.S. ListRelasi LR tidak kosong.
// F.S. Elemen pertama LR dilepas dan alamatnya disimpan pada R.
void deleteFirstRelasi(ListRelasi &LR, adrRelasi &R);

// I.S. ListRelasi LR tidak kosong dan prec adalah alamat elemen valid yang memiliki suksesor.
// F.S. Elemen setelah prec dilepas dari LR dan alamatnya disimpan pada R.
void deleteAfterRelasi(ListRelasi &LR, adrRelasi prec, adrRelasi &R);

// I.S. ListRelasi LR dan nomorOrder terdefinisi.
// F.S. Seluruh elemen relasi yang merujuk ke nomorOrder dihapus dan didealokasi dari LR.
void deleteAllRelasiByOrder(ListRelasi &LR, int nomorOrder);

// I.S. ListRelasi LR dan idMenu terdefinisi.
// F.S. Seluruh elemen relasi yang merujuk ke idMenu dihapus dan didealokasi dari LR.
void deleteAllRelasiByMenu(ListRelasi &LR, string idMenu);

// I.S. ListOrder LO, ListRelasi LR, dan nomorOrder terdefinisi.
// F.S. Jika ditemukan, seluruh relasi milik nomorOrder dan elemen Order tersebut dihapus serta didealokasi.
void deleteOrderByNomor(ListOrder &LO, ListRelasi &LR, int nomorOrder);

// I.S. ListMenu LM, ListRelasi LR, dan idMenu terdefinisi.
// F.S. Jika ditemukan, seluruh relasi milik idMenu dan elemen Menu tersebut dihapus serta didealokasi.
void deleteMenuByID(ListMenu &LM, ListRelasi &LR, string idMenu);

// I.S. ListRelasi LR, nomorOrder, dan idMenu terdefinisi.
// F.S. Jika ditemukan, satu elemen relasi antara nomorOrder dan idMenu dihapus dan didealokasi.
void deleteRelasiTertentu(ListRelasi &LR, int nomorOrder, string idMenu);

// --- Update Status ---

// I.S. ListOrder LO, BST root, nomorOrder, dan statusBaru terdefinisi.
// F.S. Jika nomorOrder ditemukan, statusPesanan diperbarui pada ListOrder LO dan disinkronkan pada BST root.
void updateStatusOrder(ListOrder &LO, adrBST &root, int nomorOrder, string statusBaru);

// --- Show & Count ---

// I.S. ListOrder LO terdefinisi.
// F.S. Menampilkan seluruh daftar Order (parent) dalam bentuk tabel ke layar.
void showAllOrder(ListOrder LO);

// I.S. ListMenu LM terdefinisi.
// F.S. Menampilkan seluruh daftar Menu (child) dalam bentuk tabel ke layar.
void showAllMenu(ListMenu LM);

// I.S. ListOrder LO dan ListRelasi LR terdefinisi.
// F.S. Menampilkan seluruh Order beserta daftar Menu yang dipesan pada masing-masing Order.
void showAllOrderWithMenu(ListOrder LO, ListRelasi LR);

// I.S. ListMenu LM dan ListRelasi LR terdefinisi.
// F.S. Menampilkan seluruh Menu beserta daftar Order yang memesan masing-masing Menu.
void showAllMenuWithOrder(ListMenu LM, ListRelasi LR);

// I.S. ListRelasi LR dan nomorOrder terdefinisi.
// F.S. Mengembalikan jumlah jenis Menu (child) yang berelasi dengan Order tertentu.
int countMenuByOrder(ListRelasi LR, int nomorOrder);

// I.S. ListRelasi LR dan idMenu terdefinisi.
// F.S. Mengembalikan jumlah Order (parent) yang berelasi dengan Menu tertentu.
int countOrderByMenu(ListRelasi LR, string idMenu);

// I.S. ListRelasi LR dan nomorOrder terdefinisi.
// F.S. Mengembalikan total biaya transaksi (jumlahPorsi * hargaSaatPesan) untuk nomorOrder tersebut.
int calculateTotalBayarOrder(ListRelasi LR, int nomorOrder);

// ============================================================================
// 3. FUNGSIONALITAS UMUM BST (KEY: nomorOrder)
// ============================================================================

// I.S. Pointer root sembarang.
// F.S. Terbentuk BST kosong (root == NULL).
void createBST(adrBST &root);

// I.S. data bertipe infotypeOrder terdefinisi.
// F.S. Mengembalikan alamat NodeBST baru dengan info = data, left = NULL, right = NULL.
adrBST allocateBST(infotypeOrder data);

// I.S. BST root mungkin kosong, data transaksi terdefinisi.
// F.S. Node baru dengan key data.nomorOrder disisipkan pada posisi BST yang sesuai (duplikat diabaikan).
void insertBST(adrBST &root, infotypeOrder data);

// I.S. BST root dan key nomorOrder terdefinisi.
// F.S. Mengembalikan alamat NodeBST dengan key nomorOrder, atau NULL jika tidak ditemukan.
adrBST searchBST(adrBST root, int nomorOrder);

// I.S. BST root terdefinisi.
// F.S. Mengembalikan alamat NodeBST dengan key nomorOrder terkecil, atau NULL jika pohon kosong.
adrBST findMinBST(adrBST root);

// I.S. BST root terdefinisi.
// F.S. Mengembalikan alamat NodeBST dengan key nomorOrder terbesar, atau NULL jika pohon kosong.
adrBST findMaxBST(adrBST root);

// I.S. BST root dan key nomorOrder terdefinisi.
// F.S. Node dengan key nomorOrder dihapus dari BST (menangani kasus 0, 1, dan 2 anak) dan didealokasi.
void deleteBST(adrBST &root, int nomorOrder);

// I.S. BST root terdefinisi.
// F.S. Seluruh node pada BST ditampilkan dengan urutan In-Order (Left - Root - Right).
void inOrderBST(adrBST root);

// I.S. BST root terdefinisi.
// F.S. Seluruh node pada BST ditampilkan dengan urutan Pre-Order (Root - Left - Right).
void preOrderBST(adrBST root);

// I.S. BST root terdefinisi.
// F.S. Seluruh node pada BST ditampilkan dengan urutan Post-Order (Left - Right - Root).
void postOrderBST(adrBST root);

// I.S. BST root terdefinisi.
// F.S. Mengembalikan tinggi pohon BST (0 jika kosong, 1 jika hanya terdiri dari 1 node root).
int heightBST(adrBST root);

// I.S. BST root terdefinisi.
// F.S. Mengembalikan jumlah total node yang ada di dalam BST.
int countNodesBST(adrBST root);

// I.S. BST root terdefinisi.
// F.S. Menampilkan informasi nilai minimum, maksimum, tinggi pohon, dan jumlah node BST ke layar.
void showStatistikBST(adrBST root);

// ============================================================================
// 4. FUNGSIONALITAS KHUSUS TOPIK 13
// ============================================================================

// Fungsionalitas Khusus 1:
// I.S. ListMenu LM dan ListRelasi LR terdefinisi.
// F.S. Menampilkan total jumlah porsi per idMenu serta menampilkan menu paling diminati pelanggan.
void hitungTotalPorsiPerMenu(ListMenu LM, ListRelasi LR);

// Fungsionalitas Khusus 2:
// I.S. ListOrder LO, ListMenu LM, dan ListRelasi LR terdefinisi.
// F.S. Menampilkan pasangan menu yang sering dipesan bersamaan dalam satu nomorOrder.
void analisisMenuBersamaan(ListOrder LO, ListMenu LM, ListRelasi LR);

// Fungsionalitas Khusus 3:
// I.S. ListMenu LM dan ListRelasi LR terdefinisi.
// F.S. Menampilkan total pendapatan per menu (jumlahPorsi * hargaSaatPesan) dan total keseluruhan.
void hitungPendapatanPerMenu(ListMenu LM, ListRelasi LR);

// Fungsionalitas Khusus 4:
// I.S. ListMenu LM, ListRelasi LR, dan idMenu terdefinisi.
// F.S. Menggabungkan waktuPesan dengan idMenu untuk menampilkan distribusi waktu pemesanan
//      (Pagi/Siang/Sore/Malam) serta waktu favorit pelanggan memesan menu tersebut.
void analisisWaktuFavoritMenu(ListMenu LM, ListRelasi LR, string idMenu);

// ============================================================================
// 5. UTILITAS & DEALOKASI MEMORI
// ============================================================================

// I.S. waktuPesan dalam format "HH:MM" terdefinisi.
// F.S. Mengembalikan kategori slot waktu: "Pagi" (05-10), "Siang" (11-14), "Sore" (15-17), atau "Malam" (18-04).
string getSlotWaktu(string waktuPesan);

// I.S. teks bertipe string terdefinisi.
// F.S. Mengembalikan salinan teks dengan seluruh huruf kapital diubah menjadi huruf kecil.
string toLowerString(string teks);

// I.S. BST root terdefinisi.
// F.S. Seluruh node BST didealokasi secara post-order sehingga root menjadi NULL.
void deleteAllBST(adrBST &root);

// I.S. ListOrder LO, ListMenu LM, ListRelasi LR, dan BST root terdefinisi.
// F.S. Seluruh elemen MLL-02 dan seluruh node BST didealokasi dengan aman.
void dealokasiSemua(ListOrder &LO, ListMenu &LM, ListRelasi &LR, adrBST &root);

#endif // PEMESANAN_H
