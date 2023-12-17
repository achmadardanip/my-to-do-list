#include<iostream>
#include<string>
#include<ctime>
#include<cstring>
#include<chrono>
#include<sstream>
#include<iomanip>
#include <cctype>
#include <algorithm>

using namespace std;
typedef struct ToDoLists
{
	int Id;
	string Tugas;
	string Status;
	string Prioritas;
	char Deadline[100];
	char Tanggal[100];
} todo;

void TambahToDo(todo[]);
void HapusToDo(todo[]);
void LihatToDo(todo[]);
void EditToDo(todo[]);
void CariToDo(todo[]);
string TanggalWaktuSekarang();
string ConvertToLowercase(string);

int urut = 0;

string Deadline, Tugas, Prioritas, Status, ulangi, ulangicari;

int main (void){
	todo ToDos[101];
	char menupilihan;

	while(menupilihan != '7'){
		cout << "************" << endl;
		cout << "(1) Tambah tugas" << endl;
		cout << "(2) Lihat tugas" << endl;
		cout << "(3) Edit tugas" << endl;
		cout << "(4) Hapus tugas" << endl;
		cout << "(5) Cari tugas" << endl;
		cout << "(6) Keluar" << endl;
		cout << "************" << endl;
		cout << "Silakan pilih menu: ";
		cin >> menupilihan;

		switch (menupilihan) {
			case '1':
				TambahToDo(ToDos);
				break;
			case '2':
				LihatToDo(ToDos);
				break;
			case '3':
				EditToDo(ToDos);
				break;
			case '4':
				HapusToDo(ToDos);
				break;
			case '5':
				CariToDo(ToDos);
				break;
			case '6':
				cout << "Anda telah keluar dari aplikasi";
				return 0;
			default:
				cout << "Menu yang dipilih salah";
		}
	}    
}

void TambahToDo(todo ToDos[]){

	if (urut > 100) {
		cout << "Maaf, tidak dapat menambahkan tugas baru karena memori penuh. Hapus salah satu tugas" << endl;
		return;
	}

	urut++;

	ToDos[urut-1].Id = urut++;

	cout << "Tugas: ";
	cin.ignore();
	getline(cin, ToDos[urut-1].Tugas);

	cout << "Prioritas (Low/Medium/High): ";
	getline(cin, ToDos[urut-1].Prioritas);

	cout << "Status (New/In Progress/Done): ";
	getline(cin, ToDos[urut-1].Status);

	cout << "Deadline (DD/MM/YYYY HH:MM): ";
	getline(cin, Deadline);

	tm DateTime = {};
	istringstream ss(Deadline);
	ss >> get_time(&DateTime, "%d/%m/%Y %H:%M");

	while (ss.fail()) {
		cout << "Ada kesalahan input tanggal. Silakan masukkan kembali deadline (DD/MM/YYYY HH:MM): ";
		getline(cin, Deadline);
		ss.clear();
		ss.str(Deadline);
		ss >> get_time(&DateTime, "%d/%m/%Y %H:%M");
	}

	time_t waktu = mktime(&DateTime);
	chrono::system_clock::time_point timePoint = chrono::system_clock::from_time_t(waktu);

	stringstream DeadlineFormatted;
	DeadlineFormatted << put_time(&DateTime, "%A, %d %B %Y - %H:%M");
	strcpy(ToDos[urut-1].Deadline, DeadlineFormatted.str().c_str());

	strcpy(ToDos[urut-1].Tanggal, TanggalWaktuSekarang().c_str());

	cout << "Tugas berhasil ditambahkan!"<< endl;

	cout << "Apakah Anda ingin menambah tugas baru lagi? Y/T: ";
	getline(cin, ulangi);

	if(ulangi == "Y" || ulangi == "y"){
	    TambahToDo(ToDos);
	} else if(ulangi == "T" || ulangi == "t"){
	    return;
	} else {
	    cout << "Input salah!" << endl;
		return;
	}
}

void LihatToDo (todo ToDos[]){
	cout << "*************************************************************************************************************************************************" << endl;
	cout << "*                                   					Daftar Tugas                                       		        *" << endl;
	cout << "*************************************************************************************************************************************************" << endl;
	cout << setw(5) << "ID" << setw(15) << "Tugas" << setw(15) << "Prioritas" << setw(15) << "Status" << setw(30) << "Deadline" << setw(30) << "Tanggal Diubah" << endl;
	cout << "--------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
	
	for(int i = 1; i < urut; i++){
		cout << setw(5) << ToDos[i].Id << setw(15) << ToDos[i].Tugas << setw(15) << ToDos[i].Prioritas << setw(15) << ToDos[i].Status << setw(40) << ToDos[i].Deadline << setw(40) << ToDos[i].Tanggal << endl;
	}
	cout << "--------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
}

