print("Generating Hina...")

project("Hina")
	kind("SharedLib")
	-- StaticLib, ConsoleApp
	language("C++")
	cppdialect("C++latest")
	dependson { "glfw", "assimp", "spdlog" }
	
	-- Intermediate path.
	location(IntermediatePath)

	-- Binary path and target name.
    filter { "configurations:Debug" }
	targetdir(path.join(BinaryPath, "Debug-x64/Hina"))
	targetname("Hinad")
    filter { "configurations:Release" }
	targetdir(path.join(BinaryPath, "Release-x64/Hina"))
	targetname("Hina")
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
        path.join(ThirdPartyPath, "spdlog/build/Debug"),
    }
    links {
        "glfw3", "assimp-vc143-mtd", "spdlogd"
    }
    filter { "configurations:Release" }
    libdirs {
        path.join(ThirdPartyPath, "glfw/build/src/Release"),
        path.join(ThirdPartyPath, "assimp/build/lib/Release"),
        path.join(ThirdPartyPath, "spdlog/build/Release"),
    }
    links {
        "glfw3", "assimp-vc143-mt", "spdlog"
    }
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

print("")
