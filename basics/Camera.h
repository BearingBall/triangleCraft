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
    void rotate(float upDown, float leftRight);
    void step(float forwBack, float leftRight);

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

inline void Camera::rotate(float upDown, float leftRight)
{
    QQuaternion rotateLeftRight = QQuaternion::fromAxisAndAngle(QVector3D(0,1,0), leftRight);
    QQuaternion rotateUpDown = QQuaternion::fromAxisAndAngle(rightDir, upDown);
    eyeLaser = rotateLeftRight * rotateUpDown * eyeLaser;
    headDir = rotateLeftRight * rotateUpDown * headDir;
    rightDir = rotateLeftRight * rotateUpDown * rightDir;
}

inline void Camera::step(float forwBack, float leftRight)
{
    center = center + eyeLaser*forwBack;
    center = center + rightDir*leftRight;
}

#endif // CAMERA_H