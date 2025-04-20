#include <iostream>
#include <sstream>
#include <vector>
#include <memory>
#include <cmath>
#include <iomanip>
using namespace std;

template <typename CONTAINER, typename FUNC>
auto map_join(const CONTAINER& c, FUNC f, const string& sep = ", ") {
    stringstream ss;
    for (auto it = c.begin(); it != c.end(); ++it) {
        ss << (it != c.begin() ? sep : "");
        ss << f(*it);
    }
    return ss.str();
}

struct Shape{ //principal base isso dai q sena disse
    virtual double getArea() const = 0;
    virtual double getPerimeter() const = 0;
    virtual string getName() const = 0;
    virtual string toString() const = 0;
    virtual ~Shape() {}
};

struct Point2D
{
    double x, y;
    Point2D(double x = 0, double y = 0) : x(x), y(y) {}
    string toString() const{
        stringstream ss;
        ss << fixed << setprecision(2)
        << "(" << x << ", " << y << ")";
        return ss.str();
    }
};

struct Circle : Shape{
    string name;
    Point2D center;
    double radius;
    Circle( Point2D center = Point2D(), double radius = 0)
        : name("Circ"), center(center), radius(radius) {}
    virtual string getName() const override { return name; }
    virtual double getArea() const override{ return M_PI * radius * radius; }
    virtual double getPerimeter() const override{ return 2 * M_PI * radius; }
    virtual string toString() const override{
        stringstream ss;
        ss << name << ": C=" << center.toString() << ", R=" << fixed << setprecision(2) << radius;
        return ss.str();
    }

};
struct Rectangle : Shape{
    string name;
    Point2D p1, p2;
    Rectangle(Point2D p1 = Point2D(), Point2D p2 = Point2D())
        : name("Rect"), p1(p1), p2(p2) {}
    virtual string getName() const override { return name; }
    virtual double getArea() const override{
        double width = abs(p1.x - p2.x);
        double height = abs(p1.y - p2.y);
        return width * height;
    }
    virtual double getPerimeter() const override{
        double width = abs(p1.x - p2.x);
        double height = abs(p1.y - p2.y);
        return 2 * (width + height);
    }
    virtual string toString() const override{
        stringstream ss;
        ss << name << ": P1=" << p1.toString() << " P2=" << p2.toString();
        return ss.str();
    }

};



//teste teste teste
int main() {
    vector<shared_ptr<Shape>> shapes;
    while (true) {
        string line, cmd;
        getline(cin, line);
        cout << "$" << line << endl;

        stringstream ss(line);
        ss >> cmd;

        if (cmd == "end")  { 
            break;                                  
        }
        else if (cmd == "show") { 
            // Imprima as formas, uma por linha
            for(auto& shape : shapes){
                cout << shape->toString() << endl;
            }

        }
        else if (cmd == "circle") { 
            // Crie um novo circulo e adicione ao vetor
             double x{}, y{}, radius{};
             ss >> x >> y >> radius;
             shapes.push_back(make_shared<Circle>(Point2D(x, y), radius));
        }
        else if (cmd == "rect") {
            // Crie um retangulo e insira no vetor
             double x1{}, y1{}, x2{}, y2{};
             ss >> x1 >> y1 >> x2 >> y2;
             shapes.push_back(make_shared<Rectangle>(Point2D(x1, y1), Point2D(x2, y2)));
        }
        else if (cmd == "info") {
            // Imprima as informações de área e perímetro de todas as formas
            for(auto& shape: shapes){
                cout << shape->getName() << ": A=" << fixed << setprecision(2)
                << shape->getArea() << " P=" << fixed << setprecision(2) <<
                shape->getPerimeter() << endl;
            }
        }
        else {
            cout << "fail: comando inválido" << '\n';
        }
    }
}
