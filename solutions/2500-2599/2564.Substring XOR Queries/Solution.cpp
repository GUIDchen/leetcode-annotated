// 题目：2564. 子字符串异或查询（Substring XOR Queries）
// 核心思路：预处理 s 的所有长度不超过 32 的二进制子串，把「数值 → 首次出现的区间」存入哈希表；查询时先由 a ^ b 求出目标值再直接查表。
// 时间复杂度：O(32n + q)，n 为字符串长度、q 为查询数；空间复杂度：O(32n)，哈希表最多保存这么多个不同数值。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<int>> substringXorQueries(string s, vector<vector<int>>& queries) {  // s：二进制字符串；queries：若干 [first, second]
        unordered_map<int, vector<int>> d;  // 键是子串的二进制数值，值是它首次出现时的 [左下标, 右下标]
        int n = s.size();  // 字符串长度
        for (int i = 0; i < n; ++i) {  // 枚举子串的左端点 i
            int x = 0;  // 从空串开始累积二进制数值
            for (int j = 0; j < 32 && i + j < n; ++j) {  // 子串长度最多 32 位（更长会溢出 int，且答案也用不到）
                x = x << 1 | (s[i + j] - '0');  // 整体左移一位，再把当前字符的 0/1 拼到最低位
                if (!d.count(x)) {  // 只保留第一次出现，对应的就是该数值最短的区间
                    d[x] = {i, i + j};  // 记录区间左右端点
                }
                if (x == 0) {  // 数值为 0 时继续追加前导 0 仍是 0，无需再扩展
                    break;  // 提前结束内层循环
                }
            }
        }
        vector<vector<int>> ans;  // 按查询顺序存放答案
        for (auto& q : queries) {  // 逐个处理查询
            int first = q[0], second = q[1];  // 查询给出的两个数
            int val = first ^ second;  // 由 first ^ second = val 直接得到需要查找的子串数值
            if (d.count(val)) {  // 该数值确实作为某个子串出现过
                ans.emplace_back(d[val]);  // 原地构造，直接拷贝记录的区间
            } else {  // 没有这样的子串
                ans.push_back({-1, -1});  // 按题目要求返回 [-1, -1]
            }
        }
        return ans;  // 返回全部查询结果
    }
};