// 题目：2053. 数组中第 K 个独一无二的字符串（Kth Distinct String in an Array）
// 思路：先用哈希表统计每个字符串的出现次数，再按原数组顺序扫描，数到第 k 个出现次数为 1 的字符串即为答案。
// 时间复杂度：O(n)，两次线性扫描；空间复杂度：O(n)，哈希表保存不同字符串的出现次数。
class Solution {  // 题解类
public:  // 对外接口
    string kthDistinct(vector<string>& arr, int k) {  // arr 是字符串数组，k 是要求的第 k 个独一无二字符串
        unordered_map<string, int> cnt;  // 哈希表统计每个字符串的出现次数
        for (const auto& s : arr) {  // 第一遍扫描：统计频次
            ++cnt[s];  // 出现次数加一
        }  // 统计结束
        for (const auto& s : arr) {  // 第二遍按原顺序扫描，保证“第 k 个”的顺序性
            if (cnt[s] == 1 && --k == 0) {  // 独一无二的字符串计数减一，减到 0 就是答案
                return s;  // 返回第 k 个独一无二的字符串
            }  // 判断结束
        }  // 扫描结束
        return "";  // 不足 k 个独一无二字符串，按题目要求返回空串
    }  // 方法结束
};  // 类定义结束
