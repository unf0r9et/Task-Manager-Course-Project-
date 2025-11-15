#include "StyleLoader.h"
#include <QFile>
#include <QApplication>
#include <QWidget>

void StyleLoader::loadStyleSheet(QWidget* widget, const QString& path) {
    QFile file(path);
    if (file.open(QFile::ReadOnly)) {
        widget->setStyleSheet(file.readAll());
    }
}