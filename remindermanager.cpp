#include "ReminderManager.h"
#include <QFile>
#include <QTextStream>
#include <algorithm>

ReminderManager::ReminderManager() {
    loadFromFile();
}

void ReminderManager::addReminder(const ReminderRecord& reminder) {
    reminders.append(reminder);
    std::sort(reminders.begin(), reminders.end(), [](const ReminderRecord& a, const ReminderRecord& b) {
        return a.datetime < b.datetime;
    });
    saveToFile(reminder);
}

void ReminderManager::saveToFile(const ReminderRecord& reminder) {
    QFile file("reminder.txt");
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << reminder.datetime.toString("yyyy-MM-dd HH:mm") << "," << reminder.content << "," << reminder.priority << "\n";
    }
}

void ReminderManager::loadFromFile() {
    QFile file("reminder.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split(',');
            if (parts.size() >= 3) {
                ReminderRecord r;
                r.datetime = QDateTime::fromString(parts[0], "yyyy-MM-dd HH:mm");
                r.content = parts[1];
                r.priority = parts[2].toInt();
                reminders.append(r);
            }
        }
    }
}

QVector<ReminderRecord> ReminderManager::getRemindersByDate(const QDate& date) {
    QVector<ReminderRecord> result;
    for (const auto& r : reminders)
    {
        if (r.datetime.date() == date)
            result.append(r);
    }
    return result;
}

QVector<ReminderRecord> ReminderManager::getAllReminders() {
    return reminders;
}
