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

    printf("Terima kasih! Sampai jumpa lagi!\n");
    return 0;
}
