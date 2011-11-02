//////////////////////////////////////////////////////////////////////////////
//
// Projector.h:  Object to read files generated by modified CERR (Matlab)
// code, (in visualStruct3D.m), place the data thereby acquired into a
// vtkPolyData object, color according to the agreed-upon convention, and
// display images.
//
//////////////////////////////////////////////////////////////////////////////

#include "windows.h" 
#include <float.h>

#include <QtGui>
#include "qvtkwidget.h"

#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkProperty.h"
#include "vtkCamera.h"
#include "vtkRenderer.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderWindow.h"
#include "vtkVectorText.h"
#include "vtkConeSource.h"
#include "vtkCubeSource.h"
#include "vtkCylinderSource.h"
#include "vtkFollower.h"
#include "vtkTextActor.h"
#include "vtkTextProperty.h"
#include "vtkCommand.h"
#include "vtkWindowToImageFilter.h"
#include "vtkPNGWriter.h"
#include "vtkCellArray.h"
#include "vtkDecimatePro.h"
#include "vtkPolyDataNormals.h"
#include "vtkSmoothPolyDataFilter.h"
#include "vtkAxes.h"
#include "vtkWindowToImageFilter.h"
#include "vtkAssembly.h"

#include "Projector.h"

using namespace std;

// Global window size and position:
static const int kRenWinX = 256;
static const int kRenWinY = 256;

// Global: Structures don't show up in release build if class members:
vtkTextActor *legendTextActor[Projector::kNumStructureTypes]; 
bool usedThemUp = false; // HACK because multiple Projectors now share single legend

// const member initializations:
const int Projector::kNumInFileTypes = ekVertices + 1;

static const char inFileType[Projector::kNumInFileTypes][kMaxFileTypeChars] = {"faces", "vertices"};

static const char structureType[Projector::kNumStructureTypes][kMaxFileTypeChars] = 
	{"bladder", "LtFem", "PTV", "rectum", "RtFem" /*, "body" */};


// 2011/05/02: values from current CompareDialog:
static const double structureColor[Projector::kNumStructureTypes][3] =
{
	1.0, 0.84, 0.0,			// bladder "golden yellow"
	0.33, 0.33, 0.4,		// left femoral head blue-gray
	0.9, 0.0, 0.0,			// PTV red     
	0.545, 0.271, 0.075,	// rectum "saddle brown"
	0.67, 0.67, 0.67		// right femoral head lite gray
//		0.961, 0.8, 0.69		// flesh F5CCB0 = 245, 204, 176 = 0.961, 0.8, 0.69
};

// The Carl Zhang/Vorakarn Chanyavanich convention for naming structure 
// geometry input files:
//
//     <inFileType>_<patient number>_<structure>.out
// where <inFileType> = [ "faces" | "vertices" ],
//       <patient number> is a 3-digit integer (possibly front-padded with 0's),
// and   <structure>  = [ "bladder" | "LtFem" | "PTV" | "rectum" | "RtFem" ].
//
//char inPathFormat[] = 
//"C:/Users/Steve/Documents/IMRT/Zhang-test/PMC069_body_included/%s_PMC%03d_%s.out"; // test case for body
//"C:/Users/Steve/Documents/IMRT/structures-2010-11-30/%03d/%s_%03d_%s.out";
//"C:/Duke_Cases_2011-06-13/structures/%03d/%s_%03d_%s.out";

class RendererCallback : public vtkCommand
{
public:
  static RendererCallback *New() { return new RendererCallback; }

  ///Execute////////////////////////////////////////////////////////////////////
  // 
  // Gets called whenever the user interactively manipulates the camera.  
  //
  //////////////////////////////////////////////////////////////////////////////
  virtual void Execute(vtkObject *caller, unsigned long, void *)
  {
    vtkRenderer *r = vtkRenderer::SafeDownCast(caller);
	double clip[2];
	r->GetActiveCamera()->GetClippingRange(clip);
	cout << "RendererCallback::Execute(...) clip: " << clip[0] << ", " << clip[1] << endl;

    //Projector::ReportCameraPosition(r);
  }
};

