// 3602. 十六进制和三十六进制转化 / Hexadecimal and Hexatrigesimal Conversion
// 核心思路：把 n 的平方转成十六进制、n 的立方转成三十六进制，共用一个“除 k 取余、末位逆序”的进制转换函数，最后把两段字符串拼接返回。
// 复杂度：时间 O(log n)，空间 O(log n)，即结果字符串的长度。
class Solution {  // 定义题解类
public:  // 公有接口部分
    string concatHex36(int n) {  // 主函数：返回 n^2 的十六进制与 n^3 的三十六进制拼接串
        int x = n * n;  // 先算 n 的平方，作为十六进制的转换对象
        int y = n * n * n;  // 再算 n 的立方，作为三十六进制的转换对象
        return f(x, 16) + f(y, 36);  // 两段进制转换结果直接拼接后返回
    }  // 主函数结束

private:  // 私有辅助函数部分
    string f(int x, int k) {  // 把十进制数 x 转换成 k 进制字符串
        string res;  // 结果的低位字符先追加，最后需要逆序
        while (x > 0) {  // 不断取余直到 x 被除尽
            int v = x % k;  // 取出当前最低位数字
            if (v <= 9) {  // 0~9 的位用数字字符表示
                res += char('0' + v);  // 拼上对应的数字字符
            } else {  // 10 及以上的位用大写字母表示
                res += char('A' + v - 10);  // 拼上 A 起算的字母字符
            }  // 分支结束
            x /= k;  // 去掉已处理的最低位
        }  // 循环结束
        reverse(res.begin(), res.end());  // 此时的字符是低位在前，需要整体反转
        return res;  // 返回这一段的 k 进制表示
    }  // 辅助函数结束
};  // 类定义结束
