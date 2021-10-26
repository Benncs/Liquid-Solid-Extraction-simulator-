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
    /**
     * @class Provides an interface to save results from an extraction process in a csv r txt file
     */
public:
    /**
     * @brief Default Constructor
     *
     */
    SaveFiles();

    /**
     * @brief Destructor
     * Delete file and stream
     */
    ~SaveFiles();

    /**
     * Write txt file
     * @param Filename file name
     * @param Data Extraction data computed before by process
     * @param Feed Feed used to compute data
     * @param Output Output used to compute data
     */
    void WriteTxt(const QString& Filename,const std::shared_ptr<ExtractionData>& Data,const std::shared_ptr<Current>& Feed, const std::shared_ptr<Current>& Output);

    /**
     * Write csv file
     * @param Filename file name
     * @param Data Extraction data computed before by process
     * @param Feed Feed used to compute data
     * @param Output Output used to compute data
     */
    void WriteCsv(const QString& Filename,const std::shared_ptr<ExtractionData>& Data,const std::shared_ptr<Current>& Feed, const std::shared_ptr<Current>& Output);

private:

    /** object that represents file in which data will be written **/
    QFile *file = nullptr;

    /** Text stream to store data information that will be linked to file  **/
    QTextStream *Stream = nullptr;

    /**
     * @brief Open a file
     * @param FileName file to open name
     */
    void Open(const QString& FileName);

    /**
     * @brief Close file
     */
    void inline Close(){file->close();};

    /** @brief Header of text file **/
    const QString FileHeader = "Data from extraction simulation:\nInit Data :\n\n";


    /** @brief shortcut to make a line feed, -> lisibility of text **/
    const QString LF = "\n";

};

#endif // SAVEFILES_HPP
