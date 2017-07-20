#ifndef DOOGIE_MAIN_WINDOW_H_
#define DOOGIE_MAIN_WINDOW_H_

#include <QtWidgets>
#include "cef.h"
#include "cef_widget.h"
#include "page_tree_dock.h"
#include "dev_tools_dock.h"
#include "logging_dock.h"

namespace doogie {

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(Cef* cef, QWidget* parent = nullptr);
  ~MainWindow();

  QJsonObject DebugDump();

 protected:
  void closeEvent(QCloseEvent* event) override;
  void dropEvent(QDropEvent* event) override;
  void dragEnterEvent(QDragEnterEvent* event) override;
  void keyPressEvent(QKeyEvent* event) override;
  void timerEvent(QTimerEvent* event) override;

 private:
  void ShowDevTools(BrowserWidget* browser,
                    const QPoint& inspect_at,
                    bool force_open);
  static void LogQtMessage(QtMsgType type,
                           const QMessageLogContext& ctx,
                           const QString& str);

  Cef* cef_;
  PageTreeDock* page_tree_dock_;
  DevToolsDock* dev_tools_dock_;
  LoggingDock* logging_dock_;
  bool attempting_to_close_ = false;
  static MainWindow* instance_;
};

}  // namespace doogie

#endif  // DOOGIE_MAIN_WINDOW_H_
