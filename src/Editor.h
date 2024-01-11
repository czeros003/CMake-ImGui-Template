#pragma once
#include <string>
#include <vector>

namespace Editor
{
	// Generuj wykres tutaj
	void RenderPlot(const std::vector<float>& data, const char* plotTitle);

	void DrawMultilineColoredText(const std::string& text);
}
