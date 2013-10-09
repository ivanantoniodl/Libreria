CONFIG    += ordered
TEMPLATE  = subdirs

SUBDIRS   = plugin_core \
			plugin_configlugar \
			plugin_configusers \
            plugin_configempresa


plugin_core.subdir = coreplugin

plugin_configlugar.subdir = configlugar
plugin_configlugar.depends = plugin_core

plugin_configusers.subdir = configusers
plugin_configusers.depends = plugin_core

plugin_configempresa.subdir = configempresa
plugin_configempresa.depends = plugin_core

