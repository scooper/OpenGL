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
includes["Glad"] = "OpenGL/vendor/Glad/include"
includes["ImGui"] = "OpenGL/vendor/imgui"
includes["glm"]  = "OpenGL/vendor/glm"
includes["spdlog"] = "OpenGL/vendor/spdlog/include"
includes["stbimage"] = "OpenGL/vendor/stbimage"

-- all dependencies go between the group labels below
group "Dependencies"

	include "OpenGL/vendor/GLFW"
	include "OpenGL/vendor/Glad"
	include "OpenGL/vendor/imgui"

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
			"%{prj.name}/src/**.cpp",
			"%{prj.name}/vendor/glm/glm/**.hpp",
			"%{prj.name}/vendor/glm/glm/**.inl",
			"%{prj.name}/vendor/stbimage/**.cpp",
			"%{prj.name}/vendor/stbimage/**.h",
			"%{prj.name}/vendor/imgui/examples/imgui_impl_opengl3.h",
			"%{prj.name}/vendor/imgui/examples/imgui_impl_opengl3.cpp",
			"%{prj.name}/vendor/imgui/examples/imgui_impl_glfw.h",
			"%{prj.name}/vendor/imgui/examples/imgui_impl_glfw.cpp"
			
		}

		includedirs {
			"%{prj.name}/src",
			"%{includes.GLFW}",
			"%{includes.Glad}",
			"%{includes.ImGui}",
			"%{includes.glm}",
			"%{includes.spdlog}",
			"%{includes.stbimage}"
			
		}

		links {
			"GLFW",
			"Glad",
			"ImGui",
			"opengl32.lib",
			"glu32.lib"
		}

		filter "system:windows"
			cppdialect "C++17"
			staticruntime "On"
			systemversion "latest"

			defines {
				"WINDOWS",
				"GLFW_INCLUDE_NONE"
			}

		filter "configurations:Debug"
			defines "_DEBUG"
			symbols "On"

		filter "configurations:Release"
			defines "_RELEASE"
			optimize "On"

		filter "configurations:Dist"
			defines "_DIST"
			optimize "On"
