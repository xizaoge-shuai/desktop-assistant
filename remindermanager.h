#ifndef REMINDERMANAGER_H
#define REMINDERMANAGER_H

#include <QString>
#include <QVector>
#include <QDateTime>

struct ReminderRecord {
    QDateTime datetime;
    QString content;
    int priority;
};

class ReminderManager {
public:
    ReminderManager();
    void addReminder(const ReminderRecord& reminder);
    QVector<ReminderRecord> getRemindersByDate(const QDate& date);
    QVector<ReminderRecord> getAllReminders();

private:
    QVector<ReminderRecord> reminders;
    void loadFromFile();
    void saveToFile(const ReminderRecord& reminder);
};

#endif // REMINDERMANAGER_H
