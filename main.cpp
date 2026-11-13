#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <cctype>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

bool aturanTerpenuhi(const json& kondisi, const set<string>& fakta) {
    string mode = kondisi.at("mode").get<string>();
    vector<string> daftarFakta = kondisi.at("fakta").get<vector<string>>();

    if (mode == "AND") {
        // Semua fakta dalam aturan harus tersedia.
        for (const string& f : daftarFakta) {
            if (fakta.count(f) == 0) return false;
        }
        return true;
    }

    if (mode == "OR") {
        // Cukup satu fakta dalam aturan yang tersedia.
        for (const string& f : daftarFakta) {
            if (fakta.count(f) > 0) return true;
        }
        return false;
    }

    return false;
}

int main() {
    // 1. Membuka file JSON.
    ifstream file("aturan_ikan_cupang.json");

    if (!file.is_open()) {
        cerr << "Error: file aturan_ikan_cupang.json tidak ditemukan.\n";
        cerr << "Pastikan file JSON berada di folder yang sama dengan program.\n";
        return 1;
    }

    // 2. Membaca dan mengurai (parse) isi JSON.
    json basisPengetahuan;
    try {
        file >> basisPengetahuan;
    } catch (const json::parse_error& e) {
        cerr << "Error membaca format JSON: " << e.what() << '\n';
        return 1;
    }
    file.close();

    cout << "============================================\n";
    cout << basisPengetahuan.at("judul").get<string>() << '\n';
    cout << "Metode: "
         << basisPengetahuan.at("metode").get<string>() << '\n';
    cout << "============================================\n\n";
    cout << "Jawab pertanyaan dengan Y = Ya atau T = Tidak.\n\n";

    // 3. Mengumpulkan fakta awal dari jawaban pengguna.
    set<string> fakta;

    for (const auto& gejala : basisPengetahuan.at("gejala")) {
        string id = gejala.at("id").get<string>();
        string pertanyaan = gejala.at("pertanyaan").get<string>();
        char jawaban;

        while (true) {
            cout << pertanyaan << " (Y/T): ";
            cin >> jawaban;
            jawaban = static_cast<char>(
                toupper(static_cast<unsigned char>(jawaban))
            );

            if (jawaban == 'Y' || jawaban == 'T') break;
            cout << "Input tidak valid. Masukkan Y atau T.\n";
        }

        if (jawaban == 'Y') {
            fakta.insert(id);
        }
    }

    // 4. Proses Forward Chaining.
    // Fakta hasil aturan dimasukkan kembali ke memori fakta.
    // Aturan diperiksa berulang sampai tidak ada fakta baru.
    set<string> aturanSudahDipakai;
    vector<string> hasilKesimpulan;
    bool adaFaktaBaru = true;
    int putaran = 0;

    cout << "\n========== PROSES FORWARD CHAINING ==========\n";

    while (adaFaktaBaru) {
        adaFaktaBaru = false;
        putaran++;

        for (const auto& aturan : basisPengetahuan.at("aturan")) {
            string idAturan = aturan.at("id").get<string>();
            string faktaHasil = aturan.at("maka").at("fakta").get<string>();

            if (aturanSudahDipakai.count(idAturan) > 0) {
                continue;
            }

            if (aturanTerpenuhi(aturan.at("jika"), fakta)) {
                aturanSudahDipakai.insert(idAturan);

                // Simpan fakta baru agar dapat dipakai aturan berikutnya.
                bool faktaBaru = fakta.insert(faktaHasil).second;

                cout << "Putaran " << putaran << " - " << idAturan
                     << " terpenuhi.\n";
                cout << "Kesimpulan: "
                     << aturan.at("maka").at("kesimpulan").get<string>()
                     << '\n';
                cout << "Penjelasan: "
                     << aturan.at("penjelasan").get<string>() << "\n\n";

                hasilKesimpulan.push_back(
                    aturan.at("maka").at("kesimpulan").get<string>()
                );

                if (faktaBaru) {
                    adaFaktaBaru = true;
                }
            }
        }
    }

    // 5. Menampilkan hasil akhir.
    cout << "============== HASIL IDENTIFIKASI ==============\n";

    if (hasilKesimpulan.empty()) {
        cout << "Tidak ditemukan kesimpulan dari aturan yang tersedia.\n";
        cout << "Bukan berarti ikan pasti sehat. Periksa kembali gejala "
                "dan kualitas air.\n";
    } else {
        for (size_t i = 0; i < hasilKesimpulan.size(); ++i) {
            cout << i + 1 << ". " << hasilKesimpulan[i] << '\n';
        }
    }

    cout << "\nCatatan: "
         << basisPengetahuan.at("catatan").get<string>() << '\n';

    return 0;
}
