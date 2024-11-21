#include <stdio.h>
#include <time.h>

// Struktur untuk menyimpan informasi produk
typedef struct {
    int kode;
    const char *nama;
    int harga;
} Produk;

// Daftar produk yang tersedia
Produk daftarProduk[] = {
    {101, "Aquah", 4000},
    {102, "Teh Pucuk", 5000},
    {103, "Mizon", 9000},
    {201, "Ciki Ciki", 4000},
    {202, "Doritos", 5000},
    {203, "Chisato", 8000}
};
int jumlahProduk = sizeof(daftarProduk) / sizeof(daftarProduk[0]);

// Fungsi untuk mendapatkan pointer produk berdasarkan kode
Produk* pilihProduk(int kode) {
    for (int i = 0; i < jumlahProduk; i++) {
        if (daftarProduk[i].kode == kode) {
            return &daftarProduk[i];
        }
    }
    return NULL; // Produk tidak ditemukan
}

// Fungsi untuk menampilkan menu produk
void tampilkanMenu() {
    printf("+------------------------------------------+\n");
    printf("|           VENDING MACHINE CERIA          |\n");
    printf("+------------------------------------------+\n");
    for (int i = 0; i < jumlahProduk; i++) {
        printf("| %-11s | (Rp %d) | (Kode: %d)    |\n", daftarProduk[i].nama, daftarProduk[i].harga, daftarProduk[i].kode);
    }
    printf("+------------------------------------------+\n");
}

// Fungsi untuk menangani pembayaran tunai
void pembayaranTunai(int harga, int *kembalian) {
    int uang;
    do {
        printf("Masukkan uang Anda: ");
        scanf("%d", &uang);

        if (uang < harga) {
            printf("Uang tidak cukup. Harga produk adalah Rp%d.\n", harga);
        } 

    } while (uang < harga);

    *kembalian = uang - harga;
    if (*kembalian == 0) {
        printf("Uang pas. Terima kasih telah berbelanja!\n");
    } else {
        printf("Terima kasih telah berbelanja! Kembalian Anda: Rp%d\n", *kembalian);
    }
}

// Fungsi untuk menangani pembayaran QRIS
void pembayaranQRIS(int harga, int *kembalian) {
    int uang;
    printf("\n=============== QRIS Payment ===============\n");
    printf("|                                          |\n");
    printf("|      ##############################      |\n");
    printf("|      ##                          ##      |\n");
    printf("|      ##  ##  ####  ##  ##  ####  ##      |\n");
    printf("|      ##  ##    ##  ##  ##    ######      |\n");
    printf("|      ##  ####  ##  ######  ####  ##      |\n");
    printf("|      ##    ##  ##    ##    ##    ##      |\n");
    printf("|      ##############################      |\n");
    printf("|      ##  ##  ##      ######  ##  ##      |\n");
    printf("|      ##      ######    ##      ####      |\n");
    printf("|      ##  ##  ##  ##    ##    ##   #      |\n");
    printf("|      ##  ######  ######  ######  ##      |\n");
    printf("|      ##      ##  ##  ##   ## ######      |\n");
    printf("|      ##############################      |\n");
    printf("|                                          |\n");
    printf("============================================\n");
    printf("|    Scan kode ini menggunakan aplikasi    |\n");
    printf("|     pembayaran QRIS untuk melanjutkan    |\n");
    printf("============================================\n\n");
    
    printf("Silakan lakukan pembayaran sebesar Rp%d dengan QRIS.\n", harga);

    do {
        printf("Masukkan uang Anda: ");
        scanf("%d", &uang);

        if (uang < harga) {
            printf("Uang tidak cukup. Harga produk adalah Rp%d.\n", harga);
        }

    } while (uang < harga);

    *kembalian = uang - harga;
    if (*kembalian == 0) {
        printf("Uang pas. Terima kasih telah berbelanja!\n");
    } else {
        printf("Terima kasih telah berbelanja! Kembalian Anda: Rp%d\n", *kembalian);
    }
}

// Fungsi untuk mencatat rekap pembelian ke dalam file teks
void rekapPembelian(const char *namaProduk, int kode, int harga, int metode, const char *status, int kembalian) {
    FILE *file = fopen("rekap_pembelian.txt", "a");
    
    if (file == NULL) {
        printf("Gagal membuka file untuk rekap pembelian.\n");
        return;
    }

    // Dapatkan tanggal dan waktu saat ini
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    char tanggal[20];
    strftime(tanggal, sizeof(tanggal), "%Y-%m-%d %H:%M:%S", tm_info);

    // Tulis rekap pembelian ke dalam file
    fprintf(file, "Tanggal: %s\n", tanggal);
    fprintf(file, "Nama Produk: %s\n", namaProduk);
    fprintf(file, "Kode Produk: %d\n", kode);
    fprintf(file, "Harga: Rp%d\n", harga);
    fprintf(file, "Metode Pembayaran: %s\n", 
        (metode == 1) ? "Tunai" : 
        (metode == 2) ? "QRIS" : 
        "Invalid");
    fprintf(file, "Status Transaksi: %s\n", status);
    if (kembalian > 0) {
        fprintf(file, "Kembalian: Rp%d\n", kembalian);
    }
    fprintf(file, "------------------------------------------\n");

    fclose(file);
}

