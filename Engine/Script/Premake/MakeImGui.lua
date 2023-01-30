print("Generating imgui...")

project("imgui")
	kind("StaticLib")
	-- SharedLib, StaticLib, ConsoleApp
	language("C++")
	cppdialect("C++20")

	local imguiBuildPath = path.join(ThirdPartyPath, "imgui/build")
	location(imguiBuildPath)

	filter { "configurations:Debug" }
		targetdir(path.join(imguiBuildPath, "Debug"))
		targetname("%{prj.name}".."d")
	filter { "configurations:Release" }
		targetdir(path.join(imguiBuildPath, "Release"))
		targetname("%{prj.name}")
	filter {}

	files {
		path.join(ThirdPartyPath, "imgui/*.h"),
		path.join(ThirdPartyPath, "imgui/*.cpp"),
	}
	
	includedirs {
		path.join(ThirdPartyPath, "imgui"),
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
