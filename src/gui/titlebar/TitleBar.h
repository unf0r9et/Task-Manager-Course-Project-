//
// Created by unf0r9et on 24.10.25.
//

#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QMouseEvent>
#include <QWidget>

class QPushButton;

class TitleBar : public QWidget {
    Q_OBJECT

public:
    explicit TitleBar(QWidget *parent = nullptr);

private:
    QPushButton *closeButton;
//     QPoint dragPosition;
//     bool dragging = false;
//
// protected:
//     void mousePressEvent(QMouseEvent *event) override {
//         if(event->button() == Qt::LeftButton) {
//             dragging = true;
//             dragPosition = event->globalPos() - parentWidget()->frameGeometry().topLeft();
//             event->accept();
//         }
//     }
//
//     void mouseMoveEvent(QMouseEvent *event) override {
//         if(dragging && (event->buttons() & Qt::LeftButton)) {
//             parentWidget()->move(event->globalPos() - dragPosition);
//             event->accept();
//         }
//     }
//
//     void mouseReleaseEvent(QMouseEvent *event) override {
//         Q_UNUSED(event);
//         dragging = false;
//     }

};


#endif //TITLEBAR_H
