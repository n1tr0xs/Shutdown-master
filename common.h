#ifndef COMMON_H
#define COMMON_H

#include <QDebug>

#ifdef QT_DEBUG
    #define DEBUG(x) qDebug() << x
#else
    #define DEBUG(x)
#endif

#endif // COMMON_H
