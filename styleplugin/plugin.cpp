#include <QtWidgets>

#include "phantomstyle.h"

QPalette loadPalette() {
    QFile jsonFile(QStandardPaths::writableLocation(QStandardPaths::ConfigLocation) + "/phantom.json");
    jsonFile.open(QFile::ReadOnly);
    QJsonObject json = QJsonDocument().fromJson(jsonFile.readAll()).object();

    QColor window(json["window"].toString());
    QColor text(json["text"].toString());
    QColor disabledText(json["disabledText"].toString());
    QColor brightText(json["brightText"].toString());
    QColor highlight(json["highlight"].toString());
    QColor highlightedText(json["highlightedText"].toString());
    QColor base(json["base"].toString());
    QColor alternateBase(json["alternateBase"].toString());
    QColor shadow(json["shadow"].toString());
    QColor button(json["button"].toString());
    QColor disabledButton(json["disabledButton"].toString());
    QColor unreadBadge(json["unreadBadge"].toString());
    QColor unreadBadgeText(json["unreadBadgeText"].toString());
    QColor icon(json["icon"].toString());
    QColor disabledIcon(json["disabledIcon"].toString());
    QColor chatTimestampText(json["chatTimestampText"].toString());

    QPalette pal;
    pal.setColor(QPalette::Window, window);
    pal.setColor(QPalette::WindowText, text);
    pal.setColor(QPalette::Text, text);
    pal.setColor(QPalette::ButtonText, text);
    if (brightText.isValid())
      pal.setColor(QPalette::BrightText, brightText);
    pal.setColor(QPalette::Disabled, QPalette::WindowText, disabledText);
    pal.setColor(QPalette::Disabled, QPalette::Text, disabledText);
    pal.setColor(QPalette::Disabled, QPalette::ButtonText, disabledText);
    pal.setColor(QPalette::Base, base);
    pal.setColor(QPalette::AlternateBase, alternateBase);
    if (shadow.isValid())
      pal.setColor(QPalette::Shadow, shadow);
    pal.setColor(QPalette::Button, button);
    pal.setColor(QPalette::Highlight, highlight);
    pal.setColor(QPalette::HighlightedText, highlightedText);
    if (disabledButton.isValid())
      pal.setColor(QPalette::Disabled, QPalette::Button, disabledButton);
    pal.setColor(QPalette::Disabled, QPalette::Light, Qt::transparent);

  return pal;
}



QT_BEGIN_NAMESPACE

class PhantomStylePlugin : public QStylePlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QStyleFactoryInterface" FILE "phantom.json")
public:
    QStyle *create(const QString &key);
};

QStyle *PhantomStylePlugin::create(const QString &key)
{
    qDebug() << key;
    if (key == "phantom") {

        qApp->setPalette(loadPalette());
        return new PhantomStyle;
    }
    return 0;
}

QT_END_NAMESPACE

#include "plugin.moc"
