#pragma once
#include"Renderer.h"

class Texture
{
private:
	unsigned int m_RendererID;
	std::string m_FilePaht;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Heght, m_BPP;

public:
	Texture(const std::string& path);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	inline int GetWigth() const { return m_Width; };
	inline int GetHeght() const { return m_Heght; };

};