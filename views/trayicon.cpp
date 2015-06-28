#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>

#include "trayicon.h"


TrayIcon::TrayIcon(QObject *parent) : QSystemTrayIcon(parent),
    m_icons()
{
    m_menu = new QMenu(nullptr);

    m_actions.insert(active,tr("activate"));
    m_actions.insert(quit, tr("quit"));
    m_actions.insert(settings, tr("settings"));

    act = m_menu->addAction(m_actions.value(active));
    sett = m_menu->addAction(m_actions.value(settings));
    qt = m_menu->addAction(m_actions.value(quit));

    connect(act, &QAction::triggered, [this] () {emit menuTriggered(active);});
    connect(sett, &QAction::triggered, [this] () {emit menuTriggered(settings);});
    connect(qt, &QAction::triggered, [this] () {emit menuTriggered(quit);});

    setContextMenu(m_menu);

    m_icons.insert(gray, ":/images/images/gray.png");
    m_icons.insert(green,":/images/images/green.png");
    m_icons.insert(red, ":/images/images/red.png");
    changeIcon(green);
}

void
TrayIcon::changeIcon(Color color){
    setIcon(QIcon(m_icons.value(color)));
}

void
TrayIcon::changeToolTip(QString tooltip){
    setToolTip(tooltip);
}



TrayIcon::~TrayIcon()
{
    delete m_menu;
}

