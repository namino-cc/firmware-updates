Import("env")

env.Replace(PROGNAME="pyblhost_bridge_esp32_%s" % env.GetProjectOption("custom_prog_version"))
