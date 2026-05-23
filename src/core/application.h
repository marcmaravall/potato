#ifndef POTATO_APPLICATION_H
#define POTATO_APPLICATION_H

namespace PotatoEngine::Core {

	class Application {
	protected:
		bool m_running = true;
		bool showWindow = true;

	public:
		virtual ~Application() = default;

		void Run();

		virtual void OnStart()	 {}
		virtual void OnUpdate()  {}
		virtual void OnDestroy() {}
	};
}

#endif // POTATO_APPLICATION_H