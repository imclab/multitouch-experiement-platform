#ifndef EXPERIMENTTRIAL_H
#define EXPERIMENTTRIAL_H

#include <MultiWidgets/Widget.hpp>
#include <MultiWidgets/GrabManager.hpp>
#include <MultiWidgets/SimpleSDLApplication.hpp>

#include "locationawarewidget.h"
#include "connectioncheck.h"


class ExperimentTrial : public MultiWidgets::Widget
{
public:
    enum RotationDirection {Clockwise, Counterclockwise};
    ExperimentTrial( int id, RotationDirection direction, int distance, int size, int angle, int x1, int y1);
    void setApplication( MultiWidgets::GrabManager * application);

private:
    int id;
    RotationDirection direction;
    int size;
    double angle;
    int distance;
    int x1;
    int y1;

    void createUI();
    LocationAwareWidget * createMovable(int x, int y);

    LocationAwareWidget * first;
    LocationAwareWidget * second;

    ConnectionCheck * firstCheck;
    ConnectionCheck * secondCheck;

    MultiWidgets::GrabManager * application;

    virtual void processMessage (const char * id, Radiant::BinaryData & data);
};

#endif // EXPERIMENTTRIAL_H
