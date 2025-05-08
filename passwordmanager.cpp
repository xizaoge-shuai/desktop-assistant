#include "PasswordManager.h"
#include <QFile>
#include <QTextStream>

PasswordManager::PasswordManager() {
    loadFromFile();
}

QString PasswordManager::encrypt(const QString& plain) {
    QString result;
    for (QChar ch : plain)
        result.append(QChar(ch.unicode() + 1));
    return result;
}

QString PasswordManager::decrypt(const QString& encrypted) {
    QString result;
    for (QChar ch : encrypted)
        result.append(QChar(ch.unicode() - 1));
    return result;
}

void PasswordManager::addPassword(const PasswordRecord& record) {
    passwords.append(record);
    saveToFile(record);
}

void PasswordManager::saveToFile(const PasswordRecord& record) {
    QFile file("password.txt");
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << record.website << "," << record.username << "," << record.encryptedPassword << "\n";
    }
}

void PasswordManager::loadFromFile() {
    QFile file("password.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split(',');
            if (parts.size() == 3) {
                passwords.append({parts[0], parts[1], parts[2]});
            }
        }
    }
}

QString PasswordManager::getPasswordByWebsite(const QString& website) {
    for (const auto& r : passwords)
    {
        if (r.website.compare(website, Qt::CaseInsensitive) == 0)
            return decrypt(r.encryptedPassword);
    }
    return "Not found";
}

QVector<PasswordRecord> PasswordManager::getAllPasswords() {
    return passwords;
}
