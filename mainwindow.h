//
// Created by mt on 10/5/26.
//

#ifndef UNTITLED1_MAINWINDOW_H
#define UNTITLED1_MAINWINDOW_H
#include <QMainWindow>
class QTextEdit;
class QAction;
class FIleExplorer;
class MainWindow : public QMainWindow {
    Q_OBJECT
public :
    explicit MainWindow(QWidget *parent = nullptr);
private :
    void setupMenuBar();
    void openFile(const QString &filePath);
    QTextEdit *codeEditor = nullptr;
    FIleExplorer *sidebar = nullptr; // Kept so the tree can be hidden/shown again
    QAction *fileTreeAction = nullptr; // View > File Tree toggle, kept in sync with the sidebar
};
#endif //UNTITLED1_MAINWINDOW_H