///ctor/////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
Projector::Projector()
	:	structure(NULL),
		deci(NULL),
		smoother(NULL),
		normals(NULL),
		mapper(NULL),
		actor(NULL),
		renderWindowInteractor(NULL),
		renWin(NULL), 
		textActor(NULL),
		renderer(NULL),
		isPatientChanged(true),
		flatShaded(true),
		noFemoralHeads(false),
		avgX(0.0),
		minX(kMinInit),
		maxX(kMaxInit),
		avgY(0.0),
		minY(kMinInit),
		maxY(kMaxInit),
		avgZ(0.0),
		minZ(kMinInit),
		maxZ(kMaxInit),
		slicePlane(NULL)
{
	for (int i = ekBladder; i < kNumStructureTypes; i++)
	{
		drawStructure[i] = true;

		if (!usedThemUp) legendTextActor[i] = NULL;
	}
}

///ctor/////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
Projector::Projector(QString dataDir)
	:	structure(NULL),
		deci(NULL),
		smoother(NULL),
		normals(NULL),
		mapper(NULL),
		actor(NULL),
		renderWindowInteractor(NULL),
		renWin(NULL), 
		textActor(NULL),
		renderer(NULL),
		isPatientChanged(true),
		flatShaded(true),
		noFemoralHeads(false),
		avgX(0.0),
		minX(kMinInit),
		maxX(kMaxInit),
		avgY(0.0),
		minY(kMinInit),
		maxY(kMaxInit),
		avgZ(0.0),
		minZ(kMinInit),
		maxZ(kMaxInit),
		slicePlane(NULL)
{
	inPathFormat = dataDir + "/structures/%03d/%s_%03d_%s.out";

	for (int i = ekBladder; i < kNumStructureTypes; i++)
	{
		drawStructure[i] = true;

		if (!usedThemUp) legendTextActor[i] = NULL;
	}
}

///AddFollowingText/////////////////////////////////////////////////////////////
// 
// Specify some text, where you want it to go in 3-space, a color, and a
// renderer, and it will always face the active camera associated with that
// renderer.
//
////////////////////////////////////////////////////////////////////////////////
vtkFollower *Projector::AddFollowingText(char *text, double x, double y, double z,
	double r, double g, double b, vtkRenderer *ren)
{
  vtkVectorText *xText = vtkVectorText::New();;
  vtkPolyDataMapper *xTextMapper = vtkPolyDataMapper::New();
  vtkFollower *xTextActor = vtkFollower::New();

  xText->SetText(text);
  xTextMapper->SetInputConnection(xText->GetOutputPort());
  xTextActor->SetMapper(xTextMapper);
  xTextActor->SetScale(2, 2, 2);
  xTextActor->AddPosition(x, y, z);
  xTextActor->GetProperty()->SetColor(r, g, b);
  xTextActor->SetCamera(ren->GetActiveCamera());
  ren->AddActor(xTextActor);

  xText->Delete();

  return xTextActor;
}

void Projector::setTransparency(int transp)
{
	transparency = transp;
}

