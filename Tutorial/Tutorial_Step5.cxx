#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkConeSource.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>

int main(int, char*[])
{
  vtkNew<vtkNamedColors> colors;
  vtkNew<vtkConeSource> cone;
  cone->SetHeight(3.0);
  cone->SetRadius(1.0);
  cone->SetResolution(10);

  vtkNew<vtkPolyDataMapper> coneMapper;
  coneMapper->SetInputConnection(cone->GetOutputPort());

  vtkNew<vtkActor> coneActor;
  coneActor->SetMapper(coneMapper);
  coneActor->GetProperty()->SetColor(colors->GetColor3d("Bisque").GetData());

  vtkNew<vtkRenderer> ren1;
  ren1->AddActor(coneActor);
  ren1->SetBackground(colors->GetColor3d("MidnightBlue").GetData());

  vtkNew<vtkRenderWindow> renWin;
  renWin->AddRenderer(ren1);
  renWin->SetSize(300, 300);
  renWin->SetWindowName("Tutorial_Step5");

  vtkNew<vtkRenderWindowInteractor> iren;
  iren->SetRenderWindow(renWin);

  //
  // By default the vtkRenderWindowInteractor instantiates an instance
  // of vtkInteractorStyle. vtkInteractorStyle translates a set of events
  // it observes into operations on the camera, actors, and/or properties
  // in the vtkRenderWindow associated with the vtkRenderWinodwInteractor.
  // Here we specify a particular interactor style.
  vtkNew<vtkInteractorStyleTrackballCamera> style;
  iren->SetInteractorStyle(style);

  //
  // Unlike the previous scripts where we performed some operations and then
  // exited, here we leave an event loop running. The user can use the mouse
  // and keyboard to perform the operations on the scene according to the
  // current interaction style. When the user presses the "e" key, by default
  // an ExitEvent is invoked by the vtkRenderWindowInteractor which is caught
  // and drops out of the event loop (triggered by the Start() method that
  // follows.
  //
  iren->Initialize();
  iren->Start();

  //
  // Final note: recall that observers can watch for particular events and
  // take appropriate action. Pressing "u" in the render window causes the
  // vtkRenderWindowInteractor to invoke a UserEvent. This can be caught to
  // popup a GUI, etc. See the Tcl Cone5.tcl example for an idea of how this
  // works.

  return EXIT_SUCCESS;
}