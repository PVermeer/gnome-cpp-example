#ifndef APPLICATION_H
#define APPLICATION_H

#include <gtkmm.h>

class Application : public Gtk::Application
{
protected:
  Application();

public:
  static Glib::RefPtr<Application> create();

protected:
  // Overrides of default signal handlers:
  void on_startup() override;
  void on_activate() override;

private:
  void create_window();

  void on_menu_file_new_generic();
  void on_menu_file_quit();
  void on_menu_help_about();

  Glib::RefPtr<Gtk::Builder> builder;
};

#endif // APPLICATION_H
