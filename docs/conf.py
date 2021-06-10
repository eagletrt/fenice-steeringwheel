project = 'Steering Wheel'
description = 'C++ / Qt / QML'
copyright = '2021, Eagle TRT'
author = 'Filippo Rossi'

release = '0.0.1'

extensions = []

templates_path = ['_templates']

exclude_patterns = ['_build', 'Thumbs.db', '.DS_Store']

html_theme = "alabaster"
html_theme_options = {
  'logo': 'logo.png',
  'description': 'UI and backend for the official EagleTRT steering wheel',
  'github_user': 'eagletrt',
  'github_repo': 'fenice-steeringwheel',
}

html_static_path = ['_static']
