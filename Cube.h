
#include </Users/nicole/Documents/2022-2/Grafica/glad/include/glad/glad.h>
#include </Users/nicole/Documents/2022-2/Grafica/glm-master/glm/glm.hpp>
#include <GLFW/glfw3.h>


#include </Users/nicole/Documents/2022-2/Grafica/glm-master/glm/gtc/matrix_transform.hpp>
#include </Users/nicole/Documents/2022-2/Grafica/glm-master/glm/gtc/type_ptr.hpp>


#include "/Users/nicole/Documents/2022-2/Grafica/CuboFinal/Prueba/shader_m.h"

#include <iostream>
#include <vector>

using namespace std;

vector<float> black = { 0.0f, 0.0f, 0.0f };
vector<float> white = { 1.0f, 1.0f, 1.0f };
vector<float> red = { 1.0f, 0.0f, 0.0f };
vector<float> green = { 0.04f, 1.0f, 0.0f };
vector<float> blue = { 0.0f, 0.12f, 1.0f };
vector<float> yellow = { 0.99f, 1.0f, 0.01f };
vector<float> pink = { 1.0f, 0.0f, 0.96f };




void multMatrix(vector<float>& result, vector<vector<float>>& A, float x, float y, float z, float w) {
    result[0] = A[0][0] * x + A[0][1] * y + A[0][2] * z + A[0][3] * w;
    result[1] = A[1][0] * x + A[1][1] * y + A[1][2] * z + A[1][3] * w;
    result[2] = A[2][0] * x + A[2][1] * y + A[2][2] * z + A[2][3] * w;
    result[3] = A[3][0] * x + A[3][1] * y + A[3][2] * z + A[3][3] * w;
}

void translatePoints(vector<float>& vert, float x, float y, float z) {
    vector<vector<float>> matrix_translation{
        {1, 0, 0, x},
        {0, 1, 0, y},
        {0, 0, 1, z},
        {0, 0, 0, 1}
    };
    for (vector<float>::iterator it = vert.begin(); it < vert.end(); it += 8) {
        vector<float> result(4, 0);
        multMatrix(result, matrix_translation, *it, *(it + 1), *(it + 2), 1);
        *it = result[0];
        *(it + 1) = result[1];
        *(it + 2) = result[2];
    }
}

void Xrotation(vector<float>& vert, float angle) {
    vector<vector<float>> matrix_rotation{
        {1, 0, 0, 0},
        {0, static_cast<float>(cos(glm::radians(angle))), static_cast<float>(-sin(glm::radians(angle))), 0},
        {0, static_cast<float>(sin(glm::radians(angle))), static_cast<float>(cos(glm::radians(angle))), 0},
        {0, 0, 0, 1}
    };
    for (vector<float>::iterator it = vert.begin(); it < vert.end(); it += 8) {
        vector<float> result(4, 0);
        multMatrix(result, matrix_rotation, *it, *(it + 1), *(it + 2), 1);
        *it = result[0];
        *(it + 1) = result[1];
        *(it + 2) = result[2];
    }
}

void Yrotation(vector<float>& vert, float angle) {
    vector<vector<float>> matrix_rotation{
        {static_cast<float>(cos(glm::radians(angle))), 0, static_cast<float>(sin(glm::radians(angle))), 0},
        {0, 1, 0, 0},
        {static_cast<float>(-sin(glm::radians(angle))), 0, static_cast<float>(cos(glm::radians(angle))), 0},
        {0, 0, 0, 1}
    };
    for (vector<float>::iterator it = vert.begin(); it < vert.end(); it += 8) {
        vector<float> result(4, 0);
        multMatrix(result, matrix_rotation, *it, *(it + 1), *(it + 2), 1);
        *it = result[0];
        *(it + 1) = result[1];
        *(it + 2) = result[2];
    }
}

