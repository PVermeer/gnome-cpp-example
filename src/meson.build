gnome_cpp_example_sources = [
  'main.cpp',
  'application/application.cpp',
  'main-window/main-window.cpp'
]

gnome_cpp_example_deps = [
  dependency('gtk4'),
  dependency('libadwaita-1', version: '>= 1.2'),
  dependency('gtkmm-4.0'),
]

gnome_cpp_example_sources += gnome.compile_resources(
  'application-resources',
  'application.gresource.xml',
  c_name: 'gnome_c_example'
)

executable(
  'gnome-cpp-example',
  gnome_cpp_example_sources,
  dependencies: gnome_cpp_example_deps,
  install: true,
)
