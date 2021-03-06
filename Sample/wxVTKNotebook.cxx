#include "wxVTKNotebook.h"
#include "vtkSphereSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkRenderer.h"
#include "wxVTKRenderWindowInteractor.h"

#include <wx/sizer.h>

#if 0
#include <wx/wx.h>
#include "vtkRenderer.h"
#include "vtkSphereSource.h"
#include "wxVTKRenderWindowInteractor.h"
#include "vtkPolyDataMapper.h"

// http://wiki.wxwidgets.org/WxNoteBook
// http://wiki.wxwidgets.org/WxGLCanvas
//http://groups.google.com/group/comp.soft-sys.wxwindows/browse_thread/thread/4c05e3ed72c53fe4/f1dc6173abcbd7a9
//http://ghostdev85.googlepages.com/tutorial6.html
//http://www.zetcode.com/tutorials/wxwidgetstutorial/widgetsII/
//http://lists.wxwidgets.org/pipermail/wx-users/2007-August/102175.html
//http://groups.google.com/group/comp.soft-sys.wxwindows/msg/c13353efe574997d?hl=en&dmode=source

#define MY_VTK_WINDOW 102


class Page : public wxPanel{
public:
  Page(wxPanel*parent);
private:
       // DECLARE_EVENT_TABLE()
};

Page::Page(wxPanel*parent):wxPanel(parent,-1)
  {
  int grid[]={15,15}; // -> Max Xlib
  //# wxVTKRenderWindow stops working since it create its own Display
  //# When using wxVTKRenderWindowInteractor the X Display is reused (work around is working)
  //grid=(25,25) #The error was 'GLXBadDrawable'.
  //grid=(15,15)
  wxGridSizer *sizer = new wxGridSizer(grid[0],grid[1],1,1); //rows=grid[0], cols=grid[1], hgap=1, vgap=1)
  //print dir(sizer)
  //print sizer.GetRows()
  //print sizer.GetCols()
  int n = grid[0]*grid[1];

  vtkSphereSource *sphere = vtkSphereSource::New();
  vtkPolyDataMapper *sphereMapper = vtkPolyDataMapper::New();
  sphereMapper->SetInput(sphere->GetOutput());

  vtkActor *sphereActor = vtkActor::New();
  sphereActor->SetMapper(sphereMapper);

  //self._wlist=[]
  for (int i=0; i<n; ++i)
    {
    vtkRenderer *ren = vtkRenderer::New();
    ren->AddActor(sphereActor);
    wxVTKRenderWindowInteractor *renWin = new wxVTKRenderWindowInteractor(this, MY_VTK_WINDOW);
    //self,-1, size=(10,10))
    //self._wlist.append( renWin )
    renWin->GetRenderWindow()->AddRenderer(ren);
    sizer->Add( renWin, 1, wxEXPAND);
    }

  this->SetSizer(sizer);
}

class mywxframe : public wxFrame { //Creating new class that inherits wxFrame
    public:
        mywxframe(); //Constructor for the myframe class
        void OnNew(wxCommandEvent&);
        void OnNotebook(wxNotebookEvent&);
    private:
        wxNotebook *notebook;
        Page *page1;
        DECLARE_EVENT_TABLE()
};

enum
{
  ID_NOTEBOOK = 1000,
};

class myapp: public wxApp {
    public:
        virtual bool OnInit();
};

bool myapp::OnInit() {
    mywxframe *myframe = new mywxframe();
    myframe->Show(true);
    return TRUE;
}

void mywxframe::OnNew(wxCommandEvent &e) {
(void)e;
    wxTextCtrl *textctrl = new wxTextCtrl(notebook, wxID_ANY);
    notebook->AddPage(textctrl, _T("Untitled"), true);
}

void mywxframe::OnNotebook(wxNotebookEvent& e)
{
}

mywxframe::mywxframe() : wxFrame(NULL,0,_T("Title")) {
    //All things you want to add to the frame will be added here
    //mywxframe::mywxframe() constructor calls the wxFrame(NULL,0,"Title")
    //And make the class itself
    //wxMenu * mymenu = new wxMenu;
    //mymenu->Append(wxID_NEW, _T("&New\tCtrl+N"),_T("New file"));
    //wxMenuBar *mymenubar = new wxMenuBar();
    //mymenubar->Append(mymenu,_T("&File"));
    //SetMenuBar(mymenubar);
    
    notebook = new wxNotebook(this, ID_NOTEBOOK /*wxID_ANY*/);
    *page1 = new Page(notebook);
}

IMPLEMENT_APP(myapp);
BEGIN_EVENT_TABLE(mywxframe, wxFrame)
    //EVT_MENU(wxID_NEW, mywxframe::OnNew)
    EVT_NOTEBOOK_PAGE_CHANGED(ID_NOTEBOOK, mywxframe::OnNotebook)
    EVT_NOTEBOOK_PAGE_CHANGING(ID_NOTEBOOK, mywxframe::OnNotebook)
END_EVENT_TABLE()
#endif

// -*- C++ -*- generated by wxGlade 0.4.1 on Mon Jun 30 11:13:15 2008

//#include "mytest.h"

