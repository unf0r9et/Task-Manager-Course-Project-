#include <qfile.h>
#include <QWidget>
//
// Created by unf0r9et on 24.10.25.
//


namespace StyleLoader {
    inline void loadStyleSheet(QWidget *widget, const QString &path) {
        QFile file(path);
        if(file.open(QFile::ReadOnly | QFile::Text)) {
            const QString styleSheet = QLatin1String(file.readAll());
            widget->setStyleSheet(styleSheet);
        }
    }
}
