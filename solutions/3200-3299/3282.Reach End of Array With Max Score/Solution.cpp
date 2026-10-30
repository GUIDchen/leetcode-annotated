// 3282. 到达数组末尾的最大得分（Reach End of Array With Max Score）
// 核心思路：得分为每次跳跃长度乘以起跳位置的值，等价于把每个位置（除末尾外）都乘上它之前的前缀最大值再求和；因此逐步维护前缀最大值并累加即可。
// 复杂度：时间 O(n)，空间 O(1)

class Solution {  // 定义题解类
public:  // 公开接口
    long long findMaximumScore(vector<int>& nums) {  // 返回从下标 0 跳到最后一个下标能获得的最大得分
        long long ans = 0;  // 累计得分，可能超过 int 范围，用 long long
        int mx = 0;  // 到目前为止见过的最大值
        for (int i = 0; i + 1 < nums.size(); ++i) {  // 枚举每一次跳跃的起点（最后一个元素不需要再作为起点）
            mx = max(mx, nums[i]);  // 维护前缀最大值
            ans += mx;  // 每步都可以直接跳到历史最大值所在位置，故累加该最大值
        }  // 结束枚举
        return ans;  // 返回最大得分
    }  // 方法结束
};  // 类定义结束
