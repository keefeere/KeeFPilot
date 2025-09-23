#include "alerts_tr.h"

// Можна додатково додати функцію-помічник для підстановки параметрів
inline QString translateAlertText1(const QString &key, const QStringList &params = {}) {
    if (!alertTranslations.contains(key)) return key;
    QString text = alertTranslations[key].text1;
    for (int i = 0; i < params.size(); ++i) {
        text = text.arg(params[i]);
    }
    return text;
}

inline QString translateAlertText2(const QString &key, const QStringList &params = {}) {
    if (!alertTranslations.contains(key)) return "";
    QString text = alertTranslations[key].text2;
    for (int i = 0; i < params.size(); ++i) {
        text = text.arg(params[i]);
    }
    return text;
}