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


	//TODO: user-defined objects
	// https://fmt.dev/latest/api.html#udt
}

/**
 * 调试模式将 DEBUGMODEL 设置为1，即可打印时，带有文件名-函数名-行号格式
 * 设置为0时，即关闭调试模式，不会输出文件名等用户不必要信息
 */
#define DEBUGMODEL 1
#if DEBUGMODEL
#define VVLOGGER_CALL(logger, level, ...) (logger)->log(vv::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, level, __VA_ARGS__)

#define VLOGGER_TRACE(logger, ...) VVLOGGER_CALL(logger, vv::level::trace, __VA_ARGS__)
#define VTRACE(...) VLOGGER_TRACE(vv::vlogger::instance().vGetLogger(), __VA_ARGS__)

#define VLOGGER_DEBUG(logger, ...) VVLOGGER_CALL(logger, vv::level::debug, __VA_ARGS__)
#define VDEBUG(...) VLOGGER_DEBUG(vv::vlogger::instance().vGetLogger(), __VA_ARGS__)

#define VLOGGER_INFO(logger, ...) VVLOGGER_CALL(logger, vv::level::info, __VA_ARGS__)
#define VINFO(...) VLOGGER_INFO(vv::vlogger::instance().vGetLogger(), __VA_ARGS__)

#define VLOGGER_WARN(logger, ...) VVLOGGER_CALL(logger, vv::level::warn, __VA_ARGS__)
#define VWARN(...) VLOGGER_WARN(vv::vlogger::instance().vGetLogger(), __VA_ARGS__)

#define VLOGGER_ERROR(logger, ...) VVLOGGER_CALL(logger, vv::level::err, __VA_ARGS__)
#define VERROR(...) VLOGGER_ERROR(vv::vlogger::instance().vGetLogger(), __VA_ARGS__)

#define VLOGGER_CRITICAL(logger, ...) VVLOGGER_CALL(logger, vv::level::critical, __VA_ARGS__)
#define VCRITICAL(...) VLOGGER_CRITICAL(vv::vlogger::instance().vGetLogger(), __VA_ARGS__)

#else
#define VVLOGGER_CALL(logger, level, ...) (logger)->log(level, __VA_ARGS__)

#define VLOGGER_TRACE(logger, ...) VVLOGGER_CALL(logger, vv::level::trace, __VA_ARGS__)
#define VTRACE(...) VLOGGER_TRACE(vv::vlogger::instance().vGetLogger(), __VA_ARGS__)

#define VLOGGER_DEBUG(logger, ...) VVLOGGER_CALL(logger, vv::level::debug, __VA_ARGS__)
#define VDEBUG(...) VLOGGER_DEBUG(vv::vlogger::instance().vGetLogger(), __VA_ARGS__)

#define VLOGGER_INFO(logger, ...) VVLOGGER_CALL(logger, vv::level::info, __VA_ARGS__)
#define VINFO(...) VLOGGER_INFO(vv::vlogger::instance().vGetLogger(), __VA_ARGS__)

#define VLOGGER_WARN(logger, ...) VVLOGGER_CALL(logger, vv::level::warn, __VA_ARGS__)
#define VWARN(...) VLOGGER_WARN(vv::vlogger::instance().vGetLogger(), __VA_ARGS__)

#define VLOGGER_ERROR(logger, ...) VVLOGGER_CALL(logger, vv::level::err, __VA_ARGS__)
#define VERROR(...) VLOGGER_ERROR(vv::vlogger::instance().vGetLogger(), __VA_ARGS__)

#define VLOGGER_CRITICAL(logger, ...) VVLOGGER_CALL(logger, vv::level::critical, __VA_ARGS__)
#define VCRITICAL(...) VLOGGER_CRITICAL(vv::vlogger::instance().vGetLogger(), __VA_ARGS__)
#endif