void Zrotation(vector<float>& vert, float angle) {
    vector<vector<float>> matrix_rotation{
        {static_cast<float>(cos(glm::radians(angle))), static_cast<float>(-sin(glm::radians(angle))), 0, 0},
        {static_cast<float>(sin(glm::radians(angle))), static_cast<float>(cos(glm::radians(angle))), 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };
    for (vector<float>::iterator it = vert.begin(); it < vert.end(); it += 8) {
        vector<float> result(4, 0);
        multMatrix(result, matrix_rotation, *it, *(it + 1), *(it + 2), 1);
        *it = result[0];
        *(it + 1) = result[1];
        *(it + 2) = result[2];
    }
}


class LittleCube
{
public:
    int id;
    glm::vec3 initialPosition;
    vector<float> vertices;
    vector<vector<float>> listOfColors;
    vector<char> camadas;
    vector<float> textureIndices;
    LittleCube(int _id, glm::vec3 iP, vector<float> _vertices) {
        id = _id;
        initialPosition = iP;
        vertices = _vertices;
    };
};

class Cube
{
public:
    vector<LittleCube> littleCubes;
    Cube();
    ~Cube();
    
    void moveR(float angle);
    void moveL(float angle);
    void moveU(float angle);
    void moveD(float angle);
    void moveF(float angle);
    void moveB(float angle);
    void moveM(float angle);
    void moveE(float angle);
    void moveS(float angle);
    void respiracion(float dst);
    
    void desordenar();
    void girarEje();
    bool ordenar();
    bool corazon();
    void ani_corazon();
    void ani_carita();
    void ani_ucsp();
    void ani_cube();
    bool carita();
    bool ucsp();
    vector<vector<float>> animation_c;
    vector<vector<float>> animation_f;
    vector<vector<float>> animation_ord;
    vector<vector<float>> animation_ucsp;
    

    
    void createLittleCubes() {
        for (int i = 0; i < 26; i++) {
            vector<float> vecCube;
            copy(&vertices[0], &vertices[sizeof(vertices) / sizeof(float)], back_inserter(vecCube));
            LittleCube cube(i, i_cubes[i], vecCube);
            littleCubes.push_back(cube);
        }
        
        vector<vector<float>> colorCube0 = { black, red, blue, black, black, yellow };
        littleCubes[0].listOfColors = colorCube0;
        vector<vector<float>> colorCube1 = { black, red, black, black, black, yellow };
        littleCubes[1].listOfColors = colorCube1;
        vector<vector<float>> colorCube2 = { black, red, black, green, black, yellow };
        littleCubes[2].listOfColors = colorCube2;
        vector<vector<float>> colorCube3 = { black, red, blue, black, black, black };
        littleCubes[3].listOfColors = colorCube3;
        vector<vector<float>> colorCube4 = { black, red, black, black, black, black };
        littleCubes[4].listOfColors = colorCube4;
        vector<vector<float>> colorCube5 = { black, red, black, green, black, black };
        littleCubes[5].listOfColors = colorCube5;
        vector<vector<float>> colorCube6 = { black, red, blue, black, white, black };
        littleCubes[6].listOfColors = colorCube6;
        vector<vector<float>> colorCube7 = { black, red, black, black, white, black };
        littleCubes[7].listOfColors = colorCube7;
        vector<vector<float>> colorCube8 = { black, red, black, green, white, black };
        littleCubes[8].listOfColors = colorCube8;

        vector<vector<float>> colorCube9 = { black, black, blue, black, black, yellow };
        littleCubes[9].listOfColors = colorCube9;
        vector<vector<float>> colorCube10 = { black, black, black, black, black, yellow };
        littleCubes[10].listOfColors = colorCube10;
        vector<vector<float>> colorCube11 = { black, black, black, green, black, yellow };
        littleCubes[11].listOfColors = colorCube11;
        vector<vector<float>> colorCube12 = { black, black, blue, black, black, black };
        littleCubes[12].listOfColors = colorCube12;
        vector<vector<float>> colorCube13 = { black, black, black, green, black, black };
        littleCubes[13].listOfColors = colorCube13;
        vector<vector<float>> colorCube14 = { black, black, blue, black, white, black };
        littleCubes[14].listOfColors = colorCube14;
        vector<vector<float>> colorCube15 = { black, black, black, black, white, black };
        littleCubes[15].listOfColors = colorCube15;
        vector<vector<float>> colorCube16 = { black, black, black, green, white, black };
        littleCubes[16].listOfColors = colorCube16;

        vector<vector<float>> colorCube17 = { pink, black, blue, black, black, yellow };
        littleCubes[17].listOfColors = colorCube17;
        vector<vector<float>> colorCube18 = { pink, black, black, black, black, yellow };
        littleCubes[18].listOfColors = colorCube18;
        vector<vector<float>> colorCube19 = { pink, black, black, green, black, yellow };
        littleCubes[19].listOfColors = colorCube19;
        vector<vector<float>> colorCube20 = { pink, black, blue, black, black, black };
        littleCubes[20].listOfColors = colorCube20;
        vector<vector<float>> colorCube21 = { pink, black, black, black, black, black };
        littleCubes[21].listOfColors = colorCube21;
        vector<vector<float>> colorCube22 = { pink, black, black, green, black, black };
        littleCubes[22].listOfColors = colorCube22;
        vector<vector<float>> colorCube23 = { pink, black, blue, black, white, black };
        littleCubes[23].listOfColors = colorCube23;
        vector<vector<float>> colorCube24 = { pink, black, black, black, white, black };
        littleCubes[24].listOfColors = colorCube24;
        vector<vector<float>> colorCube25 = { pink, black, black, green, white, black };
        littleCubes[25].listOfColors = colorCube25;

        
        for (size_t i = 0; i < 26; i++)
        {
            for (int indexVertices = 3, indexColor = 0; indexVertices < 288; indexColor++)
            {
                for (int line = 0; line < 6; line++)
                {
                    littleCubes[i].vertices[indexVertices] = littleCubes[i].listOfColors[indexColor][0];
                    littleCubes[i].vertices[indexVertices + 1] = littleCubes[i].listOfColors[indexColor][1];
                    littleCubes[i].vertices[indexVertices + 2] = littleCubes[i].listOfColors[indexColor][2];
                    indexVertices += 8;
                }
            }
        }
        
        vector<float> textureTest = {
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0
        };

        vector<float> texture0 = {
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            3.0 / 9, 2.0 / 3,
            3.5 / 9, 2.0 / 3,
            3.5 / 9, 1.0,
            3.5 / 9, 1.0,
            3.0 / 9, 1.0,
            3.0 / 9, 2.0 / 3,

            3.0 / 9, 1.0,
            2.5 / 9, 1.0,
            2.5 / 9, 2.0 / 3,
            2.5 / 9, 2.0 / 3,
            3.0 / 9, 2.0 / 3,
            3.0 / 9, 1.0,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            0 , 1.0 / 3,
            0.5 / 9 , 1.0 / 3,
            0.5 / 9 , 0,
            0.5 / 9 , 0,
            0, 0,
            0 , 1.0 / 3
        };
        littleCubes[0].textureIndices = texture0;
        vector<float> texture1 = {
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            3.5 / 9, 2.0 / 3,
            4.0 / 9, 2.0 / 3,
            4.0 / 9, 1.0,
            4.0 / 9, 1.0,
            3.5 / 9, 1.0,
            3.5 / 9, 2.0 / 3,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            0.5 / 9, 1.0 / 3,
            1.0 / 9, 1.0 / 3,
            1.0 / 9, 0.0,
            1.0 / 9, 0.0,
            0.5 / 9, 0.0,
            0.5 / 9, 1.0 / 3
        };
        littleCubes[1].textureIndices = texture1;
        vector<float> texture2 = {
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            4.0 / 9, 2.0 / 3,
            0.5, 2.0 / 3,
            0.5, 1.0,
            0.5, 1.0,
            4.0 / 9, 1.0,
            4.0 / 9, 2.0 / 3,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            6.0 / 9, 1.0,
            6.5 / 9, 1.0,
            6.5 / 9, 2.0 / 3,
            6.5 / 9, 2.0 / 3,
            6.0 / 9, 2.0 / 3,
            6.0 / 9, 1.0,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            1.0 / 9, 1.0 / 3,
            1.5 / 9, 1.0 / 3,
            1.5 / 9, 0.0,
            1.5 / 9, 0.0,
            1.0 / 9, 0.0,
            1.0 / 9, 1.0 / 3
        };
        littleCubes[2].textureIndices = texture2;
        vector<float> texture3 = {
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            3.0 / 9, 1.0 / 3,
            3.5 / 9, 1.0 / 3,
            3.5 / 9, 2.0 / 3,
            3.5 / 9, 2.0 / 3,
            3.0 / 9, 2.0 / 3,
            3.0 / 9, 1.0 / 3,

            3.0 / 9, 2.0 / 3,
            2.5 / 9, 2.0 / 3,
            2.5 / 9, 1.0 / 3,
            2.5 / 9, 1.0 / 3,
            3.0 / 9, 1.0 / 3,
            3.0 / 9, 2.0 / 3,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0
        };
        littleCubes[3].textureIndices = texture3;
        vector<float> texture4 = {
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            3.5 / 9, 1.0 / 3,
            4.0 / 9, 1.0 / 3,
            4.0 / 9, 2.0 / 3,
            4.0 / 9, 2.0 / 3,
            3.5 / 9, 2.0 / 3,
            3.5 / 9, 1.0 / 3,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0
        };
        littleCubes[4].textureIndices = texture4;
        vector<float> texture5 = {
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            4.0 / 9, 1.0 / 3,
            0.5, 1.0 / 3,
            0.5, 2.0 / 3,
            0.5, 2.0 / 3,
            4.0 / 9, 2.0 / 3,
            4.0 / 9, 1.0 / 3,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            6.0 / 9, 2.0 / 3,
            6.5 / 9, 2.0 / 3,
            6.5 / 9, 1.0 / 3,
            6.5 / 9, 1.0 / 3,
            6.0 / 9, 1.0 / 3,
            6.0 / 9, 2.0 / 3,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0
        };
        littleCubes[5].textureIndices = texture5;
        vector<float> texture6 = {
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            3.0 / 9, 0.0,
            3.5 / 9, 0.0,
            3.5 / 9, 1.0 / 3,
            3.5 / 9, 1.0 / 3,
            3.0 / 9, 1.0 / 3,
            3.0 / 9, 0.0,

            3.0 / 9, 1.0 / 3,
            2.5 / 9, 1.0 / 3,
            2.5 / 9, 0.0,
            2.5 / 9, 0.0,
            3.0 / 9, 0.0,
            3.0 / 9, 1.0 / 3,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            0.5 , 2.0 / 3,
            5.0 / 9 , 2.0 / 3,
            5.0 / 9 , 1.0,
            5.0 / 9 , 1.0,
            0.5 , 1.0,
            0.5 , 2.0 / 3,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0
        };
        littleCubes[6].textureIndices = texture6;
        vector<float> texture7 = {
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            3.5 / 9, 0.0,
            4.0 / 9, 0.0,
            4.0 / 9, 1.0 / 3,
            4.0 / 9, 1.0 / 3,
            3.5 / 9, 1.0 / 3,
            3.5 / 9, 0.0,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            5.0 / 9, 2.0 / 3,
            5.5 / 9, 2.0 / 3,
            5.5 / 9, 1.0,
            5.5 / 9, 1.0,
            5.0 / 9, 1.0,
            5.0 / 9, 2.0 / 3,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0
        };
        littleCubes[7].textureIndices = texture7;
        vector<float> texture8 = {
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            4.0 / 9, 0.0,
            0.5, 0.0,
            0.5, 1.0 / 3,
            0.5, 1.0 / 3,
            4.0 / 9, 1.0 / 3,
            4.0 / 9, 0.0,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            6.0 / 9, 1.0 / 3,
            6.5 / 9, 1.0 / 3,
            6.5 / 9, 0.0,
            6.5 / 9, 0.0,
            6.0 / 9, 0.0,
            6.0 / 9, 1.0 / 3,

            5.5 / 9, 2.0 / 3,
            6.0 / 9, 2.0 / 3,
            6.0 / 9, 1.0,
            6.0 / 9, 1.0,
            5.5 / 9, 1.0,
            5.5 / 9, 2.0 / 3,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0
        };
        littleCubes[8].textureIndices = texture8;
        vector<float> texture9 = {
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            2.5 / 9, 1.0,
            2.0 / 9, 1.0,
            2.0 / 9, 2.0 / 3,
            2.0 / 9, 2.0 / 3,
            2.5 / 9, 2.0 / 3,
            2.5 / 9, 1.0,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            0.0, 2.0 / 3,
            0.5 / 9, 2.0 / 3,
            0.5 / 9, 1.0 / 3,
            0.5 / 9, 1.0 / 3,
            0.0, 1.0 / 3,
            0.0, 2.0 / 3
        };
        littleCubes[9].textureIndices = texture9;
        vector<float> texture10 = {
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            0.5 / 9, 2.0 / 3,
            1.0 / 9, 2.0 / 3,
            1.0 / 9, 1.0 / 3,
            1.0 / 9, 1.0 / 3,
            0.5 / 9, 1.0 / 3,
            0.5 / 9, 2.0 / 3
        };
        littleCubes[10].textureIndices = texture10;
        vector<float> texture11 = {
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            6.5 / 9, 1.0,
            7.0 / 9, 1.0,
            7.0 / 9, 2.0 / 3,
            7.0 / 9, 2.0 / 3,
            6.5 / 9, 2.0 / 3,
            6.5 / 9, 1.0,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            1.0 / 9, 2.0 / 3,
            1.5 / 9, 2.0 / 3,
            1.5 / 9, 1.0 / 3,
            1.5 / 9, 1.0 / 3,
            1.0 / 9, 1.0 / 3,
            1.0 / 9, 2.0 / 3
        };
        littleCubes[11].textureIndices = texture11;
        vector<float> texture12 = {
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            2.5 / 9, 2.0 / 3,
            2.0 / 9, 2.0 / 3,
            2.0 / 9, 1.0 / 3,
            2.0 / 9, 1.0 / 3,
            2.5 / 9, 1.0 / 3,
            2.5 / 9, 2.0 / 3,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0
        };
        littleCubes[12].textureIndices = texture12;
        vector<float> texture13 = {
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            6.5 / 9, 2.0 / 3,
            7.0 / 9, 2.0 / 3,
            7.0 / 9, 1.0 / 3,
            7.0 / 9, 1.0 / 3,
            6.5 / 9, 1.0 / 3,
            6.5 / 9, 2.0 / 3,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0
        };
        littleCubes[13].textureIndices = texture13;
        vector<float> texture14 = {
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            2.5 / 9, 1.0 / 3,
            2.0 / 9, 1.0 / 3,
            2.0 / 9, 0.0,
            2.0 / 9, 0.0,
            2.5 / 9, 0.0,
            2.5 / 9, 1.0 / 3,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            0.5, 1.0 / 3,
            5.0 / 9, 1.0 / 3,
            5.0 / 9, 2.0 / 3,
            5.0 / 9, 2.0 / 3,
            0.5, 2.0 / 3,
            0.5, 1.0 / 3,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0
        };
        littleCubes[14].textureIndices = texture14;
        vector<float> texture15 = {
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            5.0 / 9, 1.0 / 3,
            5.5 / 9, 1.0 / 3,
            5.5 / 9, 2.0 / 3,
            5.5 / 9, 2.0 / 3,
            5.0 / 9, 2.0 / 3,
            5.0 / 9, 1.0 / 3,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0
        };
        littleCubes[15].textureIndices = texture15;
        vector<float> texture16 = {
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            6.5 / 9, 1.0 / 3,
            7.0 / 9, 1.0 / 3,
            7.0 / 9, 0.0,
            7.0 / 9, 0.0,
            6.5 / 9, 0.0,
            6.5 / 9, 1.0 / 3,

            5.5 / 9, 1.0 / 3,
            6.0 / 9, 1.0 / 3,
            6.0 / 9, 2.0 / 3,
            6.0 / 9, 2.0 / 3,
            5.5 / 9, 2.0 / 3,
            5.5 / 9, 1.0 / 3,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0
        };
        littleCubes[16].textureIndices = texture16;
        vector<float> texture17 = {
            1.0, 2.0 / 3,
            8.5 / 9, 2.0 / 3,
            8.5 / 9, 1.0,
            8.5 / 9, 1.0,
            1.0, 1.0,
            1.0, 2.0 / 3,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            2.0 / 9, 1.0,
            1.5 / 9, 1.0,
            1.5 / 9, 2.0 / 3,
            1.5 / 9, 2.0 / 3,
            2.0 / 9, 2.0 / 3,
            2.0 / 9, 1.0,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            0.0, 1.0,
            0.5 / 9, 1.0,
            0.5 / 9, 2.0 / 3,
            0.5 / 9, 2.0 / 3,
            0.0, 2.0 / 3,
            0.0, 1.0
        };
        littleCubes[17].textureIndices = texture17;
        vector<float> texture18 = {
            8.5 / 9, 2.0 / 3,
            8.0 / 9, 2.0 / 3,
            8.0 / 9, 1.0,
            8.0 / 9, 1.0,
            8.5 / 9, 1.0,
            8.5 / 9, 2.0 / 3,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            0.5 / 9, 1.0,
            1.0 / 9, 1.0,
            1.0 / 9, 2.0 / 3,
            1.0 / 9, 2.0 / 3,
            0.5 / 9, 2.0 / 3,
            0.5 / 9, 1.0
        };
        littleCubes[18].textureIndices = texture18;
        vector<float> texture19 = {
            8.0 / 9, 2.0 / 3,
            7.5 / 9, 2.0 / 3,
            7.5 / 9, 1.0,
            7.5 / 9, 1.0,
            8.0 / 9, 1.0,
            8.0 / 9, 2.0 / 3,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            7.0 / 9, 1.0,
            7.5 / 9, 1.0,
            7.5 / 9, 2.0 / 3,
            7.5 / 9, 2.0 / 3,
            7.0 / 9, 2.0 / 3,
            7.0 / 9, 1.0,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            1.0 / 9, 1.0,
            1.5 / 9, 1.0,
            1.5 / 9, 2.0 / 3,
            1.5 / 9, 2.0 / 3,
            1.0 / 9, 2.0 / 3,
            1.0 / 9, 1.0
        };
        littleCubes[19].textureIndices = texture19;
        vector<float> texture20 = {
            1.0, 1.0 / 3,
            8.5 / 9, 1.0 / 3,
            8.5 / 9, 2.0 / 3,
            8.5 / 9, 2.0 / 3,
            1.0, 2.0 / 3,
            1.0, 1.0 / 3,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            2.0 / 9, 2.0 / 3,
            1.5 / 9, 2.0 / 3,
            1.5 / 9, 1.0 / 3,
            1.5 / 9, 1.0 / 3,
            2.0 / 9, 1.0 / 3,
            2.0 / 9, 2.0 / 3,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0
        };
        littleCubes[20].textureIndices = texture20;
        vector<float> texture21 = {
            8.5 / 9, 1.0 / 3,
            8.0 / 9, 1.0 / 3,
            8.0 / 9, 2.0 / 3,
            8.0 / 9, 2.0 / 3,
            8.5 / 9, 2.0 / 3,
            8.5 / 9, 1.0 / 3,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0
        };
        littleCubes[21].textureIndices = texture21;
        vector<float> texture22 = {
            8.0 / 9, 1.0 / 3,
            7.5 / 9, 1.0 / 3,
            7.5 / 9, 2.0 / 3,
            7.5 / 9, 2.0 / 3,
            8.0 / 9, 2.0 / 3,
            8.0 / 9, 1.0 / 3,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            7.0 / 9, 2.0 / 3,
            7.5 / 9, 2.0 / 3,
            7.5 / 9, 1.0 / 3,
            7.5 / 9, 1.0 / 3,
            7.0 / 9, 1.0 / 3,
            7.0 / 9, 2.0 / 3,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0
        };
        littleCubes[22].textureIndices = texture22;
        vector<float> texture23 = {
            1.0, 0.0,
            8.5 / 9, 0.0,
            8.5 / 9, 1.0 / 3,
            8.5 / 9, 1.0 / 3,
            1.0, 1.0 / 3,
            1.0, 0.0,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            2.0 / 9, 1.0 / 3,
            1.5 / 9, 1.0 / 3,
            1.5 / 9, 0.0,
            1.5 / 9, 0.0,
            2.0 / 9, 0.0,
            2.0 / 9, 1.0 / 3,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            0.5, 0.0,
            5.0 / 9, 0.0,
            5.0 / 9, 1.0 / 3,
            5.0 / 9, 1.0 / 3,
            0.5, 1.0 / 3,
            0.5, 0.0,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0
        };
        littleCubes[23].textureIndices = texture23;
        vector<float> texture24 = {
            8.5 / 9, 0.0,
            8.0 / 9, 0.0,
            8.0 / 9, 1.0 / 3,
            8.0 / 9, 1.0 / 3,
            8.5 / 9, 1.0 / 3,
            8.5 / 9, 0.0,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            5.0 / 9, 0.0,
            5.5 / 9, 0.0,
            5.5 / 9, 1.0 / 3,
            5.5 / 9, 1.0 / 3,
            5.0 / 9, 1.0 / 3,
            5.0 / 9, 0.0,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0
        };
        littleCubes[24].textureIndices = texture24;
        vector<float> texture25 = {
            8.0 / 9, 0.0,
            7.5 / 9, 0.0,
            7.5 / 9, 1.0 / 3,
            7.5 / 9, 1.0 / 3,
            8.0 / 9, 1.0 / 3,
            8.0 / 9, 0.0,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,

            7.0 / 9, 1.0 / 3,
            7.5 / 9, 1.0 / 3,
            7.5 / 9, 0.0,
            7.5 / 9, 0.0,
            7.0 / 9, 0.0,
            7.0 / 9, 1.0 / 3,

            5.5 / 9, 0.0,
            6.0 / 9, 0.0,
            6.0 / 9, 1.0 / 3,
            6.0 / 9, 1.0 / 3,
            5.5 / 9, 1.0 / 3,
            5.5 / 9, 0.0,

            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0,
            0, 0
        };
        littleCubes[25].textureIndices = texture25;
        
        //define textures
        for (size_t i = 0; i < 26; i++)//each cube
        {
            for (int indexVertices = 6, indexTexture = 0;
                indexVertices < 288;
                indexTexture+=2, indexVertices += 8)
            {
                littleCubes[i].vertices[indexVertices] = littleCubes[i].textureIndices[indexTexture];
                littleCubes[i].vertices[indexVertices + 1] = littleCubes[i].textureIndices[indexTexture + 1];
            }
        }

        
        vector<char> camada0 = { 'R', 'U', 'F' };
        littleCubes[0].camadas = camada0;
        vector<char> camada1 = { 'R', 'U', 'S' };
        littleCubes[1].camadas = camada1;
        vector<char> camada2 = { 'R', 'U', 'B' };
        littleCubes[2].camadas = camada2;

        vector<char> camada3 = { 'R', 'E', 'F' };
        littleCubes[3].camadas = camada3;
        vector<char> camada4 = { 'R', 'E', 'S' };
        littleCubes[4].camadas = camada4;
        vector<char> camada5 = { 'R', 'E', 'B' };
        littleCubes[5].camadas = camada5;

        vector<char> camada6 = { 'R', 'D', 'F' };
        littleCubes[6].camadas = camada6;
        vector<char> camada7 = { 'R', 'D', 'S' };
        littleCubes[7].camadas = camada7;
        vector<char> camada8 = { 'R', 'D', 'B' };
        littleCubes[8].camadas = camada8;

        vector<char> camada9 = { 'M', 'U', 'F' };
        littleCubes[9].camadas = camada9;
        vector<char> camada10 = { 'M', 'U', 'S' };
        littleCubes[10].camadas = camada10;
        vector<char> camada11 = { 'M', 'U', 'B' };
        littleCubes[11].camadas = camada11;

        vector<char> camada12 = { 'M', 'E', 'F' };
        littleCubes[12].camadas = camada12;
        vector<char> camada13 = { 'M', 'E', 'B' };
        littleCubes[13].camadas = camada13;

        vector<char> camada14 = { 'M', 'D', 'F' };
        littleCubes[14].camadas = camada14;
        vector<char> camada15 = { 'M', 'D', 'S' };
        littleCubes[15].camadas = camada15;
        vector<char> camada16 = { 'M', 'D', 'B' };
        littleCubes[16].camadas = camada16;

        vector<char> camada17 = { 'L', 'U', 'F' };
        littleCubes[17].camadas = camada17;
        vector<char> camada18 = { 'L', 'U', 'S' };
        littleCubes[18].camadas = camada18;
        vector<char> camada19 = { 'L', 'U', 'B' };
        littleCubes[19].camadas = camada19;

        vector<char> camada20 = { 'L', 'E', 'F' };
        littleCubes[20].camadas = camada20;
        vector<char> camada21 = { 'L', 'E', 'S' };
        littleCubes[21].camadas = camada21;
        vector<char> camada22 = { 'L', 'E', 'B' };
        littleCubes[22].camadas = camada22;

        vector<char> camada23 = { 'L', 'D', 'F' };
        littleCubes[23].camadas = camada23;
        vector<char> camada24 = { 'L', 'D', 'S' };
        littleCubes[24].camadas = camada24;
        vector<char> camada25 = { 'L', 'D', 'B' };
        littleCubes[25].camadas = camada25;


        
        for (size_t i = 0; i < 26; i++)
            translatePoints(littleCubes[i].vertices, littleCubes[i].initialPosition.x, littleCubes[i].initialPosition.y, littleCubes[i].initialPosition.z);
        
    }
void drawCube(unsigned int* VBO, unsigned int* VAO) {
        for (int i = 0; i < 26; i++) {
            glBindVertexArray(VAO[i]);
            glBindBuffer(GL_ARRAY_BUFFER, VBO[i]);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &(littleCubes[i].vertices[0]), GL_STATIC_DRAW);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
            glEnableVertexAttribArray(2);
        }

    }

private:
    float vertices[288] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 1.0f
    };
