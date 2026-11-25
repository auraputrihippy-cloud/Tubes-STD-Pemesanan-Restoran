#include "pemesanan.h"
#include <iomanip>

// ============================================================================
// 1. INISIALISASI, PENGECEKAN KOSONG & ALOKASI MLL-02
// ============================================================================

// I.S. ListOrder LO sembarang.
// F.S. Terbentuk ListOrder kosong (LO.first == NULL dan LO.last == NULL).
void createListOrder(ListOrder &LO) {
    LO.first = NULL;
    LO.last = NULL;
}

// I.S. ListMenu LM sembarang.
// F.S. Terbentuk ListMenu kosong (LM.first == NULL dan LM.last == NULL).
void createListMenu(ListMenu &LM) {
    LM.first = NULL;
    LM.last = NULL;
}

// I.S. ListRelasi LR sembarang.
// F.S. Terbentuk ListRelasi kosong (LR.first == NULL).
void createListRelasi(ListRelasi &LR) {
    LR.first = NULL;
}

// I.S. ListOrder LO terdefinisi.
// F.S. Mengembalikan true jika LO kosong, false jika tidak.
bool isEmptyOrder(ListOrder LO) {
    return (LO.first == NULL);
}

// I.S. ListMenu LM terdefinisi.
// F.S. Mengembalikan true jika LM kosong, false jika tidak.
bool isEmptyMenu(ListMenu LM) {
    return (LM.first == NULL);
}

// I.S. ListRelasi LR terdefinisi.
// F.S. Mengembalikan true jika LR kosong, false jika tidak.
bool isEmptyRelasi(ListRelasi LR) {
    return (LR.first == NULL);
}

// I.S. data bertipe infotypeOrder terdefinisi.
// F.S. Mengembalikan alamat elemen Order baru dengan info = data, next = NULL, prev = NULL.
adrOrder allocateOrder(infotypeOrder data) {
    adrOrder P = new elmOrder;
    P->info = data;
    P->next = NULL;
    P->prev = NULL;
    return P;
}

// I.S. data bertipe infotypeMenu terdefinisi.
// F.S. Mengembalikan alamat elemen Menu baru dengan info = data, next = NULL, prev = NULL.
adrMenu allocateMenu(infotypeMenu data) {
    adrMenu C = new elmMenu;
    C->info = data;
    C->next = NULL;
    C->prev = NULL;
    return C;
}

// I.S. Pointer parent P, pointer child C, dan data relasi terdefinisi.
// F.S. Mengembalikan alamat elemen Relasi baru yang menghubungkan P dan C dengan next = NULL.
adrRelasi allocateRelasi(adrOrder P, adrMenu C, infotypeRelasi data) {
    adrRelasi R = new elmRelasi;
    R->info = data;
    R->parent = P;
    R->child = C;
    R->next = NULL;
    return R;
}

// ============================================================================
// 2. FUNGSIONALITAS UMUM MLL-02 (INSERT, SEARCH, DELETE, SHOW, COUNT)
// ============================================================================

// I.S. ListOrder LO mungkin kosong, P adalah alamat elemen Order yang valid.
// F.S. P disisipkan sebagai elemen terakhir pada ListOrder LO.
void insertLastOrder(ListOrder &LO, adrOrder P) {
    if (P != NULL) {
        if (isEmptyOrder(LO)) {
            LO.first = P;
            LO.last = P;
        } else {
            P->prev = LO.last;
            LO.last->next = P;
            LO.last = P;
        }
    }
}

// I.S. ListMenu LM mungkin kosong, C adalah alamat elemen Menu yang valid.
// F.S. C disisipkan sebagai elemen pertama pada ListMenu LM.
void insertFirstMenu(ListMenu &LM, adrMenu C) {
    if (C != NULL) {
        if (isEmptyMenu(LM)) {
            LM.first = C;
            LM.last = C;
        } else {
            C->next = LM.first;
            LM.first->prev = C;
            LM.first = C;
        }
    }
}

// I.S. ListRelasi LR mungkin kosong, R adalah alamat elemen Relasi yang valid.
// F.S. R disisipkan sebagai elemen pertama pada ListRelasi LR.
void insertFirstRelasi(ListRelasi &LR, adrRelasi R) {
    if (R != NULL) {
        if (isEmptyRelasi(LR)) {
            LR.first = R;
        } else {
            R->next = LR.first;
            LR.first = R;
        }
    }
}

// I.S. ListOrder LO dan nomorOrder terdefinisi.
// F.S. Mengembalikan alamat elemen Order yang memiliki nomorOrder sesuai, atau NULL jika tidak ditemukan.
adrOrder findOrder(ListOrder LO, int nomorOrder) {
    adrOrder P = LO.first;
    adrOrder hasil = NULL;
    while (P != NULL && hasil == NULL) {
        if (P->info.nomorOrder == nomorOrder) {
            hasil = P;
        } else {
            P = P->next;
        }
    }
    return hasil;
}

// I.S. ListMenu LM dan idMenu terdefinisi.
// F.S. Mengembalikan alamat elemen Menu yang memiliki idMenu sesuai, atau NULL jika tidak ditemukan.
adrMenu findMenu(ListMenu LM, string idMenu) {
    adrMenu C = LM.first;
    adrMenu hasil = NULL;
    string target = toLowerString(idMenu);
    while (C != NULL && hasil == NULL) {
        if (toLowerString(C->info.idMenu) == target) {
            hasil = C;
        } else {
            C = C->next;
        }
    }
    return hasil;
}

