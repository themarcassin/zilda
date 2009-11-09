/*
 *  MainWindow.cpp
 *  zILDA
 *
 *  Created by Andre Normann on 05.11.09.
 *  Copyright 2009 Andre Normann. All rights reserved.
 *
 */

// Qt 
#include <QtGui>

// Project
#include "MainWindow.h"
#include "ReaderWriterILDA.h"
#include "Frame.h"

//=======================================================================================

MainWindow::MainWindow(QWidget *parent, Qt::WFlags flags)
: QMainWindow(parent, flags)
{
	setupUi(this);
	
	connect(actionOpen, SIGNAL(triggered()), this, SLOT(fileOpen()));
	
	QGraphicsScene *scene = new QGraphicsScene();
	_noFileLoadedItem = scene->addText(tr("No ILDA sequence loaded"));		
	graphicsView->setScene(scene);
}

//=======================================================================================

MainWindow::~MainWindow()
{
}

//=======================================================================================

void MainWindow::fileOpen()
{
	QFileDialog ofd(this, "Open", "");
	ofd.setFileMode(QFileDialog::AnyFile);
	ofd.setFilter(tr("ILDA files (*.ild);;All files (*.*)"));
	ofd.setViewMode(QFileDialog::Detail);
	
	if (ofd.exec())
	{
		QString fileName = ofd.selectedFiles().at(0);
		QFileInfo fileInfo(fileName);
		
		if (fileInfo.exists())
		{
			ReaderWriterILDA reader;

			_sequence = QSharedPointer<Sequence>(reader.readFile(fileName));

			frameSlider->setRange(0, _sequence->frameCount()-1);
			frameSlider->setSingleStep(1);

			connect(_sequence.data(), SIGNAL(frameChanged(int)), this, SLOT(frameChanged(int)));
			connect(firstFrameButton, SIGNAL(clicked()), _sequence.data(), SLOT(gotoFirstFrame()));
			connect(lastFrameButton, SIGNAL(clicked()), _sequence.data(), SLOT(gotoLastFrame()));
			connect(stopButton, SIGNAL(clicked()), _sequence.data(), SLOT(stopPlayback()));
			connect(playButton, SIGNAL(clicked()), _sequence.data(), SLOT(startPlayback()));
			connect(frameSlider, SIGNAL(valueChanged(int)), _sequence.data(), SLOT(setActiveFrame(int)));

			QGraphicsScene *scene = new QGraphicsScene();
			scene->addItem(_sequence.data());

			graphicsView->setScene(scene);

			resizeEvent(NULL);
		}
	}
}

//=======================================================================================

void MainWindow::resizeEvent(QResizeEvent*)
{
	QRect rect = graphicsView->viewport()->rect();
	float scalingFactor = (rect.height() < rect.width()) ? rect.height() : rect.width();
	scalingFactor /= 65535.0f;
	
	QMatrix matrix;
	matrix.translate(rect.center().x(), rect.center().y());
	matrix.scale(scalingFactor, -scalingFactor);
	
	graphicsView->setMatrix(matrix);	
}

//=======================================================================================

void MainWindow::frameChanged(int newFrameNr)
{
	frameLabel->setText(QString::number(newFrameNr+1));
	frameSlider->setSliderPosition(newFrameNr);
}

//=======================================================================================