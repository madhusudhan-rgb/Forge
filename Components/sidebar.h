//
// Created by mt on 10/6/26.
//

#ifndef UNTITLED1_SIDEBAR_H
#define UNTITLED1_SIDEBAR_H
#pragma once
#include <QFrame>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QListWidget>

class Sidebar : public QFrame {
    Q_OBJECT // Necessary for handling custom button signals/slots

public:
    explicit Sidebar(QWidget *parent = nullptr);

signals:
    void fileTreeToggleRequested();
    void settingsRequested();

private:
    void setupLayout();
    void applyStyles();

    // Visual elements inside your sidebar
    QVBoxLayout *m_layout;
    QLabel *m_logoLabel;
    QListWidget *m_historyList;
    QPushButton *m_settingsButton;
};

#endif //UNTITLED1_SIDEBAR_H
