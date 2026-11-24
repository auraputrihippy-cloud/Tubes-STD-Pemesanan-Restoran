# 🍽️ Sistem Pemesanan Menu Restoran (C++)

Aplikasi manajemen pemesanan menu restoran berbasis _console_ (CLI) yang dibangun menggunakan bahasa C++. Proyek ini mengimplementasikan struktur data **Multi-Linked List (1-to-N)** berbasis **Doubly Linked List** (*Parent-Child*) untuk mengelola hubungan antara data Pesanan Pelanggan dan daftar Item Menu yang dipesan.

## 📋 Fitur Utama

Aplikasi ini dilengkapi operasi **CRUD** (Create, Read, Update, Delete) secara menyeluruh, perhitungan tagihan otomatis, pencarian lintas pesanan, serta pengurutan tabel:

### 1. Manajemen Pesanan (Parent)
- **Insert:** Membuat pesanan baru berdasarkan kode pesanan unik (otomatis terurut secara alfabetis / *sorted insert* A–Z) dengan status awal `Diproses`.
- **Update:** Memperbarui nama pelanggan, nomor meja, dan status pesanan (`Diproses` / `Selesai` / `Dibayar`).
- **Delete:** Membatalkan atau menghapus pesanan beserta seluruh item menu di dalamnya secara otomatis (*cascade delete*) sekaligus membebaskan memori.
- **View & Struk:** Menampilkan ringkasan seluruh pesanan dalam format tabel yang rapi serta rincian struk pesanan lengkap dengan subtotal per item, total porsi, dan total bayar.

### 2. Manajemen Item Menu Pesanan (Child)
- **Insert:** Menambahkan item menu (nama menu, kategori, harga satuan, dan jumlah porsi) ke pesanan tertentu. Jika menu dengan nama yang sama ditambahkan lagi ke pesanan yang sama, jumlah porsi otomatis digabungkan.
- **Update:** Mengubah nama menu, kategori (`Makanan` / `Minuman` / `Snack` / `Dessert`), harga satuan, dan jumlah porsi.
- **Delete:** Menghapus item menu tertentu dari sebuah pesanan.
- **Search:** Mencari seluruh pesanan yang memesan suatu nama menu tertentu beserta rincian jumlah porsi dan subtotalnya.

### 3. Fitur Lanjutan (Sorting & Perhitungan Otomatis)
Aplikasi mendukung pengurutan tabel pesanan menggunakan algoritma **Selection Sort** berdasarkan 6 kriteria:
- 🔤 **Mode 1:** Kode Pesanan (A–Z)
- 💰 **Mode 2:** Total Bayar Tertinggi
- 💵 **Mode 3:** Total Bayar Terendah
- 🔢 **Mode 4:** Total Porsi Terbanyak
- 🍛 **Mode 5:** Jumlah Porsi _Makanan_ Terbanyak
- 🥤 **Mode 6:** Jumlah Porsi _Minuman_ Terbanyak

## 🛠️ Struktur Data & Susunan File

Proyek ini menggunakan **Multi-Linked List** (*List of Lists*):
- **List Parent (`ListPesanan`):** Menggunakan _Doubly Linked List_ (`next` dan `prev`). Setiap _node_ pesanan (`elemenPesanan`) memiliki pointer ke _node_ item menu pertamanya (`firstItem`).
- **List Child (`elemenItem`):** Menggunakan _Doubly Linked List_ (`next` dan `prev`) yang menyimpan rincian menu dalam lingkup satu pesanan.

**Susunan File Proyek:**
- `main.cpp` — Program utama (menu interaktif berbasis CLI).
- `pemesanan.h` — Header file berisi deklarasi struktur data (ADT) dan prototipe fungsi/prosedur.
- `pemesanan.cpp` — Implementasi logika linked list, perhitungan total bayar, pengurutan, serta tampilan tabel dan struk.
- `TUBES_RESTORAN.cbp` — File konfigurasi proyek untuk Code::Blocks IDE.
- `dummy_data.txt` — Data sampel siap pakai untuk pengujian cepat.

## 🚀 Cara Menjalankan

### Opsi 1: Menggunakan Terminal / Command Prompt (CLI)
**Prasyarat:** Compiler C++ (`g++` / Clang / MinGW).

1. Buka Terminal atau CMD lalu masuk ke folder proyek.
2. Kompilasi program:
   ```bash
   g++ main.cpp pemesanan.cpp -o pemesanan_app
   ```
3. Jalankan program:
   - **macOS / Linux:**
     ```bash
     ./pemesanan_app
     ```
   - **Windows:**
     ```bash
     pemesanan_app.exe
     ```

### Opsi 2: Menggunakan Code::Blocks IDE
1. Pastikan file `main.cpp`, `pemesanan.cpp`, `pemesanan.h`, dan `TUBES_RESTORAN.cbp` berada di dalam satu folder yang sama.
2. Buka file `TUBES_RESTORAN.cbp` langsung menggunakan Code::Blocks.
3. Tekan tombol **F9** (*Build and Run*) untuk menjalankan aplikasi.

*(Jika membuat proyek baru secara manual di Code::Blocks: pilih **Console Application (C++)**, hapus file `main.cpp` bawaan, salin `main.cpp`, `pemesanan.cpp`, dan `pemesanan.h` ke folder proyek, lalu klik kanan nama proyek > **Add files...** untuk menambahkan ketiganya).*

## 📚 Data Dummy (Copy & Paste)

Berikut adalah [data](dummy_data.txt) sampel yang dapat digunakan untuk menguji aplikasi.

**Cara penggunaan:** Jalankan aplikasi hingga muncul prompt `Pilihan: `, lalu salin seluruh isi file [dummy_data.txt](dummy_data.txt), tempel (*paste*) langsung ke jendela terminal, dan tekan **Enter** untuk mengisi 5 pesanan beserta 15 item menu secara otomatis.