// 题目：271. 字符串的编码与解码（Encode and Decode Strings）
// 思路：每个字符串前拼接定长 4 字节的长度前缀（int 的内存表示），编码无需转义也天然无歧义；解码时先读长度再按长度截取。
// 时间复杂度：O(n)，n 为所有字符总数，编码/解码各扫描一遍；空间复杂度：O(n)，需要存放编码串与结果列表。
class Codec {  // 编解码器类：encode 打包成单个字符串，decode 再还原成列表
public:  // 两个方法都对外可见
    // Encodes a list of strings to a single string.
    string encode(vector<string>& strs) {  // strs：待编码的字符串列表
        string ans;  // 保存编码结果
        for (string s : strs) {  // 逐个取出字符串（按值拷贝，不改动入参）
            int size = s.size();  // 当前字符串长度，作为长度前缀
            ans += string((const char*) &size, sizeof(size));  // 把 int 的 4 个内存字节原样拼入结果，定长前缀无需分隔符
            ans += s;  // 再拼接字符串本身的内容
        }
        return ans;  // 返回编码后的单个字符串
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(string s) {  // s：由 encode 生成的编码串
        vector<string> ans;  // 保存解码出的字符串
        int i = 0, n = s.size();  // i：当前读取位置；n：编码串总长度
        int size = 0;  // 复用变量，用来存放读出的长度前缀
        while (i < n) {  // 只要没读完就继续取下一段
            memcpy(&size, s.data() + i, sizeof(size));  // 从当前位置拷回 4 个字节，还原出长度
            i += sizeof(size);  // 跳过长度前缀
            ans.push_back(s.substr(i, size));  // 按长度截取字符串内容放入结果
            i += size;  // 跳过这段正文
        }
        return ans;  // 返回解码后的字符串列表
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.decode(codec.encode(strs));