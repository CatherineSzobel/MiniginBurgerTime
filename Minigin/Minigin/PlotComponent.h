#pragma once
#include "BaseComponent.h"
#include "Singleton.h"
namespace dae
{
	class PlotComponent final : public Singleton<PlotComponent>
	{
	public:
		void Init();
		void Render() const;

		explicit PlotComponent() = default;
		~PlotComponent() = default;
		PlotComponent(const PlotComponent& other) = delete;
		PlotComponent(PlotComponent&& other) = delete;
		PlotComponent& operator=(const PlotComponent& other) = delete;
		PlotComponent& operator=(PlotComponent&& other) = delete;
	private:

		void Exercise01() const;
		void Exercise02() const;

		void GenerateDataExercise01(const int& data) const;
		void GenerateDataExercise02(const int& data) const;
		void GenerateDataExercise02Alt(const int& data) const;

		void drawMultiPlotExercise01() const;
		void drawMultiPlotExercise02() const;
		void drawMultiPlotAltExercise02() const;

		float _xFrameSize;
		float _yFrameSize;

		struct Transform
		{
			float matrix[16] = {
				1,0,0,0,
				0,1,0,0,
				0,0,1,0,
				0,0,0,1
			};
		};
		class GameObject3D
		{
		public:
			Transform transform;
			int ID;
		};
		class GameObject3DAlternative
		{
		public:
			Transform* transform;
			int ID;
		};

	};
}

