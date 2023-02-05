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

	-- Set pch flie.
	pchheader("hnpch.h")
	pchsource(path.join(SourcePath, "hnpch.cpp"))

	-- Target name.
	filter { "configurations:Debug" }
		targetname("%{prj.name}".."d")
	filter { "configurations:Release" }
		targetname("%{prj.name}")
	filter {}

	-- Set definitions.
	defines {
		-- We don't want to use any exception in engine.
		"SPDLOG_NO_EXCEPTIONS",
		-- It seems like a VS bug.
		-- https://github.com/fmtlib/fmt/issues/2552
		-- https://developercommunity.visualstudio.com/t/C20-String-literal-operator-templat-un/1318552
		"FMT_USE_NONTYPE_TEMPLATE_ARGS=0",
		-- For imgui_impl_XXX.cpp
		"_CRT_SECURE_NO_WARNINGS",
	}
	filter { "system:Windows" }
		defines {
			"HN_PLATFORM_WIN",
			"HN_BUILD_DLL",
		}
	filter {}

	-- Set files.
	files {
		path.join(SourcePath, "*.*"),
		path.join(RuntimePath, "**.*"),

		path.join(ThirdPartyPath, "glm/**.*"),
		path.join(ThirdPartyPath, "stb/**.*"),
		path.join(ThirdPartyPath, "spdlog/include/**.*"),
	}
	
	-- Set filter.
	vpaths {
		["Source/*"] = { 
			path.join(RuntimePath, "**.*"),
		},
		["Include/*"] = { 
			path.join(SourcePath, "*.*"),
		},
	}

	-- Set include paths.
	includedirs {
		SourcePath,
		RuntimePath,
		ThirdPartyPath,
		-- Thirdparties
		path.join(ThirdPartyPath, "glad/include"),
		path.join(ThirdPartyPath, "glfw/include"),
		path.join(ThirdPartyPath, "spdlog/include"),
		path.join(ThirdPartyPath, "imgui"),
		path.join(ThirdPartyPath, "glm"),
		path.join(ThirdPartyPath, "stb"),
		path.join(ThirdPartyPath, "assimp/include"),
		path.join(ThirdPartyPath, "assimp/build/include"),
		-- Assets
		path.join(SourcePath, "Asset"),
	}

	-- Link thirdparty libs.
	filter { "configurations:Debug" }
		libdirs {
			path.join(ThirdPartyPath, "glad/build/Debug"),
			path.join(ThirdPartyPath, "glfw/build/src/Debug"),
			path.join(ThirdPartyPath, "imgui/build/Debug"),
			path.join(ThirdPartyPath, "assimp/build/lib/Debug"),
		}
		links {
			"gladd", "glfw3", "imguid", "assimp-vc143-mtd"
		}
	filter { "configurations:Release" }
		libdirs {
			path.join(ThirdPartyPath, "glad/build/Release"),
			path.join(ThirdPartyPath, "glfw/build/src/Release"),
			path.join(ThirdPartyPath, "imgui/build/Release"),
			path.join(ThirdPartyPath, "assimp/build/lib/Release"),
		}
		links {
			"glad", "glfw3", "imgui", "assimp-vc143-mt"
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

print("")
