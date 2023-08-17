#include "application.h"
#include "../app-config.h"

#include <iostream>
#include <exception>

Application::Application()
    : Gtk::Application(AppConfig::Organization, Gio::Application::Flags::HANDLES_OPEN)
{
}

Glib::RefPtr<Application> Application::create()
{
  return Glib::make_refptr_for_instance<Application>(new Application());
}

MainWindow *Application::createAppWindow()
{
  auto appwindow = MainWindow::create();

  // Make sure that the application runs for as long this window is still open.
  add_window(*appwindow);

  // A window can be added to an application with Gtk::Application::add_window()
  // or Gtk::Window::set_application(). When all added windows have been hidden
  // or removed, the application stops running (Gtk::Application::run() returns()),
  // unless Gio::Application::hold() has been called.

  // Delete the window when it is hidden.
  appwindow->signal_hide().connect([appwindow]()
                                   { delete appwindow; });

  return appwindow;
}

void Application::on_startup()
{
  Gtk::Application::on_startup();
  MainWindow::addMainMenuActions(this);
}

void Application::on_activate()
{
  try
  {
    // The application has been started, so let's show a window.
    auto appwindow = createAppWindow();
    appwindow->present();
  }
  // If create_appwindow() throws an exception (perhaps from Gtk::Builder),
  // no window has been created, no window has been added to the application,
  // and therefore the application will stop running.
  catch (const Glib::Error &ex)
  {
    std::cerr << "Application::on_activate(): " << ex.what() << std::endl;
  }
  catch (const std::exception &ex)
  {
    std::cerr << "Application::on_activate(): " << ex.what() << std::endl;
  }
}

void Application::on_action_preferences()
{
  std::cout << "Preference action not defined" << std::endl;
}

void Application::on_action_quit()
{
  // Gio::Application::quit() will make Gio::Application::run() return,
  // but it's a crude way of ending the program. The window is not removed
  // from the application. Neither the window's nor the application's
  // destructors will be called, because there will be remaining reference
  // counts in both of them. If we want the destructors to be called, we
  // must remove the window from the application. One way of doing this
  // is to hide the window. See comment in create_appwindow().
  auto windows = get_windows();
  for (auto window : windows)
    window->set_visible(false);

  // Not really necessary, when Gtk::Widget::set_visible(false) is called,
  // unless Gio::Application::hold() has been called without a corresponding
  // call to Gio::Application::release().
  quit();
}
