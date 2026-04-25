#pragma once

#include "PieceRenderer.h"
#include "PieceTypes.h"

#include <QHash>
#include <QPixmap>

namespace otpvp {

class PiecePixmapCache {
public:
    PiecePixmapCache();

    QPixmap get(PieceType type, PieceColor color, int squareSizePx, qreal devicePixelRatio);
    void clear();

    int cachedCount() const;
    int lastRenderedSquareSize() const;

private:
    struct CacheKey {
        PieceType type;
        PieceColor color;
        int squareSizePx;
        int dprHundredths;

        bool operator==(const CacheKey &other) const;
    };

    static int quantizeDpr(qreal dpr);

    PieceRenderer m_renderer;
    QHash<quint64, QPixmap> m_cache;
};

} // namespace otpvp
