//
// Created by unf0r9et on 29.11.25.
//

#include "CalendarWindow.h"

#include "interfaces/WindowOptions.h"
#include "styleloader/StyleLoader.h"

CalendarWindow::CalendarWindow(QWidget *parent) : QWidget(parent) {
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    setObjectName("CalendarWindow");

    // StyleLoader::loadStyleSheet(this, "");
}
