#ifndef _INCLUDED_MAINWINDOW_
#define _INCLUDED_MAINWINDOW_

#include <string>

class MainWindow
{
public:
  ~MainWindow();
  MainWindow(int argc, char *argv[]);
  
  int run();

private:
  void init();
  int setup();
  void createLight();
};

#endif