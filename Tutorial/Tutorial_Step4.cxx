#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkConeSource.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
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

  // First cone
  vtkNew<vtkActor> coneActor;
  coneActor->SetMapper(coneMapper);
  coneActor->GetProperty()->SetColor(0.2, 0.63, 0.79);
  coneActor->GetProperty()->SetDiffuse(0.7);
  coneActor->GetProperty()->SetSpecular(0.4);
  coneActor->GetProperty()->SetSpecularPower(20);

  //
  // Create a property and directly manipulate it. Assign it to the
  // second actor.
  //
  vtkNew<vtkProperty> property;
  property->SetColor(colors->GetColor3d("Tomato").GetData());
  property->SetDiffuse(0.7);
  property->SetSpecular(0.4);
  property->SetSpecularPower(20);

  // Second cone
  vtkNew<vtkActor> coneActor2;
  coneActor2->SetMapper(coneMapper);
  coneActor2->GetProperty()->SetColor(colors->GetColor3d("LightSeaGreen").GetData());
  coneActor2->SetProperty(property);
  coneActor2->SetPosition(0, 2, 0);

  //
  // Create the Renderer and assign actors to it. A renderer is like a
  // viewport. It is part or all of a window on the screen and it is
  // responsible for drawing the actors it has.  We also set the background
  // color here.
  //
  vtkNew<vtkRenderer> ren1;
  ren1->AddActor(coneActor);
  ren1->AddActor(coneActor2);
  ren1->SetBackground(colors->GetColor3d("CornflowerBlue").GetData());

  //
  // Finally we create the render window which will show up on the screen.
  // We put our renderer into the render window using AddRenderer. We also
  // set the size to be 300 pixels by 300.
  //
  vtkNew<vtkRenderWindow> renWin;
  renWin->AddRenderer(ren1);
  renWin->SetSize(300, 300);
  renWin->SetWindowName("Tutorial_Step4");

  //
  // Now we loop over 360 degrees and render the cones each time.
  //
  for (int i = 0; i < 360; ++i)
  {
    // render the image
    renWin->Render();
    // rotate the active camera by one degree
    ren1->GetActiveCamera()->Azimuth(1);
  }

  return EXIT_SUCCESS;
}