#ifndef PROCESSCONTROLLER_H
#define PROCESSCONTROLLER_H

#include <QObject>
#include <QWidget>

#include "TernaryPlotcontroller.hpp"
#include "ExtractionProcess/process.hpp"
#include "savefiles.hpp"
#include <QSettings>
#include "Dialogs/paramchoice.hpp"
#include <memory>

#define MAX_PROCESS_ITERATIONS 500 //Iteration number cannot be too big because with a big number of tray one, process time become big


class ProcessController : public QWidget
{
    /**
     * Class to control extraction process, child of mainwindow and contains every application widgets
     * Only controlled by mainwindow
     */

    Q_OBJECT
public:
    /**
     * @brief Default controller
     * Only creates a new ternary plot controller that will be the same during utilisation
     * @param parent : QWidget parent of this widget
     */
    explicit ProcessController(QWidget *parent = nullptr);


    /**
     * @brief Default destructor
     * delete ternary plot controller
     */
    ~ProcessController();

    /**
     * @brief Main method
     * Main function, create a new process with given feed and output that will give data from extraction and draw results
     */
    void Start();

    /**
     * @brief Intermediate method
     * Load user parameters (feed,output,number of trays, number of iteration) from a dialog window
     */
    void GetParamFromDialog();

    /**
     * @brief Intermediate method
     * Load user parameters (feed,output,number of trays, number of iteration) from a .ini file (located in the root folder)
     */
    void GetParamFromIni(QSettings* Settings);

    /**
     * @brief Save method
     * Calls method from savefile's class to save data extraction results in a csv file
     * @param Filename : Name of the file given by mainwindow
     */
    void SaveAsCsv(const QString& Filename);

    /**
    * @brief Save method
    * Calls method from savefile's class to save data extraction results in a txt file
    * @param Filename : Name of the file given by mainwindow
    */
    void SaveAsTxt(const QString& Filename);

    /**
     * @brief One of the main method
     * Perform process simulation with an unknow number of iteratons
     * Actuelly it's a loop of start method, loop stoped when simulation converged
     * @return Number of loop needed to have a convergence
     */
    int FindConvergence();


    /**
     * @brief  Getter  const method
     * method, view's getter in order to be shown by the main app window
     * @return View as a pointer of OpenGLWidget
     */
    inline  OpenGLWidget* GetView()const{return TernaryController->GetDrawer()->getView();}

    /**
     * @brief Getter const method
     * ReadyTosave's getter
     * @return true if user can save data else false
     */
    bool getReadyToSave() const;


    /**
     * @brief Getter Const method
     * If param are loaded by dialog or not
     * @return true if data from dialog are loaded
     */
    bool getLoadedParam() const;


    void DrawUnderFlowLimit()const;

private:

    //Process param
    std::shared_ptr<ExtractionData> Data; /**Data result from process **/
    std::shared_ptr<Current> Feed,Output; /**User main parameters loaded from dialog or .ini file **/
    unsigned steps; /** Number of iterations needed to have convergence **/
    unsigned ntray; /** Number of theorical trays wanted by user **/

    /**
     * @classExtraction Process
     * @brief Model used to compute the whole processd
     * **/
    Process *ExtractionProcess = nullptr;

    /**
     * @class TernaryPlotController
     * @brief ontroller that provides view and ternary plot model's
     * **/
    const TernaryPlotController *TernaryController = nullptr;

    /**
     * @class ParamChoice
     * @brief Dialog to load param from direct input
     * **/
    const ParamChoice *Dialogs = nullptr;

    /** True if user can save process' results **/
    bool readyToSave = false;

    /** True if param have been loaded by dialog window **/
    bool LoadedParam = false;

    bool Drawn = false;

    /** @class SaveFiles,
     * @brief File controller in order to save data extraction **/
    SaveFiles *Writer = nullptr;

    /**
     * @brief To plot results
     * Call ternaryplot controller's method to draw process results
     * @param steps (number of iterations) represents array's size
     *
     * TODO Delete param steps
     */
    void Draw(unsigned steps)const;

    /**
     * @brief Load feed or output parameter from settings (.ini) file
     * @param Settings Represents .ini file
     * @param group Name of group (Feed or Output)
     * @return Loaded Current as const shared ptr
     */
    const std::shared_ptr<Current> GetCurrentsFromIni(QSettings* Settings,const QString& group);


    std::shared_ptr<UnderFlowFunctionParser> Parser;


signals:

};

#endif // PROCESSCONTROLLER_H
