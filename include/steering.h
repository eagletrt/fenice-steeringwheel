#ifndef STEERING_H
#define STEERING_H

#include <QDebug>

class Steering : public QObject {
  Q_OBJECT
  Q_PROPERTY(QList<QString> logs MEMBER m_logs NOTIFY logsChanged)

public:
  Steering(QObject *parent = nullptr);
  ~Steering();

  void appendLine(const QString &line);

  static Steering &instance();
  static void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);

signals:
  void logsChanged(const QString &line);

private:
  QList<QString> m_logs;
};

#define sDebug(SCOPE) (QMessageLogger(QT_MESSAGELOG_FILE, QT_MESSAGELOG_LINE, QT_MESSAGELOG_FUNC, SCOPE).debug)()
#define sInfo(SCOPE) (QMessageLogger(QT_MESSAGELOG_FILE, QT_MESSAGELOG_LINE, QT_MESSAGELOG_FUNC, SCOPE).info)()
#define sWarning(SCOPE) (QMessageLogger(QT_MESSAGELOG_FILE, QT_MESSAGELOG_LINE, QT_MESSAGELOG_FUNC, SCOPE).warning)()
#define sCritical(SCOPE) (QMessageLogger(QT_MESSAGELOG_FILE, QT_MESSAGELOG_LINE, QT_MESSAGELOG_FUNC, SCOPE).critical)()
#define sFatal(SCOPE) (QMessageLogger(QT_MESSAGELOG_FILE, QT_MESSAGELOG_LINE, QT_MESSAGELOG_FUNC, SCOPE).fatal)()

#endif // STEERING_H
