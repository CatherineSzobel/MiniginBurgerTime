#include "MiniginPCH.h"
#include "PlotComponent.h"
#include "imgui.h"
#include "backends/imgui_impl_opengl2.h"
#include "backends/imgui_impl_sdl.h"
#include "include/imgui_plot.h"
#include <chrono>
using namespace std::chrono;
constexpr size_t buf_size = 1024;

static float x_data[buf_size];
static float y_data[buf_size];
static float y_data2[buf_size];
static float y_data3[buf_size];

void dae::PlotComponent::Render() const
{

	Exercise01();
	Exercise02();
}

void dae::PlotComponent::Exercise01() const
{
	ImGui::Begin("Exercise 1");
	static int i0 = 10;
	ImGui::InputInt("# samples", &i0);
	static int firstButtonClick = 0;


	//static float arr[] = { 1225.f / i0, 946.f / i0, 995.f / i0, 860.f/ i0, 844.f/ i0, 563.f/ i0, 322.f/ i0 };
	//ImGui::PlotLines("Curve", arr, IM_ARRAYSIZE(arr));


	if (ImGui::Button("Trash the cache"))
	{
		ImGui::Text("Please wait...");
		GenerateDataExercise01(i0);
		firstButtonClick++;
	}
	if (firstButtonClick & 1)
	{
		drawMultiPlotExercise01();
	}

	ImGui::End();


}

void dae::PlotComponent::Exercise02() const
{
	static int secondButtonClick = 0;
	static int thirdButtonClick = 0;

	ImGui::Begin("Exercise 2");
	static int i1 = 10;
	//	GenerateData(i1);
	ImGui::InputInt("# samples", &i1);
	if (ImGui::Button("Trash the cache with GameObject"))
	{
		ImGui::Text("Please wait...");
		secondButtonClick++;
		GenerateDataExercise02(i1);
	}
	if (secondButtonClick & 1)
	{
		drawMultiPlotExercise02();

	}

	//start plot

	if (ImGui::Button("Trash the cache with GameObject3DAlt"))
	{
		//start plot
		ImGui::Text("Please wait...");
		GenerateDataExercise02Alt(i1);
		thirdButtonClick++;
	}
	if (thirdButtonClick & 1)
	{
		drawMultiPlotAltExercise02();

	}


	ImGui::End();
}

void dae::PlotComponent::GenerateDataExercise01(const int& data) const
{
	std::vector<int> intArr;
	intArr.resize(data);
	std::vector<int> durationArr;
	for (int k = 1; k <= 1024; k *= 2)
	{

		const auto begin = high_resolution_clock::now();
		for (int i = 0; i < data; i += k)
		{
			intArr[i] *= 2;
			intArr[i] *= 2;
			intArr[i] *= 2;
			intArr[i] *= 2;
			intArr[i] *= 2;
		}
		const auto end = high_resolution_clock::now();
		const auto duration = duration_cast<nanoseconds>(end - begin).count();
		durationArr.push_back(static_cast<int>(duration));
	}
	for (size_t i = 0; i < 11; ++i)
	{

		x_data[i] = static_cast<float>(i);
		y_data[i] = static_cast<float>(durationArr[i]);
	}
}

void dae::PlotComponent::GenerateDataExercise02(const int& data) const
{
	std::vector<int> durationArr;
	std::vector<GameObject3D> gameobjectArr;
	gameobjectArr.resize(data);

	for (int k = 1; k <= 1024; k *= 2)
	{

		const auto begin = high_resolution_clock::now();
		for (int i = 0; i < data; i += k)
		{
			gameobjectArr[i].ID *= 2;
		}
		const auto end = high_resolution_clock::now();
		const auto duration = duration_cast<nanoseconds>(end - begin).count();
		durationArr.push_back(static_cast<int>(duration));
	}
	for (size_t i = 0; i < 300; ++i)
	{

		y_data2[i] = static_cast<float>(i);
		y_data2[i] = durationArr[i] / 1000.f;
	}
}

