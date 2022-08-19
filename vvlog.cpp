#include "vvlog.h"
#include "spdlog/sinks/sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include <iostream>
#include <vector>

void vv::vlogger::vSetLevel(vvLevel l)
{
	mLogger->set_level(l);
}

void vv::vlogger::vSetFlush(vvLevel l)
{
	mLogger->flush_on(l);

}

vv::vlogger& vv::vlogger::instance()
{
	static vlogger v;
	return v;
}

vv::vlogger::vlogger()
{
	try {
		auto getLogger = spdlog::get("file_logger");
		if (getLogger == nullptr)
		{
			std::vector<spdlog::sink_ptr> sinks;
			sinks.push_back(std::make_shared<spdlog::sinks::stderr_color_sink_mt>());
			//创建一个循环文件日志 最大5MB和3个文件
			sinks.push_back(std::make_shared<spdlog::sinks::rotating_file_sink_mt>("vvlog.txt", 1048576 * 5, 3));
			mLogger =
				std::make_shared<spdlog::logger>("vvlog", std::begin(sinks), std::end(sinks));
			//注册全局
			spdlog::register_logger(mLogger);
		}
		else
		{
			mLogger = getLogger;
		}

	}
	catch (const spdlog::spdlog_ex& ex)
	{
		std::cout << "Log initialization failed: " << ex.what() << std::endl;
	}
}
