#ifndef FINANCEMANAGER_H
#define FINANCEMANAGER_H

#include <QString>
#include <QVector>

struct FinanceRecord {
    QString date;
    double amount;
    QString category;
};

class FinanceManager {
public:
    FinanceManager();
    void addRecord(const FinanceRecord& record);
    QVector<FinanceRecord> getMonthlyRecords(const QString& month);
    double getMonthlyTotal(const QString& month);
    QVector<FinanceRecord> getAllRecords();

private:
    QVector<FinanceRecord> records;
    void loadFromFile();
    void saveToFile(const FinanceRecord& record);
};

#endif // FINANCEMANAGER_H
