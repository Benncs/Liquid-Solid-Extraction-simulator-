QT       += core gui openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Controllers/TernaryPlotcontroller.cpp \
    Controllers/processcontroller.cpp \
    Controllers/savefiles.cpp \
    Dialogs/paramchoice.cpp \
    ExtractionProcess/current.cpp \
    ExtractionProcess/process.cpp \
    ExtractionProcess/theoricaltray.cpp \
    Maths/Geometry/Core/PolygonFactory.cpp \
    Maths/Geometry/Objects/Points.cpp \
    Maths/Geometry/Shapes/Circle.cpp \
    Maths/Geometry/Shapes/Line2D.cpp \
    Maths/Geometry/Shapes/Polygons/Polygon.cpp \
    Maths/Geometry/Shapes/Polygons/Quadrilateral/Diamond.cpp \
    Maths/Geometry/Shapes/Polygons/Quadrilateral/Parallelogram.cpp \
    Maths/Geometry/Shapes/Polygons/Quadrilateral/Rectangle.cpp \
    Maths/Geometry/Shapes/Polygons/Quadrilateral/Square.cpp \
    Maths/Geometry/Shapes/Segment2D.cpp \
    Maths/Geometry/Tools.cpp \
    Maths/Sequence.cpp \
    OpenGL/Methods.cpp \
    OpenGL/graphopengl.cpp \
    OpenGL/openglwidget.cpp \
    Plot/TernaryDrawer.cpp \
    TernaryPlot/Interfaces/Ratios.cpp \
    TernaryPlot/Interfaces/Tuples.cpp \
    TernaryPlot/TernaryPlot.cpp \
    TernaryPlot/Triangles/Triangle.cpp \
    TernaryPlot/Triangles/TriangleFabric.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Controllers/TernaryPlotcontroller.hpp \
    Controllers/processcontroller.hpp \
    Controllers/savefiles.hpp \
    Dialogs/paramchoice.hpp \
    ExtractionProcess/ExtractionData.hpp \
    ExtractionProcess/current.hpp \
    ExtractionProcess/process.hpp \
    ExtractionProcess/theoricaltray.hpp \
    Maths/Algebra.hpp \
    Maths/Calculus/NewtonN.hpp \
    Maths/Calculus/calculus.hpp \
    Maths/Geometry/Core/GeoCore.hpp \
    Maths/Geometry/Core/PolygonFactory.hpp \
    Maths/Geometry/Objects/Points.hpp \
    Maths/Geometry/Objects/ThreeTuple.hpp \
    Maths/Geometry/Objects/Tuple.hpp \
    Maths/Geometry/Shapes/Circle.hpp \
    Maths/Geometry/Shapes/Line2D.hpp \
    Maths/Geometry/Shapes/Polygons/Polygon.hpp \
    Maths/Geometry/Shapes/Polygons/Quadrilateral/Diamond.hpp \
    Maths/Geometry/Shapes/Polygons/Quadrilateral/Parallelogram.hpp \
    Maths/Geometry/Shapes/Polygons/Quadrilateral/Rectangle.hpp \
    Maths/Geometry/Shapes/Polygons/Quadrilateral/Square.hpp \
#    Maths/Geometry/Shapes/Polygons/Triangle/Equilateral.hpp \
#    Maths/Geometry/Shapes/Polygons/Triangle/Triangle.hpp \
    Maths/Geometry/Shapes/Segment2D.hpp \
    Maths/Geometry/Shapes/Shape.hpp \
    Maths/Geometry/Tools.hpp \
    Maths/Maths.hpp \
    Maths/MatrixLib/Diagonalize.hpp \
    Maths/MatrixLib/EigenValues.hpp \
    Maths/MatrixLib/EigenVector.hpp \
    Maths/MatrixLib/Exceptions.hpp \
    Maths/MatrixLib/GaussElimination.hpp \
    Maths/MatrixLib/LinSolve.hpp \
    Maths/MatrixLib/Matrix.hpp \
    Maths/MatrixLib/MatrixMethods.hpp \
    Maths/MatrixLib/QR.hpp \
    Maths/MatrixLib/RegLin.hpp \
    Maths/MatrixLib/Vector.hpp \
    Maths/NewtonTwo.hpp \
    Maths/Sequence.hpp \
    Maths/Trigo/Pi.hpp \
    Maths/Trigo/Trigo.hpp \
    Maths/Trigo/power.hpp \
    OpenGL/Methods.h \
    OpenGL/graphopengl.h \
    OpenGL/openglwidget.h \
    Plot/TernaryDrawer.h \
    TernaryPlot/Interfaces/Pair.hpp \
    TernaryPlot/Interfaces/Points.hpp \
    TernaryPlot/Interfaces/Ratios.hpp \
    TernaryPlot/Interfaces/ThreeTuple.hpp \
    TernaryPlot/Interfaces/Tuples.hpp \
    TernaryPlot/TernaryPlot.hpp \
    TernaryPlot/Triangles/Equilateral.hpp \
    TernaryPlot/Triangles/Rectangle.hpp \
    TernaryPlot/Triangles/Triangle.hpp \
    TernaryPlot/Triangles/TriangleFabric.hpp \
    mainwindow.h

FORMS += \
    Dialogs/paramchoice.ui \
    OpenGL/graphopengl.ui \
    Plot/TernaryDrawer.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

QMAKE_CXXFLAGS_RELEASE += -O3

TARGET = ExtractionSimulator

RESOURCES += \
    Ressources/ressources.qrc
