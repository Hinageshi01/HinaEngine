print("Generating Example_PBR...")

project("Example_PBR")
	kind("ConsoleApp")
    language("C++")
	cppdialect("C++20")
	dependson { "Hina" }
	
	location(IntermediatePath)

    filter { "configurations:Debug" }
	targetdir(path.join(BinaryPath, "Debug-x64/PBR"))
	targetname("PBRd")
    filter { "configurations:Release" }
	targetdir(path.join(BinaryPath, "Release-x64/PBR"))
	targetname("PBR")
    filter {}

    defines {
		"HN_PLATFORM_WIN",
	}

    local PBRPath = path.join(SourcePath, "Example_PBR")

	files {
		path.join(PBRPath, "**.**"),
	}
	
	vpaths {
		["Source/*"] = { 
			path.join(PBRPath, "**.**"),
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
		path.join(ThirdPartyPath, "spdlog/include"),

		RuntimePath,
	}

    filter { "configurations:Debug" }
    libdirs {
        path.join(BinaryPath, "Debug-x64/Hina"),
    }
    links {
        "Hinad"
    }
    filter { "configurations:Release" }
    libdirs {
        path.join(BinaryPath, "Release-x64/Hina"),
    }
    links {
        "Hina",
    }
    filter {}

	-- copy dll into binary folder automatically.
	-- filter { "configurations:Debug" }
	-- 	postbuildcommands {
    --         "copy \""..path.join(BinaryPath, "Debug-x64\\Hina\\Hinad.dll\" \"")..path.join(BinaryPath, "Debug-x64\\PBR\\Hinad.dll\" /y")
	-- 	}
	-- filter { "configurations:Release" }
	-- 	postbuildcommands {
    --         "copy \""..path.join(BinaryPath, "Release-x64\\Hina\\Hina.dll\" \"")..path.join(BinaryPath, "Release-x64\\PBR\\Hina.dll\" /y")
	-- 	}
	-- filter {}

	-- Disable these options can reduce the size of compiled binaries.
	justmycode("Off")
	editAndContinue("Off")
	exceptionhandling("Off")
	rtti("Off")	
		
	-- Strict.
	warnings("Default")
	externalwarnings("Off")
	
	flags {
		-- "FatalWarnings",
		"MultiProcessorCompile",
	}

    exceptionhandling ("On")

print("")
