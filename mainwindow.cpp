#include "MainWindow.h"
#include <QTabWidget>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QDateEdit>
#include <QDateTimeEdit>
#include <QComboBox>
#include <QHeaderView>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setupUI();
}

MainWindow::~MainWindow() {}

void MainWindow::setupUI() {
    tabWidget = new QTabWidget(this);
    setCentralWidget(tabWidget);

    // ================= Finance Tab =================
    QWidget *financeTab = new QWidget;
    QVBoxLayout *financeLayout = new QVBoxLayout;

    QHBoxLayout *inputLayout = new QHBoxLayout;
    dateEdit = new QDateEdit(QDate::currentDate());
    amountEdit = new QLineEdit;
    categoryEdit = new QLineEdit;
    QPushButton *addFinanceBtn = new QPushButton("添加记录");
    inputLayout->addWidget(new QLabel("日期:"));
    inputLayout->addWidget(dateEdit);
    inputLayout->addWidget(new QLabel("金额:"));
    inputLayout->addWidget(amountEdit);
    inputLayout->addWidget(new QLabel("类别:"));
    inputLayout->addWidget(categoryEdit);
    inputLayout->addWidget(addFinanceBtn);
    connect(addFinanceBtn, &QPushButton::clicked, this, &MainWindow::addFinanceRecord);

    QHBoxLayout *queryLayout = new QHBoxLayout;
    monthQueryEdit = new QLineEdit;
    QPushButton *queryFinanceBtn = new QPushButton("查询月份");
    queryLayout->addWidget(new QLabel("月份 (YYYY-MM):"));
    queryLayout->addWidget(monthQueryEdit);
    queryLayout->addWidget(queryFinanceBtn);
    connect(queryFinanceBtn, &QPushButton::clicked, this, &MainWindow::queryFinanceMonth);

    financeTable = new QTableWidget;
    financeTable->setColumnCount(3);
    financeTable->setHorizontalHeaderLabels({"日期", "金额", "类别"});
    financeTable->horizontalHeader()->setStretchLastSection(true);

    financeLayout->addLayout(inputLayout);
    financeLayout->addLayout(queryLayout);
    financeLayout->addWidget(financeTable);
    financeTab->setLayout(financeLayout);
    tabWidget->addTab(financeTab, "记账本");

    // ================= Reminder Tab =================
    QWidget *reminderTab = new QWidget;
    QVBoxLayout *reminderLayout = new QVBoxLayout;

    QHBoxLayout *reminderInputLayout = new QHBoxLayout;
    reminderTimeEdit = new QDateTimeEdit(QDateTime::currentDateTime());
    reminderContentEdit = new QLineEdit;
    priorityCombo = new QComboBox;
    priorityCombo->addItems({"1", "2", "3"});
    QPushButton *addReminderBtn = new QPushButton("添加提醒");
    reminderInputLayout->addWidget(new QLabel("时间:"));
    reminderInputLayout->addWidget(reminderTimeEdit);
    reminderInputLayout->addWidget(new QLabel("内容:"));
    reminderInputLayout->addWidget(reminderContentEdit);
    reminderInputLayout->addWidget(new QLabel("优先级:"));
    reminderInputLayout->addWidget(priorityCombo);
    reminderInputLayout->addWidget(addReminderBtn);
    connect(addReminderBtn, &QPushButton::clicked, this, &MainWindow::addReminder);

    QHBoxLayout *reminderQueryLayout = new QHBoxLayout;
    reminderQueryDateEdit = new QDateEdit(QDate::currentDate());
    QPushButton *queryReminderBtn = new QPushButton("查询当天提醒");
    reminderQueryLayout->addWidget(new QLabel("日期:"));
    reminderQueryLayout->addWidget(reminderQueryDateEdit);
    reminderQueryLayout->addWidget(queryReminderBtn);
    connect(queryReminderBtn, &QPushButton::clicked, this, &MainWindow::queryReminderDate);

    reminderTable = new QTableWidget;
    reminderTable->setColumnCount(3);
    reminderTable->setHorizontalHeaderLabels({"时间", "内容", "优先级"});
    reminderTable->horizontalHeader()->setStretchLastSection(true);

    reminderLayout->addLayout(reminderInputLayout);
    reminderLayout->addLayout(reminderQueryLayout);
    reminderLayout->addWidget(reminderTable);
    reminderTab->setLayout(reminderLayout);
    tabWidget->addTab(reminderTab, "课程提醒");

    // ================= Password Tab =================
    QWidget *passwordTab = new QWidget;
    QVBoxLayout *passwordLayout = new QVBoxLayout;

    QHBoxLayout *passwordInputLayout = new QHBoxLayout;
    websiteEdit = new QLineEdit;
    usernameEdit = new QLineEdit;
    passwordEdit = new QLineEdit;
    QPushButton *addPasswordBtn = new QPushButton("添加密码");
    passwordInputLayout->addWidget(new QLabel("网站:"));
    passwordInputLayout->addWidget(websiteEdit);
    passwordInputLayout->addWidget(new QLabel("用户名:"));
    passwordInputLayout->addWidget(usernameEdit);
    passwordInputLayout->addWidget(new QLabel("密码:"));
    passwordInputLayout->addWidget(passwordEdit);
    passwordInputLayout->addWidget(addPasswordBtn);
    connect(addPasswordBtn, &QPushButton::clicked, this, &MainWindow::addPassword);

    QHBoxLayout *passwordQueryLayout = new QHBoxLayout;
    passwordQueryEdit = new QLineEdit;
    QPushButton *queryPasswordBtn = new QPushButton("查询密码");
    passwordQueryLayout->addWidget(new QLabel("网站:"));
    passwordQueryLayout->addWidget(passwordQueryEdit);
    passwordQueryLayout->addWidget(queryPasswordBtn);
    connect(queryPasswordBtn, &QPushButton::clicked, this, &MainWindow::queryPassword);

    passwordTable = new QTableWidget;
    passwordTable->setColumnCount(3);
    passwordTable->setHorizontalHeaderLabels({"网站", "用户名", "密码"});
    passwordTable->horizontalHeader()->setStretchLastSection(true);

    passwordLayout->addLayout(passwordInputLayout);
    passwordLayout->addLayout(passwordQueryLayout);
    passwordLayout->addWidget(passwordTable);
    passwordTab->setLayout(passwordLayout);
    tabWidget->addTab(passwordTab, "密码管理");
}

