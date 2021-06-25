
#include "image_set.h"

ImageSet::ImageSet()
{
}

ImageSet::~ImageSet()
{
}


void ImageSet::difference(AnimatedImage& img, int& x1, int& y1, int& x2, int& y2)
{
    QImage& base = m_baseline.m_image;
    QImage& active = img.m_image;
    int nx = base.width();
    int ny = base.height();
    x1 = 0;
    y1 = 0;
    x2 = base.width() - 1;
    y2 = base.height() - 1;
    if (nx != active.width()) {
        printf("<<< ImageSet::difference: images are different width %d vs %d >>>\n", nx, active.width());
        return;
    }
    if (ny != active.height()) {
        printf("<<< ImageSet::difference: images are different height %d vs %d >>>\n", ny, active.height());
        return;
    }
    int minx = x2;
    int miny = y2;
    int maxx = x1;
    int maxy = y1;
    for (int j = 0; j < ny; j++) {
        const uchar* base_line = base.constScanLine(j);
        const uchar* active_line = active.constScanLine(j);
        for (int i = 0; i < nx; i++) {
            if ( base_line[4 * i]     != active_line[4 * i]
              || base_line[4 * i + 1] != active_line[4 * i + 1]
              || base_line[4 * i + 2] != active_line[4 * i + 2] ) {
                maxx = std::max(maxx, i);
                minx = std::min(minx, i);
                maxy = std::max(maxy, j);
                miny = std::min(miny, j);
            }
        }
    }
    if (maxx != x1 || minx != x2 || maxy != y1 || miny != y2) {
        x1 = minx;
        x2 = maxx;
        y1 = miny;
        y2 = maxy;
    }
}