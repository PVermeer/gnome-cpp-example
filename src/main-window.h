#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <gtkmm.h>

class MainWindow : public Gtk::ApplicationWindow
{
public:
  MainWindow();
  virtual ~MainWindow();

private:
  void buildToolbar();

  // Signal handlers:
  void on_menu_others();

  void on_menu_choices(const Glib::ustring &parameter);
  void on_menu_choices_other(int parameter);
  void on_menu_toggle();

  // Child widgets:
  Gtk::Box childWidgets;

  Glib::RefPtr<Gtk::Builder> gtkBuilder;

  // Two sets of choices:
  Glib::RefPtr<Gio::SimpleAction> actionChoice;
  Glib::RefPtr<Gio::SimpleAction> actionChoiceOther;

  Glib::RefPtr<Gio::SimpleAction> actionToggle;
};

#endif // MAIN_WINDOW_H