// =================== 槽函数 ===================

void MainWindow::addFinanceRecord() {
    FinanceRecord record;
    record.date = dateEdit->date().toString("yyyy-MM-dd");
    record.amount = amountEdit->text().toDouble();
    record.category = categoryEdit->text();
    financeManager.addRecord(record);
    loadFinanceTable(financeManager.getAllRecords());
}

void MainWindow::queryFinanceMonth() {
    QString month = monthQueryEdit->text();
    loadFinanceTable(financeManager.getMonthlyRecords(month));
}

void MainWindow::addReminder() {
    ReminderRecord record;
    record.datetime = reminderTimeEdit->dateTime();
    record.content = reminderContentEdit->text();
    record.priority = priorityCombo->currentText().toInt();
    reminderManager.addReminder(record);
    loadReminderTable(reminderManager.getAllReminders());
}

void MainWindow::queryReminderDate() {
    QDate date = reminderQueryDateEdit->date();
    loadReminderTable(reminderManager.getRemindersByDate(date));
}

void MainWindow::addPassword() {
    PasswordRecord record;
    record.website = websiteEdit->text();
    record.username = usernameEdit->text();
    record.encryptedPassword = passwordManager.encrypt(passwordEdit->text());
    passwordManager.addPassword(record);
    loadPasswordTable(passwordManager.getAllPasswords());
}

void MainWindow::queryPassword() {
    QString website = passwordQueryEdit->text();
    QString password = passwordManager.getPasswordByWebsite(website);
    passwordTable->setRowCount(1);
    passwordTable->setItem(0, 0, new QTableWidgetItem(website));
    passwordTable->setItem(0, 1, new QTableWidgetItem("（已查询）"));
    passwordTable->setItem(0, 2, new QTableWidgetItem(password));
}

// =================== 表格加载函数 ===================

void MainWindow::loadFinanceTable(const QVector<FinanceRecord> &records) {
    financeTable->setRowCount(records.size());
    for (int i = 0; i < records.size(); ++i) {
        financeTable->setItem(i, 0, new QTableWidgetItem(records[i].date));
        financeTable->setItem(i, 1, new QTableWidgetItem(QString::number(records[i].amount, 'f', 2)));
        financeTable->setItem(i, 2, new QTableWidgetItem(records[i].category));
    }
}

void MainWindow::loadReminderTable(const QVector<ReminderRecord> &records) {
    reminderTable->setRowCount(records.size());
    for (int i = 0; i < records.size(); ++i) {
        reminderTable->setItem(i, 0, new QTableWidgetItem(records[i].datetime.toString("yyyy-MM-dd HH:mm")));
        reminderTable->setItem(i, 1, new QTableWidgetItem(records[i].content));
        reminderTable->setItem(i, 2, new QTableWidgetItem(QString::number(records[i].priority)));
    }
}

void MainWindow::loadPasswordTable(const QVector<PasswordRecord> &records) {
    passwordTable->setRowCount(records.size());
    for (int i = 0; i < records.size(); ++i) {
        passwordTable->setItem(i, 0, new QTableWidgetItem(records[i].website));
        passwordTable->setItem(i, 1, new QTableWidgetItem(records[i].username));
        passwordTable->setItem(i, 2, new QTableWidgetItem(passwordManager.decrypt(records[i].encryptedPassword)));
    }
}
