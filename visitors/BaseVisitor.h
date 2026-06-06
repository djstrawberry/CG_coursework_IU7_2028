#ifndef BASE_VISITOR_H
#define BASE_VISITOR_H

class CelestialBody;
class Composite;
class BaseCamera;

class BaseVisitor {
public:
    BaseVisitor() = default;
    virtual ~BaseVisitor() = default;

    virtual void visitCelestialBody(CelestialBody& body) = 0;
    virtual void visitComposite(Composite& comp) = 0;
    virtual void visitCamera(BaseCamera& camera) = 0;
};

#endif // BASE_VISITOR_H