// I.S. ListRelasi LR, nomorOrder, dan idMenu terdefinisi.
// F.S. Mengembalikan alamat elemen Relasi yang menghubungkan nomorOrder dan idMenu, atau NULL jika tidak ada.
adrRelasi findRelasi(ListRelasi LR, int nomorOrder, string idMenu) {
    adrRelasi R = LR.first;
    adrRelasi hasil = NULL;
    string targetMenu = toLowerString(idMenu);
    while (R != NULL && hasil == NULL) {
        if (R->parent != NULL && R->child != NULL &&
            R->parent->info.nomorOrder == nomorOrder &&
            toLowerString(R->child->info.idMenu) == targetMenu) {
            hasil = R;
        } else {
            R = R->next;
        }
    }
    return hasil;
}

// I.S. ListRelasi LR, nomorOrder, dan idMenu terdefinisi.
// F.S. Mengembalikan true jika Order dan Menu saling berelasi, false jika tidak.
bool isRelated(ListRelasi LR, int nomorOrder, string idMenu) {
    return (findRelasi(LR, nomorOrder, idMenu) != NULL);
}

// --- Delete Primitif ListOrder (DLL) ---

// I.S. ListOrder LO tidak kosong.
// F.S. Elemen pertama LO dilepas dan alamatnya disimpan pada P.
void deleteFirstOrder(ListOrder &LO, adrOrder &P) {
    if (isEmptyOrder(LO)) {
        P = NULL;
    } else if (LO.first == LO.last) {
        P = LO.first;
        LO.first = NULL;
        LO.last = NULL;
    } else {
        P = LO.first;
        LO.first = P->next;
        LO.first->prev = NULL;
        P->next = NULL;
    }
}

// I.S. ListOrder LO tidak kosong.
// F.S. Elemen terakhir LO dilepas dan alamatnya disimpan pada P.
void deleteLastOrder(ListOrder &LO, adrOrder &P) {
    if (isEmptyOrder(LO)) {
        P = NULL;
    } else if (LO.first == LO.last) {
        P = LO.last;
        LO.first = NULL;
        LO.last = NULL;
    } else {
        P = LO.last;
        LO.last = P->prev;
        LO.last->next = NULL;
        P->prev = NULL;
    }
}

// I.S. ListOrder LO tidak kosong dan prec adalah alamat elemen valid yang memiliki suksesor.
// F.S. Elemen setelah prec dilepas dari LO dan alamatnya disimpan pada P.
void deleteAfterOrder(ListOrder &LO, adrOrder prec, adrOrder &P) {
    if (prec == NULL || prec->next == NULL) {
        P = NULL;
    } else if (prec->next == LO.last) {
        deleteLastOrder(LO, P);
    } else {
        P = prec->next;
        prec->next = P->next;
        P->next->prev = prec;
        P->next = NULL;
        P->prev = NULL;
    }
}

// --- Delete Primitif ListMenu (DLL) ---

// I.S. ListMenu LM tidak kosong.
// F.S. Elemen pertama LM dilepas dan alamatnya disimpan pada C.
void deleteFirstMenu(ListMenu &LM, adrMenu &C) {
    if (isEmptyMenu(LM)) {
        C = NULL;
    } else if (LM.first == LM.last) {
        C = LM.first;
        LM.first = NULL;
        LM.last = NULL;
    } else {
        C = LM.first;
        LM.first = C->next;
        LM.first->prev = NULL;
        C->next = NULL;
    }
}

// I.S. ListMenu LM tidak kosong.
// F.S. Elemen terakhir LM dilepas dan alamatnya disimpan pada C.
void deleteLastMenu(ListMenu &LM, adrMenu &C) {
    if (isEmptyMenu(LM)) {
        C = NULL;
    } else if (LM.first == LM.last) {
        C = LM.last;
        LM.first = NULL;
        LM.last = NULL;
    } else {
        C = LM.last;
        LM.last = C->prev;
        LM.last->next = NULL;
        C->prev = NULL;
    }
}

// I.S. ListMenu LM tidak kosong dan prec adalah alamat elemen valid yang memiliki suksesor.
// F.S. Elemen setelah prec dilepas dari LM dan alamatnya disimpan pada C.
void deleteAfterMenu(ListMenu &LM, adrMenu prec, adrMenu &C) {
    if (prec == NULL || prec->next == NULL) {
        C = NULL;
    } else if (prec->next == LM.last) {
        deleteLastMenu(LM, C);
    } else {
        C = prec->next;
        prec->next = C->next;
        C->next->prev = prec;
        C->next = NULL;
        C->prev = NULL;
    }
}

// --- Delete Primitif ListRelasi (SLL) ---

// I.S. ListRelasi LR tidak kosong.
// F.S. Elemen pertama LR dilepas dan alamatnya disimpan pada R.
void deleteFirstRelasi(ListRelasi &LR, adrRelasi &R) {
    if (isEmptyRelasi(LR)) {
        R = NULL;
    } else {
        R = LR.first;
        LR.first = R->next;
        R->next = NULL;
    }
}

// I.S. ListRelasi LR tidak kosong dan prec adalah alamat elemen valid yang memiliki suksesor.
// F.S. Elemen setelah prec dilepas dari LR dan alamatnya disimpan pada R.
void deleteAfterRelasi(ListRelasi &LR, adrRelasi prec, adrRelasi &R) {
    if (prec == NULL || prec->next == NULL) {
        R = NULL;
    } else {
        R = prec->next;
        prec->next = R->next;
        R->next = NULL;
    }
}

// --- Cascade Delete & Hapus Spesifik ---

