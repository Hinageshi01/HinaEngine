print("Setting path...")

CurrentWorkingDirectory = os.getcwd()
RootPath = string.sub(CurrentWorkingDirectory, 0, string.len(CurrentWorkingDirectory) - string.len("Engine/Script/Premake"))
EnginePath = path.join(RootPath, "Engine")

BinaryPath = path.join(EnginePath, "bin")
IntermediatePath = path.join(EnginePath, "int")

SourcePath = path.join(EnginePath, "Source")
RuntimePath = path.join(SourcePath, "Runtime")
ThirdPartyPath = path.join(SourcePath, "ThirdParty")

print("Root path : "..RootPath)
print("Engine path : "..EnginePath)
print("Binary path : "..BinaryPath)
print("Intermediate path : "..IntermediatePath)
print("Source path : "..SourcePath)
print("Runtime path : "..RuntimePath)
print("Thirdparty path : "..ThirdPartyPath)
print("")
