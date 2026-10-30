// 3754. 连接非零数字并乘以其数字和 I（Concatenate Non-Zero Digits and Multiply by Sum I）
// 核心思路：从低位到高位取出每一位数字，跳过 0，用权值 p 把非零数字依次拼成新数 x，同时累加数字和 s，最后返回 x * s。
// 复杂度：时间 O(log n)（n 的位数），空间 O(1)。
class Solution {  // 定义解法类
public:  // 公有接口
    long long sumAndMultiply(int n) {  // 接口：返回把 n 的非零数字拼成的数乘以数字和
        int p = 1;  // p 为当前拼接位的权值（个位是 1，逐位乘 10）
        int x = 0, s = 0;  // x 保存拼接出的数，s 保存各数字之和
        for (; n > 0; n /= 10) {  // 从最低位到最高位逐位扫描 n
            int v = n % 10;  // 取出当前最低位数字 v
            if (v != 0) {  // 只有非零数字才参与拼接与求和
                s += v;  // 把 v 累加到数字和
                x += p * v;  // 把 v 放到权值 p 对应的拼接位上
                p *= 10;  // 权值扩大 10 倍，留给下一个非零数字
            }  // if 结束
        }  // for 结束
        return 1LL * x * s;  // 返回拼接数乘数字和，1LL 提升为 long long 防止溢出
    }  // 方法结束
};  // 类定义结束