enum
{
  ID_NOTEBOOK = 101,
};
MyFrame::MyFrame(wxWindow* parent, int id, const wxString& title, const wxPoint& pos, const wxSize& size, long style):
    wxFrame(parent, id, title, pos, size, wxDEFAULT_FRAME_STYLE)
{
    // begin wxGlade: MyFrame::MyFrame
    notebook_1 = new wxNotebook(this, ID_NOTEBOOK, wxDefaultPosition, wxDefaultSize, 0);
    notebook_1_pane_2 = new wxPanel(notebook_1, -1);
    notebook_1_pane_1 = new wxPanel(notebook_1, -1);

    set_properties();
    do_layout();
    // end wxGlade
}


BEGIN_EVENT_TABLE(MyFrame, wxFrame)
    // begin wxGlade: MyFrame::event_table
    EVT_NOTEBOOK_PAGE_CHANGED(ID_NOTEBOOK, MyFrame::OnNotebookChanged)
    EVT_NOTEBOOK_PAGE_CHANGING(ID_NOTEBOOK, MyFrame::OnNoteBookChanging)
    // end wxGlade
END_EVENT_TABLE();


void MyFrame::OnNotebookChanged(wxNotebookEvent &event)
{
std::cout << "OnNotebookChanged" << std::endl;
    event.Skip();
}


void MyFrame::OnNoteBookChanging(wxNotebookEvent &event)
{
std::cout << "OnNoteBookChanging" << std::endl;



   // const wxSizerItemList& list = notebook_1_pane_1->GetChildren();
   //wxWindowList::compatibility_iterator node = notebook_1_pane_1->GetChildren().GetFirst();
   for ( wxWindowList::compatibility_iterator node = notebook_1_pane_1->GetChildren().GetFirst();
     node;
     node = node->GetNext() )
     {
     wxWindow *child = node->GetData();
     wxVTKRenderWindowInteractor *renwin = dynamic_cast<wxVTKRenderWindowInteractor*>(child);
     std::cout << renwin->GetClassName() << std::endl;
     renwin->GetRenderWindow()->Finalize();
     }

    event.Skip();
}


// wxGlade: add MyFrame event handlers


void MyFrame::set_properties()
{
    // begin wxGlade: MyFrame::set_properties
    SetTitle(wxT("frame_1"));
    // end wxGlade
}

void MyFrame::FillVTK(wxPanel *notebook_1_pane_1, wxGridSizer *sizer)
{
  vtkSphereSource *sphere = vtkSphereSource::New();
  vtkPolyDataMapper *sphereMapper = vtkPolyDataMapper::New();
  sphereMapper->SetInput(sphere->GetOutput());

  vtkActor *sphereActor = vtkActor::New();
  sphereActor->SetMapper(sphereMapper);

  //  self._wlist=[];
  int n = GridSize*GridSize;
  for (int i = 0; i < n; ++i)
    {
    vtkRenderer *ren = vtkRenderer::New();
    ren->AddActor(sphereActor);
    wxPanel *self = notebook_1_pane_1;
    wxVTKRenderWindowInteractor *renWin = new wxVTKRenderWindowInteractor(self,-1); //, size=(10,10));
    //self._wlist.append( renWin );
    renWin->GetRenderWindow()->AddRenderer(ren);
    sizer->Add( renWin, 1, wxEXPAND);
    }
}

void MyFrame::do_layout()
{
    // begin wxGlade: MyFrame::do_layout
    wxBoxSizer* sizer_1 = new wxBoxSizer(wxVERTICAL);
    wxGridSizer* grid_sizer_2 = new wxGridSizer(GridSize, GridSize, 1, 1);
    wxGridSizer* grid_sizer_1 = new wxGridSizer(GridSize, GridSize, 1, 1);

    // Fill size1:
    FillVTK(notebook_1_pane_1, grid_sizer_1);
    FillVTK(notebook_1_pane_2, grid_sizer_2);


    notebook_1_pane_1->SetAutoLayout(true);
    notebook_1_pane_1->SetSizer(grid_sizer_1);
    grid_sizer_1->Fit(notebook_1_pane_1);
    grid_sizer_1->SetSizeHints(notebook_1_pane_1);
    notebook_1_pane_2->SetAutoLayout(true);
    notebook_1_pane_2->SetSizer(grid_sizer_2);
    grid_sizer_2->Fit(notebook_1_pane_2);
    grid_sizer_2->SetSizeHints(notebook_1_pane_2);
    notebook_1->AddPage(notebook_1_pane_1, wxT("tab1"));
    notebook_1->AddPage(notebook_1_pane_2, wxT("tab2"));
    sizer_1->Add(notebook_1, 1, wxEXPAND, 0);
    SetAutoLayout(true);
    SetSizer(sizer_1);
    sizer_1->Fit(this);
    sizer_1->SetSizeHints(this);
    Layout();
    // end wxGlade
}



class MyApp: public wxApp {
public:
    bool OnInit();
};

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    wxInitAllImageHandlers();
    MyFrame* frame_1 = new MyFrame(0, -1, wxT(""));
    SetTopWindow(frame_1);
    frame_1->Show();
    return true;
}
