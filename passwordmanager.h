#ifndef PASSWORDMANAGER_H
#define PASSWORDMANAGER_H

#include <QString>
#include <QVector>

struct PasswordRecord {
    QString website;
    QString username;
    QString encryptedPassword;
};

class PasswordManager {
public:
    PasswordManager();
    void addPassword(const PasswordRecord& record);
    QString getPasswordByWebsite(const QString& website);
    QVector<PasswordRecord> getAllPasswords();

private:
    QVector<PasswordRecord> passwords;
    void loadFromFile();
    void saveToFile(const PasswordRecord& record);
public:
    QString encrypt(const QString& plain);
    QString decrypt(const QString& encrypted);
};

#endif // PASSWORDMANAGER_H
