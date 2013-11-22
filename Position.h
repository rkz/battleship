/*
 * Position.h
 *
 * Une position correspond à un couple de coordonnées (x, y) sur la grille de jeu.
 *
 * x et y sont des coordonnées entières commençant à 0.
 * x = numéro de colonne (abscisse)
 * y = numéro de ligne (ordonnée)
 *
 * Une position se code en une chaîne de 2 ou 3 caractères pour le plateau.
 * Par exemple, (0, 0) <-> "A1" et (3, 20) <-> "D21"
 * Ce codage implique que les grilles ne peuvent pas dépasser 26*26 cases.
 *
 * Il n'y a pas de lien entre une position et une grille (les positions sont
 * généralement utilisées comme paramètres et donc vérifiées par les méthodes
 * de Grid), ainsi (-3, -1) ou (1000, 999) sont des positions valides.
 */

#ifndef POSITION_H_
#define POSITION_H_

#include <ostream>

class Position
{
private:
	int x;
	int y;

public:
	// Construction d'une Position par ses coordonnées
	Position(int x, int y);

	// Construction d'une Position à partir d'une chaîne type "A1"
	Position(std::string pos);

	// Copie d'une position
	Position(const Position&);

	// Lecture des coordonnées
	int getX() const;
	int getY() const;

	// Conversion de Position(1,1) en "B2"
	std::string toString() const;

	// Helpers pour convertir les lettres de A à Z en nombres et vice-versa
	static char toLetter(int x); // 5 -> "F"
	static int toInt(char a); // "F" -> 5
	static int numberToInt(std::string numberString); // "12" -> 12
};

// Comparaison de positions
bool operator==(Position const& a, Position const& b);
bool operator!=(Position const& a, Position const& b);

// Affichage d'une position sur un flux de sortie (utilise toString)
std::ostream & operator<<(std::ostream & ofs, Position const& p);

// Invalid position
class InvalidPositionString : public std::exception
{
	std::string str;

public:
	InvalidPositionString(std::string _str = "") throw() : str(_str) {}
	~InvalidPositionString() throw() {}
};

#endif /* POSITION_H_ */
