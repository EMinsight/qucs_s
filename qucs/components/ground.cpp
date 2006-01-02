/***************************************************************************
                          ground.cpp  -  description
                             -------------------
    begin                : Sat Aug 23 2003
    copyright            : (C) 2003 by Michael Margraf
    email                : michael.margraf@alumni.tu-berlin.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "ground.h"
#include "node.h"


Ground::Ground()
{
  Type = isComponent;   // both analog and digital
  Description = QObject::tr("ground (reference potential)");

  Lines.append(new Line(  0,  0,  0, 10,QPen(QPen::darkBlue,2)));
  Lines.append(new Line(-11, 10, 11, 10,QPen(QPen::darkBlue,3)));
  Lines.append(new Line( -7, 16,  7, 16,QPen(QPen::darkBlue,3)));
  Lines.append(new Line( -3, 22,  3, 22,QPen(QPen::darkBlue,3)));

  Ports.append(new Port(  0,  0));

  x1 = -12; y1 =  0;
  x2 =  12; y2 = 25;

  tx = 0;
  ty = 0;
  Model = "GND";
  Name  = "";
}

Ground::~Ground()
{
}

Component* Ground::newOne()
{
  return new Ground();
}

// -------------------------------------------------------
Element* Ground::info(QString& Name, char* &BitmapFile, bool getNewOne)
{
  Name = QObject::tr("Ground");
  BitmapFile = "gnd";

  if(getNewOne)  return new Ground();
  return 0;
}

// -------------------------------------------------------
QString Ground::NetList()
{
  return QString("");
}

// -------------------------------------------------------
QString Ground::VHDL_Code(int)
{
  QString s = "  ";
  Port *pp = Ports.first();
  s += pp->Connection->Name + " <= ";  // output port
  s += pp->Connection->Name + " and '0';";   // to keep it low all the time
  return s;
}
