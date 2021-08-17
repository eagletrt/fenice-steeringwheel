#ifndef GLOBAL_H
#define GLOBAL_H

#include <QDebug>

class Global : public QObject {
  Q_OBJECT
public:
  Global(QObject *parent = nullptr);
  ~Global();

  void appendLine(const QString &line);

  static Global &instance();
  static void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);

signals:
  void logsChanged(const QString &line);
};

#define sDebug(SCOPE) (QMessageLogger(QT_MESSAGELOG_FILE, QT_MESSAGELOG_LINE, QT_MESSAGELOG_FUNC, SCOPE).debug)()
#define sInfo(SCOPE) (QMessageLogger(QT_MESSAGELOG_FILE, QT_MESSAGELOG_LINE, QT_MESSAGELOG_FUNC, SCOPE).info)()
#define sWarning(SCOPE) (QMessageLogger(QT_MESSAGELOG_FILE, QT_MESSAGELOG_LINE, QT_MESSAGELOG_FUNC, SCOPE).warning)()
#define sCritical(SCOPE) (QMessageLogger(QT_MESSAGELOG_FILE, QT_MESSAGELOG_LINE, QT_MESSAGELOG_FUNC, SCOPE).critical)()
#define sFatal(SCOPE) (QMessageLogger(QT_MESSAGELOG_FILE, QT_MESSAGELOG_LINE, QT_MESSAGELOG_FUNC, SCOPE).fatal)()

#endif // GLOBAL_H
