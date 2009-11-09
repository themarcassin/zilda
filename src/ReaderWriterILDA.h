/*
 *  ReadWriterILDA.h
 *  zILDA
 *
 *  Created by Andre Normann on 06.11.09.
 *  Copyright 2009 Andre Normann. All rights reserved.
 *
 */

#pragma once

// Qt
#include <QtCore>

// Project
#include "Sequence.h"


class ReaderWriterILDA
{
public:

			ReaderWriterILDA();
	virtual ~ReaderWriterILDA();

	Sequence*	readFile(const QString& fileName);

	int			version() const { return _ildaVersion; }


private:
	
	bool	readTrueColorSection(QDataStream& stream);
	bool	readFrameSection(QDataStream& stream, bool is3DFrame);
	void	readHeader(QDataStream& stream, QString& name, 
					   QString& companyName, quint16& entryCount, 
					   quint16& objectNumber, quint16& objectCount);

	Sequence		*_sequence;
	QVector<QColor> _currentPalette;
	QVector<QColor> _defaultIldaPalette;
	int				_ildaVersion;
};
