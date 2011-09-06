#include "mainwindow.h"

#include <QDebug>
#include <QFile>
#include "datareader.h"

MainWindow::MainWindow(MultiWidgets::GrabManager * application)
{
    QFile * f = new QFile("example.xml");
    DataReader * data = new DataReader( f );

    this->trials = data->trials();

    this->setFixed(true);
    this->setAllowRotation(false);

    this->setInputTransparent(true);
    this->setColor(0, 0, 0, 0);

    this->status = new MultiWidgets::TextBox();
    this->status->setText("");
    this->addChild( this->status );
    this->status->setLocation(800,0);

    this->application = application;

    // initial setup
    this->currentTrial = -1;
    this->nextTrial();
}

void MainWindow::nextTrial()
{
    ExperimentTrial * trial;;
    trial = trials[ this->currentTrial ];
    // causes seg fault!
    // this->deleteChild(trial);

    this->currentTrial++;

    // when finished, show finished text
    if( this->currentTrial >= this->trials.size() ) {
        MultiWidgets::TextBox * text = new MultiWidgets::TextBox();
        text->setText("Test is over, thank you!");
        this->addChild( text );
        return;
    }

    trial = trials[ this->currentTrial ];
    trial->show();
    trial->setApplication( this->application );
    trial->eventAddListener("next_trial", "next_trial", this );

    QString s = QString::number( this->currentTrial + 1) + " of " + QString::number( this->trials.size() );
    this->status->setText( s.toStdString() );

    this->addChild(trial);
}

void MainWindow::processMessage(const char *id, Radiant::BinaryData &data)
{
    if( strcmp( id , "next_trial") == 0 ) {
        this->nextTrial();
    }
}