//2.5 2.0 1.0   2.5 -2.0 1.0
    glm::vec3 i_cubes[26] = {
        glm::vec3(-1.0f, 1.0f, 1.0f),   //0
        glm::vec3(0.0f, 1.0f, 1.0f),   //1
        glm::vec3(1.0f, 1.0f, 1.0f),   //2

        glm::vec3(-1.0f, 0.0f, 1.0f),  //3
        glm::vec3(0.0f, 0.0f, 1.0f),  //4
        glm::vec3(1.0f, 0.0f, 1.0f),  //5

        glm::vec3(-1.0f, -1.0f, 1.0f),  //6
        glm::vec3(0.0f, -1.0f, 1.0f),  //7
        glm::vec3(1.0f, -1.0f, 1.0f),  //8

        glm::vec3(-1.0f, 1.0f, 0.0f),  //9
        glm::vec3(0.0f, 1.0f, 0.0f),  //10
        glm::vec3(1.0f, 1.0f, 0.0f),  //11

        glm::vec3(-1.0f, 0.0f, 0.0f), //12
        glm::vec3(1.0f, 0.0f, 0.0f), //13

        glm::vec3(-1.0f, -1.0f, 0.0f), //14
        glm::vec3(0.0f, -1.0f, 0.0f), //15
        glm::vec3(1.0f, -1.0f, 0.0f), //16

        glm::vec3(-1.0f, 1.0f, -1.0f),  //17
        glm::vec3(0.0f, 1.0f, -1.0f),  //18
        glm::vec3(1.0f, 1.0f, -1.0f),  //19

        glm::vec3(-1.0f, 0.0f, -1.0f), //20
        glm::vec3(0.0f, 0.0f, -1.0f), //21
        glm::vec3(1.0f, 0.0f, -1.0f), //22

        glm::vec3(-1.0f, -1.0f, -1.0f), //23
        glm::vec3(0.0f, -1.0f, -1.0f), //24
        glm::vec3(1.0f, -1.0f, -1.0f)  //25
    };
    glm::vec3 i_cubes_ani[26] = {
        glm::vec3(-1.0f -9.0f, 1.0f +9.0f, 1.0f-25.0f),   //0
        glm::vec3(0.0f-9.0f, 1.0f +9.0f, 1.0f-25.0f),   //1
        glm::vec3(1.0f-9.0f, 1.0f +9.0f, 1.0f-25.0f),   //2

        glm::vec3(-1.0f-9.0f, 0.0f +9.0f, 1.0f-25.0f),  //3
        glm::vec3(0.0f-9.0f, 0.0f +9.0f, 1.0f-25.0f),  //4
        glm::vec3(1.0f-9.0f, 0.0f +9.0f, 1.0f-25.0f),  //5

        glm::vec3(-1.0f-9.0f, -1.0f +9.0f, 1.0f-25.0f),  //6
        glm::vec3(0.0f-9.0f, -1.0f +9.0f, 1.0f-25.0f),  //7
        glm::vec3(1.0f-9.0f, -1.0f +9.0f, 1.0f-25.0f),  //8

        glm::vec3(-1.0f-9.0f, 1.0f+9.0f, 0.0f-25.0f),  //9
        glm::vec3(0.0f-9.0f, 1.0f+9.0f, 0.0f-25.0f),  //10
        glm::vec3(1.0f-9.0f, 1.0f+9.0f, 0.0f-25.0f),  //11

        glm::vec3(-1.0f-9.0f, 0.0f+9.0f, 0.0f-25.0f), //12
        glm::vec3(1.0f-9.0f, 0.0f+9.0f, 0.0f-25.0f), //13

        glm::vec3(-1.0f-9.0f, -1.0f+9.0f, 0.0f-25.0f), //14
        glm::vec3(0.0f-9.0f, -1.0f+9.0f, 0.0f-25.0f), //15
        glm::vec3(1.0f-9.0f, -1.0f+9.0f, 0.0f-25.0f), //16

        glm::vec3(-1.0f-9.0f, 1.0f+9.0f, -1.0f-25.0f),  //17
        glm::vec3(0.0f-9.0f, 1.0f+9.0f, -1.0f-25.0f),  //18
        glm::vec3(1.0f-9.0f, 1.0f+9.0f, -1.0f-25.0f),  //19

        glm::vec3(-1.0f-9.0f, 0.0f+9.0f, -1.0f-25.0f), //20
        glm::vec3(0.0f-9.0f, 0.0f+9.0f, -1.0f-25.0f), //21
        glm::vec3(1.0f-9.0f, 0.0f+9.0f, -1.0f-25.0f), //22

        glm::vec3(-1.0f-9.0f, -1.0f+9.0f, -1.0f-25.0f), //23
        glm::vec3(0.0f-9.0f, -1.0f+9.0f, -1.0f-25.0f), //24
        glm::vec3(1.0f-9.0f, -1.0f+9.0f, -1.0f-25.0f)  //25
    };
    glm::vec3 i_cubes_ucsp[26] = {
        
        
        glm::vec3(1.5f+7.0f, 9.5f, -25.0f),   //s
        glm::vec3(2.5f+7.0f, 9.35f, -25.0f), //s
        glm::vec3(0.5f+7.0f, 9.15f, -25.0f), //s
        glm::vec3(1.5f+7.0f, 8.15f, -25.0f), //s
        glm::vec3(1.5f+7.0f, 7.15f, -25.0f),   //s
        glm::vec3(2.5f+7.0f, 7.5f, -25.0f), //s
        glm::vec3(0.5f+7.0f, 7.15f, -25.0f), //s
        
        glm::vec3(-7.0f+7.0f, 9.5f, -25.0f),   //u
        glm::vec3(-7.0f+7.0f, 8.5f, -25.0f),   //u
        glm::vec3(-6.5f+7.0f, 7.5f, -25.0f),   //u
        glm::vec3(-5.5f+7.0f, 7.5f, -25.0f),  //u
        glm::vec3(-5.0f+7.0f, 9.5f, -25.0f),   //u
        glm::vec3(-5.0f+7.0f, 8.5f, -25.0f),   //u

        glm::vec3(-1.0f+7.0f, 9.25f, -25.0f),   //c
        glm::vec3(-2.0f+7.0f, 9.5f, -25.0f), //c
        glm::vec3(-3.0f+7.0f, 9.25f, -25.0f), //c
        glm::vec3(-3.0f+7.0f, 8.5f, -25.0f),   //c
        glm::vec3(-1.0f+7.0f, 7.5f, -25.0f),   //c
        glm::vec3(-2.0f+7.0f, 7.25f, -25.0f), //c
        glm::vec3(-3.f+7.0f, 7.5f, -25.0f), //c
        
        
        glm::vec3(5.5f+7.0f, 9.5f, -25.0f),   //p
        glm::vec3(6.5f+7.0f, 9.25f, -25.0f), //p
        glm::vec3(4.5f+7.0f, 9.25f, -25.0f), //p
        glm::vec3(4.5f+7.0f, 8.25f, -25.0f), //p
        glm::vec3(4.5f+7.0f, 7.25f, -25.0f), //p
        glm::vec3(5.5f+7.0f, 8.05f, -25.0f), //p
        
    };
    glm::vec3 i_cubes_h[26] = {
        
        
        glm::vec3(0.0f -9.0f, -5.5f -3.0f, -25.0f),   //s
        
        glm::vec3(0.75f -9.0f, -4.5f -3.0f, -25.0f),   //s
        glm::vec3(-0.75f -9.0f, -4.5f -3.0f, -25.0f),   //s
        glm::vec3(1.25f -9.0f, -3.5f -3.0f, -25.0f),   //s
        glm::vec3(-1.25f -9.0f, -3.5f -3.0f, -25.0f),   //s
        glm::vec3(2.0f -9.0f, -2.5f -3.0f, -25.0f),   //s
        glm::vec3(-2.0f -9.0f, -2.5f -3.0f, -25.0f),   //s
        
        glm::vec3(2.75f -9.0f, -1.5f -3.0f, -25.0f),   //s
        glm::vec3(-2.75f -9.0f, -1.5f -3.0f, -25.0f),   //s
        glm::vec3(3.25f -9.0f, -0.5f -3.0f, -25.0f),   //s
        glm::vec3(-3.25f -9.0f, -0.5f -3.0f, -25.0f),   //s
        glm::vec3(4.0f -9.0f, 0.5f -3.0f, -25.0f),   //s
        glm::vec3(-4.0f -9.0f, 0.5f -3.0f, -25.0f),   //s
        glm::vec3(4.75f -9.0f, 1.5f -3.0f, -25.0f),   //s
        glm::vec3(-4.75f -9.0f, 1.5f -3.0f, -25.0f),   //s
        
        glm::vec3(-5.0f -9.0f, 2.5f -3.0f, -25.0f),   //s
        glm::vec3(5.0f -9.0f, 2.5f -3.0f, -25.0f),   //s
        glm::vec3(-4.0f -9.0f, 3.5f -3.0f, -25.0f),   //s
        glm::vec3(4.0f -9.0f, 3.5f -3.0f, -25.0f),   //s
        //
        glm::vec3(-3.0f -9.0f, 4.25f -3.0f, -25.0f),   //s
        glm::vec3(3.0f -9.0f, 4.25f -3.0f, -25.0f),   //s
        
        glm::vec3(-2.0f -9.0f, 3.75f -3.0f, -25.0f),   //s
        glm::vec3(2.0f -9.0f, 3.75f -3.0f, -25.0f),   //s
        
        glm::vec3(-1.0f -9.0f, 3.0f -3.0f, -25.0f),   //s
        glm::vec3(1.0f -9.0f, 3.0f -3.0f, -25.0f),   //s
        
        glm::vec3(-0.0f -9.0f, 2.0f-3.0f, -25.0f),   //s


        
    };
    glm::vec3 i_cubes_f[26] = {
        glm::vec3(0.0f +9.0f, -5.0f -3.0f, -25.0f),   //s
        glm::vec3(0.0f +9.0f, 5.0f-3.0f, -25.0f),   //s
        
        glm::vec3(-5.0f +9.0f, 0.0f-3.0f, -25.0f),   //s
        glm::vec3(5.0f +9.0f, 0.0f-3.0f, -25.0f),   //s
        
        glm::vec3(-3.47f +9.0f, 3.47f-3.0f, -25.0f),   //s
        glm::vec3(3.47f +9.0f, 3.47f-3.0f, -25.0f),   //s
        
        glm::vec3(-3.47f +9.0f, -3.47f-3.0f, -25.0f),   //s
        glm::vec3(3.47f +9.0f, -3.47f-3.0f, -25.0f),   //s
        
        glm::vec3(-4.55f +9.0f, -2.06f-3.0f, -25.0f),   //s
        glm::vec3(4.55f +9.0f, -2.06f-3.0f, -25.0f),   //s
        
        glm::vec3(-4.55f +9.0f, 2.06f-3.0f, -25.0f),   //s
        glm::vec3(4.55f +9.0f, 2.06f-3.0f, -25.0f),   //s
        
        glm::vec3(2.06f +9.0f, 4.55f-3.0f, -25.0f),   //s
        glm::vec3(-2.06f +9.0f, 4.55f-3.0f, -25.0f),   //s
        
        glm::vec3(2.06f +9.0f, -4.55f-3.0f, -25.0f),   //s
        glm::vec3(-2.06f +9.0f, -4.55f-3.0f, -25.0f),   //s
        
        glm::vec3(1.5f +9.0f, 2.5f-3.0f, -25.0f),   //s
        glm::vec3(-1.5f +9.0f, 2.5f-3.0f, -25.0f),   //s
        glm::vec3(1.5f +9.0f, 1.5f-3.0f, -25.0f),   //s
        glm::vec3(-1.5f +9.0f, 1.5f-3.0f, -25.0f),   //s
        
        glm::vec3(0.0f +9.0f, -3.0f-3.0f, -25.0f),   //s
        glm::vec3(1.0f +9.0f, -2.5f-3.0f, -25.0f),   //s
        glm::vec3(-1.0f +9.0f, -2.5f-3.0f, -25.0f),   //s
        glm::vec3(2.0f +9.0f, -1.75f-3.0f, -25.0f),   //s
        glm::vec3(-2.0f+9.0f, -1.75f-3.0f, -25.0f),   //s
        
        glm::vec3(0.0f+9.0f, 0.0f-3.0f, -25.0f),   //s



        
    };
    
};

