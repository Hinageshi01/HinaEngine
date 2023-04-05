project("Setup")
	kind("Utility")

	location(IntermediatePath)
	objdir(path.join(IntermediatePath, "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}"))
	targetdir(path.join(BinaryPath, "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}"))

	files {
		path.join(EnginePath, "Script/**.bat"),
		path.join(EnginePath, "Script/**.lua"),
	}

	postbuildcommands {
		"cd "..RootPath,
		"Setup.bat",
	}
