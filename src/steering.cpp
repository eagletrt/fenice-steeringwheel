#include "steering.h"

#include <QVector>

Steering::Steering(QObject *parent) : QObject(parent) {}
Steering::~Steering() {}

void Steering::appendLine(const QString &line) {
  m_logs.append(line);
  emit logsChanged(line);
}

Q_GLOBAL_STATIC(Steering, steering);

Steering &Steering::instance() {
  return *steering;
}

void Steering::messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg){
  QByteArray message = msg.toLocal8Bit();
  const char *category = context.category ? context.category : "global";

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

  if (steering.exists()) {
      steering->appendLine(result);
    }
}
