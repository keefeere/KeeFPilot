#include "alerts_tr.h"

inline QString translateAlertText1(const QString &text, const QStringList &params = {}) {
    // Шукаємо переклад по значенню text, а не по ключу
    auto it = std::find_if(alertTranslations.begin(), alertTranslations.end(),
                           [&text](const auto &pair){ return pair.text1 == text; });

    if (it == alertTranslations.end()) return text;

    QString translated = it->text1;
    for (int i = 0; i < params.size(); ++i)
        translated = translated.arg(params[i]);

    return translated;
}

inline QString translateAlertText2(const QString &text, const QStringList &params = {}) {
    auto it = std::find_if(alertTranslations.begin(), alertTranslations.end(),
                           [&text](const auto &pair){ return pair.text2 == text; });

    if (it == alertTranslations.end()) return text;

    QString translated = it->text2;
    for (int i = 0; i < params.size(); ++i)
        translated = translated.arg(params[i]);

    return translated;
}