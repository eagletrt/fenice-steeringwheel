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

#define S_PROPERTY(type, external, internal, capitalized) \
  Q_PROPERTY(type external READ get##capitalized WRITE set##capitalized NOTIFY external##Changed) \
  public: \
    type get##capitalized() const { return internal; } \
    void set##capitalized(const type& value) { \
      if (internal == value) return; \
      internal = value; \
      emit external##Changed(value); \
    } \
    Q_SIGNAL void external##Changed(type value); \
  private: \
    type internal;

#endif // GLOBAL_H
