// 题目：396. 旋转函数（Rotate Function）
// 思路：先按定义算出 F(0)，再用递推式 F(i) = F(i-1) + sum - n·nums[n-i] 依次推出其余 F 值并取最大。
// 时间复杂度：O(n)，两趟线性扫描；空间复杂度：O(1)，只保存当前 F 值、总和与答案。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxRotateFunction(vector<int>& nums) {  // nums 是输入数组，返回所有旋转方式中 F 的最大值
        long long f = 0, s = 0;  // f 表示当前 F 值，s 是数组元素总和
        int n = nums.size();  // 数组长度，后面多次用到
        for (int i = 0; i < n; ++i) {  // 按定义计算 F(0)，同时累加总和
            f += 1LL * i * nums[i];  // F(0) = 0*nums[0] + 1*nums[1] + 2*nums[2] + ...
            s += nums[i];  // 顺便把数组总和累加出来，供递推使用
        }
        long long ans = f;  // 答案先用 F(0) 初始化
        for (int i = 1; i < n; ++i) {  // 依次递推出 F(1) 到 F(n-1)
            f = f + s - 1LL * n * nums[n - i];  // 递推式：F(i) = F(i-1) + sum - n * nums[n-i]
            ans = max(ans, f);  // 用当前 F 值更新最大值
        }
        return (int) ans;  // 题目保证结果在 32 位范围内，转回 int 返回
    }
};