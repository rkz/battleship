#include "ShotResult.h"

#include <cassert>

ShotResult::ShotResult(Grid _targetGrid, Result _result, bool _winningShot)
    : targetGrid(_targetGrid), result(_result), winningShot(_winningShot)
{

}

bool ShotResult::isValid() const
{
    return (result != ALREADY_PLAYED);
}

Result ShotResult::getResult() const
{
	return result;
}

bool ShotResult::isWinning() const
{
    return winningShot;
}

std::string ShotResult::getResultAsString() const
{
    switch (result) {
        case MISSED: return "missed";
        case TOUCHED: return "touched";
        case SUNK: return "sunk";
        case ALREADY_PLAYED: return "position already shot";
        default: return "";
    };
}

Grid* ShotResult::getTargetGrid() const
{
    return new Grid (targetGrid);
}

std::string ShotResult::serialize()
{
    std::string serializedString = targetGrid.serialize() + "/";

    switch (result) {
        case MISSED:
            serializedString += "M";
            break;
        case TOUCHED:
            serializedString += "T";
            break;
        case SUNK:
            serializedString += "S";
            break;
        case ALREADY_PLAYED:
            serializedString += "A";
            break;
        default:
        	assert(false);
            break;
    }

    if (winningShot) serializedString += "T";
    else serializedString += "F";

    return serializedString;
}

ShotResult ShotResult::unserialize(std::string str)
{
	std::string gridPart = str.substr(0, str.size() - 3);  // exclude 3 last characters (e.g. "/MT")
	char resultPart = str.at(str.size() - 2);  // penultimate character (e.g. "M")
	char winningPart = str.at(str.size() - 1);  // last character (e.g. "T")

	// Unserialize grid part
	Grid g = Grid::unserialize(gridPart);

	// Unserialize result part
	Result result = MISSED;
	if (resultPart == 'M') result = MISSED;
	else if (resultPart == 'T') result = TOUCHED;
	else if (resultPart == 'S') result = SUNK;
	else if (resultPart == 'A') result = ALREADY_PLAYED;
	else assert(false);

	// Unserialize winning part
	bool winning = false;
	if (winningPart == 'T') winning = true;
	else if (winningPart == 'F') winning = false;
	else assert(false);

	return ShotResult(g, result, winning);
}
