#include "main_window.h"
#include "page_tree_dock.h"
#include "browser_stack.h"
#include "dev_tools_dock.h"

MainWindow::MainWindow(Cef *cef, QWidget *parent)
    : QMainWindow(parent), cef_(cef) {
  // TODO: how to determine best interval
  // TODO: is the timer stopped for us?
  if (startTimer(10) == 0) {
    throw std::runtime_error("Unable to start CEF timer");
  }

  // Common settings
  setWindowTitle("Doogie");
  setFocusPolicy(Qt::FocusPolicy::StrongFocus);
  resize(1024, 768);

  auto browser_stack = new BrowserStack(cef, this);
  setCentralWidget(browser_stack);

  auto page_tree = new PageTreeDock(browser_stack, this);
  addDockWidget(Qt::LeftDockWidgetArea, page_tree);

  auto dev_tools = new DevToolsDock(cef, browser_stack, this);
  addDockWidget(Qt::BottomDockWidgetArea, dev_tools);

  resizeDocks({dev_tools}, {300}, Qt::Vertical);

  // We choose for verticle windows to occupy the corners
  setCorner(Qt::TopLeftCorner, Qt::LeftDockWidgetArea);
  setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
  setCorner(Qt::TopRightCorner, Qt::RightDockWidgetArea);
  setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);
}

MainWindow::~MainWindow() {
}

void MainWindow::timerEvent(QTimerEvent*) {
  cef_->Tick();
}
