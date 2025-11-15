#ifndef STYLELOADER_H
#define STYLELOADER_H

class QWidget;
class QString;

class StyleLoader {
public:
    static void loadStyleSheet(QWidget* widget, const QString& path);
};

#endif