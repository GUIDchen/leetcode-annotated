// 题目：1518. 换水问题（Water Bottles）
// 思路：每换一次水，手里空瓶净减少 numExchange-1 个、喝到的瓶数加 1，模拟到空瓶不够换为止。
// 时间复杂度：O(n/numExchange)，交换次数不超过初始瓶数；空间复杂度：O(1)，只用两个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int numWaterBottles(int numBottles, int numExchange) {  // numBottles：初始满水瓶数；numExchange：多少个空瓶换一瓶；返回最多能喝到的瓶数
        int ans = numBottles;  // ans：喝到的总瓶数，初始满水瓶全部能喝掉
        for (; numBottles >= numExchange; ++ans) {  // 空瓶数量够换就继续；每成功换一次 ans 自增 1（省略初始化表达式）
            numBottles -= (numExchange - 1);  // 换来的 1 瓶喝完后空瓶净变化：先交出 numExchange 个，再拿回 1 个，故减去 numExchange-1
        }  // 结束交换循环
        return ans;  // 返回总共喝到的瓶数
    }  // 结束方法
};  // 结束题解类