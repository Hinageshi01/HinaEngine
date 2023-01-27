print("Generating glad...")

project("glad")
	kind("StaticLib")
	-- SharedLib, StaticLib, ConsoleApp
	language("C++")
	cppdialect("C++20")

    local gladPath = path.join(ThirdPartyPath, "glad/build")
    print("[ glad ] project path : "..gladPath)
    location(gladPath)

    filter { "configurations:Debug" }
	    targetdir(path.join(gladPath, "Debug"))
		targetname("%{prj.name}".."d")
    filter { "configurations:Release" }
        targetdir(path.join(gladPath, "Release"))
		targetname("%{prj.name}")
    filter {}

	files {
		path.join(ThirdPartyPath, "glad/**.**"),
	}
	
    includedirs {
		path.join(ThirdPartyPath, "glad/include"),
	}

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
