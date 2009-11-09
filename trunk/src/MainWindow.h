/*
 *  MainWindow.h
 *  zILDA
 *
 *  Created by Andre Normann on 05.11.09.
 *  Copyright 2009 Andre Normann. All rights reserved.
 *
 */

#pragma once

// Qt
#include <QtGui>

// Project
#include "ui_MainWindow.h"

class Sequence;

class MainWindow : 
	public QMainWindow,
	protected Ui_MainWindow
{
	Q_OBJECT
	
public:
	
			MainWindow(QWidget *parent = 0L, Qt::WFlags flags = 0);
	virtual ~MainWindow();


protected:

	void	resizeEvent(QResizeEvent *event);

	
protected slots:

	void	fileOpen();


private:

	QSharedPointer<Sequence>	_sequence;
	QGraphicsTextItem			*_noFileLoadedItem;
};
