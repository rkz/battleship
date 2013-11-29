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
    std::string serializedString;
    serializedString += targetGrid.stringFromGrid();
    serializedString += ","
    switch (result) {
        case MISSED:
            serializedString += "m"
            break;
        case TOUCHED:
            serializedString += "t"
            break;
        case SUNK:
            serializedString += "s"
            break;
        case ALREADY_PLAYED:
            serializedString += "a"
        default:
            break;
    }
    serializedString += ","
    if (winningShot) serializedString += "t";
    else serializedString += "f";

    return serializedString;
}

ShotResult shotResultFromString(std::string stringToUnserialize)
{
    std::vector<std::string> strings;
    int i = 0;

    for (int j = 0; j < 3; j++){
        while (stringToUnserialize[i] != "$"){
            strings.push_back(stringToUnserialize[i]);
            i++;
            }
        i++;
        }

    Grid itsGrid = gridFromString(strings[0]);
    Result itsResult = MISSED; // arbitraire
    bool itsWinningShot = false; // arbitraire

    switch(strings[1]){
        case "m" :
            itsResult = MISSED;
            break;
        case "t" :
            itsResult = TOUCHED;
            break;
        case "s" :
            itsResult = SUNK;
            break;
        case "a" :
            itsResult = ALREADY_PLAYED;
            break;
        default :
            break;
    }
    switch(strings[2]){
        case "t" :
            itsWinningShot = true;
            break;
        case "f" :
            itsWinningShot = false;
            break;
    }

    return ShotResult unserializedShot (itsGrid, itsResult, itsWinningShot);
}