///AddOrigin////////////////////////////////////////////////////////////////////
//
// The standard three arrows -- red = x, green = y, blue = z -- emanating from a
// white cube.
//
////////////////////////////////////////////////////////////////////////////////
void Projector::AddOrigin(vtkRenderer *renderer, double shaftLength /* = 20.0 */)
{
	vtkActor *oActor = NULL;
	vtkActor *xConeActor = NULL;
	vtkActor *yConeActor = NULL;
	vtkActor *zConeActor = NULL;
	vtkActor *xShaftActor = NULL;
	vtkActor *yShaftActor = NULL;
	vtkActor *zShaftActor = NULL;

	vtkConeSource *xCone = vtkConeSource::New();
	vtkPolyDataMapper *xConeMapper = vtkPolyDataMapper::New();
	xConeActor = vtkActor::New();
	xCone->SetResolution(40);
	xCone->SetHeight(shaftLength / 10.0);
	xCone->SetRadius(shaftLength * 0.0375);
	xCone->SetDirection(1, 0, 0);
	xConeMapper->SetInputConnection(xCone->GetOutputPort());
	xConeActor->SetPosition(shaftLength, 0, 0);
	xConeMapper->ScalarVisibilityOff();
	xConeActor->SetMapper(xConeMapper);
	xConeActor->GetProperty()->SetColor(1, 0, 0);
  
	vtkCylinderSource *xShaft = vtkCylinderSource::New();
	vtkPolyDataMapper *xShaftMapper = vtkPolyDataMapper::New();
	xShaftActor = vtkActor::New();
	xShaft->SetResolution(40);
	xShaft->SetHeight(shaftLength);
	xShaft->SetRadius(shaftLength / 200.0);
	xShaftMapper->SetInputConnection(xShaft->GetOutputPort());
	xShaftMapper->ScalarVisibilityOff();
	xShaftActor->RotateZ(90);
	xShaftActor->SetPosition(shaftLength / 2.0, 0, 0);
	xShaftActor->SetMapper(xShaftMapper);
	xShaftActor->GetProperty()->SetColor(1, 0, 0);

	vtkConeSource *yCone = vtkConeSource::New();
	vtkPolyDataMapper *yConeMapper = vtkPolyDataMapper::New();
	yConeActor = vtkActor::New();
	yCone->SetResolution(40);
	yCone->SetHeight(shaftLength / 10.0);
	yCone->SetRadius(shaftLength * 0.0375);
	yCone->SetDirection(0, 1, 0);
	yConeMapper->SetInputConnection(yCone->GetOutputPort());
	yConeActor->SetPosition(0, shaftLength, 0);
	yConeMapper->ScalarVisibilityOff();
	yConeActor->SetMapper(yConeMapper);
	yConeActor->GetProperty()->SetColor(0, 1, 0);
  
	vtkCylinderSource *yShaft = vtkCylinderSource::New();
	vtkPolyDataMapper *yShaftMapper = vtkPolyDataMapper::New();
	yShaftActor = vtkActor::New();
	yShaft->SetResolution(40);
	yShaft->SetHeight(shaftLength);
	yShaft->SetRadius(shaftLength / 200.0);
	yShaftMapper->SetInputConnection(yShaft->GetOutputPort());
	yShaftMapper->ScalarVisibilityOff();
	yShaftActor->SetPosition(0, shaftLength / 2.0, 0);
	yShaftActor->SetMapper(yShaftMapper);
	yShaftActor->GetProperty()->SetColor(0, 1, 0);

	vtkConeSource *zCone = vtkConeSource::New();
	vtkPolyDataMapper *zConeMapper = vtkPolyDataMapper::New();
	zConeActor = vtkActor::New();
	zCone->SetResolution(40);
	zCone->SetHeight(shaftLength / 10.0);
	zCone->SetRadius(shaftLength * 0.0375);
	zCone->SetDirection(0, 0, 1);
	zConeMapper->SetInputConnection(zCone->GetOutputPort());
	zConeActor->SetPosition(0, 0, shaftLength);
	zConeMapper->ScalarVisibilityOff();
	zConeActor->SetMapper(zConeMapper);
	zConeActor->GetProperty()->SetColor(0, 0, 1);
  
	vtkCylinderSource *zShaft = vtkCylinderSource::New();
	vtkPolyDataMapper *zShaftMapper = vtkPolyDataMapper::New();
	zShaftActor = vtkActor::New();
	zShaft->SetResolution(40);
	zShaft->SetHeight(shaftLength);
	zShaft->SetRadius(shaftLength / 200.0);
	zShaftMapper->SetInputConnection(zShaft->GetOutputPort());
	zShaftMapper->ScalarVisibilityOff();
	zShaftActor->RotateX(90);
	zShaftActor->SetPosition(0, 0, shaftLength / 2.0);
	zShaftActor->SetMapper(zShaftMapper);
	zShaftActor->GetProperty()->SetColor(0, 0, 1);
  
	vtkCubeSource *origin = vtkCubeSource::New();
	vtkPolyDataMapper *oMapper = vtkPolyDataMapper::New();
	oActor = vtkActor::New();
	origin->SetXLength(shaftLength * 0.025);
	origin->SetYLength(shaftLength * 0.025);
	origin->SetZLength(shaftLength * 0.025);
	oMapper->SetInputConnection(origin->GetOutputPort());
	oMapper->ScalarVisibilityOff();
	oActor->SetMapper(oMapper);
	oActor->GetProperty()->SetColor(1, 1, 1);
  
	char x[] = "+x";
	char y[] = "+y";
	char z[] = "+z";

	double textLabelOffset = shaftLength / 20.0; 
	vtkFollower *xf = AddFollowingText(x, shaftLength + textLabelOffset, -textLabelOffset, 0, 1, 0, 0, renderer);
	vtkFollower *yf = AddFollowingText(y, -textLabelOffset, shaftLength + textLabelOffset, 0, 0, 1, 0, renderer);
	vtkFollower *zf = AddFollowingText(z, 0, -textLabelOffset, shaftLength + 2 *textLabelOffset, 0, 0, 1, renderer);

	xf->SetScale(shaftLength / 30.0);
	yf->SetScale(shaftLength / 30.0);
	zf->SetScale(shaftLength / 30.0);

  	renderer->AddActor(xConeActor);
  	renderer->AddActor(yConeActor);
	renderer->AddActor(zConeActor);
	renderer->AddActor(xShaftActor);
	renderer->AddActor(yShaftActor);
	renderer->AddActor(zShaftActor);
	renderer->AddActor(oActor);
	renderer->AddActor(xf);
	renderer->AddActor(yf);
	renderer->AddActor(zf);
}

