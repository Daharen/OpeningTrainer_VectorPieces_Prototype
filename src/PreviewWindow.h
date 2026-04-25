#pragma once

#include "PiecePixmapCache.h"

#include <QWidget>

class QLabel;

namespace otpvp {

class PreviewCanvas final : public QWidget {
public:
    explicit PreviewCanvas(PiecePixmapCache *cache, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    PiecePixmapCache *m_cache;
};

class PreviewWindow final : public QWidget {
public:
    explicit PreviewWindow(QWidget *parent = nullptr);

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    void refreshStatus();

    PiecePixmapCache m_cache;
    PreviewCanvas *m_canvas;
    QLabel *m_statusLabel;
};

} // namespace otpvp
