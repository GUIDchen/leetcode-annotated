// 题目：535. TinyURL 的加密与解密（Encode and Decode TinyURL）
// 思路：自增计数当短码，用哈希表建立「短码 → 原链接」的映射；解密时切掉域名前缀取出短码再查表。
// 时间复杂度：encode / decode 均为 O(L)，L 为链接长度（字符串拷贝与查表）；空间复杂度：O(n*L)，保存所有链接。
class Solution {  // LeetCode 约定的题解类
public:  // 编码、解码接口对外可见
    // Encodes a URL to a shortened URL.  // 编码：把长链接换成一个短的
    string encode(string longUrl) {  // longUrl 是原始长链接
        string v = to_string(++idx);  // 先自增计数器再转字符串，得到全局唯一的短码
        m[v] = longUrl;  // 用短码作键把原链接存进哈希表，解密时靠它还原
        return domain + v;  // 拼上固定域名作为短链接返回
    }

    // Decodes a shortened URL to its original URL.  // 解码：把短链接还原成原来的长链接
    string decode(string shortUrl) {  // shortUrl 是编码得到的短链接
        int i = shortUrl.rfind('/') + 1;  // 找最后一个 '/' 的下一位，即短码的起始下标
        return m[shortUrl.substr(i, shortUrl.size() - i)];  // 从短码起点截到末尾，查表拿回原链接
    }

private:  // 以下成员只给 encode / decode 内部使用
    unordered_map<string, string> m;  // 短码 → 原链接 的映射表
    int idx = 0;  // 自增计数器，保证每次编码得到的短码都不相同
    string domain = "https://tinyurl.com/";  // 短链接的固定域名前缀
};

// Your Solution object will be instantiated and called as such:
// Solution solution;
// solution.decode(solution.encode(url));