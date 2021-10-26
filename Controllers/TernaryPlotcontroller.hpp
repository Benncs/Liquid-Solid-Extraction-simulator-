#ifndef TERNARYPLOTCONTROLLER_H
#define TERNARYPLOTCONTROLLER_H

#include <QObject>
#include <QWidget>
#include "TernaryPlot/TernaryPlot.hpp"
#include "Plot/TernaryDrawer.h"

class TernaryPlotController : public QWidget
{
    /*!
     * @brief TernaryPlot controller : Model = Ternaryplot; View = TernaryDrawer
     * @class Can be instantiated as const because every methods are const qualified
     * Groups all methods that can be used by user
    */
    Q_OBJECT
public:
    /*!
     * \brief Constructor
    */
    explicit TernaryPlotController(QWidget *parent = nullptr);


    /*!
     * \brief Drawer(Vue)'s getter, used only by main application to show it
     * \return Controller's ternarydrawer
    */
    inline const TernaryDrawer* GetDrawer()const{return Drawer;}


    /*!
     * \brief Draw a line on the canvas
     * \param Ratio1 : Line's start point represented as componenent ratio (trilinear coordinates)
     * \param Ratio2 : Line's end point represented as componenent ratio (trilinear coordinates)
     * \param Pen : QPen with which we want to draw the line (Optional)
    */
    void DrawLine(const Ratios& Ratio1,const Ratios& Ratio2,const QPen& Pen = QPen{Qt::red,3})const;

    /*!
     * \brief Draw a line on the canvas
     * \param Point1 : Line's start point represented as point with cartesian coordinates
     * \param Point2 : Line's end point represented as point with cartesian coordinates
     * \param Pen : QPen with which we want to draw the line (Optional)
    */
    void DrawLine(const Points& Point1,const Points& Point2,const QPen& Pen = QPen{Qt::red,3})const;

    /*!
     * \brief Draw a line on the canvas
     * \param Point1 : Line's start point represented as point with cartesian coordinates
     * \param Point2 : Line's end point represented as point with cartesian coordinates
     * \param Pen : QPen with which we want to draw the line (Optional)
    */
    void DrawLineInside(const Ratios& Ratio1,const Ratios& Ratio2,const QPen& Pen = QPen{Qt::red,3})const;


    /*!
     * \brief Draw isotherm with ratio stored in the model
     * \param Pen : QPen with which we want to draw the line (Optional)
    */
    void DrawIsotherm(const QPen& Pen = QPen{Qt::red,3}) const;


    /*!
     * \brief Add ratio to model's ratio list in order to draw isotherm later
     * \param FirstRatiosList : List of ratios that have to be stored in the list, ratios represent first componenent's fraction
     * \param SecondRatiosList : List of ratios that have to be stored in the list, ratios represent second componenent's fraction
     * \param percentage : true if fraction are written with percentage
    */
    void AddRatioToIsothermList(const QVector<double>& FirstRatiosList,const QVector<double>&SecondRatiosList,bool percentage = true)const;

    /*!
     * \brief Plot a point in the canvas
     * \param Ratio1: Point coordinates passed as trilinear coordinates
    */
    void DrawPoint(const Ratios& Ratio1) const;

    /*!
     * \brief Plot a point in the canvas
     * \param Ratio1: Point coordinates passed as cartesian coordinates
    */
    void DrawPoint(const Points& Point1) const;

    /*!
     * \brief Add a conodal to the model's conodal list in order to draw them later
     * \param FirstRatiosList : List of ratios that have to be stored in the list, ratios represent first componenent's fraction
     * \param SecondRatiosList : List of ratios that have to be stored in the list, ratios represent second componenent's fraction
    */
    void AddConodalToList(const QVector<double>& FirstRatiosList,const QVector<double>&SecondRatiosList,bool percentage = true)const;

    /*!
     * \brief Draw a conodals stored into the model on the canvas
     * \param Pen : QPen with which we want to draw the line (Optional)
    */
    void DrawConodals(const QPen& Pen = QPen{Qt::red,3})const;

    /*!
     * \brief Create a conodal that pass through the point given and add it the model's list
     * \param Ratio: Ratio on which conodal will pass through
    */
    void ConodalsInterpolation(const Ratios& Ratio)const;


    /**
     * @brief Refresh scene to draw new element
     */
    inline void Refresh()const{Drawer->Refresh();};

    /**
     * @brief Clear scene to make a new drawing
     */
    inline void Clear()const{Drawer->Clear();DrawTriangle();}



public slots:
    /*!
     * \brief Slot to receive cursor information from drawer (vue)
     * \param point : Cursor location
    */
    void Position(const Points & point);
private:
    const TernaryDrawer *Drawer; //Vue
    TernaryPlot *Model; //Model

    /**
     * @brief Draw triangle given by model
     */
    inline void DrawTriangle()const{Drawer->DrawTriangle(this->Model->GetTriangle());};

};

#endif // TERNARYPLOTCONTROLLER_H
