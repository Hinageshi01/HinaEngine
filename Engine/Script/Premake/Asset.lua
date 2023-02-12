print("Adding Assets...")

project("Asset")
	kind("Utility")

	location(IntermediatePath)
	objdir(path.join(IntermediatePath, "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}"))
	targetdir(path.join(BinaryPath, "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}"))

	files {
		path.join(SourcePath, "Asset/Shader/**.*"),
	}

	vpaths {
		["Shader/*"] = { 
			path.join(SourcePath, "Asset/Shader/**.*"),
		},
	}

print("")
