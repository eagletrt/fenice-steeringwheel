#include "global.h"

#include <QVector>

QString timestamp_conversion(long int value) {
  time_t canlib_build_time = value;
  struct tm *ds = localtime(&canlib_build_time);
  char buffer[256];
  strftime(buffer, 256, "%x - %I:%M%p", ds);
  return QString(buffer);
}

Global::Global(QObject *parent) : QObject(parent) {}
Global::~Global() {}

void Global::append_line(const QString &line) { emit logs_changed(line); }

Q_GLOBAL_STATIC(Global, global);

Global &Global::instance() { return *global; }

void Global::messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
  QByteArray message = msg.toLocal8Bit();
  const char *category = context.category ? context.category : "steering";

  QString result;
  QTextStream stream(&result);

  switch (type) {
  case QtDebugMsg:
    stream << "[dbg:" << category << "]: ";
    break;
  case QtInfoMsg:
    stream << "[inf:" << category << "]: ";
    break;
  case QtWarningMsg:
    stream << "[war:" << category << "]: ";
    break;
  case QtCriticalMsg:
    stream << "[crt:" << category << "]: ";
    break;
  case QtFatalMsg:
    stream << "[fat:" << category << "]: ";
    break;
  }
  stream << message;

#ifdef S_LOG_FILE_POSITION
  const char *file = context.file ? context.file : "";
  const char *function = context.function ? context.function : "";
  int line = context.line;
  stream << "\t\t\t(" << file << ":" << line << " " << function << ")";
#endif

  QByteArray resultBytes = result.toLocal8Bit();
  fprintf(stderr, "%s\n", resultBytes.constData());

  if (global.exists()) {
    global->append_line(result);
  }
}