///WindowInit//////////////////////////////////////////////////////////////////
//
// Set up the window and associated objects like the renderer, etc.
//
////////////////////////////////////////////////////////////////////////////////
void Projector::WindowInit(vtkRenderWindow *renWin, QVTKWidget *qVTKWidget)
{
  renderer = vtkRenderer::New();
  //renderer->SetBackground(0.8, 0.8, 0.8); // like CERR
  RendererCallback *callback = RendererCallback::New();
  renderer->AddObserver(vtkCommand::StartEvent, callback);
  callback->Delete();

  this->renWin = renWin;
  renWin->SetWindowName("cartoon projection");
  renWin->AddRenderer(renderer);
  renWin->SetSize(kRenWinX, kRenWinY);

  renderWindowInteractor = qVTKWidget->GetInteractor();
  renderWindowInteractor->SetRenderWindow(renWin);
}

///InitExtrema//////////////////////////////////////////////////////////////////
//
// Note:  if InitExtrema() is not called before WindowInit(), the value for 
// actor is either uninitialized or overwritten, thus triggering an access  
// violation. ??SAC
//
////////////////////////////////////////////////////////////////////////////////
void Projector::InitExtrema(void)
{  
  minX = kMinInit;
  maxX = kMaxInit;
  minY = kMinInit;
  maxY = kMaxInit;
  minZ = kMinInit;
  maxZ = kMaxInit;
}

///PrintStructureName///////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void Projector::PrintStructureName(eStructureType structureNum)
{
  cout << structureType[structureNum] << ". ";
}  

///ComputeAverages///////////////////////////////////////////////////////////////
//
// avgZ is used to set the camera's position and focal point, so this method
// is therefore not an optional diagnostic function.
//
////////////////////////////////////////////////////////////////////////////////
void Projector::ComputeAverages(void)
{
  avgX = (minX + maxX) / 2.0;
  avgY = (minY + maxY) / 2.0;
  avgZ = (minZ + maxZ) / 2.0;
}

///ReportCameraPosition/////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void Projector::ReportCameraPosition(vtkRenderer *renderer)
{
  double pos[3], fp[3], vUp[3];
  renderer->GetActiveCamera()->GetPosition(pos);
  renderer->GetActiveCamera()->GetFocalPoint(fp);  
  renderer->GetActiveCamera()->GetViewUp(vUp);  
 cout << "\n///Active Camera////////////////////////////////////" << endl;
 cout << "position: (" << pos[0] << ", " << pos[1] << ", " << pos[2] << ")"
      << endl;
 cout << "focal point: (" << fp[0] << ", " << fp[1] << ", " << fp[2] << ")"
      << endl;
 cout << "view up: (" << vUp[0] << ", " << vUp[1] << ", " << vUp[2] << ")"
      << endl;
      
 cout << "////////////////////////////////////////////////////" << endl;
}

///SetCameraPosition////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void Projector::SetCameraPosition(vtkRenderer *renderer, 
	double pos[3], double fp[3], double vUp[3])
{
  renderer->GetActiveCamera()->SetPosition(pos);
  renderer->GetActiveCamera()->SetFocalPoint(fp);  
  renderer->GetActiveCamera()->SetViewUp(vUp);  
}

