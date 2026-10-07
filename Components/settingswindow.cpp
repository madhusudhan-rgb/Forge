#include "../settingswindow.h"
#include <QDialogButtonBox>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QListWidget>
#include <QStackedWidget>
#include <QGroupBox>
#include <QAbstractButton>
#include <QApplication>

namespace {

// The two complete themes behind the "Screen mode" box on the General tab.
// They are kept symmetric so a switch never drops rules (group boxes, sidebar
// tabs, menus, scrollbars, ...) that the other theme still has.

const char *lightTheme = R"(
    QDialog, QMainWindow {
        background-color: #f8f9fa;
        color: #212529;
    }
    QSplitter::handle {
        background-color: #dee2e6;
    }
    QLabel {
        background: transparent;
        color: #212529;
    }
    QGroupBox {
        background-color: #ffffff;
        color: #212529;
        border: 1px solid #dee2e6;
        border-radius: 6px;
        margin-top: 14px;
        font-weight: bold;
    }
    QGroupBox::title {
        subcontrol-origin: margin;
        subcontrol-position: top left;
        left: 10px;
        padding: 0 6px;
        color: #495057;
    }
    QLineEdit, QComboBox {
        background-color: #ffffff;
        color: #212529;
        border: 1px solid #ced4da;
        border-radius: 4px;
        padding: 5px;
        selection-background-color: #0d6efd;
        selection-color: #ffffff;
    }
    QLineEdit:hover, QComboBox:hover {
        border-color: #86b7fe;
    }
    QLineEdit:focus, QComboBox:focus {
        border: 1px solid #0d6efd;
    }
    QComboBox QAbstractItemView {
        background-color: #ffffff;
        color: #212529;
        border: 1px solid #ced4da;
        selection-background-color: #0d6efd;
        selection-color: #ffffff;
    }
    QListWidget {
        background-color: #ffffff;
        color: #212529;
        border: 1px solid #dee2e6;
        border-radius: 6px;
        padding: 4px;
        outline: none;
    }
    QListWidget::item {
        padding: 7px 8px;
        border-radius: 4px;
    }
    QListWidget::item:hover {
        background-color: #f1f3f5;
    }
    QListWidget::item:selected {
        background-color: #e7f5ff;
        color: #1971c2;
    }
    QTextEdit, QTreeView {
        background-color: #ffffff;
        color: #212529;
        border: 1px solid #dee2e6;
        alternate-background-color: #f8f9fa;
    }
    QTreeView::item {
        padding: 3px 2px;
    }
    QTreeView::item:hover {
        background-color: #f1f3f5;
    }
    QTreeView::item:selected {
        background-color: #e7f5ff;
        color: #1971c2;
    }
    QPushButton {
        background-color: #ffffff;
        color: #212529;
        border: 1px solid #ced4da;
        border-radius: 4px;
        padding: 6px 14px;
    }
    QPushButton:hover {
        background-color: #f1f3f5;
    }
    QPushButton:pressed {
        background-color: #e9ecef;
    }
    QPushButton:default {
        background-color: #0d6efd;
        border: 1px solid #0d6efd;
        color: #ffffff;
    }
    QPushButton:default:hover {
        background-color: #0b5ed7;
    }
    QPushButton:disabled {
        background-color: #f1f3f5;
        color: #adb5bd;
    }
    QMenuBar {
        background-color: #f8f9fa;
        color: #212529;
    }
    QMenuBar::item {
        padding: 6px 10px;
        background-color: transparent;
    }
    QMenuBar::item:selected {
        background-color: #e9ecef;
    }
    QMenuBar::item:pressed {
        background-color: #dee2e6;
    }
    QMenu {
        background-color: #ffffff;
        color: #212529;
        border: 1px solid #dee2e6;
    }
    QMenu::item {
        padding: 6px 28px 6px 18px;
    }
    QMenu::item:selected {
        background-color: #0d6efd;
        color: #ffffff;
    }
    QMenu::separator {
        height: 1px;
        background-color: #dee2e6;
        margin: 4px 8px;
    }
)";

