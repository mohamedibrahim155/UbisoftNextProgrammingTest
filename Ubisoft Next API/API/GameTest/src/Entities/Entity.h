#pragma once
#include <string>
class CEntity
{
public:
	CEntity();
	virtual ~CEntity();
	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void OnDestroy() = 0;
	virtual void Clean() = 0;
	virtual void Render() = 0;
	virtual void Destroy();
	virtual void CopyFromOther(CEntity* entity);

	void InitializeEntity(CEntity* entity);
	
	std::string m_entityID = "unknown";
	bool m_isEnabled = true;
};

