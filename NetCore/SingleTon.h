/*  	
 *@file   SingleTon.h
 *@brief  brief  description  
 *@author louyk
 *@date   2017/04/11
 *@version 0.1.0
 *@note   无参数单例模板类
 */
#ifndef NETCORE_SINGLETON_H
#define NETCORE_SINGLETON_H

template <class T>
class SingleTon
{
public:
	/*
	 * @return T*:对象T的实例
	 * @ref    创建一个对象的单例实例
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
	 * @ref     销毁一个对象的单例实例
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
