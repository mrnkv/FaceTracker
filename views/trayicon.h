#ifndef TRAYICON_H
#define TRAYICON_H

#include <QSystemTrayIcon>
#include <QMap>


enum Color {green, gray, red};
enum Action {active, quit, settings};

class QMenu;
class QAction;

class TrayIcon : public QSystemTrayIcon
{
    Q_OBJECT
public:
    explicit TrayIcon(QObject *parent = 0);
    ~TrayIcon();

signals:
    void menuTriggered(Action);

public slots:
    void changeIcon(Color color);
    void changeToolTip(QString tooltip);

private:
    QMap<Color, QString> m_icons;
    QMap<Action, QString> m_actions;
    QAction *act, *qt, *sett;
    QMenu *m_menu;
};

#endif // TRAYICON_H
