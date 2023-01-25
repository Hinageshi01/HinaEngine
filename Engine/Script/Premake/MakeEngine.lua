print("Generating Hina...")

project("Hina")
	kind("SharedLib")
	-- StaticLib, ConsoleApp
	language("C++")
	cppdialect("C++latest")
	dependson { "glfw", "assimp" }
	
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

		path.join(ThirdPartyPath, "glad/**.c"),
        path.join(ThirdPartyPath, "glad/**.h"),
		path.join(ThirdPartyPath, "glad/**.cpp"),
		path.join(ThirdPartyPath, "glad/**.hpp"),

		path.join(ThirdPartyPath, "glm/**.c"),
		path.join(ThirdPartyPath, "glm/**.h"),
		path.join(ThirdPartyPath, "glm/**.cpp"),
		path.join(ThirdPartyPath, "glm/**.hpp"),

		path.join(ThirdPartyPath, "stb/**.c"),
		path.join(ThirdPartyPath, "stb/**.h"),
		path.join(ThirdPartyPath, "stb/**.cpp"),
		path.join(ThirdPartyPath, "stb/**.hpp"),
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

		RuntimePath,
	}

	-- Link thirdparty libs.
    filter { "configurations:Debug" }
    libdirs {
        path.join(ThirdPartyPath, "glfw/build/src/Debug"),
        path.join(ThirdPartyPath, "assimp/build/lib/Debug"),
    }
    links {
        "glfw3", "assimp-vc143-mtd"
    }
    filter { "configurations:Release" }
    libdirs {
        path.join(ThirdPartyPath, "glfw/build/src/Release"),
        path.join(ThirdPartyPath, "assimp/build/lib/Release"),
    }
    links {
        "glfw3", "assimp-vc143-mt"
    }
    filter {}

    -- Use /MT and /MTd, not /MD and /MDd.
	staticruntime "on"
	filter { "configurations:Debug" }
		runtime "Debug" -- /MTd
	filter { "configurations:Release" }
		runtime "Release" -- /MT
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
		"FatalWarnings",
		-- Compiler uses multiple thread.
		"MultiProcessorCompile",
	}

print("")
