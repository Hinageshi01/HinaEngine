print("Adding thirdparty project...")

local glfwProjectPath = path.join(ThirdPartyPath, "glfw/build/src")
print("[ glfw ] project path : "..glfwProjectPath)
group "ThirdParty"
	externalproject("glfw")
		kind("StaticLib")
		location(glfwProjectPath)
		targetdir(BinaryPath)

local assimpProjectPath = path.join(ThirdPartyPath, "assimp/build/code")
print("[ assimp ] project path : "..assimpProjectPath)
group "ThirdParty"
	externalproject("assimp")
		kind("StaticLib")
		location(assimpProjectPath)
		targetdir(BinaryPath)

local spdlogProjectPath = path.join(ThirdPartyPath, "spdlog/build")
print("[ spdlog ] project path : "..spdlogProjectPath)
group "ThirdParty"
	externalproject("spdlog")
		kind("StaticLib")
		location(spdlogProjectPath)
		targetdir(BinaryPath)

group ""

print("")