// Fungsi untuk print Analisis Program
void analisisProgram() {
    printf("\n========== ANALISIS PROGRAM ==========\n");

    printf("\nTUJUAN PROGRAM:\n");

    printf("Program ini adalah simulasi vending machine digital dengan fitur:\n");
    printf("1. Melihat daftar produk yang tersedia.\n");
    printf("2. Memilih produk berdasarkan kode.\n");
    printf("3. Melakukan pembayaran (Tunai/QRIS).\n");
    printf("4. Mencatat transaksi ke dalam file teks.\n");
    printf("5. Memberikan kembalian jika ada.\n");
    printf("6. Mendukung pembatalan transaksi.\n\n");

    printf("STRUKTUR DATA:\n");
    printf("- Struktur Produk menyimpan kode, nama, dan harga produk.\n");
    printf("- Array daftarProduk menyimpan semua produk yang tersedia.\n\n");

    printf("FUNGSI UTAMA:\n");
    printf("1. pilihProduk(kode):\n");
    printf("   - Menemukan produk berdasarkan kode.\n");
    printf("   - Mengembalikan pointer ke produk jika ditemukan.\n");
    printf("\n2. tampilkanMenu():\n");
    printf("   - Menampilkan daftar produk dalam format tabel.\n");
    printf("\n3. pembayaranTunai(harga, *kembalian):\n");
    printf("   - Mengatur pembayaran tunai, memvalidasi jumlah uang, dan menghitung kembalian.\n");
    printf("\n4. pembayaranQRIS(harga, *kembalian):\n");
    printf("   - Mensimulasikan pembayaran QRIS, memvalidasi jumlah uang, dan menghitung kembalian.\n");
    printf("\n5. rekapPembelian(...):\n");
    printf("   - Mencatat transaksi ke dalam file rekap_pembelian.txt, termasuk waktu transaksi.\n");
    printf("\n6. main():\n");
    printf("   - Mengatur alur utama program, termasuk memilih produk, metode pembayaran, dan pembelian berulang.\n\n");

    printf("KEUNGGULAN:\n");
    printf("1. Modular: Fungsi-fungsi terpisah mempermudah pemeliharaan.\n");
    printf("2. Fleksibilitas: Mendukung pembayaran tunai dan QRIS.\n");
    printf("3. Rekap Transaksi: Setiap transaksi tercatat dalam file untuk referensi.\n");

    printf("\nPOTENSI PENINGKATAN:\n");
    printf("1. Validasi input non-numerik pada kode produk dan jumlah uang.\n");
    printf("2. Menambahkan laporan ringkasan pembelian setelah program selesai.\n");
    printf("3. Penanganan error jika file rekap gagal dibuka.\n");
    printf("======================================\n");
}

// Fungsi utama program
int main() {
    int kode, metode, kembalian = 0;
    char beliLagi;
    Produk *produk;

    do {
        tampilkanMenu();

        printf("Masukkan kode produk yang ingin dibeli (atau 0 untuk batal): ");
        scanf("%d", &kode);
        if (kode == 0) {
            rekapPembelian("Tidak ada", kode, 0, 0, "Batal", 0);
            printf("Pembelian dibatalkan.\n");
            break;
        }

        // Cari produk berdasarkan kode
        produk = pilihProduk(kode);
        if (produk == NULL) {
            rekapPembelian("Tidak valid", kode, 0, 0, "Batal", 0);
            printf("Kode yang dimasukkan tidak valid!\n\n");
            continue;
        }

        printf("\nPilih metode pembayaran:\n");
        printf("1. Tunai\n");
        printf("2. QRIS\n");
        printf("3. Kembali ke menu awal\n");
        printf("Masukkan pilihan (1/2/3): ");
        scanf("%d", &metode);

        if (metode == 1) {
            pembayaranTunai(produk->harga, &kembalian);
            rekapPembelian(produk->nama, produk->kode, produk->harga, metode, "Sukses", kembalian);
        } else if (metode == 2) {
            pembayaranQRIS(produk->harga, &kembalian);
            rekapPembelian(produk->nama, produk->kode, produk->harga, metode, "Sukses", kembalian);
        } else if (metode == 3) {
            rekapPembelian(produk->nama, produk->kode, produk->harga, metode, "Batal", 0);
            continue;
        } else {
            printf("Metode pembayaran tidak valid!\n");
        }

        printf("\nApakah Anda ingin membeli lagi? (y/n): ");
        scanf(" %c", &beliLagi);

    } while (beliLagi == 'y' || beliLagi == 'Y');

    printf("\nTerima kasih! Sampai jumpa lagi!\n");

    analisisProgram();
    
    return 0;
}
