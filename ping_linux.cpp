#include "ping_base.h"

#if defined(Q_OS_LINUX)

#include <QString>
#include <QProcess>
#include <QDebug>

int ping_host(const QString& host)
{
    QProcess proc;
    proc.start("ping", QStringList() << "-c" << "1" << host);
    proc.waitForFinished();
    if (proc.exitCode() == 0)
    {
        QString output = QString::fromUtf8(proc.readAllStandardOutput());
        QStringList lines = output.split('\n');
        if (lines.size() >= 2)
        {
            QStringList fields = lines[1].split('=');
            if (fields.size() >= 2)
            {
                QString time = fields[1].trimmed();
                time.chop(2); // remove "ms"
                return time.toInt();
            }
        }
    }
    return -1;
}

#endif
