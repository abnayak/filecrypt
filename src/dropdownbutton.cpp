#include "dropdownbutton.h"

DropDownButton::DropDownButton(QObject *parent):QToolButton((QWidget*)parent) {
    this->parent = parent;
    setPopupMode(QToolButton::MenuButtonPopup);
    QObject::connect(this, SIGNAL(triggered(QAction*)), this, SLOT(setDefaultAction(QAction*)));

    // Initialize the actions
    fileBrowser = new QAction(this);
    fileBrowser->setIcon(QIcon(":/File-26.png"));
    fileBrowser->setIconText("File Browser");
    folderBrowser = new QAction(this);
    folderBrowser->setIconText("Folder Browser");

    folderBrowser->setIcon(QIcon(":/Folder-26.png"));

    // Initialize the menu and attach to the button
    buttonMenu = new QMenu(this);
    //buttonMenu->addAction(QIcon(":/File-26.png"), "File Browser",parent, "onFileBrowseButtonClick");
    //buttonMenu->addAction(QIcon(":/Folder-26.png"), "Folder Browser",parent, "onFolderBrowseButtonClick");
    buttonMenu->addAction(fileBrowser);
    buttonMenu->addAction(folderBrowser);

    // Set the menu for the tool button
    setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    setMenu(buttonMenu);
    setDefaultAction(fileBrowser);
    setPopupMode(QToolButton::InstantPopup);
    setFixedSize(QSize(85,27));
    setText(tr("Open"));

    // Connect the actions to tool button slots
    connect(fileBrowser,SIGNAL(triggered()),parent,SLOT(onFileBrowseButtonClick()));
    connect(folderBrowser,SIGNAL(triggered()),parent,SLOT(onFolderBrowseButtonClick()));
}
