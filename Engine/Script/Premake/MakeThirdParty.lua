print("Adding thirdparty project...")

local glfwProjectPath = path.join(ThirdPartyPath, "glfw/build/src")
print("[ glfw ] project path : "..glfwProjectPath)
group "ThirdParty/glfw"
	externalproject("glfw")
		kind("StaticLib")
		location(glfwProjectPath)
		targetdir(BinaryPath)

local assimpProjectPath = path.join(ThirdPartyPath, "assimp/build/code")
print("[ assimp ] project path : "..assimpProjectPath)
group "ThirdParty/assimp"
	externalproject("assimp")
		kind("StaticLib")
		location(assimpProjectPath)
		targetdir(BinaryPath)

group ""

print("")