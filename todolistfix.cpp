#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include<iostream>
#include<string>
#include<ctime>
#include <vector>
#include<cstring>
#include<chrono>
#include<sstream>
#include<iomanip>
#include <cctype>
#include <algorithm>

using namespace std;

struct Todo {
	int Id;
	string Tugas;
	string Status;
	string Prioritas;
	char Deadline[100];
	char Tanggal[100];
};

const int MAX_TASKS = 100;
Todo todos[MAX_TASKS];
int numTugas = 0;

int generateId() {
	static int Id = 0;
	return ++Id;
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

string Deadline, Tugas, Prioritas, Status, ulangi, ulangicari;

void TambahToDo() {
	if (numTugas >= MAX_TASKS) {
		cout << "Tidak dapat menambah tugas" << endl;
		return;
	}

	Todo todo;
	todo.Id = generateId();

	cout << "Masukkan nama tugas: ";
	cin.ignore();
	getline(cin, todo.Tugas);

	cout << "Masukkan prioritas tugas (Low/Medium/High): ";
	getline(cin, todo.Prioritas);

	cout << "Masukkan status tugas (New/In Progress/Done): ";
	getline(cin, todo.Status);

	cout << "Masukkan deadline tugas (DD/MM/YYYY HH:MM): ";
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

    strcpy(todo.Deadline, DeadlineFormatted.str().c_str());

    strcpy(todo.Tanggal, TanggalWaktuSekarang().c_str());

	todos[numTugas++] = todo;

	cout << "Task added successfully!" << endl;

	cout << "Apakah Anda ingin menambah tugas baru lagi? Y/T: ";
    getline(cin, ulangi);

	if(ulangi == "Y" || ulangi == "y"){
	    TambahToDo();
	} else if(ulangi == "T" || ulangi == "t"){
	    return;
	} else {
	    cout << "Input salah!" << endl;
		return;
	}
}

void HapusToDo(int id) {
	auto it = find_if(todos, todos + numTugas, [id](const Todo& todo) {
		return todo.Id == id;
	});

	string pilihanhapus;
	
	if (it != todos + numTugas) {
		cout << "Apakah anda yakin ingin menghapus tugas ini? Y/T: ";
		cin.ignore();
		getline(cin, pilihanhapus);

		if(pilihanhapus == "Y" || pilihanhapus == "y"){
			todos[it - todos] = todos[numTugas - 1];
			numTugas--;
			cout << "Tugas dengan ID " << id << " berhasil dihapus!" << endl;
		} else if(pilihanhapus == "T" || pilihanhapus == "t"){
			return;
		} else {
			return;
		}
	} else {
		cout << "Tugas dengan ID " << id << " tidak ditemukan!" << endl;
		return;
	}
}

void EditTugas(int id){
	int pilihanedit;

	auto it = find_if(todos, todos + numTugas, [id](const Todo& todo) {
		return todo.Id == id;
	});

	if(it != todos + numTugas){
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
			getline(cin, todos[it - todos].Tugas);
		} else if(pilihanedit == 2){
			cout << "Prioritas (Low/Medium/High): ";
			cin.ignore();
			getline(cin, todos[it - todos].Prioritas);
		} else if(pilihanedit == 3){
			cout << "Status (New/In Progress/Done): ";
			cin.ignore();
			getline(cin, todos[it - todos].Status);
		} else if(pilihanedit == 4){
			cout << "Deadline (DD/MM/YYY HH:MM): ";
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
			strcpy(todos[it-todos].Deadline, DeadlineFormatted.str().c_str());

		}

		strcpy(todos[it-todos].Tanggal, TanggalWaktuSekarang().c_str());

		cout << "Tugas dengan ID " << id << " berhasil diedit!" << endl;

		cout << "Apakah Anda ingin mengedit tugas lagi? Y/T: ";
		getline(cin, ulangi);

		if(ulangi == "Y" || ulangi == "y"){
			cout << "Masukkan ID tugas yang ingin diedit: ";
			cin >> id;
			EditTugas(id);
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

void LihatToDo() {
	cout << "*************************************************************************************************************************************************" << endl;
	cout << "*                                   							Task List                                       								  *" << endl;
	cout << "**************************************************************************************************************************************************" << endl;
	cout << setw(5) << "ID" << setw(15) << "Task" << setw(20) << "Priority" << setw(20) << "Status" << setw(30) << "Deadline" << setw(30) << "Date Modified" << endl;
	cout << "--------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < numTugas; i++) {
		const Todo& todo = todos[i];
		cout << setw(5) << todo.Id << setw(15) << todo.Tugas << setw(20) << todo.Prioritas << setw(20) << todo.Status << setw(30) << todo.Deadline << setw(30) << todo.Tanggal <<endl;
	}
	cout << "--------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
}

void CariToDo(){
	int pilihanpencarian;

	cout << "Ingin mencari berdasarkan apa?" << endl;
	cout << "************" << endl;
	cout << "(1) Pencarian Berdasarkan ID" << endl;
	cout << "(2) Pencarian Berdasarkan nama tugas" << endl;
	cout << "(3) Pencarian Berdasarkan prioritas" << endl;
	cout << "(4) Pencarian Berdasarkan status" << endl;
	cout << "(5) Pencarian Berdasarkan deadline" << endl;
	cout << "************" << endl;

	cout << "Masukkan pilihan pencarian: ";
	cin >> pilihanpencarian;

	if(pilihanpencarian == 1){
		int id;
		cout << "Masukkan ID tugas yang ingin dicari: ";
		cin >> id;

		auto it = find_if(todos, todos + numTugas, [id](const Todo& todo) {
			return todo.Id == id;
		});
			if(it != todos + numTugas){
				cout << "*************************************************************************************************************************************************" << endl;
				cout << "*                                   							Task List                                       								  *" << endl;
				cout << "**************************************************************************************************************************************************" << endl;
				cout << setw(5) << "ID" << setw(15) << "Task" << setw(20) << "Priority" << setw(20) << "Status" << setw(30) << "Deadline" << setw(30) << "Date Modified" << endl;
				cout << "--------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
				for (int i = 0; i < numTugas; i++) {
					const Todo& todo = todos[it - todos];
					cout << setw(5) << todo.Id << setw(15) << todo.Tugas << setw(20) << todo.Prioritas << setw(20) << todo.Status << setw(30) << todo.Deadline << setw(30) << todo.Tanggal <<endl;
				}
				cout << "--------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
			} else {
				cout << "Tugas dengan ID " << id << " tidak ditemukan!" << endl;
				return;
			}
	} else if(pilihanpencarian == 2){
		cout << "Masukkan nama tugas yang ingin dicari: ";
		cin.ignore();
		getline(cin, Tugas);

		for (int i = 0; i < numTugas; i++) {
			if (ConvertToLowercase(todos[i].Tugas) == ConvertToLowercase(Tugas)) {
				cout << "Tugas dengan nama " << Tugas << " ditemukan!" << endl;
				cout << "*************************************************************************************************************************************************" << endl;
				cout << "*                                   							Daftar Tugas                                       								  *" << endl;
				cout << "**************************************************************************************************************************************************" << endl;
				cout << setw(5) << "ID" << setw(15) << "Tugas" << setw(15) << "Prioritas" << setw(15) << "Status" << setw(30) << "Deadline" << setw(30) << "Tanggal Diubah" << endl;
				cout << "--------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
				for (int j = 0; j < numTugas; j++) {
					if (ConvertToLowercase(todos[j].Tugas) == ConvertToLowercase(Tugas)) {
						cout << setw(5) << todos[j].Id << setw(15) << todos[j].Tugas << setw(15) << todos[j].Prioritas << setw(15) << todos[j].Status << setw(40) << todos[j].Deadline << setw(40) << todos[j].Tanggal << endl;
					}
				}
				cout << "--------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

				cout << "Apakah Anda ingin mencari lagi? Y/T: ";
				getline(cin, ulangicari);

				if (ulangicari == "Y" || ulangicari == "y") {
					CariToDo();
				} else if (ulangicari == "T" || ulangicari == "t") {
					return;
				} else {
					cout << "Input salah!" << endl;
					return;
				}
			} else {
				cout << "Tugas dengan nama " << Tugas << " tidak ditemukan!" << endl;
				return;
			}
		}
	} else if(pilihanpencarian == 3){
		cout << "Masukkan prioritas tugas yang ingin dicari: ";
		cin.ignore();
		getline(cin, Prioritas);

		for (int i = 0; i < numTugas; i++) {
			cout << ConvertToLowercase(todos[i].Prioritas);
			if (ConvertToLowercase(todos[i].Prioritas) == ConvertToLowercase(Prioritas)) {
				cout << "Tugas dengan prioritas " << Prioritas << " ditemukan!" << endl;
				cout << "*************************************************************************************************************************************************" << endl;
				cout << "*                                   							Daftar Tugas                                       								  *" << endl;
				cout << "**************************************************************************************************************************************************" << endl;
				cout << setw(5) << "ID" << setw(15) << "Tugas" << setw(15) << "Prioritas" << setw(15) << "Status" << setw(30) << "Deadline" << setw(30) << "Tanggal Diubah" << endl;
				cout << "--------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
				// for (int j = 0; j < numTugas; j++) {
					// if (ConvertToLowercase(todos[j].Prioritas) == ConvertToLowercase(Prioritas)) {
						cout << setw(5) << todos[i].Id << setw(15) << todos[i].Tugas << setw(15) << todos[i].Prioritas << setw(15) << todos[i].Status << setw(40) << todos[i].Deadline << setw(40) << todos[i].Tanggal << endl;
					//}
				//}
				cout << "--------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
				
				cout << "Apakah Anda ingin mencari lagi? Y/T: ";
				getline(cin, ulangicari);
				
				if (ulangicari == "Y" || ulangicari == "y") {
					CariToDo();
				} else if (ulangicari == "T" || ulangicari == "t") {
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

		for (int i = 0; i < numTugas; i++) {
			if (ConvertToLowercase(todos[i].Status) == ConvertToLowercase(Status)) {
				cout << "Tugas dengan status " << Status << " ditemukan!" << endl;
				cout << "*************************************************************************************************************************************************" << endl;
				cout << "*                                   							Daftar Tugas                                       								  *" << endl;
				cout << "**************************************************************************************************************************************************" << endl;
				cout << setw(5) << "ID" << setw(15) << "Tugas" << setw(15) << "Prioritas" << setw(15) << "Status" << setw(30) << "Deadline" << setw(30) << "Tanggal Diubah" << endl;
				cout << "--------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
				for (int j = i; j < numTugas; j++) {
					if (ConvertToLowercase(todos[j].Status) == ConvertToLowercase(Status)) {
						cout << setw(5) << todos[j].Id << setw(15) << todos[j].Tugas << setw(15) << todos[j].Prioritas << setw(15) << todos[j].Status << setw(40) << todos[j].Deadline << setw(40) << todos[j].Tanggal << endl;
					}
				}
				cout << "--------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
				cout << "Apakah Anda ingin mencari lagi? Y/T: ";
				getline(cin, ulangicari);
				if (ulangicari == "Y" || ulangicari == "y") {
					CariToDo();
				} else if (ulangicari == "T" || ulangicari == "t") {
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

		for (int i = 0; i < numTugas; i++) {
			if (ConvertToLowercase(todos[i].Deadline) == LowercaseDeadline) {
				cout << "Tugas dengan deadline " << DeadlineFormatted.str().c_str() << " ditemukan!" << endl;
				cout << "*************************************************************************************************************************************************" << endl;
				cout << "*                                   							Daftar Tugas                                       								  *" << endl;
				cout << "**************************************************************************************************************************************************" << endl;
				cout << setw(5) << "ID" << setw(15) << "Tugas" << setw(15) << "Prioritas" << setw(15) << "Status" << setw(30) << "Deadline" << setw(30) << "Tanggal Diubah" << endl;
				cout << "--------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
				for (int j = i; j < numTugas; j++) {
					if (ConvertToLowercase(todos[j].Deadline) == LowercaseDeadline) {
						cout << setw(5) << todos[j].Id << setw(15) << todos[j].Tugas << setw(15) << todos[j].Prioritas << setw(15) << todos[j].Status << setw(40) << todos[j].Deadline << setw(40) << todos[j].Tanggal << endl;
					}
				}
				cout << "--------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
				cout << "Apakah Anda ingin mencari lagi? Y/T: ";
				getline(cin, ulangicari);
				if (ulangicari == "Y" || ulangicari == "y") {
					CariToDo();
				} else if (ulangicari == "T" || ulangicari == "t") {
					return;
				} else {
					cout << "Input salah!" << endl;
					return;
				}
			} else {
				cout << "Tugas dengan deadline " <<  DeadlineFormatted.str().c_str() << " tidak ditemukan!" << endl;
				return;
			}
		}
	} else {
		cout << "Input salah!" << endl;
		return;
	}
}

int main() {
	int pilihan, id;
	do {
		cout << "(1) Tambah Tugas" << endl;
		cout << "(2) Lihat Tugas" << endl;
		cout << "(3) Edit Tugas" << endl;
		cout << "(4) Hapus Tugas" << endl;
		cout << "(5) Cari Tugas" << endl;
		cout << "(6) Keluar" << endl;
		cout << "Enter your choice: ";
		cin >> pilihan;
		switch (pilihan) {
			case 1:
				TambahToDo();
				break;
			case 2:
				LihatToDo();
				break;
			case 3:
				cout << "Masukkan ID tugas yang ingin diedit: ";
				cin >> id;
				EditTugas(id);
				break;
			case 4:
				cout << "Masukkan ID tugas yang ingin dihapus: ";
				cin >> id;
				HapusToDo(id);
				break;
			case 5:
				CariToDo();
				break;
			case '6':
				cout << "Anda telah keluar dari aplikasi";
				return 0;
			default:
				cout << "Invalid choice! Please try again." << endl;
				break;
		}
		cout << endl;
	} while (pilihan != 4);
	return 0;
}