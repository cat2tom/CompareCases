////////////////////////////////////////////////////////////////////////////////
//
// CompareDialog.h: Qt-based GUI for prostate cancer radiation therapy planning 
// tool. This window displays two horizontal "panels": the top displays data
// for the "query" patient, i.e., the current patient for whom treatment is 
// being planned.  The lower "panel" displays data for the "match" patient,
// that is, data associated with a prior case who has completed a successful
// program of radiation therapy and has been selected by an algorithm external
// to this code as one of the cases in the database most like the query case.
//
// Each "panel" consists of three widgets, in order left to right: 1) a CT 
// (Computerized Tomography) image data display, including controls for axis
// selection, slice selection, and auto-play (image animation along the current
// slice axis); 2) a projection display, which shows an image projection of the
// overlap or degree of occlusion between the various anatomical structures in
// the treatment area from any of the seven (user-selectable) standard gantry
// angles ("standard" with respect to the system used at Duke Medical Center,
// namely the Eclipse treatment planning system from Palo Alto-based Varian
// Medical Systems); and 3) Dose Volume Histogram (DVH) data as a cartesian
// graph for the selected anatomical structures (femoral head data display
// may be toggled on or off for projection and DVH displays).  
//
// The various user-selectable display options are synchronized so that both 
// query and match data are shown with identical options set (e.g., CT display
// axis, projection gantry angle).  At some future date some or all aspects
// of these displays may be desynchronized, for example if a planning
// physician chooses to look at a different CT slice in the query patient
// than in a match, so the patient and match functionality has been
// separated out in many cases, even though this code currently doesn't
// exploit that separability.
//
// author:  Steve Chall, RENCI
// primary collaborator: Vorakarn Chanyanavich, Duke Medical Center
//
////////////////////////////////////////////////////////////////////////////////

#ifndef COMPARE_DIALOG_H
#define COMPARE_DIALOG_H

#include <QDialog>

#include "ui_CompareDialog.h"  // auto generated from XML output from QT Designer


static const int numDVHPoints = 103; // Based on DVH input data format

// Forward declarations:
class vtkPNGReader;
class vtkImageViewer;
class vtkImageViewer2;
class vtkDICOMImageReader;
class vtkRenderer;
class vtkRenderWindow;
class vtkImageFlip;
class vtkContextView;
class vtkTable;
class vtkChartXY;
class Patient;

class CompareDialog : public QDialog, public Ui_CompareDialog
{
	Q_OBJECT

public:
	enum Structure
	{
		PTV = 0,							// Planning Target Volume
		rectum,
		bladder,
		leftFem,
		rightFem,
		numStructures
	};

	CompareDialog();
	~CompareDialog();

private slots:
	void selectQuery(int patientNum);		// For query CT, projection, DVH displays
	void selectMatch(int patientNum);		// For match CT, projection, DVH displays
	void setSliceAxis(bool val = true);		// Both query and match CT data
	void changeSlice(int slice);			// Both query and match CT data
	void autoplay();						// Both query and match CT data
	void setGantryAngle27();				// All these for projection data, ...
	void setGantryAngle78();				
	void setGantryAngle129();
	void setGantryAngle180();
	void setGantryAngle231();
	void setGantryAngle282();
	void setGantryAngle333();				// ...both query and match.
	void toggleFemoralHeads(bool checked);	// For projection and DVH data. q. and m.

private:
	// General setup methods:
	void setupVTKUI();
	void createActions();

	// CT data display methods:
	void selectQueryCTSlice(int slice);
	void selectMatchCTSlice(int slice);
	void extractQueryDICOMFileMetaData();

	// Projection data display methods:
	void selectQueryProjection();
	void selectMatchProjection();
	void setupProjectionGantryAngleMenu();

	// Dose Volume Histogram data display methods:
	void initQueryDVHObjects();
	void initMatchDVHObjects();
	bool readDVHData(Patient &patient);
	void setupDVHChart(vtkChartXY *chart, char *title);
	void clearDVHPlots(vtkChartXY *chart);

	void displayQueryDVHData();
	void displayMatchDVHData();
	void setDVHYAxisTicks(vtkChartXY *chart);

	// Objects:
	Patient *queryPatient;
	Patient *matchPatient;

	// CT data display objects:
	vtkDICOMImageReader *queryDICOMReader;
	vtkDICOMImageReader *matchDICOMReader;
	vtkImageFlip *queryCTImageFlip;	// CT image orientation appropriate to prostate data
	vtkImageFlip *matchCTImageFlip;	// "
	vtkImageViewer2 *queryCTImageViewer;
	vtkImageViewer2 *matchCTImageViewer;

	// Projection data display objects:
	vtkPNGReader *queryProjectionReader;
	vtkPNGReader *matchProjectionReader;
	vtkImageViewer *queryProjectionViewer;
	vtkImageViewer *matchProjectionViewer;

	// Projection gantry angle drop-down menu elements:
	QMenu *gantryAngleMenu;
	QActionGroup *gantryAngleActionGroup;
	QAction *angle27Action;
	QAction *angle78Action;
	QAction *angle129Action;
	QAction *angle180Action;
	QAction *angle231Action;
	QAction *angle282Action;
	QAction *angle333Action;

	int queryAngle;	// Current gantry angle for query projection display
	int matchAngle; // Current gantry angle for match projection display

	// Dose Volume Histogram data display objects:
	vtkChartXY *queryDVH;
	vtkChartXY *matchDVH;
	vtkContextView *queryDVHView;
	vtkContextView *matchDVHView;

	float dose[numDVHPoints];					// x-axis DVH values 	
	float volumes[numStructures][numDVHPoints];	// y-axis DVH values

	static const int xDVHWidget;				// DVH display width
	static const int yDVHWidget;				// DVH display height

private:
	CompareDialog(const CompareDialog&);				// Not implemented.
	void operator=(const CompareDialog&);			// Not implemented.
};

#endif