print("Setting path...")

CurrentWorkingDirectory = os.getcwd()
RootPath = string.sub(CurrentWorkingDirectory, 0, string.len(CurrentWorkingDirectory) - string.len("Engine/Script/Premake"))
EnginePath = path.join(RootPath, "Engine")

VSConfigPath = path.join(EnginePath, "VSConfig/Win64")
BinaryPath = path.join(EnginePath, "Binary/Win64")
SourcePath = path.join(EnginePath, "Source")

RuntimePath = path.join(SourcePath, "Runtime")
ThirdPartyPath = path.join(SourcePath, "ThirdParty")

print("Root path : "..RootPath)
print("Engine path : "..EnginePath)
print("VSConfig path : "..VSConfigPath)
print("Binary path : "..BinaryPath)
print("Source path : "..SourcePath)
print("Runtime path : "..RuntimePath)
print("Thirdparty path : "..ThirdPartyPath)
print("")