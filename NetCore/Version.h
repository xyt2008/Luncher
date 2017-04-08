/************************************************************
  Copyright (C), 2014-2017, SSIT Tech. Co., Ltd.
  �ļ���: Version.h
  ����: louyk
  �汾: V0.1.0
  ����: 2017/03/30
  ģ������:�汾����
  ��ʷ�޸ļ�¼:
  1��
***********************************************************/
#ifndef NETCORE_VERSION_H
#define NETCORE_VERSION_H
#include <string>
#include <stdio.h>

#define NETCORE_MAJOR_VERSION    0
#define NETCORE_MINOR_VERSION    1
#define NETCORE_PATCH_VERSION    0

class NETCORE_EXPORT Version
{
public:
	static const std::string getProjectVersion()
	{
		static char version[32];
		static int versionInit = 1;
		if (versionInit)
		{
			sprintf_s(version, "%d.%d.%d", NETCORE_MAJOR_VERSION, NETCORE_MINOR_VERSION, NETCORE_PATCH_VERSION);

			versionInit = 0;
		}

		return version;
	}
};

#endif // NETCORE_VERSION_H
