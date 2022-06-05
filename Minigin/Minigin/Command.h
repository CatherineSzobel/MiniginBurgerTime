#pragma once
namespace dae
{
	class Command
	{
	public:
		virtual ~Command() = default;
		virtual void Execute() = 0;
	};

	class FireCommand final : public Command
	{
	public:
		void Execute() override { std::cout << "Fire!"; }
	};

	class JumpCommand final : public Command
	{
	public:
		void Execute() override { std::cout << "Jump!"; }
		
	};

	class DuckCommand final : public Command
	{
	public:
		void Execute() override { std::cout << "Duck!"; }
	};

	class FartCommand final : public Command
	{
	public:
		void Execute() override { std::cout << "Fart!"; }
	};
}