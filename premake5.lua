workspace "OpenGL"
	startproject "OpenGL"

	architecture "x64"

	configurations {
		"Debug",
		"Release"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

includes = {}
includes["GLFW"] = "OpenGL/vendor/GLFW/include"

-- all dependencies go between the group labels below
group "Dependencies"

	include "OpenGL/vendor/GLFW"

-- main project group
group ""

	project "OpenGL"
		location "OpenGL"
		kind "ConsoleApp"
		language "C++"

		targetdir ("bin/" .. outputdir .. "/%{prj.name}")
		objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

		files {
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp"
		}

		includedirs {
			"%{prj.name}/src",
			"%{includes.GLFW}"
			--"%{prj.name}/vendor/spdlog/include"
		}

		links {
			"GLFW",
			"opengl32.lib"
		}

		filter "system:windows"
			cppdialect "C++17"
			staticruntime "On"
			systemversion "latest"

		filter "configurations:Debug"
			defines "E2D_DEBUG"
			symbols "On"

		filter "configurations:Release"
			defines "E2D_RELEASE"
			optimize "On"

		filter "configurations:Dist"
			defines "E2D_DIST"
			optimize "On"
