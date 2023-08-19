#include "main-window.h"
#include "../app-config.h"

#include <iostream>
#include <stdexcept>

MainWindow::MainWindow(BaseObjectType *cobject, const std::shared_ptr<Gtk::Builder> &refBuilder)
    : Gtk::ApplicationWindow(cobject),
      builder(refBuilder)
{
  set_title(AppConfig::Name);
  createMainMenu();
}

// static
MainWindow *MainWindow::create()
{
  // Load the Builder file and instantiate its widgets.
  auto windowBuilder = Gtk::Builder::create_from_resource("/main-window/main-window.ui");

  auto window = Gtk::Builder::get_widget_derived<MainWindow>(windowBuilder, "app_window");
  if (!window)
    throw std::runtime_error("No \"app_window\" object in main-window.ui");

  return window;
}

// static
void MainWindow::addMainMenuActions(Application *app)
{
  app->add_action("preferences", sigc::mem_fun(*app, &Application::on_action_preferences));
  app->add_action("about", sigc::mem_fun(*app, &Application::on_action_about));
  app->add_action("quit", sigc::mem_fun(*app, &Application::on_action_quit));
  app->set_accel_for_action("app.quit", "<Ctrl>Q");
}

void MainWindow::createMainMenu()
{
  this->menu = builder->get_widget<Gtk::MenuButton>("main-menu");
  if (!this->menu)
    throw std::runtime_error("No \"main-menu\" object in main-window.ui");

  // Connect the menu to the MenuButton.
  // (The connection between action and menu item is specified in main_menu.ui.)
  auto menuBuilder = Gtk::Builder::create_from_resource("/main-window/main-menu.ui");
  auto menuModel = menuBuilder->get_object<Gio::MenuModel>("menu");
  if (!menuModel)
    throw std::runtime_error("No \"menu\" object in main-menu.ui");

  this->menu->set_menu_model(menuModel);
}
