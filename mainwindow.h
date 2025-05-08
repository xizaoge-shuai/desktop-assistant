#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "FinanceManager.h"
#include "ReminderManager.h"
#include "PasswordManager.h"

class QTabWidget;
class QTableWidget;
class QPushButton;
class QLineEdit;
class QDateEdit;
class QDateTimeEdit;
class QComboBox;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void addFinanceRecord();
    void queryFinanceMonth();
    void addReminder();
    void queryReminderDate();
    void addPassword();
    void queryPassword();

private:
    FinanceManager financeManager;
    ReminderManager reminderManager;
    PasswordManager passwordManager;

    // Tabs
    QTabWidget* tabWidget;

    // Finance tab
    QTableWidget* financeTable;
    QLineEdit *amountEdit, *categoryEdit;
    QDateEdit *dateEdit;
    QLineEdit *monthQueryEdit;

    // Reminder tab
    QTableWidget* reminderTable;
    QDateTimeEdit *reminderTimeEdit;
    QLineEdit *reminderContentEdit;
    QComboBox *priorityCombo;
    QDateEdit *reminderQueryDateEdit;

    // Password tab
    QTableWidget* passwordTable;
    QLineEdit *websiteEdit, *usernameEdit, *passwordEdit;
    QLineEdit *passwordQueryEdit;

    void setupUI();
    void loadFinanceTable(const QVector<FinanceRecord>&);
    void loadReminderTable(const QVector<ReminderRecord>&);
    void loadPasswordTable(const QVector<PasswordRecord>&);
};

#endif // MAINWINDOW_H
