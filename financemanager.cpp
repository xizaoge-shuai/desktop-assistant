#include "FinanceManager.h"
#include <QFile>
#include <QTextStream>
#include <QDate>

FinanceManager::FinanceManager() {
    loadFromFile();
}

void FinanceManager::addRecord(const FinanceRecord& record) {
    records.append(record);
    saveToFile(record);
}

void FinanceManager::saveToFile(const FinanceRecord& record) {
    QFile file("finance.txt");
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << record.date << "," << record.amount << "," << record.category << "\n";
    }
}

void FinanceManager::loadFromFile() {
    QFile file("finance.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split(',');
            if (parts.size() == 3) {
                records.append({parts[0], parts[1].toDouble(), parts[2]});
            }
        }
    }
}

QVector<FinanceRecord> FinanceManager::getMonthlyRecords(const QString& month) {
    QVector<FinanceRecord> result;
    for (const auto& r : records) {
        if (r.date.startsWith(month)) result.append(r);
    }
    return result;
}

double FinanceManager::getMonthlyTotal(const QString& month) {
    double total = 0.0;
    for (const auto& r : getMonthlyRecords(month)) total += r.amount;
    return total;
}

QVector<FinanceRecord> FinanceManager::getAllRecords() {
    return records;
}
