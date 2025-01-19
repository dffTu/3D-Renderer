class Vertex {
public:
    Vertex();
    Vertex(long double aX, long double aY, long double aZ);
    Vertex(const Vertex& aVertex);
    Vertex(Vertex&& aVertex);

    Vertex& operator=(const Vertex& aVertex);
    Vertex& operator=(Vertex&& aVertex);

    long double getX() const;
    long double getY() const;
    long double getZ() const;

private:
    long double x_;
    long double y_;
    long double z_;
};
