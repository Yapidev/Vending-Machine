#include <stdio.h>
#include <time.h>

// Fungsi untuk menentukan harga dan nama produk berdasarkan kode produk
void pilihProduk(int kode, int *harga, const char **namaProduk) {
    switch (kode) {
        case 101:
            *namaProduk = "Aquah";
            *harga = 4000;
            break;
        case 102:
            *namaProduk = "Teh Pucuk";
            *harga = 5000;
            break;
        case 103:
            *namaProduk = "Mizon";
            *harga = 9000;
            break;
        case 201:
            *namaProduk = "Ciki Ciki";
            *harga = 4000;
            break;
        case 202:
            *namaProduk = "Doritos";
            *harga = 5000;
            break;
        case 203:
            *namaProduk = "Chisato";
            *harga = 10000;
            break;
        default:
            *namaProduk = "Tidak valid";
            *harga = 0;
            printf("Kode yang dimasukkan tidak valid!\n\n");
    }
}

// Fungsi untuk menampilkan menu produk
void tampilkanMenu() {
    printf("+------------------------------------------+\n");
    printf("|           VENDING MACHINE CERIA          |\n");
    printf("+------------------------------------------+\n");
    printf("|    Aquah    |   Teh Pucuk   |    Mizon   |\n");
    printf("|   (Rp 4000) |   (Rp 5000)   |  (Rp 9000) |\n");
    printf("|  (Kode: 101)|  (Kode: 102)  | (Kode: 103)|\n");
    printf("+------------------------------------------+\n");
    printf("|  Ciki Ciki  |    Doritos    |  Chisato   |\n");
    printf("|  (Rp 4000)  |   (Rp 5000)   | (Rp 10000) |\n");
    printf("| (Kode: 201) |  (Kode: 202)  | (Kode: 203)|\n");
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
    
    // Jika file gagal dibuka, coba buat file baru
    if (file == NULL) {
        file = fopen("rekap_pembelian.txt", "w");
        if (file == NULL) {
            printf("Gagal membuat file untuk rekap pembelian.\n");
            return;
        }
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
    // printf("Rekap pembelian berhasil dicatat.\n");
}

// Fungsi utama program
int main() {
    int kode, harga, metode, kembalian = 0;
    char beliLagi;
    const char *namaProduk;

    do {
        tampilkanMenu();

        printf("Masukkan kode produk yang ingin dibeli (atau 0 untuk batal): ");
        scanf("%d", &kode);
        if (kode == 0) {
            rekapPembelian("Tidak ada", kode, 0, 0, "Batal", 0);
            printf("Pembelian dibatalkan.\n");
            break;
        }

        // Tentukan nama produk dan harga berdasarkan kode
        pilihProduk(kode, &harga, &namaProduk);
        if (harga == 0) {
            rekapPembelian("Tidak valid", kode, harga, 0, "Batal", 0);
            continue;
        }

        printf("\nPilih metode pembayaran:\n");
        printf("1. Tunai\n");
        printf("2. QRIS\n");
        printf("3. Kembali ke menu awal\n");
        printf("Masukkan pilihan (1/2/3): ");
        scanf("%d", &metode);

        if (metode == 1) {
            pembayaranTunai(harga, &kembalian);
            rekapPembelian(namaProduk, kode, harga, metode, "Sukses", kembalian);
        } else if (metode == 2) {
            pembayaranQRIS(harga, &kembalian);
            rekapPembelian(namaProduk, kode, harga, metode, "Sukses", kembalian);
        } else if (metode == 3) {
            rekapPembelian(namaProduk, kode, harga, metode, "Batal", 0);
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
