#include "Igrac.h"

Igrac::Igrac() : ime("Novi"), prezime("Igrac"),brBodova(0) {};
Igrac::Igrac(const std::string& imeIgraca,std::string& prezimeIgraca, int skorIgraca) : ime(imeIgraca), prezime(prezimeIgraca), brBodova(skorIgraca){}