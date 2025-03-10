#pragma once

class UIButton : public sf::Drawable {
public:
  // Constructor that takes position, size, text, and colors
  UIButton(const sf::Vector2f &position, float width, float height,
           const std::string &text, const std::string &fontPath)
      : width(width), height(height) {

    button.setSize({width, height});
    button.setPosition(position);
    button.setFillColor(sf::Color(20, 82, 36)); // Default color
    //
    if (!font.loadFromFile(fontPath)) {
      throw std::runtime_error("Failed to load font");
    }

    buttonText.setFont(font);
    buttonText.setString(text);
    buttonText.setCharacterSize(20);
    buttonText.setFillColor(sf::Color::White);

    // Center text on button
    centerText();
  }

  // Check if a point (like mouse position) is inside the button
  bool contains(const sf::Vector2f &point) const {
    return button.getGlobalBounds().contains(point);
  }

  // Setters for customization
  void setPosition(const sf::Vector2f &position) {
    button.setPosition(position);
    centerText();
  }

  void setText(const std::string &text) {
    buttonText.setString(text);
    centerText();
  }

  void setFillColor(const sf::Color &color) { button.setFillColor(color); }

private:
  void centerText() {
    // Center the text on the button
    sf::FloatRect textBounds = buttonText.getLocalBounds();
    buttonText.setPosition(
        button.getPosition().x + (width - textBounds.width) / 2.0f,
        button.getPosition().y + (height - textBounds.height) / 2.0f -
            textBounds.top);
  }

  virtual void draw(sf::RenderTarget &target,
                    sf::RenderStates states) const override {
    target.draw(button, states);
    target.draw(buttonText, states);
  }

  sf::RectangleShape button;
  sf::Text buttonText;
  sf::Font font;

  const float width;
  const float height;
};
