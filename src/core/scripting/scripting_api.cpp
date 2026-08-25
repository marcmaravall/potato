#include "scripting_api.hpp"

#include <ecs/components/all_components.h>
#include <input/input_state.h>

#include <glm/glm.hpp>

namespace PotatoEngine::Core::Scripting {

using namespace ECS::Components;

void ScriptingAPI::InitInput(sol::state& lua, EngineContext& ctx) {
    sol::table input = lua.create_named_table("Input");
    input.set_function("isKey", [&ctx](Input::Key key) -> bool {
        return ctx.InputState.IsKey(key);
    });
    input.set_function("isKeyDown", [&ctx](Input::Key key) -> bool {
        return ctx.InputState.IsKeyDown(key);
    });
    input.set_function("isKeyUp", [&ctx](Input::Key key) -> bool {
        return ctx.InputState.IsKeyUp(key);
    });

    lua.new_enum<Input::Key>("Key",
                             {
                                 {"NONE", Input::Key::NONE},

                                 {"Q", Input::Key::Q},
                                 {"W", Input::Key::W},
                                 {"E", Input::Key::E},
                                 {"R", Input::Key::R},
                                 {"T", Input::Key::T},
                                 {"Y", Input::Key::Y},
                                 {"U", Input::Key::U},
                                 {"I", Input::Key::I},
                                 {"O", Input::Key::O},
                                 {"P", Input::Key::P},

                                 {"A", Input::Key::A},
                                 {"S", Input::Key::S},
                                 {"D", Input::Key::D},
                                 {"F", Input::Key::F},
                                 {"G", Input::Key::G},
                                 {"H", Input::Key::H},
                                 {"J", Input::Key::J},
                                 {"K", Input::Key::K},
                                 {"L", Input::Key::L},

                                 {"Z", Input::Key::Z},
                                 {"X", Input::Key::X},
                                 {"C", Input::Key::C},
                                 {"V", Input::Key::V},
                                 {"B", Input::Key::B},
                                 {"N", Input::Key::N},
                                 {"M", Input::Key::M},

                                 {"LEFT_CTRL", Input::Key::LEFT_CTRL},
                                 {"RIGHT_CTRL", Input::Key::RIGHT_CTRL},
                                 {"LEFT_SHIFT", Input::Key::LEFT_SHIFT},
                                 {"RIGHT_SHIFT", Input::Key::RIGHT_SHIFT},
                                 {"LEFT_MAYUS", Input::Key::LEFT_MAYUS},
                                 {"RIGHT_MAYUS", Input::Key::RIGHT_MAYUS},
                                 {"LEFT_ALT", Input::Key::LEFT_ALT},
                                 {"RIGHT_ALT", Input::Key::RIGHT_ALT},

                                 {"TAB", Input::Key::TAB},
                                 {"ESC", Input::Key::ESC},

                                 {"NUM1", Input::Key::NUM1},
                                 {"NUM2", Input::Key::NUM2},
                                 {"NUM3", Input::Key::NUM3},
                                 {"NUM4", Input::Key::NUM4},
                                 {"NUM5", Input::Key::NUM5},
                                 {"NUM6", Input::Key::NUM6},
                                 {"NUM7", Input::Key::NUM7},
                                 {"NUM8", Input::Key::NUM8},
                                 {"NUM9", Input::Key::NUM9},
                                 {"NUM0", Input::Key::NUM0},

                                 {"F1", Input::Key::F1},
                                 {"F2", Input::Key::F2},
                                 {"F3", Input::Key::F3},
                                 {"F4", Input::Key::F4},
                                 {"F5", Input::Key::F5},
                                 {"F6", Input::Key::F6},
                                 {"F7", Input::Key::F7},
                                 {"F8", Input::Key::F8},
                                 {"F9", Input::Key::F9},
                                 {"F10", Input::Key::F10},
                                 {"F11", Input::Key::F11},
                                 {"F12", Input::Key::F12},

                                 {"SPACE", Input::Key::SPACE},
                                 {"ENTER", Input::Key::ENTER},

                                 {"LEFT", Input::Key::LEFT},
                                 {"DOWN", Input::Key::DOWN},
                                 {"RIGHT", Input::Key::RIGHT},
                                 {"UP", Input::Key::UP},
                             });
}

void ScriptingAPI::InitTime(sol::state& lua, EngineContext& ctx) {
    sol::table time = lua.create_named_table("Time");
    time.set_function("deltaTime", [&ctx] { return ctx.GetDeltaTime(); });
    time.set_function("time", [&ctx] { return ctx.GetTime(); });
}

void ScriptingAPI::InitComponents(sol::state& lua) {
    lua.new_usertype<ECS::Component>("Component");

    lua.new_usertype<Name>(
        "Name", sol::constructors<Name(const std::string& name)>(), "value",
        &Name::Value, sol::base_classes, sol::bases<ECS::Component>());

    lua.new_usertype<Transform>(
        "Transform",
        sol::constructors<Transform(),
                          Transform(glm::vec3, glm::vec3, glm::vec3)>(),

        "position", &Transform::Position, "rotation", &Transform::Rotation,
        "scale", &Transform::Scale);

    lua.new_usertype<SpriteRenderer>(
        "SpriteRenderer",
        sol::constructors<SpriteRenderer()  //,
                                            // SpriteRenderer(const std::string&
                                            // path)
                          >(),

        "color", &SpriteRenderer::Color, "pivot", &SpriteRenderer::Pivot,
        "layer", &SpriteRenderer::Layer, "flipX", &SpriteRenderer::FlipX,
        "flipY", &SpriteRenderer::FlipY);

    lua.new_usertype<Camera>("Camera", sol::constructors<Camera()>(),

                             "clearColor", &Camera::ClearColor, "zoom",
                             &Camera::Zoom);
}

void ScriptingAPI::InitGLM(sol::state& lua) {
    lua.new_usertype<glm::vec3>(
        "Vec3",
        sol::constructors<glm::vec3(), glm::vec3(float, float, float)>(),

        "x", &glm::vec3::x, "y", &glm::vec3::y, "z", &glm::vec3::z,

        "r", &glm::vec3::r, "g", &glm::vec3::g, "b", &glm::vec3::b,

        "length", [](const glm::vec3& self) { return glm::length(self); },
        "normalize", [](glm::vec3& self) { self = glm::normalize(self); },
        "dot",
        [](const glm::vec3& self, const glm::vec3& other) {
            return glm::dot(self, other);
        },
        "cross",
        [](const glm::vec3& self, const glm::vec3& other) {
            return glm::cross(self, other);
        },

        sol::meta_function::addition,
        [](const glm::vec3& a, const glm::vec3& b) { return a + b; },
        sol::meta_function::subtraction,
        [](const glm::vec3& a, const glm::vec3& b) { return a - b; },
        sol::meta_function::multiplication,
        [](const glm::vec3& v, float s) { return v * s; },

        sol::meta_function::to_string,
        [](const glm::vec3& self) {
            return "Vec3(" + std::to_string(self.x) + ", " +
                   std::to_string(self.y) + ", " + std::to_string(self.z) + ")";
        });

    lua.new_usertype<glm::vec4>(
        "Vec4",
        sol::constructors<glm::vec4(), glm::vec4(float, float, float, float)>(),

        "x", &glm::vec4::x, "y", &glm::vec4::y, "z", &glm::vec4::z, "w",
        &glm::vec4::w,

        "r", &glm::vec4::r, "g", &glm::vec4::g, "b", &glm::vec4::b, "a",
        &glm::vec4::a,

        "length", [](const glm::vec4& self) { return glm::length(self); },
        "normalize", [](glm::vec4& self) { self = glm::normalize(self); },
        "dot",
        [](const glm::vec4& self, const glm::vec4& other) {
            return glm::dot(self, other);
        },

        sol::meta_function::addition,
        [](const glm::vec4& a, const glm::vec4& b) { return a + b; },
        sol::meta_function::subtraction,
        [](const glm::vec4& a, const glm::vec4& b) { return a - b; },
        sol::meta_function::multiplication,
        [](const glm::vec4& v, float s) { return v * s; },

        sol::meta_function::to_string,
        [](const glm::vec4& self) {
            return "Vec4(" + std::to_string(self.x) + ", " +
                   std::to_string(self.y) + ", " + std::to_string(self.z) +
                   ", " + std::to_string(self.w) + ")";
        });
}

void ScriptingAPI::InitCore(sol::state& lua, EngineContext& ctx) {
    InitTime(lua, ctx);
    InitInput(lua, ctx);
    InitGLM(lua);
    InitComponents(lua);
}

}  // namespace PotatoEngine::Core::Scripting
