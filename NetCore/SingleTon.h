/*  	
 *@file   SingleTon.h
 *@brief  brief  description  
 *@author louyk
 *@date   2017/04/11
 *@version 0.1.0
 *@note   �޲�������ģ����
 */
#ifndef NETCORE_SINGLETON_H
#define NETCORE_SINGLETON_H

template <class T>
class SingleTon
{
public:
	/*
	 * @return T*:����T��ʵ��
	 * @ref    ����һ������ĵ���ʵ��
	 * @see    destory
	 * @note   SingleTon<UpdataXml>::ins()->praseXmlFile("updatalist.xml");
	 */
	static T* ins()
	{
		if (m_pIns == 0)
		{
			m_pIns = new T();
		}

		return m_pIns;
	}

	/*
	 * @return 
	 * @ref     ����һ������ĵ���ʵ��
	 * @see    ins
	 * @note   SingleTon<UpdataXml>::destory();
	 */
	static void destory()
	{
		delete m_pIns;
		m_pIns = 0;
	}

private:
	SingleTon(){}
	~SingleTon(){}

private:
	static T* m_pIns;
};

template <class T> T* SingleTon<T>::m_pIns = 0;

#endif // NETCORE_SINGLETON_H
