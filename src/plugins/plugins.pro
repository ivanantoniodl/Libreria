CONFIG    += ordered
TEMPLATE  = subdirs

SUBDIRS   = plugin_core \
			plugin_configlugar \
			plugin_configusers \
            plugin_configempresa\
            plugin_libro\
            plugin_autores


plugin_core.subdir = coreplugin

plugin_configlugar.subdir = configlugar
plugin_configlugar.depends = plugin_core

plugin_configusers.subdir = configusers
plugin_configusers.depends = plugin_core

plugin_configempresa.subdir = configempresa
plugin_configempresa.depends = plugin_core

plugin_libro.subdir = libros
plugin_libro.depends = plugin_core

plugin_autores.subdir = autores
plugin_autores.depends = plugin_core
