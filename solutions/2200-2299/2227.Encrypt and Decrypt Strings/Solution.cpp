// 题目：2227. 加密解密字符串（Encrypt and Decrypt Strings）
// 思路：加密用「明文字符 → 密文」映射正向替换；解密不逐字符回溯，而是在构造时把每个字典词加密并统计密文出现次数，解密直接查表。
// 时间复杂度：构造 O(D·L)，encrypt O(L)，decrypt O(1)；空间复杂度：O(D·L)，D 为字典词数、L 为单词长度。
class Encrypter {  // 题目要求的加密器类
public:  // 字段与方法对外可见
    unordered_map<string, int> cnt;  // 密文 → 能加密成该密文的字典单词个数，用于 O(1) 解密
    unordered_map<char, string> mp;  // 明文字符 → 两位密文，用于加密

    Encrypter(vector<char>& keys, vector<string>& values, vector<string>& dictionary) {  // 构造函数：建立加密映射，并预处理字典里每个词的密文词频
        for (int i = 0; i < keys.size(); ++i) {  // 遍历 keys，把每个明文字符与对应的密文配对
            mp[keys[i]] = values[i];  // 记录该字符的密文映射
        }
        for (auto v : dictionary) {  // 逐个字典词求密文
            cnt[encrypt(v)]++;  // 同一个密文可能由多个字典词得到，因此累加计数
        }
    }

    string encrypt(string word1) {  // 加密：把明文逐字符替换成对应密文
        string res = "";  // 结果串从空开始逐步拼接
        for (char c : word1) {  // 遍历明文的每个字符
            if (!mp.count(c)) {  // 该字符不在映射表中，说明无法加密
                return "";  // 按题意返回空串表示加密失败
            }
            res += mp[c];  // 追加该字符对应的密文
        }
        return res;  // 返回拼好的完整密文
    }

    int decrypt(string word2) {  // 解密：返回能加密成 word2 的字典单词个数
        return cnt[word2];  // 直接查预处理好的词频表，未出现过的密文默认计 0
    }
};

// 下面是 LeetCode 判题器自动生成的调用示例，不属于题解实现
/**
 * Your Encrypter object will be instantiated and called as such:
 * Encrypter* obj = new Encrypter(keys, values, dictionary);
 * string param_1 = obj->encrypt(word1);
 * int param_2 = obj->decrypt(word2);
 */
