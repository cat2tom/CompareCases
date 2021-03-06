////////////////////////////////////////////////////////////////////////////////
//
// MainWindow.cpp: Qt-based GUI for prostate cancer radiation therapy treatment 
// tool. This window allows the user to select top-level data source
// directories for the current three institutions providing that data: Duke, 
// Pocono, and High Point. The data must be in the specified directory
// organization beneath that top level. Once one or more of these directories
// are determined, the user may then select a particular patient case from the
// established institutions for use as query case. Once a specific query case
// is selected, the View Case Space button, which opens the Case Space dialog
// for selecting a match case, is enabled.
//
// Author:    Steve Chall, RENCI
//
// Primary collaborators: 
//            Joseph Lo, Shiva Das, Vorakarn Chanyavanich, Duke Medical Center
//
// Copyright: The Renaissance Computing Institute (RENCI)
//
// License:   Licensed under the RENCI Open Source Software License v. 1.0
//
//            See http://www.renci.org/resources/open-source-software-license
//            for details.
//
////////////////////////////////////////////////////////////////////////////////

#include <QtGui>
#include "CaseSpaceDialog.h"
#include "MainWindow.h"

///ctor/////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
MainWindow::MainWindow()
  : versionNumber(360),
    queryCaseSourceInstitution(kDuke),
    queryCasePatientNumber(-1),
    dukeDataDirName(""),
    dukeDataDirFile("./PathToDukeData"),
    selectDukeQueryCaseAction(NULL),
    selectPoconoQueryCaseAction(NULL),
    selectHighPointQueryCaseAction(NULL),
    caseSpaceDialog(NULL)
{
  setupUi(this);

  if (!dukeDataDirFile.open(QIODevice::ReadOnly))
  {
    selectDukeDirectory();  
  }
  else
  {
    dukeDataDirName = dukeDataDirFile.readLine();
    dukeDataDirFile.close();
  }

  setupSelectQueryCaseComboBoxes();
  createActions();

  loadDukeLineEdit->setText(dukeDataDirName);
  dukeQueryCaseComboBox->setDisabled(false);
  poconoQueryCaseComboBox->setDisabled(true);
  highPointQueryCaseComboBox->setDisabled(true);
  viewCaseSpaceButton->setDisabled(true);
}

///dtor/////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
MainWindow::~MainWindow()
{
  if (selectDukeQueryCaseAction) delete selectDukeQueryCaseAction;
  if (selectPoconoQueryCaseAction) delete selectPoconoQueryCaseAction;
  if (selectHighPointQueryCaseAction) delete selectHighPointQueryCaseAction;
};

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void MainWindow::openCaseSpaceDialog()
{
  caseSpaceDialog = new CaseSpaceDialog(this);
  caseSpaceDialog->show();
}

////////////////////////////////////////////////////////////////////////////////
//
// dukeDataDirFile is a QFile object that points to a text file that holds a
// string which represents the top-level directory that contains the Duke data.
// This method is constructed to be called when the user wants to write the path
// to that top-level Duke data directory into the text file (either an attempt
// to open that text file has failed, or else that the user wants to explicitly
// set the path string in that file). It opens a file dialog so that the user 
// can make that selection, and writes the selected path to the text file.  If
// data directory path selection succeeds, the list of Duke cases is set up in 
// dukeQueryCaseComboBox which is then enabled, the path is written into 
// loadDukeLineEdit, and the selected path is written to the file pointed to by
// dukeDataDirFile for future use.
//
////////////////////////////////////////////////////////////////////////////////
void MainWindow::selectDukeDirectory()
{
  QFileDialog *dlg = new QFileDialog();
  dlg->setMode(QFileDialog::Directory);
  dlg->setOption(QFileDialog::ShowDirsOnly);

  dukeDataDirName = dlg->getExistingDirectory(0,
    tr("Select directory for Duke case data"), ".");

  if (!dukeDataDirName.isEmpty())
  {
    setupDukeSelectQueryCaseComboBox();

    if (!dukeDataDirFile.open(QIODevice::WriteOnly))
    {
      QString warn = "Failed to open \"PathToDukeData\"";
      QMessageBox::warning(this, tr("File Open Failed"), warn);
    }
    else
    {
      dukeDataDirFile.write(dukeDataDirName);
      dukeDataDirFile.close();
    }

    loadDukeLineEdit->setText(dukeDataDirName);
    dukeQueryCaseComboBox->setDisabled(false);
  }
}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void MainWindow::selectPoconoDirectory()
{
  QFileDialog *dlg = new QFileDialog();
  dlg->setMode(QFileDialog::Directory);
  dlg->setOption(QFileDialog::ShowDirsOnly);

  poconoDir = dlg->getExistingDirectory(0,
    tr("Select directory for Pocono case data"), ".");

  if (!poconoDir.isEmpty())
  {
    loadPoconoLineEdit->setText(poconoDir);
    poconoQueryCaseComboBox->setDisabled(false);
  }
}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void MainWindow::selectHighPointDirectory()
{
  QFileDialog *dlg = new QFileDialog();
  dlg->setMode(QFileDialog::Directory);
  dlg->setOption(QFileDialog::ShowDirsOnly);

  highPointDir = dlg->getExistingDirectory(0,
    tr("Select directory for High Point case data"), ".");

  if (!highPointDir.isEmpty())
  {
    loadHighPointLineEdit->setText(highPointDir);
    highPointQueryCaseComboBox->setDisabled(false);
  }
}

