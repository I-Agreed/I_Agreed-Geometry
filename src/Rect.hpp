#pragma once
#include <algorithm>
#include "Vector2.hpp"

namespace IA::geo {

    template <typename T>
    struct Rect {

        Vector2<T> p1; // Top Left point
        Vector2<T> p2; // Bottom Right point

        Rect<T>() { // Blank Constructor
            p1 = Vector2<T>(0, 0);
            p2 = Vector2<T>(0, 0);
        }

        Rect<T>(T x1, T y1, T x2, T y2) { // Construct from Coords, x2 and y2 are not width and height
            p1 = Vector2<T>(x1, y1);
            p2 = Vector2<T>(x2, y2);
        }

        Rect<T>(Vector2<T> _p1, Vector2<T> _p2) { // Construct from 2 Vectors
            p1 = _p1;
            p2 = _p2;
        }

        Rect<T>(T x2, T y2) { // Construct from single set of Coords, with p1 = 0, 0
            p2 = Vector2<T>(x2, y2);
        }

        Rect<T>(Vector2<T> _p2) { // Construct from single Vector
            p2 = _p2;
        }

        bool operator ==(Rect<T> other) {
            return other.p1 == p1 && other.p2 == p2;
        }

        bool operator !=(Rect<T> other) {
            return other.p2 != p1 || other.p2 != p2;
        }

        // Returns Width, x2 - x1
        double width() {
            return (p2 - p1).x;
        }

        // Returns Height, y2 - y1
        double height() {
            return (p2 - p1).y;
        }
        
        // Returns Area, Width * Height
        double area() {
            return width() * height();
        }

        // Returns True if the point is inside the rectangle (or on the edge)
        bool contains(Vector2<T> p) {
            return p.x >= p1.x && p.x <= p2.x && p.y >= p1.y && p.y <= p2.y;
        }

        // Returns True if the two rectangles intersect, excluding if they share an edge
        bool intersect(Rect<T> other) {
            // Left x, Right x, Top y, Bottom y
            double lx = std::max(std::min(p1.x, p2.x), std::min(other.p1.x, other.p2.x));
            double rx = std::min(std::max(p1.x, p2.x), std::max(other.p1.x, other.p2.x));
            double ty = std::max(std::min(p1.y, p2.y), std::min(other.p1.y, other.p2.y));
            double by = std::min(std::max(p1.y, p2.y), std::max(other.p1.y, other.p2.y));
            return lx < rx && ty < by;
        }

        // Returns the intersection of two rectangles (doesn't check if they actually intersect)
        Rect<T> intersection(Rect<T> other) {
            double lx = std::max(std::min(p1.x, p2.x), std::min(other.p1.x, other.p2.x));
            double rx = std::min(std::max(p1.x, p2.x), std::max(other.p1.x, other.p2.x));
            double ty = std::max(std::min(p1.y, p2.y), std::min(other.p1.y, other.p2.y));
            double by = std::min(std::max(p1.y, p2.y), std::max(other.p1.y, other.p2.y));
            return Rect(lx, ty, rx, by);
        }

        // Returns a new rectangle that is translated by an amount
        Rect<T> transform(Vector2<T> shift) {
            return Rect(p1 + shift, p2 + shift);
        }

        template <typename C>
        operator Rect<C>() {
            return Rect<C>(p1.x, p1.y, p2.x, p2.y);
        }

        #ifdef SFML_SYSTEM_HPP // convert to SFML Rectangle
        template <typename C>
        operator sf::Rect<C>() {
            return sf::Rect<C>(p1, p2);
        }

        //Converting Constructor
        template <typename C>
        Rect<T>(sf::Rect<C> a) {
            p1 = Vector2<T>(a.left, a.top);
            p2 = Vector2<T>(a.left + a.width, a.top + a.height);
        }
        #endif
    };
}