#pragma once



#include "Camera.h"



class CameraManager {
private:
	Camera *        m_CurrentCamera;


public:
	static CameraManager * Get();

	void            SetCamera(Camera * _camera);
	Camera *        GetCamera();
};
