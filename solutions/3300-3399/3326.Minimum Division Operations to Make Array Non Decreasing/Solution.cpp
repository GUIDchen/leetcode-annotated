// 题目：3326. 使数组非递减的最少除法操作次数（Minimum Division Operations to Make Array Non Decreasing）
// 思路：先筛出每个数的最小质因子；从右往左贪心，逆序时把 nums[i] 除成它的最小质因子（一次操作能取到的最小值），仍逆序即返回 -1。
// 时间复杂度：O(MX log log MX + n)，MX = 10^6；空间复杂度：O(MX)，存放最小质因子表。
const int MX = 1e6;  // 元素上界是 1e6，筛法只要筛到这个数
int LPF[MX + 1];  // LPF[x] 保存 x 的最小质因子，全局数组默认全为 0

auto init = [] {  // 立即执行的 lambda：程序启动时先把整张最小质因子表筛好
    for (int i = 2; i <= MX; i++) {  // 从小到大枚举可能的质因子
        if (LPF[i] == 0) {  // 还没被更小的数标记过，说明 i 本身是质数
            for (int j = i; j <= MX; j += i) {  // 用质数 i 去扫它的所有倍数
                if (LPF[j] == 0) {  // 只标记尚未赋值的位置，先到先得保证留下的是最小质因子
                    LPF[j] = i;  // 记下 j 的最小质因子是 i
                }  // if 结束
            }  // 倍数扫描结束
        }  // if 结束
    }  // 枚举结束，整张表已建好
    return 0;  // 返回 0，顺带把 lambda 的返回类型定为 int
}();  // 末尾的 () 表示立刻调用，返回值赋给全局变量 init

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minOperations(vector<int>& nums) {  // nums：允许把某个元素换成它的真因子的数组
        int ans = 0;  // 累计除法操作次数
        for (int i = nums.size() - 2; i >= 0; i--) {  // 从倒数第二个元素往左扫：右边已经定好，左边只需不超过它
            if (nums[i] > nums[i + 1]) {  // 出现逆序，必须把 nums[i] 变小
                nums[i] = LPF[nums[i]];  // 一次操作能变到的最小值，就是除以它的最小质因子
                if (nums[i] > nums[i + 1]) {  // 变成最小之后仍然大于右边，后面无从补救
                    return -1;  // 无解
                }  // if 结束
                ans++;  // 这次除法计入操作次数
            }  // if 结束
        }  // 扫描结束，数组已非递减
        return ans;  // 返回最少操作次数
    }  // 方法结束
};  // 类定义结束
