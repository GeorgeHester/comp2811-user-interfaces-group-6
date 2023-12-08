#include "settingshandler.h"

QSettings* SettingsHandler::settings = nullptr;

void
SettingsHandler::initalise()
{
    if (SettingsHandler::settings == nullptr)
    {
        SettingsHandler::settings = new QSettings(
          QSettings::Scope::UserScope, ORGANISATION_NAME, APPLICATION_NAME);
    };
};

SettingsHandler::SettingsHandler()
{
    SettingsHandler::initalise();
};

SettingsHandler::~SettingsHandler()
{
    delete SettingsHandler::settings;
    SettingsHandler::settings = nullptr;
};

void
SettingsHandler::setValue(const QString& key, const QVariant& default_value)
{
    SettingsHandler::initalise();
    SettingsHandler::settings->setValue(key, default_value);
};

QVariant
SettingsHandler::getValue(const QString& key, const QVariant& default_value)
{
    SettingsHandler::initalise();
    return SettingsHandler::settings->value(key, default_value);
};

QString
SettingsHandler::debug()
{
    SettingsHandler::initalise();
    return SettingsHandler::settings->fileName();
};