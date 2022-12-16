#define STB_IMAGE_IMPLEMENTATION
#include </Users/nicole/Documents/2022-2/Grafica/glad/include/glad/glad.h>
#include </Users/nicole/Documents/2022-2/Grafica/glm-master/glm/glm.hpp>
#include <GLFW/glfw3.h>


#include </Users/nicole/Documents/2022-2/Grafica/glm-master/glm/gtc/matrix_transform.hpp>
#include </Users/nicole/Documents/2022-2/Grafica/glm-master/glm/gtc/type_ptr.hpp>


#include "/Users/nicole/Documents/2022-2/Grafica/CuboFinal/Prueba/shader_m.h"
#include </Users/nicole/Documents/2022-2/Grafica/CuboFinal/Prueba/stb_image.h>
#include </Users/nicole/Documents/2022-2/Grafica/CuboFinal/Prueba/camera.h>
#include </Users/nicole/Documents/2022-2/Grafica/CuboFinal/Prueba/Cube.h>


#include "/Users/nicole/Documents/2022-2/Grafica/CuboFinal/Prueba/Solver/solve.h"
#include "/Users/nicole/Documents/2022-2/Grafica/CuboFinal/Prueba/Solver/random.h"


#include <iostream>
#include <vector>

using namespace std;


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void RenderText(Shader &shader, std::string text, float x, float y, float scale, glm::vec3 color);

unsigned int VBO[26], VAO[26];
unsigned int VBO_c[26], VAO_c[26];
unsigned int VBO_f[26], VAO_f[26];
unsigned int VBO_ucsp[26], VAO_ucsp[26];
const unsigned int SCR_WIDTH = 1000;
const unsigned int SCR_HEIGHT = 800;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 5.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;


bool t= false;
bool r= false;
bool resp= false;
bool desordenar=false;
bool cor= false;
bool face= false;
bool ucsp_= false;
bool rb_= false;
bool spl_= false;


int solver_size=0;
bool solver_e=false;
int solver_size_it=0;

bool condR = false;
bool condL = false;
bool condU = false;
bool condD = false;
bool condF = false;
bool condB = false;


bool animation= false;
bool mov_ani=false;
void solvecube(vector<string> moves);
void randomMoves(vector<string>&cubo);



template<typename T>
T random(std::vector<T> const& v);

vector<char> movementsList;
float angle;
vector<string> cubo;
vector<string> lcR;
vector<string> moves;



glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 7.5f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

glm::vec3 translate_ = glm::vec3(0.f, 0.f, 0.0f);
glm::vec3 rotate_ =glm::vec3(0.0f, 0.0f, 0.0f);

