#pragma once
#include "Asset.h"
#include "graphics_device_interface.h"
#include "EmawEngine.h"


class ShaderAsset : public Asset
{
public:
	ShaderStruct Shaders;
	ShaderAsset(void* gdi);
	~ShaderAsset();
	void* load(std::string);
	void* getData();
	bool unload();

private:
	int	getShaderType(char*);
	void* gInterface;
};

