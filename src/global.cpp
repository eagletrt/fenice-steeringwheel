#include "global.h"

#include <QVector>

Global::Global(QObject *parent) : QObject(parent) {}
Global::~Global() {}

void Global::appendLine(const QString &line) { emit logsChanged(line); }

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
    global->appendLine(result);
  }
}
