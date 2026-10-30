// 3660. Jump Game IX（3660. 跳跃游戏 IX）
// 核心思路：用前缀最大值 preMax 与后缀最小值 sufMin 判断能否越过当前位置继续向右借力，从右往左一维递推得到每个起点的答案。
// 复杂度：时间 O(n)，空间 O(n)。
class Solution {  // 定义题解类
public:  // 公有成员，供判题器调用
    vector<int> maxValue(vector<int>& nums) {  // 计算从每个位置出发所能到达的数值上界
        int n = nums.size();  // 数组长度
        vector<int> ans(n);  // 答案数组
        vector<int> preMax(n, nums[0]);  // preMax[i] 表示 nums[0..i] 的前缀最大值
        for (int i = 1; i < n; ++i) {  // 从左到右递推前缀最大值
            preMax[i] = max(preMax[i - 1], nums[i]);  // 取前一个前缀最大值与当前元素的较大者
        }  // 结束前缀递推
        int sufMin = 1 << 30;  // 后缀最小值，初值取足够大的数
        for (int i = n - 1; i >= 0; --i) {  // 从右往左处理每个起点
            ans[i] = preMax[i] > sufMin ? ans[i + 1] : preMax[i];  // 前缀最大值大于后缀最小值时可继续向右，继承 i+1 的答案
            sufMin = min(sufMin, nums[i]);  // 把 nums[i] 并入后缀最小值
        }  // 结束后缀递推
        return ans;  // 返回答案数组
    }  // 结束方法
};  // 结束题解类
