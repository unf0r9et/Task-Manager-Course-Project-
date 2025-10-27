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
