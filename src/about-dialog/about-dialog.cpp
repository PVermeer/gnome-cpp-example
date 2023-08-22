#include "about-dialog.h"

AboutDialog::AboutDialog()
    : Gtk::AboutDialog()
{
  set_title("Gtk::AboutDialog example");
  set_default_size(400, 150);
  set_modal(true);
  set_hide_on_close(true);

  set_program_name("Example application");
  set_version("1.0.0");
  set_copyright("Murray Cumming");
  set_comments("This is just an example application.");
  set_license("LGPL");

  set_website("http://www.gtkmm.org");
  set_website_label("gtkmm website");
}
