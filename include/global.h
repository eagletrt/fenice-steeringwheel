#ifndef GLOBAL_H
#define GLOBAL_H

#include <QDebug>
#include <QMetaEnum>

QString timestamp_conversion(long int value);

class Global : public QObject {
  Q_OBJECT
public:
  Global(QObject *parent = nullptr);
  ~Global();

  void append_line(const QString &line);

  static Global &instance();
  static void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);

signals:
  void logs_changed(const QString &line);
};

template <typename QEnum> inline QString enum_to_string(const QEnum value) {
  return QString(QMetaEnum::fromType<QEnum>().valueToKey(value));
}

#define sDebug(SCOPE) (QMessageLogger(QT_MESSAGELOG_FILE, QT_MESSAGELOG_LINE, QT_MESSAGELOG_FUNC, SCOPE).debug)()
#define sInfo(SCOPE) (QMessageLogger(QT_MESSAGELOG_FILE, QT_MESSAGELOG_LINE, QT_MESSAGELOG_FUNC, SCOPE).info)()
#define sWarning(SCOPE) (QMessageLogger(QT_MESSAGELOG_FILE, QT_MESSAGELOG_LINE, QT_MESSAGELOG_FUNC, SCOPE).warning)()
#define sCritical(SCOPE) (QMessageLogger(QT_MESSAGELOG_FILE, QT_MESSAGELOG_LINE, QT_MESSAGELOG_FUNC, SCOPE).critical)()
#define sFatal(SCOPE) (QMessageLogger(QT_MESSAGELOG_FILE, QT_MESSAGELOG_LINE, QT_MESSAGELOG_FUNC, SCOPE).fatal)()

#define SS_CAT(A, B) A##B
#define SS_EXPAND(...) __VA_ARGS__

#define SS_VA_ARG_SIZE(...) SS_EXPAND(SS_APPLY_ARG_N((SS_ZERO_ARGS_DETECT(__VA_ARGS__), SS_RSEQ_N)))

#define SS_ZERO_ARGS_DETECT(...) SS_EXPAND(SS_ZERO_ARGS_DETECT_PREFIX_##__VA_ARGS__##_ZERO_ARGS_DETECT_SUFFIX)
#define SS_ZERO_ARGS_DETECT_PREFIX__ZERO_ARGS_DETECT_SUFFIX , , , , , , , , , , , 0

#define SS_APPLY_ARG_N(ARGS) SS_EXPAND(SS_ARG_N ARGS)
#define SS_ARG_N(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, N, ...) N
#define SS_RSEQ_N 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0

#define SS_OVERLOAD_SELECT(NAME, NUM) SS_CAT(NAME##_, NUM)
#define SS_MACRO_OVERLOAD(NAME, ...) SS_OVERLOAD_SELECT(NAME, SS_VA_ARG_SIZE(__VA_ARGS__))(__VA_ARGS__)

#define S_PROPERTY(...) SS_MACRO_OVERLOAD(S_PROPERTY, __VA_ARGS__)

#define S_PROPERTY_2(type, name) _S_PROPERTY(type, name, )

#define S_PROPERTY_3(type, name, def) _S_PROPERTY(type, name, = def)

#define _S_PROPERTY(type, name, init)                                                                                  \
  Q_PROPERTY(type name READ name WRITE set_##name NOTIFY name##_changed)                                               \
public:                                                                                                                \
  type name() const { return m_##name; }                                                                               \
  Q_SLOT void set_##name(const type &value) {                                                                          \
    if (m_##name == value)                                                                                             \
      return;                                                                                                          \
    m_##name = value;                                                                                                  \
    emit name##_changed(value);                                                                                        \
  }                                                                                                                    \
  Q_SIGNAL void name##_changed(type value);                                                                            \
                                                                                                                       \
private:                                                                                                               \
  type m_##name init;

#endif // GLOBAL_H
