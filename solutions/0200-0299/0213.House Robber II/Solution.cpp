// 题目：213. 打家劫舍 II（House Robber II）
// 思路：首尾相邻成环，于是拆成两个线性区间分别做打家劫舍：不偷最后一户 / 不偷第 0 户，取两者较优。
// 时间复杂度：O(n)，两次线性扫描；空间复杂度：O(1)，只用常数个滚动变量。
class Solution {  // LeetCode 约定的题解类
public:  // 解题接口对外可见
    int rob(vector<int>& nums) {  // nums 是每户人家的金额，首尾两户相邻构成环
        int n = nums.size();  // 房屋数量
        if (n == 1) {  // 只有一户时首尾是同一户，单独处理
            return nums[0];  // 唯一能偷的就是这一户
        }  // if 分支结束
        return max(robRange(nums, 0, n - 2), robRange(nums, 1, n - 1));  // 两种情况取较优：偷第 0 户则不能偷最后一户，不偷第 0 户则最后一户可以偷
    }  // 方法结束

    int robRange(vector<int>& nums, int l, int r) {  // 在闭区间 [l, r] 上做打家劫舍（线性、无环）
        int f = 0, g = 0;  // f 表示当前这户不偷的最大收益，g 表示当前这户偷的最大收益
        for (; l <= r; ++l) {  // 逐个房屋向右推进，直接复用参数 l 当游标
            int ff = max(f, g);  // 这一户不偷：上一户偷与不偷取较大者
            g = f + nums[l];  // 这一户偷：上一户必须不偷，再加上本户金额
            f = ff;  // 更新不偷状态；上面先用 ff 暂存，避免 f 被提前覆盖
        }  // 区间遍历结束
        return max(f, g);  // 最后一个状态两种取较大者即为最优解
    }  // robRange 结束
};  // 类定义结束（源文件末尾没有换行符，此处保持原样）