#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "../application/application.h"

#include <gtkmm/applicationwindow.h>
#include <gtkmm/builder.h>
#include <gtkmm/menubutton.h>

class Application;

class MainWindow : public Gtk::ApplicationWindow
{
public:
  MainWindow(BaseObjectType *cobject,
             const Glib::RefPtr<Gtk::Builder> &refBuilder);

  static MainWindow *create();
  static void addMainMenuActions(Application *app);

protected:
  Glib::RefPtr<Gtk::Builder> builder;
  Gtk::MenuButton *menu{nullptr};

private:
  void createMainMenu();
};

#endif // MAIN_WINDOW_H
