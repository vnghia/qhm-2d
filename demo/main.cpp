#include <SFML/Graphics.hpp>
#include <chrono>
#include <vector>

#include "point.h"
#include "space.h"

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

int main() {
  int x_max = 2;
  int y_max = 2;
  int scale = 500;
  sf::RenderWindow window(sf::VideoMode(x_max * scale, y_max * scale), "QHM");
  sleep(5);

  auto points = std::vector<Point>{{1, 1, 0.1, 1}, {0.5, 1, 0.1, 1}};
  auto space = Space{0, x_max, 0, y_max};
  space.AddPoint(Point{1, 1, 0.1, 1}, 0, 0);
  space.AddPoint(Point{0.5, 1, 0.1, 1}, 0.0000005, 0);
  auto shapes = std::vector<sf::CircleShape>(points.size());
  for (int i = 0; i < space.points.size(); ++i) {
    auto point = space.points[i];
    auto r = point.r(scale);
    shapes[i] = sf::CircleShape{r};
    shapes[i].setOrigin({r, r});
    shapes[i].setFillColor(sf::Color(100, 250, 50));
    shapes[i].setPosition({point.x * scale, point.y * scale});
    shapes[i].setOutlineThickness(-r / 20);
    shapes[i].setOutlineColor(sf::Color(250, 0, 0));
  }

  auto begin = std::chrono::steady_clock::now();
  auto end = begin;

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
    }
    window.clear(sf::Color::Black);
    for (int i = 0; i < shapes.size(); ++i) {
      shapes[i].setPosition(
          {space.points[i].x * scale, space.points[i].y * scale});
      window.draw(shapes[i]);
    }
    window.display();
    end = std::chrono::steady_clock::now();
    auto dt = std::chrono::duration_cast<std::chrono::microseconds>(end - begin)
                  .count();
    space.Update(dt);
    begin = end;
  }

  return 0;
}
