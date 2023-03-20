#pragma once
namespace GameEngine {
	class ITameable
	{
	private:
		bool _tamed;

	protected:
		void tame() { _tamed = true; }
		void untame() { _tamed = false; }
		void tamed(bool t) { _tamed = t; }

	public:
		ITameable();
		~ITameable();
		bool tamed() { return _tamed; }

	};
}