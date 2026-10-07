//
// Created by madhusudhan on 10/5/26.
//
#include "../mainwindow.h"
#include "../settingswindow.h"
#include "sidebar.h"
#include "fileexplorer.h"
#include <QSplitter>
#include <QTextEdit>
#include <QMenuBar>
#include <QMenu>
#include <QFileDialog>
#include <QDebug>
#include <QAction>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    // Set up the window basics
    setWindowTitle("Strata");
    resize(1200, 800); // Expanded baseline width to accommodate the vertical nav panel cleanly

    // 1. Create a top-level master layout container widget
    QWidget *centralWidget = new QWidget(this);
    QHBoxLayout *masterLayout = new QHBoxLayout(centralWidget);
    masterLayout->setContentsMargins(0, 0, 0, 0); // Eliminates padding gap styles around outer screen boundaries
    masterLayout->setSpacing(0);                 // Eliminates gaps between the sidebar panel and splitter container

    // 2. Instantiate your global Sidebar (Permanent Navbar layout)
    Sidebar *neoSidebar = new Sidebar(centralWidget);

    // 3. Create the horizontal splitter for the flexible workspace contents
    QSplitter *workspaceSplitter = new QSplitter(Qt::Horizontal, centralWidget);
    workspaceSplitter->setHandleWidth(1);

    // 4. Set up your file explorer inside the resizable workspace area
    sidebar = new FIleExplorer(workspaceSplitter);
    sidebar->openFolder(QDir::currentPath());
    workspaceSplitter->addWidget(sidebar);

    // 5. Set up your central code editor workspace inside the splitter
    QTextEdit *editor = new QTextEdit(workspaceSplitter);
    codeEditor = editor;
    workspaceSplitter->addWidget(editor);

    // Enforce split engine behavior settings
    workspaceSplitter->setStretchFactor(0, 0); // File Explorer doesn't dynamically bloat
    workspaceSplitter->setStretchFactor(1, 1); // Code Editor takes up all remaining splitter balance layout spaces

    // 6. Hook components up to the master un-collapsible horizontal frame
    masterLayout->addWidget(neoSidebar, 0);       // Stretch factor 0 keeps navbar width strictly manual
    masterLayout->addWidget(workspaceSplitter, 1); // Splitter expands fluidly to fill the rest of the window screen

    setCentralWidget(centralWidget);

    // Double-clicking a file in the tree loads it into the editor
    connect(sidebar, &FIleExplorer::fileActivated, this, &MainWindow::openFile);

    // The X button on the sidebar header hides just the tree view view frame, keeping the nav panel safe
    connect(sidebar, &FIleExplorer::closeRequested, sidebar, &QWidget::hide);

    // Initialize the menu bar
    setupMenuBar();
}

void MainWindow::setupMenuBar() {
    QMenuBar *menuBar = this->menuBar();

    //  File
    QMenu *fileMenu = menuBar->addMenu("&File");
        QAction *viewFileAction = fileMenu->addAction("&Open File");
        connect(viewFileAction, &QAction::triggered ,this, [this]( ) {
           QString filePath = QFileDialog::getOpenFileName(this, "Open File", "", "Text Files (*.txt);;All Files (*)");
            if (!filePath.isEmpty()) {
                qDebug() << "Selected" << filePath;
                openFile(filePath); // Actually show the picked file in the editor
            } else {
                qDebug() << "No file selected";
            }
        });
        QAction *viewFolderAction = fileMenu->addAction("Open F&older...");
        connect(viewFolderAction, &QAction::triggered, this, [this]() {
            QString folderPath = QFileDialog::getExistingDirectory(this, "Open Folder", "");
            if (!folderPath.isEmpty()) {
                qDebug() << "Selected" << folderPath;
                sidebar->openFolder(folderPath); // Point the tree at the chosen folder
                if (fileTreeAction && !fileTreeAction->isChecked()) {
                    fileTreeAction->setChecked(true); // Bring the tree back if it was hidden
                }
            } else {
                qDebug() << "No folder selected";
            }
        });

            QAction *sAveAction = fileMenu->addAction("&Save as");
            connect(sAveAction, &QAction::triggered, this, [this]() {
                QString filePath = QFileDialog::getSaveFileName(this, "Save File As", "", "Text Files (*.txt);;All Files (*)");
                if (!filePath.isEmpty()) {
                    QFile file(filePath);
                    if (file.open(QFile::WriteOnly | QFile::Text)) {
                        QTextStream out(&file);
                        out << codeEditor->toPlainText();
                        file.close();
                        QMessageBox::information(this, "Success", "File successfully saved!");
                    } else {
                        QMessageBox::warning(this, "Error", "Could not save file to path.");
                    }
                }
            });
        QAction *saveAction = fileMenu->addAction("&Save");
            connect(saveAction, &QAction::triggered, this, [this]() {
                QString filePath = QFileDialog::getSaveFileName(this, "Save File", "", "Text Files (*.txt);;All Files (*)");
                if (!filePath.isEmpty()) {
                    QFile file(filePath);
                    if (file.open(QFile::WriteOnly | QFile::Text)) {
                        QTextStream out(&file);
                        out << codeEditor->toPlainText();
                        file.close();
                        QMessageBox::information(this, "Success", "File successfully saved!");
                    } else {
                        QMessageBox::warning(this, "Error", "Could not save file to path.");
                    }
                }
            });


                QAction *exitAction = fileMenu->addAction("E&xit");
                exitAction->setShortcut(QKeySequence::Quit);

                connect(exitAction, &QAction::triggered, this, [this]() {
                    int reply = QMessageBox::warning(this, "Confirm Exit",
                                                     "Do you want to close Strata?",
                                                     QMessageBox::Yes | QMessageBox::No);
                    if (reply == QMessageBox::Yes) {
                        this->close();
                    }
                });

    // Settings options and the view button in the topmenu
    QMenu *viewMenu = menuBar->addMenu("&View");
            // Open/hide the file tree from the topmenu (Ctrl+B, like most editors)
            fileTreeAction = viewMenu->addAction("&Open File Tree");
            fileTreeAction->setCheckable(true);
            fileTreeAction->setChecked(true); // The tree starts out visible
            fileTreeAction->setShortcut(QKeySequence("Ctrl+B"));
            connect(fileTreeAction, &QAction::toggled, this, [this](bool visible) {
                sidebar->setVisible(visible); // Show the explorer when checked, hide it when not
            });
            // The X on the sidebar header hides it too; uncheck the menu item so both stay in sync
            connect(sidebar, &FIleExplorer::closeRequested, this, [this]() {
                if (fileTreeAction && fileTreeAction->isChecked()) {
                    fileTreeAction->setChecked(false);
                }
            });
            QAction *viewAction = viewMenu->addAction("Settings");
                connect(viewAction, &QAction::triggered, this, [this]() {
                        SettingsDialog dialog(this);
                        dialog.exec();
                });
            QAction *aboutAction = viewMenu->addAction("A&bout");
            connect(aboutAction, &QAction::triggered, this, [this]() {
                int reply = QMessageBox::question(this,
                                                  "Struct",
                                                  "V0.0.1\nVisit here for the repository",
                                                  QMessageBox::Yes | QMessageBox::No);
                if (reply == QMessageBox::Yes) {
                    QDesktopServices::openUrl(QUrl("https://github.com"));
                }
            });
}

void MainWindow::openFile(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Strata", "Could not open file:\n" + filePath);
        return;
    }
    QTextStream in(&file);
    codeEditor->setPlainText(in.readAll());
    file.close();
}
