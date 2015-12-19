#ifndef STATE_HPP_
#define STATE_HPP_

struct State {
    float x, y, radius, r, g, b, a;

    State(float x, float y, float radius,
          float r, float g, float b, float a):
        x(x), y(y), radius(radius),
        r(r), g(g), b(b), a(a)
    {}
};

State operator+(const State &s1,
                const State &s2)
{
    return State(s1.x + s2.x,
                 s1.y + s2.y,
                 s1.radius + s2.radius,
                 s1.r + s2.r,
                 s1.g + s2.g,
                 s1.b + s2.b,
                 s1.a + s2.a);
}

State operator-(const State &s1,
                const State &s2)
{
    return State(s1.x - s2.x,
                 s1.y - s2.y,
                 s1.radius - s2.radius,
                 s1.r - s2.r,
                 s1.g - s2.g,
                 s1.b - s2.b,
                 s1.a - s2.a);
}

State operator*(const State &state, const float factor)
{
    return State(state.x * factor,
                 state.y * factor,
                 state.radius * factor,
                 state.r * factor,
                 state.g * factor,
                 state.b * factor,
                 state.a * factor);
}

std::ostream &operator<<(std::ostream &os, const State &state)
{
    os << "("
       << state.x << ", "
       << state.y << ", "
       << state.radius << ", "
       << state.r << ", "
       << state.g << ", "
       << state.b << ", "
       << state.a
       << ")";
    return os;
}

sf::CircleShape stateToCircle(const State &state)
{
    sf::CircleShape circle(state.radius);
    circle.setFillColor(sf::Color(state.r, state.g, state.b, state.a));
    circle.setPosition(state.x - state.radius / 2.0f, state.y - state.radius / 2.0f);
    return circle;
}

#endif  // STATE_HPP_
