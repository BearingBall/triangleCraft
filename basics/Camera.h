#ifndef CAMERA_H
#define CAMERA_H
#include <QMatrix4x4>
#include <QQuaternion>

class Camera final
{
public:
    Camera();
    ~Camera() = default;

    QMatrix4x4 getPerspective();
    QMatrix4x4 getView();
    QVector3D getPos();
    void rotate(float upDown, float leftRight);
    void step(float forwBack, float leftRight);
    void verticalStrafe(float step);

    QVector3D getPosBesideScreen(float farness);

    QVector3D getCenter();
    QVector3D getEye();
    QVector3D getHead();
    QVector3D getRight();
private:
    QVector3D center;
    QVector3D eyeLaser;
    QVector3D headDir;
    QVector3D rightDir;

};

inline Camera::Camera()
{
    center = QVector3D(0,0,0);
    eyeLaser = QVector3D(0,0,-1);
    headDir = QVector3D(0,1,0);
    rightDir = QVector3D(1,0,0);
}

inline QMatrix4x4 Camera::getPerspective()
{
    QMatrix4x4 perspective;
    perspective.perspective(60.0f, 4.0f/3.0f, 0.1f, 100.0f);
    return perspective;
}

inline QMatrix4x4 Camera::getView()
{
    QMatrix4x4 view;
    view.lookAt(center, center+eyeLaser, headDir);
    return view;
}

inline QVector3D Camera::getPos()
{
    return center;
}

inline void Camera::rotate(float upDown, float leftRight)
{
    QQuaternion rotateLeftRight = QQuaternion::fromAxisAndAngle(QVector3D(0,1,0), leftRight);
    QQuaternion rotateUpDown = QQuaternion::fromAxisAndAngle(rightDir, upDown);
    QVector3D tmpHead = rotateLeftRight * rotateUpDown * headDir;
    if (tmpHead.y() > 0)
    {
        eyeLaser = rotateLeftRight * rotateUpDown * eyeLaser;
        headDir = rotateLeftRight * rotateUpDown * headDir;
        rightDir = rotateLeftRight * rotateUpDown * rightDir;
    }
    else
    {
        eyeLaser = rotateLeftRight * eyeLaser;
        headDir = rotateLeftRight * headDir;
        rightDir = rotateLeftRight * rightDir;
    }
}

inline void Camera::step(float forwBack, float leftRight)
{
    center = center + eyeLaser*forwBack;
    center = center + rightDir*leftRight;
}

inline void Camera::verticalStrafe(float step)
{
    center = center + QVector3D(0, step, 0);
}

inline QVector3D Camera::getPosBesideScreen(float farness)
{
    return center + eyeLaser*farness;
}

inline QVector3D Camera::getCenter()
{
    return center;
}

inline QVector3D Camera::getEye()
{
    return eyeLaser;
}

inline QVector3D Camera::getHead()
{
    return headDir;
}

inline QVector3D Camera::getRight()
{
    return rightDir;
}

#endif // CAMERA_H
