#ifndef STEERING_H
#define STEERING_H

#include <QDebug>

#define sDebug(SCOPE)                                                          \
  (QMessageLogger(QT_MESSAGELOG_FILE, QT_MESSAGELOG_LINE, QT_MESSAGELOG_FUNC,  \
                  "[" SCOPE "]")                                               \
       .debug)()

#endif // STEERING_H
