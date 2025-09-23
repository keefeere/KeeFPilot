#pragma once
#include <QString>
#include <QMap>
#include <QObject>

struct AlertTranslation {
  QString text1;
  QString text2;
};

inline QMap<QString, AlertTranslation> alertTranslations = {
  {"CalibrationInProgress", {QObject::tr("Calibration in Progress: %1%"), QObject::tr("Drive Above %1 km/h")}},
  {"SystemOverheated",      {QObject::tr("System Overheated"),            QObject::tr("%1 °C")}},
  {"StartupWarning",        {QObject::tr("WARNING: This branch is not tested"), QObject::tr("%1")}},
  {"StartupMessage",        {QObject::tr("Hop in and buckle up!"),        QObject::tr("Human-tested, frog-approved 🐸")}}
};