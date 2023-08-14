#include "application.h"
#include "main-window.h"
#include "app-config.h"

#include <iostream>

Application::Application()
    : Gtk::Application(AppConfig::Organization)
{
  Glib::set_application_name(AppConfig::Name.data());
}

Glib::RefPtr<Application> Application::create()
{
  return Glib::make_refptr_for_instance<Application>(new Application());
}

void Application::on_startup()
{
  // Call the base class's implementation:
  Gtk::Application::on_startup();

  // Create actions for menus and toolbars.
  // We can use add_action() because Gtk::Application derives from Gio::ActionMap.

  // File|New sub menu:
  add_action("newstandard",
             sigc::mem_fun(*this, &Application::on_menu_file_new_generic));

  add_action("newfoo",
             sigc::mem_fun(*this, &Application::on_menu_file_new_generic));

  add_action("newgoo",
             sigc::mem_fun(*this, &Application::on_menu_file_new_generic));

  // File menu:
  add_action("quit", sigc::mem_fun(*this, &Application::on_menu_file_quit));

  // Help menu:
  add_action("about", sigc::mem_fun(*this, &Application::on_menu_help_about));

  // Set accelerator keys:
  set_accel_for_action("app.newstandard", "<Primary>n");
  set_accel_for_action("app.quit", "<Primary>q");
  set_accel_for_action("win.copy", "<Primary>c");
  set_accel_for_action("win.paste", "<Primary>v");

  builder = Gtk::Builder::create();

  try
  {
    builder->add_from_resource("/application.ui");
  }
  catch (const Glib::Error &ex)
  {
    std::cerr << "Building menus failed: " << ex.what();
  }

  // Get the menubar and the app menu, and add them to the application:
  auto gmenu = builder->get_object<Gio::Menu>("menu-example");
  if (!gmenu)
  {
    g_warning("GMenu not found");
  }
  else
  {
    set_menubar(gmenu);
  }
}

void Application::on_activate()
{
  // std::cout << "debug1: " << G_STRFUNC << std::endl;
  //  The application has been started, so let's show a window.
  //  A real application might want to reuse this window in on_open(),
  //  when asked to open a file, if no changes have been made yet.
  create_window();
}

void Application::create_window()
{
  auto mainWindow = new MainWindow();

  // Make sure that the application runs for as long this window is still open:
  add_window(*mainWindow);

  // Delete the window when it is hidden.
  // That's enough for this simple example.
  mainWindow->signal_hide().connect([mainWindow]()
                                    { delete mainWindow; });

  mainWindow->set_show_menubar();
  mainWindow->set_visible(true);
}

void Application::on_menu_file_new_generic()
{
  std::cout << "A File|New menu item was selected." << std::endl;
}

void Application::on_menu_file_quit()
{
  std::cout << G_STRFUNC << std::endl;
  quit(); // Not really necessary, when Gtk::Widget::set_visible(false) is called.

  // Gio::Application::quit() will make Gio::Application::run() return,
  // but it's a crude way of ending the program. The window is not removed
  // from the application. Neither the window's nor the application's
  // destructors will be called, because there will be remaining reference
  // counts in both of them. If we want the destructors to be called, we
  // must remove the window from the application. One way of doing this
  // is to hide the window.
  std::vector<Gtk::Window *> windows = get_windows();
  if (windows.size() > 0)
    windows[0]->set_visible(false); // In this simple case, we know there is only one window.
}

void Application::on_menu_help_about()
{
  std::cout << "Help|About App was selected." << std::endl;
}
