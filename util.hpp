#pragma once
#include <cstdlib>
#include <stdint.h>
#include <iostream>
#include <unordered_map>
#include <fstream>
#include <vector>
#include <string>
#include <sys/time.h>
#include <boost/algorithm/string.hpp>

////////////////////////////////////
// 准备一个时间戳获取工具
///////////////////////////////////
class TimeUtil {
public:
    // 获取当前的时间戳
    static int64_t TimeStamp() {
        struct timeval tv;
        ::gettimeofday(&tv , NULL);// 获得精确度为秒级的时间戳
        return  tv.tv_sec;
    }
    static int64_t TimeStampMS() { // 获取精确度为毫秒级的时间戳
        struct timeval tv;
        ::gettimeofday(&tv , NULL);// 获得精确度为秒级的时间戳
        return  tv.tv_sec * 1000 + tv.tv_usec / 1000;
    }
};

///////////////////////////////////
// 打印日志的工具
///////////////////////////////////

// 日志输出格式：
// [I1554675265 util.hpp:29] hello
// [W1554675265 util.hpp:29] hello
// [E1554675265 util.hpp:29] hello
// [F1554675265 util.hpp:29] hello
// 日志使用方式：LOG(INFO) << "hello" << "\n";
// 日志级别：FATAL 致命的；ERROR 错误；WARNING 警告；INFO 提示.

enum Level {
    INFO,
    WARNING,
    ERROR,
    FATAL,
};

inline std::ostream& Log(Level level , const std::string& file_name , int line_num) {
    std::string prefix = "[";
    if (level == INFO) {
        prefix += "I";
    } else if (level == WARNING) {
        prefix += "W";
    } else if (level == ERROR) {
        prefix += "E";
    } else if (level == FATAL) {
        prefix += "F";
    }
    prefix += std::to_string(TimeUtil::TimeStamp());
    prefix += " ";
    prefix += file_name;
    prefix += ";";
    prefix += std::to_string(line_num);
    prefix += "] ";
    std::cout << prefix;
    return std::cout;
}

#define LOG(level) Log(level , __FILE__ , __LINE__)

/////////////////////////////////////
// 准备文件相关工具类
/////////////////////////////////////

class FileUtil {
public:
    // 传入一个文件路径，把文件的所有内容都读出来放到 content 字符串中
    static bool Read(const std::string& file_path , std::string* content) {
        content->clear();
        std::ifstream file(file_path.c_str());
        if (!file.is_open()) {
            return false;
        } 
        std::string line;
        while(std::getline(file , line)) {
            *content += line + "\n";
        }
        file.close();
        return true;
    }

    static bool Write(const std::string& file_path , const std::string& content) {
        std::ofstream file(file_path.c_str());
        if (!file.is_open()) {
            return false;
        }
        file.write(content.c_str() , content.size());
        file.close();
        return true;
    }
};

//////////////////////////////////////
// URL / body 解析模块
//////////////////////////////////////

// 字符串切分？
// 1.strtok()
// 2.stringstream
// 3.boost split 函数
class StringUtil {
public:
    static void Split(const std::string& input , const std::string& split_char , std::vector<std::string>* output) {
        boost::split(*output , input , boost::is_any_of(split_char) , boost::token_compress_off);
    }
};

class UrlUtil {
public:
    static void ParseBody(const std::string& body ; std::unordered_map<std::string , std::string>* params) {
        // 1.先对这里的 body 字符串切分成键值对的形式；
        //   a）先按照 & 切分
        //   b）再按照 = 切分
        std::vector<std::string> kvs;
        StringUtil::Split(body , "&" , &kvs);
        for (size_t i = 0 ; i < kvs.size() ; ++i) {
            std::vector<std::string> kv;
            // kvs[i]里面存的是一个键值对
            StringUtil::(kvs[i] , "=" , &kv);

        }
        // 2.对这里的键值对进行 urldecode
        
    }
};























