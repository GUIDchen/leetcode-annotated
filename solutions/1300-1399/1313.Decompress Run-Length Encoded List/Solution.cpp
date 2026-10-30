// 题目：1313. 解压缩编码列表（Decompress Run-Length Encoded List）
// 核心思路：nums 以 (freq, val) 成对出现，顺序遍历每对，把 val 连续追加 freq 次即可。
// 时间复杂度：O(n + 答案长度)；空间复杂度：O(答案长度)，即结果数组本身。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> decompressRLElist(vector<int>& nums) {  // nums 是形如 [f1, v1, f2, v2, ...] 的编码数组
        vector<int> ans;  // 存放展开后的结果
        for (int i = 0; i < nums.size(); i += 2) {  // 每步跨两个元素，一次处理一组
            for (int j = 0; j < nums[i]; j++) {  // nums[i] 是频次，循环这么多次
                ans.push_back(nums[i + 1]);  // 把对应的值 nums[i+1] 追加进答案
            }
        }
        return ans;  // 返回解压后的列表
    }
};
