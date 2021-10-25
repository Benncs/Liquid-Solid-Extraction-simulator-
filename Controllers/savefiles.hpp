#ifndef SAVEFILES_HPP
#define SAVEFILES_HPP

#include <QWidget>
#include <QFile>
#include <QTextStream>
#include <QFile>
#include "ExtractionProcess/ExtractionData.hpp"
#include <QDir>
#include <memory>

class SaveFiles
{
public:
    SaveFiles();
    ~SaveFiles();
    void WriteTxt(const QString& Filename,const std::shared_ptr<ExtractionData>& Data,const std::shared_ptr<Current>& Feed, const std::shared_ptr<Current>& Output);
    void WriteCsv(const QString& Filename,const std::shared_ptr<ExtractionData>& Data,const std::shared_ptr<Current>& Feed, const std::shared_ptr<Current>& Output);

private:
    QFile *file = nullptr;
    QTextStream *Stream = nullptr;
    void Open(const QString& FileName);
    void inline Close(){file->close();};
    const QString FileHeader = "Data from extraction simulation:\nInit Data :\n\n";

    const QString LF = "\n";

};

#endif // SAVEFILES_HPP
