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
				SpriteRenderer(),
				SpriteRenderer(const std::string& path)
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