float dist = 0.5;
float distMax = 0.5;
float distac = 0.0;
float distMin=0.0;
vector<bool> des={false, true,true,true, true,true, true,true,true, true,true, true,true,true, true,true,true, true,true,true, true,true, true,true,true, true,true, true,true,true, true,true};
int it=0;
int main()
{
    srand(time(NULL));
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    glEnable(GL_DEPTH_TEST);
    
    
    Shader lightingShader("/Users/nicole/Documents/2022-2/Grafica/CuboFinal/Prueba/light_casters.vs", "/Users/nicole/Documents/2022-2/Grafica/CuboFinal/Prueba/light_casters.fs");
    
    lightingShader.use();

    // COMPILE SHADER PROGRAM
    Shader ourShader("/Users/nicole/Documents/2022-2/Grafica/CuboFinal/Prueba/cube.vs", "/Users/nicole/Documents/2022-2/Grafica/CuboFinal/Prueba/cube.fs");
   
    glGenVertexArrays(26, VAO);
    glGenBuffers(26, VBO);
    Cube RubikCube;

    RubikCube.createLittleCubes();
    
    RubikCube.drawCube(&VBO[0], &VAO[0]);
    
    //FOR TEXTURE
    // load and create a texture 
    unsigned int texture1;

    // texture 1
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
    
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    string tt=to_string((1+rand()%27));
    string txts= "/Users/nicole/Documents/2022-2/Grafica/CuboFinal/Prueba/Textures/"+tt+".jpg";
    //cout << "texture " << tt<< std::endl;
    const char * txt = txts.c_str();
    unsigned char* data = stbi_load(txt, &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    
    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    ourShader.use();
    ourShader.setInt("texture1", 0);
    
    
   
    glGenVertexArrays(26, VAO_c);
    glGenBuffers(26, VBO_c);
    Cube RubikCube_c;

    RubikCube_c.createLittleCubes();
    
    RubikCube_c.drawCube(&VBO_c[0], &VAO_c[0]);
    
    glGenVertexArrays(26, VAO_f);
    glGenBuffers(26, VBO_f);
    Cube RubikCube_f;

    RubikCube_f.createLittleCubes();
    
    RubikCube_f.drawCube(&VBO_f[0], &VAO_f[0]);
    
    glGenVertexArrays(26, VAO_ucsp);
    glGenBuffers(26, VBO_ucsp);
    Cube RubikCube_ucsp;

    RubikCube_ucsp.createLittleCubes();
    
    RubikCube_ucsp.drawCube(&VBO_c[0], &VAO_c[0]);
    
    
    
    // pass projection matrix to shader (as projection matrix rarely changes there's no need to do this per frame)
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    ourShader.setMat4("projection", projection);
    
    //delta corps priest 1
    cout<<endl;
    cout << "    ▄████████ ███    █▄  ▀█████████▄   ▄█     ▄█   ▄█▄       ▄████████ ███    █▄  ▀█████████▄     ▄████████ " << endl;
    cout << "    ███    ███ ███    ███   ███    ███ ███    ███ ▄███▀      ███    ███ ███    ███   ███    ███   ███    ███ " << endl;
    cout << "    ███    ███ ███    ███   ███    ███ ███▌   ███▐██▀        ███    █▀  ███    ███   ███    ███   ███    █▀ " << endl;
    cout << "   ▄███▄▄▄▄██▀ ███    ███  ▄███▄▄▄██▀  ███▌  ▄█████▀         ███        ███    ███  ▄███▄▄▄██▀   ▄███▄▄▄ " << endl;
    cout << "  ▀▀███▀▀▀▀▀   ███    ███ ▀▀███▀▀▀██▄  ███▌ ▀▀█████▄         ███        ███    ███ ▀▀███▀▀▀██▄  ▀▀███▀▀▀ " << endl;
    cout << "  ▀███████████ ███    ███   ███    ██▄ ███    ███▐██▄        ███    █▄  ███    ███   ███    ██▄   ███    █▄ " << endl;
    cout << "    ███    ███ ███    ███   ███    ███ ███    ███ ▀███▄      ███    ███ ███    ███   ███    ███   ███    ███ " << endl;
    cout << "    ███    ███ ████████▀  ▄█████████▀  █▀     ███   ▀█▀      ████████▀  ████████▀  ▄█████████▀    ██████████ " << endl;
    cout << "    ███    ███                                ▀   " << endl;
                                                                                                                    
    cout<<endl;
    cout<<endl;
    cout<<endl;
    //small
    cout << " _  _  ___  ___  ___   _     ___   ___   _   _  ___    _    _  _  ___    ____ ___  ___    _    _     _     ___   ___" << endl;
    cout << "| \\| ||_ _|/ __|/ _ \\ | |   | __| |   \\ | | | || _ \\  /_\\  | \\| ||   \\  |_  /| __|| _ )  /_\\  | |   | |   / _ \\ / __| " << endl;
    cout << "| .` | | || (__| (_) || |__ | _|  | |) || |_| ||   / / _ \\ | .` || |) |  / / | _| | _ \\ / _ \\ | |__ | |__| (_) |\\__ \\ " << endl;
    cout << "|_|\\_||___|\\___|\\___/ |____||___| |___/  \\___/ |_|_\\/_/ \\_\\|_|\\_||___/  /___||___||___//_/ \\_\\|____||____|\\___/ |___/ " << endl;
    cout<<endl;
    cout<<endl;
    cout << "_   _  _  _ " << endl;
    cout << " ) / \\  )  ) " << endl;
    cout << "/_ \\_/ /_ /_ " << endl;
    cout<<endl;
    //stick letters
    cout << "         ______ __             __          __            ___   _____     __   __    ___ " << endl;
    cout << "______    ||__ /  `|    /\\    |__).   |\\/|/  \\\\  /||\\/|||__ |\\ ||/  \\   |__)|/ _`|__||    ______" << endl;
    cout << "          ||___\\__,|___/~~\\   |  \\.   |  |\\__/ \\/ ||  |||___| \\||\\__/   |  \\|\\__>|  || " << endl;
    cout << "         ______ __                         __            ___   _____         ___ ______ " << endl;
    cout << "______    ||__ /  `|    /\\    |   .   |\\/|/  \\\\  /||\\/|||__ |\\ ||/  \\   |   |__ |__  |    ______" << endl;
    cout << "          ||___\\__,|___/~~\\   |___.   |  |\\__/ \\/ ||  |||___| \\||\\__/   |___|___|    |" << endl;
    cout << "         ______ __                         __            ___   _____         __" << endl;
    cout << "______    ||__ /  `|    /\\    |  |.   |\\/|/  \\\\  /||\\/|||__ |\\ ||/  \\   |  ||__)   ______" << endl;
    cout << "          ||___\\__,|___/~~\\   \\__/.   |  |\\__/ \\/ ||  |||___| \\||\\__/   \\__/|" << endl;
    cout << "         ______ __             __          __            ___   _____     __  __" << endl;
    cout << "______    ||__ /  `|    /\\    |  \\.   |\\/|/  \\\\  /||\\/|||__ |\\ ||/  \\   |  \\/  \\|  ||\\ |   ______" << endl;
    cout << "          ||___\\__,|___/~~\\   |__/.   |  |\\__/ \\/ ||  |||___| \\||\\__/   |__/\\__/|/\\|| \\|" << endl;
    cout << "         ______ __             __          __            ___   _____     __      __              __  __" << endl;
    cout << "______    ||__ /  `|    /\\    |__).   |\\/|/  \\\\  /||\\/|||__ |\\ ||/  \\   |__) /\\ /  `|__/|  | /\\ |__)|  \\   ______" << endl;
    cout << "          ||___\\__,|___/~~\\   |__).   |  |\\__/ \\/ ||  |||___| \\||\\__/   |__)/~~\\\\__,|  \\|/\\|/~~\\|  \\|__/" << endl;
    cout << "         ______ __             ___         __            ___   _____     _____  __          __  __" << endl;
    cout << "______    ||__ /  `|    /\\    |__ .   |\\/|/  \\\\  /||\\/|||__ |\\ ||/  \\   |__/  \\|__)|  | /\\ |__)|  \\   ______" << endl;
    cout << "          ||___\\__,|___/~~\\   |   .   |  |\\__/ \\/ ||  |||___| \\||\\__/   |  \\__/|  \\|/\\|/~~\\|  \\|__/" << endl;
    cout << "         ______ __             __      __  ___ __      __          __         ___        __      __  __             ___   _____  __           ___   ______" << endl;
    cout << "______    ||__ /  `|    /\\    |__).   |  \\|__ /__` /\\ |__)|\\/| /\\ |__) /\\    |__ |      /  `|  ||__)/  \\    /\\ |   |__  /\\ |/  \\|__)| /\\ |\\/||__ |\\ |||__    ______" << endl;
    cout << "          ||___\\__,|___/~~\\   |   .   |__/|___.__//~~\\|  \\|  |/~~\\|  \\/~~\\   |___|___   \\__,\\__/|__)\\__/   /~~\\|___|___/~~\\|\\__/|  \\|/~~\\|  ||___| \\|||___ " << endl;
    cout << "         ______ __             __      __  __  __  ___         __         ___        __      __  __" << endl;
    cout << "______    ||__ /  `|    /\\    /__`.   /  \\|__)|  \\|__ |\\ | /\\ |__) /\\    |__ |      /  `|  ||__)/  \\   ______" << endl;
    cout << "          ||___\\__,|___/~~\\   .__/.   \\__/|  \\|__/|___| \\|/~~\\|  \\/~~\\   |___|___   \\__,\\__/|__)\\__/" << endl;
    cout << "         ______ __                                      __   __         __  ___    __  ___ __  __   __      __   __" << endl;
    cout << "______    ||__ /  `|    /\\    |  |.    /\\ |\\ |||\\/| /\\ /  `|/  \\|\\ |   |  \\|__    |__)|__ /__`|__)||__) /\\ /  `|/  \\|\\ |   ______" << endl;
    cout << "          ||___\\__,|___/~~\\   |/\\|.   /~~\\| \\|||  |/~~\\\\__,|\\__/| \\|   |__/|___   |  \\|___.__/|   ||  \\/~~\\\\__,|\\__/| \\|" << endl;
                                                                                                                                                                        
    cout<<endl;
    cout<<endl;
    
    int cont =0;
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        // input
        processInput(window);   //cambiar con kewWordCallBack

        // render
        //glClearColor((1.0f/255)*255, (1.0f/255)*255, (1.0f/255)*255, 1.0f);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        //glClearColor(0, 0, 0, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        
        glm::mat4 transform = glm::mat4(1.0f);
        
        if(spl_==true){
            // be sure to activate shader when setting uniforms/drawing objects
            lightingShader.use();
            lightingShader.setVec3("light.position", camera.Position);
            lightingShader.setVec3("light.direction", camera.Front);
            lightingShader.setFloat("light.cutOff", glm::cos(glm::radians(5.5f)));
            lightingShader.setVec3("viewPos", camera.Position);

            // light properties
            lightingShader.setVec3("light.ambient", 0.1f, 0.1f, 0.1f);
            // we configure the diffuse intensity slightly higher; the right lighting conditions differ with each lighting method and environment.
            // each environment and lighting type requires some tweaking to get the best out of your environment.
            lightingShader.setVec3("light.diffuse", 0.8f, 0.8f, 0.8f);
            lightingShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
            lightingShader.setFloat("light.constant", 1.0f);
            lightingShader.setFloat("light.linear", 0.09f);
            lightingShader.setFloat("light.quadratic", 0.032f);

            // material properties
            lightingShader.setFloat("material.shininess", 100.0f);
            
            // world transformation
            glm::mat4 model = glm::mat4(1.0f);
            lightingShader.setMat4("model", model);
        }
            
            
        if(t==true){
            
            transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
            transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
            
        }
        transform = glm::translate(transform , translate_);
        if(r == true){
            transform = glm::rotate(transform, (float)glfwGetTime(), rotate_);
        }
        if(desordenar == true){
            RubikCube_c.desordenar();
            RubikCube_f.desordenar();
            RubikCube_ucsp.desordenar();
            RubikCube.desordenar();
            animation=true;
            desordenar=!desordenar;
        }
        
        if(cor == true){
            bool a= RubikCube_c.corazon();
            if(a== true ) cor=!cor;
           
        }
        if(face == true){
            bool a= RubikCube_f.carita();
            if(a== true ) face=!face;
        }
        if(ucsp_ == true){
            bool a= RubikCube_ucsp.ucsp();
            if(a== true ) ucsp_=!ucsp_;
        }
        if(rb_ == true){
            bool a= RubikCube.ordenar();
            if(a== true ) rb_=!rb_;
        }
        
        if(mov_ani==true){
            RubikCube_c.ani_corazon();
            RubikCube_f.ani_carita();
            RubikCube_ucsp.ani_ucsp();
            RubikCube.ani_cube();
            cont++;
            if(cont==2500) {mov_ani=!mov_ani;}
        }

        if(animation){
            RubikCube_c.drawCube(&VBO_c[0], &VAO_c[0]);
            RubikCube_f.drawCube(&VBO_f[0], &VAO_f[0]);
            RubikCube_ucsp.drawCube(&VBO_ucsp[0], &VAO_ucsp[0]);
        }
        
        if(resp == true){
            if(des[it%des.size()]==false){
                RubikCube.respiracion(dist);
                if(dist == distMax) dist=-0.1;
                if(distac == -0.5 ) dist=0.5;
                if(dist == distMin ) dist= 0.5;
                distac+=dist;
                //resp=!resp;
            }
            it++;
            if(it == 555){
                resp=!resp;
                it=0;
                desordenar=true;
            }
        }
        
        
        unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
        // activate shader
        ourShader.use();

        // camera/view transformation
        glm::mat4 view = glm::mat4(1.0f);
        view = glm::lookAt(cameraPos, cameraFront, cameraUp);
        ourShader.setMat4("view", view);

        // render boxes
        for (unsigned int i = 0; i < 26; i++)
        {
            glBindVertexArray(VAO[i]);
            glm::mat4 model = glm::mat4(1.0f);
            ourShader.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        if(animation){
            for (unsigned int i = 0; i < 26; i++)
            {
                glBindVertexArray(VAO_c[i]);
                glm::mat4 model = glm::mat4(1.0f);
                ourShader.setMat4("model", model);
                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
            
            
            for (unsigned int i = 0; i < 26; i++)
            {
                glBindVertexArray(VAO_f[i]);
                glm::mat4 model = glm::mat4(1.0f);
                ourShader.setMat4("model", model);
                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
            
            for (unsigned int i = 0; i < 26; i++)
            {
                glBindVertexArray(VAO_ucsp[i]);
                glm::mat4 model = glm::mat4(1.0f);
                ourShader.setMat4("model", model);
                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
            
        }
        if (!movementsList.empty()) {
            //read actual movement
            
            
            if (movementsList[0] == 'R') {
                condR = true;
                condL = condF = condB = condU = condD = false;
            }
            if (movementsList[0] == 'L') {
                condL = true;
                condR = condF = condB = condU = condD = false;
            }
            if (movementsList[0] == 'F') {
                condF = true;
                condL = condR = condB = condU = condD = false;
            }
            if (movementsList[0] == 'B') {
                condB = true;
                condL = condF = condR = condU = condD = false;
            }
            if (movementsList[0] == 'U') {
                condU = true;
                condL = condF = condB = condR = condD = false;
            }
            if (movementsList[0] == 'D') {
                condD = true;
                condL = condF = condB = condU = condR = false;
            }
            
            if (condR) {
                if (angle < 90) {
                    RubikCube.moveR(-1);
                    angle++;
                }
                else {
                    condR = false;
                    if(solver_e==true){
                        solver_size_it--;
                        cout<<"Ejecutando Solver "<<100 - ((solver_size_it* 100)/solver_size)<<" %  --> "<< movementsList[0]<<endl;
                        
                    }
                    else{
                        cout<<"Ejecutando --> "<< movementsList[0]<<endl;
                    }
                    
                    
                    movementsList.erase(movementsList.begin());
                    angle = 0;
                    
                    bool searchR = false;
                    for (unsigned int indexCube = 0; indexCube < 26; indexCube++)
                    {
                        
                        for (int i = 0; i < 3; i++) {
                            if (RubikCube.littleCubes[indexCube].camadas[i] == 'R') {
                                searchR = true;
                                break;
                            }
                        }
                        if (searchR) {
                            
                            bool searchU = false;
                            for (int j = 0; j < 3; j++) {
                                if (RubikCube.littleCubes[indexCube].camadas[j] == 'U') {
                                    searchU = true;
                                    break;
                                }
                            }
                            if (searchU) {
                                bool searchF = false;
                                bool searchS = false;
                                bool searchB = false;
                                
                                for (int k = 0; k < 3; k++) {
                                    if (RubikCube.littleCubes[indexCube].camadas[k] == 'F')
                                        searchF = true;
                                    if (RubikCube.littleCubes[indexCube].camadas[k] == 'S')
                                        searchS = true;
                                    if (RubikCube.littleCubes[indexCube].camadas[k] == 'B')
                                        searchB = true;
                                }
                                if (searchF) {
                                    vector<char> camadaTemp = { 'R', 'B', 'U' };
                                    RubikCube.littleCubes[indexCube].camadas = camadaTemp;
                                    
                                }
                                if (searchS) {
                                    vector<char> camadaTemp = { 'R', 'B', 'E' };
                                    RubikCube.littleCubes[indexCube].camadas = camadaTemp;
                                    
                                }
                                if (searchB) {
                                    vector<char> camadaTemp = { 'R', 'B', 'D' };
                                    RubikCube.littleCubes[indexCube].camadas = camadaTemp;
                                    
                                }
                                searchU = false;
                            }
                            else {
                                
                                bool searchE = false;
                                for (int j = 0; j < 3; j++) {
                                    if (RubikCube.littleCubes[indexCube].camadas[j] == 'E') {
                                        searchE = true;
                                        break;
                                    }
                                }
                                if (searchE) {
                                    bool searchF = false;
                                    bool searchS = false;
                                    bool searchB = false;
                                    
                                    for (int k = 0; k < 3; k++) {
                                        if (RubikCube.littleCubes[indexCube].camadas[k] == 'F')
                                            searchF = true;
                                        if (RubikCube.littleCubes[indexCube].camadas[k] == 'S')
                                            searchS = true;
                                        if (RubikCube.littleCubes[indexCube].camadas[k] == 'B')
                                            searchB = true;
                                    }
                                    if (searchF) {
                                        vector<char> camadaTemp = { 'R', 'S', 'U' };
                                        RubikCube.littleCubes[indexCube].camadas = camadaTemp;
                                       
                                    }
                                    if (searchS) {
                                        vector<char> camadaTemp = { 'R', 'S', 'E' };
                                        RubikCube.littleCubes[indexCube].camadas = camadaTemp;
                                        
                                    }
                                    if (searchB) {
                                        vector<char> camadaTemp = { 'R', 'S', 'D' };
                                        RubikCube.littleCubes[indexCube].camadas = camadaTemp;
                                        
                                    }
                                    searchE = false;
                                }
                                else {
                                    
                                    bool searchD = false;
                                    for (int j = 0; j < 3; j++) {
                                        if (RubikCube.littleCubes[indexCube].camadas[j] == 'D') {
                                            searchD = true;
                                            break;
                                        }
                                    }
                                    if (searchD) {
                                        bool searchF = false;
                                        bool searchS = false;
                                        bool searchB = false;
                                        
                                        for (int k = 0; k < 3; k++) {
                                            if (RubikCube.littleCubes[indexCube].camadas[k] == 'F')
                                                searchF = true;
                                            if (RubikCube.littleCubes[indexCube].camadas[k] == 'S')
                                                searchS = true;
                                            if (RubikCube.littleCubes[indexCube].camadas[k] == 'B')
                                                searchB = true;
                                        }
                                        if (searchF) {
                                            vector<char> camadaTemp = { 'R', 'F', 'U' };
                                            RubikCube.littleCubes[indexCube].camadas = camadaTemp;
                                            
                                        }
                                        if (searchS) {
                                            vector<char> camadaTemp = { 'R', 'F', 'E' };
                                            RubikCube.littleCubes[indexCube].camadas = camadaTemp;
                                            
                                        }
                                        if (searchB) {
                                            vector<char> camadaTemp = { 'R', 'F', 'D' };
                                            RubikCube.littleCubes[indexCube].camadas = camadaTemp;
                                           
                                        }
                                        searchD = false;
                                    }
                                }
                            }
                            searchR = false;
                        }
                    }
                }
            }
           
            if (condL) {
                if (angle < 90) {
                    RubikCube.moveL(1);
                    angle++;
                }
                else {
                    condL = false;
                    if(solver_e==true){
                        solver_size_it--;
                        cout<<"Ejecutando Solver "<<100 - ((solver_size_it* 100)/solver_size)<<" %  --> "<< movementsList[0]<<endl;
                        
                        
                    }
                    else{
                        cout<<"Ejecutando --> "<< movementsList[0]<<endl;
                    }
                    movementsList.erase(movementsList.begin());
                    angle = 0;
                    
                    bool searchL = false;
                    for (unsigned int indexCube = 0; indexCube < 26; indexCube++)
                    {
                       
                        for (int i = 0; i < 3; i++) {
                            if (RubikCube.littleCubes[indexCube].camadas[i] == 'L') {
                                searchL = true;
                                break;
                            }
                        }
                        if (searchL) {
                            
                            bool searchU = false;
                            for (int j = 0; j < 3; j++) {
                                if (RubikCube.littleCubes[indexCube].camadas[j] == 'U') {
                                    searchU = true;
                                    break;
                                }
                            }
                            if (searchU) {
                                bool searchF = false;
                                bool searchS = false;
                                bool searchB = false;
                                
                                for (int k = 0; k < 3; k++) {
                                    if (RubikCube.littleCubes[indexCube].camadas[k] == 'F')
                                        searchF = true;
                                    if (RubikCube.littleCubes[indexCube].camadas[k] == 'S')
                                        searchS = true;
                                    if (RubikCube.littleCubes[indexCube].camadas[k] == 'B')
                                        searchB = true;
                                }
                                if (searchF) {
                                    vector<char> camadaTemp = { 'L', 'F', 'D' };
                                    RubikCube.littleCubes[indexCube].camadas = camadaTemp;
                                }
                                if (searchS) {
                                    vector<char> camadaTemp = { 'L', 'F', 'E' };
                                    RubikCube.littleCubes[indexCube].camadas = camadaTemp;
                                }
                                if (searchB) {
                                    vector<char> camadaTemp = { 'L', 'F', 'U' };
                                    RubikCube.littleCubes[indexCube].camadas = camadaTemp;
                                }
                                searchU = false;
                            }
                            else {
                                
                                bool searchE = false;
                                for (int j = 0; j < 3; j++) {
                                    if (RubikCube.littleCubes[indexCube].camadas[j] == 'E') {
                                        searchE = true;
                                        break;
                                    }
                                }
                                if (searchE) {
                                    bool searchF = false;
                                    bool searchS = false;
                                    bool searchB = false;
                                    
                                    for (int k = 0; k < 3; k++) {
                                        if (RubikCube.littleCubes[indexCube].camadas[k] == 'F')
                                            searchF = true;
                                        if (RubikCube.littleCubes[indexCube].camadas[k] == 'S')
                                            searchS = true;
                                        if (RubikCube.littleCubes[indexCube].camadas[k] == 'B')
                                            searchB = true;
                                    }
                                    if (searchF) {
                                        vector<char> camadaTemp = { 'L', 'S', 'D' };
                                        RubikCube.littleCubes[indexCube].camadas = camadaTemp;
                                    }
                                    if (searchS) {
                                        vector<char> camadaTemp = { 'L', 'S', 'E' };
                                        RubikCube.littleCubes[indexCube].camadas = camadaTemp;
                                    }
                                    if (searchB) {
                                        vector<char> camadaTemp = { 'L', 'S', 'U' };
                                        RubikCube.littleCubes[indexCube].camadas = camadaTemp;
                                    }
                                    searchE = false;
                                }
                                else {
                                    
                                    bool searchD = false;
                                    for (int j = 0; j < 3; j++) {
                                        if (RubikCube.littleCubes[indexCube].camadas[j] == 'D') {
                                            searchD = true;
                                            break;
                                        }
                                    }
                                    if (searchD) {
                                        bool searchF = false;
                                        bool searchS = false;
                                        bool searchB = false;
                                        
                                        for (int k = 0; k < 3; k++) {
                                            if (RubikCube.littleCubes[indexCube].camadas[k] == 'F')
                                                searchF = true;
                                            if (RubikCube.littleCubes[indexCube].camadas[k] == 'S')
                                                searchS = true;
                                            if (RubikCube.littleCubes[indexCube].camadas[k] == 'B')
                                                searchB = true;
                                        }
                                        if (searchF) {
                                            vector<char> camadaTemp = { 'L', 'B', 'D' };
                                            RubikCube.littleCubes[indexCube].camadas = camadaTemp;
                                        }
                                        if (searchS) {
                                            vector<char> camadaTemp = { 'L', 'B', 'E' };
                                            RubikCube.littleCubes[indexCube].camadas = camadaTemp;
                                        }
                                        if (searchB) {
                                            vector<char> camadaTemp = { 'L', 'B', 'U' };
                                            RubikCube.littleCubes[indexCube].camadas = camadaTemp;
                                        }
                                        searchD = false;
                                    }
                                }
                            }
                            searchL = false;
                        }
                    }
                }
            }
            
            if (condU) {
                if (angle < 90) {
                    RubikCube.moveU(-1);
                    angle++;
                }
                else {
                    condU = false;
                    if(solver_e==true){
                        solver_size_it--;
                        cout<<"Ejecutando Solver "<<100 - ((solver_size_it* 100)/solver_size)<<" %  --> "<< movementsList[0]<<endl;
                        
                        
                    }
                    else{
                        cout<<"Ejecutando --> "<< movementsList[0]<<endl;
                    }
                    movementsList.erase(movementsList.begin());
                    angle = 0;
                    //update groups
                    /*
                    * URF -> UFL
                    * URS -> UFM
                    * URB -> UFR
                    * UMF -> USL
                    * UMS -> USM
                    * UMB -> USR
                    * ULF -> UBL
                    * ULS -> UBM
                    * ULB -> UBR
                    */
                    bool searchU = false;
                    for (unsigned int indexCube = 0; indexCube < 26; indexCube++)
                    {
                        //U
                        for (int i = 0; i < 3; i++) {
                            if (RubikCube.littleCubes[indexCube].camadas[i] == 'U') {
                                searchU = true;
                                break;
                            }
                        }
                        if (searchU) {
                            //R
                            bool searchR = false;
                            for (int j = 0; j < 3; j++) {
                                if (RubikCube.littleCubes[indexCube].camadas[j] == 'R') {
                                    searchR = true;
                                    break;
                                }
                            }
                            if (searchR) {
                                bool searchF = false;
                                bool searchS = false;
                                bool searchB = false;
                                //FSB
                                for (int k = 0; k < 3; k++) {
                                    if (RubikCube.littleCubes[indexCube].camadas[k] == 'F')
                                        searchF = true;
                                    if (RubikCube.littleCubes[indexCube].camadas[k] == 'S')
                                        searchS = true;
                                    if (RubikCube.littleCubes[indexCube].camadas[k] == 'B')
                                        searchB = true;
                                }
                                if (searchF) {
                                    vector<char> camadaTemp = { 'U', 'F', 'L' };
                                    RubikCube.littleCubes[indexCube].camadas = camadaTemp;
                                }
                                if (searchS) {
                                    vector<char> camadaTemp = { 'U', 'F', 'M' };
                                    RubikCube.littleCubes[indexCube].camadas = camadaTemp;
                                }
                                if (searchB) {
                                    vector<char> camadaTemp = { 'U', 'F', 'R' };
                                    RubikCube.littleCubes[indexCube].camadas = camadaTemp;
                                }
                                searchR = false;
                            }
                            else {
                                //M
                                bool searchM = false;
                                for (int j = 0; j < 3; j++) {
                                    if (RubikCube.littleCubes[indexCube].camadas[j] == 'M') {
                                        searchM = true;
                                        break;
                                    }
                                }
                                if (searchM) {
                                    bool searchF = false;
                                    bool searchS = false;
                                    bool searchB = false;
                                    //FSB
                                    for (int k = 0; k < 3; k++) {
                                        if (RubikCube.littleCubes[indexCube].camadas[k] == 'F')
                                            searchF = true;
                                        if (RubikCube.littleCubes[indexCube].camadas[k] == 'S')
                                            searchS = true;
                                        if (RubikCube.littleCubes[indexCube].camadas[k] == 'B')
                                            searchB = true;
                                    }
                                    if (searchF) {
                                        vector<char> camadaTemp = { 'U', 'S', 'L' };
                                        RubikCube.littleCubes[indexCube].camadas = camadaTemp;
                                    }
                                    if (searchS) {
                                        vector<char> camadaTemp = { 'U', 'S', 'M' };
                                        RubikCube.littleCubes[indexCube].camadas = camadaTemp;
                                    }
                                    if (searchB) {
                                        vector<char> camadaTemp = { 'U', 'S', 'R' };
                                        RubikCube.littleCubes[indexCube].camadas = camadaTemp;
                                    }
                                    searchM = false;
                                }
                                else {
                                    //L
                                    bool searchL = false;
                                    for (int j = 0; j < 3; j++) {
                                        if (RubikCube.littleCubes[indexCube].camadas[j] == 'L') {
                                            searchL = true;
                                            break;
                                        }
                                    }
                                    if (searchL) {
                                        bool searchF = false;
                                        bool searchS = false;
                                        bool searchB = false;
                                        //FSB
                                        for (int k = 0; k < 3; k++) {
                                            if (RubikCube.littleCubes[indexCube].camadas[k] == 'F')
                                                searchF = true;
                                            if (RubikCube.littleCubes[indexCube].camadas[k] == 'S')
                                                searchS = true;
                                            if (RubikCube.littleCubes[indexCube].camadas[k] == 'B')
                                                searchB = true;
                                        }
                                        if (searchF) {
                                            vector<char> camadaTemp = { 'U', 'B', 'L' };
                                            RubikCube.littleCubes[indexCube].camadas = camadaTemp;
                                        }
                                        if (searchS) {
                                            vector<char> camadaTemp = { 'U', 'B', 'M' };
                                            RubikCube.littleCubes[indexCube].camadas = camadaTemp;
                                        }
                                        if (searchB) {
                                            vector<char> camadaTemp = { 'U', 'B', 'R' };
                                            RubikCube.littleCubes[indexCube].camadas = camadaTemp;
                                        }
                                        searchL = false;
                                    }
                                }
                            }
                            searchU = false;
                        }
                    }

                }
            }
            
            if (condD) {
                if (angle < 90) {
                    RubikCube.moveD(1);
                    angle++;
                }
                else {
                    condD = false;
                    if(solver_e==true){
                        solver_size_it--;
                        cout<<"Ejecutando Solver "<<100 - ((solver_size_it* 100)/solver_size)<<" %  --> "<< movementsList[0]<<endl;
                        
                    }
                    else{
                        cout<<"Ejecutando --> "<< movementsList[0]<<endl;
                    }
                    movementsList.erase(movementsList.begin());
                    angle = 0;
                    //update groups
                    /*
                    * DRF -> DBR
                    * DRS -> DBM
                    * DRB -> DBL
                    * DMF -> DSR
                    * DMS -> DSM
                    * DMB -> DSL
                    * DLF -> DFR
                    * DLS -> DFM
                    * DLB -> DFL
                    */
                    bool searchD = false;
                    for (unsigned int indexCube = 0; indexCube < 26; indexCube++)
                    {
                        //D
                        for (int i = 0; i < 3; i++) {
                            if (RubikCube.littleCubes[indexCube].camadas[i] == 'D') {
                                searchD = true;
                                break;
                            }
                        }
                        if (searchD) {
                            //R
                            bool searchR = false;
                            for (int j = 0; j < 3; j++) {
                                if (RubikCube.littleCubes[indexCube].camadas[j] == 'R') {
                                    searchR = true;
                                    break;
                                }
                            }
                            if (searchR) {
                                bool searchF = false;
                                bool searchS = false;
                                bool searchB = false;
                                //FSB
                                for (int k = 0; k < 3; k++) {
                                    if (RubikCube.littleCubes[indexCube].camadas[k] == 'F')
                                        searchF = true;
                                    if (RubikCube.littleCubes[indexCube].camadas[k] == 'S')
                                        searchS = true;
                                    if (RubikCube.littleCubes[indexCube].camadas[k] == 'B')
                                        searchB = true;
                                }
                                if (searchF) {
                                    vector<char> camadaTemp = { 'D', 'B', 'R' };
                                    RubikCube.littleCubes[indexCube].camadas = camadaTemp;
                                }
                                if (searchS) {
                                    vector<char> camadaTemp = { 'D', 'B', 'M' };
                                    RubikCube.littleCubes[indexCube].camadas = camadaTemp;
                                }
                                if (searchB) {
                                    vector<char> camadaTemp = { 'D', 'B', 'L' };
                                    RubikCube.littleCubes[indexCube].camadas = camadaTemp;
                                }
                                searchR = false;
                            }
                            else {
                                //M
                                bool searchM = false;
                                for (int j = 0; j < 3; j++) {
                                    if (RubikCube.littleCubes[indexCube].camadas[j] == 'M') {
                                        searchM = true;
                                        break;
                                    }
                                }
                                if (searchM) {
                                    bool searchF = false;
                                    bool searchS = false;
                                    bool searchB = false;
                                    //FSB
                                    for (int k = 0; k < 3; k++) {
                                        if (RubikCube.littleCubes[indexCube].camadas[k] == 'F')
                                            searchF = true;
                                        if (RubikCube.littleCubes[indexCube].camadas[k] == 'S')
                                            searchS = true;
                                        if (RubikCube.littleCubes[indexCube].camadas[k] == 'B')
                                            searchB = true;
                                    }
                                    if (searchF) {
                                        vector<char> camadaTemp = { 'D', 'S', 'R' };
                                        RubikCube.littleCubes[indexCube].camadas = camadaTemp;
                                    }
                                    if (searchS) {
                                        vector<char> camadaTemp = { 'D', 'S', 'M' };
                                        RubikCube.littleCubes[indexCube].camadas = camadaTemp;
                                    }
                                    if (searchB) {
                                        vector<char> camadaTemp = { 'D', 'S', 'L' };
                                        RubikCube.littleCubes[indexCube].camadas = camadaTemp;
                                    }
                                    searchM = false;
                                }
                                else {
                                    //L
                                    bool searchL = false;
                                    for (int j = 0; j < 3; j++) {
                                        if (RubikCube.littleCubes[indexCube].camadas[j] == 'L') {
                                            searchL = true;
                                            break;
                                        }
                                    }
                                    if (searchL) {
                                        bool searchF = false;
                                        bool searchS = false;
                                        bool searchB = false;
                                        //FSB
                                        for (int k = 0; k < 3; k++) {
                                            if (RubikCube.littleCubes[indexCube].camadas[k] == 'F')
                                                searchF = true;
                                            if (RubikCube.littleCubes[indexCube].camadas[k] == 'S')
                                                searchS = true;
                                            if (RubikCube.littleCubes[indexCube].camadas[k] == 'B')
                                                searchB = true;
                                        }
                                        if (searchF) {
                                            vector<char> camadaTemp = { 'D', 'F', 'R' };
                                            RubikCube.littleCubes[indexCube].camadas = camadaTemp;
                                        }
                                        if (searchS) {
                                            vector<char> camadaTemp = { 'D', 'F', 'M' };
                                            RubikCube.littleCubes[indexCube].camadas = camadaTemp;
                                        }
                                        if (searchB) {
                                            vector<char> camadaTemp = { 'D', 'F', 'L' };
                                            RubikCube.littleCubes[indexCube].camadas = camadaTemp;
                                        }
                                        searchL = false;
                                    }
                                }
                            }
                            searchD = false;
                        }
                    }

                }
            }
            
            if (condF) {
                if (angle < 90) {
                    RubikCube.moveF(1);
                    angle++;
                }
                else {
                    condF = false;
                    if(solver_e==true){
                        solver_size_it--;
                        cout<<"Ejecutando Solver "<<100 - ((solver_size_it* 100)/solver_size)<<" %  --> "<< movementsList[0]<<endl;
                        
                        
                    }
                    else{
                        cout<<"Ejecutando --> "<< movementsList[0]<<endl;
                    }
                    movementsList.erase(movementsList.begin());
                    angle = 0;
                    //update groups
                    /*
                    * FRU -> FDR
                    * FRE -> FDM
                    * FRD -> FDL
                    * FMU -> FER
                    * FME -> FEM
                    * FMD -> FEL
                    * FLU -> FUR
                    * FLE -> FUM
                    * FLD -> FUL
                    */
                    bool searchF = false;
                    for (unsigned int indexCube = 0; indexCube < 26; indexCube++)
                    {
                        //F
                        for (int i = 0; i < 3; i++) {
                            if (RubikCube.littleCubes[indexCube].camadas[i] == 'F') {
                                searchF = true;
                                break;
                            }
                        }
                        if (searchF) {
                            //R
                            bool searchR = false;
                            for (int j = 0; j < 3; j++) {
                                if (RubikCube.littleCubes[indexCube].camadas[j] == 'R') {
                                    searchR = true;
                                    break;
                                }
                            }
                            if (searchR) {
                                bool searchU = false;
                                bool searchE = false;
                                bool searchD = false;
                                //UED
                                for (int k = 0; k < 3; k++) {
                                    if (RubikCube.littleCubes[indexCube].camadas[k] == 'U')
                                        searchU = true;
                                    if (RubikCube.littleCubes[indexCube].camadas[k] == 'E')
                                        searchE = true;
                                    if (RubikCube.littleCubes[indexCube].camadas[k] == 'D')
                                        searchD = true;
                                }
                                if (searchU) {
                                    vector<char> camadaTemp = { 'F', 'D', 'R' };
                                    RubikCube.littleCubes[indexCube].camadas = camadaTemp;
                                }
                                if (searchE) {
                                    vector<char> camadaTemp = { 'F', 'D', 'M' };
                                    RubikCube.littleCubes[indexCube].camadas = camadaTemp;
                                }
                                if (searchD) {
                                    vector<char> camadaTemp = { 'F', 'D', 'L' };
                                    RubikCube.littleCubes[indexCube].camadas = camadaTemp;
                                }
                                searchR = false;
                            }
                            else {
                                //M
                                bool searchM = false;
                                for (int j = 0; j < 3; j++) {
                                    if (RubikCube.littleCubes[indexCube].camadas[j] == 'M') {
                                        searchM = true;
                                        break;
                                    }
                                }
                                if (searchM) {
                                    bool searchU = false;
                                    bool searchE = false;
                                    bool searchD = false;
                                    //UED
                                    for (int k = 0; k < 3; k++) {
                                        if (RubikCube.littleCubes[indexCube].camadas[k] == 'U')
                                            searchU = true;
                                        if (RubikCube.littleCubes[indexCube].camadas[k] == 'E')
                                            searchE = true;
                                        if (RubikCube.littleCubes[indexCube].camadas[k] == 'D')
                                            searchD = true;
                                    }
                                    if (searchU) {
                                        vector<char> camadaTemp = { 'F', 'E', 'R' };
                                        RubikCube.littleCubes[indexCube].camadas = camadaTemp;
                                    }
                                    if (searchE) {
                                        vector<char> camadaTemp = { 'F', 'E', 'M' };
                                        RubikCube.littleCubes[indexCube].camadas = camadaTemp;
                                    }
                                    if (searchD) {
                                        vector<char> camadaTemp = { 'F', 'E', 'L' };
                                        RubikCube.littleCubes[indexCube].camadas = camadaTemp;
                                    }
                                    searchM = false;
                                }
                                else {
                                    //L
                                    bool searchL = false;
                                    for (int j = 0; j < 3; j++) {
                                        if (RubikCube.littleCubes[indexCube].camadas[j] == 'L') {
                                            searchL = true;
                                            break;
                                        }
                                    }
                                    if (searchL) {
                                        bool searchU = false;
                                        bool searchE = false;
                                        bool searchD = false;
                                        //UED
                                        for (int k = 0; k < 3; k++) {
                                            if (RubikCube.littleCubes[indexCube].camadas[k] == 'U')
                                                searchU = true;
                                            if (RubikCube.littleCubes[indexCube].camadas[k] == 'E')
                                                searchE = true;
                                            if (RubikCube.littleCubes[indexCube].camadas[k] == 'D')
                                                searchD = true;
                                        }
                                        if (searchU) {
                                            vector<char> camadaTemp = { 'F', 'U', 'R' };
                                            RubikCube.littleCubes[indexCube].camadas = camadaTemp;
                                        }
                                        if (searchE) {
                                            vector<char> camadaTemp = { 'F', 'U', 'M' };
                                            RubikCube.littleCubes[indexCube].camadas = camadaTemp;
                                        }
                                        if (searchD) {
                                            vector<char> camadaTemp = { 'F', 'U', 'L' };
                                            RubikCube.littleCubes[indexCube].camadas = camadaTemp;
                                        }
                                        searchL = false;
                                    }
                                }
                            }
                            searchF = false;
                        }
                    }
                }
            }
            
            if (condB) {
                if (angle < 90) {
                    RubikCube.moveB(-1);
                    angle++;
                }
                else {
                    condB = false;
                    if(solver_e==true){
                        solver_size_it--;
                        cout<<"Ejecutando Solver "<<100 - ((solver_size_it* 100)/solver_size)<<" %  --> "<< movementsList[0]<<endl;
                        
                        
                    }
                    else{
                        cout<<"Ejecutando --> "<< movementsList[0]<<endl;
                    }
                    movementsList.erase(movementsList.begin());
                    angle = 0;
                    bool searchB = false;
                    for (unsigned int indexCube = 0; indexCube < 26; indexCube++)
                    {
                        //B
                        for (int i = 0; i < 3; i++) {
                            if (RubikCube.littleCubes[indexCube].camadas[i] == 'B') {
                                searchB = true;
                                break;
                            }
                        }
                        if (searchB) {
                            //R
                            bool searchR = false;
                            for (int j = 0; j < 3; j++) {
                                if (RubikCube.littleCubes[indexCube].camadas[j] == 'R') {
                                    searchR = true;
                                    break;
                                }
                            }
                            if (searchR) {
                                bool searchU = false;
                                bool searchE = false;
                                bool searchD = false;
                                //UED
                                for (int k = 0; k < 3; k++) {
                                    if (RubikCube.littleCubes[indexCube].camadas[k] == 'U')
                                        searchU = true;
                                    if (RubikCube.littleCubes[indexCube].camadas[k] == 'E')
                                        searchE = true;
                                    if (RubikCube.littleCubes[indexCube].camadas[k] == 'D')
                                        searchD = true;
                                }
                                if (searchU) {
                                    vector<char> camadaTemp = { 'B', 'U', 'L' };
                                    RubikCube.littleCubes[indexCube].camadas = camadaTemp;
                                }
                                if (searchE) {
                                    vector<char> camadaTemp = { 'B', 'U', 'M' };
                                    RubikCube.littleCubes[indexCube].camadas = camadaTemp;
                                }
                                if (searchD) {
                                    vector<char> camadaTemp = { 'B', 'U', 'R' };
                                    RubikCube.littleCubes[indexCube].camadas = camadaTemp;
                                }
                                searchR = false;
                            }
                            else {
                                //M
                                bool searchM = false;
                                for (int j = 0; j < 3; j++) {
                                    if (RubikCube.littleCubes[indexCube].camadas[j] == 'M') {
                                        searchM = true;
                                        break;
                                    }
                                }
                                if (searchM) {
                                    bool searchU = false;
                                    bool searchE = false;
                                    bool searchD = false;
                                    //UED
                                    for (int k = 0; k < 3; k++) {
                                        if (RubikCube.littleCubes[indexCube].camadas[k] == 'U')
                                            searchU = true;
                                        if (RubikCube.littleCubes[indexCube].camadas[k] == 'E')
                                            searchE = true;
                                        if (RubikCube.littleCubes[indexCube].camadas[k] == 'D')
                                            searchD = true;
                                    }
                                    if (searchU) {
                                        vector<char> camadaTemp = { 'B', 'E', 'L' };
                                        RubikCube.littleCubes[indexCube].camadas = camadaTemp;
                                    }
                                    if (searchE) {
                                        vector<char> camadaTemp = { 'B', 'E', 'M' };
                                        RubikCube.littleCubes[indexCube].camadas = camadaTemp;
                                    }
                                    if (searchD) {
                                        vector<char> camadaTemp = { 'B', 'E', 'R' };
                                        RubikCube.littleCubes[indexCube].camadas = camadaTemp;
                                    }
                                    searchM = false;
                                }
                                else {
                                    //L
                                    bool searchL = false;
                                    for (int j = 0; j < 3; j++) {
                                        if (RubikCube.littleCubes[indexCube].camadas[j] == 'L') {
                                            searchL = true;
                                            break;
                                        }
                                    }
                                    if (searchL) {
                                        bool searchU = false;
                                        bool searchE = false;
                                        bool searchD = false;
                                        //UED
                                        for (int k = 0; k < 3; k++) {
                                            if (RubikCube.littleCubes[indexCube].camadas[k] == 'U')
                                                searchU = true;
                                            if (RubikCube.littleCubes[indexCube].camadas[k] == 'E')
                                                searchE = true;
                                            if (RubikCube.littleCubes[indexCube].camadas[k] == 'D')
                                                searchD = true;
                                        }
                                        if (searchU) {
                                            vector<char> camadaTemp = { 'B', 'D', 'L' };
                                            RubikCube.littleCubes[indexCube].camadas = camadaTemp;
                                        }
                                        if (searchE) {
                                            vector<char> camadaTemp = { 'B', 'D', 'M' };
                                            RubikCube.littleCubes[indexCube].camadas = camadaTemp;
                                        }
                                        if (searchD) {
                                            vector<char> camadaTemp = { 'B', 'D', 'R' };
                                            RubikCube.littleCubes[indexCube].camadas = camadaTemp;
                                        }
                                        searchL = false;
                                    }
                                }
                            }
                            searchB = false;
                        }
                    }

                }
            }
            
        }
        
        RubikCube.drawCube(&VBO[0], &VAO[0]);
        
        
                    
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    glDeleteVertexArrays(26, VAO);
    glDeleteBuffers(26, VBO);
    
    glDeleteVertexArrays(26, VAO_c);
    glDeleteBuffers(26, VBO_c);
    
    glDeleteVertexArrays(26, VAO_f);
    glDeleteBuffers(26, VBO_f);
    
    glDeleteVertexArrays(26, VAO_ucsp);
    glDeleteBuffers(26, VBO_ucsp);

    // terminate, clearing allocated GLFW resources.
    glfwTerminate();
    return 0;
}

void solvecube(vector<string> moves) {
    for (int i = 0; i < moves.size(); i++) {
        if (moves[i] == "R") {
            movementsList.push_back('R');
        }
        if (moves[i] == "L") {
            movementsList.push_back('L');
        }
        if (moves[i] == "U") {
            movementsList.push_back('U');
        }
        if (moves[i] == "D") {
            movementsList.push_back('D');
        }
        if (moves[i] == "F") {
            movementsList.push_back('F');
        }
        if (moves[i] == "B") {
            movementsList.push_back('B');
        }
        if (moves[i] == "R2") {
            movementsList.push_back('R');
            movementsList.push_back('R');
        }
        if (moves[i] == "L2") {
            movementsList.push_back('L');
            movementsList.push_back('L');
        }
        if (moves[i] == "U2") {
            movementsList.push_back('U');
            movementsList.push_back('U');
        }
        if (moves[i] == "D2") {
            movementsList.push_back('D');
            movementsList.push_back('D');
        }
        if (moves[i] == "F2") {
            movementsList.push_back('F');
            movementsList.push_back('F');
        }
        if (moves[i] == "B2") {
            movementsList.push_back('B');
            movementsList.push_back('B');
        }
        if (moves[i] == "R\'") {
            movementsList.push_back('R');
            movementsList.push_back('R');
            movementsList.push_back('R');
        }
        if (moves[i] == "L\'") {
            movementsList.push_back('L');
            movementsList.push_back('L');
            movementsList.push_back('L');
        }
        if (moves[i] == "U\'") {
            movementsList.push_back('U');
            movementsList.push_back('U');
            movementsList.push_back('U');
        }
        if (moves[i] == "D\'") {
            movementsList.push_back('D');
            movementsList.push_back('D');
            movementsList.push_back('D');
        }
        if (moves[i] == "F\'") {
            movementsList.push_back('F');
            movementsList.push_back('F');
            movementsList.push_back('F');
        }
        if (moves[i] == "B\'") {
            movementsList.push_back('B');
            movementsList.push_back('B');
            movementsList.push_back('B');
        }
    }
    
    solver_size=movementsList.size();
    solver_size_it=solver_size;
}

void randomMoves(vector<string>&cubo) {

    vector<string> cuboRandom = {"R","L","U","D","F","B","R\'","L\'" ,"U\'" ,"D\'" , "F\'","B\'"};

    for (int i = 0; i < 8; i++) {
        cubo.push_back(cuboRandom[rand() % cuboRandom.size()]);
    }
     

}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    
    
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        cameraFront += glm::vec3(0.0f, 0.10f, 0.0f);
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        cameraFront -= glm::vec3(0.0f, 0.10f, 0.0f);
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        cameraFront -= glm::vec3(0.10f, 0.0f, 0.0f);
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        cameraFront += glm::vec3(0.10f, 0.0f, 0.0f);
    if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
        cameraFront -= glm::vec3(0.0f, 0.0f, 0.10f);
    if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
        cameraFront += glm::vec3(0.0f, 0.0f, 0.10f);
  
    
     if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
        t=!t;
    
    
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
        cameraPos += glm::vec3(0.0f, 0.90f, 0.0f);
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
        cameraPos -= glm::vec3(0.0f, 0.90f, 0.0f);
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
        cameraPos -= glm::vec3(0.90f, 0.0f, 0.0f);
    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
        cameraPos += glm::vec3(0.90f, 0.0f, 0.0f);
    if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
        cameraPos -= glm::vec3(0.0f, 0.0f, 0.90f);
    if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
        cameraPos += glm::vec3(0.0f, 0.0f, 0.90f);

    
    
    if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS)
        translate_ += glm::vec3(0.5f, 0.0f, 0.0f);
    if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS)
        translate_ += glm::vec3(-0.5f, 0.0f, 0.0f);
    if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS)
        translate_ += glm::vec3(0.0f, -0.5f, 0.0f);
    if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)
        translate_ += glm::vec3(0.0f, 0.5f, 0.0f);

     
    
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS){
        rotate_= glm::vec3(1.0f, 0.0f, 0.0f);
        r=!r;
    }
    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS){
        rotate_= glm::vec3(0.0f, 1.0f, 0.0f);
        r=!r;
    }
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS){
        rotate_= glm::vec3(0.0f, 0.0f, 1.0f);
        r=!r;
    }
    
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS){
        rotate_= glm::vec3(1.0f, 1.0f, 1.0f);
        r=!r;
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        resp=!resp;
    }
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
        desordenar=!desordenar;
    }
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS){
        cor=!cor;
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS){
        face=!face;
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS){
        ucsp_=!ucsp_;
    }
    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS){
        rb_=!rb_;
    }
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS){
        spl_=!spl_;
    }
    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS){
        mov_ani=!mov_ani;
    }
    
    
    
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        cubo.push_back("R");
        movementsList.push_back('R');
    }
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
        cubo.push_back("L");
        movementsList.push_back('L');
    }
    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
        cubo.push_back("U");
        movementsList.push_back('U');
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        cubo.push_back("D");
        movementsList.push_back('D');
    }
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
        cubo.push_back("F");
        movementsList.push_back('F');
    }
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
        cubo.push_back("B");
        movementsList.push_back('B');
    }
    
    
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
        randomMoves(lcR);
        solvecube(lcR);
        vector<string> AB;
        AB = cubo;
        AB.reserve(AB.size() + lcR.size());
        AB.insert(AB.end(), lcR.begin(), lcR.end());
        cubo= AB;
    }
    
    
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        cout << endl;
        cout << "Moves -> ";
        for (int i = 0; i < cubo.size(); i++) {
            if (i == 0) {
                cout << cubo[i];
            }
            else {
                cout << " ," << cubo[i];
            }
        }
        cout << endl;

        std::vector<std::string> move = get_solution(to_cube_not(cubo));
        solver_e=true;
        cout << "Solution -> ";

        for (int i = 0; i < move.size(); i++) {
            if (i == 0) {
                cout << move[i];
            }
            else {
                cout << " ," << move[i];
            }
        }
        solvecube(move);
        cout << endl;
        cubo = vector<string>();
        lcR = vector<string>();
        moves = vector<string>();
    }
        
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}


void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
