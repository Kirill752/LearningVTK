// Creating lines by using VTK
#include <vtkActor.h>
#include <vtkAxesActor.h>
#include <vtkCamera.h>
#include <vtkCaptionActor2D.h>
#include <vtkCellArray.h>
#include <vtkCellData.h>
#include <vtkLine.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkTextProperty.h>
#include <vtkTransform.h>
#include <vtkUnsignedCharArray.h>

// For compatibility with new VTK generic data arrays.
#ifdef vtkGenericDataArray_h
#define InsertNextTupleValue InsertNextTypedTuple
#endif

int main(int argc, char* argv[])
{
  // Create the polydata where we will store all the geometric data

  vtkNew<vtkPolyData> linesPolydata;

  // Create three points

  double origin[3] = { 0.0, 0.0, 0.0 };
  double p1[3] = { 1.0, 0.0, 0.0 };
  double p2[3] = { 0.0, 1.0, 0.0 };
  double p3[3] = { 0.0, 0.0, 1.0 };

  // Create a vtkPoints container and store the points in it.
  vtkNew<vtkPoints> pts;
  pts->InsertNextPoint(origin);
  pts->InsertNextPoint(p1);
  pts->InsertNextPoint(p2);
  pts->InsertNextPoint(p3);

  // Add the points to the polydata container.
  linesPolydata->SetPoints(pts);

  // Create the first line (between Origin and P1).
  vtkNew<vtkLine> line1;
  line1->GetPointIds()->SetId(
    0, 0); // the second 0 is the index of the Origin in linesPolyData's points.
  line1->GetPointIds()->SetId(1, 1); // the second 1 is the index of P1 in linesPolyData's points.

  // Create the second line (between Origin and P2).
  vtkNew<vtkLine> line2;
  line2->GetPointIds()->SetId(
    0, 0); // the second 0 is the index of the Origin in linesPolyData's points.
  line2->GetPointIds()->SetId(1, 2); // 2 is the index of P2 in linesPolyData's points.

  // Create the second line (between Origin and P2).
  vtkNew<vtkLine> line3;
  line3->GetPointIds()->SetId(
    0, 1); // the second 0 is the index of the Origin in linesPolyData's points.
  line3->GetPointIds()->SetId(1, 2); // 2 is the index of P2 in linesPolyData's points.

  // Create a vtkCellArray container and store the lines in it.
  vtkNew<vtkCellArray> lines;
  lines->InsertNextCell(line1);
  lines->InsertNextCell(line2);
  lines->InsertNextCell(line3);

  // Add the lines to the polydata container.
  linesPolydata->SetLines(lines);
  // Create a vtkUnsignedCharArray container and store the colors in it.
  vtkNew<vtkNamedColors> namedColors;
  vtkNew<vtkUnsignedCharArray> colors;
  colors->SetNumberOfComponents(3);
  colors->InsertNextTupleValue(namedColors->GetColor3ub("Tomato").GetData());
  colors->InsertNextTupleValue(namedColors->GetColor3ub("Mint").GetData());
  colors->InsertNextTupleValue(namedColors->GetColor3ub("MidnightBlue").GetData());

  // Color the lines.
  // SetScalars() automatically associates the values in the data array passed
  // as parameter to the elements in the same indices of the cell data array on
  // which it is called. This means the first component (red) of the colors
  // array is matched with the first component of the cell array (line 0) and
  // the second component (green) of the colors array is matched with the second
  // component of the cell array (line 1).
  linesPolydata->GetCellData()->SetScalars(colors);

  // Setup the visualization pipeline.
  vtkNew<vtkPolyDataMapper> mapper;
  mapper->SetInputData(linesPolydata);

  vtkNew<vtkActor> actor;
  actor->SetMapper(mapper);
  actor->GetProperty()->SetLineWidth(4);

  vtkNew<vtkRenderer> renderer;
  renderer->AddActor(actor);
  renderer->SetBackground(namedColors->GetColor3d("SlateGray").GetData());

  // Добавление Осей координат
  vtkNew<vtkTransform> transform;
  transform->Translate(-1.0, -1.0, -1.0);

  vtkNew<vtkAxesActor> axes;

  // The axes are positioned with a user transform
  axes->SetUserTransform(transform);

  // properties of the axes labels can be set as follows
  // this sets the x axis label to red
  // axes->GetXAxisCaptionActor2D()->GetCaptionTextProperty()->SetColor(
  //  colors->GetColor3d("Red").GetData());

  // the actual text of the axis label can be changed:
  // axes->SetXAxisLabelText("test");

  renderer->AddActor(axes);

  renderer->GetActiveCamera()->Azimuth(50);
  renderer->GetActiveCamera()->Elevation(-30);

  renderer->ResetCamera();

  vtkNew<vtkRenderWindow> window;
  window->SetWindowName("Colored Lines");
  window->AddRenderer(renderer);

  vtkNew<vtkRenderWindowInteractor> interactor;
  interactor->SetRenderWindow(window);

  // Visualize
  window->Render();
  interactor->Start();
  return EXIT_SUCCESS;
}