////////////////////////////////////////////////////////////////////////////////
// 
// Associate the appropriate responses to user manipulation of the GUI controls.
//
////////////////////////////////////////////////////////////////////////////////
void MainWindow::createActions()
{
  connect(viewCaseSpaceButton, SIGNAL(clicked()), this,
    SLOT(openCaseSpaceDialog()));

  connect(actionSelect_Duke_Directory, SIGNAL(triggered()), this,
    SLOT(selectDukeDirectory()));
  connect(actionSelect_Pocono_Directory, SIGNAL(triggered()), this,
    SLOT(selectPoconoDirectory()));
  connect(actionSelect_High_Point_Directory, SIGNAL(triggered()), this,
    SLOT(selectHighPointDirectory()));

  connect(loadDukePushButton, SIGNAL(clicked()), this,
    SLOT(selectDukeDirectory()));
  connect(loadPoconoPushButton, SIGNAL(clicked()), this,
    SLOT(selectPoconoDirectory()));
  connect(loadHighPointPushButton, SIGNAL(clicked()), this,
    SLOT(selectHighPointDirectory()));

  connect(dukeQueryCaseComboBox, SIGNAL(currentIndexChanged(int)), this,
    SLOT(selectDukeQueryCase(int)));
  connect(poconoQueryCaseComboBox, SIGNAL(currentIndexChanged(int)), this,
    SLOT(selectPoconoQueryCase(int)));
  connect(highPointQueryCaseComboBox, SIGNAL(currentIndexChanged(int)), this,
    SLOT(selectHighPointQueryCase(int)));

  actionExit->setShortcut(tr("Ctrl+Q"));
  connect(actionExit, SIGNAL(triggered()), this, SLOT(close()));

  connect(actionAbout_CompareCases, SIGNAL(triggered()), this, SLOT(about()));
  connect(action_View_documentation, SIGNAL(triggered()), this,
    SLOT(viewDocumentation()));
}

////////////////////////////////////////////////////////////////////////////////
//
// NOTE: relative path from master Duke directory to data currently hardwired.
//
////////////////////////////////////////////////////////////////////////////////
bool MainWindow::setupDukeSelectQueryCaseComboBox()
{
  selectDukeQueryCaseAction = new QAction(dukeQueryCaseComboBox);
  dukeQueryCaseComboBox->addAction(selectDukeQueryCaseAction); 
  dukeQueryCaseComboBox->addItem(QString("-"));

  // for each Duke patient for which we have overlap data, create a combo
  // box item:
  dukeXYDataPath = dukeDataDirName + "/overlap/Duke_struct_overlap";
  QString defaultPath = dukeXYDataPath + "Avg.txt";

  QFile file(defaultPath);

  if (!file.open(QIODevice::ReadOnly))
  {
    QString warn = "Failed to open \"" + defaultPath + "\"";
    QMessageBox::warning(this, tr("File Open Failed"), warn);
    return false;
  }

  QTextStream in(&file);
 
  in.readLine();    // Skip over the first line (column headers):

  int index;

  while (!in.atEnd())
  {
    in >> index;
    in.readLine();  // for now, throw the rest of the line away
    dukeQueryCaseComboBox->addItem(QString::number(index)); 
  }

  in.flush();
  file.close();

  return true;
}

