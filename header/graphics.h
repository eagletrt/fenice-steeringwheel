#include <QDebug>
#include <QQuickView>

class Graphics : public QObject {
    Q_OBJECT
    QQuickView* view;
public slots:
    void startGraphics();
public:
    Graphics(QQuickView*);
    ~Graphics();
};