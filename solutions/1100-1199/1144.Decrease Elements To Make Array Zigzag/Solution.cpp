// 题目：1144. 递减元素使数组呈锯齿状（Decrease Elements To Make Array Zigzag）
// 思路：枚举两种锯齿形态（偶数下标为谷或奇数下标为谷），对每个峰位置计算必须减到比两侧都小所需的步数，取两种方案的最小值。
// 时间复杂度：O(n)，两种形态各扫一半元素；空间复杂度：O(1)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int movesToMakeZigzag(vector<int>& nums) {  // nums 是待调整的数组，只能把元素减小，返回使它变成锯齿数组的最少操作次数
        vector<int> ans(2);  // ans[0]、ans[1] 分别记录两种形态所需的操作数
        int n = nums.size();  // 数组长度
        for (int i = 0; i < 2; ++i) {  // i=0 表示偶数下标做谷，i=1 表示奇数下标做谷，两种形态都要试
            for (int j = i; j < n; j += 2) {  // 只遍历属于「谷」的那一半下标，步长为 2
                int d = 0;  // 本位置需要减少的量，初始为 0
                if (j) d = max(d, nums[j] - nums[j - 1] + 1);  // 不是首元素时，必须比左边小，减到 nums[j-1]-1 才满足
                if (j < n - 1) d = max(d, nums[j] - nums[j + 1] + 1);  // 不是末元素时，必须比右边小，两边要求取较大的减少量
                ans[i] += d;  // 累加到对应形态的总操作数
            }  // 谷位置遍历结束
        }  // 形态遍历结束
        return min(ans[0], ans[1]);  // 两种形态取较小者即为最优
    }  // 方法结束
};  // 类定义结束