///SetCameraPosition////////////////////////////////////////////////////////////
//
// Setting camera position and orientation to values for gantry angles with
// azimuth defined by argument az.
//
////////////////////////////////////////////////////////////////////////////////
void Projector::SetCameraPosition(double az)
{
	double posY = -150; // 1/28/11 changed from -250
	//double posY = -210; // 04/13/11 so the body is entirely visible

	renderer->GetActiveCamera()->SetPosition(64.5, posY, avgZ);   // campos in Matlab
  renderer->GetActiveCamera()->SetFocalPoint(64, 64, avgZ);     // camtarget "
  renderer->GetActiveCamera()->SetViewUp(0, 0, -1);             // camup     "
  renderer->GetActiveCamera()->Azimuth(-az);                    // [az,el] = view "
}

///UpdateExtrema////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void Projector::UpdateExtrema(eStructureType structure, double v[3])
{
  if (v[0] < minX) minX = v[0];
  if (v[0] > maxX) maxX = v[0];
  if (v[1] < minY) minY = v[1];
  if (v[1] > maxY) maxY = v[1];
  if (v[2] < minZ) minZ = v[2];
  if (v[2] > maxZ) maxZ = v[2];
}

///BuildStructure///////////////////////////////////////////////////////////////
//
// Read in geometric data from the appropriate files -- assumed to have been
// generated by our modified version of CERR -- and generate a 3D surface
// therefrom.
//
////////////////////////////////////////////////////////////////////////////////
bool Projector::BuildStructure(int patientNum, eStructureType st)
{
  char vPath[kMaxChars]; 
  char fPath[kMaxChars];

  QByteArray formatArray = inPathFormat.toAscii();
  char *formatString = formatArray.data();
  sprintf_s(vPath, formatString, patientNum, inFileType[ekVertices], patientNum,
            structureType[st]);
  sprintf_s(fPath, formatString, patientNum, inFileType[ekFaces], patientNum,
            structureType[st]);

// The Carl Zhang/Vorakarn Chanyavanich convention for naming input files:
//     <inFileType>_<patient number>_<structure>.out
// where <inFileType> = [ "faces" | "vertices" ],
//       <patient number> is a 3-digit integer (possibly front-padded with 0's),
// and   <structure>  = [ "bladder" | "LtFem" | "PTV" | "rectum" | "RtFem" ].

  fstream vfs(vPath, ios_base::in); // Vertex File Stream

  if (!vfs.is_open())
  {
    cout << "Failed to open vertices file " << vPath << endl;
    return false;
  }

  fstream ffs(fPath, ios_base::in); // Faces File Stream
   
  if (!ffs.is_open())
  {
    cout << "Failed to open faces file " << fPath << endl;
    return false;
  }
  
  double v[3];
  vtkIdType f[3];
 
  vtkPoints *points = vtkPoints::New();
  int vNum = -1;
  
  while(!vfs.eof())
  {
    vNum++;
    vfs >> v[0] >> v[1] >> v[2];
    vfs.ignore(kMaxChars, '\n');
    //cout << "vertex[" << vNum << "]: " << v[0] << ", " << v[1] << ", " << v[2] << endl;
    points->InsertPoint(vNum, v);
    if (isPatientChanged) UpdateExtrema(st, v);   
  }
  
  vfs.close();
  
  vtkCellArray *polys = vtkCellArray::New();
  int fNum = -1;

  while(!ffs.eof())
  {
    fNum++;
   
    ffs >> f[0] >> f[1] >> f[2];
    ffs.ignore(kMaxChars, '\n');
    f[0]--; // Matlab arrays are 1-based vs. 0-based in C/C++. 
    f[1]--;
    f[2]--; 
    //cout << "  face[" << fNum << "]: "<< f[0] << ", " << f[1] << ", " << f[2] << endl;
    polys->InsertNextCell(3, f);
  }
  
  ffs.close();

  /*
  PrintStructureName(st);
  cout << "vNum: " << vNum << "; fNum: " << fNum
       << "; color: " << structureColor[st][0] << ", "
       << structureColor[st][1] << ", "
       << structureColor[st][2] << endl;
 */

  if (structure) structure->Delete(); 
  structure = vtkPolyData::New();
  structure->SetPoints(points);
  points->Delete();
  structure->SetPolys(polys);
  polys->Delete();

#if STRAIGHTPIPE
  cout << "Straight pipe." << endl;

  if (mapper) mapper->Delete();
  mapper = vtkPolyDataMapper::New();
  mapper->SetInput(structure);

#else
  //cout << "Decimated and smoothed." << endl;
  if (deci) deci->Delete(); 
  deci = vtkDecimatePro::New();
  deci->SetInput(structure);
  deci->SetTargetReduction(0.5);
  deci->PreserveTopologyOn();

  if (smoother) smoother->Delete();
  smoother = vtkSmoothPolyDataFilter::New();
  smoother->SetInputConnection(deci->GetOutputPort());
  smoother->SetNumberOfIterations(100);

  if (normals) normals->Delete();
  normals = vtkPolyDataNormals::New();
  normals->SetInputConnection(smoother->GetOutputPort());
  normals->NonManifoldTraversalOff();
  //normals->FlipNormalsOn();
  //normals->FlipNormalsOff();
  normals->AutoOrientNormalsOn();
  normals->ConsistencyOn();
  //normals->ComputeCellNormalsOn();

  if (mapper) mapper->Delete();
  mapper = vtkPolyDataMapper::New();
  mapper->SetInputConnection(normals->GetOutputPort());
#endif

  if (actor) actor->Delete(); 
  actor = vtkActor::New();  
  actor->SetMapper(mapper);
  actor->GetProperty()->SetColor(structureColor[st][0], structureColor[st][1],
	  structureColor[st][2]);
  actor->GetProperty()->SetInterpolationToPhong();

  //actor->GetProperty()->SetOpacity(st == ekBody ? 0.3 : 1.0);

  if (transparency != 0.0)
  {
    //normals->FlipNormalsOn();
	//normals->FlipNormalsOff();
	normals->ComputeCellNormalsOn();
    actor->GetProperty()->SetOpacity(1.0 - (transparency / 100.0));
  }

/* 
  if (st == ekBody)
  {
	actor->GetProperty()->SetSpecular(2);
	actor->GetProperty()->SetSpecularPower(3);
	actor->GetProperty()->SetColor(
		structureColor[st][0],
		structureColor[st][1],
		structureColor[st][2]);
	//actor->GetProperty()->SetSpecularColor(1, 1, 1);
	//actor->GetProperty()->SetSpecularColor(
		structureColor[st][0], 
		structureColor[st][1],
		structureColor[st][2]);
	actor->GetProperty()->SetSpecularColor(.5, .4, .4);
  }
  else
  {
*/
	if (flatShaded)
	{
	  actor->GetProperty()->SetSpecular(0);
	  actor->GetProperty()->SetDiffuse(0);
	  actor->GetProperty()->SetAmbient(1);
	  actor->GetProperty()->SetAmbientColor(
		  structureColor[st][0],
		  structureColor[st][1],
		  structureColor[st][2]);
	  actor->GetProperty()->SetColor(
		  structureColor[st][0],
		  structureColor[st][1],
		  structureColor[st][2]);
	}
	else
	{
	  actor->GetProperty()->SetSpecular(4);
	  actor->GetProperty()->SetSpecularPower(30);
	  actor->GetProperty()->SetColor(
		  structureColor[st][0], 
		  structureColor[st][1],
		  structureColor[st][2]);
	  actor->GetProperty()->SetSpecularColor(1, 1, 1);
	}
/*  } */

  renderer->AddActor(actor);
  int numActors = renderer->GetActors()->GetNumberOfItems();
  
  return true;
}

