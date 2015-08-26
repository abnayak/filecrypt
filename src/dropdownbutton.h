#ifndef DROPDOWNBUTTON_H
#define DROPDOWNBUTTON_H

#include <QToolButton>
#include <QAction>
#include <QIcon>
#include <QMenu>
#include <QFileDialog>
#include <QMetaObject>

class DropDownButton:public QToolButton
{

private:
    QObject *parent;
    QAction *fileBrowser;
    QAction *folderBrowser;
    QMenu *buttonMenu;

public:
    DropDownButton(QObject *parent = 0);
};

#endif // DROPDOWNBUTTON_H