void dae::PlotComponent::GenerateDataExercise02Alt(const int& data) const
{
	//alternative -> use pointers
	std::vector<GameObject3DAlternative> gameobjectArrAlt{};

	gameobjectArrAlt.resize(data);
	std::vector<int> durationArr;
	for (int k = 1; k <= 1024; k *= 2)
	{

		const auto begin = high_resolution_clock::now();
		for (int i = 0; i < data; i += k)
		{
			gameobjectArrAlt[i].ID *= 2;
		}
		const auto end = high_resolution_clock::now();
		const auto duration = duration_cast<nanoseconds>(end - begin).count();
		durationArr.push_back(static_cast<int>(duration));
	}
	for (size_t i = 0; i < 300; ++i)
	{

		y_data3[i] = static_cast<float>(i);
		y_data3[i] = durationArr[i] / 1000.f;
	}
}

void dae::PlotComponent::drawMultiPlotExercise01() const
{
	static ImU32 colors[1] = { ImColor(0, 255, 0) };
	static uint32_t selection_start = 0, selection_length = 0;

	ImGui::PlotConfig conf;
	conf.values.xs = x_data;
	conf.values.count = buf_size;
	conf.values.ys = y_data; // use ys_list to draw several lines simultaneously
	conf.values.ys_count = 1;
	conf.values.colors = colors;
	conf.scale.min = 0;
	conf.scale.max = 1;
	conf.tooltip.show = true;
	conf.grid_x.size = 128;
	conf.grid_x.subticks = 1;
	conf.grid_y.show = true;
	conf.grid_y.size = 0.5f;
	conf.grid_y.subticks = 1;
	conf.selection.show = true;
	conf.selection.start = &selection_start;
	conf.selection.length = &selection_length;
	conf.frame_size = ImVec2(300, 150);
	ImGui::Plot("plot1", conf);
}

void dae::PlotComponent::drawMultiPlotExercise02() const
{
	static ImU32 colors[1] = { ImColor(0, 255, 0) };
	static uint32_t selection_start = 0, selection_length = 0;

	ImGui::PlotConfig conf;
	conf.values.xs = x_data;
	conf.values.count = buf_size;
	conf.values.ys = y_data2; // use ys_list to draw several lines simultaneously
	conf.values.ys_count = 1;
	conf.values.colors = colors;
	conf.scale.min = 0;
	conf.scale.max = 1;
	conf.tooltip.show = true;
	conf.grid_x.size = 128;
	conf.grid_x.subticks = 1;
	conf.grid_y.show = true;
	conf.grid_y.size = 0.5f;
	conf.grid_y.subticks = 1;
	conf.selection.show = true;
	conf.selection.start = &selection_start;
	conf.selection.length = &selection_length;
	conf.frame_size = ImVec2(300, 150);
	ImGui::Plot("plot2", conf);
}

void dae::PlotComponent::drawMultiPlotAltExercise02() const
{
	static ImU32 colors[1] = { ImColor(0, 255, 0) };
	static uint32_t selection_start = 0, selection_length = 0;

	ImGui::PlotConfig conf;
	conf.values.xs = x_data;
	conf.values.count = buf_size;
	conf.values.ys = y_data3; // use ys_list to draw several lines simultaneously
	conf.values.ys_count = 1;
	conf.values.colors = colors;
	conf.scale.min = 0;
	conf.scale.max = 1;
	conf.tooltip.show = true;
	conf.grid_x.size = 128;
	conf.grid_x.subticks = 1;
	conf.grid_y.show = true;
	conf.grid_y.size = 0.5f;
	conf.grid_y.subticks = 1;
	conf.selection.show = true;
	conf.selection.start = &selection_start;
	conf.selection.length = &selection_length;
	conf.frame_size = ImVec2(300, 150);
	ImGui::Plot("plot3", conf);
}
