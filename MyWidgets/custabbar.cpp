#include "custabbar.h"
#include <QStylePainter>
#include <QStyleOptionTab>
#include <QPixmap>

CusTabBar::CusTabBar() {}

QSize CusTabBar::tabSizeHint(int index) const
{
    QSize s = QTabBar::tabSizeHint(index);
    return s.transposed(); // 修正：返回 transposed 的结果
}

void CusTabBar::paintEvent(QPaintEvent *event)
{
    QStylePainter painter(this);
    QStyleOptionTab opt;

    for (int i = 0; i < count(); ++i)
    {
        initStyleOption(&opt, i);
        painter.drawControl(QStyle::CE_TabBarTabShape, opt);

        painter.save();

        QSize s = opt.rect.size();
        s.transpose();
        QRect r(QPoint(), s);
        r.moveCenter(opt.rect.center());
        opt.rect = r;

        // 旋转标签的中心点
        QPoint c = tabRect(i).center();
        painter.translate(c);
        painter.rotate(90); // 旋转90度
        painter.translate(-c);

        // 绘制标签的图标
        if (!opt.icon.isNull()) {
            QPixmap pixmap = opt.icon.pixmap(16, 16, QIcon::Normal, QIcon::On);
            QRect iconRect(QPoint(-pixmap.height() / 2, -pixmap.width() / 2), pixmap.size());
            painter.drawPixmap(iconRect, pixmap);
        }

        // 绘制标签的文字
        painter.drawControl(QStyle::CE_TabBarTabLabel, opt);

        painter.restore();
    }
}
