#ifndef APPLICATION_H
#define APPLICATION_H

#include "../main-window/main-window.h"
#include "../about-dialog/about-dialog.h"

#include <gtkmm/application.h>

class MainWindow;

class Application : public Gtk::Application
{
protected:
  Application();

public:
  static Glib::RefPtr<Application> create();
  void on_action_preferences();
  void on_action_about();
  void on_action_quit();

protected:
  // Override default signal handlers:
  void on_startup() override;
  void on_activate() override;

  std::unique_ptr<AboutDialog> aboutDialog;

private:
  MainWindow *createAppWindow();
};

#endif // APPLICATION_H
