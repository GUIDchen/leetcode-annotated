// 3727. Maximum Alternating Sum of Squares（最大交替平方和）
// 核心思路：先把每个元素平方（非负），排序后让较小的前一半取负、较大的后一半取正，即可使交替和最大。
// 复杂度：时间 O(n log n)（排序），空间 O(1)（原地修改）。

class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums) {  // 返回数组元素平方后能得到的最大交替和
        for (int& x : nums) {  // 遍历数组，把每个元素原地替换为它的平方
            x = x * x;  // 用引用取出元素并平方
        }  // 平方遍历结束
        ranges::sort(nums);  // 平方后升序排序，便于把小的放负号位、大的放正号位
        long long ans = 0;  // ans 保存交替和
        int m = nums.size() >> 1;  // m 为元素个数的一半，前 m 个相加时取负号
        for (int i = 0; i < nums.size(); ++i) {  // 按下标遍历排序后的数组
            ans += i < m ? -nums[i] : nums[i];  // 前一半（较小值）取负、后一半（较大值）取正，交替和最大
        }  // 遍历结束
        return ans;  // 返回最大交替和
    }  // 函数结束
};  // 题解类结束
