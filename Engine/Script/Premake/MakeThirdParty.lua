print("Adding thirdparty project...")

local glfwProjectPath = path.join(ThirdPartyPath, "glfw/build/src")
print("[ glfw ] project path : "..glfwProjectPath)
group "ThirdParty/glfw"
	externalproject("glfw")
		kind("StaticLib")
		location(glfwProjectPath)
		targetdir(BinaryPath)

group ""

print("")