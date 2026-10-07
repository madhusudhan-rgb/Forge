//
// Created by mt on 10/6/26.
//
#include "sidebar.h"
#include "../settingswindow.h"
Sidebar::Sidebar(QWidget *parent) : QFrame(parent) {
    // 1. Shrink width from 250px down to a sharp, compact navbar size
    setFixedWidth(60);

    // 2. Build the visual icon hierarchy and apply layout styling
    setupLayout();
    applyStyles();
}

void Sidebar::setupLayout() {
    // Tight vertical stack layout for icon actions
    m_layout = new QVBoxLayout(this);
    m_layout->setContentsMargins(0, 15, 0, 15); // Zero side margins keeps icons perfectly centered
    m_layout->setSpacing(15);                  // Even vertical gaps between icon nodes
    m_layout->setAlignment(Qt::AlignHCenter);  // Forces all children to lock to the horizontal center line

    // --- TOP SECTION ACTION ICONS ---

    // Icon Button 1: E.g., Neo Core Agent / Chat Prompt Interface
    QPushButton *agentBtn = new QPushButton(this);
    agentBtn->setFixedSize(42, 42); // Perfect square box shape layout
    agentBtn->setCursor(Qt::PointingHandCursor);
    agentBtn->setToolTip("Neo Agent Canvas"); // Hover description text hint
    agentBtn->setIcon(QIcon(":/icons/chatbubble-ellipses-outline.svg"));
    agentBtn->setIconSize(QSize(24, 24));
    m_layout->addWidget(agentBtn);

    QPushButton *fileTreeButton = new QPushButton(this);
    fileTreeButton->setFixedSize(42, 42);
    fileTreeButton->setCursor(Qt::PointingHandCursor);
    fileTreeButton->setToolTip("File Tree");
    fileTreeButton->setIcon(QIcon(":/icons/folder-outline.svg"));
    fileTreeButton->setIconSize(QSize(24, 24));
    connect(fileTreeButton, &QPushButton::clicked, this, &Sidebar::fileTreeToggleRequested);
    m_layout->addWidget(fileTreeButton);

    // Icon Button 3: E.g., Local Extensions / Custom Automation Blueprints
    QPushButton *automationBtn = new QPushButton(this);
    automationBtn->setFixedSize(42, 42);
    automationBtn->setCursor(Qt::PointingHandCursor);
    automationBtn->setToolTip("Automation Tasks");
    automationBtn->setIcon(QIcon(":/icons/apps-outline.svg"));
    automationBtn->setIconSize(QSize(24, 24));
    m_layout->addWidget(automationBtn);

    // The Layout Spacer: Pushes your core utility icons to the top
    // and forces your preference controls down to stay at the absolute bottom.
    m_layout->addStretch();

    // --- BOTTOM SECTION PREFERENCE ICONS ---

    m_settingsButton = new QPushButton(this);
    m_settingsButton->setFixedSize(42, 42);
    m_settingsButton->setCursor(Qt::PointingHandCursor);
    m_settingsButton->setToolTip("System Preferences");
    m_settingsButton->setIcon(QIcon(":/icons/settings-outline.svg"));
    m_settingsButton->setIconSize(QSize(24, 24));
    connect(m_settingsButton, &QPushButton::clicked, this, &Sidebar::settingsRequested);
    m_layout->addWidget(m_settingsButton);
}

void Sidebar::applyStyles() {
    // Global dark pane framework styling for the navigation strip
    this->setStyleSheet(
        "Sidebar {"
        "   background-color: #18181c;" // Slightly deeper dark shade for high-contrast panel separation
        "   border-right: 1px solid #222226;"
        "}"
    );

    // Clean, flat design styling for the square icon modules with subtle selection focus states
    QString iconButtonStyle =
        "QPushButton {"
        "   background-color: transparent;" // Invisible backgrounds by default
        "   border: none;"
        "   border-radius: 8px;"            // Modern rounded corners
        "   color: #ffffff;"                // Text fallback color if using simple character symbols
        "}"
        "QPushButton:hover {"
        "   background-color: #282830;"     // Clear hover feedback box highlights
        "}"
        "QPushButton:pressed {"
        "   background-color: #121214;"
        "}";

    // Set styling rules uniformly across your buttons
    // (If you add more buttons above, make sure to call .setStyleSheet() on them here)
    for (int i = 0; i < m_layout->count(); ++i) {
        QWidget *widget = m_layout->itemAt(i)->widget();
        if (QPushButton *btn = qobject_cast<QPushButton*>(widget)) {
            btn->setStyleSheet(iconButtonStyle);
        }
    }
}
