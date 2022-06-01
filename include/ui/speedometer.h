#ifndef SPEEDOMETER_H
#define SPEEDOMETER_H

#include <QObject>
#include <QQuickPaintedItem>

const qreal SPEEDOMETER_MAXIMUM_SPEED = 180;

class Speedometer : public QQuickPaintedItem {
  Q_OBJECT

  Q_PROPERTY(qreal speedometerSize READ getSpeedometerSize WRITE setSpeedometerSize NOTIFY speedometerSizeChanged)
  Q_PROPERTY(qreal startAngle READ getStartAngle WRITE setStartAngle NOTIFY startAngleChanged)
  Q_PROPERTY(qreal alignAngle READ getAlignAngle WRITE setAlignAngle NOTIFY alignAngleChanged)
  Q_PROPERTY(qreal lowestRange READ getLowestRange WRITE setLowestRange NOTIFY lowestRangeChanged)
  Q_PROPERTY(qreal highestRange READ getHighestRange WRITE setHighestRange NOTIFY highestRangeChanged)
  Q_PROPERTY(qreal speed READ getSpeed WRITE setSpeed NOTIFY speedChanged)
  Q_PROPERTY(int arcWidth READ getArcWidth WRITE setArcWidth NOTIFY arcWidthChanged)
  Q_PROPERTY(QColor outerColor READ getOuterColor WRITE setOuterColor NOTIFY outerColorChanged)
  Q_PROPERTY(QColor innerColor READ getInnerColor WRITE setInnerColor NOTIFY innerColorChanged)
  Q_PROPERTY(QColor textColor READ getTextColor WRITE setTextColor NOTIFY textColorChanged)
  Q_PROPERTY(QColor backgroundColor READ getBackgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)

public:
  Speedometer(QQuickItem *parent = 0);
  virtual void paint(QPainter *painter);

  qreal getSpeedometerSize();
  qreal getStartAngle();
  qreal getAlignAngle();
  qreal getLowestRange();
  qreal getHighestRange();
  qreal getSpeed();
  int getArcWidth();
  QColor getOuterColor();
  QColor getInnerColor();
  QColor getTextColor();
  QColor getBackgroundColor();

  void setSpeedometerSize(qreal size);
  void setStartAngle(qreal startAngle);
  void setAlignAngle(qreal angle);
  void setLowestRange(qreal losbwestRange);
  void setHighestRange(qreal highestRange);
  void setSpeed(qreal speed);
  void setArcWidth(int arcWidth);
  void setOuterColor(QColor outerColor);
  void setInnerColor(QColor innerColor);
  void setTextColor(QColor textColor);
  void setBackgroundColor(QColor backgroundColor);

signals:
  void speedometerSizeChanged();
  void startAngleChanged();
  void alignAngleChanged();
  void lowestRangeChanged();
  void highestRangeChanged();
  void speedChanged();
  void arcWidthChanged();
  void outerColorChanged();
  void innerColorChanged();
  void textColorChanged();
  void backgroundColorChanged();

private:
  qreal m_SpeedometerSize = 470;
  qreal m_StartAngle = 50;
  qreal m_AlignAngle = 360 - (m_StartAngle * 3);
  qreal m_LowestRange = 0;
  qreal m_HighestRange = SPEEDOMETER_MAXIMUM_SPEED;
  qreal m_Speed = 2340;
  int m_ArcWidth = 10;
  QColor m_OuterColor = QColor(0x4F4F4F);
  QColor m_InnerColor = QColor(0x323232);
  QColor m_TextColor = QColor(0xFFFFFF);
  QColor m_BackgroundColor = Qt::transparent;
};

#endif // SPEEDOMETER_H
