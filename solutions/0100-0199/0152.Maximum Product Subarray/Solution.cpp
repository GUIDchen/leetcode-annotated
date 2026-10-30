// 题目：152. 乘积最大子数组（Maximum Product Subarray）
// 思路：同时维护以当前元素结尾的最大乘积 f 与最小乘积 g（负数乘负会变正），每步在“只取自身/接最大值/接最小值”中取最值。
// 时间复杂度：O(n)，一次遍历；空间复杂度：O(1)，只用常数个变量。
class Solution {  // 题目要求的题解类
public:  // 对外提供 maxProduct 方法
    int maxProduct(vector<int>& nums) {  // nums 为整数数组，返回连续子数组的最大乘积
        int f = nums[0], g = nums[0], ans = nums[0];  // f：以当前元素结尾的最大乘积；g：最小乘积；ans：全局答案。都先以首元素初始化
        for (int i = 1; i < nums.size(); ++i) {  // 从第二个元素开始递推
            int ff = f, gg = g;  // 暂存上一轮的 f、g，避免本轮更新后互相污染
            f = max({nums[i], ff * nums[i], gg * nums[i]});  // 新最大值在“只取自身”“接上一轮最大”“接上一轮最小”三者中取最大
            g = min({nums[i], ff * nums[i], gg * nums[i]});  // 最小值同样在这三者中取最小
            ans = max(ans, f);  // 用当前最大值更新答案
        }  // 遍历结束
        return ans;  // 返回全局最大乘积
    }  // maxProduct 方法结束
};  // Solution 类定义结束