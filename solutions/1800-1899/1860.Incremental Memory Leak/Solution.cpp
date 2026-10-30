// 题目：1860. 增长的内存泄露（Incremental Memory Leak）
// 思路：直接模拟。第 i 秒要消耗 i 个单位，每次从两块中较大的一块扣减（相等时选 memory1）；一旦较大的一块都不够 i，就说明第 i 秒崩溃，返回 i 与两块剩余容量。
// 时间复杂度：O(√(memory1 + memory2))，i 从 1 递增，累加和超过总容量即停；空间复杂度：O(1)，只用常数额外变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> memLeak(int memory1, int memory2) {  // memory1、memory2：两块内存的初始空闲容量
        int i = 1;  // 第 i 秒，每秒消耗 i 个单位
        for (; i <= max(memory1, memory2); ++i) {  // 较大的那块仍够第 i 秒消耗就继续；退出时 i 就是崩溃的那一秒
            if (memory1 >= memory2) {  // 优先消耗较大的那一块，相等时选 memory1，与题目的贪心规则一致
                memory1 -= i;  // 从 memory1 扣掉 i（此时它是较大者，必不会扣成负数）
            } else {  // 否则 memory2 才是较大者
                memory2 -= i;  // 从 memory2 扣掉 i
            }  // 分支结束
        }  // 循环结束
        return {i, memory1, memory2};  // 返回崩溃时刻 i 与两块剩余容量
    }  // 方法结束
};  // 类定义结束