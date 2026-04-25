# Piece Language (Draft)

## Normalized Coordinate System

All procedural pieces should be authored in a normalized coordinate space (`1000 x 1000`) and later scaled to target square sizes.

Benefits:
- Consistent proportions across all rendered resolutions.
- Easier style iteration with shared constants.
- Predictable stroke scaling and silhouette checks.

## Silhouette Priority

At chess-board scales, silhouette recognition matters more than internal detail.

Design constraints:
- Piece identity must remain legible at 32px and 48px.
- Internal decorations should never overpower the outer contour.
- Distinct crown/head/top motifs should disambiguate pieces quickly.

## Calligraphic / Branching-Line Direction

The long-term visual language aims for:
- Calligraphy-inspired flow lines.
- Branching/stem-like rhythm in body details.
- Organic structural motifs without sacrificing geometric clarity.

## Queen Concept (Planned Evolution)

Current prototype queen is a placeholder geometry used to validate pipeline behavior.

Target conceptual evolution:
- **Star-origin influence** in upper crown geometry.
- **Calligraphy-like body** with tapered, elegant negative spaces.
- **Flower-crown motif** that remains readable at small board sizes.

## Legibility Requirement

Every revision must be tested at multiple piece sizes (`32, 48, 64, 96, 128, 192`) on both light and dark square backgrounds.

If style refinements reduce readability at lower sizes, silhouette simplification takes precedence over decorative complexity.
