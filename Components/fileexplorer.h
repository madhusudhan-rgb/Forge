#ifndef FILEEXPLORER_H
#define FILEEXPLORER_H

#include <QWidget>
#include <QTreeView>
#include <QFileSystemModel>
#include <QVBoxLayout>

class FIleExplorer : public QWidget { // Made sure 'I' is uppercase
    Q_OBJECT

public:
    explicit FIleExplorer(QWidget *parent = nullptr); // Made sure 'I' is uppercase
    void openFolder(const QString &path);

signals:
    void fileActivated(const QString &filePath); // A file row was double-clicked/entered
    void closeRequested();                       // The X button on the header was pressed

private:
    void handleIndex(const QModelIndex &index);

    QVBoxLayout *layout;
    QTreeView *treeView;
    QFileSystemModel *fileModel; // Fixed spelling from QFileSytemModel to QFileSystemModel
};

#endif // FILEEXPLORER_H
