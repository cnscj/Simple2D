#include "SHash.h"

int HashSpace::init_hash_table()
{
    static bool is_init =  false;
    if (is_init)
    {
        return 1;
    }
    memset(s_crypt_table, 0x0, sizeof(s_crypt_table));
    
    uint64_t seed = 0x00100001, index1 = 0, index2 = 0, i;
    
    for( index1 = 0; index1 < 0x100; ++index1 )
    {
        for( index2 = index1, i = 0; i < 5; ++i, index2 += 0x100 )
        {
            uint64_t temp1, temp2;
            seed = (seed * 125 + 3) % 0x2AAAAB;
            temp1 = (seed & 0xFFFF) << 0x10;
            seed = (seed * 125 + 3) % 0x2AAAAB;
            temp2 = (seed & 0xFFFF);
            s_crypt_table[index2] = ( temp1 | temp2 );
        }
    }
    
    return 0;
}

/**
 * @brief hash 字符串哈希算法
 * @param str 待hash的字符串
 * @param str_len 字符串长度
 * @param hash_type 哈希偏移标识
 * @param case_sensitive 是否大消息敏感，默认是敏感的
 * @return 哈希值
 */
uint64_t HashSpace::hash(const char* str, size_t str_len, uint32_t hash_type, bool case_sensitive)
{
    const unsigned char *key = reinterpret_cast<const unsigned char *>(str);
    size_t index = 0;
    
    uint64_t seed1 = 0x7FED7FED, seed2 = 0xEEEEEEEE;
    uint32_t ch;
    
    while( 0 != *key && index < str_len )
    {
        ch = *key++;
        
        // 大小写敏感的计算，将大写的英文字母转换成小写字母
        if (!case_sensitive)
        {
            if( ch >= 'A' && ch <= 'Z' )
            {
                ch += 'a' - 'A';
            }
        }
        
        seed1 = s_crypt_table[(hash_type << 8) + ch] ^ (seed1 + seed2);
        seed2 = ch + seed1 + seed2 + (seed2 << 5) + 3;
        
        ++index;
    }
    
    return seed1;
}


/// @brief 程序启动前初始化哈希表
const HashSpace::HashInit hash_init = HashSpace::HashInit();

HashSpace::HashInit::HashInit()
{
    HashSpace::init_hash_table();
}

/////
SHash::SHash(std::string str)
:m_strSrc(str)
{
    
}
SHash::~SHash()
{
    
}
uint64_t SHash::ToHash()
{
    return HashSpace::hash(m_strSrc.c_str(), m_strSrc.size());
}

std::string SHash::ToStrHash()
{
    uint64_t res = ToHash();
    char buffer[512];
#if defined __GNUC__ || defined __APPLE__
    sprintf(buffer, "%lu", res);
#else
    sprintf_s(buffer, "%lu", res);
#endif
    return std::string(buffer);
}
