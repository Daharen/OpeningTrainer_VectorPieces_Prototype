#include "PieceRenderer.h"

#include <QColor>
#include <QPainter>
#include <QPainterPath>
#include <QPen>

#include <cmath>

namespace otpvp {

namespace {
constexpr qreal kDesignSize = 1000.0;
}

PieceRenderer::PieceRenderer()
    : m_style {
        QColor("#1F2024"),
        QColor("#E8E7E2"),
        QColor("#F2F1EC"),
        QColor("#26282D"),
        QColor("#0E1014"),
        22.0,
        14.0,
    }
    , m_lastRenderedSquareSize(0)
{
}

QPixmap PieceRenderer::render(PieceType type, PieceColor color, int squareSizePx, qreal devicePixelRatio) const
{
    const int scaledSize = static_cast<int>(std::ceil(squareSizePx * devicePixelRatio));
    QPixmap pixmap(scaledSize, scaledSize);
    pixmap.setDevicePixelRatio(devicePixelRatio);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing, true);

    switch (type) {
    case PieceType::Queen:
        drawQueen(painter, color, squareSizePx);
        break;
    }

    m_lastRenderedSquareSize = squareSizePx;
    return pixmap;
}

int PieceRenderer::lastRenderedSquareSize() const
{
    return m_lastRenderedSquareSize;
}

QPainterPath PieceRenderer::queenOuterPath() const
{
    QPainterPath path;

    // Base
    path.addRoundedRect(QRectF(160, 820, 680, 120), 40, 40);
    path.addRoundedRect(QRectF(210, 760, 580, 80), 28, 28);

    // Body silhouette
    QPainterPath body;
    body.moveTo(300, 760);
    body.cubicTo(280, 620, 340, 500, 420, 350);
    body.cubicTo(450, 300, 470, 260, 480, 210);
    body.lineTo(520, 210);
    body.cubicTo(530, 260, 550, 300, 580, 350);
    body.cubicTo(660, 500, 720, 620, 700, 760);
    body.closeSubpath();
    path.addPath(body);

    // Neck/head
    path.addRoundedRect(QRectF(430, 150, 140, 80), 30, 30);

    // Crown ring
    path.addRoundedRect(QRectF(365, 95, 270, 75), 30, 30);

    // Crown points as circles (placeholder flower/star motif seeds)
    path.addEllipse(QPointF(390, 85), 34, 34);
    path.addEllipse(QPointF(455, 60), 30, 30);
    path.addEllipse(QPointF(520, 48), 28, 28);
    path.addEllipse(QPointF(585, 60), 30, 30);
    path.addEllipse(QPointF(650, 85), 34, 34);

    return path;
}

QPainterPath PieceRenderer::queenDetailPath() const
{
    QPainterPath detail;

    detail.moveTo(500, 250);
    detail.lineTo(500, 710);

    detail.moveTo(400, 360);
    detail.cubicTo(440, 470, 440, 600, 390, 720);

    detail.moveTo(600, 360);
    detail.cubicTo(560, 470, 560, 600, 610, 720);

    detail.moveTo(320, 780);
    detail.lineTo(680, 780);

    detail.moveTo(270, 860);
    detail.lineTo(730, 860);

    return detail;
}

void PieceRenderer::drawQueen(QPainter &painter, PieceColor color, int squareSizePx) const
{
    painter.save();

    const qreal scale = squareSizePx / kDesignSize;
    painter.scale(scale, scale);

    const QPainterPath outer = queenOuterPath();
    const QPainterPath detail = queenDetailPath();

    QColor fill = (color == PieceColor::White) ? m_style.whiteFill : m_style.blackFill;
    QColor detailColor = (color == PieceColor::White) ? m_style.whiteDetail : m_style.blackDetail;

    QPen outlinePen(m_style.outline);
    outlinePen.setWidthF(m_style.baseOutlineWidth);
    outlinePen.setJoinStyle(Qt::RoundJoin);
    outlinePen.setCapStyle(Qt::RoundCap);

    painter.setPen(outlinePen);
    painter.setBrush(fill);
    painter.drawPath(outer);

    QPen detailPen(detailColor);
    detailPen.setWidthF(m_style.detailLineWidth);
    detailPen.setJoinStyle(Qt::RoundJoin);
    detailPen.setCapStyle(Qt::RoundCap);

    painter.setBrush(Qt::NoBrush);
    painter.setPen(detailPen);
    painter.drawPath(detail);

    painter.restore();
}

} // namespace otpvp