// I.S. ListRelasi LR dan nomorOrder terdefinisi.
// F.S. Seluruh elemen relasi yang merujuk ke nomorOrder dihapus dan didealokasi dari LR.
void deleteAllRelasiByOrder(ListRelasi &LR, int nomorOrder) {
    adrRelasi curr = LR.first;
    adrRelasi prev = NULL;
    while (curr != NULL) {
        if (curr->parent != NULL && curr->parent->info.nomorOrder == nomorOrder) {
            adrRelasi del = NULL;
            if (prev == NULL) {
                deleteFirstRelasi(LR, del);
                curr = LR.first;
            } else {
                deleteAfterRelasi(LR, prev, del);
                curr = prev->next;
            }
            delete del;
        } else {
            prev = curr;
            curr = curr->next;
        }
    }
}

// I.S. ListRelasi LR dan idMenu terdefinisi.
// F.S. Seluruh elemen relasi yang merujuk ke idMenu dihapus dan didealokasi dari LR.
void deleteAllRelasiByMenu(ListRelasi &LR, string idMenu) {
    adrRelasi curr = LR.first;
    adrRelasi prev = NULL;
    string target = toLowerString(idMenu);
    while (curr != NULL) {
        if (curr->child != NULL && toLowerString(curr->child->info.idMenu) == target) {
            adrRelasi del = NULL;
            if (prev == NULL) {
                deleteFirstRelasi(LR, del);
                curr = LR.first;
            } else {
                deleteAfterRelasi(LR, prev, del);
                curr = prev->next;
            }
            delete del;
        } else {
            prev = curr;
            curr = curr->next;
        }
    }
}

// I.S. ListOrder LO, ListRelasi LR, dan nomorOrder terdefinisi.
// F.S. Jika ditemukan, seluruh relasi milik nomorOrder dan elemen Order tersebut dihapus serta didealokasi.
void deleteOrderByNomor(ListOrder &LO, ListRelasi &LR, int nomorOrder) {
    adrOrder target = findOrder(LO, nomorOrder);
    if (target == NULL) {
        cout << "Order #" << nomorOrder << " tidak ditemukan pada MLL." << endl;
    } else {
        deleteAllRelasiByOrder(LR, nomorOrder);
        adrOrder del = NULL;
        if (target == LO.first) {
            deleteFirstOrder(LO, del);
        } else if (target == LO.last) {
            deleteLastOrder(LO, del);
        } else {
            deleteAfterOrder(LO, target->prev, del);
        }
        delete del;
        cout << "Order #" << nomorOrder << " beserta seluruh item relasinya berhasil dihapus dari MLL." << endl;
    }
}

// I.S. ListMenu LM, ListRelasi LR, dan idMenu terdefinisi.
// F.S. Jika ditemukan, seluruh relasi milik idMenu dan elemen Menu tersebut dihapus serta didealokasi.
void deleteMenuByID(ListMenu &LM, ListRelasi &LR, string idMenu) {
    adrMenu target = findMenu(LM, idMenu);
    if (target == NULL) {
        cout << "Menu dengan ID '" << idMenu << "' tidak ditemukan." << endl;
    } else {
        string idAsli = target->info.idMenu;
        deleteAllRelasiByMenu(LR, idAsli);
        adrMenu del = NULL;
        if (target == LM.first) {
            deleteFirstMenu(LM, del);
        } else if (target == LM.last) {
            deleteLastMenu(LM, del);
        } else {
            deleteAfterMenu(LM, target->prev, del);
        }
        delete del;
        cout << "Menu '" << idAsli << "' beserta seluruh relasinya berhasil dihapus." << endl;
    }
}

// I.S. ListRelasi LR, nomorOrder, dan idMenu terdefinisi.
// F.S. Jika ditemukan, satu elemen relasi antara nomorOrder dan idMenu dihapus dan didealokasi.
void deleteRelasiTertentu(ListRelasi &LR, int nomorOrder, string idMenu) {
    adrRelasi curr = LR.first;
    adrRelasi prev = NULL;
    bool found = false;
    string targetMenu = toLowerString(idMenu);

    while (curr != NULL && !found) {
        if (curr->parent != NULL && curr->child != NULL &&
            curr->parent->info.nomorOrder == nomorOrder &&
            toLowerString(curr->child->info.idMenu) == targetMenu) {
            found = true;
        } else {
            prev = curr;
            curr = curr->next;
        }
    }

    if (found) {
        adrRelasi del = NULL;
        if (prev == NULL) {
            deleteFirstRelasi(LR, del);
        } else {
            deleteAfterRelasi(LR, prev, del);
        }
        delete del;
        cout << "Relasi antara Order #" << nomorOrder << " dan Menu '" << idMenu << "' berhasil dihapus." << endl;
    } else {
        cout << "Relasi antara Order #" << nomorOrder << " dan Menu '" << idMenu << "' tidak ditemukan." << endl;
    }
}

// --- Update Status ---

// I.S. ListOrder LO, BST root, nomorOrder, dan statusBaru terdefinisi.
// F.S. Jika nomorOrder ditemukan, statusPesanan diperbarui pada ListOrder LO dan disinkronkan pada BST root.
void updateStatusOrder(ListOrder &LO, adrBST &root, int nomorOrder, string statusBaru) {
    adrOrder P = findOrder(LO, nomorOrder);
    adrBST B = searchBST(root, nomorOrder);

    if (P == NULL && B == NULL) {
        cout << "Order #" << nomorOrder << " tidak ditemukan." << endl;
    } else {
        if (P != NULL) {
            P->info.statusPesanan = statusBaru;
        }
        if (B != NULL) {
            B->info.statusPesanan = statusBaru;
        }
        cout << "Status Order #" << nomorOrder << " berhasil diperbarui menjadi '" << statusBaru << "'." << endl;
    }
}

