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