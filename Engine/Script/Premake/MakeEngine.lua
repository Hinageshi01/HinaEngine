print("Generating Hina...")

project("Hina")
	kind("StaticLib")
	-- SharedLib, StaticLib, ConsoleApp
	language("C++")
	cppdialect("C++20")
	dependson { "glfw", "assimp" }
	
	-- Intermediate and binary path.
	location(IntermediatePath)
	objdir(path.join(IntermediatePath, "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}"))
	targetdir(path.join(BinaryPath, "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}"))

	-- Target name.
    filter { "configurations:Debug" }
		targetname("%{prj.name}".."d")
    filter { "configurations:Release" }
		targetname("%{prj.name}")
    filter {}

	-- Set definitions.
	defines {
		"HN_PLATFORM_WIN",
		"HN_BUILD_DLL",
	}

	-- Set files.
	files {
		path.join(RuntimePath, "**.**"),

		path.join(ThirdPartyPath, "glad/**.**"),
		path.join(ThirdPartyPath, "glm/**.**"),
		path.join(ThirdPartyPath, "stb/**.**"),
		path.join(ThirdPartyPath, "spdlog/include/spdlog/**.**"),
	}
	
	-- Set filter.
	vpaths {
		["Source/*"] = { 
			path.join(RuntimePath, "**.**"),
		},
	}

	-- Set include paths.
    includedirs {
		ThirdPartyPath,
		path.join(ThirdPartyPath, "glfw/include"),
		path.join(ThirdPartyPath, "glad/include"),
		path.join(ThirdPartyPath, "stb"),
		path.join(ThirdPartyPath, "glm"),
		path.join(ThirdPartyPath, "assimp/include"),
		path.join(ThirdPartyPath, "assimp/build/include"),
		path.join(ThirdPartyPath, "spdlog/include"),

		RuntimePath,
	}

	-- Link thirdparty libs.
    filter { "configurations:Debug" }
    	libdirs {
    	    path.join(ThirdPartyPath, "glfw/build/src/Debug"),
    	    path.join(ThirdPartyPath, "assimp/build/lib/Debug"),
    	}
    	links {
    	    "glfw3", "assimp-vc143-mtd",
    	}
    filter { "configurations:Release" }
    	libdirs {
    	    path.join(ThirdPartyPath, "glfw/build/src/Release"),
    	    path.join(ThirdPartyPath, "assimp/build/lib/Release"),
    	}
    	links {
    	    "glfw3", "assimp-vc143-mt",
    	}
    filter {}

	-- Use /MT and /MTd.
	staticruntime "on"
	filter { "configurations:Debug" }
		runtime("Debug") -- /MTd
	filter { "configurations:Release" }
		runtime("Release") -- /MT
	filter {}

	-- Disable these options can reduce the size of compiled binaries.
	justmycode("Off")
	editAndContinue("Off")
	exceptionhandling("Off")
	rtti("Off")	
		
	-- Strict.
	warnings("Default")
	externalwarnings("Off")
	
	flags {
		-- Treat warnings as errors.
		-- "FatalWarnings",
		-- Compiler uses multiple thread.
		"MultiProcessorCompile",
	}
	
	-- Enable cpp exception.
	exceptionhandling("On")

print("")
