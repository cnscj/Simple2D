
/**
 * @file hash.h
 * @The header file of md5.
 * @author zouxiaoliang
 * @mail weijieweijerry@163.com
 * @github https://gitee.com/www.evangerlion.com/hash.git
 * @data Oct 19 2015
 *
 */
#ifndef _SHASH_H_
#define _SHASH_H_

#include <stdint.h>
#include <stdlib.h>
#include <string>

namespace HashSpace {
    /**
     * @brief hash 字符串哈希算法
     * @param str 待hash的字符串
     * @param str_len 字符串长度
     * @param hash_type 哈希偏移标识
     * @param case_sensitive 是否大消息敏感，默认是敏感的
     * @return 哈希值
     */
    uint64_t hash(const char *str, size_t str_len, uint32_t hash_type = 1, bool case_sensitive = true);
    //}
    
    //namespace HashSpace {
    
    /// @brief 哈希表
    static uint64_t s_crypt_table[0x500];
    
    /**
     * @brief init_hash_table 初始化hash表
     * @return 0 成功； 1 表示已经初始化
     */
    int init_hash_table();
    
    /**
     * @brief hash 字符串哈希算法
     * @param str 待hash的字符串
     * @param str_len 字符串长度
     * @param hash_type 哈希偏移标识
     * @param case_sensitive 是否大消息敏感，默认是敏感的
     * @return 哈希值
     */
    uint64_t hash(const char* str, size_t str_len, uint32_t hash_type, bool case_sensitive);

    /**
     * @brief The HashInit class 哈希表初始类
     */
    class HashInit
    {
    public:
        HashInit();
    };
    
    /// @brief 程序启动前初始化哈希表
    extern const HashInit hash_init;

}

class SHash
{
public:
    SHash(std::string str="");
    ~SHash();
public:
    uint64_t ToHash();
    std::string ToStrHash();
private:
    std::string m_strSrc;
};
#endif //_S2HASH_H_

