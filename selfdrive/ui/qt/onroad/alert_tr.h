#pragma once
#include <QString>
#include <QStringList>
#include <map>
#include <QCoreApplication>

struct AlertTranslation {
    const char *text1;
    const char *text2;
};

inline QMap<QString, AlertTranslation> alertTranslations = {
  {"CalibrationInProgress", {QT_TRANSLATE_NOOP("Alerts", "Calibration in Progress: %1%"), QT_TRANSLATE_NOOP("Alerts", "Drive Above %1 km/h")}},
  {"SystemOverheated",      {QT_TRANSLATE_NOOP("Alerts", "System Overheated"),            QT_TRANSLATE_NOOP("Alerts", "%1 °C")}},
  {"StartupWarning",        {QT_TRANSLATE_NOOP("Alerts", "WARNING: This branch is not tested"), QT_TRANSLATE_NOOP("Alerts", "%1")}},
  {"StartupMessage",        {QT_TRANSLATE_NOOP("Alerts", "Hop in and buckle up!"),        QT_TRANSLATE_NOOP("Alerts", "Human-tested, frog-approved 🐸")}}
};


inline QString translateAlertText1(const QString &text, const QStringList &params = {});
inline QString translateAlertText2(const QString &text, const QStringList &params = {});

inline QString translateAlertText1(const QString &text, const QStringList &params) {
    auto it = std::find_if(alertTranslations.begin(), alertTranslations.end(),
                           [&text](const auto &pair){ return pair.text1 == text; });

    if (it == alertTranslations.end()) return text;

    QString translated = QCoreApplication::translate("Alerts", it->text1);
    for (int i = 0; i < params.size(); ++i) translated = translated.arg(params[i]);
    return translated;
}

inline QString translateAlertText2(const QString &text, const QStringList &params) {
    auto it = std::find_if(alertTranslations.begin(), alertTranslations.end(),
                           [&text](const auto &pair){ return pair.text2 == text; });

    if (it == alertTranslations.end()) return text;

    QString translated = QCoreApplication::translate("Alerts", it->text2);
    for (int i = 0; i < params.size(); ++i) translated = translated.arg(params[i]);
    return translated;
}
