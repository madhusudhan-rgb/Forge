#include "fileexplorer.h"
#include <QDir>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <qmessagebox.h>

FIleExplorer::FIleExplorer(QWidget *parent) : QWidget(parent) { // Changed to FIleExplorer
    layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    // Header row: title + the X button that closes the whole sidebar
    QWidget *header = new QWidget(this);
    QHBoxLayout *headerLayout = new QHBoxLayout(header);
    headerLayout->setContentsMargins(6, 4, 4, 4);
    headerLayout->setSpacing(4);


    QLabel *titleLabel = new QLabel("Explorer", header);
    headerLayout->addWidget(titleLabel);
    headerLayout->addStretch();

    QPushButton *closeButton = new QPushButton("X", header);
    closeButton->setFixedSize(20, 20);
    closeButton->setFocusPolicy(Qt::NoFocus);
    closeButton->setFlat(true);
    headerLayout->addWidget(closeButton);
    layout->addWidget(header);

    treeView = new QTreeView(this);
    layout->addWidget(treeView);

    fileModel = new QFileSystemModel(this); // Matches header name
    fileModel->setRootPath(QDir::rootPath());

    treeView->setModel(fileModel);

    treeView->setColumnHidden(1, true);
    treeView->setColumnHidden(2, true);
    treeView->setColumnHidden(3, true);

    connect(closeButton, &QPushButton::clicked, this, &FIleExplorer::closeRequested);
    // 'activated' fires on double-click AND on Enter/F2, so one connection is enough
    // (connecting doubleClicked as well would open every file twice)
    connect(treeView, &QTreeView::activated, this, &FIleExplorer::handleIndex);
}

void FIleExplorer::openFolder(const QString &path) { // Changed to FIleExplorer
    treeView->setRootIndex(fileModel->setRootPath(path)); // Matches header name
}

void FIleExplorer::handleIndex(const QModelIndex &index) {
    if (!index.isValid() || !fileModel->fileInfo(index).isFile()) {
        return; // Directories just expand/collapse, only files go to the editor
    }
    emit fileActivated(fileModel->filePath(index));
}
