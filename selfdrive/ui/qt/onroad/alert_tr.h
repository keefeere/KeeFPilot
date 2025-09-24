#pragma once
#include <QString>
#include <QStringList>
#include <map>

struct AlertTranslation {
    QString text1;
    QString text2;
};

inline QMap<QString, AlertTranslation> alertTranslations = {
  {"CalibrationInProgress", {QT_TR_NOOP("Calibration in Progress: %1%"), QT_TR_NOOP("Drive Above %1 km/h")}},
  {"SystemOverheated",      {QT_TR_NOOP("System Overheated"),            QT_TR_NOOP("%1 °C")}},
  {"StartupWarning",        {QT_TR_NOOP("WARNING: This branch is not tested"), QT_TR_NOOP("%1")}},
  {"StartupMessage",        {QT_TR_NOOP("Hop in and buckle up!"),        QT_TR_NOOP("Human-tested, frog-approved 🐸")}}
};



// обʼяви функції прямо тут
inline QString translateAlertText1(const QString &text, const QStringList &params = {});
inline QString translateAlertText2(const QString &text, const QStringList &params = {});

inline QString translateAlertText1(const QString &text, const QStringList &params) {
    auto it = std::find_if(alertTranslations.begin(), alertTranslations.end(),
                           [&text](const auto &pair){ return pair.text1 == text; });

    if (it == alertTranslations.end()) return text;

    QString translated = QObject::tr(it->text1.toUtf8().constData());
    for (int i = 0; i < params.size(); ++i) translated = translated.arg(params[i]);
    return translated;
}

inline QString translateAlertText2(const QString &text, const QStringList &params) {
    auto it = std::find_if(alertTranslations.begin(), alertTranslations.end(),
                           [&text](const auto &pair){ return pair.text2 == text; });

    if (it == alertTranslations.end()) return text;

    QString translated = QObject::tr(it->text2.toUtf8().constData());
    for (int i = 0; i < params.size(); ++i) translated = translated.arg(params[i]);
    return translated;
}
