#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cmath>

float interpolate(float a0, float a1, float w)
{
    // return (a1 - a0) * w + a0;
    // return (a1 - a0) * (3.0 - w * 2.0) * w * w + a0;
    return (a1 - a0) * ((w * (w * 6.0 - 15.0) + 10.0) * w * w * w) + a0;
}

float f(float x)
{
    return -16 * x * (x - 0.5);
}
float g(float x)
{
    float w = 2.50775 / sqrt(2 * 3.14159265359) * pow(2.71828182846, -((21.6992 * x - 5.44596) * (21.6992 * x - 5.44596)));
    if (w > 1) { return 1; }
    else { return w; }
}

int main()
{
    srand(1000);
    int window_width = 1200;
    int window_height = 600;
    sf::ContextSettings window_settings;
    window_settings.antialiasingLevel = 16;
    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "SFML works!", sf::Style::Default, window_settings);
    sf::View view;
    view.setSize(window_width, window_height);
    view.setCenter(window_width / 2, window_height / 2);
    int row_length = 20;
    int col_length = 20;
    int grid_length = 50;
    float gradient_vector_length = 20;
    sf::VertexArray horizontal_lines(sf::Lines, (col_length + 1) * 2);
    for (int i = 0; i < col_length; i++)
    {
        horizontal_lines[2 * i].position = sf::Vector2f((window_width - grid_length * row_length) / 2, (window_height - grid_length * col_length) / 2 + grid_length * i);
        horizontal_lines[2 * i].color = sf::Color::Black;
        horizontal_lines[2 * i + 1].position = sf::Vector2f((window_width + grid_length * row_length) / 2, (window_height - grid_length * col_length) / 2 + grid_length * i);
        horizontal_lines[2 * i + 1].color = sf::Color::Black;
    }
    horizontal_lines[2 * col_length].position = sf::Vector2f((window_width - grid_length * row_length) / 2, (window_height - grid_length * col_length) / 2 + grid_length * col_length);
    horizontal_lines[2 * col_length].color = sf::Color::Black;
    horizontal_lines[2 * col_length + 1].position = sf::Vector2f((window_width + grid_length * row_length) / 2, (window_height - grid_length * col_length) / 2 + grid_length * col_length);
    horizontal_lines[2 * col_length + 1].color = sf::Color::Black;
    sf::VertexArray vertical_lines(sf::Lines, (row_length + 1) * 2);
    for (int i = 0; i < row_length; i++)
    {
        vertical_lines[2 * i].position = sf::Vector2f((window_width - grid_length * row_length) / 2 + grid_length * i, (window_height - grid_length * col_length) / 2);
        vertical_lines[2 * i].color = sf::Color::Black;
        vertical_lines[2 * i + 1].position = sf::Vector2f((window_width - grid_length * row_length) / 2 + grid_length * i, (window_height + grid_length * col_length) / 2);
        vertical_lines[2 * i + 1].color = sf::Color::Black;
    }
    vertical_lines[2 * row_length].position = sf::Vector2f((window_width - grid_length * row_length) / 2 + grid_length * row_length, (window_height - grid_length * col_length) / 2);
    vertical_lines[2 * row_length].color = sf::Color::Black;
    vertical_lines[2 * row_length + 1].position = sf::Vector2f((window_width - grid_length * row_length) / 2 + grid_length * row_length, (window_height + grid_length * col_length) / 2);
    vertical_lines[2 * row_length + 1].color = sf::Color::Black;

    sf::VertexArray gradient_vectors(sf::Lines, 2 * (col_length + 1) * (row_length + 1));
    for (int i = 0; i < col_length + 1; i++)
    {
        for (int j = 0; j < row_length + 1; j++)
        {
            gradient_vectors[2 * i * (row_length + 1) + 2 * j].position = sf::Vector2f((window_width - grid_length * row_length) / 2 + grid_length * j, (window_height - grid_length * col_length) / 2 + grid_length * i);
            gradient_vectors[2 * i * (row_length + 1) + 2 * j].color = sf::Color::Red;
            float angle = rand() % 360 * 3.141592653589 / 180;
            sf::Vector2f random_point = sf::Vector2f(cos(angle), sin(angle));
            gradient_vectors[2 * i * (row_length + 1) + 2 * j + 1].position = sf::Vector2f((window_width - grid_length * row_length) / 2 + grid_length * j + gradient_vector_length * random_point.x, (window_height - grid_length * col_length) / 2 + grid_length * i + gradient_vector_length * random_point.y);
            gradient_vectors[2 * i * (row_length + 1) + 2 * j + 1].color = sf::Color::Red;
        }
    }
    sf::VertexArray points(sf::Points, col_length * row_length * grid_length * grid_length);
    for (int i = 0; i < col_length; i++)
    {
        for (int j = 0; j < row_length; j++)
        {
            sf::Vector2f top_left = gradient_vectors[2 * i * (row_length + 1) + 2 * j + 1].position - gradient_vectors[2 * i * (row_length + 1) + 2 * j].position;
            top_left.x /= gradient_vector_length; top_left.y /= gradient_vector_length;
            sf::Vector2f top_right = gradient_vectors[2 * i * (row_length + 1) + 2 * (j + 1) + 1].position - gradient_vectors[2 * i * (row_length + 1) + 2 * (j + 1)].position;;
            top_right.x /= gradient_vector_length; top_right.y /= gradient_vector_length;
            sf::Vector2f bot_left = gradient_vectors[2 * (i + 1) * (row_length + 1) + 2 * j + 1].position - gradient_vectors[2 * (i + 1) * (row_length + 1) + 2 * j].position;;
            bot_left.x /= gradient_vector_length; bot_left.y /= gradient_vector_length;
            sf::Vector2f bot_right = gradient_vectors[2 * (i + 1) * (row_length + 1) + 2 * (j + 1) + 1].position - gradient_vectors[2 * (i + 1) * (row_length + 1) + 2 * (j + 1)].position;;
            bot_right.x /= gradient_vector_length; bot_right.y /= gradient_vector_length;
            float dot_product;
            for (int px = 0; px < grid_length; px++)
            {
                for (int py = 0; py < grid_length; py++)
                {
                    points[(i * row_length + j) * grid_length * grid_length + px * grid_length + py].position = sf::Vector2f((window_width - grid_length * row_length) / 2 + grid_length * j + px, (window_height - grid_length * col_length) / 2 + grid_length * i + py);
                    /*
                    * Without linear interpolation
                    if (px <= grid_length / 2 && py <= grid_length / 2)
                        dot_product = px * top_left.x + py * top_left.y;
                    else if (px > grid_length / 2 && py <= grid_length / 2)
                        dot_product = (px - grid_length) * top_right.x + py * top_right.y;
                    else if (px <= grid_length / 2 && py > grid_length / 2)
                        dot_product = px * bot_left.x + (py - grid_length) * bot_left.y;
                    else
                        dot_product = (px - grid_length) * bot_right.x + (py - grid_length) * bot_right.y;

                    if (dot_product > 0)
                        points[(i * row_length + j) * grid_length * grid_length + px * grid_length + py].color = sf::Color(0, 255, 0, 255 * dot_product / (2 * (floor(grid_length / 2))));
                    else
                        points[(i * row_length + j) * grid_length * grid_length + px * grid_length + py].color = sf::Color(255, 0, 255, -255 * dot_product / (2 * (floor(grid_length / 2))));
                        */
                    // With linear interpolation
                    // dot products
                    float x0, y0, x, y;
                    float D11 = 0, D12 = 0, D21 = 0, D22 = 0;
                    x = (float) px / (grid_length - 1);
                    y = (float) py / (grid_length - 1);
                    float intensity = 1; // between 0 and 1
                    intensity *= sqrt(2);

                    x0 = x, y0 = y;
                    D11 = (x0 * top_left.x + y0 * top_left.y) * intensity;

                    x0 = x, y0 = y - 1;
                    D12 = (x0 * bot_left.x + y0 * bot_left.y) * intensity;

                    x0 = x - 1, y0 = y;
                    D21 = (x0 * top_right.x + y0 * top_right.y) * intensity;

                    x0 = x - 1, y0 = y - 1;
                    D22 = (x0 * bot_right.x + y0 * bot_right.y) * intensity;

                    // interpolations
                    float inter1 = interpolate(D11, D21, x);
                    float inter2 = interpolate(D12, D22, x);
                    float value = interpolate(inter1, inter2, y);
                    // type = 1 and a = 0 is ideal perlin noise
                    int type = 2;
                    if (type == 0)
                    {
                        if (value > 0.5)
                            points[(i * row_length + j) * grid_length * grid_length + px * grid_length + py].color = sf::Color( 255, 0, 0, 255 * (1.5 - value) / 0.5);
                        else if (value > 0)
                            points[(i * row_length + j) * grid_length * grid_length + px * grid_length + py].color = sf::Color(0, 0, 255, 255 * value / 0.5);
                        else if (value > -0.5)
                            points[(i * row_length + j) * grid_length * grid_length + px * grid_length + py].color = sf::Color(255, 255, 0, -255 * value / 0.5);
                        else
                            points[(i * row_length + j) * grid_length * grid_length + px * grid_length + py].color = sf::Color(255, 0, 255, -255 * (-1.5 - value) / 0.5);
                    }
                    else if (type == 1)
                    {
                        float a = 0;
                        if (value > -a)
                            points[(i * row_length + j) * grid_length * grid_length + px * grid_length + py].color = sf::Color(255, 0, 255, 255 * (value + a) / (1 + a));
                        else
                            points[(i * row_length + j) * grid_length * grid_length + px * grid_length + py].color = sf::Color(255, 0, 0, -255 * (value + a) / (1 - a));
                    }
                    else if (type == 2)
                    {
                        if (value > 0.5)
                            points[(i * row_length + j) * grid_length * grid_length + px * grid_length + py].color = sf::Color(255, 0, 0, 255 * f(value - 0.5));
                        else if (value > 0)
                            points[(i * row_length + j) * grid_length * grid_length + px * grid_length + py].color = sf::Color(0, 0, 255, 255 * f(value));
                        else if (value > -0.5)
                            points[(i * row_length + j) * grid_length * grid_length + px * grid_length + py].color = sf::Color(255, 0, 255, 255 * f(-value));
                        else
                            points[(i * row_length + j) * grid_length * grid_length + px * grid_length + py].color = sf::Color(255, 255, 0, 255 * f(-value - 0.5));
                    }
                    else if (type == 3)
                    {
                        if (value > 0.5)
                            points[(i * row_length + j) * grid_length * grid_length + px * grid_length + py].color = sf::Color(255, 0, 0, 255 * g(value - 0.5));
                        else if (value > 0)
                            points[(i * row_length + j) * grid_length * grid_length + px * grid_length + py].color = sf::Color(0, 0, 255, 255 * g(value));
                        else if (value > -0.5)
                            points[(i * row_length + j) * grid_length * grid_length + px * grid_length + py].color = sf::Color(255, 0, 255, 255 * g(-value));
                        else
                            points[(i * row_length + j) * grid_length * grid_length + px * grid_length + py].color = sf::Color(255, 255, 0, 255 * g(-value - 0.5));
                    }
                }
            }
        }
    }

    bool lines_state = false;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::Resized)
            {
                view.setSize(event.size.width, event.size.height);
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::F)
                    lines_state = !lines_state;
            }
        }

        window.setView(view);
        window.clear(sf::Color::White);
        window.draw(points);
        if (lines_state)
        {
            window.draw(horizontal_lines);
            window.draw(vertical_lines);
            window.draw(gradient_vectors);
        }
        window.display();
    }

    return 0;
}