workspace "Realiti2D"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
	}
	
	startproject "VisionsEditor"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
IncludeDir = {}
IncludeDir["SDL2"] = "%{prj.name}/thirdparty/SDL2-2.0.12/include"
IncludeDir["GLEW"] = "%{prj.name}/thirdparty/glew-2.1.0/include"
IncludeDir["SOIL"] = "%{prj.name}/thirdparty/soil-0.0.3/include"
IncludeDir["GLM"] = "%{prj.name}/thirdparty/glm"
IncludeDir["RAPIDJSON"] = "%{prj.name}/thirdparty/rapidjson-1.1.0/include"
IncludeDir["DEARIMGUI"] = "%{prj.name}/thirdparty/dearimgui"
IncludeDir["SDL_TTF"] = "%{prj.name}/thirdparty/SDL2_ttf-2.0.15/include"
LibDir = {}
LibDir["SDL2"] = "%{prj.name}/thirdparty/SDL2-2.0.12/lib/x64"
LibDir["GLEW"] = "%{prj.name}/thirdparty/glew-2.1.0/lib/Release/x64"
LibDir["SDL_TTF"] = "%{prj.name}/thirdparty/SDL2_ttf-2.0.15/lib/x64"


--- project "SOIL"
--- 	location "Realiti2D/thirdparty/soil-0.0.3"
--- 	kind "StaticLib"
--- 	language "C"
--- 	staticruntime "on"
---
--- 	targetdir("bin/".. outputdir .. "/%{prj.name}");
--- 	objdir("bin-int/" .. outputdir .. "/%{prj.name}");
---
--- 	files
--- 	{
--- 		"Realiti2D/thirdparty/soil-0.0.3/include/SOIL/**.h",
--- 		"Realiti2D/thirdparty/soil-0.0.3/src/**.c"
--- 	}

project "Realiti2D"
    location "Realiti2D"
    kind "StaticLib"
    language "C++"
    staticruntime "on"

    targetdir("bin/" .. outputdir .. "/%{prj.name}" )
    objdir("bin-int/" .. outputdir .. "/%{prj.name}" )

    files
    {
        "%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		
		-- this is temporary (and bad), I should fix this.

		"%{prj.name}/thirdparty/soil-0.0.3/include/SOIL/**.h",
		"%{prj.name}/thirdparty/soil-0.0.3/src/**.c",
		"%{prj.name}/thirdparty/dearimgui/*.h",
		"%{prj.name}/thirdparty/dearimgui/*.cpp"
    }

    includedirs
    {
        "%{prj.name}/src",
		"%{prj.name}/thirdparty/spdlog/include",
		"%{IncludeDir.SDL2}",
		"%{IncludeDir.GLEW}",
		"%{IncludeDir.SOIL}",
		"%{IncludeDir.GLM}",
		"%{IncludeDir.RAPIDJSON}",
		"%{IncludeDir.DEARIMGUI}",
		"%{IncludeDir.SDL_TTF}",
	}
	
	libdirs
	{
		"%{LibDir.SDL2}",
		"%{LibDir.GLEW}",
		"%{LibDir.SDL_TTF}",
	}

    links
    {
		"SDL2.lib",
		"glew32.lib",
		"opengl32.lib",
		"SDL2_ttf.lib",
    }

    filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines 
		{
			"R2D_ENABLE_ASSERT"
		}
	
	filter "configurations:Debug"
		defines "R2D_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "R2D_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "R2D_DIST"
        optimize "On"
        
project "VisionsEditor"
		location "VisionsEditor"
		kind "ConsoleApp"
		language "C++"

		targetdir ("bin/" .. outputdir .. "/%{prj.name}")
		objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

		files
		{
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp"
		}

		includedirs
		{
			"Realiti2D/src",
			"Realiti2D/thirdparty/spdlog/include",
			"Realiti2D/thirdparty/SDL2-2.0.12/include",
			"Realiti2D/thirdparty/glew-2.1.0/include",
			"Realiti2D/thirdparty/soil-0.0.3/include",
			"Realiti2D/thirdparty/glm",
			"Realiti2D/thirdparty/rapidjson-1.1.0/include",
			"Realiti2D/thirdparty/dearimgui",
		}

		links 
		{
			"Realiti2D"
		}

		postbuildcommands
		{
		
		}

		filter "system:windows"
			cppdialect "C++17"
			staticruntime "On"
			systemversion "latest"

			defines 
			{
			}

		filter "configurations:Debug"
			defines { "R2D_DEBUG", "VISIONS_EDITOR" }
			symbols "On"

		filter "configurations:Release"
			defines { "R2D_RELEASE", "VISIONS_EDITOR" }
			optimize "On"

		filter "configurations:Dist"
			defines { "R2D_DIST", "VISIONS_EDITOR" }
			optimize "On"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Realiti2D/src",
		"Realiti2D/thirdparty/spdlog/include",
		"Realiti2D/thirdparty/SDL2-2.0.12/include",
		"Realiti2D/thirdparty/glew-2.1.0/include",
		"Realiti2D/thirdparty/soil-0.0.3/include",
		"Realiti2D/thirdparty/glm",
		"Realiti2D/thirdparty/rapidjson-1.1.0/include",
		"Realiti2D/thirdparty/SDL2_ttf-2.0.15/include"
	}

	links 
	{
		"Realiti2D"
	}

	postbuildcommands
	{
		
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines 
		{
		}

	filter "configurations:Debug"
		defines "R2D_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "R2D_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "R2D_DIST"
        optimize "On"