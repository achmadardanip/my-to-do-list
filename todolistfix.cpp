#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstring>
#include <chrono>
#include <sstream>
#include <iomanip>

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
		cout << "Tidak dapat menambah tugas sudah mencapai limit 100 tugas. Silakan hapus salah satu tugas lalu tambah lagi!" << endl;
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
	// chrono::system_clock::time_point timePoint = chrono::system_clock::from_time_t(waktu);

	stringstream DeadlineFormatted;
	DeadlineFormatted << put_time(&DateTime, "%A, %d %B %Y - %H:%M");

    strcpy(todo.Deadline, DeadlineFormatted.str().c_str());

    strcpy(todo.Tanggal, TanggalWaktuSekarang().c_str());

	todos[numTugas++] = todo;

	cout << "Tugas berhasil ditambahkan!" << endl;

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
		} 
		else if(pilihanhapus == "T" || pilihanhapus == "t"){
			return ;
		}
		else {
			return ;
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
		cout << "______________________________" << endl;
		cout << "|| Apa yang ingin Anda edit? ||"<< endl;
		cout << "||___________________________||" << endl;
		cout << "|| (1) Edit tugas            ||"<< endl;
		cout << "|| (2) Edit prioritas        ||" << endl;
		cout << "|| (3) Edit status           ||" << endl;
		cout << "|| (4) Edit deadline         ||" << endl;
		cout << "||___________________________||" << endl;


		do {
		    cout << "Silakan pilih: ";
		    cin >> pilihanedit;
		    if (cin.fail()) {
		        cout << "Input salah. Harap masukkan angka!" << endl;
		        cin.clear();
		        cin.ignore(numeric_limits<streamsize>::max(), '\n');
		    } else {
		        break;
		    }
		} while (true);

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
			// chrono::system_clock::time_point timePoint = chrono::system_clock::from_time_t(waktu);

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
	cout << "____________________________________________________________________________________________________________________________________________________________________________________" << endl;
	cout << "||                                                                          Daftar Tugas                               					                          ||" << endl;
	cout << "||________________________________________________________________________________________________________________________________________________________________________________||" << endl;
	cout << "||";
	cout << setw(8) <<left << "   ID";
	cout << "||" << setw(15) << "     Tugas" <<left;
	cout << "||" << setw(20) << "      Prioritas"<<left;
	cout << "||" << setw(14) << "    Status" <<left;
	cout << "||" << setw(40) << "               Deadline" <<left;
	cout << "||" << setw(27) << "        Sisa Waktu" <<left;
	cout << "||" << setw(40) << "            Tanggal Ubah" <<left;
	cout << "||" <<endl;
	cout << "||________||_______________||____________________||______________||________________________________________||___________________________||________________________________________||" << endl;

	for (int i = 0; i < numTugas; i++) {
		const Todo& todo = todos[i];

		time_t WaktuSekarang = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

		tm WaktuDeadline = {};
		istringstream deadlineStream(todo.Deadline);
		deadlineStream >> std::get_time(&WaktuDeadline, "%A, %d %B %Y - %H:%M");

		time_t deadline = std::mktime(&WaktuDeadline);

		time_t SisaDetik = deadline - WaktuSekarang;

		int SisaHari = SisaDetik / (60 * 60 * 24);

		int SisaJam = SisaDetik / (60 * 60);

		int SisaMenit = SisaDetik / 60;

		string sisawaktu;

		if (SisaHari == 0) {
			int jam = SisaMenit / 60;
			int menit = SisaMenit % 60;

			if (SisaJam == 0) {
				if(menit < 0){
					sisawaktu = to_string(abs(menit)) + " menit terlewati";
				} else {
					sisawaktu = to_string(menit) + " menit";
				}
			} else {
				if(jam < 0 && menit < 0 ){
					sisawaktu = to_string(abs(jam)) + " jam " + to_string(abs(menit)) + " menit terlewati";
				} else {
					sisawaktu = to_string(jam) + " jam " + to_string(menit) + " menit";
				}
			}
			cout << "||";
			cout << setw(8) <<left << todo.Id;
			cout << "||" << setw(15) << todo.Tugas <<left;
			cout << "||" << setw(20) << todo.Prioritas <<left;
			cout << "||" << setw(14) << todo.Status <<left;
			cout << "||" << setw(40) << todo.Deadline <<left;
			cout << "||" << setw(27) << sisawaktu <<left;
			cout << "||" << setw(40) << todo.Tanggal <<left;
			cout << "||" <<endl;
		} else if (SisaHari > 0) {
			SisaHari = SisaMenit / (60 * 24);
			SisaJam = (SisaMenit % (60 * 24)) / 60;
			SisaMenit = (SisaMenit % (60 * 24)) % 60;

			sisawaktu = to_string(SisaHari) + " hari " + to_string(SisaJam) + " jam " + to_string(SisaMenit) + " menit";
			cout << "||";
			cout << setw(8) <<left << todo.Id;
			cout << "||" << setw(15) << todo.Tugas <<left;
			cout << "||" << setw(20) << todo.Prioritas <<left;
			cout << "||" << setw(14) << todo.Status <<left;
			cout << "||" << setw(40) << todo.Deadline <<left;
			cout << "||" << setw(27) << sisawaktu <<left;
			cout << "||" << setw(40) << todo.Tanggal <<left;
			cout << "||" <<endl;
		
		} else {
			sisawaktu = to_string(abs(SisaHari)) + " hari terlewati";
			cout << "||";
			cout << setw(8) <<left << todo.Id;
			cout << "||" << setw(15) << todo.Tugas <<left;
			cout << "||" << setw(20) << todo.Prioritas <<left;
			cout << "||" << setw(14) << todo.Status <<left;
			cout << "||" << setw(40) << todo.Deadline <<left;
			cout << "||" << setw(27) << sisawaktu <<left;
			cout << "||" << setw(40) << todo.Tanggal <<left;
			cout << "||" <<endl;
		}
	}
	cout << "||________||_______________||____________________||______________||________________________________________||___________________________||________________________________________||" << endl;
}

