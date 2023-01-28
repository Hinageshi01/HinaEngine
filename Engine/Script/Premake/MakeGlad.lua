print("Generating glad...")

project("glad")
	kind("StaticLib")
	-- SharedLib, StaticLib, ConsoleApp
	language("C++")
	cppdialect("C++20")

    local gladBuildPath = path.join(ThirdPartyPath, "glad/build")
    location(gladBuildPath)

    filter { "configurations:Debug" }
	    targetdir(path.join(gladBuildPath, "Debug"))
		targetname("%{prj.name}".."d")
    filter { "configurations:Release" }
        targetdir(path.join(gladBuildPath, "Release"))
		targetname("%{prj.name}")
    filter {}

	files {
		path.join(ThirdPartyPath, "glad/include/**.**"),
		path.join(ThirdPartyPath, "glad/src/**.**"),
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
	
print("")
