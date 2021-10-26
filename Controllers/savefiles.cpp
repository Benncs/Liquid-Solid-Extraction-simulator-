#include "savefiles.hpp"

SaveFiles::SaveFiles()
{

}

void SaveFiles::Open(const QString& FileName){

    try{
        delete file; //If there is file, delete it before
        file = new QFile(FileName.toStdString().c_str());
        //Check if we can ope file
        if(!file->open(QIODevice::Append)){
            return;
        }
        Stream = new QTextStream(file); // Stream that will store data to write
    }
    catch(...){
        //Catch everything If something wrong happens
        throw std::invalid_argument("Cannot open file");
    }

}

SaveFiles::~SaveFiles()
{
    if(file->isOpen()) file->close(); //Close file before deleting it
    delete file;
    delete Stream;
}


void SaveFiles::WriteTxt(const QString& Filename,const std::shared_ptr<ExtractionData>& Data,const std::shared_ptr<Current>& Feed, const std::shared_ptr<Current>& Output)
{

    try{
        Open(Filename);
        *Stream<<FileHeader;
        *Stream<<QString("Theoricals trays = %1\n").arg(Data->ntray);
        *Stream<<QString("Loop iterations = %1\n\n").arg(Data->step);
        *Stream<<"Feed : \n\t"<<*Feed;
        *Stream<<"Output : \n\t"<<*Output;

        *Stream<<"\n\t\t------\n\nComputed Data: \n\n";
        *Stream<<"Operating Point : \n\t"<<*Data->M;

        file->close();
    }
    catch(...){
        //Catch everything If something wrong happens
        throw std::invalid_argument("Cannot write on txt");
    }

}

void SaveFiles::WriteCsv(const QString& Filename,const std::shared_ptr<ExtractionData> &Data, const std::shared_ptr<Current> &Feed, const std::shared_ptr<Current> &Output)
{
    try{
        Open(Filename);
        *Stream<<"Simulation Data"<<LF<<LF<<LF;
        *Stream<<"Theorical trays,"<<Data->ntray<<LF<<"Loop iterations,"<<Data->step<<LF<<LF<<LF;

        *Stream<<",Flow,Xa,Xb,Xs"<<LF;

        *Stream<<"Feed"<<*Feed<<LF;
        *Stream<<"Output"<<*Output<<LF;

        *Stream<<"Operating Point"<<*Data->M<<LF<<LF<<LF<<LF;

        *Stream<<"Refined,Flow,Xa,Xb,Xs,,Extracted,Flow,Xa,Xb,Xs"<<LF;
        int count = 0 ;
        //Refined and extracted are array that represents every result for each simulation iteration, thus we have to loop through them
        for(auto i = 0; i<Data->Refined.size();++i){
            *Stream<<(count+1)<<*Data->Refined[i]<<",,"<<(count+1)<<*Data->Extracted[i]<<LF;
            ++count;
        }
        file->close();
    }catch(...){
        throw std::invalid_argument("Cannot write in csv");
    }

}
