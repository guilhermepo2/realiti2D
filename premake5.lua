workspace "Realiti2D"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
	}
	
	startproject "Sandbox"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
IncludeDir = {}
IncludeDir["SDL2"] = "%{prj.name}/thirdparty/SDL2-2.0.12/include"
IncludeDir["GLEW"] = "%{prj.name}/thirdparty/glew-2.1.0/include"
LibDir = {}
LibDir["SDL2"] = "%{prj.name}/thirdparty/SDL2-2.0.12/lib/x64"
LibDir["GLEW"] = "%{prj.name}/thirdparty/glew-2.1.0/lib/Release/x64"

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
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/src",
		"%{prj.name}/thirdparty/spdlog/include",
		"%{IncludeDir.SDL2}",
		"%{IncludeDir.GLEW}"
	}
	
	libdirs
	{
		"%{LibDir.SDL2}",
		"%{LibDir.GLEW}",
	}

    links
    {
		"SDL2.lib",
		"glew32.lib",
		"opengl32.lib"
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
		"%{IncludeDir.SDL2}",
		"%{IncludeDir.GLEW}"
	}

	links 
	{
		"Realiti2D"
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