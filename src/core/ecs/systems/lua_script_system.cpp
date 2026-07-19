#include "lua_script_system.h"
#include <engine_context.h>

namespace PotatoEngine::Core::ECS::Systems {
	using namespace ECS::Components;

	LuaScriptSystem::LuaScriptSystem(EngineContext& ctx) : ECS::System(ctx) {
		m_lua.open_libraries(
			sol::lib::base,
			sol::lib::package,
			sol::lib::math,
			sol::lib::string,
			sol::lib::table
		);

		sol::table debug = m_lua.create_named_table("debug");

		debug.set_function("log", [&ctx](const std::string& message) {
			ctx.Debug.Log(message);
		});

		sol::table reg = m_lua.create_named_table("registry");
		reg.set_function("create", [&ctx](const std::string& name) -> EntityID {
			return ctx.Registry.CreateEntity(name);
		});

		reg.set_function("get_component", [&ctx](sol::this_state ts, EntityID e, const std::string& name) -> sol::object {
			sol::state_view lua(ts);

			for (const auto& comp : ctx.Registry.GetComponentNames()) {
				if (name == comp) {
					Component* c = ctx.Registry.GetComponentByName(e, name);
					MEB_ASSERT(c);
					 
					return ctx.Registry.BindComponentToLua(lua, c, name);
				}
			}

			return sol::nil;
		});

		sol::table time = m_lua.create_named_table("time");
		time.set_function("delta_time", [&ctx] { return ctx.GetDeltaTime(); });
		time.set_function("time", [&ctx] { return ctx.GetTime(); });

		// input:
		sol::table input = m_lua.create_named_table("input");
		input.set_function("is_key", [&ctx](Input::Key key) -> bool { return ctx.InputState.IsKey(key); });
		input.set_function("is_key_down", [&ctx](Input::Key key) -> bool { return ctx.InputState.IsKeyDown(key); });
		input.set_function("is_key_up", [&ctx](Input::Key key) -> bool { return ctx.InputState.IsKeyUp(key); });

		// enums:
		m_lua.new_enum<Input::Key>("Key", {
			{ "NONE", Input::Key::NONE },

			{ "Q", Input::Key::Q },
			{ "W", Input::Key::W },
			{ "E", Input::Key::E },
			{ "R", Input::Key::R },
			{ "T", Input::Key::T },
			{ "Y", Input::Key::Y },
			{ "U", Input::Key::U },
			{ "I", Input::Key::I },
			{ "O", Input::Key::O },
			{ "P", Input::Key::P },

			{ "A", Input::Key::A },
			{ "S", Input::Key::S },
			{ "D", Input::Key::D },
			{ "F", Input::Key::F },
			{ "G", Input::Key::G },
			{ "H", Input::Key::H },
			{ "J", Input::Key::J },
			{ "K", Input::Key::K },
			{ "L", Input::Key::L },

			{ "Z", Input::Key::Z },
			{ "X", Input::Key::X },
			{ "C", Input::Key::C },
			{ "V", Input::Key::V },
			{ "B", Input::Key::B },
			{ "N", Input::Key::N },
			{ "M", Input::Key::M },

			{ "LEFT_CTRL", Input::Key::LEFT_CTRL },
			{ "RIGHT_CTRL", Input::Key::RIGHT_CTRL },
			{ "LEFT_SHIFT", Input::Key::LEFT_SHIFT },
			{ "RIGHT_SHIFT", Input::Key::RIGHT_SHIFT },
			{ "LEFT_MAYUS", Input::Key::LEFT_MAYUS },
			{ "RIGHT_MAYUS", Input::Key::RIGHT_MAYUS },
			{ "LEFT_ALT", Input::Key::LEFT_ALT },
			{ "RIGHT_ALT", Input::Key::RIGHT_ALT },

			{ "TAB", Input::Key::TAB },
			{ "ESC", Input::Key::ESC },

			{ "NUM1", Input::Key::NUM1 },
			{ "NUM2", Input::Key::NUM2 },
			{ "NUM3", Input::Key::NUM3 },
			{ "NUM4", Input::Key::NUM4 },
			{ "NUM5", Input::Key::NUM5 },
			{ "NUM6", Input::Key::NUM6 },
			{ "NUM7", Input::Key::NUM7 },
			{ "NUM8", Input::Key::NUM8 },
			{ "NUM9", Input::Key::NUM9 },
			{ "NUM0", Input::Key::NUM0 },

			{ "F1", Input::Key::F1 },
			{ "F2", Input::Key::F2 },
			{ "F3", Input::Key::F3 },
			{ "F4", Input::Key::F4 },
			{ "F5", Input::Key::F5 },
			{ "F6", Input::Key::F6 },
			{ "F7", Input::Key::F7 },
			{ "F8", Input::Key::F8 },
			{ "F9", Input::Key::F9 },
			{ "F10", Input::Key::F10 },
			{ "F11", Input::Key::F11 },
			{ "F12", Input::Key::F12 },

			{ "SPACE", Input::Key::SPACE },
			{ "ENTER", Input::Key::ENTER },

			{ "LEFT", Input::Key::LEFT },
			{ "DOWN", Input::Key::DOWN },
			{ "RIGHT", Input::Key::RIGHT },
			{ "UP", Input::Key::UP },
		});

		// TODO: organize better the structure 
		// 
		// usertypes:

		m_lua.new_usertype<Component>("Component");

		m_lua.new_usertype<Name>("Name",
			sol::constructors<Name(const std::string& name)>(),
			"value", &Name::Value,
			sol::base_classes, sol::bases<Component>()
		);

		m_lua.new_usertype<Transform>("Transform",
			sol::constructors<
				Transform(),
				Transform(glm::vec3, glm::vec3, glm::vec3)
			>(),

			"position", &Transform::Position,
			"rotation", &Transform::Rotation,
			"scale",	&Transform::Scale
		);

		m_lua.new_usertype<SpriteRenderer>("SpriteRenderer",
			sol::constructors<
				SpriteRenderer()//,
				// SpriteRenderer(const std::string& path)
			>(),

			"color", &SpriteRenderer::Color,
			"pivot", &SpriteRenderer::Pivot,
			"layer", &SpriteRenderer::Layer,
			"flipX", &SpriteRenderer::FlipX,
			"flipY", &SpriteRenderer::FlipY
		);

		m_lua.new_usertype<Camera>("Camera",
			sol::constructors<
			Camera()
			>(),

			"clearColor", &Camera::ClearColor
		);

		m_lua.new_usertype<glm::vec3>("vec3",
			sol::constructors<
				glm::vec3(),
				glm::vec3(float, float, float) 
			>(),

			"x", &glm::vec3::x,
			"y", &glm::vec3::y,
			"z", &glm::vec3::z,

			"r", &glm::vec3::r,
			"g", &glm::vec3::g,
			"b", &glm::vec3::b,

			"length", [](const glm::vec3& self) { return glm::length(self); },
			"normalize", [](glm::vec3& self) { self = glm::normalize(self); },
			"dot", [](const glm::vec3& self, const glm::vec3& other) { return glm::dot(self, other); },
			"cross", [](const glm::vec3& self, const glm::vec3& other) { return glm::cross(self, other); },

			sol::meta_function::addition, [](const glm::vec3& a, const glm::vec3& b) { return a + b; },
			sol::meta_function::subtraction, [](const glm::vec3& a, const glm::vec3& b) { return a - b; },
			sol::meta_function::multiplication, [](const glm::vec3& v, float s) { return v * s; },

			sol::meta_function::to_string, [](const glm::vec3& self) {
				return "vec3(" + std::to_string(self.x) + ", " + std::to_string(self.y) + ", " + std::to_string(self.z) + ")";
			}
		);

		m_lua.new_usertype<glm::vec4>("vec4",
			sol::constructors<
				glm::vec4(),
				glm::vec4(float, float, float, float)
			>(),

			"x", &glm::vec4::x,
			"y", &glm::vec4::y,
			"z", &glm::vec4::z,
			"w", &glm::vec4::w,

			"r", &glm::vec4::r,
			"g", &glm::vec4::g,
			"b", &glm::vec4::b,
			"a", &glm::vec4::a,

			"length", [](const glm::vec4& self) { return glm::length(self); },
			"normalize", [](glm::vec4& self) { self = glm::normalize(self); },
			"dot", [](const glm::vec4& self, const glm::vec4& other) { return glm::dot(self, other); },

			sol::meta_function::addition, [](const glm::vec4& a, const glm::vec4& b) { return a + b; },
			sol::meta_function::subtraction, [](const glm::vec4& a, const glm::vec4& b) { return a - b; },
			sol::meta_function::multiplication, [](const glm::vec4& v, float s) { return v * s; },

			sol::meta_function::to_string, [](const glm::vec4& self) {
				return "vec4(" + std::to_string(self.x) + ", " + std::to_string(self.y) + ", " +
					std::to_string(self.z) + ", " + std::to_string(self.w) + ")";
			}
		);
	}