// --- Show & Count ---

// I.S. ListOrder LO terdefinisi.
// F.S. Menampilkan seluruh daftar Order (parent) dalam bentuk tabel ke layar.
void showAllOrder(ListOrder LO) {
    cout << "\n==================== DAFTAR ORDER (PARENT) ====================" << endl;
    cout << left << setw(10) << "NO ORDER"
         << setw(16) << "ID PELANGGAN"
         << setw(14) << "WAKTU PESAN"
         << setw(16) << "STATUS" << endl;
    cout << "---------------------------------------------------------------" << endl;

    if (isEmptyOrder(LO)) {
        cout << "(Belum ada data order)" << endl;
    } else {
        adrOrder P = LO.first;
        while (P != NULL) {
            cout << left << setw(10) << P->info.nomorOrder
                 << setw(16) << P->info.idPelanggan
                 << setw(14) << P->info.waktuPesan
                 << setw(16) << P->info.statusPesanan << endl;
            P = P->next;
        }
    }
    cout << "===============================================================" << endl;
}

// I.S. ListMenu LM terdefinisi.
// F.S. Menampilkan seluruh daftar Menu (child) dalam bentuk tabel ke layar.
void showAllMenu(ListMenu LM) {
    cout << "\n======================== DAFTAR MENU (CHILD) ========================" << endl;
    cout << left << setw(10) << "ID MENU"
         << setw(26) << "NAMA MENU"
         << setw(14) << "KATEGORI"
         << setw(14) << "HARGA SATUAN" << endl;
    cout << "---------------------------------------------------------------------" << endl;

    if (isEmptyMenu(LM)) {
        cout << "(Belum ada data menu)" << endl;
    } else {
        adrMenu C = LM.first;
        while (C != NULL) {
            cout << left << setw(10) << C->info.idMenu
                 << setw(26) << C->info.namaMenu
                 << setw(14) << C->info.kategori
                 << "Rp " << C->info.hargaSatuan << endl;
            C = C->next;
        }
    }
    cout << "=====================================================================" << endl;
}

// I.S. ListOrder LO dan ListRelasi LR terdefinisi.
// F.S. Menampilkan seluruh Order beserta daftar Menu yang dipesan pada masing-masing Order.
void showAllOrderWithMenu(ListOrder LO, ListRelasi LR) {
    cout << "\n=============== DAFTAR SELURUH ORDER BESERTA MENU ===============" << endl;
    if (isEmptyOrder(LO)) {
        cout << "(Belum ada data order)" << endl;
    } else {
        adrOrder P = LO.first;
        while (P != NULL) {
            cout << "\n[Order #" << P->info.nomorOrder << "]"
                 << " | Pelanggan: " << P->info.idPelanggan
                 << " | Waktu: " << P->info.waktuPesan
                 << " (" << getSlotWaktu(P->info.waktuPesan) << ")"
                 << " | Status: " << P->info.statusPesanan << endl;

            adrRelasi R = LR.first;
            bool adaItem = false;
            int totalBayar = 0;

            while (R != NULL) {
                if (R->parent == P && R->child != NULL) {
                    int subtotal = R->info.jumlahPorsi * R->info.hargaSaatPesan;
                    totalBayar += subtotal;
                    cout << "   -> [" << R->child->info.idMenu << "] "
                         << R->child->info.namaMenu
                         << " (" << R->info.jumlahPorsi << " x Rp " << R->info.hargaSaatPesan
                         << " = Rp " << subtotal << ")"
                         << " | Catatan: " << R->info.catatan << endl;
                    adaItem = true;
                }
                R = R->next;
            }

            if (!adaItem) {
                cout << "   -> (Belum ada item menu yang dipesan)" << endl;
            } else {
                cout << "   Total Jenis Menu: " << countMenuByOrder(LR, P->info.nomorOrder)
                     << " | Total Bayar: Rp " << totalBayar << endl;
            }
            P = P->next;
        }
    }
    cout << "=================================================================" << endl;
}

// I.S. ListMenu LM dan ListRelasi LR terdefinisi.
// F.S. Menampilkan seluruh Menu beserta daftar Order yang memesan masing-masing Menu.
void showAllMenuWithOrder(ListMenu LM, ListRelasi LR) {
    cout << "\n=============== DAFTAR SELURUH MENU BESERTA ORDER ===============" << endl;
    if (isEmptyMenu(LM)) {
        cout << "(Belum ada data menu)" << endl;
    } else {
        adrMenu C = LM.first;
        while (C != NULL) {
            cout << "\n[" << C->info.idMenu << "] " << C->info.namaMenu
                 << " (" << C->info.kategori << " | Rp " << C->info.hargaSatuan << ")" << endl;

            adrRelasi R = LR.first;
            bool adaOrder = false;

            while (R != NULL) {
                if (R->child == C && R->parent != NULL) {
                    cout << "   -> Order #" << R->parent->info.nomorOrder
                         << " (Pelanggan: " << R->parent->info.idPelanggan
                         << ", Waktu: " << R->parent->info.waktuPesan
                         << ", Porsi: " << R->info.jumlahPorsi
                         << ", Status: " << R->parent->info.statusPesanan << ")" << endl;
                    adaOrder = true;
                }
                R = R->next;
            }

            if (!adaOrder) {
                cout << "   -> (Belum pernah dipesan)" << endl;
            } else {
                cout << "   Total Order Memesan Menu Ini: " << countOrderByMenu(LR, C->info.idMenu) << endl;
            }
            C = C->next;
        }
    }
    cout << "=================================================================" << endl;
}

