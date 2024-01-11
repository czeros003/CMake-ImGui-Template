#pragma once
#include <GLFW/glfw3.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <imgui.h>
#include <implot.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <vector>
#include <implot_internal.h>

namespace Editor 
{
	static char text[4096];
	
	
	void Render();
	void Environment();
	void PlotDataFunction();
	void RenderPlot(const std::vector<float>& data, const char* plotTitle);
	void TextEditor();
	void FormatToJson();

	void SaveFile(const char* text, const char* fileName);
	void OpenFile(char* text);
	void Settings();
	void HighlightText(const char* text, const char* highlight);
	void Find(char* text, bool* pOpen);
	void Replace(char* text);
	void ReplaceAll(char* text);
	void DrawMultilineColoredText(const std::string& text);
	
}