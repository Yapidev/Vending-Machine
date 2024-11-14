 do {
        tampilkanMenu();

        // Input kode produk dan cek harga produk
        printf("Masukkan kode produk yang ingin dibeli (atau 0 untuk batal): ");
        scanf("%d", &kode);
        if (kode == 0) {
            printf("Pembelian dibatalkan.\n");
            break;; // Kembali ke awal jika dibatalkan
        }

        pilihProduk(kode, &harga);
        if (harga == 0) continue; // Kembali ke awal jika kode tidak valid

        // Memilih metode pembayaran
        printf("\nPilih metode pembayaran:\n");
        printf("1. Tunai\n");
        printf("2. QRIS\n");
        printf("3. Kembali ke menu awal\n");
        printf("Masukkan pilihan (1/2/3): ");
        scanf("%d", &metode);

        // Proses pembayaran berdasarkan metode
        if (metode == 1) {
            pembayaranTunai(harga);
        } else if (metode == 2) {
            pembayaranQRIS(harga);
        } else if (metode == 3) {
            continue;
        }   else {
            printf("Metode pembayaran tidak valid!\n");
        }

        // Tanyakan apakah ingin membeli lagi
        printf("\nApakah Anda ingin membeli lagi? (y/n): ");
        scanf(" %c", &beliLagi);

    } while (beliLagi == 'y' || beliLagi == 'Y');