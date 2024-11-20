#version 450

const int MAX_ITERATIONS = 100;
uniform int u_iterations;

in vec2 position;
out vec4 frag_color;

int mandelbrot_iterations(vec2 c)
{
    vec2 z = vec2(0.0);
    int i;

    // for (i = 0; i < min(iterations, MAX_ITERATIONS); ++i)
    for (i = 0; i < MAX_ITERATIONS; ++i)
    {
        if (dot(z, z) > 4)
        {
            break;
        }

        z = vec2(
            z.x * z.x - z.y * z.y + c.x, // Re
            2 * z.x * z.y + c.y          // Img
        );
    }
    return i;
}

void main()
{
    int iters = mandelbrot_iterations(position);

    float color = float(iters) / float(MAX_ITERATIONS);
    frag_color = vec4(vec3(color), 1.0);

    // frag_color = vec4(1.0, 0.0, 0.0, 1.0);
}