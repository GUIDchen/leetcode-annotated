// 3659. Partition Array Into K-Distinct Groups（3659. 数组元素分组）
// 核心思路：每组大小固定为 k 且组内元素互不相同，故元素出现次数不能超过组数 m = n / k；先判能否均分，再统计最大频次是否超标。
// 复杂度：时间 O(n + max(nums))，空间 O(max(nums))。
class Solution {  // 定义题解类
public:  // 公有成员，供判题器调用
    bool partitionArray(vector<int>& nums, int k) {  // 判断能否把 nums 分成若干大小为 k 且组内互不相同的组
        int n = nums.size();  // 数组长度
        if (n % k) {  // 长度不是 k 的整数倍，无法均分
            return false;  // 无法分组，直接失败
        }  // 结束边界判断
        int m = n / k;  // 最多能把数组分成 m 组，每组恰好 k 个
        int mx = *ranges::max_element(nums);  // 找出最大值，用于确定计数数组的大小
        vector<int> cnt(mx + 1);  // 统计每个取值出现的次数
        for (int x : nums) {  // 遍历数组中的每个元素
            if (++cnt[x] > m) {  // 某元素出现次数超过组数 m，必然有两份落在同一组
                return false;  // 组内出现重复，无法完成分组
            }  // 结束计数循环
        }  // 结束循环体
        return true;  // 所有元素出现次数都不超过 m，可以完成分组
    }  // 结束方法
};  // 结束题解类
