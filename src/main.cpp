#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// hase table
struct Akun {
    string username;
    string password;
};

// global varaibel
bool isAdmin = false;
string name;

void printDataAkun()
{
    cout << "Data akun" << endl;
    cout << "|index\t -username - password|"<<endl;

    Akun lihat;

    fstream file;

    // open file
    file.open("data/dataAkun.bin", ios::out | ios::in | ios::binary);

    while(!file.eof()) {
        // tampilkan data
        cout << "| " << lihat.username << " - " << lihat.password << " |" << endl;
        // baca file
        file.read(reinterpret_cast<char*>(&lihat), sizeof(Akun));
    }

    // close file
    file.close();

}

    //  view dafter
void viewDaftar() {
    Akun akun;
    
    fstream fileAkun;

    fileAkun.open("data/dataAkun.bin", ios::app | ios::out | ios::in | ios::binary);
    cout <<"\n== MENU DAFTAR ==" << endl;
    cout <<"Masukan username & password" <<endl;
    cout <<"Isi username \t : ";
    cin >> akun.username;
    cout <<"isi password \t : ";
    cin >> akun.password;

    fileAkun.write(reinterpret_cast<char*>(&akun),sizeof(Akun));

    cout << "Akun Berhasil daftar" << endl;

    fileAkun.close();
}

bool isLogin() {
    Akun akun;
    string username, password;
    fstream fileAkun;

    fileAkun.open("data/dataAkun.bin", ios::app | ios::out | ios::in | ios::binary);
    cout <<"\n== MENU LOGIN ==" << endl;
    cout <<"Masukan username & password" <<endl;
    cout <<"Username \t : ";
    cin >> username;
    cout <<"Password \t : ";
    cin >> password;

    // cek jika yang login adalah admin
    if(username == "admin" && password == "hamz123!") {
        fileAkun.close();
        cout << "Anda Login Sebagai Admin!" << endl;
        isAdmin = true;
        name = "admin";
        return true;
    }

    while(!fileAkun.eof()) {

        // cek jika username dan password sama dengan yang ada pada data bin
        if(akun.username == username && akun.password == password) {
            name = akun.username;

            // jika berhasil close file
            fileAkun.close();

            cout << "Login berhasil" << endl;
            return true;
        }
        // baca file
        fileAkun.read(reinterpret_cast<char*>(&akun), sizeof(Akun));
    }
    fileAkun.close();

    return false;
}

void viewDashboard() {
    cout << "Hallo " << name << " Selamat Datang" << endl;
    cout << "Anda Berhasil masuk ke dashboard" << endl;
}
    

int main()
{
    bool isBool = true;
    while (isBool){
        char pilihan;
        cout << "== PROGRAM LOGIN SEDERHANA ==" << endl;
        cout << "Menu Pilihan :" << endl;
        cout << "1. Daftar" << endl;
        cout << "2. login" << endl;
        cout << "3. Munculkan Data" << endl;
        cout << "4. keluar" << endl;
        cout << "Pilih Menu [1/2/3]:";
        cin >> pilihan;

        switch (pilihan) {
            case '1':
                system("cls");
                viewDaftar();
                break;
            case '2':
                system("cls");
                cout << "\n Anda Berada Pasa Menu Laogin " << endl;
                if (isLogin()){
                    system("cls");
                    viewDashboard();
                } else {
                    system("cls");
                    cout << "===================" << endl;
                    cout << "\tLogin Gagal" << endl;
                    cout << "===================" << endl;
                }
                break;
            case '3':
                system("cls");
                if(isAdmin) {
                    printDataAkun();
                } else {
                cout << "Menu tidak tersedia" << endl;
                }
                break;
            case '4':
                isBool = false;
                break;
            default:
                break;
        }
    }

    cin.get();

    return 0;
}