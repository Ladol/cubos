DOXYFILE = 'Doxyfile'

MAIN_PROJECT_URL = 'https://cubosengine.org'

LINKS_NAVBAR1 = [
    (None, 'pages', []),
    (None, 'modules', []),
]

FAVICON = '@DOXYGEN_PROJECT_ROOT@/docs/images/Favicon.png'

# Load m.css theme FIRST, then custom.css
STYLESHEETS = [
    'https://fonts.googleapis.com/css?family=Source+Sans+Pro:400,400i,600,600i%7CSource+Code+Pro:400,400i,600',  # mCSS fonts
    '../_deps/mcss-src/css/m-dark+documentation.compiled.css',  # Use the compiled dark theme
    'custom.css'  # Custom overrides
]

# Add theme switcher HTML and JavaScript
FINE_PRINT = '''
    <div class="theme-switcher">
        <button class="theme-button dark active" data-theme="dark"></button>
        <button class="theme-button gray" data-theme="gray"></button>
        <button class="theme-button light" data-theme="light"></button>
    </div>
    <script>
''' + open('theme-switcher.js').read() + '''
    </script>
'''

# Remove SCRIPTS since we're including it inline
# SCRIPTS = [
#     'theme-switcher.js'
# ]

# Add your own navbar links using the code below.
# To find the valid link names, you can inspect the URL of a generated documentation site.

# LINKS_NAVBAR1 = [
#     (None, 'pages', [(None, 'about')]),
#     (None, 'namespaces', [(None, 'namespacegreeter')]),
# ]
#
# LINKS_NAVBAR2 = [
#     (None, 'annotated', [(None, 'classgreeter_1_1_greeter')]),
#     (None, 'files', [(None, 'greeter_8h')]),
# ]
