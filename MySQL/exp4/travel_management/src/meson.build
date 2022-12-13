travel_management_sources = [
  'main.vala',
  'classes.vala',
  'database.vala',
  'database-error.vala',
  'management.vala'
]

travel_management_deps = [
  dependency('glib-2.0'),
  dependency('gobject-2.0'),
  dependency('sqlite3'),
  dependency('readline'),
  dependency('gee-0.8'),
]

executable('travel_management', travel_management_sources,
  vala_args: '--target-glib=2.58',  dependencies: travel_management_deps,
  install: true,
)