void Cube::respiracion(float dist) {
    
    for (unsigned int indexCube = 0; indexCube < 26; indexCube++){
       
        translatePoints(littleCubes[indexCube].vertices, littleCubes[indexCube].initialPosition.x*dist, littleCubes[indexCube].initialPosition.y *dist, littleCubes[indexCube].initialPosition.z *dist);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}

void Cube::desordenar() {
    for (unsigned int indexCube = 0; indexCube < 26; indexCube++){
        int a=rand();
        float x_=0.0 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(8.0-0.0)));
        float y_=0.0 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(10.0-0.0)));
        float z_= (20.0 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(20.0-30.0))));
        if(a%2 == 0 || a%4 == 0 || a%6 == 0) {
            x_=-x_;
        }
        if(a%3 == 0 || a%8 == 0 || a%9 == 0 || a%7 == 0) {
            y_=-y_;
        }
        if(a%5 == 0) {
            x_=-x_;
            y_=-y_;
        }
        translatePoints(littleCubes[indexCube].vertices, -littleCubes[indexCube].vertices[0] -x_, -littleCubes[indexCube].vertices[1]-y_,-littleCubes[indexCube].vertices[2]-z_);
        a=rand();
        if(a % 4 == 0 || a % 6 == 0){
            Yrotation(littleCubes[indexCube].vertices, 1);
        }
        if(a % 2 == 0 || a % 5 == 0){
            Zrotation(littleCubes[indexCube].vertices, 1);
        }
        if(a % 3 == 0 || a % 7 == 0){
            Xrotation(littleCubes[indexCube].vertices, 1);
        }
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    

    for (unsigned int indexCube = 0; indexCube < 26; indexCube++){
        float x_=(i_cubes_h[indexCube][0]-littleCubes[indexCube].vertices[0]);
        float y_=i_cubes_h[indexCube][1]-littleCubes[indexCube].vertices[1] ;
        float z_=i_cubes_h[indexCube][2]-littleCubes[indexCube].vertices[2] ;
        vector<float>tmp = {x_/2500,y_/2500,z_/2500};
        animation_c.push_back(tmp);
    }
    
    for (unsigned int indexCube = 0; indexCube < 26; indexCube++){
        float x_=i_cubes_f[indexCube][0]-littleCubes[indexCube].vertices[0] ;
        float y_=i_cubes_f[indexCube][1]-littleCubes[indexCube].vertices[1] ;
        float z_=i_cubes_f[indexCube][2]-littleCubes[indexCube].vertices[2] ;
        vector<float>tmp = {x_/2500,y_/2500,z_/2500};
        animation_f.push_back(tmp);
    }
    for (unsigned int indexCube = 0; indexCube < 26; indexCube++){
        float x_=i_cubes_ucsp[indexCube][0]-littleCubes[indexCube].vertices[0] ;
        float y_=i_cubes_ucsp[indexCube][1]-littleCubes[indexCube].vertices[1] ;
        float z_=i_cubes_ucsp[indexCube][2]-littleCubes[indexCube].vertices[2] ;
        vector<float>tmp = {x_/2500,y_/2500,z_/2500};
        animation_ucsp.push_back(tmp);
    }
    
    for (unsigned int indexCube = 0; indexCube < 26; indexCube++){
        float x_=i_cubes_ani[indexCube][0]-littleCubes[indexCube].vertices[0] ;
        float y_=i_cubes_ani[indexCube][1]-littleCubes[indexCube].vertices[1] ;
        float z_=i_cubes_ani[indexCube][2]-littleCubes[indexCube].vertices[2] ;
        vector<float>tmp = {x_/2500,y_/2500,z_/2500};
        animation_ord.push_back(tmp);
    }
}

