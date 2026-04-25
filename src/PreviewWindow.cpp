#include "PreviewWindow.h"

#include "PieceTypes.h"

#include <QLabel>
#include <QPaintEvent>
#include <QPainter>
#include <QResizeEvent>
#include <QTimer>
#include <QVBoxLayout>

namespace otpvp {

namespace {
QColor lightSquareColor()
{
    return QColor("#F0D9B5");
}

QColor darkSquareColor()
{
    return QColor("#B58863");
}

QRect centeredRectIn(const QRect &container, int size)
{
    return QRect(
        container.x() + (container.width() - size) / 2,
        container.y() + (container.height() - size) / 2,
        size,
        size);
}
} // namespace

PreviewCanvas::PreviewCanvas(PiecePixmapCache *cache, QWidget *parent)
    : QWidget(parent)
    , m_cache(cache)
{
    setMinimumSize(720, 480);
}

void PreviewCanvas::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    if (!m_cache) {
        return;
    }

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.fillRect(rect(), QColor("#101418"));

    const qreal dpr = devicePixelRatioF();

    // Large queen preview zone.
    const int largeSize = 320;
    QRect largeZone(20, 20, 380, height() - 40);
    QRect largeSwatch = centeredRectIn(largeZone, largeSize);
    painter.fillRect(largeSwatch, lightSquareColor());

    QPixmap largeWhite = m_cache->get(PieceType::Queen, PieceColor::White, largeSize, dpr);
    painter.drawPixmap(largeSwatch, largeWhite);

    // Smaller board-size previews.
    const QList<int> sizes {32, 48, 64, 96, 128, 192};
    const int startX = 430;
    const int rowSpacing = 16;
    const int swatchPadding = 6;

    int y = 36;
    for (int size : sizes) {
        const QRect whiteSwatch(startX, y, size + swatchPadding * 2, size + swatchPadding * 2);
        const QRect blackSwatch(startX + 260, y, size + swatchPadding * 2, size + swatchPadding * 2);

        painter.fillRect(whiteSwatch, (size % 2 == 0) ? darkSquareColor() : lightSquareColor());
        painter.fillRect(blackSwatch, (size % 2 == 0) ? lightSquareColor() : darkSquareColor());

        QPixmap whitePixmap = m_cache->get(PieceType::Queen, PieceColor::White, size, dpr);
        QPixmap blackPixmap = m_cache->get(PieceType::Queen, PieceColor::Black, size, dpr);

        painter.drawPixmap(whiteSwatch.adjusted(swatchPadding, swatchPadding, -swatchPadding, -swatchPadding), whitePixmap);
        painter.drawPixmap(blackSwatch.adjusted(swatchPadding, swatchPadding, -swatchPadding, -swatchPadding), blackPixmap);

        painter.setPen(Qt::white);
        painter.drawText(startX + 125, y + size / 2 + 4, QString("%1 px").arg(size));

        y += size + rowSpacing;
    }
}

PreviewWindow::PreviewWindow(QWidget *parent)
    : QWidget(parent)
    , m_canvas(new PreviewCanvas(&m_cache, this))
    , m_statusLabel(new QLabel(this))
{
    setWindowTitle(QStringLiteral("OpeningTrainerVectorPiecesPrototype"));
    resize(980, 860);

    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(8, 8, 8, 8);
    layout->setSpacing(8);

    layout->addWidget(m_canvas, 1);

    m_statusLabel->setMinimumHeight(48);
    m_statusLabel->setStyleSheet(QStringLiteral("QLabel { background:#1e1e1e; color:#e6e6e6; padding:8px; font-family:Consolas, monospace; }"));
    m_statusLabel->setWordWrap(true);
    layout->addWidget(m_statusLabel);

    auto *timer = new QTimer(this);
    timer->setInterval(250);
    connect(timer, &QTimer::timeout, this, [this]() { refreshStatus(); });
    timer->start();

    refreshStatus();
}

void PreviewWindow::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    refreshStatus();
}

void PreviewWindow::refreshStatus()
{
    const qreal dpr = devicePixelRatioF();
    const QString text = QStringLiteral(
                             "devicePixelRatio: %1 | window: %2x%3 | cached pixmaps: %4 | last rendered square size: %5 px")
                             .arg(QString::number(dpr, 'f', 2))
                             .arg(width())
                             .arg(height())
                             .arg(m_cache.cachedCount())
                             .arg(m_cache.lastRenderedSquareSize());
    m_statusLabel->setText(text);
}

} // namespace otpvp
