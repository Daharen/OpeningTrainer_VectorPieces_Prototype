#pragma once

#include <QString>

namespace otpvp {

enum class PieceType {
    Queen
};

enum class PieceColor {
    White,
    Black
};

inline QString toString(PieceType type)
{
    switch (type) {
    case PieceType::Queen:
        return QStringLiteral("Queen");
    }

    return QStringLiteral("Unknown");
}

inline QString toString(PieceColor color)
{
    switch (color) {
    case PieceColor::White:
        return QStringLiteral("White");
    case PieceColor::Black:
        return QStringLiteral("Black");
    }

    return QStringLiteral("Unknown");
}

} // namespace otpvp
