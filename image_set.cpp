
#include "image_set.h"

ImageSet::ImageSet()
{
}

ImageSet::~ImageSet()
{
}

void ImageSet::show(const QString& name, AnimatedImage& img)
{
    printf("'%s': (%d, %d) %d x %d\n", name.toLatin1().data(),
           img.m_x, img.m_y, img.m_image.width(), img.m_image.height());
}

void ImageSet::difference(AnimatedImage& img)
{
    QImage& base = m_baseline;
    QImage& active = img.m_image;
    int nx = base.width();
    int ny = base.height();
    int x1 = 0;
    int y1 = 0;
    int x2 = base.width() - 1;
    int y2 = base.height() - 1;
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
        img.m_x = x1;
        img.m_y = y1;
        img.m_image = active.copy(x1, y1, x2 - x1 + 1, y2 - y1 + 1);
    } else {
        img.m_x = 0;
        img.m_y = 0;
        img.m_image = QImage(); // Nothing to draw if no difference
    }
}
