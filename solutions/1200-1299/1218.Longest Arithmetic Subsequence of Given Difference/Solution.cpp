// 题目：1218. 最长定差子序列（Longest Arithmetic Subsequence of Given Difference）
// 思路：以序列末项的值作为状态，f[x] = f[x-difference] + 1；一次遍历按原数组顺序递推即可。
// 时间复杂度：O(n)，每项只做一次哈希查找与写入；空间复杂度：O(n)，哈希表最多保存 n 个不同的值。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int longestSubsequence(vector<int>& arr, int difference) {  // arr：原数组；difference：要求的公差（可正可负）
        unordered_map<int, int> f;  // 哈希表 f[x]：以值 x 结尾的最长定差子序列长度
        int ans = 0;  // ans：记录所有状态中的最大值
        for (int x : arr) {  // 按原数组顺序遍历，天然保证了子序列的下标递增
            f[x] = f[x - difference] + 1;  // 接在值 x-difference 结尾的序列后面；该键不存在时 operator[] 会默认插入 0，正好得到长度 1
            ans = max(ans, f[x]);  // 用新状态更新全局答案
        }  // 遍历结束
        return ans;  // 返回最长定差子序列的长度
    }  // 方法结束
};  // 类定义结束