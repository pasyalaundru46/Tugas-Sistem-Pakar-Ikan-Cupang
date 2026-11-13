#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
using namespace std;

struct Aturan {
    string id;
    vector<string> syarat;
    string mode; 
    string maka;
    string sumber;
};

struct BasisPengetahuan {
    string judul;
    string batas;
    vector<Aturan> aturanList;
};

struct JejakAturan {
    string idAturan;
    string hasil;
    vector<string> syaratTerpenuhi;
};

int main() {

    BasisPengetahuan kb;
    kb.judul = "Diagnosis Masalah Kesehatan Ikan Cupang";
    kb.batas = "Aturan berasal dari literatur akuakultur dan perawatan ikan hias universitas. Hasilnya adalah saran awal, bukan diagnosis dokter hewan profesional.";

    kb.aturanList = {
        {"R1", {"sirip robek atau koyak", "tepi sirip menghitam"}, "atau", "indikasi infeksi bakteri", "S1: Betta Fish Disease Guide, University of Florida IFAS Extension"},
        {"R2", {"indikasi infeksi bakteri", "suhu air terlalu dingin atau kotor"}, "dan", "sirip busuk (fin rot)", "S1: Betta Fish Disease Guide, University of Florida IFAS Extension"},
        {"R3", {"tubuh membengkak seperti buah pinus", "sisik berdiri"}, "dan", "penyakit dropsy", "S2: Ornamental Fish Health Management, Journal of Aquatic Animal Health"},
        {"R4", {"muncul bintik putih seperti garam di tubuh", "ikan sering gesekan badan ke dekorasi"}, "dan", "penyakit ich (white spot)", "S1: Betta Fish Disease Guide, University of Florida IFAS Extension"},
        {"R5", {"ikan pasif di dasar aquarium", "warna tubuh memudar"}, "atau", "stres lingkungan", "S2: Ornamental Fish Health Management, Journal of Aquatic Animal Health"}
    };

    cout << "=== " << kb.judul << " ===" << endl << endl;

    set<string> semuaSyarat;
    set<string> semuaHasil;

    for (const auto& aturan : kb.aturanList) {
        for (const auto& s : aturan.syarat) {
            semuaSyarat.insert(s);
        }
        semuaHasil.insert(aturan.maka);
    }

    vector<string> daftarPertanyaan;
    for (const auto& syarat : semuaSyarat) {
        if (semuaHasil.find(syarat) == semuaHasil.end()) {
            daftarPertanyaan.push_back(syarat);
        }
    }
    set<string> memoriFakta;
    vector<string> faktaAwal;
    cout << "Jawab pertanyaan berikut dengan 'y' (ya) atau 't' (tidak):\n";
    for (size_t i = 0; i < daftarPertanyaan.size(); ++i) {
        char jawab;
        cout << (i + 1) << ". Apakah " << daftarPertanyaan[i] << "? (y/t) > ";
        cin >> jawab;
        if (jawab == 'y' || jawab == 'Y') {
            memoriFakta.insert(daftarPertanyaan[i]);
            faktaAwal.push_back(daftarPertanyaan[i]);
        }
    }

    // Tampilkan fakta awal yang diketahui
    cout << "\nFakta awal yang diketahui: ";
    if (faktaAwal.empty()) {
        cout << "Tidak ada fakta yang dipilih.";
    } else {
        for (size_t i = 0; i < faktaAwal.size(); ++i) {
            cout << faktaAwal[i] << (i + 1 < faktaAwal.size() ? ", " : "");
        }
    }
    cout << "\n\n--- Proses Forward Chaining ---\n";
    vector<JejakAturan> jejakPencapaian;
    set<string> aturanDijalankan;
    int siklus = 1;

    while (true) {
        bool adaAturanBaru = false;
        string aturanDipilih = "";
        Aturan aturanObjek;

        for (const auto& aturan : kb.aturanList) {
            string id = aturan.id;
            string hasil = aturan.maka;

            
            if (aturanDijalankan.find(id) == aturanDijalankan.end() && memoriFakta.find(hasil) == memoriFakta.end()) {
                bool syaratTerpenuhi = false;

                if (aturan.mode == "dan") {
                    bool semuaAda = true;
                    for (const auto& s : aturan.syarat) {
                        if (memoriFakta.find(s) == memoriFakta.end()) {
                            semuaAda = false;
                            break;
                        }
                    }
                    syaratTerpenuhi = semuaAda;
                } else if (aturan.mode == "atau") {
                    bool adaSatu = false;
                    for (const auto& s : aturan.syarat) {
                        if (memoriFakta.find(s) != memoriFakta.end()) {
                            adaSatu = true;
                            break;
                        }
                    }
                    syaratTerpenuhi = adaSatu;
                }

                if (syaratTerpenuhi) {
                    aturanDipilih = id;
                    aturanObjek = aturan;
                    break;
                }
            }
        }

        if (!aturanDipilih.empty()) {
            string hasilBaru = aturanObjek.maka;
            memoriFakta.insert(hasilBaru);
            aturanDijalankan.insert(aturanDipilih);

            jejakPencapaian.push_back({aturanDipilih, hasilBaru, aturanObjek.syarat});
            cout << "Siklus " << siklus << ": " << aturanDipilih << " -> " << hasilBaru << endl;

            adaAturanBaru = true;
            siklus++;
        }

        if (!adaAturanBaru) {
            cout << "Siklus " << siklus << ": tidak ada aturan baru, berhenti\n" << endl;
            break;
        }
    }

    
    cout << "=== KESIMPULAN ===" << endl;
    vector<string> kesimpulanAkhir;
    for (const auto& hasil : semuaHasil) {
        if (memoriFakta.find(hasil) != memoriFakta.end() && find(faktaAwal.begin(), faktaAwal.end(), hasil) == faktaAwal.end()) {
            kesimpulanAkhir.push_back(hasil);
        }
    }

    if (kesimpulanAkhir.empty()) {
        cout << "Tidak ada kesimpulan (penyakit/masalah) yang dapat disimpulkan berdasarkan gejala tersebut." << endl;
    } else {
        cout << "Ditemukan kesimpulan:\n";
        for (const auto& k : kesimpulanAkhir) {
            cout << "- " << k << endl;
        }

        cout << "\nAlasan (Jejak Rantai):\n";
        for (const auto& jejak : jejakPencapaian) {
            cout << "  " << jejak.hasil << " <- " << jejak.idAturan << " (";
            for (size_t i = 0; i < jejak.syaratTerpenuhi.size(); ++i) {
                cout << jejak.syaratTerpenuhi[i] << (i + 1 < jejak.syaratTerpenuhi.size() ? ", " : "");
            }
            cout << ")\n";
        }
    }

    return 0;
}