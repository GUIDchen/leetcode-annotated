// 题目：2570. 合并两个二维数组 - 求和法（Merge Two 2D Arrays by Summing Values）
// 思路：id 范围只有 1 ~ 1000，用一个计数数组把两个数组里同 id 的 value 累加起来，再按 id 升序输出非零项。
// 时间复杂度：O(n + m + 1000)，与数据规模线性相关；空间复杂度：O(1000)，即固定的计数数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<int>> mergeArrays(vector<vector<int>>& nums1, vector<vector<int>>& nums2) {  // 两个按 id 升序排列的 [id, value] 数组
        int cnt[1001]{};  // 计数数组：cnt[id] 存该 id 的 value 之和；{} 让全部元素初始化为 0，下标 1 ~ 1000 有效
        for (auto& x : nums1) {  // 遍历第一个数组
            cnt[x[0]] += x[1];  // 把 id 为 x[0] 的项的 value（x[1]）累加到对应位置
        }
        for (auto& x : nums2) {  // 遍历第二个数组
            cnt[x[0]] += x[1];  // 同 id 的 value 继续累加，自动完成「求和合并」
        }
        vector<vector<int>> ans;  // 存放合并结果，天然按 id 升序
        for (int i = 0; i < 1001; ++i) {  // 从小到大扫描所有可能的 id
            if (cnt[i]) {  // 只输出实际出现过的 id（value 之和为 0 的项按题意也不存在）
                ans.push_back({i, cnt[i]});  // 把 [id, 累加后的 value] 追加到答案
            }
        }
        return ans;  // 返回合并后的二维数组
    }
};