double MAX(double a, double b, double c)
{
	return (a > b) ? ((a > c) ? a : c) : ((b > c) ? b : c);
}

///BuildStructuresForPatient////////////////////////////////////////////////////
//
// Build all the requested structures for patientNum.  If none were built return
// false, else return true.
//
// If it's a first or different patient, initialize and recompute extrema and 
// averages.  If it's the same patient with different structures, don't
// recompute, to avoid the stuctures moving around in the render window.
//
////////////////////////////////////////////////////////////////////////////////
bool Projector::BuildStructuresForPatient(int patientNum, bool isDifferentPatient /* = false */)
{
  isPatientChanged = isDifferentPatient;

  renderer->RemoveAllViewProps();

  bool wasAtLeastOneStructureBuilt = false;
  
  for (int s = ekBladder; s < kNumStructureTypes; s++)
  {

	if (!drawStructure[s]) continue;

    if (BuildStructure(patientNum, (eStructureType)s))
	{
		wasAtLeastOneStructureBuilt = true;
	}
  }
 
  InitSlicePlane();
  renderer->GetActiveCamera()->SetClippingRange(1.0, MAX(maxX, maxY, maxZ) * 3.0);

  if (isPatientChanged)
  {
	  cout << "Projector::BuildStructuresForPatient(...) patient #" << patientNum << " extrema: " 
	   << minX << ", " << maxX << "; "
	   << minY << ", " << maxY << "; "
	   << minZ << ", " << maxZ << endl;
  }

  isPatientChanged = false;

  return wasAtLeastOneStructureBuilt;
}

