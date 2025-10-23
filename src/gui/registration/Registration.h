//
// Created by unf0r9et on 23.10.25.
//

#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <QWidget>


class Registration : public QWidget {
    Q_OBJECT

public:
    explicit Registration(QWidget *parent = nullptr);

signals:
    void authorizationRequested();

private:
    void backToAuthorization();
};


#endif //REGISTRATION_H
