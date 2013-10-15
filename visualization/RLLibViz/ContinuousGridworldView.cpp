/*
 * ContinuousGridworldView.cpp
 *
 *  Created on: Oct 11, 2013
 *      Author: sam
 */

#include "ContinuousGridworldView.h"

using namespace RLLibViz;

ContinuousGridworldView::ContinuousGridworldView(QWidget *parent) :
    ViewBase(parent)
{
  // Set the background
  setBackgroundRole(QPalette::Base);
  setAutoFillBackground(true);
}

ContinuousGridworldView::~ContinuousGridworldView()
{
}

void ContinuousGridworldView::initialize()
{
  std::cout << "ContinuousGridworldView" << std::endl;
  vecE = Vec(1.0, 1.0);
  vecX = Vec(0.0f, 0.0f);
  vecY = Vec(width(), height());

  Vec diag = vecY - vecX;
  Mat scaleX = scale(diag.x / vecE.x, 1.0, 1.0);
  Mat scaleY = scale(1.0, diag.y / vecE.y, 1.0);
  Mat trans = translate(vecX);
  T = trans * (scaleX * scaleY);

}

void ContinuousGridworldView::add(QWidget* that, const Vec& p1, const Vec& p2)
{
  if (this != that)
    return;
  current->add(T * p1);
}

void ContinuousGridworldView::draw(QWidget* that)
{
  if (this != that)
    return;
  swap();
  current->clear();
  update();
}


void ContinuousGridworldView::resizeEvent(QResizeEvent* event)
{
  initialize();
}

