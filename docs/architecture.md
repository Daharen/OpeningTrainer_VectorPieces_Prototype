# Architecture Overview

## Scope

This repository is a standalone lab for procedural/vector chess piece development. It is intentionally isolated from the main Opening Trainer application.

## Rendering Pipeline

1. **Vector definition**
   - Pieces are defined in normalized logical coordinates (`1000 x 1000`).
   - The first implementation provides only `PieceType::Queen` in `PieceRenderer`.

2. **Rasterization**
   - `PieceRenderer::render(...)` creates a transparent `QPixmap` sized for both square size and device pixel ratio.
   - `QPainter` with antialiasing draws `QPainterPath` geometry for the queen.

3. **Pixmap cache**
   - `PiecePixmapCache` is the boundary between UI and renderer.
   - Cache key includes:
     - piece type
     - piece color
     - square size
     - device pixel ratio (quantized)
   - Preview UI requests all piece images through this cache.

4. **Resize / DPR behavior**
   - When window/UI requests a piece size at the current DPR, the cache returns existing pixmap or triggers render.
   - Cached pixmaps are reused to avoid expensive repeated path rendering during paint.

## Preview Window Responsibilities

- Shows one large queen preview.
- Shows a matrix of smaller board-like sizes (`32, 48, 64, 96, 128, 192`).
- Renders both white and black variants.
- Paints light/dark square swatches under selected samples.
- Displays runtime status text (DPR, window size, cached count, last render size).

## Future Export Path

Planned extension points:

- Export vector definition to SVG in `exports/svg/`.
- Export raster samples (by size/color/theme) to PNG in `exports/png/`.
- Add quality checks for silhouette readability at low resolutions.

## Eventual Main-App Integration

Intended integration path (future work):

1. Move stable renderer + cache classes into shared chess asset module.
2. Integrate with board paint path in main app.
3. Request pixmaps per board square size + DPR.
4. Invalidate/rebuild cache only when style theme or DPI context changes.
