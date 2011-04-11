#include "glutMaster.h"
#include "glutWindow.h"
#include "demoWindow.h"

GlutMaster     * glutMaster;
DemoWindow     * firstWindow       = 0;
DemoWindow     * secondWindow      = 0;

int main()
{
   glutMaster   = new GlutMaster();    
 
   firstWindow  = new DemoWindow(glutMaster,
      500, 500,    // height, width
      300, 100,    // initPosition (x,y)
      "First Window"); // title
   
   //firstWindow->StartSpinning(glutMaster);
   glutMaster->CallGlutMainLoop();
   return 0;
}
