// 题目：2122. 还原原数组（Recover the Original Array）
// 核心思路：排序后把 nums[0] 与 nums[i] 视为最小的一对（差 d = 2k），再双指针把剩余元素按差值 d 两两配对。
// 时间复杂度：O(n^2)，最坏枚举 n 个配对起点并各扫一遍；空间复杂度：O(n)，vis 标记与答案数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> recoverArray(vector<int>& nums) {  // nums：被打乱并加入 k 偏移后的数组
        sort(nums.begin(), nums.end());  // 先排序，让配对关系只可能发生在有序序列的相邻候选之间
        for (int i = 1, n = nums.size(); i < n; ++i) {  // 枚举与 nums[0] 配对的那个元素下标 i
            int d = nums[i] - nums[0];  // d 应等于 2k，是这一对之间的差值
            if (d == 0 || d % 2 == 1) continue;  // 差为 0 说明重复，差为奇数则除不尽，都无法还原出整数 k
            vector<bool> vis(n);  // vis 标记排序后哪些元素已经被配对使用
            vis[i] = true;  // nums[0] 与 nums[i] 配成第一对，标记 nums[i] 已用
            vector<int> ans;  // 收集还原出的原数组元素（即每一对的中点）
            ans.push_back((nums[0] + nums[i]) >> 1);  // 一对的中点就是原数组元素，右移一位等价于除以 2
            for (int l = 1, r = i + 1; r < n; ++l, ++r) {  // l 找未用的较小值，r 找比它大 d 的较大值
                while (l < n && vis[l]) ++l;  // 跳过已经被配对掉的较小值
                while (r < n && nums[r] - nums[l] < d) ++r;  // 差值不够 d 就继续往后找较大值
                if (r == n || nums[r] - nums[l] > d) break;  // 找不到恰好差 d 的配对，这个 i 不成立
                vis[r] = true;  // 标记这个较大值已被使用
                ans.push_back((nums[l] + nums[r]) >> 1);  // 这一对的中点同样是原数组中的一个元素
            }
            if (ans.size() == (n >> 1)) return ans;  // 恰好配出 n/2 对，说明还原成功
        }
        return {};  // 题目保证有解，理论上不会走到这里
    }
};