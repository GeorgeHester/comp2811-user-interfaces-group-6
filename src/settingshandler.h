#ifndef SETTINGSHANDLER_H
#define SETTINGSHANDLER_H

#include <QSettings>
#include <QVariant>

#define ORGANISATION_NAME "vrealcorp"
#define APPLICATION_NAME "vreal"

class SettingsHandler
{
  public:
    SettingsHandler();
    ~SettingsHandler();

    static void setValue(const QString& key, const QVariant& new_value);
    static QVariant getValue(const QString& key, const QVariant& default_value);
    static QString debug();

  private:
    static QSettings* settings;
    static void initalise();
};

#endif // SETTINGSHANDLER_H