const char *darkTheme = R"(
    QDialog, QMainWindow {
        background-color: #1e1e1e;
        color: #ffffff;
    }
    QSplitter::handle {
        background-color: #3e3e3e;
    }
    QLabel {
        background: transparent;
        color: #ffffff;
    }
    QGroupBox {
        background-color: #252526;
        color: #ffffff;
        border: 1px solid #3e3e3e;
        border-radius: 6px;
        margin-top: 14px;
        font-weight: bold;
    }
    QGroupBox::title {
        subcontrol-origin: margin;
        subcontrol-position: top left;
        left: 10px;
        padding: 0 6px;
        color: #adb5bd;
    }
    QLineEdit, QComboBox {
        background-color: #2d2d2d;
        color: #ffffff;
        border: 1px solid #3e3e3e;
        border-radius: 4px;
        padding: 5px;
        selection-background-color: #0e639c;
        selection-color: #ffffff;
    }
    QLineEdit:hover, QComboBox:hover {
        border-color: #1177bb;
    }
    QLineEdit:focus, QComboBox:focus {
        border: 1px solid #1177bb;
    }
    QComboBox QAbstractItemView {
        background-color: #2d2d2d;
        color: #ffffff;
        border: 1px solid #3e3e3e;
        selection-background-color: #0e639c;
        selection-color: #ffffff;
    }
    QListWidget {
        background-color: #252526;
        color: #ffffff;
        border: 1px solid #3e3e3e;
        border-radius: 6px;
        padding: 4px;
        outline: none;
    }
    QListWidget::item {
        padding: 7px 8px;
        border-radius: 4px;
    }
    QListWidget::item:hover {
        background-color: #2f2f31;
    }
    QListWidget::item:selected {
        background-color: #0e639c;
        color: #ffffff;
    }
    QTextEdit, QTreeView {
        background-color: #1e1e1e;
        color: #ffffff;
        border: 1px solid #3e3e3e;
        alternate-background-color: #252526;
    }
    QTreeView::item {
        padding: 3px 2px;
    }
    QTreeView::item:hover {
        background-color: #2f2f31;
    }
    QTreeView::item:selected {
        background-color: #0e639c;
        color: #ffffff;
    }
    QPushButton {
        background-color: #2d2d2d;
        color: #ffffff;
        border: 1px solid #3e3e3e;
        border-radius: 4px;
        padding: 6px 14px;
    }
    QPushButton:hover {
        background-color: #37373d;
    }
    QPushButton:pressed {
        background-color: #0b5382;
    }
    QPushButton:default {
        background-color: #0e639c;
        border: 1px solid #0e639c;
        color: #ffffff;
    }
    QPushButton:default:hover {
        background-color: #1177bb;
    }
    QPushButton:disabled {
        background-color: #2d2d2d;
        color: #6c757d;
    }
    QMenuBar {
        background-color: #1e1e1e;
        color: #ffffff;
    }
    QMenuBar::item {
        padding: 6px 10px;
        background-color: transparent;
    }
    QMenuBar::item:selected {
        background-color: #2d2d2d;
    }
    QMenuBar::item:pressed {
        background-color: #37373d;
    }
    QMenu {
        background-color: #252526;
        color: #ffffff;
        border: 1px solid #3e3e3e;
    }
    QMenu::item {
        padding: 6px 28px 6px 18px;
    }
    QMenu::item:selected {
        background-color: #0e639c;
        color: #ffffff;
    }
    QMenu::separator {
        height: 1px;
        background-color: #3e3e3e;
        margin: 4px 8px;
    }
    QScrollBar:vertical {
        background-color: #1e1e1e;
        width: 12px;
        margin: 0;
        border: none;
    }
    QScrollBar::handle:vertical {
        background-color: #3e3e3e;
        min-height: 30px;
        border-radius: 5px;
    }
    QScrollBar::handle:vertical:hover {
        background-color: #55555c;
    }
    QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {
        height: 0;
        width: 0;
    }
    QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {
        background-color: transparent;
    }
    QScrollBar:horizontal {
        background-color: #1e1e1e;
        height: 12px;
        margin: 0;
        border: none;
    }
    QScrollBar::handle:horizontal {
        background-color: #3e3e3e;
        min-width: 30px;
        border-radius: 5px;
    }
    QScrollBar::handle:horizontal:hover {
        background-color: #55555c;
    }
    QScrollBar::add-line:horizontal, QScrollBar::sub-line:horizontal {
        height: 0;
        width: 0;
    }
    QScrollBar::add-page:horizontal, QScrollBar::sub-page:horizontal {
        background-color: transparent;
    }
    QScrollBar::corner {
        background-color: transparent;
    }
    QToolTip {
        background-color: #2d2d2d;
        color: #ffffff;
        border: 1px solid #3e3e3e;
        padding: 4px 6px;
    }
)";

// Last mode handed to QApplication; empty until the user picks one. Needed
// because a stylesheet set on the dialog itself beats the app-wide one, so
// the dialog has to drop its local sheet as soon as a global theme exists.
QString appliedTheme;

QString themeStyleSheet(const QString &mode) {
    return QString::fromUtf8(mode == "Dark" ? darkTheme : lightTheme);
}

} // namespace

