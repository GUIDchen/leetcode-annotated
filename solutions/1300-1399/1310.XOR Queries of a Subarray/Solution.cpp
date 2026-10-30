// 题目：1310. 子数组异或查询（XOR Queries of a Subarray）
// 核心思路：构造前缀异或数组 s，s[i] = arr[0]^...^arr[i-1]；由 x^x=0 可知区间 [l, r] 的异或等于 s[r+1] ^ s[l]。
// 时间复杂度：O(n + q)，预处理 O(n)、每个查询 O(1)；空间复杂度：O(n)，存放前缀异或数组与答案。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> xorQueries(vector<int>& arr, vector<vector<int>>& queries) {  // arr 是原数组，queries 是若干 [l, r] 查询
        int n = arr.size();  // 数组长度
        int s[n + 1];  // 前缀异或数组，多开一位放 s[0] = 0（变长数组，GCC 扩展）
        memset(s, 0, sizeof(s));  // 全部清零，保证 s[0] = 0
        for (int i = 1; i <= n; ++i) {  // 从左到右递推前缀异或
            s[i] = s[i - 1] ^ arr[i - 1];  // 前 i 个元素的异或 = 前 i-1 个异或再异或上第 i 个元素
        }
        vector<int> ans;  // 存放每个查询的答案
        for (auto& q : queries) {  // 依次处理每个查询
            int l = q[0], r = q[1];  // 取出查询区间的左右端点
            ans.push_back(s[r + 1] ^ s[l]);  // 异或的前缀差：抵消掉 [0, l-1] 的部分，只剩 [l, r]
        }
        return ans;  // 返回所有查询的结果
    }
};  // 类定义结束（文件末尾无换行，保持原样）