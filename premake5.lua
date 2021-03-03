GameName = "Sandbox"

workspace (GameName)
	configurations {
		"Debug",
		"Release"
    }

    platforms {
        "Win64"
    }

    system "windows"
	systemversion "latest"
    architecture "x64"

    flags {
        "MultiProcessorCompile"
    }

OutputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
DependencyDir = "%{GameName}/Library"
SourceDir = "%{ProjectName}/Source"

-- Dependency Directiories --
Dependencies = {}
Dependencies["Log"] = "%{DependencyDir}/spdlog"
Dependencies["SFML"] = "%{DependencyDir}/SFML"
Dependencies["glad"] = "%{DependencyDir}/glad"
Dependencies["glm"] = "%{DependencyDir}/glm"

include "Sandbox/Library/glad"

project (GameName)
	location (GameName)
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++latest"
	staticruntime "on"

	targetdir ("bin/"..OutputDir.."/%{prj.name}")
	objdir ("bin-int/"..OutputDir.."/%{prj.name}")

    pchheader "pch.h"
    pchsource "%{prj.name}/Source/pch.cpp"

    files {
        "%{prj.name}/Source/**.h",
        "%{prj.name}/Source/**.cpp"
    }

    includedirs {
        "%{prj.name}/Source",
        "%{Dependencies.Log}/include",
        "%{Dependencies.SFML}/include",
        "%{Dependencies.glad}",
         "%{Dependencies.glm}",
	}

	defines {
		"_CRT_SECURE_NO_WARNINGS",
        "SFML_STATIC"
    }

    filter {"platforms:Win64", "configurations:Debug"}
		libdirs {
			"%{Dependencies.SFML}/lib"
	    }

	    postbuildcommands {
	        ("{COPY} %{prj.location}/Library/SFML/bin/openal32.dll %{wks.location}/bin/"..OutputDir.. "/%{GameName}")
	    }


	filter {"platforms:Win64", "configurations:Debug"}
		defines {
			"ENABLE_ASSERTS"
		}

	filter "configurations:Debug"
		defines "DEBUG"
	    buildoptions "/MDd"
		runtime "Debug"
	    symbols "on"

	    links {
			"opengl32.lib",
            "freetype.lib",
            "winmm.lib",
            "gdi32.lib",
            "openal32.lib",
            "flac.lib",
            "vorbisenc.lib",
            "vorbisfile.lib",
            "vorbis.lib",
            "ogg.lib",
            "sfml-audio-s-d.lib",
            "sfml-graphics-s-d.lib",
            "sfml-window-s-d.lib",
            "sfml-system-s-d.lib"
	    }

	filter "configurations:Release"
        defines "RELEASE"
        buildoptions "/MD"
        runtime "Release"
        optimize "on"

        links {
			"opengl32.lib",
            "freetype.lib",
            "winmm.lib",
            "gdi32.lib",
            "openal32.lib",
            "flac.lib",
            "vorbisenc.lib",
            "vorbisfile.lib",
            "vorbis.lib",
            "ogg.lib",
            "sfml-audio-s.lib",
            "sfml-graphics-s.lib",
            "sfml-window-s.lib",
            "sfml-system-s.lib"
        }