	bool LuaScriptSystem::RunLuaSafe(sol::load_result& chunk, const char* stage) {
		if (!chunk.valid()) {
			sol::error err = chunk;
			MEB_LOG_ERRORF("Lua compile error (%s): %s", stage, err.what());
			return false;
		}

		sol::protected_function_result result = chunk();

		if (!result.valid()) {
			sol::error err = result;
			MEB_LOG_ERRORF("Lua runtime error (%s): %s", stage, err.what());
			return false;
		}

		return true;
	}

	bool LuaScriptSystem::CallLuaFunction(sol::function& func, const char* name) {
		if (!func.valid()) {
			MEB_LOG_WARNINGF("Lua function '%s' not found", name);
			return false;
		}

		try {
			sol::protected_function_result r = func();
			if (!r.valid()) {
				sol::error err = r;
				MEB_LOG_ERRORF("Lua runtime error (%s): %s", name, err.what());
				return false;
			}
		}
		catch (const sol::error& err) {
			MEB_LOG_ERRORF("Lua runtime error (%s): %s", name, err.what());
			return false;
		}


		return true;
	}

    void LuaScriptSystem::OnStart() {
        m_context.Registry.Each<Components::LuaScript>([&](auto& script) {
			MEB_LOG_INFOF("Calling lua start to script with assetid: %lld", script.GetScriptAssetID());
			script.CallFunction(LUA_START_FUNC_NAME);
        });
    }

	void LuaScriptSystem::OnUpdate() {
		m_context.Registry.Each<Components::LuaScript>([&](auto& script) {
			script.CallFunction(LUA_UPDATE_FUNC_NAME);
		});
	}

	void LuaScriptSystem::OnDestroy() {
		m_context.Registry.Each<Components::LuaScript>([&](auto& script) {
			script.CallFunction(LUA_DESTROY_FUNC_NAME);
		});
	}
}
