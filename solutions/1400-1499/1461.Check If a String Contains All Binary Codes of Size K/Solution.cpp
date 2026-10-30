// 题目：1461. 检查一个字符串是否包含所有长度为 K 的二进制子串（Check If a String Contains All Binary Codes of Size K）
// 思路：长度为 k 的二进制串共 2^k 种，把所有滑动窗口截出的子串放进哈希集合去重，最后看集合大小是否等于 2^k；先用子串个数做可行性剪枝。
// 时间复杂度：O(n×k)，每个窗口截取 k 长字符串；空间复杂度：O(n×k)，集合中最多存 n-k+1 个 k 长子串。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool hasAllCodes(string s, int k) {  // s：二进制字符串；k：子串长度
        int n = s.size();  // 字符串长度 n
        int m = 1 << k;  // 长度为 k 的二进制串共有 2^k 种，用移位快速算出
        if (n - k + 1 < m) {  // 子串总数为 n-k+1，若比 2^k 还少，必然无法覆盖全部编码
            return false;  // 提前判否，避免无谓的哈希建表
        }  // if 语句块结束
        unordered_set<string> ss;  // 哈希集合：存放出现过的所有长度 k 子串，天然去重
        for (int i = 0; i + k <= n; ++i) {  // i 为窗口左端点，保证 i+k 不越界
            ss.insert(move(s.substr(i, k)));  // substr 截出长度 k 的子串，move 把临时串移动进集合以减少拷贝
        }  // for 循环体结束
        return ss.size() == m;  // 集合大小等于 2^k，说明每种编码都至少出现一次
    }  // 方法体结束
};  // 类定义结束
