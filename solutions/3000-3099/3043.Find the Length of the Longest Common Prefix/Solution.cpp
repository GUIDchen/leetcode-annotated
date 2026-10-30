// 题目：3043. 最长公共前缀的长度（Find the Length of the Longest Common Prefix）
// 核心思路：把 arr1 每个数的所有十进制前缀存入哈希集合，再对 arr2 的每个数从长到短查前缀，取数值最大的公共前缀，其位数即答案。
// 时间复杂度：O((n + m) * log10 V)，每个数只按位数枚举前缀；空间复杂度：O(n * log10 V)，保存 arr1 的全部前缀。
class Solution {
public:
    int longestCommonPrefix(vector<int>& arr1, vector<int>& arr2) {  // arr1、arr2：两个正整数数组，返回它们任意元素之间最长的公共十进制前缀长度
        unordered_set<int> s;  // 哈希集合：保存 arr1 中每个数的所有十进制前缀（含数字本身）
        for (int x : arr1) {  // 枚举 arr1 中的每个数
            for (; x; x /= 10) {  // 反复除以 10，从长到短枚举该数的所有前缀
                s.insert(x);  // 把当前前缀加入集合，重复插入由集合自动去重
            }
        }
        int mx = 0;  // mx：两个数组公共前缀中数值最大的那个
        for (int x : arr2) {  // 枚举 arr2 中的每个数
            for (; x; x /= 10) {  // 同样从长到短枚举当前数的前缀，先命中就是最长的
                if (s.count(x)) {  // 该前缀在 arr1 的前缀集合中出现过，说明找到了公共前缀
                    mx = max(mx, x);  // 数值越大前缀越长，所以用 max 保留更大的那个
                    break;  // 当前数已取到最长公共前缀，继续缩短只会更短
                }
            }
        }
        return mx > 0 ? (int) log10(mx) + 1 : 0;  // 有公共前缀时 log10(mx)+1 就是它的十进制位数；mx 为 0 说明没有公共前缀
    }  // 方法结束
};  // 题解类结束
