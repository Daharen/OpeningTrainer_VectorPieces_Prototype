#include "PiecePixmapCache.h"

#include <QtGlobal>

#include <cmath>

namespace otpvp {

namespace {
quint64 composeKey(PieceType type, PieceColor color, int squareSizePx, int dprHundredths)
{
    const quint64 typePart = static_cast<quint64>(type) & 0xFF;
    const quint64 colorPart = static_cast<quint64>(color) & 0xFF;
    const quint64 sizePart = static_cast<quint64>(squareSizePx) & 0xFFFF;
    const quint64 dprPart = static_cast<quint64>(dprHundredths) & 0xFFFF;

    return (typePart << 48) | (colorPart << 40) | (sizePart << 16) | dprPart;
}
} // namespace

PiecePixmapCache::PiecePixmapCache() = default;

QPixmap PiecePixmapCache::get(PieceType type, PieceColor color, int squareSizePx, qreal devicePixelRatio)
{
    const int dprHundredths = quantizeDpr(devicePixelRatio);
    const quint64 key = composeKey(type, color, squareSizePx, dprHundredths);

    const auto it = m_cache.constFind(key);
    if (it != m_cache.cend()) {
        return it.value();
    }

    const QPixmap rendered = m_renderer.render(type, color, squareSizePx, devicePixelRatio);
    m_cache.insert(key, rendered);
    return rendered;
}

void PiecePixmapCache::clear()
{
    m_cache.clear();
}

int PiecePixmapCache::cachedCount() const
{
    return m_cache.size();
}

int PiecePixmapCache::lastRenderedSquareSize() const
{
    return m_renderer.lastRenderedSquareSize();
}

bool PiecePixmapCache::CacheKey::operator==(const CacheKey &other) const
{
    return type == other.type
        && color == other.color
        && squareSizePx == other.squareSizePx
        && dprHundredths == other.dprHundredths;
}

int PiecePixmapCache::quantizeDpr(qreal dpr)
{
    return static_cast<int>(std::round(dpr * 100.0));
}

} // namespace otpvp