// I.S. ListRelasi LR dan nomorOrder terdefinisi.
// F.S. Mengembalikan jumlah jenis Menu (child) yang berelasi dengan Order tertentu.
int countMenuByOrder(ListRelasi LR, int nomorOrder) {
    int count = 0;
    adrRelasi R = LR.first;
    while (R != NULL) {
        if (R->parent != NULL && R->parent->info.nomorOrder == nomorOrder) {
            count++;
        }
        R = R->next;
    }
    return count;
}

// I.S. ListRelasi LR dan idMenu terdefinisi.
// F.S. Mengembalikan jumlah Order (parent) yang berelasi dengan Menu tertentu.
int countOrderByMenu(ListRelasi LR, string idMenu) {
    int count = 0;
    string target = toLowerString(idMenu);
    adrRelasi R = LR.first;
    while (R != NULL) {
        if (R->child != NULL && toLowerString(R->child->info.idMenu) == target) {
            count++;
        }
        R = R->next;
    }
    return count;
}

// I.S. ListRelasi LR dan nomorOrder terdefinisi.
// F.S. Mengembalikan total biaya transaksi (jumlahPorsi * hargaSaatPesan) untuk nomorOrder tersebut.
int calculateTotalBayarOrder(ListRelasi LR, int nomorOrder) {
    int total = 0;
    adrRelasi R = LR.first;
    while (R != NULL) {
        if (R->parent != NULL && R->parent->info.nomorOrder == nomorOrder) {
            total += (R->info.jumlahPorsi * R->info.hargaSaatPesan);
        }
        R = R->next;
    }
    return total;
}

// ============================================================================
// 3. FUNGSIONALITAS UMUM BST (KEY: nomorOrder)
// ============================================================================

// I.S. Pointer root sembarang.
// F.S. Terbentuk BST kosong (root == NULL).
void createBST(adrBST &root) {
    root = NULL;
}