void EditToDo(todo ToDos[]){
	int id;
	int pilihanedit;
	cout << "Masukkan ID pekerjaan yang ingin diedit: ";
	cin >> id;

	for(int i = 1; i < urut; i++){
		if(ToDos[i].Id == id){
			cout << "Apa yang ingin Anda edit?" << endl;
			cout << "************" << endl;
			cout << "(1) Edit tugas" << endl;
			cout << "(2) Edit prioritas" << endl;
			cout << "(3) Edit status" << endl;
			cout << "(4) Edit deadline" << endl;
			cout << "************" << endl;
			cout << "Silakan pilih: ";
			cin >> pilihanedit;

			while (pilihanedit < 1 || pilihanedit > 4) {
				cout << "Input salah! Silakan pilih kembali: ";
				cin >> pilihanedit;
			}

			if(pilihanedit == 1){
				cout << "Tugas: ";
				cin.ignore();
				getline(cin, ToDos[urut-1].Tugas);
			} else if(pilihanedit == 2){
				cout << "Prioritas (Low/Medium/High): ";
				cin.ignore();
				getline(cin, ToDos[urut-1].Prioritas);
			} else if(pilihanedit == 3){
				cout << "Status (New/In Progress/Done): ";
				cin.ignore();
				getline(cin, ToDos[urut-1].Status);
			} else if(pilihanedit == 4){
				cout << "Deadline (DD/MM/YYY HH:MM): ";
				getline(cin, Deadline);

				tm DateTime = {};
				istringstream ss(Deadline);
				ss >> get_time(&DateTime, "%d/%m/%Y %H:%M");

				while (ss.fail()) {
					cout << "Ada kesalahan input tanggal. Silakan masukkan kembali deadline (DD/MM/YYYY HH:MM): ";
					getline(cin, Deadline);
					ss.clear();
					ss.str(Deadline);
					ss >> get_time(&DateTime, "%d/%m/%Y %H:%M");
				}

				time_t waktu = mktime(&DateTime);
				chrono::system_clock::time_point timePoint = chrono::system_clock::from_time_t(waktu);

				stringstream DeadlineFormatted;
				DeadlineFormatted << put_time(&DateTime, "%A, %d %B %Y - %H:%M");
				strcpy(ToDos[urut-1].Deadline, DeadlineFormatted.str().c_str());
			} 

			strcpy(ToDos[i].Tanggal, TanggalWaktuSekarang().c_str());

			cout << "Tugas dengan ID " << id << " berhasil diedit!" << endl;

			cout << "Apakah Anda ingin mengedit tugas lagi? Y/T: ";
			getline(cin, ulangi);

			if(ulangi == "Y" || ulangi == "y"){
			    EditToDo(ToDos);
			} else if(ulangi == "T" || ulangi == "t"){
			    return;
			} else {
			    cout << "Input salah!" << endl;
				return;
			}
		} else {
			cout << "Tugas dengan ID " << id << " tidak ditemukan!" << endl;
			return;
		}
	}
}

void HapusToDo (todo ToDos[]){
	int id;
	cout << "Masukkan ID tugas yang ingin dihapus: ";
	cin >> id;

	for(int i = 1; i < urut; i++){
		if(ToDos[i].Id == id){
			string pilihanhapus;
			cout << "Apakah anda yakin ingin menghapus tugas ini? Y/T: ";
			cin.ignore();
			getline(cin, pilihanhapus);

			if(pilihanhapus == "Y" || pilihanhapus == "y"){
				for(int j = i; j < urut; j++){
					ToDos[j] = ToDos[j+1];
				}
				urut--;
				cout << "Tugas dengan ID " << id << " berhasil dihapus!" << endl;
			} else if(pilihanhapus == "T" || pilihanhapus == "t"){
				return;
			} else {
				cout << "Input salah!" << endl;
				return;
			}
		} else {
			cout << "Pekerjaan dengan ID " << id << " tidak ditemukan!" << endl;
		}
	}
}