///InitAxes/////////////////////////////////////////////////////////////////////
//
// Set up the standard VTK axes.
//
////////////////////////////////////////////////////////////////////////////////
void Projector::InitAxes(void)
{
  vtkAxes *axes = vtkAxes::New();
  axes->SetOrigin(0, 0, 0);
  axes->SetScaleFactor(40);
  vtkPolyDataMapper *axesMapper = vtkPolyDataMapper::New();
  axesMapper->SetInputConnection(axes->GetOutputPort());
  vtkActor *axesActor = vtkActor::New();
  axesActor->GetProperty()->SetAmbient(0.5);
  axesActor->SetMapper(axesMapper);
  renderer->AddActor(axesActor);
}

///TextInit/////////////////////////////////////////////////////////////////////
//
// Set up text in the lower (with a default placeholder string) in the lower
// left hand corner of the window.
//
////////////////////////////////////////////////////////////////////////////////
void Projector::TextInit(void)
{
  textActor = vtkTextActor::New();
  textActor->SetHeight(0.34);
  textActor->SetDisplayPosition(10, 3);

  textActor->SetInput("Structure Projections");

  renderer->AddActor(textActor);
}

///InitLegend///////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void Projector::InitLegend()
{
	usedThemUp = !usedThemUp; //major HACK

	if (legendTextActor[0]) return;

	// HACK: copied from CompareDialog.cpp:
	static const char *shortStructureName[kNumStructureTypes] =
	{
		"PTV",		// Planning Target Volume
		"rec",
		"bla",
		"lfem",
		"rfem"
	};

	// SAME HACK: rgb values, 0.0-1.0 range (used by Projector class):
	static const double structureColor[kNumStructureTypes][3] =
	{
		0.9, 0.0, 0.0,			// PTV red     
		0.545, 0.271, 0.075,	// rectum "saddle brown"
		1.0, 0.84, 0.0,			// bladder "golden yellow"
		0.5, 0.5, 0.6,			// left femoral head blue-gray
		0.75, 0.75, 0.75		// right femoral head lite gray
	};

	const int startY = kRenWinY - 10;
	const int yDecrement = 13;
	const int startX = kRenWinX - 28;

	for (int i = 0; i < kNumStructureTypes; i++)
	{
		legendTextActor[i] = vtkTextActor::New();
		legendTextActor[i]->SetHeight(0.25);
		legendTextActor[i]->SetDisplayPosition(startX, startY - i * yDecrement);
		legendTextActor[i]->GetTextProperty()->SetColor(1, 1, 0);
		legendTextActor[i]->GetTextProperty()->BoldOn();
		legendTextActor[i]->SetInput(shortStructureName[i]);
		legendTextActor[i]->GetTextProperty()->SetColor(
			structureColor[i][0], structureColor[i][1], structureColor[i][2]);
		renderer->AddActor(legendTextActor[i]);
	}
}

