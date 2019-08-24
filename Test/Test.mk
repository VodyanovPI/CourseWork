##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Release
ProjectName            :=Test
ConfigurationName      :=Release
WorkspacePath          :=/home/vlad/ntp_client
ProjectPath            :=/home/vlad/ntp_client/Test
IntermediateDirectory  :=Release
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=
Date                   :=08/24/19
CodeLitePath           :=/home/maksim/.codelite
LinkerName             :=g++
SharedObjectLinkerName :=g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-gstab
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="Test.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  -O2
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)UnitTest++ 
ArLibs                 :=  "libUnitTest++.a" 
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := g++
CC       := gcc
CXXFLAGS :=   $(Preprocessors)
CFLAGS   :=   $(Preprocessors)
ASFLAGS  := 
AS       := as


##
## User defined environment variables
##
CodeLiteDir:=/home/maksim/prog/codelite/share/codelite
Objects0=$(IntermediateDirectory)/up_ntp_NTP.cpp$(ObjectSuffix) $(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/NTPTest.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d Release || $(MakeDirCommand) Release


$(IntermediateDirectory)/.d:
	@test -d Release || $(MakeDirCommand) Release

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/up_ntp_NTP.cpp$(ObjectSuffix): ../ntp/NTP.cpp $(IntermediateDirectory)/up_ntp_NTP.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/vlad/ntp_client/ntp/NTP.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_ntp_NTP.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_ntp_NTP.cpp$(DependSuffix): ../ntp/NTP.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_ntp_NTP.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_ntp_NTP.cpp$(DependSuffix) -MM ../ntp/NTP.cpp

$(IntermediateDirectory)/up_ntp_NTP.cpp$(PreprocessSuffix): ../ntp/NTP.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_ntp_NTP.cpp$(PreprocessSuffix) ../ntp/NTP.cpp

$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/vlad/ntp_client/Test/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM main.cpp

$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) main.cpp

$(IntermediateDirectory)/NTPTest.cpp$(ObjectSuffix): NTPTest.cpp $(IntermediateDirectory)/NTPTest.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/vlad/ntp_client/Test/NTPTest.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/NTPTest.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/NTPTest.cpp$(DependSuffix): NTPTest.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/NTPTest.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/NTPTest.cpp$(DependSuffix) -MM NTPTest.cpp

$(IntermediateDirectory)/NTPTest.cpp$(PreprocessSuffix): NTPTest.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/NTPTest.cpp$(PreprocessSuffix) NTPTest.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r Release/


