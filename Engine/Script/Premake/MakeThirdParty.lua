print("Generating thirdparty projects by premake...")

group("ThirdParty")
	dofile("MakeGlad.lua")
	dofile("MakeImGui.lua")

print("Adding thirdparty projects...")

local gladProjectPath = path.join(ThirdPartyPath, "glad/build")
print("[ glad ] project path: "..gladProjectPath)

local imguiProjectPath = path.join(ThirdPartyPath, "imgui/build")
print("[ imgui ] project path: "..imguiProjectPath)

-- Already generated by CMake.
local glfwProjectPath = path.join(ThirdPartyPath, "glfw/build/src")
print("[ glfw ] project path: "..glfwProjectPath)
group("ThirdParty")
	externalproject("glfw")
		kind("StaticLib")
		location(glfwProjectPath)

-- Already generated by CMake.
-- Assimp depends on it.
local zlibProjectPath = path.join(ThirdPartyPath, "assimp/build/contrib/zlib")
print("[ zlib ] project path: "..zlibProjectPath)
group("ThirdParty/assimp")
	externalproject("zlibstatic")
		kind("StaticLib")
		location(zlibProjectPath)

-- Already generated by CMake.
local assimpProjectPath = path.join(ThirdPartyPath, "assimp/build/code")
print("[ assimp ] project path: "..assimpProjectPath)
group("ThirdParty/assimp")
	externalproject("assimp")
		kind("StaticLib")
		location(assimpProjectPath)
		dependson("zlibstatic")

-- We use spdlog as a header only lib now.
-- local spdlogProjectPath = path.join(ThirdPartyPath, "spdlog/build")
-- print("[ spdlog ] project path: "..spdlogProjectPath)
-- group "ThirdParty"
-- 	externalproject("spdlog")
-- 		kind("StaticLib")
-- 		location(spdlogProjectPath)
-- 		targetdir(BinaryPath)

group("")

print("")
