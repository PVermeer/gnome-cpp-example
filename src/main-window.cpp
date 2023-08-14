#include "main-window.h"
#include "app-config.h"

#include <iostream>

MainWindow::MainWindow()
    : childWidgets(Gtk::Orientation::VERTICAL)
{
  set_title(AppConfig::Name);
  set_default_size(500, 500);

  // ExampleApplication displays the menubar. Other stuff, such as a toolbar,
  // is put into the box.
  set_child(childWidgets);

  // Build window widgets
  buildToolbar();
}

MainWindow::~MainWindow()
{
}

void MainWindow::buildToolbar()
{
  // Create actions for menus and toolbars.
  // We can use add_action() because Gtk::ApplicationWindow derives from Gio::ActionMap.
  // This Action Map uses a "win." prefix for the actions.
  // Therefore, for instance, "win.copy", is used in ExampleApplication::on_startup()
  // to layout the menu.

  // Edit menu:
  add_action("copy", sigc::mem_fun(*this, &MainWindow::on_menu_others));
  add_action("paste", sigc::mem_fun(*this, &MainWindow::on_menu_others));
  add_action("something", sigc::mem_fun(*this, &MainWindow::on_menu_others));

  // Choices menus, to demonstrate Radio items,
  // using our convenience methods for string and int radio values:
  actionChoice = add_action_radio_string("choice",
                                         sigc::mem_fun(*this, &MainWindow::on_menu_choices), "a");

  actionChoiceOther = add_action_radio_integer("choiceother",
                                               sigc::mem_fun(*this, &MainWindow::on_menu_choices_other), 1);

  actionToggle = add_action_bool("sometoggle",
                                 sigc::mem_fun(*this, &MainWindow::on_menu_toggle), false);

  // Help menu:
  add_action("about", sigc::mem_fun(*this, &MainWindow::on_menu_others));

  // Create the toolbar and add it to a container widget:
  gtkBuilder = Gtk::Builder::create();
  try
  {
    gtkBuilder->add_from_resource("/main-window.ui");
  }
  catch (const Glib::Error &ex)
  {
    std::cerr << "Building toolbar failed: " << ex.what();
  }

  auto toolbar = gtkBuilder->get_widget<Gtk::Box>("toolbar");
  if (!toolbar)
    g_warning("toolbar not found");
  else
    childWidgets.append(*toolbar);
}

void MainWindow::on_menu_others()
{
  std::cout << "A menu item was selected." << std::endl;
}

void MainWindow::on_menu_choices(const Glib::ustring &choise)
{
  // The radio action's state does not change automatically:
  actionChoice->change_state(choise);

  Glib::ustring message;
  if (choise == "a")
    message = "Choice a was selected.";
  else
    message = "Choice b was selected.";

  std::cout << message << std::endl;
}

void MainWindow::on_menu_choices_other(int choise)
{
  // The radio action's state does not change automatically:
  actionChoiceOther->change_state(choise);

  Glib::ustring message;
  if (choise == 1)
    message = "Choice 1 was selected.";
  else
    message = "Choice 2 was selected.";

  std::cout << message << std::endl;
}

void MainWindow::on_menu_toggle()
{
  bool active = false;
  actionToggle->get_state(active);

  // The toggle action's state does not change automatically:
  active = !active;
  actionToggle->change_state(active);

  Glib::ustring message;
  if (active)
    message = "Toggle is active.";
  else
    message = "Toggle is not active.";

  std::cout << message << std::endl;
}
