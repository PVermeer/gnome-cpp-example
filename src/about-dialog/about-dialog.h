#ifndef ABOUT_DIALOG_H
#define ABOUT_DIALOG_H

#include <gtkmm/aboutdialog.h>

class AboutDialog : public Gtk::AboutDialog
{
public:
  AboutDialog();
  virtual ~AboutDialog();
};

#endif // ABOUT_DIALOG_H
