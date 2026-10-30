// 题目：2789. 合并后数组中的最大元素（Largest Element in an Array after Merge Operations）
// 思路：从右往左扫描，用 t 记录右侧可合并段的和；左侧元素不大于 t 就并入，否则另起一段，途中取最大值。
// 时间复杂度：O(n)，只需一次反向遍历；空间复杂度：O(1)，只用了若干常量变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long maxArrayValue(vector<int>& nums) {  // nums：可以反复执行「合并相邻且左边不大于右边」的数组
        int n = nums.size();  // 数组长度
        long long ans = nums[n - 1], t = nums[n - 1];  // ans 记录历史最大值；t 表示当前这段可合并区间的和，初值为最后一个元素
        for (int i = n - 2; ~i; --i) {  // 从倒数第二个位置向左遍历；~i 等价于 i >= 0
            if (nums[i] <= t) {  // 左边的数不大于右侧段和，就可以并入这一段
                t += nums[i];  // 累加进当前段（long long 防止多元素求和溢出）
            } else {  // 否则这一段无法继续向左合并
                t = nums[i];  // 以当前元素作为新的段起点
            }  // if/else 结束
            ans = max(ans, t);  // 用当前段和更新全局最大值
        }  // for 结束
        return ans;  // 返回合并后数组中的最大元素
    }  // 方法结束
};  // 类定义结束