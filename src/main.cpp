#include "Settings.h"
#include "DisplayGLFW.h"
#include "SFEvent.h"
#include "Vec2.h"
#include "OutUtils.h"
#include "Maths.h"
#include "Timer.h"
#include "RenderGame.h"
#include "InputHandler.h"
#include "ObjLoader.h"
#include "GlobalMacros.h"

#include <iostream>

#define TEST 0

struct StartupOperations
{
    StartupOperations() 
    {
        //std::ios::sync_with_stdio(false); 
        output::print("Starting...");
        glfwInit();
    }
}   so;

struct ExitOperations
{
    ~ExitOperations() 
    {
        output::print("Press enter to exit...");
        std::cin.get();
        glfwTerminate();
    }
}   eo;


#if !TEST
#define DEBUGMODE

// Everything I need to know for a PC platform
namespace PC
{
    uint WIDTH = Settings::width();
    uint HEIGHT = Settings::height();
    const std::string TITLE = "OpenGL Playground";
    bool FULLSCREEN = Settings::fullscreen();
}


namespace Main_GB
{
    bool collision = false;
    bool show_fps = Settings::show_fps();
    int current_level = 2;
}


int main()
{
#ifdef PERFORMANCE_TESTS
    StartStopTimer timer{"Startup"};
    timer.start();
#endif
    DisplayGLFW display {PC::WIDTH, PC::HEIGHT, PC::TITLE, PC::FULLSCREEN ? FULLSCREEN : WINDOWED};
    InputHandler::init(&display.get_instance());
    InputHandler::update_collision(Main_GB::collision);

    RenderGame render_game {PC::WIDTH, PC::HEIGHT, Main_GB::current_level, InputHandler::m_camera};
    InputHandler::m_camera.current_level = render_game.m_levels[Main_GB::current_level];

    float delta_time;
    float current_time;
    float last_time {0};
    float sum {0};
    float fps {0};

    //Enabling OpenGL stuff
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glFrontFace(GL_CW);
    //glDepthFunc(GL_LESS);
    //glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_CULL_FACE);

    glCullFace(GL_FRONT);
#ifdef PERFORMANCE_TESTS
    timer.stop();
#endif

    while(!display.close_requested())
    {
        current_time = (float)glfwGetTime();
        delta_time = current_time - last_time;
        last_time = current_time;

        render_game.set_deltatime(delta_time);
        render_game.update_camera_pos(InputHandler::m_camera.position);

        InputHandler::update_dt(delta_time);

        if(display.is_active())
        {
            glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            InputHandler::handle_input();

            render_game.render(InputHandler::m_camera, InputHandler::m_draw_normals);

            render_game.render_transparent(Main_GB::show_fps, (int)(fps + 0.5f), {0, -10, 0});
            
            if(sum >= 0.1f)
            {
                fps = 1 / delta_time;
                sum = 0;
            }

            sum += delta_time;
        }

        glfwPollEvents();
        glfwSwapBuffers(&display.get_instance());
    }
}


#else

#include "Tests.h"

int main()
{
    ObjLoader loader;
    loader.load_obj_file(File{"Data/Models/cube.obj"});

    for(const auto& e : loader.data().vertices)
    {
        std::cout << e.x << ", " << e.y << ", " << e.z << ", " << e.w << "\n";
    }
}

#endif