// I.S. data bertipe infotypeOrder terdefinisi.
// F.S. Mengembalikan alamat NodeBST baru dengan info = data, left = NULL, right = NULL.
adrBST allocateBST(infotypeOrder data) {
    adrBST node = new NodeBST;
    node->info = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// I.S. BST root mungkin kosong, data transaksi terdefinisi.
// F.S. Node baru dengan key data.nomorOrder disisipkan pada posisi BST yang sesuai (duplikat diabaikan).
void insertBST(adrBST &root, infotypeOrder data) {
    if (root == NULL) {
        root = allocateBST(data);
    } else if (data.nomorOrder < root->info.nomorOrder) {
        insertBST(root->left, data);
    } else if (data.nomorOrder > root->info.nomorOrder) {
        insertBST(root->right, data);
    }
}

// I.S. BST root dan key nomorOrder terdefinisi.
// F.S. Mengembalikan alamat NodeBST dengan key nomorOrder, atau NULL jika tidak ditemukan.
adrBST searchBST(adrBST root, int nomorOrder) {
    adrBST curr = root;
    adrBST hasil = NULL;
    while (curr != NULL && hasil == NULL) {
        if (nomorOrder == curr->info.nomorOrder) {
            hasil = curr;
        } else if (nomorOrder < curr->info.nomorOrder) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }
    return hasil;
}

// I.S. BST root terdefinisi.
// F.S. Mengembalikan alamat NodeBST dengan key nomorOrder terkecil, atau NULL jika pohon kosong.
adrBST findMinBST(adrBST root) {
    adrBST curr = root;
    while (curr != NULL && curr->left != NULL) {
        curr = curr->left;
    }
    return curr;
}

// I.S. BST root terdefinisi.
// F.S. Mengembalikan alamat NodeBST dengan key nomorOrder terbesar, atau NULL jika pohon kosong.
adrBST findMaxBST(adrBST root) {
    adrBST curr = root;
    while (curr != NULL && curr->right != NULL) {
        curr = curr->right;
    }
    return curr;
}

// I.S. BST root dan key nomorOrder terdefinisi.
// F.S. Node dengan key nomorOrder dihapus dari BST (menangani kasus 0, 1, dan 2 anak) dan didealokasi.
void deleteBST(adrBST &root, int nomorOrder) {
    if (root != NULL) {
        if (nomorOrder < root->info.nomorOrder) {
            deleteBST(root->left, nomorOrder);
        } else if (nomorOrder > root->info.nomorOrder) {
            deleteBST(root->right, nomorOrder);
        } else {
            // Kasus 1: Node daun (0 anak)
            if (root->left == NULL && root->right == NULL) {
                delete root;
                root = NULL;
            }
            // Kasus 2a: Hanya punya anak kanan (1 anak)
            else if (root->left == NULL) {
                adrBST temp = root;
                root = root->right;
                delete temp;
            }
            // Kasus 2b: Hanya punya anak kiri (1 anak)
            else if (root->right == NULL) {
                adrBST temp = root;
                root = root->left;
                delete temp;
            }
            // Kasus 3: Punya 2 anak (ganti dengan in-order successor dari subtree kanan)
            else {
                adrBST succ = findMinBST(root->right);
                root->info = succ->info;
                deleteBST(root->right, succ->info.nomorOrder);
            }
        }
    }
}

// I.S. BST root terdefinisi.
// F.S. Seluruh node pada BST ditampilkan dengan urutan In-Order (Left - Root - Right).
void inOrderBST(adrBST root) {
    if (root != NULL) {
        inOrderBST(root->left);
        cout << left << setw(10) << root->info.nomorOrder
             << setw(16) << root->info.idPelanggan
             << setw(14) << root->info.waktuPesan
             << setw(16) << root->info.statusPesanan << endl;
        inOrderBST(root->right);
    }
}

// I.S. BST root terdefinisi.
// F.S. Seluruh node pada BST ditampilkan dengan urutan Pre-Order (Root - Left - Right).
void preOrderBST(adrBST root) {
    if (root != NULL) {
        cout << left << setw(10) << root->info.nomorOrder
             << setw(16) << root->info.idPelanggan
             << setw(14) << root->info.waktuPesan
             << setw(16) << root->info.statusPesanan << endl;
        preOrderBST(root->left);
        preOrderBST(root->right);
    }
}

// I.S. BST root terdefinisi.
// F.S. Seluruh node pada BST ditampilkan dengan urutan Post-Order (Left - Right - Root).
void postOrderBST(adrBST root) {
    if (root != NULL) {
        postOrderBST(root->left);
        postOrderBST(root->right);
        cout << left << setw(10) << root->info.nomorOrder
             << setw(16) << root->info.idPelanggan
             << setw(14) << root->info.waktuPesan
             << setw(16) << root->info.statusPesanan << endl;
    }
}

// I.S. BST root terdefinisi.
// F.S. Mengembalikan tinggi pohon BST (0 jika kosong, 1 jika hanya terdiri dari 1 node root).
int heightBST(adrBST root) {
    int hasil = 0;
    if (root != NULL) {
        int kiri = heightBST(root->left);
        int kanan = heightBST(root->right);
        if (kiri > kanan) {
            hasil = 1 + kiri;
        } else {
            hasil = 1 + kanan;
        }
    }
    return hasil;
}

// I.S. BST root terdefinisi.
// F.S. Mengembalikan jumlah total node yang ada di dalam BST.
int countNodesBST(adrBST root) {
    int hasil = 0;
    if (root != NULL) {
        hasil = 1 + countNodesBST(root->left) + countNodesBST(root->right);
    }
    return hasil;
}

// I.S. BST root terdefinisi.
// F.S. Menampilkan informasi nilai minimum, maksimum, tinggi pohon, dan jumlah node BST ke layar.
void showStatistikBST(adrBST root) {
    cout << "\n================ STATISTIK BST RIWAYAT ORDER ================" << endl;
    if (root == NULL) {
        cout << "BST masih kosong." << endl;
    } else {
        adrBST minNode = findMinBST(root);
        adrBST maxNode = findMaxBST(root);
        cout << "Nomor Order Minimum : #" << minNode->info.nomorOrder
             << " (Pelanggan: " << minNode->info.idPelanggan
             << ", Status: " << minNode->info.statusPesanan << ")" << endl;
        cout << "Nomor Order Maksimum: #" << maxNode->info.nomorOrder
             << " (Pelanggan: " << maxNode->info.idPelanggan
             << ", Status: " << maxNode->info.statusPesanan << ")" << endl;
        cout << "Tinggi Pohon (Height): " << heightBST(root) << endl;
        cout << "Jumlah Total Node    : " << countNodesBST(root) << endl;
    }
    cout << "=============================================================" << endl;
}

// ============================================================================
// 4. FUNGSIONALITAS KHUSUS TOPIK 13
// ============================================================================

// Fungsionalitas Khusus 1:
// I.S. ListMenu LM dan ListRelasi LR terdefinisi.
// F.S. Menampilkan total jumlah porsi per idMenu serta menampilkan menu paling diminati pelanggan.
void hitungTotalPorsiPerMenu(ListMenu LM, ListRelasi LR) {
    cout << "\n============ TOTAL PORSI TERJUAL PER MENU ============" << endl;
    cout << left << setw(10) << "ID MENU"
         << setw(26) << "NAMA MENU"
         << setw(14) << "TOTAL PORSI" << endl;
    cout << "------------------------------------------------------" << endl;

    if (isEmptyMenu(LM)) {
        cout << "(Belum ada data menu)" << endl;
    } else {
        adrMenu C = LM.first;
        int maxPorsi = -1;

        while (C != NULL) {
            int totalPorsi = 0;
            adrRelasi R = LR.first;
            while (R != NULL) {
                if (R->child == C) {
                    totalPorsi += R->info.jumlahPorsi;
                }
                R = R->next;
            }
            cout << left << setw(10) << C->info.idMenu
                 << setw(26) << C->info.namaMenu
                 << setw(14) << totalPorsi << endl;

            if (totalPorsi > maxPorsi) {
                maxPorsi = totalPorsi;
            }
            C = C->next;
        }

        cout << "------------------------------------------------------" << endl;
        if (maxPorsi <= 0) {
            cout << "Belum ada porsi menu yang terjual." << endl;
        } else {
            cout << "Menu Paling Diminati (" << maxPorsi << " porsi):" << endl;
            C = LM.first;
            while (C != NULL) {
                int totalPorsi = 0;
                adrRelasi R = LR.first;
                while (R != NULL) {
                    if (R->child == C) {
                        totalPorsi += R->info.jumlahPorsi;
                    }
                    R = R->next;
                }
                if (totalPorsi == maxPorsi) {
                    cout << " * [" << C->info.idMenu << "] " << C->info.namaMenu << endl;
                }
                C = C->next;
            }
        }
    }
    cout << "======================================================" << endl;
}

// Fungsionalitas Khusus 2:
// I.S. ListOrder LO, ListMenu LM, dan ListRelasi LR terdefinisi.
// F.S. Menampilkan pasangan menu yang sering dipesan bersamaan dalam satu nomorOrder.
void analisisMenuBersamaan(ListOrder LO, ListMenu LM, ListRelasi LR) {
    cout << "\n========= ANALISIS MENU YANG DIPESAN BERSAMAAN =========" << endl;
    if (isEmptyOrder(LO) || isEmptyMenu(LM) || isEmptyRelasi(LR)) {
        cout << "(Data order, menu, atau relasi belum mencukupi untuk analisis)" << endl;
    } else {
        int maxBersamaan = 0;
        bool adaPasangan = false;

        adrMenu M1 = LM.first;
        while (M1 != NULL) {
            adrMenu M2 = M1->next;
            while (M2 != NULL) {
                int frekuensi = 0;
                adrOrder P = LO.first;
                while (P != NULL) {
                    if (isRelated(LR, P->info.nomorOrder, M1->info.idMenu) &&
                        isRelated(LR, P->info.nomorOrder, M2->info.idMenu)) {
                        frekuensi++;
                    }
                    P = P->next;
                }

                if (frekuensi > 0) {
                    adaPasangan = true;
                    cout << " - [" << M1->info.idMenu << "] " << M1->info.namaMenu
                         << "  +  [" << M2->info.idMenu << "] " << M2->info.namaMenu
                         << "  -->  " << frekuensi << " order bersamaan" << endl;
                    if (frekuensi > maxBersamaan) {
                        maxBersamaan = frekuensi;
                    }
                }
                M2 = M2->next;
            }
            M1 = M1->next;
        }

        if (!adaPasangan) {
            cout << "Belum ada pasangan menu yang dipesan bersamaan dalam satu order." << endl;
        } else {
            cout << "--------------------------------------------------------" << endl;
            cout << "Pasangan Paling Sering Dipesan Bersamaan (" << maxBersamaan << "x):" << endl;

            M1 = LM.first;
            while (M1 != NULL) {
                adrMenu M2 = M1->next;
                while (M2 != NULL) {
                    int frekuensi = 0;
                    adrOrder P = LO.first;
                    while (P != NULL) {
                        if (isRelated(LR, P->info.nomorOrder, M1->info.idMenu) &&
                            isRelated(LR, P->info.nomorOrder, M2->info.idMenu)) {
                            frekuensi++;
                        }
                        P = P->next;
                    }

                    if (frekuensi == maxBersamaan) {
                        cout << " * " << M1->info.namaMenu << " + " << M2->info.namaMenu << endl;
                    }
                    M2 = M2->next;
                }
                M1 = M1->next;
            }
        }
    }
    cout << "========================================================" << endl;
}

// Fungsionalitas Khusus 3:
// I.S. ListMenu LM dan ListRelasi LR terdefinisi.
// F.S. Menampilkan total pendapatan per menu (jumlahPorsi * hargaSaatPesan) dan total keseluruhan.
void hitungPendapatanPerMenu(ListMenu LM, ListRelasi LR) {
    cout << "\n================ TOTAL PENDAPATAN PER MENU ================" << endl;
    cout << left << setw(10) << "ID MENU"
         << setw(26) << "NAMA MENU"
         << setw(20) << "TOTAL PENDAPATAN" << endl;
    cout << "-----------------------------------------------------------" << endl;

    if (isEmptyMenu(LM)) {
        cout << "(Belum ada data menu)" << endl;
    } else {
        int grandTotal = 0;
        adrMenu C = LM.first;
        while (C != NULL) {
            int pendapatan = 0;
            adrRelasi R = LR.first;
            while (R != NULL) {
                if (R->child == C) {
                    pendapatan += (R->info.jumlahPorsi * R->info.hargaSaatPesan);
                }
                R = R->next;
            }
            grandTotal += pendapatan;
            cout << left << setw(10) << C->info.idMenu
                 << setw(26) << C->info.namaMenu
                 << "Rp " << pendapatan << endl;
            C = C->next;
        }
        cout << "-----------------------------------------------------------" << endl;
        cout << "TOTAL PENDAPATAN KESELURUHAN: Rp " << grandTotal << endl;
    }
    cout << "===========================================================" << endl;
}

// Fungsionalitas Khusus 4:
// I.S. ListMenu LM, ListRelasi LR, dan idMenu terdefinisi.
// F.S. Menggabungkan waktuPesan dengan idMenu untuk menampilkan distribusi waktu pemesanan
//      (Pagi/Siang/Sore/Malam) serta waktu favorit pelanggan memesan menu tersebut.
void analisisWaktuFavoritMenu(ListMenu LM, ListRelasi LR, string idMenu) {
    adrMenu C = findMenu(LM, idMenu);
    cout << "\n=========== ANALISIS WAKTU FAVORIT PEMESANAN MENU ===========" << endl;

    if (C == NULL) {
        cout << "Menu dengan ID '" << idMenu << "' tidak ditemukan." << endl;
    } else {
        int pagi = 0, siang = 0, sore = 0, malam = 0;
        int porsiPagi = 0, porsiSiang = 0, porsiSore = 0, porsiMalam = 0;

        cout << "Menu: [" << C->info.idMenu << "] " << C->info.namaMenu << endl;
        cout << "Detail Pemesanan:" << endl;

        adrRelasi R = LR.first;
        bool adaData = false;
        while (R != NULL) {
            if (R->child == C && R->parent != NULL) {
                adaData = true;
                string slot = getSlotWaktu(R->parent->info.waktuPesan);
                cout << " - Order #" << R->parent->info.nomorOrder
                     << " | Waktu: " << R->parent->info.waktuPesan
                     << " (" << slot << ") | Porsi: " << R->info.jumlahPorsi << endl;

                if (slot == "Pagi") {
                    pagi++;
                    porsiPagi += R->info.jumlahPorsi;
                } else if (slot == "Siang") {
                    siang++;
                    porsiSiang += R->info.jumlahPorsi;
                } else if (slot == "Sore") {
                    sore++;
                    porsiSore += R->info.jumlahPorsi;
                } else if (slot == "Malam") {
                    malam++;
                    porsiMalam += R->info.jumlahPorsi;
                }
            }
            R = R->next;
        }

        if (!adaData) {
            cout << "(Menu ini belum memiliki riwayat pemesanan)" << endl;
        } else {
            cout << "-------------------------------------------------------------" << endl;
            cout << "Rekap Distribusi Waktu:" << endl;
            cout << " * Pagi  (05:00-10:59) : " << pagi << " transaksi (" << porsiPagi << " porsi)" << endl;
            cout << " * Siang (11:00-14:59) : " << siang << " transaksi (" << porsiSiang << " porsi)" << endl;
            cout << " * Sore  (15:00-17:59) : " << sore << " transaksi (" << porsiSore << " porsi)" << endl;
            cout << " * Malam (18:00-04:59) : " << malam << " transaksi (" << porsiMalam << " porsi)" << endl;

            int maxPorsi = porsiPagi;
            if (porsiSiang > maxPorsi) maxPorsi = porsiSiang;
            if (porsiSore > maxPorsi) maxPorsi = porsiSore;
            if (porsiMalam > maxPorsi) maxPorsi = porsiMalam;

            cout << "Waktu Favorit Pelanggan (" << maxPorsi << " porsi): ";
            bool pertama = true;
            if (porsiPagi == maxPorsi) {
                cout << "Pagi";
                pertama = false;
            }
            if (porsiSiang == maxPorsi) {
                if (!pertama) cout << ", ";
                cout << "Siang";
                pertama = false;
            }
            if (porsiSore == maxPorsi) {
                if (!pertama) cout << ", ";
                cout << "Sore";
                pertama = false;
            }
            if (porsiMalam == maxPorsi) {
                if (!pertama) cout << ", ";
                cout << "Malam";
            }
            cout << endl;
        }
    }
    cout << "=============================================================" << endl;
}

// ============================================================================
// 5. UTILITAS & DEALOKASI MEMORI
// ============================================================================

// I.S. waktuPesan dalam format "HH:MM" terdefinisi.
// F.S. Mengembalikan kategori slot waktu: "Pagi" (05-10), "Siang" (11-14), "Sore" (15-17), atau "Malam" (18-04).
string getSlotWaktu(string waktuPesan) {
    int jam = -1;
    if (waktuPesan.length() >= 2 &&
        waktuPesan[0] >= '0' && waktuPesan[0] <= '9' &&
        waktuPesan[1] >= '0' && waktuPesan[1] <= '9') {
        jam = (waktuPesan[0] - '0') * 10 + (waktuPesan[1] - '0');
    } else if (waktuPesan.length() >= 1 &&
               waktuPesan[0] >= '0' && waktuPesan[0] <= '9') {
        jam = waktuPesan[0] - '0';
    }

    string slot = "Tidak Valid";
    if (jam >= 5 && jam <= 10) {
        slot = "Pagi";
    } else if (jam >= 11 && jam <= 14) {
        slot = "Siang";
    } else if (jam >= 15 && jam <= 17) {
        slot = "Sore";
    } else if ((jam >= 18 && jam <= 23) || (jam >= 0 && jam <= 4)) {
        slot = "Malam";
    }
    return slot;
}

// I.S. teks bertipe string terdefinisi.
// F.S. Mengembalikan salinan teks dengan seluruh huruf kapital diubah menjadi huruf kecil.
string toLowerString(string teks) {
    string hasil = "";
    for (size_t i = 0; i < teks.length(); i++) {
        if (teks[i] >= 'A' && teks[i] <= 'Z') {
            hasil += char(teks[i] + 32);
        } else {
            hasil += teks[i];
        }
    }
    return hasil;
}

// I.S. BST root terdefinisi.
// F.S. Seluruh node BST didealokasi secara post-order sehingga root menjadi NULL.
void deleteAllBST(adrBST &root) {
    if (root != NULL) {
        deleteAllBST(root->left);
        deleteAllBST(root->right);
        delete root;
        root = NULL;
    }
}

// I.S. ListOrder LO, ListMenu LM, ListRelasi LR, dan BST root terdefinisi.
// F.S. Seluruh elemen MLL-02 dan seluruh node BST didealokasi dengan aman.
void dealokasiSemua(ListOrder &LO, ListMenu &LM, ListRelasi &LR, adrBST &root) {
    adrRelasi R = NULL;
    while (!isEmptyRelasi(LR)) {
        deleteFirstRelasi(LR, R);
        delete R;
    }

    adrOrder P = NULL;
    while (!isEmptyOrder(LO)) {
        deleteFirstOrder(LO, P);
        delete P;
    }

    adrMenu C = NULL;
    while (!isEmptyMenu(LM)) {
        deleteFirstMenu(LM, C);
        delete C;
    }

    deleteAllBST(root);
}
