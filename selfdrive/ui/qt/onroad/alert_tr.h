#pragma once
#include <QString>
#include <QMap>
#include <QObject>
#include <QStringList>
#include <map>

struct AlertTranslation {
    QString text1;
    QString text2;
};

extern std::map<QString, AlertTranslation> alertTranslations;

// обʼяви функції прямо тут
inline QString translateAlertText1(const QString &text, const QStringList &params = {});
inline QString translateAlertText2(const QString &text, const QStringList &params = {});



inline QMap<QString, AlertTranslation> alertTranslations = {
  {"CalibrationInProgress", {QObject::tr("Calibration in Progress: %1%"), QObject::tr("Drive Above %1 km/h")}},
  {"SystemOverheated",      {QObject::tr("System Overheated"),            QObject::tr("%1 °C")}},
  {"StartupWarning",        {QObject::tr("WARNING: This branch is not tested"), QObject::tr("%1")}},
  {"StartupMessage",        {QObject::tr("Hop in and buckle up!"),        QObject::tr("Human-tested, frog-approved 🐸")}}
};