//
// Created by unf0r9et on 15.11.25.
//

#include "../windows/EditTasks.h"
#include "interfaces/WindowOptions.h"
#include "styleloader/StyleLoader.h"

EditTasks::EditTasks(QWidget *parent) : QWidget(parent) {
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    setObjectName("EditTasks");

    StyleLoader::loadStyleSheet(this, "");
}
