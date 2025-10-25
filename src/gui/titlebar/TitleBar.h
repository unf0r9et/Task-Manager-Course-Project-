//
// Created by unf0r9et on 24.10.25.
//

#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QMouseEvent>
#include <QWidget>
#include <QDebug>

class QPushButton;

class TitleBar : public QWidget {
    Q_OBJECT

public:
    explicit TitleBar(QWidget *parent = nullptr);

private:
    QPushButton *closeButton;

    //     bool m_dragging = false;
    //     QPoint m_dragPosition;
    //
    // protected:
    //     void mousePressEvent(QMouseEvent *event) override;
    //     void mouseMoveEvent(QMouseEvent *event) override;
    //     void mouseReleaseEvent(QMouseEvent *event) override;
    // };


    QPoint dragPosition;
    bool dragging = false;

protected:
    void mousePressEvent(QMouseEvent *event) override {
        if (event->button() == Qt::LeftButton) {
            dragging = true;
            dragPosition = event->globalPos() - window()->frameGeometry().topLeft();
            event->accept();
        }
    }

    void mouseMoveEvent(QMouseEvent *event) override {
        if (dragging && (event->buttons() & Qt::LeftButton)) {
            window()->move(event->globalPos() - dragPosition);
            event->accept();
            qDebug() << "Move event:" << event->globalPos() << "WINDOW: " << window();
        }
    }

    void mouseReleaseEvent(QMouseEvent *event) override {
        Q_UNUSED(event);
        dragging = false;
    }

};

#endif //TITLEBAR_H
