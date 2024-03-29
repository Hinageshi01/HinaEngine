print("Generating examples...")

print("Generating Example_PBR...")

project("Example_PBR")
	kind("ConsoleApp")
	language("C++")
	cppdialect("C++20")
	dependson { "Hina" }
	
	location(IntermediatePath)
	objdir(path.join(IntermediatePath, "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}"))
	targetdir(path.join(BinaryPath, "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}"))

	pchheader("hnpch.h")
	pchsource(path.join(SourcePath, "hnpch.cpp"))

	filter { "configurations:Debug" }
		targetname("%{prj.name}".."d")
	filter { "configurations:Release" }
		targetname("%{prj.name}")
	filter {}

	defines {
		"SPDLOG_NO_EXCEPTIONS",
		"FMT_USE_NONTYPE_TEMPLATE_ARGS=0",
		"_CRT_SECURE_NO_WARNINGS",
		"HN_ENGINE_ROOT_PATH=\""..RootPath.."\"",
	}
	filter { "system:Windows" }
		defines {
			"HN_PLATFORM_WIN",
		}
	filter {}

	local PBRPath = path.join(SourcePath, "Example_PBR")

	files {
		path.join(SourcePath, "*.*"),
		path.join(PBRPath, "**.*"),
	}
	
	vpaths {
		["Source/*"] = { 
			path.join(PBRPath, "**.*"),
		},
		["Include/*"] = { 
			path.join(SourcePath, "*.*"),
		},
	}

	includedirs {
		SourcePath,
		RuntimePath,
		ThirdPartyPath,
		path.join(ThirdPartyPath, "glad/include"),
		path.join(ThirdPartyPath, "glfw/include"),
		path.join(ThirdPartyPath, "spdlog/include"),
		path.join(ThirdPartyPath, "imgui"),
		path.join(ThirdPartyPath, "glm"),
		path.join(ThirdPartyPath, "stb"),
		path.join(ThirdPartyPath, "entt/src"),
		path.join(ThirdPartyPath, "assimp/include"),
		path.join(ThirdPartyPath, "assimp/build/include"),
		path.join(SourcePath, "Asset"),
	}

	libdirs {
		path.join(BinaryPath, "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/Hina"),
	}

	filter { "configurations:Debug" }
		links {
			"Hinad",
		}
	filter { "configurations:Release" }
		links {
			"Hina",
		}
	filter {}

	staticruntime "on"
	filter { "configurations:Debug" }
		runtime("Debug")
	filter { "configurations:Release" }
		runtime("Release")
	filter {}

	justmycode("Off")
	editAndContinue("Off")
	exceptionhandling("Off")
	rtti("Off")	
		
	warnings("Default")
	externalwarnings("Off")
	
	flags {
		"MultiProcessorCompile",
	}

print("")
