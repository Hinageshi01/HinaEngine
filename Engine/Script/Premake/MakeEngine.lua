project("Engine")
	kind("ConsoleApp")
	language("C++")
	cppdialect("C++latest")
	dependson { "glfw", "assimp" }
	
	location(path.join(VSConfigPath, "Engine"))
	targetdir(BinaryPath)

	files {
		path.join(RuntimePath, "**.**"),

        path.join(ThirdPartyPath, "glad/**.h"),
		path.join(ThirdPartyPath, "glad/**.c"),
		path.join(ThirdPartyPath, "glad/**.cpp"),
		path.join(ThirdPartyPath, "glad/**.hpp"),

		path.join(ThirdPartyPath, "glm/**.h"),
		path.join(ThirdPartyPath, "glm/**.c"),
		path.join(ThirdPartyPath, "glm/**.cpp"),
		path.join(ThirdPartyPath, "glm/**.hpp"),

		path.join(ThirdPartyPath, "stb/**.h"),
		path.join(ThirdPartyPath, "stb/**.c"),
		path.join(ThirdPartyPath, "stb/**.cpp"),
		path.join(ThirdPartyPath, "stb/**.hpp"),
	}
	
	vpaths {
		["Source/*"] = { 
			path.join(RuntimePath, "**.**"),
		},
	}

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

    -- use /MT /MTd, not /MD /MDd
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
		"FatalWarnings", -- treat warnings as errors
		"MultiProcessorCompile", -- compiler uses multiple thread
	}