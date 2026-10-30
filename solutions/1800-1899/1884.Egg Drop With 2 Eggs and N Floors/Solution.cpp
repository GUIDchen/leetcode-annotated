// 题目：1884. 鸡蛋掉落-两枚鸡蛋（Egg Drop With 2 Eggs and N Floors）
// 思路：动态规划，f[i] 表示确定 i 层楼所需的最少操作次数；第一次在第 j 层扔，碎了要线性查 j-1 层、没碎则递归到 f[i-j]，取最坏情况加 1。
// 时间复杂度：O(n^2)，两层循环；空间复杂度：O(n)，一维 DP 数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int twoEggDrop(int n) {  // n 是楼层总数
        int f[n + 1];  // f[i] 表示 i 层楼的最少操作次数（变长数组，题解片段写法）
        memset(f, 0x3f, sizeof(f));  // 全部填成 0x3f3f3f3f，充当无穷大
        f[0] = 0;  // 边界：0 层楼不需要任何操作
        for (int i = 1; i <= n; i++) {  // 自小到大递推楼层数
            for (int j = 1; j <= i; j++) {  // 枚举第一次扔鸡蛋的楼层 j
                f[i] = min(f[i], 1 + max(j - 1, f[i - j]));  // 碎了查 j-1 层，没碎查 i-j 层，取最坏情况再加本次操作
            }
        }
        return f[n];  // 返回 n 层楼的最少操作次数
    }
};
