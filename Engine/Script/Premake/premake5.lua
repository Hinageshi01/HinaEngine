print("Generating HinaEngine solution...")

dofile("path.lua")

EngineName = "HinaEngine"

workspace(EngineName)
	location(RootPath)
	targetdir(BinariesPath)

	-- Set platform.
	architecture("x64")
	
	-- Set configurations.
	configurations { "Debug", "Release" }
	
	-- No optimization.
	filter "configurations:Debug"
		defines { "_DEBUG" }
		symbols("On")
		optimize("Off")

	-- Full optimization.
	filter "configurations:Release"
		defines { "NDEBUG" }
		symbols("Off")
		optimize("Full")

	-- Avoid compiler warnings about non-utf8 characters.
	filter "system:Windows"
		systemversion("latest")
		buildoptions { "/utf-8" }

	filter {}
	
	startproject("Example_PBR")

dofile("MakeThirdParty.lua")

dofile("MakeEngine.lua")

dofile("MakeExample.lua")

dofile("Util.lua")

dofile("Asset.lua")
