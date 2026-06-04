#ifndef POTATO_DEBUG_INFO_H
#define POTATO_DEBUG_INFO_H

#include <ref_scope.h>

#include <string>
#include <vector>

namespace PotatoEngine::Core::Logging {

	class DebugSystem {
	public:
		class Message {
		public:
			
			enum class Type {
				_INFO,
				_SUCCESS,
				_WARNING,
				_ERROR
			};

			std::string Text;
			Type _Type;

			Message(const std::string& str, const Type t) : Text(str), _Type(t) {}
		};

	protected:
		std::vector<Message> m_messages;
	
	public:
		DebugSystem();
		~DebugSystem();

	public:
		void Log(const Message& message);
		void Log(const std::string& message, const Message::Type type = Message::Type::_INFO) {
			Log(Message(message, type));
		}
		void PopLast();
		void Clear();

		std::vector<Message>& GetMessages() { return m_messages; }

	public:
		// Singleton:
		static DebugSystem *s_Instance;
	};
}

#endif // POTATO_DEBUG_INFO_H