////SetProjection///////////////////////////////////////////////////////////////
//
// Set the camera angle and add the corresponding text.
//
////////////////////////////////////////////////////////////////////////////////
void Projector::SetProjection(int patientNum, int angle)
{
  char txt[kMaxChars];  
  SetCameraPosition(angle); 
  sprintf_s(txt, "patient #%03d: gantry angle %d degrees", patientNum, angle);
  renderer->AddActor(textActor); // Need to do this every time to see text

  //if (!usedThemUp)
  {
	  for (int i = 0; i < kNumStructureTypes; i++) // Why? Dunno, but it works
		  if (legendTextActor[i]) renderer->AddActor(legendTextActor[i]);
  }

  usedThemUp = !usedThemUp; //major HACK

  textActor->SetInput(txt);    
  renWin->Render();
  //ReportCameraPosition(renderer);
}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void Projector::InitSlicePlane()
{
	if (slicePlane)
	{
		slicePlane->Delete();
		sliceMapper->Delete();
		sliceActor->Delete();
	}

	slicePlane = vtkCubeSource::New();
	sliceMapper = vtkPolyDataMapper::New();
	sliceActor = vtkActor::New();
 

	sliceMapper->SetInputConnection(slicePlane->GetOutputPort());
	sliceMapper->ScalarVisibilityOff();
	sliceActor->SetMapper(sliceMapper);
	sliceActor->GetProperty()->SetOpacity(0.2);

	renderer->AddActor(sliceActor);  
}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void Projector::PositionSlicePlane(int orientation, int slice, double *spacing)
{
	slicePlane->SetCenter(avgX, avgY, avgZ);

	slicePlane->SetXLength(maxX - minX);
	slicePlane->SetYLength(maxY - minY);
	slicePlane->SetZLength(maxZ - minZ);

	const double thinDimension = 1.0;

	switch(orientation)
	{
	case 0: // Sagittal
		slicePlane->SetXLength(spacing[0]);
		slicePlane->SetCenter(slice * spacing[0], avgY, avgZ);
		break;
	case 1: // Coronal
		slicePlane->SetYLength(spacing[1]);
		slicePlane->SetCenter(avgX, slice * spacing[1], avgZ);
		break;
	case 2: // Axial
		slicePlane->SetZLength(spacing[2]);
		slicePlane->SetCenter(avgX, avgY, slice * spacing[2]);
		break;
	default:
		cout << "Projector::PositionSlicePlane(...): Invalid orientation: " << endl;		
		break;
	}

	renWin->Render();
}

////////////////////////////////////////////////////////////////////////////////
//
// TEMP hack 
//
////////////////////////////////////////////////////////////////////////////////
void Projector::PositionSlicePlane(int orientation, int slice, int numSlices)
{
	slicePlane->SetCenter(avgX, avgY, avgZ);

	slicePlane->SetXLength(maxX - minX);
	slicePlane->SetYLength(maxY - minY);
	slicePlane->SetZLength(maxZ - minZ);

	const double thinDimension = 1.0;

	double rangeXMin = avgX - 2 * (avgX - minX);
	double rangeYMin = avgY - 2 * (avgY - minY);
	double rangeZMin = avgZ - 2 * (avgZ - minZ);
	double rangeXMax = avgX + 2 * (maxX - avgX);
	double rangeYMax = avgY + 2 * (maxY - avgY);
	double rangeZMax = avgZ + 2 * (maxZ - avgZ);

	double xSliceSize = (rangeXMax - rangeXMin) / numSlices;
	double ySliceSize = (rangeYMax - rangeYMin) / numSlices;
	double zSliceSize = (rangeZMax - rangeZMin) / numSlices;

	switch(orientation)
	{
	case 0: // Sagittal
		slicePlane->SetXLength(thinDimension);
		//slicePlane->SetXLength(spacing[0]);
		//slicePlane->SetCenter(slice * spacing[0], avgY, avgZ);
		//slicePlane->SetCenter(rangeXMin + (xSliceSize * slice), avgY, avgZ);
		slicePlane->SetCenter(rangeXMax - (xSliceSize * slice), avgY, avgZ);
		break;
	case 1: // Coronal
		slicePlane->SetYLength(thinDimension);
		//slicePlane->SetYLength(spacing[1]);
		slicePlane->SetCenter(avgX, rangeYMax - (ySliceSize * slice), avgZ);
		break;
	case 2: // Axial
		slicePlane->SetZLength(thinDimension);
		//slicePlane->SetZLength(spacing[2]);
		slicePlane->SetCenter(avgX, avgY, rangeZMin + (zSliceSize * slice));
		break;
	default:
		cout << "Projector::PositionSlicePlane(...): Invalid orientation: " << endl;		
		break;
	}

	renWin->Render();
}
