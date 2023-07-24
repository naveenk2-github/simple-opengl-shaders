/* Write a simple C based shader code to convert srgb colorspace to bt2020 using opengl. 

To convert sRGB colorspace to BT.2020 colorspace using OpenGL, you can use a fragment shader to apply the colorspace conversion matrix to each pixel during rendering. Below is a simple C-based OpenGL code that demonstrates how to perform the sRGB to BT.2020 colorspace conversion:*/

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

const char* vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec2 aPos;\n"
                                 "layout (location = 1) in vec2 aTexCoord;\n"
                                 "out vec2 TexCoord;\n"
                                 "void main()\n"
                                 "{\n"
                                 "    gl_Position = vec4(aPos, 0.0, 1.0);\n"
                                 "    TexCoord = vec2(aTexCoord.x, 1.0 - aTexCoord.y);\n"
                                 "}\0";

const char* fragmentShaderSource = "#version 330 core\n"
                                   "in vec2 TexCoord;\n"
                                   "out vec4 FragColor;\n"
                                   "uniform sampler2D textureImage;\n"
                                   "const mat3 sRGBtoBT2020Matrix = mat3(1.7166511880, -0.3556707838, -0.2533662814,\n"
                                   "                                    -0.6666843518, 1.6164812366,  0.0157685458,\n"
                                   "                                    0.0176398574, -0.0427706133,  0.9421031212);\n"
                                   "void main()\n"
                                   "{\n"
                                   "    vec3 color = texture(textureImage, TexCoord).rgb;\n"
                                   "    FragColor = vec4(sRGBtoBT2020Matrix * color, 1.0);\n"
                                   "}\0";

int main()
{
    // Initialize GLFW and create a window

    // Initialize GLEW

    // Load the image as a texture (you should have a texture ID)

    // Create and compile the vertex shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Create and compile the fragment shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Create the shader program and link the shaders
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Delete the shaders as they are linked to the program and no longer needed
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Set up vertex data (a quad covering the entire screen) and vertex attributes
    // ...

    // Render loop
    while (!glfwWindowShouldClose(window))
    {
        // Clear the screen
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Use the shader program
        glUseProgram(shaderProgram);

        // Bind the texture (use your texture ID)
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);

        // Set the uniform for the texture sampler
        glUniform1i(glGetUniformLocation(shaderProgram, "textureImage"), 0);

        // Draw the quad
        // ...

        // Swap buffers and poll for events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean up and terminate
    // ...

    return 0;
}


/* In this code, the fragment shader takes the texture coordinates (aTexCoord), looks up the color of the pixel in the texture, and applies the sRGB to BT.2020 colorspace conversion using the sRGB to BT.2020 conversion matrix. The resulting color is then assigned to the output color (FragColor).

Please note that this is a simple example for converting colorspace from sRGB to BT.2020, and in a real application, you may want to implement more sophisticated colorspace conversion algorithms based on your specific requirements. Additionally, proper handling of shader compilation errors, setting up vertex data, and managing resources should be done in a real-world scenario.*/
