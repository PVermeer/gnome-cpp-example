#ifndef APPLICATION_H
#define APPLICATION_H

#include <gtkmm.h>
#include "../main-window/main-window.h"

class MainWindow;

class Application : public Gtk::Application
{
protected:
  Application();

public:
  static Glib::RefPtr<Application> create();
  void on_action_quit();
  void on_action_preferences();

protected:
  // Override default signal handlers:
  void on_startup() override;
  void on_activate() override;

private:
  MainWindow *createAppWindow();
};

#endif // APPLICATION_H
