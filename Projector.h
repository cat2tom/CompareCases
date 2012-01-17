//////////////////////////////////////////////////////////////////////////////
//
// Projector.h:  Object to read files generated by modified CERR (Matlab)
// code, (in visualStruct3D.m), place the data thereby acquired into a
// vtkPolyData object, color according to the agreed-upon convention, and
// display images.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef PROJECTOR_H
#define PROJECTOR_H

#include <qstring.h>

#define STRAIGHTPIPE 0 // Skip decimation and smoothing if non-zero
#define USE_PROJECTOR_SLICE_PLANE 0

// To initialize variables for holding geometric extrema:
const double kMinInit = DBL_MAX;
const double kMaxInit = -DBL_MAX;

const int kMaxChars = 255;
const int kMaxFileTypeChars = 9;
const int kMaxStructureTypeChars = 8;

// The Carl Zhang/Vorakarn Chanyavanich convention for naming input files:
//     <inFileType>_<patient number>_<structure>.out
// where <inFileType> = [ "faces" | "vertices" ],
//       <patient number> is a 3-digit integer (possibly front-padded with 0's),
// and   <structure>  = [ "bladder" | "LtFem" | "PTV" | "rectum" | "RtFem" ].
//

// forward declarations:
class vtkPoints;
class vtkCellArray;
class vtkPolyData;
class vtkDecimatePro;
class vtkSmoothPolyDataFilter;
class vtkPolyDataNormals;
class vtkPolyDataMapper;
class vtkActor;
class vtkRenderer;
class vtkRenderWindowInteractor;
class vtkRenderWindow; 
class vtkTextActor;
class vtkAssembly;
class QVTKWidget;
class vtkCubeSource;

class Projector
{
public:
  enum eInFileType
  {
    ekFaces = 0,
    ekVertices
  };

  static const int kNumInFileTypes; // = ekVertices + 1;

  enum eStructureType
  {
    ekBladder = 0,
    ekLtFem = 1,
    ekPTV = 2,
    ekRectum = 3,
    ekRtFem = 4,
    kNumStructureTypes = 5, // = last structure type + 1: currently no body
    ekBody = 5
  };

  Projector();
  Projector(QString dataDir);
  ~Projector();

  void setFlatShaded(bool value) { flatShaded = value; };
  void setDrawStructure(int sNum, bool value) { drawStructure[sNum] = value; };
  void setTransparency(int transp);
  vtkRenderer *GetRenderer() { return renderer; };
  void WindowInit(vtkRenderWindow *renWin, QVTKWidget *qVTKWidget);
  void InitExtrema(void);
  void PrintStructureName(eStructureType structureNum);
  void ComputeAverages(void);
  static void ReportCameraPosition(vtkRenderer *renderer);
  void SetCameraPosition(vtkRenderer *renderer, double pos[3], double fp[3], double vUp[3]);
  void SetCameraPosition(double az);
  void UpdateExtrema(eStructureType structure, double v[3]);
  bool BuildStructure(int patientNum, eStructureType st);
  bool BuildStructuresForPatient(int patientNum, bool isDifferentPatient = false);
  void InitAxes(void);
  void TextInit(void);
  void InitLegend(void);
  void SetProjection(int patientNum, int queryAngle);
  void InitSlicePlane();
  void PositionSlicePlane(int orientation, int slice, double *spacing);
  void PositionSlicePlane(int orientation, int slice, int numSlices);

private:
  vtkPoints *points[kNumStructureTypes];
  vtkCellArray *polys[kNumStructureTypes];
  vtkPolyData *structure[kNumStructureTypes];
  vtkDecimatePro *deci[kNumStructureTypes];
  vtkSmoothPolyDataFilter *smoother[kNumStructureTypes];
  vtkPolyDataNormals *normals[kNumStructureTypes];
  vtkPolyDataMapper *mapper[kNumStructureTypes];
  vtkActor *actor[kNumStructureTypes];

  QVTKWidget *vtkWidget;
  vtkRenderWindowInteractor *renderWindowInteractor;
  vtkRenderWindow *renWin; 
  vtkTextActor *textActor;

  vtkCubeSource *slicePlane;
  vtkPolyDataMapper *sliceMapper;
  vtkActor *sliceActor;

  vtkTextActor *legendTextActor[kNumStructureTypes]; 
  vtkTextActor *dummy[kNumStructureTypes]; 

  bool isPatientChanged;
  bool flatShaded;
  bool drawStructure[kNumStructureTypes];
  int transparency; // percentage

  QString inPathFormat;

  vtkRenderer *renderer;

  double minX;
  double maxX;
  double avgX; 
  double minY;
  double maxY;
  double avgY; 
  double minZ;
  double maxZ;
  double avgZ; 
};

#endif // #ifndef PROJECTOR_H