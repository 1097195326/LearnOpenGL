
#include "CameraManager.h"


CameraManager * CameraManager::Get()
{
	static CameraManager m;
	return &m;
}
void CameraManager::SetCamera(Camera *_camera)
{
	m_CurrentCamera = _camera;
}
Camera * CameraManager::GetCamera()
{
	return m_CurrentCamera;
}