SettingsDialog::SettingsDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Preferences");
    resize(640, 420);
    setMinimumSize(540, 360);

    // Root horizontal layout: Sidebar on the left, Content on the right
    auto *rootLayout = new QHBoxLayout(this);
    rootLayout->setContentsMargins(12, 12, 12, 12);
    rootLayout->setSpacing(12);

    // 1. Left Sidebar Navigation
    auto *sidebar = new QListWidget(this);
    sidebar->setFixedWidth(140);
    sidebar->addItem("Model ID");
    sidebar->addItem("General");
    sidebar->setCurrentRow(0);
    rootLayout->addWidget(sidebar);

    // 2. Right Pane: Stacked Pages & Footer
    auto *rightPaneLayout = new QVBoxLayout();
    auto *pageStack = new QStackedWidget(this);

    // --- Page 1: AI Models Configuration ---
    auto *aiPage = new QWidget();
    auto *aiPageLayout = new QVBoxLayout(aiPage);
    aiPageLayout->setContentsMargins(0, 0, 0, 0);

    // Group box for API / Provider settings
    auto *apiGroup = new QGroupBox("LLM && Provider Configuration", aiPage);
    auto *formLayout = new QFormLayout(apiGroup);
    formLayout->setSpacing(10);
    formLayout->setLabelAlignment(Qt::AlignRight);

    // Provider Dropdown or Input
    auto *providerCombo = new QComboBox(apiGroup);
    providerCombo->addItems({"Custom / Local", "OpenAI", "Anthropic", "Groq", "Other"});
    formLayout->addRow("Provider:", providerCombo);

    // Endpoint URL input
    auto *endpointInput = new QLineEdit(apiGroup);
    endpointInput->setPlaceholderText("http://localhost:11434 or API base URL");
    formLayout->addRow("Endpoint:", endpointInput);

    // API Key input
    auto *apiKeyInput = new QLineEdit(apiGroup);
    apiKeyInput->setEchoMode(QLineEdit::Password);
    apiKeyInput->setPlaceholderText("sk-...");
    formLayout->addRow("API Key:", apiKeyInput);

    aiPageLayout->addWidget(apiGroup);
    aiPageLayout->addStretch(); // Pins the group box neatly to the top

    // General / Editor Settings
    // --- Page 2: General / Editor Settings ---
    auto *generalPage = new QWidget();
    auto *generalLayout = new QVBoxLayout(generalPage);
    generalLayout->setContentsMargins(0, 0, 0, 0);

    auto *generalGroup = new QGroupBox("Window && Appearance", generalPage);
    auto *generalFormLayout = new QFormLayout(generalGroup);
    generalFormLayout->setSpacing(10);
    generalFormLayout->setLabelAlignment(Qt::AlignRight);

    auto *modeCombo = new QComboBox(generalGroup);
    modeCombo->addItems({"Light", "Dark"});
    // Reopen on the mode that is actually applied instead of always "Light"
    if (!appliedTheme.isEmpty()) {
        modeCombo->setCurrentText(appliedTheme);
    }
    connect(modeCombo, &QComboBox::currentTextChanged, this, [this](const QString &text) {
        appliedTheme = text;
        // Drop the dialog-local sheet first: it would outrank the app-wide
        // one and keep this dialog stuck on the previous theme.
        setStyleSheet(QString());
        qApp->setStyleSheet(themeStyleSheet(text));
    });
    generalFormLayout->addRow("Screen mode:", modeCombo);

    generalLayout->addWidget(generalGroup);
    generalLayout->addStretch();


    // Add pages to stacked widget
    pageStack->addWidget(aiPage);
    pageStack->addWidget(generalPage);
    rightPaneLayout->addWidget(pageStack);

    // Wire sidebar navigation to page changes
    connect(sidebar, &QListWidget::currentRowChanged, pageStack, &QStackedWidget::setCurrentIndex);

    // 3. Dialog Button Box (Bottom Right)
    auto *buttonBox = new QDialogButtonBox(
        QDialogButtonBox::Apply | QDialogButtonBox::Reset | QDialogButtonBox::Close, this);
    rightPaneLayout->addWidget(buttonBox);

    rootLayout->addLayout(rightPaneLayout);

    // Style the dialog right away, but only while no app-wide theme has been
    // picked yet; once one exists it already covers this dialog, and a local
    // copy here would outrank later theme switches.
    if (appliedTheme.isEmpty()) {
        setStyleSheet(themeStyleSheet(modeCombo->currentText()));
    }

    //Button Actions
    connect(buttonBox, &QDialogButtonBox::clicked, this,
            [this, apiKeyInput, endpointInput, providerCombo, buttonBox ,modeCombo](QAbstractButton *button) {
                auto role = buttonBox->buttonRole(button);

                if (role == QDialogButtonBox::ApplyRole) {
                    // Logic to store/apply credentials
                    QMessageBox::information(this, "Settings", "Settings applied successfully.", QMessageBox::Ok);
                    this->accept();
                } else if (role == QDialogButtonBox::ResetRole) {
                    apiKeyInput->clear();
                    endpointInput->clear();
                    providerCombo->setCurrentIndex(0);
                    modeCombo->setCurrentIndex(0);
                } else if (role == QDialogButtonBox::RejectRole) {
                    this->reject();
                }
            });
}