bool Cube::ordenar() {
    for (unsigned int indexCube = 0; indexCube < 26; indexCube++){
        translatePoints(littleCubes[indexCube].vertices, i_cubes_ani[indexCube][0]-littleCubes[indexCube].vertices[0], i_cubes_ani[indexCube][1]-littleCubes[indexCube].vertices[1], i_cubes_ani[indexCube][2] -littleCubes[indexCube].vertices[2]);
        Yrotation(littleCubes[indexCube].vertices, 1); // gira en su eje
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    
    return true;

}

bool Cube::corazon() {
    for (unsigned int indexCube = 0; indexCube < 26; indexCube++){
        translatePoints(littleCubes[indexCube].vertices, i_cubes_h[indexCube][0]-littleCubes[indexCube].vertices[0], i_cubes_h[indexCube][1]-littleCubes[indexCube].vertices[1], i_cubes_h[indexCube][2] -littleCubes[indexCube].vertices[2]);
        Yrotation(littleCubes[indexCube].vertices, 1); // gira en su eje
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    return true;

}

void Cube::ani_carita() {
    
    for (unsigned int indexCube = 0; indexCube < 26; indexCube++){
        translatePoints(littleCubes[indexCube].vertices,animation_f[indexCube][0],animation_f[indexCube][1],animation_f[indexCube][2]);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

}
void Cube::ani_corazon() {
    
    for (unsigned int indexCube = 0; indexCube < 26; indexCube++){
        translatePoints(littleCubes[indexCube].vertices,animation_c[indexCube][0],animation_c[indexCube][1],animation_c[indexCube][2]);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

}

void Cube::ani_ucsp(){
    
    for (unsigned int indexCube = 0; indexCube < 26; indexCube++){
        translatePoints(littleCubes[indexCube].vertices,animation_ucsp[indexCube][0],animation_ucsp[indexCube][1],animation_ucsp[indexCube][2]);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

}
void Cube::ani_cube() {
    
    for (unsigned int indexCube = 0; indexCube < 26; indexCube++){
        translatePoints(littleCubes[indexCube].vertices,animation_ord[indexCube][0],animation_ord[indexCube][1],animation_ord[indexCube][2]);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

}

bool Cube::carita() {
    for (unsigned int indexCube = 0; indexCube < 26; indexCube++){
        translatePoints(littleCubes[indexCube].vertices, i_cubes_f[indexCube][0]-littleCubes[indexCube].vertices[0], i_cubes_f[indexCube][1]-littleCubes[indexCube].vertices[1], i_cubes_f[indexCube][2] -littleCubes[indexCube].vertices[2]);
        Yrotation(littleCubes[indexCube].vertices, 1); // gira en su eje
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    return true;

}

bool Cube::ucsp() {
    for (unsigned int indexCube = 0; indexCube < 26; indexCube++){
        translatePoints(littleCubes[indexCube].vertices, i_cubes_ucsp[indexCube][0]-littleCubes[indexCube].vertices[0], i_cubes_ucsp[indexCube][1]-littleCubes[indexCube].vertices[1], i_cubes_ucsp[indexCube][2] -littleCubes[indexCube].vertices[2]);
        Yrotation(littleCubes[indexCube].vertices, 1); // gira en su eje
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    return true;

}

void Cube::moveR(float angle) {
    bool selectedCube = false;
    for (unsigned int indexCube = 0; indexCube < 26; indexCube++)
    {
        for (int i = 0; i < 3; i++) {
            if (littleCubes[indexCube].camadas[i] == 'R') {
                selectedCube = true;
                break;
            }
        }
        if (selectedCube) {
            Zrotation(littleCubes[indexCube].vertices, angle);
            selectedCube = false;
        }
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}

void Cube::moveL(float angle) {
    bool selectedCube = false;
    for (unsigned int indexCube = 0; indexCube < 26; indexCube++)
    {
        for (int i = 0; i < 3; i++) {
            if (littleCubes[indexCube].camadas[i] == 'L') {
                selectedCube = true;
                break;
            }
        }
        if (selectedCube) {
            Zrotation(littleCubes[indexCube].vertices, angle);
            selectedCube = false;
        }
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}

void Cube::moveU(float angle) {
    bool selectedCube = false;
    for (unsigned int indexCube = 0; indexCube < 26; indexCube++)
    {
        for (int i = 0; i < 3; i++) {
            if (littleCubes[indexCube].camadas[i] == 'U') {
                selectedCube = true;
                break;
            }
        }
        if (selectedCube) {
            Yrotation(littleCubes[indexCube].vertices, angle);
            selectedCube = false;
        }
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}

void Cube::moveD(float angle) {
    bool selectedCube = false;
    for (unsigned int indexCube = 0; indexCube < 26; indexCube++)
    {
        for (int i = 0; i < 3; i++) {
            if (littleCubes[indexCube].camadas[i] == 'D') {
                selectedCube = true;
                break;
            }
        }
        if (selectedCube) {
            Yrotation(littleCubes[indexCube].vertices, angle);
            selectedCube = false;
        }
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}

void Cube::moveF(float angle) {
    bool selectedCube = false;
    for (unsigned int indexCube = 0; indexCube < 26; indexCube++)
    {
        for (int i = 0; i < 3; i++) {
            if (littleCubes[indexCube].camadas[i] == 'F') {
                selectedCube = true;
                break;
            }
        }
        if (selectedCube) {
            Xrotation(littleCubes[indexCube].vertices, angle);
            selectedCube = false;
        }
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}

void Cube::moveB(float angle) {
    bool selectedCube = false;
    for (unsigned int indexCube = 0; indexCube < 26; indexCube++)
    {
        for (int i = 0; i < 3; i++) {
            if (littleCubes[indexCube].camadas[i] == 'B') {
                selectedCube = true;
                break;
            }
        }
        if (selectedCube) {
            Xrotation(littleCubes[indexCube].vertices, angle);
            selectedCube = false;
        }
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}

Cube::Cube()
{
    
}

Cube::~Cube()
{
}


