#pragma once
/*****************************************************************//**
 * \file   vvlog.h
 * \brief  日志库封装
 * 
 * \author Listening
 * \date   August 2022
 *********************************************************************/
#include "spdlog/spdlog.h"
#include <memory>

namespace vv {
	using namespace spdlog;
	using vvLevel = spdlog::level::level_enum;

	/**
	 * @brief vlogger 单例日志类.
	 */
	class vlogger
	{
	public:
		/**
		 * @brief 设置显示日志等级.
		 * level: trace,debug,info,warn,err,critical,off,n_levels
		 * \param l
		 */
		void vSetLevel(vvLevel l);
		/**
		 * @brief 设置日志文件刷新条件.
		 * 遇到level级别，立马将缓存的buffer写到日志文件中
		 * level: trace,debug,info,warn,err,critical,off,n_levels
		 * \param l
		 */
		void vSetFlush(vvLevel l);
		/**
		 * 获取日志句柄执行更多操作.
		 * 
		 * \return 
		 */
		std::shared_ptr<logger> vGetLogger()
		{
			return this->mLogger;
		}
	public:
		static vlogger& instance();
		std::shared_ptr<spdlog::logger> mLogger;
	private:
		vlogger();
	};

	//仅打印到控制台
	/**
	 * vv::info()
	 * vv::warn()
	 * vv::error()
	 * vv::critical()
	 * vv::trace()
	 * vv::debug()
	 */

	//同时输出到控制台和文件
	template<typename... Args>
	inline void vvTrace(string_view_t fmt, const Args &... args)
	{
		vlogger::instance().mLogger->trace(fmt, args...);
	}

	template<typename... Args>
	inline void vvDebug(string_view_t fmt, const Args &... args)
	{
		vlogger::instance().mLogger->debug(fmt, args...);
	}

	template<typename... Args>
	inline void vvInfo(string_view_t fmt, const Args &... args)
	{
		vlogger::instance().mLogger->info(fmt, args...);
	}

	template<typename... Args>
	inline void vvWarn(string_view_t fmt, const Args &... args)
	{
		vlogger::instance().mLogger->warn(fmt, args...);
	}

	template<typename... Args>
	inline void vvError(string_view_t fmt, const Args &... args)
	{
		vlogger::instance().mLogger->error(fmt, args...);
	}

	template<typename... Args>
	inline void vvCritical(string_view_t fmt, const Args &... args)
	{
		vlogger::instance().mLogger->critical(fmt, args...);
	}

	template<typename T>
	void vvTrace(const T& msg)
	{
		vlogger::instance().mLogger->trace(msg);
	}

	template<typename T>
	void vvDebug(const T& msg)
	{
		vlogger::instance().mLogger->debug(msg);
	}

	template<typename T>
	void vvInfo(const T&& msg)
	{
		vlogger::instance().mLogger->info(msg);
	}

	template<typename T>
	void vvWarn(const T& msg)
	{
		vlogger::instance().mLogger->warn(msg);
	}

	template<typename T>
	void vvError(const T& msg)
	{
		vlogger::instance().mLogger->error(msg);
	}

	template<typename T>
	void vvCritical(const T& msg)
	{
		vlogger::instance().mLogger->critical(msg);
	}

	/**
	 * @brief 设置全局日志等级.
	 */
	void vvSetGlobalLevel(vvLevel l);


	//TODO: func(Args &&) 
	//TODO: user-defined objects
	// https://fmt.dev/latest/api.html#udt
	//template<typename... Args>
	//void info(format_string_t<Args...> fmt, Args &&... args)
	//{
	//	log(level::info, fmt, std::forward<Args>(args)...);
	//}
}
