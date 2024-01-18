#include "SmartPointer.h"
#include "Quiz.h"
#include <algorithm>
#include <random>
#include <fstream>
#include <iomanip>

Quiz::Quiz()  : skor(0){
   /* std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(pitanja.begin(),pitanja.end(),g);*/
}

void Quiz::loadPitanja(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Greska prilikom otvaranja datoteke: " << filename << std::endl;
        return;
    }
    std::string line;
    while (std::getline(file,line)){
        std::string pitanje = line;
        std::vector <std::string>opcije;
        int tacanOdgovor;
        for (int i=0;i<4;++i) {
            std::getline(file,line);
            opcije.push_back(line);
        }
        std::getline(file,line);
        if (!line.empty()) {
            try {
                tacanOdgovor = std::stoi(line);
                pitanja.push_back(Pitanja(pitanje, opcije, tacanOdgovor));
            } catch (const std::invalid_argument& e) {
                std::cerr << "Invalid argument: " << e.what() << std::endl;
            } catch (const std::out_of_range& e) {
                std::cerr << "Out of range: " << e.what() << std::endl;
            } catch (...) {
                std::cerr << "An unexpected error occurred while converting to integer." << std::endl;
            }
        } else {
            std::cerr << "Empty line encountered. Skipping." << std::endl;
        }
    }
    file.close();
}


void Quiz::start()  {
    SmartPointer<int> skorPointer(std::make_shared<int> (skor));
    odabirOblasti();
    int brPitanja = 15;
    int trenutnoPitanje = 0;
    while (trenutnoPitanje < brPitanja && trenutnoPitanje < pitanja.size()) {
        const auto &pitanje = pitanja[trenutnoPitanje];
        pitanje.display();
        int odabir;
        std::cout << "Unesite vas odgovor(1-" << pitanje.opcije.size() << "): ";
        std::cin >> odabir;
        if(pitanje.isTacno(odabir)){
            std::cout << "Tacno!\n";
               skor++;
        }else{
            std::cout << "Netacno, Tacan odgovor je: " << pitanje.tacanOdgovor  << ". " << pitanje.opcije[pitanje.tacanOdgovor - 1] << "\n";

        }
        std::cout << std::endl;
        trenutnoPitanje++;
        int skorUpdate = *skorPointer.get();
    }
    std::cout << "Quizz zavrsen. Vas skor je: " << skor << " od " << brPitanja << std::endl;

}

void Quiz::odabirOblasti() {
    std::cout << "Dobro dosli u kviz!,Odaberite oblast u kojoj imate najvise znanja:" << std::endl;
    std::cout << "1. Sport" << std::endl;
    std::cout << "2. Geografija(Zemljopis)" << std::endl;
    std::cout << "3. Historija" << std::endl;
    std::cout << "4. Zivotinjski svijet" << std::endl;

    int userOdabir;
    std::cout << "Unesite vas odabir: ";
    std::cin >> userOdabir;

    switch (userOdabir) {
        case 1: {
            loadPitanja("Sport.txt");
            std::random_device rd;
            std::mt19937 g(rd());
            std::shuffle(pitanja.begin(), pitanja.end(), g);
        }
            break;
        case 2: {
            loadPitanja("Geografija.txt");
            std::random_device rd;
            std::mt19937 g(rd());
            std::shuffle(pitanja.begin(), pitanja.end(), g);
        }
            break;
        case 3:
        {   loadPitanja("Historija.txt");
            std::random_device rd;
            std::mt19937 g(rd());
            std::shuffle(pitanja.begin(),pitanja.end(),g);
        }

            break;
        case 4: {
            loadPitanja("Zivotinje.txt");
            std::random_device rd;
            std::mt19937 g(rd());
            std::shuffle(pitanja.begin(), pitanja.end(), g);
        }
            break;
        default:
            std::cerr << "Pogresan unos. Zavrsavam program." << std::endl;
            exit(1);
    }
}

void Quiz::pohraniSkor(const std::string &imeIgraca, std::string &prezimeIgraca) {
    for(auto& igrac : igraci) {
        if (igrac.ime == imeIgraca && igrac.prezime == prezimeIgraca) {
            igrac.brBodova += skor;
            std::cout << "Skor igraca " << imeIgraca << " " << prezimeIgraca << " je pohranjen." << std::endl;
            return;
        }
        storedTabela("Tabela.txt");
    }
    igraci.push_back(Igrac(imeIgraca, prezimeIgraca, skor));
    std::cout << "Igrac " << imeIgraca << " " << prezimeIgraca << " dodan u tabelu." << std::endl;
}

void Quiz::tabela() const {
    std::vector<Igrac> sortedIgraci = igraci;
    std::sort(sortedIgraci.begin(), sortedIgraci.end(), [](const Igrac& a, const Igrac& b) {
        return a.brBodova > b.brBodova;
    });

    std::cout << "Tabela igraca" << std::endl;
    std::cout << std::setw(15) << "Ime" << std::setw(15) << "Prezime" << std::setw(10) << "Bodovi" << std::endl;

    std::ofstream tabelaFile("Tabela.txt");
    if (!tabelaFile.is_open()){
        std::cerr << "Error, greska prilikom otvaranja Tabela.txt za zapisivanje" << std::endl;
        return;
    }
    tabelaFile << std::setw(15) << "Ime" << std::setw(15) << "Prezime" << std::setw(10) << "Bodovi" << std::endl;
    for (const auto& igrac : igraci) {
        std::cout << std::setw(15) << igrac.ime << std::setw(15) << igrac.prezime << std::setw(10) << igrac.brBodova << std::endl;
        tabelaFile << std::setw(15) << igrac.ime << std::setw(15) << igrac.prezime << std::setw(10) << igrac.brBodova << std::endl;
    }
    tabelaFile.close();
}
void Quiz::storedTabela(const std::string &filename) const {
    std::ifstream tabelaFile(filename);
    if (!tabelaFile.is_open()) {
        std::cerr << "Greska prilikom otvaranja " << filename << "za iscitavanje." << std::endl;
        return;
    }
    std::string line;
    while (std::getline(tabelaFile, line)) {
        std::cout << line << std::endl;
    }
    tabelaFile.close();
}

void Quiz::saveTable(const std::string& filename) const {
    std::ofstream tabelaFile(filename);
    if (!tabelaFile.is_open()) {
        std::cerr << "Unable to open " << filename << " for writing." << std::endl;
        return;
    }


    tabelaFile << std::setw(15) << "Ime" << std::setw(15) << "Prezime" << std::setw(10) << "Bodovi" << std::endl;


    for (const auto& igrac : igraci) {
        tabelaFile << std::setw(15) << igrac.ime << std::setw(15) << igrac.prezime << std::setw(10) << igrac.brBodova << std::endl;
    }

    tabelaFile.close();
}

void Quiz::loadTable(const std::string& filename) {
    std::ifstream tabelaFile(filename);
    if (!tabelaFile.is_open()) {
        std::cerr << "Unable to open " << filename << " for reading." << std::endl;
        return;
    }


    std::string header;
    std::getline(tabelaFile, header);


    Igrac igrac;
    while (tabelaFile >> igrac.ime >> igrac.prezime >> igrac.brBodova) {
        igraci.push_back(igrac);
    }

    tabelaFile.close();
}
