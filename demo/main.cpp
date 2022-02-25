#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <vector>

#include "point.h"
#include "space.h"

#define SPF 1 / 30

int main() {
  int x_max = 2;
  int y_max = 2;
  int scale = 500;
  sf::RenderWindow window(sf::VideoMode(x_max * scale, y_max * scale), "QHM");
  window.setVerticalSyncEnabled(true);

  auto space = Space{0, (float)x_max, 0, (float)y_max};
  space.AddPoint(Point{1, 1, 0.2, 1}, Coord{0.3, 0.35});
  space.AddPoint(Point{1, 1.1, 0.1, 1}, Coord{0.9, 0});
  space.AddPoint(Point{1.7, 1.1, 0.1, 1}, Coord{0.9, 0.75});
  space.AddPoint(Point{1.75, 0.3, 0.1, 1}, Coord{1.9, 0.8});

  auto shapes = std::vector<sf::CircleShape>(space.Size());
  for (int i = 0; i < space.Size(); ++i) {
    auto point = space[i];
    auto r = point.r() * scale;
    shapes[i] = sf::CircleShape{r};
    shapes[i].setOrigin({r, r});
    shapes[i].setFillColor(sf::Color(100, 250, 50));
    shapes[i].setPosition({point.coord.x * scale, point.coord.y * scale});
    shapes[i].setOutlineThickness(-r / 20);
    shapes[i].setOutlineColor(sf::Color(250, 0, 0));
  }

  sf::Clock clock;
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
    }
    window.clear(sf::Color::Black);
    for (int i = 0; i < shapes.size(); ++i) {
      shapes[i].setPosition(
          {space[i].coord.x * scale, space[i].coord.y * scale});
      window.draw(shapes[i]);
    }
    window.display();
    space.Update(clock.restart().asSeconds());
  }

  return 0;
}
