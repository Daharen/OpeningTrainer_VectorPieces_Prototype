#pragma once

#include "PieceTypes.h"

#include <QPixmap>

namespace otpvp {

class PieceRenderer {
public:
    struct Style {
        QColor blackFill;
        QColor blackDetail;
        QColor whiteFill;
        QColor whiteDetail;
        QColor outline;
        qreal baseOutlineWidth;
        qreal detailLineWidth;
    };

    PieceRenderer();

    QPixmap render(PieceType type, PieceColor color, int squareSizePx, qreal devicePixelRatio) const;

    int lastRenderedSquareSize() const;

private:
    QPainterPath queenOuterPath() const;
    QPainterPath queenDetailPath() const;
    void drawQueen(QPainter &painter, PieceColor color, int squareSizePx) const;

    Style m_style;
    mutable int m_lastRenderedSquareSize;
};

} // namespace otpvp
