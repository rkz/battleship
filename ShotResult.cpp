#include "ShotResult.h"

ShotResult::ShotResult(Grid _targetGrid, Result _result, bool _winningShot)
    : targetGrid(_targetGrid), result(_result), winningShot(_winningShot)
{

}

bool ShotResult::isValid() const
{
    return (result != ALREADY_PLAYED);
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

std::string ShotResult::stringFromShotResult() const
{
    std::string serializedString = targetGrid.stringFromGrid();
    serializedString += "$";
    switch (result) {
        case MISSED:
            serializedString += "m";
            break;
        case TOUCHED:
            serializedString += "t";
            break;
        case SUNK:
            serializedString += "s";
            break;
        case ALREADY_PLAYED:
            serializedString += "a";
            break;
        default:
            break;
    }
    serializedString += "$";

    if (winningShot) serializedString += "t";
    else serializedString += "f";

    return serializedString;
}

ShotResult shotResultFromString(std::string stringToUnserialize)
{
    std::string str[3];
    int i = 0;

    // r�cup�ration des trois strings : la premi�re codant la grille, la seconde le result et la troisi�me le winningShot
    for (int j = 0; j < 3; j++){
        while ( i < stringToUnserialize.size() && stringToUnserialize[i] != '$'){
            str[j].push_back(stringToUnserialize[i]);
            i++;
            }
        i++;
        }

    Grid itsGrid = gridFromString(str[0]);

    Result itsResult = MISSED; // arbitraire
    bool itsWinningShot = false; // arbitraire

    if (str[1] == "m")
            itsResult = MISSED;
    else if (str[1] == "t")
            itsResult = TOUCHED;
    else if (str[1] == "s")
            itsResult = SUNK;
    else if (str[1] == "a")
            itsResult = ALREADY_PLAYED;

    if (str[2] == "t")
            itsWinningShot = true;
    else if (str[2] == "f")
            itsWinningShot = false;

    ShotResult unserializedShot (itsGrid, itsResult, itsWinningShot);

    return unserializedShot;
}

bool ShotResult::isEqual(ShotResult toCompare) const {

return targetGrid.isEqual(toCompare.targetGrid)
    && result == toCompare.result
    && winningShot == toCompare.winningShot;

}

bool operator== (ShotResult const& shot1, ShotResult const& shot2){

    return shot1.isEqual(shot2);
}


