#include "../include/Case.h"
#include "../include/Exceptions.h"

using namespace JeuHive;
using namespace std;

const Piece* JeuHive::Case::getDessus() const {
	try {
		if (pieces.empty()) {
			return nullptr;
		}
		const Piece* dessus = pieces.back();
		if (!dessus) {
		}
		return dessus;
	}
	catch (exception& e) {
		throw HiveException(e.what());
	}
}

string Case::toString() const
{
	string str_case;

	for (const Piece* piece : pieces) {
		if (!piece) {
			cerr << "Erreur : pièce null dans la case." << endl;
			continue;
		}

		try {
			str_case.append(piece->toString());
		}
		catch (const HiveException& e) {
			cerr << "Erreur lors de la génération de la représentation textuelle : " << e.getInfo() << endl;
		}
	}

	return str_case;
}

ResumeCase Case::resumer() const {
	ResumeCase resume;
	resume.q = coo.get_q();
	resume.r = coo.get_r();

	for (const auto& piece : pieces) {
		if (piece) {
			resume.pieces.push_back(piece->resumer());
		}
	}

	return resume;
}


ostream& JeuHive::operator<<(ostream& os, const Case& c)
{
	os << c.toString();
	return os;
}