void CariToDo(){
	int pilihanpencarian;

	cout << "___________________________________________" << endl;
	cout << "||    Ingin mencari berdasarkan apa?     ||" << endl;
	cout << "||_______________________________________||" << endl;
	cout << "|| (1) Pencarian Berdasarkan ID          ||" << endl;
	cout << "|| (2) Pencarian Berdasarkan nama tugas  ||" << endl;
	cout << "|| (3) Pencarian Berdasarkan prioritas   ||" << endl;
	cout << "|| (4) Pencarian Berdasarkan status      ||" << endl;
	cout << "|| (5) Pencarian Berdasarkan deadline    ||" << endl;
	cout << "||_______________________________________||" << endl;

	do {
	    cout << " Masukkan pilihan pencarian: ";
	    cin >> pilihanpencarian;
	    if (cin.fail()) {
	        cout << " Input salah. Harap masukkan angka!" << endl;
	        cin.clear();
	        cin.ignore(numeric_limits<streamsize>::max(), '\n');
	    } else {
			break;
	    }
	} while (true);

	if(pilihanpencarian == 1){
		int id;		
		do {
		    cout << " Masukkan ID tugas yang ingin dicari: ";
		    cin >> id;
		    if (cin.fail()) {
		        cout << " Input salah. Harap masukkan angka!" << endl;
		        cin.clear();
		        cin.ignore(numeric_limits<streamsize>::max(), '\n');
		    } else {
				break;
		    }
		} while (true);

		vector<const Todo*> mencocokkanTodos;

		auto it = find_if(todos, todos + numTugas, [id](const Todo& todo) {
			return todo.Id == id;
		});

		while (it != todos + numTugas) {
			mencocokkanTodos.push_back(&(*it));
			it = find_if(it + 1, todos + numTugas, [id](const Todo& todo) {
				return todo.Id == id;
			});
		}

		if (!mencocokkanTodos.empty()) {
			cout << "____________________________________________________________________________________________________________________________________________________________________________________" << endl;
			cout << "||                                                                          Daftar Tugas                               					                          ||" << endl;
			cout << "||________________________________________________________________________________________________________________________________________________________________________________||" << endl;
			cout << "||";
			cout << setw(8) <<left << "   ID";
			cout << "||" << setw(15) << "     Tugas" <<left;
			cout << "||" << setw(20) << "      Prioritas"<<left;
			cout << "||" << setw(14) << "    Status" <<left;
			cout << "||" << setw(40) << "               Deadline" <<left;
			cout << "||" << setw(27) << "        Sisa Waktu" <<left;
			cout << "||" << setw(40) << "            Tanggal Ubah" <<left;
			cout << "||" <<endl;
			cout << "||________||_______________||____________________||______________||________________________________________||___________________________||________________________________________||" << endl;

			for (const Todo* todo : mencocokkanTodos) {

				time_t WaktuSekarang = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

				tm WaktuDeadline = {};
				istringstream deadlineStream(todo->Deadline);
				deadlineStream >> std::get_time(&WaktuDeadline, "%A, %d %B %Y - %H:%M");

				time_t deadline = std::mktime(&WaktuDeadline);

				time_t SisaDetik = deadline - WaktuSekarang;

				int SisaHari = SisaDetik / (60 * 60 * 24);

				int SisaJam = SisaDetik / (60 * 60);

				int SisaMenit = SisaDetik / 60;

				string sisawaktu;

				if (SisaHari == 0) {
					int jam = SisaMenit / 60;
					int menit = SisaMenit % 60;

					if (SisaJam == 0) {
						if(menit < 0){
							sisawaktu = to_string(abs(menit)) + " menit terlewati";
						} else {
							sisawaktu = to_string(menit) + " menit";
						}
					} else {
						if(jam < 0 && menit < 0 ){
							sisawaktu = to_string(abs(jam)) + " jam " + to_string(abs(menit)) + " menit terlewati";
						} else {
							sisawaktu = to_string(jam) + " jam " + to_string(menit) + " menit";
						}
					}
					cout << "||";
					cout << setw(8) <<left << todo->Id;
					cout << "||" << setw(15) << todo->Tugas <<left;
					cout << "||" << setw(20) << todo->Prioritas <<left;
					cout << "||" << setw(14) << todo->Status <<left;
					cout << "||" << setw(40) << todo->Deadline <<left;
					cout << "||" << setw(27) << sisawaktu <<left;
					cout << "||" << setw(40) << todo->Tanggal <<left;
					cout << "||" <<endl;
				} else if (SisaHari > 0) {
					SisaHari = SisaMenit / (60 * 24);
					SisaJam = (SisaMenit % (60 * 24)) / 60;
					SisaMenit = (SisaMenit % (60 * 24)) % 60;

					sisawaktu = to_string(SisaHari) + " hari " + to_string(SisaJam) + " jam " + to_string(SisaMenit) + " menit";
					cout << "||";
					cout << setw(8) <<left << todo->Id;
					cout << "||" << setw(15) << todo->Tugas <<left;
					cout << "||" << setw(20) << todo->Prioritas <<left;
					cout << "||" << setw(14) << todo->Status <<left;
					cout << "||" << setw(40) << todo->Deadline <<left;
					cout << "||" << setw(27) << sisawaktu <<left;
					cout << "||" << setw(40) << todo->Tanggal <<left;
					cout << "||" <<endl;
				} else {
					sisawaktu = to_string(abs(SisaHari)) + " hari terlewati";
					cout << "||";
					cout << setw(8) <<left << todo->Id;
					cout << "||" << setw(15) << todo->Tugas <<left;
					cout << "||" << setw(20) << todo->Prioritas <<left;
					cout << "||" << setw(14) << todo->Status <<left;
					cout << "||" << setw(40) << todo->Deadline <<left;
					cout << "||" << setw(27) << sisawaktu <<left;
					cout << "||" << setw(40) << todo->Tanggal <<left;
					cout << "||" <<endl;
				}
			}
			cout << "||________||_______________||____________________||______________||________________________________________||___________________________||________________________________________||" << endl;
		} else {
			cout << " Tugas dengan ID " << id << " tidak ditemukan!" << endl;
			return;
		}
	} else if(pilihanpencarian == 2){
		cout << " Masukkan nama tugas yang ingin dicari: ";
		cin.ignore();
		getline(cin, Tugas);

		vector<const Todo*> mencocokkanTodos;

		auto it = find_if(todos, todos + numTugas, [=](const Todo& todo) {
			return ConvertToLowercase(todo.Tugas) == ConvertToLowercase(Tugas);
		});

		while (it != todos + numTugas) {
			mencocokkanTodos.push_back(&(*it));
			it = find_if(it + 1, todos + numTugas, [=](const Todo& todo) {
				return ConvertToLowercase(todo.Tugas) == ConvertToLowercase(Tugas);
			});
		}

		if (!mencocokkanTodos.empty()) {
			cout << "____________________________________________________________________________________________________________________________________________________________________________________" << endl;
			cout << "||                                                                          Daftar Tugas                               					                          ||" << endl;
			cout << "||________________________________________________________________________________________________________________________________________________________________________________||" << endl;
			cout << "||";
			cout << setw(8) <<left << "   ID";
			cout << "||" << setw(15) << "     Tugas" <<left;
			cout << "||" << setw(20) << "      Prioritas"<<left;
			cout << "||" << setw(14) << "    Status" <<left;
			cout << "||" << setw(40) << "               Deadline" <<left;
			cout << "||" << setw(27) << "        Sisa Waktu" <<left;
			cout << "||" << setw(40) << "            Tanggal Ubah" <<left;
			cout << "||" <<endl;
			cout << "||________||_______________||____________________||______________||________________________________________||___________________________||________________________________________||" << endl;

			for (const Todo* todo : mencocokkanTodos) {
				time_t WaktuSekarang = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

				tm WaktuDeadline = {};
				istringstream deadlineStream(todo->Deadline);
				deadlineStream >> std::get_time(&WaktuDeadline, "%A, %d %B %Y - %H:%M");

				time_t deadline = std::mktime(&WaktuDeadline);

				time_t SisaDetik = deadline - WaktuSekarang;

				int SisaHari = SisaDetik / (60 * 60 * 24);

				int SisaJam = SisaDetik / (60 * 60);

				int SisaMenit = SisaDetik / 60;

				string sisawaktu;

				if (SisaHari == 0) {
					int jam = SisaMenit / 60;
					int menit = SisaMenit % 60;

					if (SisaJam == 0) {
						if(menit < 0){
							sisawaktu = to_string(abs(menit)) + " menit terlewati";
						} else {
							sisawaktu = to_string(menit) + " menit";
						}
					} else {
						if(jam < 0 && menit < 0 ){
							sisawaktu = to_string(abs(jam)) + " jam " + to_string(abs(menit)) + " menit terlewati";
						} else {
							sisawaktu = to_string(jam) + " jam " + to_string(menit) + " menit";
						}
					}
					cout << "||";
					cout << setw(8) <<left << todo->Id;
					cout << "||" << setw(15) << todo->Tugas <<left;
					cout << "||" << setw(20) << todo->Prioritas <<left;
					cout << "||" << setw(14) << todo->Status <<left;
					cout << "||" << setw(40) << todo->Deadline <<left;
					cout << "||" << setw(27) << sisawaktu <<left;
					cout << "||" << setw(40) << todo->Tanggal <<left;
					cout << "||" <<endl;
				} else if (SisaHari > 0) {
					SisaHari = SisaMenit / (60 * 24);
					SisaJam = (SisaMenit % (60 * 24)) / 60;
					SisaMenit = (SisaMenit % (60 * 24)) % 60;

					sisawaktu = to_string(SisaHari) + " hari " + to_string(SisaJam) + " jam " + to_string(SisaMenit) + " menit";
					sisawaktu = to_string(abs(SisaHari)) + " hari terlewati";
					cout << "||";
					cout << setw(8) <<left << todo->Id;
					cout << "||" << setw(15) << todo->Tugas <<left;
					cout << "||" << setw(20) << todo->Prioritas <<left;
					cout << "||" << setw(14) << todo->Status <<left;
					cout << "||" << setw(40) << todo->Deadline <<left;
					cout << "||" << setw(27) << sisawaktu <<left;
					cout << "||" << setw(40) << todo->Tanggal <<left;
					cout << "||" <<endl;
				} else {
					sisawaktu = to_string(abs(SisaHari)) + " hari terlewati";
					cout << "||";
					cout << setw(8) <<left << todo->Id;
					cout << "||" << setw(15) << todo->Tugas <<left;
					cout << "||" << setw(20) << todo->Prioritas <<left;
					cout << "||" << setw(14) << todo->Status <<left;
					cout << "||" << setw(40) << todo->Deadline <<left;
					cout << "||" << setw(27) << sisawaktu <<left;
					cout << "||" << setw(40) << todo->Tanggal <<left;
					cout << "||" <<endl;
				}
			}
			cout << "||________||_______________||____________________||______________||________________________________________||___________________________||________________________________________||" << endl;

			cout << " Apakah Anda ingin mencari lagi? Y/T: ";
			getline(cin, ulangicari);

			if (ulangicari == "Y" || ulangicari == "y") {
				CariToDo();
			} else if (ulangicari == "T" || ulangicari == "t") {
				return;
			} else {
				cout << " Input salah!" << endl;
				return;
			}
		} else {
			cout << " Tugas dengan nama " << Tugas << " tidak ditemukan!" << endl;
			return;
		}
	} else if(pilihanpencarian == 3){
		cout << " Masukkan prioritas tugas yang ingin dicari: ";
		cin.ignore();
		getline(cin, Prioritas);

		vector<const Todo*> mencocokkanTodos;

		auto it = find_if(todos, todos + numTugas, [=](const Todo& todo) {
			return ConvertToLowercase(todo.Prioritas) == ConvertToLowercase(Prioritas);
		});

		while (it != todos + numTugas) {
			mencocokkanTodos.push_back(&(*it));
			it = find_if(it + 1, todos + numTugas, [=](const Todo& todo) {
				return ConvertToLowercase(todo.Prioritas) == ConvertToLowercase(Prioritas);
			});
		}

		if (!mencocokkanTodos.empty()) {
			cout << "____________________________________________________________________________________________________________________________________________________________________________________" << endl;
			cout << "||                                                                          Daftar Tugas                               					                          ||" << endl;
			cout << "||________________________________________________________________________________________________________________________________________________________________________________||" << endl;
			cout << "||";
			cout << setw(8) <<left << "   ID";
			cout << "||" << setw(15) << "     Tugas" <<left;
			cout << "||" << setw(20) << "      Prioritas"<<left;
			cout << "||" << setw(14) << "    Status" <<left;
			cout << "||" << setw(40) << "               Deadline" <<left;
			cout << "||" << setw(27) << "        Sisa Waktu" <<left;
			cout << "||" << setw(40) << "            Tanggal Ubah" <<left;
			cout << "||" <<endl;
			cout << "||________||_______________||____________________||______________||________________________________________||___________________________||________________________________________||" << endl;

			for (const Todo* todo : mencocokkanTodos) {

				time_t WaktuSekarang = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

				tm WaktuDeadline = {};
				istringstream deadlineStream(todo->Deadline);
				deadlineStream >> std::get_time(&WaktuDeadline, "%A, %d %B %Y - %H:%M");

				time_t deadline = std::mktime(&WaktuDeadline);

				time_t SisaDetik = deadline - WaktuSekarang;

				int SisaHari = SisaDetik / (60 * 60 * 24);

				int SisaJam = SisaDetik / (60 * 60);

				int SisaMenit = SisaDetik / 60;

				string sisawaktu;

				if (SisaHari == 0) {
					int jam = SisaMenit / 60;
					int menit = SisaMenit % 60;

					if (SisaJam == 0) {
						if(menit < 0){
							sisawaktu = to_string(abs(menit)) + " menit terlewati";
						} else {
							sisawaktu = to_string(menit) + " menit";
						}
					} else {
						if(jam < 0 && menit < 0 ){
							sisawaktu = to_string(abs(jam)) + " jam " + to_string(abs(menit)) + " menit terlewati";
						} else {
							sisawaktu = to_string(jam) + " jam " + to_string(menit) + " menit";
						}
					}
					cout << "||";
					cout << setw(8) <<left << todo->Id;
					cout << "||" << setw(15) << todo->Tugas <<left;
					cout << "||" << setw(20) << todo->Prioritas <<left;
					cout << "||" << setw(14) << todo->Status <<left;
					cout << "||" << setw(40) << todo->Deadline <<left;
					cout << "||" << setw(27) << sisawaktu <<left;
					cout << "||" << setw(40) << todo->Tanggal <<left;
					cout << "||" <<endl;
				} else if (SisaHari > 0) {
					SisaHari = SisaMenit / (60 * 24);
					SisaJam = (SisaMenit % (60 * 24)) / 60;
					SisaMenit = (SisaMenit % (60 * 24)) % 60;

					sisawaktu = to_string(SisaHari) + " hari " + to_string(SisaJam) + " jam " + to_string(SisaMenit) + " menit";
					cout << "||";
					cout << setw(8) <<left << todo->Id;
					cout << "||" << setw(15) << todo->Tugas <<left;
					cout << "||" << setw(20) << todo->Prioritas <<left;
					cout << "||" << setw(14) << todo->Status <<left;
					cout << "||" << setw(40) << todo->Deadline <<left;
					cout << "||" << setw(27) << sisawaktu <<left;
					cout << "||" << setw(40) << todo->Tanggal <<left;
					cout << "||" <<endl;
				} else {
					sisawaktu = to_string(abs(SisaHari)) + " hari terlewati";
					cout << "||";
					cout << setw(8) <<left << todo->Id;
					cout << "||" << setw(15) << todo->Tugas <<left;
					cout << "||" << setw(20) << todo->Prioritas <<left;
					cout << "||" << setw(14) << todo->Status <<left;
					cout << "||" << setw(40) << todo->Deadline <<left;
					cout << "||" << setw(27) << sisawaktu <<left;
					cout << "||" << setw(40) << todo->Tanggal <<left;
					cout << "||" <<endl;
				}
			}

			cout << "||________||_______________||____________________||______________||________________________________________||___________________________||________________________________________||" << endl;
			
			cout << " Apakah Anda ingin mencari lagi? Y/T: ";
			getline(cin, ulangicari);
			
			if (ulangicari == "Y" || ulangicari == "y") {
				CariToDo();
			} else if (ulangicari == "T" || ulangicari == "t") {
				return;
			} else {
				cout << " Input salah!" << endl;
				return;
			}
		}
		else {
			cout << " Tugas dengan prioritas " << Prioritas << " tidak ditemukan!" << endl;
			return;
		}
			
	} 
	else if(pilihanpencarian == 4){
		cout << " Masukkan status tugas yang ingin dicari: ";
		cin.ignore();
		getline(cin, Status);

		vector<const Todo*> mencocokkanTodos;

		auto it = find_if(todos, todos + numTugas, [=](const Todo& todo) {
			return ConvertToLowercase(todo.Status) == ConvertToLowercase(Status);
		});

		while (it != todos + numTugas) {
			mencocokkanTodos.push_back(&(*it));
			it = find_if(it + 1, todos + numTugas, [=](const Todo& todo) {
				return ConvertToLowercase(todo.Status) == ConvertToLowercase(Status);
			});
		}

		if (!mencocokkanTodos.empty()) {
			cout << "____________________________________________________________________________________________________________________________________________________________________________________" << endl;
			cout << "||                                                                          Daftar Tugas                               					                          ||" << endl;
			cout << "||________________________________________________________________________________________________________________________________________________________________________________||" << endl;
			cout << "||";
			cout << setw(8) <<left << "   ID";
			cout << "||" << setw(15) << "     Tugas" <<left;
			cout << "||" << setw(20) << "      Prioritas"<<left;
			cout << "||" << setw(14) << "    Status" <<left;
			cout << "||" << setw(40) << "               Deadline" <<left;
			cout << "||" << setw(27) << "        Sisa Waktu" <<left;
			cout << "||" << setw(40) << "            Tanggal Ubah" <<left;
			cout << "||" <<endl;
			cout << "||________||_______________||____________________||______________||________________________________________||___________________________||________________________________________||" << endl;

			for (const Todo* todo : mencocokkanTodos) {

				time_t WaktuSekarang = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

				tm WaktuDeadline = {};
				istringstream deadlineStream(todo->Deadline);
				deadlineStream >> std::get_time(&WaktuDeadline, "%A, %d %B %Y - %H:%M");

				time_t deadline = std::mktime(&WaktuDeadline);

				time_t SisaDetik = deadline - WaktuSekarang;

				int SisaHari = SisaDetik / (60 * 60 * 24);

				int SisaJam = SisaDetik / (60 * 60);

				int SisaMenit = SisaDetik / 60;

				string sisawaktu;

				if (SisaHari == 0) {
					int jam = SisaMenit / 60;
					int menit = SisaMenit % 60;

					if (SisaJam == 0) {
						if(menit < 0){
							sisawaktu = to_string(abs(menit)) + " menit terlewati";
						} else {
							sisawaktu = to_string(menit) + " menit";
						}
					} else {
						if(jam < 0 && menit < 0 ){
							sisawaktu = to_string(abs(jam)) + " jam " + to_string(abs(menit)) + " menit terlewati";
						} else {
							sisawaktu = to_string(jam) + " jam " + to_string(menit) + " menit";
						}
					}
					cout << "||";
					cout << setw(8) <<left << todo->Id;
					cout << "||" << setw(15) << todo->Tugas <<left;
					cout << "||" << setw(20) << todo->Prioritas <<left;
					cout << "||" << setw(14) << todo->Status <<left;
					cout << "||" << setw(40) << todo->Deadline <<left;
					cout << "||" << setw(27) << sisawaktu <<left;
					cout << "||" << setw(40) << todo->Tanggal <<left;
					cout << "||" <<endl;
				} else if (SisaHari > 0) {
					SisaHari = SisaMenit / (60 * 24);
					SisaJam = (SisaMenit % (60 * 24)) / 60;
					SisaMenit = (SisaMenit % (60 * 24)) % 60;

					sisawaktu = to_string(SisaHari) + " hari " + to_string(SisaJam) + " jam " + to_string(SisaMenit) + " menit";
					cout << "||";
					cout << setw(8) <<left << todo->Id;
					cout << "||" << setw(15) << todo->Tugas <<left;
					cout << "||" << setw(20) << todo->Prioritas <<left;
					cout << "||" << setw(14) << todo->Status <<left;
					cout << "||" << setw(40) << todo->Deadline <<left;
					cout << "||" << setw(27) << sisawaktu <<left;
					cout << "||" << setw(40) << todo->Tanggal <<left;
					cout << "||" <<endl;
				} else {
					sisawaktu = to_string(abs(SisaHari)) + " hari terlewati";
					cout << "||";
					cout << setw(8) <<left << todo->Id;
					cout << "||" << setw(15) << todo->Tugas <<left;
					cout << "||" << setw(20) << todo->Prioritas <<left;
					cout << "||" << setw(14) << todo->Status <<left;
					cout << "||" << setw(40) << todo->Deadline <<left;
					cout << "||" << setw(27) << sisawaktu <<left;
					cout << "||" << setw(40) << todo->Tanggal <<left;
					cout << "||" <<endl;
				}
			}
			cout << "||________||_______________||____________________||______________||________________________________________||___________________________||________________________________________||" << endl;

			cout << " Apakah Anda ingin mencari lagi? Y/T: ";
			getline(cin, ulangicari);

			if (ulangicari == "Y" || ulangicari == "y") {
				CariToDo();
			} else if (ulangicari == "T" || ulangicari == "t") {
				return;
			} else {
				cout << " Input salah!" << endl;
				return;
			}
		} else {
			cout << " Tugas dengan status " << Status << " tidak ditemukan!" << endl;
			return;
		}
	} else if(pilihanpencarian == 5){
		cout << " Masukkan deadline yang ingin dicari (DD/MM/YYYY HH:MM): ";
		cin.ignore();
		getline(cin, Deadline);

		tm DateTime = {};
		istringstream ss(Deadline);
		ss >> get_time(&DateTime, "%d/%m/%Y %H:%M");

		while (ss.fail()) {
			cout << " Ada kesalahan input tanggal. Silakan masukkan kembali deadline (DD/MM/YYYY HH:MM): ";
			getline(cin, Deadline);
			ss.clear();
			ss.str(Deadline);
			ss >> get_time(&DateTime, "%d/%m/%Y %H:%M");
		}

		time_t waktu = mktime(&DateTime);
		// chrono::system_clock::time_point timePoint = chrono::system_clock::from_time_t(waktu);
		stringstream DeadlineFormatted;
		DeadlineFormatted << put_time(&DateTime, "%A, %d %B %Y - %H:%M");
		string LowercaseDeadline = ConvertToLowercase(DeadlineFormatted.str().c_str());

		vector<const Todo*> mencocokkanTodos;

		auto it = find_if(todos, todos + numTugas, [LowercaseDeadline](const Todo& todo) {
			return ConvertToLowercase(todo.Deadline) == LowercaseDeadline;
		});

		while (it != todos + numTugas) {
			mencocokkanTodos.push_back(&(*it));
			it = find_if(it + 1, todos + numTugas, [=](const Todo& todo) {
				return ConvertToLowercase(todo.Deadline) == LowercaseDeadline;
			});
		}

		if (!mencocokkanTodos.empty()) {
			cout << "____________________________________________________________________________________________________________________________________________________________________________________" << endl;
			cout << "||                                                                          Daftar Tugas                               					                          ||" << endl;
			cout << "||________________________________________________________________________________________________________________________________________________________________________________||" << endl;
			cout << "||";
			cout << setw(8) <<left << "   ID";
			cout << "||" << setw(15) << "     Tugas" <<left;
			cout << "||" << setw(20) << "      Prioritas"<<left;
			cout << "||" << setw(14) << "    Status" <<left;
			cout << "||" << setw(40) << "               Deadline" <<left;
			cout << "||" << setw(27) << "        Sisa Waktu" <<left;
			cout << "||" << setw(40) << "            Tanggal Ubah" <<left;
			cout << "||" <<endl;
			cout << "||________||_______________||____________________||______________||________________________________________||___________________________||________________________________________||" << endl;

			for (const Todo* todo : mencocokkanTodos) {

				time_t WaktuSekarang = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

				tm WaktuDeadline = {};
				istringstream deadlineStream(todo->Deadline);
				deadlineStream >> std::get_time(&WaktuDeadline, "%A, %d %B %Y - %H:%M");

				time_t deadline = std::mktime(&WaktuDeadline);

				time_t SisaDetik = deadline - WaktuSekarang;

				int SisaHari = SisaDetik / (60 * 60 * 24);

				int SisaJam = SisaDetik / (60 * 60);

				int SisaMenit = SisaDetik / 60;

				string sisawaktu;

				if (SisaHari == 0) {
					int jam = SisaMenit / 60;
					int menit = SisaMenit % 60;

					if (SisaJam == 0) {
						sisawaktu = to_string(menit) + " menit";
					} else {
						if(jam < 0 && menit < 0 ){
							sisawaktu = to_string(abs(jam)) + " jam " + to_string(abs(menit)) + " menit";
						} else {
							sisawaktu = to_string(jam) + " jam " + to_string(menit) + " menit";
						}
					}
					cout << "||";
					cout << setw(8) <<left << todo->Id;
					cout << "||" << setw(15) << todo->Tugas <<left;
					cout << "||" << setw(20) << todo->Prioritas <<left;
					cout << "||" << setw(14) << todo->Status <<left;
					cout << "||" << setw(40) << todo->Deadline <<left;
					cout << "||" << setw(27) << sisawaktu <<left;
					cout << "||" << setw(40) << todo->Tanggal <<left;
					cout << "||" <<endl;
				} else if (SisaHari > 0) {
					SisaHari = SisaMenit / (60 * 24);
					SisaJam = (SisaMenit % (60 * 24)) / 60;
					SisaMenit = (SisaMenit % (60 * 24)) % 60;

					sisawaktu = to_string(SisaHari) + " hari " + to_string(SisaJam) + " jam " + to_string(SisaMenit) + " menit";
					cout << "||";
					cout << setw(8) <<left << todo->Id;
					cout << "||" << setw(15) << todo->Tugas <<left;
					cout << "||" << setw(20) << todo->Prioritas <<left;
					cout << "||" << setw(14) << todo->Status <<left;
					cout << "||" << setw(40) << todo->Deadline <<left;
					cout << "||" << setw(27) << sisawaktu <<left;
					cout << "||" << setw(40) << todo->Tanggal <<left;
					cout << "||" <<endl;
				} else {
					sisawaktu = to_string(abs(SisaHari)) + " hari terlewati";
					cout << "||";
					cout << setw(8) <<left << todo->Id;
					cout << "||" << setw(15) << todo->Tugas <<left;
					cout << "||" << setw(20) << todo->Prioritas <<left;
					cout << "||" << setw(14) << todo->Status <<left;
					cout << "||" << setw(40) << todo->Deadline <<left;
					cout << "||" << setw(27) << sisawaktu <<left;
					cout << "||" << setw(40) << todo->Tanggal <<left;
					cout << "||" <<endl;
				}
			}
			cout << "||________||_______________||____________________||______________||________________________________________||___________________________||________________________________________||" << endl;

			cout << " Apakah Anda ingin mencari lagi? Y/T: ";
			getline(cin, ulangicari);
			
			if (ulangicari == "Y" || ulangicari == "y") {
				CariToDo();
			} else if (ulangicari == "T" || ulangicari == "t") {
				return;
			} else {
				cout << " Input salah!" << endl;
				return;
			}
		} else {
			cout << " Tugas dengan deadline " <<  DeadlineFormatted.str().c_str() << " tidak ditemukan!" << endl;
			return;
		}
	} else {
		cout << " Input salah!" << endl;
		return;
	}
}

