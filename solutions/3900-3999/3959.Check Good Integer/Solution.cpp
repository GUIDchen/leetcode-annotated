// 3959. 判定好整数 / Check Good Integer
// 核心思路：不断取出 n 的十进制末位数字 x，累加每位的贡献 x * (x-1)，最后判断总和是否达到 50。
// 复杂度：时间 O(log n)（十进制位数），空间 O(1)。

class Solution {
public:
    bool checkGoodInteger(int n) {  // 判断整数 n 是否为“好整数”
        int s = 0;  // 保存各位数字贡献的累加和
        for (; n > 0; n /= 10) {  // 每轮处理最低位，随后把 n 去掉末位，直到 n 为 0
            int x = n % 10;  // 取出当前的十进制最低位数字
            s += x * (x - 1);  // 该位贡献 x * (x-1)，累加进总和
        }
        return s >= 50;  // 总和达到 50 及以上即返回 true
    }
};