////////////////////////////////////////////////////////////////////////////////
// 
// 2do: Need to extend to include non-Duke institutions when their data becomes
// available.
//
////////////////////////////////////////////////////////////////////////////////
void MainWindow::setupSelectQueryCaseComboBoxes()
{
  QFile dataDir(dukeDataDirName);

  if (dataDir.exists())
  {
    setupDukeSelectQueryCaseComboBox();
  }

/*
  // Dummy values
  selectPoconoQueryCaseAction = new QAction(poconoQueryCaseComboBox);
  poconoQueryCaseComboBox->addAction(selectPoconoQueryCaseAction); 
  poconoQueryCaseComboBox->addItem(QString("-")); 

  for (int i = 1; i < 30; i++)
  {
    poconoQueryCaseComboBox->addItem(QString::number(i)); 
  }

  selectHighPointQueryCaseAction = new QAction(highPointQueryCaseComboBox);
  highPointQueryCaseComboBox->addAction(selectHighPointQueryCaseAction); 
  highPointQueryCaseComboBox->addItem(QString("-")); 

  for (int i = 1; i < 200; i++)
  {
    highPointQueryCaseComboBox->addItem(QString::number(i)); 
  }
*/
}

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void MainWindow::selectDukeQueryCase(int index)
{  
  if (index == 0)
  {
    queryCaseNameLabel->setText("<not selected>");
  }

  if (queryCaseSourceInstitution != kDuke)
  {
    poconoQueryCaseComboBox->setCurrentIndex(0);
    highPointQueryCaseComboBox->setCurrentIndex(0);
  }

  QString patientNumAsText = dukeQueryCaseComboBox->itemText(index);
  queryCasePatientNumber = patientNumAsText.toInt();
  QString queryCasePatientDescriptor = "Duke patient #" + patientNumAsText;
  queryCaseNameLabel->setText(queryCasePatientDescriptor);

  queryCaseSourceInstitution = kDuke;

  setViewCaseSpacePushButtonEnabling();
}

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void MainWindow::selectPoconoQueryCase(int index)
{
  if (index == 0)
  {
    queryCaseNameLabel->setText("<not selected>");
  }

  if (queryCaseSourceInstitution != kPocono)
  {
    dukeQueryCaseComboBox->setCurrentIndex(0);
    highPointQueryCaseComboBox->setCurrentIndex(0);
  }

  QString patientNumAsText = poconoQueryCaseComboBox->itemText(index);
  queryCasePatientNumber = patientNumAsText.toInt();
  QString queryCasePatientDescriptor = "Pocono patient #" + patientNumAsText;
  queryCaseNameLabel->setText(queryCasePatientDescriptor);

  queryCaseSourceInstitution = kPocono;

  setViewCaseSpacePushButtonEnabling();
}

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void MainWindow::selectHighPointQueryCase(int index)
{
  if (index == 0)
  {
    queryCaseNameLabel->setText("<not selected>");
  }

  if (queryCaseSourceInstitution != kHighPoint)
  {
    dukeQueryCaseComboBox->setCurrentIndex(0);
    poconoQueryCaseComboBox->setCurrentIndex(0);
  }

  QString patientNumAsText = highPointQueryCaseComboBox->itemText(index);
  queryCasePatientNumber = patientNumAsText.toInt();
  QString queryCasePatientDescriptor =
    "High Point patient #" + patientNumAsText;
  queryCaseNameLabel->setText(queryCasePatientDescriptor);

  queryCaseSourceInstitution = kHighPoint;

  setViewCaseSpacePushButtonEnabling();
}

void MainWindow::viewDocumentation()
{
  QMessageBox::information(this, "view docs", "view docs");
}

void MainWindow::about()
{
  QString versionNumberAsString;
  versionNumberAsString.setNum(versionNumber);
  QString info = "CompareCases\nDevelopment version #"
    + versionNumberAsString;
  info.append("\n\nCompareCases is a tool for assisting in the planning of ");
  info.append("prostate cancer radiotherapy.\n");
  info.append("It's currently under development at RENCI@Duke University.");
  info.append("\n\nContributors include:\n");
  info.append("Steve Chall, Renaissance Computing Institute\n");
  info.append("Shiva Das, Duke University\n");
  info.append("Joseph Lo, Duke University\n");
  info.append("Vorakarn Chanyavanich, Emory University\n\n");

  info.append("The open source CompareCases application is implemented");
  info.append(" using\nMicrosoft Visual C++ 2010\n");
  info.append("Qt 4.71\n");
  info.append("VTK 5.8.0\n");
  info.append("CMake 2.8.3\n");
  info.append("GitHub (https://github.com/steve9000gi/CompareCases)");   
  QMessageBox::about(this, tr("About CompareCases"), info);
}

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void MainWindow::close()
{  
  if (caseSpaceDialog) caseSpaceDialog->close();

  QMainWindow::close();
}

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void MainWindow::setViewCaseSpacePushButtonEnabling()
{
  viewCaseSpaceButton->setDisabled(
    (dukeQueryCaseComboBox->currentIndex() == 0) &&
    (poconoQueryCaseComboBox->currentIndex() == 0) &&
    (highPointQueryCaseComboBox->currentIndex() == 0));
}