int main() {
	int pilihan, id;
	do {
		cout << "      //---------------\\\\" <<endl;
		cout << "     //__/___/___/___/__\\\\" <<endl;
		cout << "   _//___/___/___/___/___\\\\_" <<endl;
		cout << "  _||   SELAMAT DATANG    ||_ " <<endl;
		cout << " _|| DI APLIKASI TO DO LIST ||_" <<endl;
		cout << "_||========||_____||========||_" << endl;
		cout << "||   <$>   MAIN MENU   <$>   ||" <<endl;
		cout << "||_________||-----||_________||" << endl;
		cout << "|| (1) Tambah Tugas          ||" << endl;
		cout << "|| (2) Lihat Tugas           ||" << endl;
		cout << "|| (3) Edit Tugas            ||" << endl;
		cout << "|| (4) Hapus Tugas           ||"  << endl;
		cout << "|| (5) Cari Tugas            ||"  << endl;
		cout << "|| (6) Keluar                ||"  << endl;
		cout << "||___________________________||" << endl;
		cout << "  Masukkan Pilihan: ";
		cin >> pilihan;
		do {
		    if (cin.fail()) {
		        cout << " Input salah. Harap masukkan angka!" << endl;
		        cin.clear();
		        cin.ignore(numeric_limits<streamsize>::max(), '\n');
		    } else {
		        break;
		    }
		} while (true);
		switch (pilihan) {
			case 1:
				TambahToDo();
				break;
			case 2:
				LihatToDo();
				break;
			case 3:
				do {
				    cout << " Masukkan ID tugas yang ingin diedit: ";
				    cin >> id;
				    if (cin.fail()) {
				        cout << " Input salah. Harap masukkan angka!" << endl;
				        cin.clear();
				        cin.ignore(numeric_limits<streamsize>::max(), '\n');
				    } else {
				        break;
				    }
				} while (true);
				EditTugas(id);
				break;
			case 4:
				do {
				    cout << " Masukkan ID tugas yang ingin dihapus: ";
				    cin >> id;
				    if (cin.fail()) {
				        cout << " Input salah. Harap masukkan angka!" << endl;
				        cin.clear();
				        cin.ignore(numeric_limits<streamsize>::max(), '\n');
				    } else {
				        break;
				    }
				} while (true);
				HapusToDo(id);
				break;
			case 5:
				CariToDo();
				break;
			case 6:
				cout << " Anda telah keluar dari aplikasi";
				return 0;
			default:
				cout << " Pilihan salah! Silakan coba lagi." << endl;
				break;
		}
		cout << endl;
	} while (pilihan != 6);
}