void CariToDo (todo ToDos[]){
	int pilihanpencarian;

	cout << "Ingin mencari berdasarkan apa?" << endl;
	cout << "************" << endl;
	cout << "(1) Berdasarkan ID" << endl;
	cout << "(2) Berdasarkan nama tugas" << endl;
	cout << "(3) Berdasarkan prioritas" << endl;
	cout << "(4) Berdasarkan status" << endl;
	cout << "(5) Berdasarkan deadline" << endl;
	cout << "************" << endl;

	cout << "Masukkan pilihan pencarian: ";
	cin >> pilihanpencarian;

	if(pilihanpencarian == 1){
		int id;
		cout << "Masukkan ID tugas yang ingin dicari: ";
		cin >> id;

		for(int i = 1; i < urut; i++){
			if(ToDos[i].Id == id){
				cout << "Tugas dengan ID " << id << " ditemukan!" << endl;
				cout << "*************************************************************************************************************************************************" << endl;
				cout << "*                                   							Daftar Tugas                                       								  *" << endl;
				cout << "**************************************************************************************************************************************************" << endl;
				cout << setw(5) << "ID" << setw(15) << "Tugas" << setw(20) << "Prioritas" << setw(20) << "Status" << setw(30) << "Deadline" << setw(30) << "Tanggal Diubah" << endl;
				cout << "--------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
				cout << setw(5) << ToDos[i].Id << setw(15) << ToDos[i].Tugas << setw(20) << ToDos[i].Prioritas << setw(20) << ToDos[i].Status << setw(30) << ToDos[i].Deadline << setw(30) << ToDos[i].Tanggal << endl;
				cout << "--------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
				cout << "Apakah Anda ingin mencari lagi? Y/T: ";
				cin.ignore();
				getline(cin, ulangicari);
				if(ulangicari == "Y" || ulangicari == "y"){
				    CariToDo(ToDos);
				} else if(ulangicari == "T" || ulangicari == "t"){
				    return;
				} else {
				    cout << "Input salah!" << endl;
					return;
				}
			} else {
				cout << "Tugas dengan ID " << id << " tidak ditemukan!" << endl;
				return;
			}
		}
	} else if(pilihanpencarian == 2){
		cout << "Masukkan nama tugas yang ingin dicari: ";
		cin.ignore();
		getline(cin, Tugas);

		for(int i = 1; i < urut; i++){
			if (ConvertToLowercase(ToDos[i].Tugas) == ConvertToLowercase(Tugas)) {
				cout << "Tugas " << Tugas << " ditemukan!" << endl;
				cout << "*************************************************************************************************************************************************" << endl;
				cout << "*                                   							Daftar Tugas                                       								  *" << endl;
				cout << "**************************************************************************************************************************************************" << endl;
				cout << setw(5) << "ID" << setw(15) << "Tugas" << setw(15) << "Prioritas" << setw(15) << "Status" << setw(30) << "Deadline" << setw(30) << "Tanggal Diubah" << endl;
				cout << "--------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
				cout << setw(5) << ToDos[i].Id << setw(15) << ToDos[i].Tugas << setw(15) << ToDos[i].Prioritas << setw(15) << ToDos[i].Status << setw(40) << ToDos[i].Deadline << setw(40) << ToDos[i].Tanggal << endl;
				cout << "--------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
				cout << "Apakah Anda ingin mencari lagi? Y/T: ";
				cin.ignore();
				getline(cin, ulangicari);
				if(ulangicari == "Y" || ulangicari == "y"){
				    CariToDo(ToDos);
				} else if(ulangicari == "T" || ulangicari == "t"){
				    return;
				} else {
				    cout << "Input salah!" << endl;
					return;
				}
			} else {
				cout << "Tugas " << Tugas << " tidak ditemukan!" << endl;
				return;
			}
		}
	} else if(pilihanpencarian == 3){
		cout << "Masukkan prioritas tugas yang ingin dicari: ";
		cin.ignore();
		getline(cin, Prioritas);

		for(int i = 1; i < urut; i++){
			if (ConvertToLowercase(ToDos[i].Prioritas) == ConvertToLowercase(Prioritas)) {
				cout << "Tugas dengan prioritas " << Prioritas << " ditemukan!" << endl;
				cout << "*************************************************************************************************************************************************" << endl;
				cout << "*                                   							Daftar Tugas                                       								  *" << endl;
				cout << "**************************************************************************************************************************************************" << endl;
				cout << setw(5) << "ID" << setw(15) << "Tugas" << setw(15) << "Prioritas" << setw(15) << "Status" << setw(30) << "Deadline" << setw(30) << "Tanggal Diubah" << endl;
				cout << "--------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
				cout << setw(5) << ToDos[i].Id << setw(15) << ToDos[i].Tugas << setw(15) << ToDos[i].Prioritas << setw(15) << ToDos[i].Status << setw(40) << ToDos[i].Deadline << setw(40) << ToDos[i].Tanggal << endl;
				cout << "--------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
				cout << "Apakah Anda ingin mencari lagi? Y/T: ";
				cin.ignore();
				getline(cin, ulangicari);
				if(ulangicari == "Y" || ulangicari == "y"){
				    CariToDo(ToDos);
				} else if(ulangicari == "T" || ulangicari == "t"){
				    return;
				} else {
				    cout << "Input salah!" << endl;
					return;
				}
			} else {
				cout << "Tugas dengan prioritas " << Prioritas << " tidak ditemukan!" << endl;
				return;
			}
		}
	} else if(pilihanpencarian == 4){
		cout << "Masukkan status tugas yang ingin dicari: ";
		cin.ignore();
		getline(cin, Status);

		for(int i = 1; i < urut; i++){
			if (ConvertToLowercase(ToDos[i].Status) == ConvertToLowercase(Status)) {
				cout << "Tugas dengan status " << Status << " ditemukan!" << endl;
				cout << "*************************************************************************************************************************************************" << endl;
				cout << "*                                   							Daftar Tugas                                       								  *" << endl;
				cout << "**************************************************************************************************************************************************" << endl;
				cout << setw(5) << "ID" << setw(15) << "Tugas" << setw(15) << "Prioritas" << setw(15) << "Status" << setw(30) << "Deadline" << setw(30) << "Tanggal Diubah" << endl;
				cout << "--------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
				cout << setw(5) << ToDos[i].Id << setw(15) << ToDos[i].Tugas << setw(15) << ToDos[i].Prioritas << setw(15) << ToDos[i].Status << setw(40) << ToDos[i].Deadline << setw(40) << ToDos[i].Tanggal << endl;
				cout << "--------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
				cout << "Apakah Anda ingin mencari lagi? Y/T: ";
				cin.ignore();
				getline(cin, ulangicari);
				if(ulangicari == "Y" || ulangicari == "y"){
				    CariToDo(ToDos);
				} else if(ulangicari == "T" || ulangicari == "t"){
				    return;
				} else {
				    cout << "Input salah!" << endl;
					return;
				}
			} else {
				cout << "Tugas dengan status " << Status << " tidak ditemukan!" << endl;
				return;
			}
		}
	} else if(pilihanpencarian == 5){
		cout << "Masukkan deadline yang ingin dicari (DD/MM/YYYY HH:MM): ";
		cin.ignore();
		getline(cin, Deadline);

		tm DateTime = {};
		istringstream ss(Deadline);
		ss >> get_time(&DateTime, "%d/%m/%Y %H:%M");

		while (ss.fail()) {
			cout << "Ada kesalahan input tanggal. Silakan masukkan kembali deadline (DD/MM/YYYY HH:MM): ";
			getline(cin, Deadline);
			ss.clear();
			ss.str(Deadline);
			ss >> get_time(&DateTime, "%d/%m/%Y %H:%M");
		}

		time_t waktu = mktime(&DateTime);
		chrono::system_clock::time_point timePoint = chrono::system_clock::from_time_t(waktu);
		stringstream DeadlineFormatted;
		DeadlineFormatted << put_time(&DateTime, "%A, %d %B %Y - %H:%M");
		string LowercaseDeadline = ConvertToLowercase(DeadlineFormatted.str().c_str());

		for(int i = 1; i < urut; i++){
			if (ConvertToLowercase(ToDos[i].Deadline) == LowercaseDeadline) {
				cout << "Tugas dengan deadline " << LowercaseDeadline << " ditemukan!" << endl;
				cout << "*************************************************************************************************************************************************" << endl;
				cout << "*                                   							Daftar Tugas                                       								  *" << endl;
				cout << "**************************************************************************************************************************************************" << endl;
				cout << setw(5) << "ID" << setw(15) << "Tugas" << setw(15) << "Prioritas" << setw(15) << "Status" << setw(30) << "Deadline" << setw(30) << "Tanggal Diubah" << endl;
				cout << "--------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
				cout << setw(5) << ToDos[i].Id << setw(15) << ToDos[i].Tugas << setw(15) << ToDos[i].Prioritas << setw(15) << ToDos[i].Status << setw(40) << ToDos[i].Deadline << setw(40) << ToDos[i].Tanggal << endl;
				cout << "--------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
				cout << "Apakah Anda ingin mencari lagi? Y/T: ";
				cin.ignore();
				getline(cin, ulangicari);
				if(ulangicari == "Y" || ulangicari == "y"){
				    CariToDo(ToDos);
				} else if(ulangicari == "T" || ulangicari == "t"){
				    return;
				} else {
				    cout << "Input salah!" << endl;
					return;
				}
			} else {
				cout << "Tugas dengan deadline " << LowercaseDeadline << " tidak ditemukan!" << endl;
				return;
			}
		}
	} else {
		cout << "Input salah!" << endl;
		return;
	}
}

string TanggalWaktuSekarang(){
	time_t now = time(0);
	tm* localTime = localtime(&now);
	char formattedDateTime[100];
	strftime(formattedDateTime, sizeof(formattedDateTime), "%A, %d %B %Y - %H:%M", localTime);
	return formattedDateTime;
}

string ConvertToLowercase(string str) {
	transform(str.begin(), str.end(), str.begin(), ::tolower);
	return str;
}