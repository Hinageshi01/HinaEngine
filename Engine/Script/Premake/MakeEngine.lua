project("Engine")
	kind("ConsoleApp")
	language("C++")
	cppdialect("C++latest")
	dependson { "glfw" }
	
	location(path.join(VSConfigPath, "Engine"))
	targetdir(BinaryPath)

	files {
		path.join(RuntimePath, "**.*"),

		path.join(ThirdPartyPath, "glfw/include/**.**"),
        path.join(ThirdPartyPath, "glad/**.**"),
	}
	
	vpaths {
		["Source/*"] = { 
			path.join(RuntimePath, "**.*"),
		},
	}

    includedirs {
		RuntimePath,
		ThirdPartyPath,
		path.join(ThirdPartyPath, "glfw/include"),
		path.join(ThirdPartyPath, "glad/include"),
	}

    filter { "configurations:Debug" }
    libdirs {
        path.join(ThirdPartyPath, "glfw/build/src/Debug"),
    }
    links {
        "glfw3"
    }
    filter { "configurations:Release" }
    libdirs {
        path.join(ThirdPartyPath, "glfw/build/src/Release"),
    }
    links {
        "glfw3"
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