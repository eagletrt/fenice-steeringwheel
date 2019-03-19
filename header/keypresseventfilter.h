#ifndef KEYPRESSEVENTFILTER_H
#define KEYPRESSEVENTFILTER_H

#include <QObject>

class KeyPressEventFilter : public QObject {

    Q_OBJECT

    public:
        explicit KeyPressEventFilter(QObject* parent = nullptr);

    protected: 
        bool eventFilter(QObject * obj, QEvent *event) override;

    signals: 
        void keyboardBtnClicked(int btnID);
};

#endif // KEYPRESSEVENTFILTER_H


